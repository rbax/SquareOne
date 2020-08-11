#pragma once

/* |INCLUDES: SQUARE| */
#include "S1-GuiTools_Export.h"
#include "square-FrameInterface.h"


class S1_GUITOOLS_EXPORT Frame : public FrameInterface {

    Q_INTERFACES(FrameInterface)
        Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

    Frame(): FrameInterface() {}

    void insert__Widget(QWidget* _widget, Location _location = Location::BODY) {
        insert_Widget(_widget, _location);
    }

private: /* --------------------------------------------------------- [PRIVATE] */

};
