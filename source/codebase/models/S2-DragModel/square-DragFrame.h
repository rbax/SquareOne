#pragma once

/* |INCLUDES: QT| */

/* |INCLUDES: SQUARE| */
#include "S2-DragModel_Export.h"
#include "square-FrameInterface.h"


class DragFramePrivate;
struct DragItem;

class S2_DRAGMODEL_EXPORT DragFrame : public FrameInterface {

    Q_INTERFACES(FrameInterface)

        Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    DragFrame();

    /* ------------------------------------- (SET) */

    void set_ItemSize(QSize size);

    void set_MimeString(QString mime);

    /* ------------------------------------- (CREATE) */

    /* each call adds a frame to the menu with a collection of items */
    void create_ItemFrame(QToolButton *button, const QStringList &imagePathList);

    void create_ItemFrame(QToolButton *button, const QList<DragItem*> &dragItemList);

    DragItem* create_DragItem(const QString &imagePath);


private: /* --------------------------------------------------------- [PRIVATE] */

    DragFramePrivate *z_ptr_;
};
