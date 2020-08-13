#pragma once

// Includes: Qt
#include <QFrame>
#include <QToolButton>
#include <QVBoxLayout>

// Includes: Project
#include "S1-GuiTools_Export.h"


class S1_GUITOOLS_EXPORT FrameInterfacePrivate;


class S1_GUITOOLS_EXPORT FrameInterface : public QFrame {

public: // ---------------------------------------------------------- PUBLIC

    enum Location {
        HEADER = 0,
        BODY = 1,
        FOOTER,
    };

    FrameInterface();
    virtual ~FrameInterface() {}

    QVBoxLayout* get_Layout();

    int frameID_;
    bool locked_;	/* True if locked, default is false */

protected: // ------------------------------------------------------- PROTECTED

    FrameInterface(FrameInterfacePrivate& d);

    void insert_Widget(QWidget*, Location location = Location::BODY);

    FrameInterfacePrivate* z_ptr_;
};


/* Interface Macro */
Q_DECLARE_INTERFACE(FrameInterface, "com.squareone.FrameInterface")
