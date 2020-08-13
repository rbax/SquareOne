#pragma once

// Includes: Qt
#include <QGraphicsLineItem>
class QRectF;
class QPainterPath;
class GraphVertex;

// Includes: Project
#include "square-GraphNode.h"
#include "S2-GraphModel_Export.h"

class S2_GRAPHMODEL_EXPORT GraphEdge : public QGraphicsLineItem, public NodeInterface {

    Q_INTERFACES(NodeInterface)

public: // ---------------------------------------------------------- PUBLIC

    enum { Type = UserType + IType::EDGE };

    GraphEdge(GraphVertex* startItem, GraphVertex* endItem, QGraphicsItem* parent = 0);

    int type() const Q_DECL_OVERRIDE { return Type; }

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void updatePosition();

    GraphVertex* startItem_;
    GraphVertex* endItem_;

protected: // ------------------------------------------------------- PROTECTED

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) Q_DECL_OVERRIDE;

public: // ---------------------------------------------------------- PUBLIC

    QPolygonF endEdge_; // arrow, caps, etc
    QPolygonF startEdge_;
};
