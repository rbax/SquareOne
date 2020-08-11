#pragma once

// Includes Qt
#include <QtCore>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

// Includes Local
#include "S2-JsonModel_Export.h"

class S2_JSONMODEL_EXPORT JsonItem {

public: /* ---------------------------------------------------------- [PUBLIC] */

    JsonItem(JsonItem* parent = 0): parent_(parent) {}
    ~JsonItem() { qDeleteAll(children_); }

    static JsonItem* load(const QJsonValue& value, JsonItem* parent = 0);

    QJsonValue jsonValue();

    QString toString();
    QString toString(int column);

    QString value(int value = 0);
    void appendValue(QString value) { values_.append(value); }
    void updateValue(QString value, int position);

    int row() const;
    int childCount() const { return children_.count(); }
    JsonItem* child(int row) { return children_.value(row); }

    QString key_;
    QJsonValue::Type type_;
    JsonItem* parent_;

private: /* --------------------------------------------------------- [PRIVATE] */

    void appendChild(JsonItem* item) { children_.append(item); }

    QStringList values_{};
    QList<JsonItem*> children_;
};
