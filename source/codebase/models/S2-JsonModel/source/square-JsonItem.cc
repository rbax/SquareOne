
#include "square-JSONItem.h"
#include "square.h"

int JsonItem::row() const {

    return (parent_)
        ? parent_->children_.indexOf(const_cast<JsonItem*>(this))
        : 0;
}

JsonItem* JsonItem::load(const QJsonValue& _value, JsonItem* _parent) {

    JsonItem* rootItem(new JsonItem(_parent));
    rootItem->key_ = "root";

    switch (_value.type()) {

        /* ------------------------------------------------ (Array) */
        case QJsonValue::Array:
        {
            int index(0);
            foreach(QJsonValue value, _value.toArray()) {

                // @todo: must check to see if the array is full of values or value pairs

                if (value.isObject()) {

                    JsonItem* child(load(value, rootItem));
                    child->key_ = QString::number(index);
                    child->type_ = value.type();

                    rootItem->appendChild(child);
                    ++index;
                }
                else {
                    rootItem->values_.append(value.toVariant().toString());
                }
            }

            break;
        }
        /* ------------------------------------------------ (Object) */
        case QJsonValue::Object:
        {
            foreach(QString key, _value.toObject().keys()) {

                QJsonValue value(_value.toObject().value(key));

                JsonItem* child(load(value, rootItem));
                child->key_ = key;
                child->type_ = value.type();

                rootItem->appendChild(child);
            }

            break;
        }

        /* ------------------------------------------------ (default) */
        default:
        {
            rootItem->appendValue(_value.toVariant().toString());
            rootItem->type_ = _value.type();
            break;
        }
    }

    return rootItem;
}

QJsonValue JsonItem::jsonValue() {

    switch (type_) {

        /* ------------------------------------------------ (Object) */
        case QJsonValue::Object:
        {
            QJsonObject jObject;
            FOR_I(childCount()) {
                jObject.insert(child(i)->key_,
                               child(i)->jsonValue());
            }

            return QJsonValue(jObject);
        }

        /* ------------------------------------------------ (Array) */
        case QJsonValue::Array:
        {
            QJsonArray jArray;

            FOR_I(values_.size()) {
                jArray.append(QJsonValue(values_.at(i)));
            }

            return QJsonValue(jArray);
        }
    }

    return QJsonValue(value());
}

QString JsonItem::toString() {

    QString str("");
    switch (type_) {

        /* ------------------------------------------------ (Null) */
        case QJsonValue::Null:
        {
            str = "NULL";
            break;
        }

        /* ------------------------------------------------ (Object) */
        case QJsonValue::Object:
        {
            QStringList tempList;

            FOR_I(childCount()) {

                tempList.append(QString("\"%1\" : %2")
                                .arg(child(i)->key_)
                                .arg(child(i)->value())
                );
            }

            str = QString("{ %1 }")
                .arg(tempList.join(", "));

            break;
        }

        /* ------------------------------------------------ (Array) */
        case QJsonValue::Array:
        {
            str = values_.join(", ");
            break;
        }

        /* ------------------------------------------------ (default) */
        default:
        {
            str = value();
            break;
        }
    }

    return str;
}

QString JsonItem::toString(int _column) {

    if (type_ == QJsonValue::Object) {
        if (_column <= childCount()) {
            return child(_column - 1)->toString();
        }
    }
    else if (_column <= values_.size()) {
        return values_.at(_column - 1);
    }

    return QString();
}

QString JsonItem::value(int _itemNum) {

    QString value((values_.size() >= _itemNum + 1)
                  ? values_.at(_itemNum)
                  : QString());

    return value;
}

void JsonItem::updateValue(QString _value, int _pos) {

    if (values_.size() > _pos) {
        if (_value == "") values_.removeAt(_pos);
        else values_[_pos] = _value;
    }
    else appendValue(_value);
}
