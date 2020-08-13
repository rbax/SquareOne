#pragma once

// Includes: Qt
#include <QGradient>
#include <QPolygon>

// Includes: Project
#include "S2-GraphModel_Export.h"
struct GraphItem;
struct GraphData;


class S2_GRAPHMODEL_EXPORT NodeInterface {

public: // ---------------------------------------------------------- PUBLIC

    enum IType { VERTEX = 1, EDGE = 2, TEXT };

    NodeInterface(IType type);

    virtual ~NodeInterface() {}

    virtual int itemID() const { return itemID_; }
    virtual IType itype() const { return type_; }

    virtual GraphItem* item() const { return item_; }
    virtual GraphData* data() const { return data_; }

    virtual QString name() const { return name_; }
    virtual void setName(QString& name) { name_ = name; }

signals: // --------------------------------------------------------- SIGNALS

    void signal_Selected(int itemID);

protected: // ------------------------------------------------------- PROTECTED

    const QSize minSize() const { return QSize(80, 50); }
    const int handleSize() const { return 6; }

    static QGradient gradient(QColor& _color, QRectF& _rect);
    static QPolygon triangle(QRectF& _rect);

private: // --------------------------------------------------------- PRIVATE

    int itemID_ = -1;
    QString name_ = "";
    IType type_;

    GraphItem* item_ = 0;
    GraphData* data_ = 0;
};

/* Interface Macro */
Q_DECLARE_INTERFACE(NodeInterface, "com.squareone.NodeFace")
