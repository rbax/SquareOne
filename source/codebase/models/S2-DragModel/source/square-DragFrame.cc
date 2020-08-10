/* |INCLUDES: QT| */
#include "qlayout.h"
#include <Qsplitter>
#include <QStackedWidget>
#include <QToolbar>

/* |INCLUDES: SQUARE| */
#include "square.h"
#include "square-FrameInterface.h"
#include "square-Menu.h"
#include "square-Frame.h"

/* |INCLUDES: PROJECT| */
#include "square-DragFrame.h"
#include "square-DragFrame_private.h"

#include "square-DragListWidget.h"
#include "square-DragWidget.h"
#include "square-DragItem.h"


/* ------------------------------------------------------------------ [DRAGFRAME] */

DragFrame::DragFrame() : FrameInterface(), z_ptr_(new DragFramePrivate(this)) {

    QWidget *headFrame = SQUARE_OBJ::containerH(); {

        QLayout *layout = headFrame->layout(); {

            layout->addWidget(z_ptr_->itemMenu_.get_ToolBar());
            layout->addWidget(SQUARE_OBJ::spacer(QSize(1, 0)));
            layout->addWidget(z_ptr_->slideMenu_.get_ToolBar());
        }
    }

    insert_Widget(headFrame);
    insert_Widget(z_ptr_->itemMenu_.get_StackedWidget());
    insert_Widget(z_ptr_->splitter_);
}


void DragFrame::set_ItemSize(QSize _size) {

    z_ptr_->itemSize_ = _size;
}


void DragFrame::set_MimeString(QString _mime) {

    z_ptr_->mimeString_ = _mime;
}


void DragFrame::create_ItemFrame(QToolButton *_button, const QStringList &_imagePathList) {

    z_ptr_->insert_Items(_button, _imagePathList);
}


void DragFrame::create_ItemFrame(QToolButton *_button, const QList<DragItem*> &_frameObjectList) {

    z_ptr_->insert_Items(_button, _frameObjectList);
}


DragItem* DragFrame::create_DragItem(const QString &_path) {

    return new DragItem();
}


/* ------------------------------------------------------------------ [DRAGFRAME_PRIVATE] */

DragFramePrivate::DragFramePrivate(DragFrame *q) : q_ptr_(q),
mimeString_("square/x-d2node-data"),
itemSize_(50, 50) {

    //square_slide_menu_ = new Menu(); {

    //   frame_node_data = new DragItemFrame();
    //   
    //   square_slide_menu_.register_Frame(frame_node_data, ObjectFactory::button("Menu", QSize(20, 50)));
    //}


    QSizePolicy policy; {

        policy.setHorizontalPolicy(QSizePolicy::Expanding);
        policy.setVerticalPolicy(QSizePolicy::Expanding);
        policy.setVerticalStretch(1);
        policy.setHorizontalStretch(1);
    }

    dragCanvas_ = new DragWidget(itemSize_); {

        QObject::connect(dragCanvas_, &DragWidget::signal_ItemSelected, [=] (QRect &_itemRect) {

            DragItem *item = dragCanvas_->get_DragItem(_itemRect); {

                if (item) {

                    //  frame_node_data->set_DragItem(item);



                }
            }
        });
    }

    splitter_ = new QSplitter();
    {
        /* Splitter Settings */
        splitter_->addWidget(dragCanvas_);
        splitter_->addWidget(slideMenu_.get_StackedWidget());
        splitter_->setStretchFactor(1, 800);
        splitter_->setCollapsible(0, false);
        splitter_->setCollapsible(1, false);
        splitter_->setSizePolicy(policy);
    }
}


void DragFramePrivate::insert_Items(QToolButton *_button, const QStringList &_imagePathList) {

    DragListWidget *dragList = new DragListWidget(itemSize_); {

        FOR_I(_imagePathList.count()) {
            QPixmap itemPixMap = _imagePathList.at(i);
            dragList->addItem(SQUARE_OBJ::listWidgetItem(itemPixMap));
        }
    }

    Frame *frame = new Frame(); {

        QSizePolicy policy; {
            policy.setHorizontalPolicy(QSizePolicy::Expanding);
            policy.setVerticalPolicy(QSizePolicy::Expanding);
            policy.setVerticalStretch(0);
        }

        frame->setSizePolicy(policy);
        frame->insert__Widget(dragList, FrameInterface::HEADER);

        itemMenu_.register_Frame(frame, _button);
    }
}


void DragFramePrivate::insert_Items(QToolButton *_button, const QList<DragItem*> &_frameObjectList) {

    DragListWidget *dragList = new DragListWidget(itemSize_); {

        FOR_I(_frameObjectList.count()) {

            QListWidgetItem *list_item = SQUARE_OBJ::listWidgetItem(_frameObjectList.at(i)->pixmap); {
                list_item->setData(Qt::UserRole + 1, dragItemList_.size());
            }

            dragList->addItem(list_item);
            dragItemList_.append(_frameObjectList.at(i));
        }
    }

    Frame *frame = new Frame(); {

        QSizePolicy policy; {
            policy.setHorizontalPolicy(QSizePolicy::Expanding);
            policy.setVerticalPolicy(QSizePolicy::Expanding);
            policy.setVerticalStretch(0);
        }

        frame->setSizePolicy(policy);
        frame->insert__Widget(dragList, FrameInterface::HEADER);

        itemMenu_.register_Frame(frame, _button);
    }
}
