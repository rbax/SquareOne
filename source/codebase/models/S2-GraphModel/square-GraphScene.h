#pragma once

class GraphTextItem;

#include <QGraphicsScene>
#include "S2-GraphModel_Export.h"

class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QAction;

class S2_GRAPHMODEL_EXPORT GraphScene : public QGraphicsScene {

    Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    enum Mode { MOVE = 0, EDIT = 1, INSERT_VERTEX, INSERT_EDGE, INSERT_TEXT };

    explicit GraphScene(QMenu *itemMenu, QObject *parent = 0);

    void setLineColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setItemColor(const QColor &color);
    void setFont(const QFont &font);

    public slots: /* ---------------------------------------------------- [PUBLIC SLOTS] */

    void slot_LostFocusTextEditor(GraphTextItem *item);
    void slot_SetMode(Mode mode) { mode_ = mode; }

signals: /* --------------------------------------------------------- [SIGNALS] */

    void signal_ItemInserted();
    void signal_FocusTextEditer(QGraphicsItem *item);
    void signal_FocusItem(QGraphicsItem *item);

protected: /* ------------------------------------------------------- [PROTECTED] */

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    
private: /* --------------------------------------------------------- [PRIVATE] */

    bool isSelectedItemofType(int type);

    QMenu *itemMenu_; // passed to the item for right click menu
    Mode mode_ = MOVE;
    QGraphicsLineItem *line_ = 0;

	QPointF mousePressPoint_;
};