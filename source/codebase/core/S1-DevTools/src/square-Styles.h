#pragma once

/* |INCLUDES: QT| */
class QLayout;
class QFrame;
class QPalette;

/*  |INCLUDES: PROJECT| */
#include "S1-DevTools_Export.h"
#include "square-Macros.h"
class FrameInterface;

SQUARE_START

class S1_DEVTOOLS_EXPORT Styles {

public:

    enum FrameStyle {
        DEEP = 0,
    };

    enum LayoutStyle {
        THIN = 0,
    };

    enum PaletteStyle {
        STANDARD = 0,
    };

    /* ---------------------------------------------------------- (FRAME STYLES) */

    static
        void set_FrameStyle(QFrame& frame,
                            FrameStyle style = DEEP);


    /* ---------------------------------------------------------- (LAYOUT STYLES) */

    static
        void set_LayoutStyle(QLayout& layout,
                             LayoutStyle style = THIN);

    static
        void set_PaletteStyle(QPalette& palette,
                              PaletteStyle style = STANDARD);
};

SQUARE_END
