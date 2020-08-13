// Includes: Qt
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

// Includes: Project
#include "square-DraglistWidget.h"
#include "square-DragItem.h"


// ------------------------------------------------------------------ PUBLIC

DragListWidget::DragListWidget(QSize _size, QWidget* _parent)
    :
    QListWidget(_parent),
    size_(_size),
    mimeString_("square/x-d2node-data") {

    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setDropIndicatorShown(true);
    setMinimumHeight(_size.height() + 10);
    setMaximumHeight(_size.height() + 10);
    setIconSize(_size);
    setWrapping(false);
}


// ------------------------------------------------------------------ PROTECTED

void DragListWidget::startDrag(Qt::DropActions) {

    QListWidgetItem* item = currentItem();
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    int itemID = item->data(Qt::UserRole + 1).toInt();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << itemID;

    QMimeData* mimeData = new QMimeData;
    mimeData->setData(mimeString_, itemData);

    QDrag* drag = new QDrag(this);
    drag->setPixmap(pixmap);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width() / 2,
                            pixmap.height() / 2));

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {/* ? */ };
}
