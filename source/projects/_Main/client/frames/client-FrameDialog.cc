/* |INCLUDES: QT| */
#include <QLayout>
#include <QToolBar>
#include <QStackedWidget>
#include <QProcess>


/* |INCLUDES: SQUARE| */
#include "square.h"
#include "square-Menu.h"
#include "square-Frame.h"

#include "square-TableFrame.h"
#include "square-JsonFrame.h"


/* |INCLUDES: PROJECT| */
#include "client-FrameDialog.h"
#include "client-DragFrame.h"


FrameDialog::FrameDialog(QWidget *parent) : QDialog(parent) {

    QSize buttonSize(50, 50);

    /* ---------------------------------------------------- (MENU FRAMES) */

    Menu *squareMenu(new Menu(false)); {
		squareMenu->register_Frame(new JsonFrame(), SQUARE_OBJ::button("JsonFrame", buttonSize));
        squareMenu->register_Frame(new TableFrame(QStringList() << "1" << "2"), SQUARE_OBJ::button("TableFrame", buttonSize));
        squareMenu->register_Frame(new ClientDragFrame(), SQUARE_OBJ::button("DragFrame", buttonSize));
        squareMenu->set_Frame(0);
    }

    /* ---------------------------------------------------- (MENU TOOLBAR) */

    QToolBar *toolbar(squareMenu->get_ToolBar()); {

        toolbar->setOrientation(Qt::Vertical);
    }

    /* ---------------------------------------------------- (MAIN LAYOUT) */

    QHBoxLayout *mainLayout(new QHBoxLayout(this)); {

        mainLayout->addWidget(toolbar);
        mainLayout->addWidget(squareMenu->get_StackedWidget());
    }
}