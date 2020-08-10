#pragma once

/* |INCLUDES: QT| */
#include <QPixmap>
#include <QMetaType>

/* |INCLUDES: PROJECT| */
#include "S2-DragModel_Export.h"


struct S2_DRAGMODEL_EXPORT DragItem {

    DragItem() {}

    int id;
    int typeID;
    QPixmap pixmap;
    QRect rect;
    QSize size;
};

Q_DECLARE_METATYPE(DragItem)
