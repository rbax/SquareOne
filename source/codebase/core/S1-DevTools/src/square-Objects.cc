
/* |INCLUDES: QT| */
#include <QLayout>
#include <QToolButton>
#include <QFrame>
#include <QLabel>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QHeaderView>
#include <QPixmap>
#include <QPoint>
#include <QSize>

/* |INCLUDES: SQUARE| */
#include "square.h"

SQUARE_START

/* --------------------------------------------------------------- (STANDARDIZATION FUNCIONS) */

QSize Objects::get_StandardSize(StandardSize _type) {

    switch (_type) {
        case ICON_TOOLBUTTON: return QSize(30, 30);
        case ICON_TABLECELL: return QSize(15, 15);
        case TOOLBAR_SPACER: return QSize(25, 25);
        case LINEEDIT_SMALL: return QSize(30, 30);
        case LINEEDIT_MEDIUM: return QSize(50, 30);
        case LINEEDIT_LARGE: return QSize(75, 30);

        default: return QSize(0, 0);
    }
}

/* ------------------------------------------------------------------ [BUTTONS] */

QToolButton* Objects::button(QString _name, QSize _size) {

    QToolButton* toolButton(new QToolButton());
    toolButton->setText(_name);
    toolButton->setMinimumSize(_size);
    toolButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    return toolButton;
}


QToolButton* Objects::button(QString _imagePath, QString _imageName, QSize _size) {

    QToolButton* toolButton(new QToolButton());
    toolButton->setIcon(QPixmap(_imagePath + _imageName));
    toolButton->setIconSize(_size);

    return toolButton;
}


QToolButton* Objects::button(QString _imagePath, QString _imageOn, QString _imageOff, QSize _size) {

    QIcon icon;
    icon.addPixmap((_imagePath + _imageOn), QIcon::Normal, QIcon::On);
    icon.addPixmap((_imagePath + _imageOff), QIcon::Normal, QIcon::Off);

    QToolButton* toggleButton(new QToolButton());
    toggleButton->setIcon(icon);
    toggleButton->setIconSize(_size);
    toggleButton->setCheckable(true);

    return toggleButton;
}

/* ------------------------------------------------------------------ [LABELS] */

QLabel* Objects::label(QString _imagePath, QString _imageName, QSize _size) {

    QPixmap pixmap(_imagePath + _imageName);

    QLabel* label(new QLabel());
    label->setPixmap(pixmap.scaled(_size));
    label->setAttribute(Qt::WA_DeleteOnClose);

    return label;
}

/* ------------------------------------------------------------------ [ITEMS] */

QListWidgetItem* Objects::listWidgetItem(const QPixmap& _pixmap) {

    QListWidgetItem* item(new QListWidgetItem());
    item->setIcon(QIcon(_pixmap));
    item->setData(Qt::UserRole, QVariant(_pixmap));
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

    return item;
}

/* ------------------------------------------------------------------ [FRAME/LAYOUT] */

QWidget* Objects::containerH() {

    QWidget* container(new QWidget());

    QHBoxLayout* layout(new QHBoxLayout(container));
    SQUARE_STYLES::set_LayoutStyle(*layout);

    return container;
}


QWidget* Objects::containerV() {

    QWidget* container(new QWidget());

    QVBoxLayout* layout(new QVBoxLayout(container));
    SQUARE_STYLES::set_LayoutStyle(*layout);

    return container;
}

/* --------------------------------------------------------------- [TABLES] */

QTableWidget* Objects::tableWidget(QStringList _columnNameList) {

    QTableWidget* tableWidget(new QTableWidget());
    tableWidget->setColumnCount(_columnNameList.size());
    tableWidget->setFrameShape(QFrame::NoFrame);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setMouseTracking(true);

    tableWidget->setHorizontalHeaderLabels(_columnNameList);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->hide();

    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    return tableWidget;
}


void Objects::insert_TableRow(QTableWidget& _table, int _row, QStringList& _items) {

    _table.insertRow(_row);

    FOR_I(_items.size()) {
        _table.setItem(_row, i, new QTableWidgetItem(_items.at(i)));
    }
}


void Objects::resize_Table(QTableWidget& _table, int _rows, int _columns) {

    if (_rows > _table.rowCount() || _columns > _table.columnCount()) return;

    int width(0);
    int height(0);

    FOR_I(_rows) height = height + _table.rowHeight(i);
    FOR_I(_columns) width = width + _table.columnWidth(i);

    _table.setFixedSize(width, height);
}

/* --------------------------------------------------------------- [SPACERS] */

QWidget* Objects::spacer(QSize _stretch) {

    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Expanding);
    policy.setVerticalStretch(_stretch.height());
    policy.setHorizontalStretch(_stretch.width());

    QWidget* spacer(new QWidget());
    spacer->setSizePolicy(policy);

    return spacer;
}

SQUARE_END
