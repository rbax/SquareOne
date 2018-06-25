#pragma once

#include <QAbstractItemModel>
#include "square-JSONItem.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QIcon>

#include "S2-JsonModel_Export.h"

class S2_JSONMODEL_EXPORT JsonModel : public QAbstractItemModel {

    Q_OBJECT

        enum Column {

        Key = 0,
        Value = 1,
        ValueMin,
        ValueMax,
    };

public: /* ---------------------------------------------------------- [PUBLIC] */

    explicit JsonModel(const QStringList &columnNames, QObject *parent = 0);

    ~JsonModel();


    /* |ITEM DATA HANDLING|
    ----------------------------------------------------------------- */

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    void setIcon(const QJsonValue::Type& type, const QIcon& icon) { iconList_.insert(type, icon); }

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;


    /* NAVIGATION AND INDEX CREATION
     ----------------------------------------------------------------- */

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;


    /* SETUP
    ----------------------------------------------------------------- */

    bool loadJson(const QByteArray& json);
    QString get_Json() { return document_.toJson(); }


private: /* --------------------------------------------------------- [PRIVATE] */

    bool load(const QString& fileName);
    bool load(QIODevice * device) { return loadJson(device->readAll()); }

    void update(QJsonObject &object, const QString &path, const QJsonValue &value);
    void update(QJsonDocument &document, const QString &path, const QJsonValue &value);

    JsonItem* get_Item(const QModelIndex &index) const;
    QString get_Path(JsonItem *item);

    QStringList headerList_;
    QHash<QJsonValue::Type, QIcon> iconList_;

    QJsonDocument document_;
    JsonItem *rootItem_;
};