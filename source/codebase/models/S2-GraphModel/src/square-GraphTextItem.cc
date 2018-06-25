
#include "square-GraphTextItem.h"


GraphTextItem::GraphTextItem(QGraphicsItem *_parent) : QGraphicsTextItem(_parent), NodeInterface(NodeInterface::TEXT) {
    
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QVariant GraphTextItem::itemChange(GraphicsItemChange _change, const QVariant &_value) {

    if (_change == QGraphicsItem::ItemSelectedHasChanged) {

        emit signal_SelectionChange(this);
    }

    return _value;
}

void GraphTextItem::focusOutEvent(QFocusEvent *event) {

    setTextInteractionFlags(Qt::NoTextInteraction);
    emit signal_LostFocus(this);

    QGraphicsTextItem::focusOutEvent(event);
}

void GraphTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    if (textInteractionFlags() == Qt::NoTextInteraction) {

        setTextInteractionFlags(Qt::TextEditorInteraction);
    }

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
