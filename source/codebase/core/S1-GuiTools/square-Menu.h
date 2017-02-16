#pragma once

/* |INCLUDES: QT| */
class QToolButton;
class QToolBar;
class QStackedWidget;

/* |INCLUDES: SQUARE| */
#include "S1-GuiTools_Export.h"
#include "square-FrameInterface.h"
class Frame;

class S1_GUITOOLS_EXPORT MenuPrivate;

class S1_GUITOOLS_EXPORT Menu {

public: /* ---------------------------------------------------------- [PUBLIC] */

    Menu(bool menu_hides = true);

    int	register_Frame(FrameInterface *frame, QToolButton *button);

    /* ------------------------------------- (SET) */

    void set_Frame(int frameID);

    void hide();

    /* ------------------------------------- (GET) */

    QToolBar* get_ToolBar();

    QStackedWidget* get_StackedWidget();

private: /* --------------------------------------------------------- [PRIVATE] */

    MenuPrivate *z_ptr_;

};
