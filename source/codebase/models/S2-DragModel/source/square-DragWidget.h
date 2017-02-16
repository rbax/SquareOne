#pragma once

/* |INCLUDES: QT| */
#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;

struct DragItem;

#include "S2-DragModel_Export.h"


class S2_DRAGMODEL_EXPORT DragWidget : public QWidget {

    Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    explicit DragWidget(QSize imageSize, QWidget *parent = 0);

    void clear();

    DragItem* get_DragItem(const QRect &itemRect);


signals: /* --------------------------------------------------------- [SIGNALS] */

    void signal_ItemSelected(QRect selectedRectangle);

protected: /* ------------------------------------------------------- [PROTECTED] */

    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private: /* --------------------------------------------------------- [PRIVATE] */


    int itemSize() const;

    int findItem(const QRect &itemRectangle) const;

    DragItem* take_DragItem(const QRect &itemRectangle);

    const QRect targetSquare(const QPoint &position) const;

    /* --------------------------------------------------------------- [PRIVATE] */

    QHash<QRect, DragItem*> dragItemHash_;

    QRect highlightRectangle_;

    int imageSize_;

    QString mimeString_;

    int itemCount_;

    DragItem* selectedItem_;
};


/* ------------------------------------------------------------------ [INLINE] */

inline uint qHash(const QRect & _r) {

    return qHash(_r.left()) ^ qHash(_r.top()) ^
        qHash(_r.right()) ^ qHash(_r.bottom());
}
