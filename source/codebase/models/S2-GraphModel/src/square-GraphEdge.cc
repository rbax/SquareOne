

#include "square-GraphItem.h"
#include "square-GraphVertex.h"
#include "square-GraphEdge.h"

#include <math.h>
#include <QPen>
#include <QPainter>

const qreal Pi(3.14);

GraphEdge::GraphEdge(GraphVertex *_startItem, GraphVertex *_endItem, QGraphicsItem *_parent) 
    : QGraphicsLineItem(_parent), startItem_(_startItem), endItem_(_endItem), NodeInterface(NodeInterface::EDGE) {

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(item()->fillColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF GraphEdge::boundingRect() const {

    qreal extra((pen().width() + 20) / 2.0); 

    return QRectF(line().p1(), 
                  QSizeF(line().p2().x() - line().p1().x(),
                  line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath GraphEdge::shape() const {

    QPainterPath path(QGraphicsLineItem::shape()); {

        path.addPolygon(endEdge_);
    }

    return path;
}

void GraphEdge::updatePosition() {

    setLine(QLineF(
        mapFromItem(startItem_, 0, 0),
        mapFromItem(endItem_, 0, 0)));
}

void GraphEdge::paint(QPainter *_painter, const QStyleOptionGraphicsItem *, QWidget *) {

    if (startItem_->collidesWithItem(endItem_)) {

        return;
    }

    QPen pen(pen()); {

        pen.setColor(item()->fillColor);
    }
  
    qreal arrowSize(20); 
      
    _painter->setPen(pen);
    _painter->setBrush(item()->fillColor);

    QLineF centerLine(startItem_->pos(), endItem_->pos());
    QPolygonF endPolygon(endItem_->polygon());

    QPointF p1(endPolygon.first() + endItem_->pos());
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;

    for (int i = 1; i < endPolygon.count(); ++i) {

        p2 = endPolygon.at(i) + endItem_->pos();
        polyLine = QLineF(p1, p2);

        QLineF::IntersectType intersectType(polyLine.intersect(centerLine, &intersectPoint));

        if (intersectType == QLineF::BoundedIntersection) {

            break;
        }

        p1 = p2;
    }

    setLine(QLineF(intersectPoint, startItem_->pos()));

    double angle(::acos(line().dx() / line().length()));
    
    if (line().dy() >= 0) {

        angle = (Pi * 2) - angle;
    }

    QPointF arrowP1(line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize));

    QPointF arrowP2(line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize));

    endEdge_.clear();
    endEdge_ 
        << line().p1() 
        << arrowP1 
        << arrowP2;

    _painter->drawLine(line());
    _painter->drawPolygon(endEdge_);

    if (isSelected()) {

        _painter->setPen(QPen(item()->fillColor, 1, Qt::DashLine));

        QLineF line(line()); {

            line.translate(0, 4.0);
            _painter->drawLine(line);

            line.translate(0, -8.0);
            _painter->drawLine(line);
        }
    }
}
