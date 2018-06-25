#include "square-GraphVertex.h"
#include "square-GraphEdge.h"
#include "square-GraphItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPalette>
#include <QGraphicsScene>
#include <QMenu>

/* ------------------------------------------------------------------ [PUBLIC] */

GraphVertex::GraphVertex(QMenu *_menu, QGraphicsItem *parent) 
    : contextMenu_(_menu), QGraphicsItem(parent), NodeInterface(NodeInterface::VERTEX) {

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void GraphVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    QPen pen(item()->textColor);
    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(gradient(item()->fillColor, item()->rect));

    QRectF rect(item()->rect);
    rect.adjust(1, 1, -handleSize() / 2, -handleSize() / 2);

    painter->drawRect(rect);

    // paint the shape
    switch (shape_) {

        case Rectangle:
            painter->drawRect(rect);
            break;
        case Circle:
            painter->setRenderHint(QPainter::Antialiasing);
            painter->drawEllipse(rect);
            painter->setRenderHint(QPainter::Antialiasing, false);
            break;
        case Triangle:
            painter->setRenderHint(QPainter::Antialiasing);
            painter->drawPolygon(triangle(rect));
            painter->setRenderHint(QPainter::Antialiasing, false);
            break;
    }

    // paint the resize handle
    painter->setPen(item()->handleColor);
    painter->setBrush(Qt::white);
    painter->drawRect(resizeHandle().adjusted(0, 0, -1, -1));

    // paint the shape name
    painter->setBrush(item()->textColor);

    if (shape_ == Triangle) {

        rect.adjust(0, rect.height() / 2, 0, 0);
    }

    painter->drawText(rect, Qt::AlignCenter, name());
}

QRectF GraphVertex::resizeHandle() const {

    QPointF br(item()->rect.bottomRight());

    return QRectF(br - QPointF(handleSize(), handleSize()), br);
}

QPolygonF GraphVertex::polygon() const {

    return QGraphicsItem::mapFromItem(this, item()->rect);
}

void GraphVertex::removeEdge(GraphEdge *_edge) {

    int index(edgeList_.indexOf(_edge));

    if (index != -1) {

        edgeList_.removeAt(index);
    }
}

void GraphVertex::removeEdges() {

    foreach(GraphEdge *edge, edgeList_) {

        edge->startItem_->removeEdge(edge);
        edge->endItem_->removeEdge(edge);
        scene()->removeItem(edge);
        delete edge;
    }
}

void GraphVertex::addEdge(GraphEdge *_edge) {

    edgeList_.append(_edge);
}

/* ------------------------------------------------------------------ [PROTECTED] */

void GraphVertex::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    mouseDown_ = resizeHandle().contains(event->pos());

    if (mouseDown_) {

        event->accept();
        mousePressOffset_ = (item()->rect.bottomRight() - event->pos());
    }

    else QGraphicsItem::mousePressEvent(event);
}

void GraphVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    if (mouseDown_) {

        event->accept();
        mouseDown_ = false;
    }

    else QGraphicsItem::mouseReleaseEvent(event);
}

void GraphVertex::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    if (mouseDown_) {

        event->accept();
        QRectF eventRect(QRectF(item()->rect.topLeft(), event->pos() + mousePressOffset_)); {

            eventRect.setSize(eventRect.size().expandedTo(minSize()));
        }

        if (item()->rect != eventRect) {

            prepareGeometryChange();
            item()->rect = eventRect;
        }
    }

    else QGraphicsItem::mouseMoveEvent(event);
}


void GraphVertex::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {

    scene()->clearSelection();
    setSelected(true);
    contextMenu_->exec(event->screenPos());
}

QVariant GraphVertex::itemChange(GraphicsItemChange _change, const QVariant &_value) {

    if (_change == QGraphicsItem::ItemPositionChange) {

        foreach(GraphEdge *edge, edgeList_) {

            edge->updatePosition();
        }
    }

    return _value;
}

/* ------------------------------------------------------------------ [PRIVATE] */

QRectF GraphVertex::boundingRect() const {

    return item()->rect;
}