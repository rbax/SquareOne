
/* |INCLUDES: QT| */
#include <QToolButton>
#include <QToolBar>
#include <QStackedWidget>

/* |INCLUDES: SQUARE| */
#include "square-FrameInterface.h"

/* |INCLUDES: PROJECT| */
#include "square-Menu.h"
#include "square-Menu_private.h"
#include "square-Macros.h"


/* ------------------------------------------------------------------ [PUBLIC: MENU] */

Menu::Menu(bool _menu_hides) : z_ptr_(new MenuPrivate(this)) {

    z_ptr_->menuHides_ = _menu_hides;

    if (_menu_hides) {

        z_ptr_->stackedWidget_->hide();
    }
}


int Menu::register_Frame(FrameInterface *_frame, QToolButton *_button) {

    return z_ptr_->register_Frame(_frame, _button);
}


/* ------------------------------------- (SET) */

void Menu::set_Frame(int _frameID) {

    z_ptr_->set_DisplayFrame(_frameID);
}


void Menu::hide() {

    if (z_ptr_->menuHides_) z_ptr_->stackedWidget_->hide();
}


/* ------------------------------------- (GET) */

QToolBar* Menu::get_ToolBar() {

    return z_ptr_->toolbar_;
}


QStackedWidget* Menu::get_StackedWidget() {

    return z_ptr_->stackedWidget_;
}


/* ------------------------------------------------------------------ [PUBLIC: MENUPRIVATE] */

MenuPrivate::MenuPrivate(Menu *q) : q_ptr_(q) {

    stackedWidget_ = new QStackedWidget; {

        stackedWidget_->setContentsMargins(0, 0, 0, 0);
        stackedWidget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    toolbar_ = new QToolBar();
}


FrameInterface* MenuPrivate::get_FrameInterface(int _frameID) {

    FrameInterface* framePtr(0);

    FOR_I(framePairList_.size()) {

        FrameInterface *frame(framePairList_.at(i).first);

        if (frame->frameID_ == _frameID) {

            framePtr = frame;
            break;
        }
    }

    return framePtr;
}


int MenuPrivate::get_FrameIndex(int _frameID) {

    int index(-1);

    FOR_I(framePairList_.size()) {

        FrameInterface *frame(framePairList_.at(i).first);

        if (frame->frameID_ == _frameID) {

            index = i;
            break;
        }
    }

    return index;
}


int MenuPrivate::register_Frame(FrameInterface *_frame, QToolButton *_button) {

    int counter(-1);

    if (_frame) {

        counter = framePairList_.size(); {

            _frame->frameID_ = counter;
            framePairList_.append(qMakePair(_frame, _button));
            stackedWidget_->addWidget(_frame);

            /* ------------------------------------- (CONNECT) */

            connect(_button, &QToolButton::clicked, [=] () {

                set_DisplayFrame(counter);
            });
        }

        toolbar_->addWidget(_button);
    }

    return counter;
}


void MenuPrivate::set_DisplayFrame(int _frameID) {

    int index(get_FrameIndex(_frameID));

    if (index < 0) return; /* returns -1 on fail */

    FrameInterface *frame(framePairList_.at(index).first);
    QToolButton *button(framePairList_.at(index).second);

    if (frame) {

        /* check if clicked frame is displayed */
        if (stackedWidget_->isVisible() &&
            stackedWidget_->currentIndex() == index) {

            if (menuHides_) stackedWidget_->hide();
        }

        else { 	/* turn all buttons off and load the selected frame */

            FOR_I(framePairList_.size()) {

                framePairList_.at(i).second->setChecked(false);
            }

            stackedWidget_->setCurrentIndex(_frameID);

            button->setChecked(true);
            stackedWidget_->show();
        }
    }
}
