
/* |INCLUDES: QT| */
#include <QFrame>
#include <QLayout>

/* |INCLUDES: SQUARE| */
#include "square.h"

/* --------------------------------------------------------------- [CSV FUNCIONS] */
SQUARE_START

void Styles::set_FrameStyle(QFrame& _frame, FrameStyle _style) {

    switch (_style) {

        /* --------------------------------------------- (DEEP) */
        case DEEP:
            _frame.setFrameStyle(QFrame::Panel | QFrame::Sunken);
            _frame.setLineWidth(3);
            _frame.setMidLineWidth(3);
            break;
    }
}


void Styles::set_LayoutStyle(QLayout& _layout, LayoutStyle _style) {

    _layout.setContentsMargins(0, 0, 0, 0);
}

void Styles::set_PaletteStyle(QPalette& _palette, PaletteStyle _style) {

    QColor window, button, highlight, buttonText, windowText;

    // background, foreground, base, alternateBase, toolTipBase, ToolTipText, Text, BrightText


    switch (_style) {

        /* --------------------------------------------- (STANDARD) */

        case STANDARD:
            button = QColor(105, 105, 105);
            window = QColor(53, 53, 53);
            highlight = QColor(66, 192, 251); // Caribbean Blue
            buttonText = QColor(Qt::white);
            windowText = QColor(Qt::black);
    }

    _palette.setColor(QPalette::Window, window);
    _palette.setColor(QPalette::Button, button);
    _palette.setColor(QPalette::Highlight, highlight);
    _palette.setColor(QPalette::ButtonText, buttonText);
    _palette.setColor(QPalette::WindowText, windowText);
}

SQUARE_END


/*

http://www.rapidtables.com/web/color/RGB_Color.htm


White               FFFFFF   QColor(255, 255, 255);

Gray, Light:        DBDBDB   QColor(219, 219, 219);
                    696969   QColor(105, 105, 105);
Gray, Dark:         353535   QColor(53, 53, 53);

Blue, Caribbean:    42C0FB  QColor(66, 192, 251);

Green, Glow:        45FF4B  QColor(69, 255, 75);

Red:                FF2B2B  QColor(255, 43, 43);

Purple              8E2DC5  QColor(142, 45, 197);


*/
