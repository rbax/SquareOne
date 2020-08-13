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

public: // ---------------------------------------------------------- PUBLIC

    Menu(bool menu_hides = true);

    QStackedWidget* get_StackedWidget();
    QToolBar* get_ToolBar();

    void hide();
    int	register_Frame(FrameInterface* frame, QToolButton* button);
    void set_Frame(int frameID);

private: // --------------------------------------------------------- PRIVATE

    MenuPrivate* z_ptr_;

};
