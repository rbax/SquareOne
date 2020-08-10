#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIcon>
#include <QFont>
#include <QBrush>
#include <QVariant>

#include "square.h"
#include "square-JsonModel.h"

JsonModel::JsonModel(const QStringList &_headers, QObject *_parent)
    : QAbstractItemModel(_parent),
    headerList_(_headers),
    rootItem_(new JsonItem) {

}

JsonModel::~JsonModel() {

    delete rootItem_;
}


/* |ITEM DATA HANDLING|
----------------------------------------------------------------- */

QVariant JsonModel::data(const QModelIndex &_index, int _role) const {

    if (_index.isValid()) {

        JsonItem *item(get_Item(_index));

        switch (_role) {

            case Qt::ForegroundRole: { // Text Color

                if (_index.column() == Column::Key) {

                    return QBrush(Qt::darkGray);
                }
                break;
            }

            case Qt::DecorationRole: { // Icons

                if (_index.column() == Column::Key) {

                    return iconList_.value(item->type_);
                }
                break;
            }

            case Qt::DisplayRole: // Read Only
            case Qt::EditRole: { // Read & Write

                if (_index.column() == Column::Key) {

                    return item->key_;
                }

                else {

                    return item->value(_index.column() - Column::Value);
                }
            }

            default: break;
        }
    }

    return QVariant();
}

bool JsonModel::setData(const QModelIndex &_index, const QVariant &_value, int _role) {

    if (_role != Qt::EditRole || _index.column() == Column::Key) {

        return false;
    }

    /* --------------------------------------------------------- [ITEM] */
    JsonItem *item(get_Item(_index)); {

        if (item->type_ == QJsonValue::Object) {

            return false;
        }
        else {

            item->updateValue(_value.toString(), (_index.column() - Column::Value));
        }
    }

    /* --------------------------------------------------------- [PARENT] */
    JsonItem *parent(item->parent_); {

        if (!parent) return false;

        if (parent->type_ == QJsonValue::Array) {

            item = parent;
        }
    }

    /* --------------------------------------------------------- [GRANDPARENT] */
    JsonItem *grandParent(parent->parent_); {

        if (grandParent &&
            grandParent->type_ == QJsonValue::Array) {

            item = grandParent;
        }
    }

    update(document_, get_Path(item), QJsonValue(item->jsonValue()));

    emit dataChanged(_index, _index);

    return true;
}

QVariant JsonModel::headerData(int _section, Qt::Orientation _orientation, int _role) const {

    if (_orientation == Qt::Horizontal && _role == Qt::DisplayRole) {

        return headerList_.value(_section);
    }

    return QVariant();
}

Qt::ItemFlags JsonModel::flags(const QModelIndex &_index) const {

    if (_index.isValid()) {

        return Qt::ItemIsEditable | QAbstractItemModel::flags(_index);
    }

    return 0;
}


/* NAVIGATION AND INDEX CREATION
----------------------------------------------------------------- */

QModelIndex JsonModel::index(int _row, int _column, const QModelIndex &_parent) const {

    if (hasIndex(_row, _column, _parent)) {

        JsonItem *parent(_parent.isValid()
                         ? static_cast<JsonItem*>(_parent.internalPointer())
                         : rootItem_);

        JsonItem *child(parent->child(_row)); {

            if (child) {

                return createIndex(_row, _column, child);
            }
        }
    }

    return QModelIndex();
}

QModelIndex JsonModel::parent(const QModelIndex &_index) const {

    if (_index.isValid()) {

        JsonItem *child(static_cast<JsonItem*>(_index.internalPointer()));
        JsonItem *parent(child->parent_);

        if (parent != rootItem_) {

            return createIndex(parent->row(), Column::Key, parent);
        }
    }

    return QModelIndex();
}

int JsonModel::rowCount(const QModelIndex &_parent) const {

    JsonItem *parent(_parent.isValid()
                     ? static_cast<JsonItem*>(_parent.internalPointer())
                     : rootItem_);

    return parent->childCount();
}

int JsonModel::columnCount(const QModelIndex &_parent) const {

    Q_UNUSED(_parent);

    return headerList_.size();
}


/* SETUP
----------------------------------------------------------------- */

bool JsonModel::loadJson(const QByteArray &_json) {

    document_ = QJsonDocument::fromJson(_json);

    if (document_.isNull()) {

        return false;
    }
    else {

        beginResetModel();

        rootItem_ = document_.isArray()
            ? JsonItem::load(QJsonValue(document_.array()))
            : JsonItem::load(QJsonValue(document_.object()));

        endResetModel();
    }

    return true;
}

/* --------------------------------------------------------- [PRIVATE] */

bool JsonModel::load(const QString &_fileName) {

    QFile file(_fileName);

    bool success(false);

    if (file.open(QIODevice::ReadOnly)) {

        success = load(&file);
        file.close();
    }

    return success;
}

void JsonModel::update(QJsonDocument &_document, const QString &_path, const QJsonValue &_value) {

    QJsonObject object(_document.object()); {

        update(object, _path, _value);
    }

    _document = QJsonDocument(object);
}

void JsonModel::update(QJsonObject &_object, const QString &_path, const QJsonValue &_value) {

    const int indexOfDot(_path.indexOf('.'));

    const QString key(_path.left(indexOfDot));

    const QString subPath((indexOfDot > 0)
                          ? _path.mid(indexOfDot + 1)
                          : QString());

    QJsonValue subValue(_object [key]); {

        if (subPath.isEmpty()) {

            subValue = _value;
        }

        else {

            if (subValue.type() == QJsonValue::Object) {

                QJsonObject object(subValue.toObject()); {

                    update(object, subPath, _value);
                    subValue = object;
                }
            }

            else {

                subValue = _value;
            }
        }
    }

    _object [key] = subValue;
}

JsonItem* JsonModel::get_Item(const QModelIndex &_index) const {

    JsonItem *item(_index.isValid()
                   ? static_cast<JsonItem*>(_index.internalPointer())
                   : rootItem_);
    return item;
}

QString JsonModel::get_Path(JsonItem *_item) {

    if (!_item) {

        return QString();
    }

    QString path(_item->key_ + "." + _item->toString()); {

        _item = _item->parent_;

        while (_item != rootItem_) {

            if (_item) {

                path.prepend(QString(_item->key_ + "."));
            }

            else {

                break;
            }

            _item = _item->parent_;
        }
    }

    return path;
}
