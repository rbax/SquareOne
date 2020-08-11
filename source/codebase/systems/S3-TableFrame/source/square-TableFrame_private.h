#pragma once

/* |INCLUDES: QT| */
class QLineEdit;
class QTableWidget;

/* |INCLUDES: SQUARE| */

/* |INCLUDES: PROJECT| */
#include "S3-TableFrame_Export.h"

class TableFrame;

class S3_TABLEFRAME_EXPORT TableFramePrivate {

public: /* ---------------------------------------------------------- [PUBLIC] */

    TableFramePrivate(TableFrame* q);

    QLineEdit* searchLineEdit_;

    QTableWidget* tableWidget_;

    QStringList columnNamesList_;

private: /* --------------------------------------------------------- [PRIVATE] */

    TableFrame* q_ptr_;

};
