#pragma once

/* |INCLUDES: QT| */
#include <QtCore>
#include <QtDebug>

class QLabel;
class QToolButton;
class QFrame;
class QListWidgetItem;
class QTableWidget;
class QSize;

/* |INCLUDES: SQUARE| */
#include "S1-DevTools_Export.h"
#include "square-Macros.h"

SQUARE_START

class S1_DEVTOOLS_EXPORT Objects {

public:

    enum StandardSize {

        ICON_TOOLBUTTON = 0,
        ICON_TABLECELL = 1,
        TOOLBAR_SPACER,
        LINEEDIT_SMALL,
        LINEEDIT_MEDIUM,
        LINEEDIT_LARGE
    };


    /* ---------------------------------------------------------- (STANDARDIZATION) */

    static
        QSize get_StandardSize(StandardSize);

    /* --------------------------------------------------------------- [BUTTONS] */

    static
        QToolButton* button(QString imageName,
                            QSize   buttonSize);

    static
        QToolButton* button(QString imagePath,
                            QString imageName,
                            QSize   buttonSize);

    static
        QToolButton* button(QString imagePath,
                            QString onImageName,
                            QString offImageName,
                            QSize   buttonSize);


    /* --------------------------------------------------------------- [LABELS] */

    static
        QLabel* label(QString imagePath,
                      QString imageName,
                      QSize   labelSize);

    /* --------------------------------------------------------------- [ITEMS] */

    static
        QListWidgetItem* listWidgetItem(const QPixmap &pixmap);

    /* --------------------------------------------------------------- [FRAME/LAYOUT] */

    static
        QWidget* containerH();

    static
        QWidget* containerV();

    /* --------------------------------------------------------------- [TABLES] */
        
    static
        QTableWidget* tableWidget(QStringList columnNameList);

    static
        void insert_TableRow(QTableWidget &table, 
                             int rowNum, 
                             QStringList &rowItems);


    static  /* Resize a table based on how many columns and rows you want to display */
        void resize_Table(QTableWidget &table, 
                          int rows, 
                          int columns);


    /* --------------------------------------------------------------- [TREES] */

    static
        void insert_Row();

    /* --------------------------------------------------------------- [SPACERS] */

    static
        QWidget* spacer(QSize stretch = QSize(0, 0));
};

SQUARE_END