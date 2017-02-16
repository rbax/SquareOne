
/* |INCLUDES: |QT| */
#include "qvboxlayout"
#include <qtoolbutton.h>
//#include <QtPlugin>
#include "qframe.h"
#include "qobject.h"
#include "qsignalmapper.h"
#include "qstackedwidget.h"
#include "qtoolbar.h"
#include "qlayout.h"

/* |INCLUDES: |PROJECT| */
#include "square-FrameInterface.h"
#include "square-FrameInterface_Private.h"
#include "square.h"

/* ------------------------------------------------------------------ [PUBLIC] */

FrameInterface::FrameInterface(FrameInterfacePrivate &_d) : z_ptr_(&_d) {

}


FrameInterface::FrameInterface() : QFrame(), z_ptr_(new FrameInterfacePrivate(this)),
frameID_(0),
locked_(false) {

    z_ptr_->mainLayout_ = new QVBoxLayout(this);
    z_ptr_->mainLayout_->setContentsMargins(0, 0, 0, 0);

    setFrameShape(QFrame::NoFrame);
}


QVBoxLayout* FrameInterface::get_Layout() {

    return z_ptr_->mainLayout_;
}


void FrameInterface::insert_Widget(QWidget *_widget, Location _location) {

    switch (_location) {

        /* ------------------------------------------------ (HEADER) */
        case HEADER: { 

            if (!z_ptr_->headContainer_) {

                z_ptr_->headContainer_ = SQUARE_OBJ::containerH();
                z_ptr_->mainLayout_->addWidget(z_ptr_->headContainer_);
            }

            z_ptr_->headContainer_->layout()->addWidget(_widget);
            break;
        }

        /* ------------------------------------------------ (BODY) */
        case BODY: { 

            if (!z_ptr_->bodyContainer_) {

                z_ptr_->bodyContainer_ = SQUARE_OBJ::containerV();
                z_ptr_->mainLayout_->addWidget(z_ptr_->bodyContainer_);
            }

            z_ptr_->bodyContainer_->layout()->addWidget(_widget);
            break;
        }

        /* ------------------------------------------------ (FOOTER) */
        case FOOTER: { 

            if (!z_ptr_->footContainer_) {

                z_ptr_->footContainer_ = SQUARE_OBJ::containerH();
                z_ptr_->mainLayout_->addWidget(z_ptr_->footContainer_);
            }

            z_ptr_->footContainer_->layout()->addWidget(_widget);
            break;
        }
    }
}


FrameInterfacePrivate::FrameInterfacePrivate(FrameInterface *_q)
    :
    q_ptr_(_q),
    headContainer_(0),
    bodyContainer_(0),
    footContainer_(0),
    toolButton_(0) {

}