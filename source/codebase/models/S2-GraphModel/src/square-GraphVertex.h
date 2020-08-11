#pragma once

#include <QGraphicsItem>
#include <QPainter>

#include "S2-GraphModel_Export.h"
#include "square-GraphNode.h"

class GraphEdge;

class S2_GRAPHMODEL_EXPORT GraphVertex : public QGraphicsItem, public NodeInterface {

    Q_INTERFACES(NodeInterface)

public: /* ---------------------------------------------------------- [PUBLIC] */

    enum ShapeType { Rectangle, Circle, Triangle };
    enum { Type = UserType + IType::VERTEX };

    GraphVertex(QMenu* contextMenu, QGraphicsItem* parent = 0);

    int type() const Q_DECL_OVERRIDE { return Type; }

    QPolygonF polygon() const;

    void removeEdges();
    void removeEdge(GraphEdge* edge);
    void addEdge(GraphEdge* edge);


signals: /* --------------------------------------------------------- [SIGNALS] */

    void signal_LostFocus(QGraphicsItem* item);

protected: /* ------------------------------------------------------- [PROTECTED] */

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) Q_DECL_OVERRIDE;

private: /* --------------------------------------------------------- [PRIVATE] */

    QRectF resizeHandle() const;

    QMenu* contextMenu_;
    QList<GraphEdge*> edgeList_;

    bool mouseDown_ = false;
    QPointF mousePressOffset_;

    ShapeType shape_ = Rectangle;
};
