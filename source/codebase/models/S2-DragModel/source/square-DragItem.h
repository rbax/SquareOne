#pragma once

// Includes: Qt
#include <QPixmap>
#include <QMetaType>

// Includes: Project
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
