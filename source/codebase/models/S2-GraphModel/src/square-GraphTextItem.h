#pragma once

#include <QGraphicsTextItem>

class QFocusEvent;
class QGraphicsItem;
class QGraphicsSceneMouseEvent;

#include "S2-GraphModel_Export.h"
#include "square-GraphNode.h"


class S2_GRAPHMODEL_EXPORT GraphTextItem : public QGraphicsTextItem, public NodeInterface {

    Q_INTERFACES(NodeInterface)
        Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    enum { Type = UserType + IType::TEXT };

    GraphTextItem(QGraphicsItem* parent = 0);

    int type() const Q_DECL_OVERRIDE { return Type; }

signals: /* --------------------------------------------------------- [SIGNALS] */

    void signal_LostFocus(GraphTextItem* item);
    void signal_SelectionChange(QGraphicsItem* item);

protected: /* ------------------------------------------------------- [PROTECTED] */

    QVariant itemChange(GraphicsItemChange change, const QVariant& value) Q_DECL_OVERRIDE;
    void focusOutEvent(QFocusEvent* event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
};
