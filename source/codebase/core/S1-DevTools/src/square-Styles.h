#pragma once

// Includes: Qt
class QLayout;
class QFrame;
class QPalette;

// Includes: Square
#include "square-Macros.h"
class FrameInterface;

// Includes: Project
#include "S1-DevTools_Export.h"


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

    // ---------------------------------------------------------- FRAME STYLES

    static
        void set_FrameStyle(QFrame& frame,
                            FrameStyle style = DEEP);

    // ---------------------------------------------------------- LAYOUT STYLES

    static
        void set_LayoutStyle(QLayout& layout,
                             LayoutStyle style = THIN);

    static
        void set_PaletteStyle(QPalette& palette,
                              PaletteStyle style = STANDARD);
};


SQUARE_END
