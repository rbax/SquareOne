#include "square-GraphNode.h"
#include "square-GraphEdge.h"
#include "square-GraphItem.h"


/* ------------------------------------------------------------------ [PUBLIC] */

NodeInterface::NodeInterface(IType _type) : type_(_type), item_(new GraphItem()), data_(new GraphData()) {}

/* ------------------------------------------------------------------ [PROTECTED] */

QGradient NodeInterface::gradient(QColor &_color, QRectF &_rect) {

    QColor color = _color; {

           color.setAlpha(160);
    }

    QLinearGradient result(_rect.topLeft(), _rect.bottomRight()); {

                    result.setColorAt(0, color.dark(150));
                    result.setColorAt(0.5, color.light(200));
                    result.setColorAt(1, color.dark(150));
    }

    return result;
}

QPolygon NodeInterface::triangle(QRectF &_rect) {

    QPolygon result(3); {

             result.setPoint(0, _rect.center().x(), _rect.top());
             result.setPoint(1, _rect.right(), _rect.bottom());
             result.setPoint(2, _rect.left(), _rect.bottom());
    }

    return result;
}

/* ------------------------------------------------------------------ [PRIVATE] */
