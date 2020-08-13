#pragma once

/* |INCLUDES: QT| */
#include <QToolBar>
#include <QSignalMapper>
#include <QStackedWidget>

/* |INCLUDES: SQUARE| */
#include "square-FrameInterface.h"
#include "square-Frame.h"
#include "S1-GuiTools_Export.h"


class S1_GUITOOLS_EXPORT Menu;


class S1_GUITOOLS_EXPORT MenuPrivate : public QObject {

    Q_OBJECT

public: // ---------------------------------------------------------- PUBLIC

    MenuPrivate(Menu* q);

    int	register_Frame(FrameInterface* frame, QToolButton* button);

    void set_DisplayFrame(int frameID);

    FrameInterface* get_FrameInterface(int frameID);
    int get_FrameIndex(int frameID);


    QToolBar* toolbar_;
    QStackedWidget* stackedWidget_;
    QList<QPair<FrameInterface*, QToolButton*>> framePairList_;
    bool menuHides_;

private: // --------------------------------------------------------- PRIVATE

    Menu* q_ptr_;
};
