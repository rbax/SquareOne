#pragma once

/* |INCLUDES: QT| */

/* |INCLUDES: SQUARE| */
#include "S1-GuiTools_Export.h"


class S1_GUITOOLS_EXPORT FrameInterface;


class S1_GUITOOLS_EXPORT FrameInterfacePrivate {

public: // ---------------------------------------------------------- PUBLIC

    FrameInterfacePrivate(FrameInterface* q);

    virtual ~FrameInterfacePrivate() {}

    QWidget* headContainer_;
    QWidget* bodyContainer_;
    QWidget* footContainer_;

    QVBoxLayout* mainLayout_;
    QHBoxLayout* headLayout_;
    QVBoxLayout* bodyLayout_;
    QHBoxLayout* footLayout_;

    QToolButton* toolButton_;

private: // --------------------------------------------------------- PRIVATE

    FrameInterface* q_ptr_;
};
