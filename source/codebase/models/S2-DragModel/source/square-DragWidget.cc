// Includes: Qt
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QDebug>
#include <QAction>

// Includes: Square
#include "square.h"

// Includes: Project
#include "square-DragWidget.h"
#include "square-DragItem.h"


// ------------------------------------------------------------------ PUBLIC

DragWidget::DragWidget(QSize _imageSize, QWidget* _parent)
    :
    QWidget(_parent),
    imageSize_(_imageSize.width() * 10),
    mimeString_("square/x-d2node-data"),
    itemCount_(0),
    selectedItem_(0) {

    setAcceptDrops(true);
}

void DragWidget::clear() {

    highlightRectangle_ = QRect();
    update();
    // @todo clean up dragitems, hashtable, etc
}


// ------------------------------------------------------------------ PROTECTED

void DragWidget::mousePressEvent(QMouseEvent* event) {

    QRect square(targetSquare(event->pos()));

    DragItem* item;

    if (event->button() == Qt::RightButton) {
        item = get_DragItem(square);
        if (!item) return;

        emit signal_ItemSelected(square);
    }

    else {
        item = take_DragItem(square);
        if (!item) return;

        update(square);

        QPixmap pixmap(item->pixmap);
        QByteArray itemData;

        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << pixmap << item->typeID;

        QMimeData* mimeData(new QMimeData);
        mimeData->setData(mimeString_, itemData);

        QDrag* drag(new QDrag(this));
        drag->setMimeData(mimeData);
        drag->setHotSpot(event->pos() - square.topLeft());
        drag->setPixmap(pixmap);
        if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
            dragItemHash_.insert(square, item);
            update(targetSquare(event->pos()));
        }
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent* event) {

    QRect updateRect(highlightRectangle_.united(targetSquare(event->pos())));

    if (event->mimeData()->hasFormat(mimeString_)
        && findItem(targetSquare(event->pos())) == -1) {

        highlightRectangle_ = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }

    else {
        highlightRectangle_ = QRect();
        event->ignore();
    }

    update(updateRect);
}

void DragWidget::dragLeaveEvent(QDragLeaveEvent* event) {

    QRect updateRect(highlightRectangle_);
    highlightRectangle_ = QRect();

    update(updateRect);
    event->accept();
}

void DragWidget::dragEnterEvent(QDragEnterEvent* event) {

    if (event->mimeData()->hasFormat(mimeString_)) event->accept();
    else event->ignore();
}

void DragWidget::dropEvent(QDropEvent* event) {

    if (event->mimeData()->hasFormat(mimeString_)
        && findItem(targetSquare(event->pos())) == -1) {

        QByteArray data(event->mimeData()->data(mimeString_)); {}
        QPixmap pixmap;
        int itemID;

        QDataStream dataStream(&data, QIODevice::ReadOnly);
        dataStream >> pixmap >> itemID;

        highlightRectangle_ = QRect();

        QRect square(targetSquare(event->pos()));
        update(square);
        event->setDropAction(Qt::MoveAction);
        event->accept();

        if (selectedItem_) {
            selectedItem_->rect = square;
            dragItemHash_.insert(square, selectedItem_);
            selectedItem_ = 0;
        }
        else {
            DragItem* item(new DragItem());
            item->id = itemCount_;
            item->pixmap = pixmap;
            item->rect = square;
            item->typeID = itemID;

            dragItemHash_.insert(square, item);
            itemCount_++;
        }
    }
    else {
        highlightRectangle_ = QRect();
        event->ignore();
    }
}

void DragWidget::paintEvent(QPaintEvent* event) {

    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightRectangle_.isValid()) {
        painter.setBrush(QColor("#42c0fb")); /* blue */
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightRectangle_.adjusted(0, 0, -1, -1));
    }

    QHashIterator<QRect, DragItem*> i(dragItemHash_);

    while (i.hasNext()) {
        i.next();
        painter.drawPixmap(i.value()->rect, i.value()->pixmap);
    }

    painter.end();
}


// ------------------------------------------------------------------ PRIVATE

int DragWidget::itemSize() const { //@TODO this is dumb

    return imageSize_ / 5;
}

int DragWidget::findItem(const QRect& _itemRect) const {

    return dragItemHash_.contains(_itemRect)
        ? 0
        : -1;
}

DragItem* DragWidget::take_DragItem(const QRect& _itemRect) {

    return selectedItem_ = dragItemHash_.contains(_itemRect)
        ? dragItemHash_.take(_itemRect)
        : 0;
}

DragItem* DragWidget::get_DragItem(const QRect& _itemRect) {

    return dragItemHash_.contains(_itemRect)
        ? dragItemHash_.value(_itemRect)
        : 0;
}

const QRect DragWidget::targetSquare(const QPoint& _position) const {

    return QRect(_position.x() / itemSize() * itemSize(),
                 _position.y() / itemSize() * itemSize(),
                 itemSize(),
                 itemSize());
}
