/* |INCLUDES: QT| */
#include "qlayout.h"
#include <QLineEdit>
#include <QTableWidget>

/* |INCLUDES: SQUARE| */
#include "square.h"
#include "square-FrameInterface.h"
#include "square-Menu.h"
#include "square-Frame.h"

/* |INCLUDES: PROJECT| */
#include "square-TableFrame.h"
#include "square-TableFrame_private.h"

/* ------------------------------------------------------------------ [TABLE FRAME] */

TableFrame::TableFrame(const QStringList& _columnNameList): FrameInterface(), z_ptr_(new TableFramePrivate(this)) {

    z_ptr_->columnNamesList_ = _columnNameList;

    insert_Widget(z_ptr_->searchLineEdit_, FrameInterface::HEADER);
    insert_Widget(z_ptr_->tableWidget_);

}


/* ------------------------------------------------------------------ [TABLE FRAME PRIVATE] */

TableFramePrivate::TableFramePrivate(TableFrame* q): q_ptr_(q) {

    searchLineEdit_ = new QLineEdit();
    searchLineEdit_->setPlaceholderText("Search:");

    QObject::connect(searchLineEdit_, &QLineEdit::textChanged, [=] (QString _text) {
        Q_UNUSED(_text);
        tableWidget_->clearContents();
    });

    tableWidget_ = SQUARE_OBJ::tableWidget(columnNamesList_);
    tableWidget_->setSelectionMode(QAbstractItemView::SingleSelection);

    QObject::connect(tableWidget_, &QTableWidget::cellPressed, [=] (int _row, int _column) {
        Q_UNUSED(_column);
        tableWidget_->selectRow(_row);
    });

    QObject::connect(tableWidget_, &QTableWidget::cellEntered, [=] (int _row, int _column) {
        Q_UNUSED(_column);
        tableWidget_->clearSelection();
        tableWidget_->selectRow(_row);
    });
}
