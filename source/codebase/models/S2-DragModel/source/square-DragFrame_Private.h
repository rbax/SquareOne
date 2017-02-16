#pragma once

/* |INCLUDES: QT| */
#include <QSize>
class QSplitter;
class QToolButton;

/* |INCLUDES: SQUARE| */
#include "square-Menu.h"

/* |INCLUDES: PROJECT| */
#include "S2-DragModel_Export.h"
class DragFrame;
class DragWidget;
struct DragItem;


class S2_DRAGMODEL_EXPORT DragFramePrivate {

public: /* ---------------------------------------------------------- [PUBLIC] */

    DragFramePrivate(DragFrame *q);

    void insert_Items(QToolButton *button, const QStringList &imagePathList);

    void insert_Items(QToolButton *button, const QList<DragItem*> &dragItemList);

    QSize itemSize_;

    QString mimeString_;

    Menu itemMenu_;
    Menu slideMenu_;

    QSplitter *splitter_;

private: /* --------------------------------------------------------- [PRIVATE] */

    DragFrame *q_ptr_;

    DragWidget *dragCanvas_;
    QList<DragItem*> dragItemList_;

};
