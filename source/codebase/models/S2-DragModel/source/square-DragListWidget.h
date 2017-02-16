#pragma once

/* |INCLUDES: QT| */
#include <QListWidget>

/* |INCLUDES: PROJECT| */
#include "S2-DragModel_Export.h"


class S2_DRAGMODEL_EXPORT DragListWidget : public QListWidget {

    Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    explicit DragListWidget(QSize size, QWidget *parent = 0);


protected: /* ------------------------------------------------------- [PROTECTED] */

    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;


private: /* --------------------------------------------------------- [PRIVATE] */

    QSize size_;

    QString mimeString_;
};
