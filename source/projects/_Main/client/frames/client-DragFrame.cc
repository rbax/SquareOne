/* |INCLUDES:  |QT| */
#include <QSize>
#include <QDir>

/* |INCLUDES:  |SQUARE| */
#include "square.h"
#include "square-DragFrame.h"

/* |INCLUDES:  |PROJECT| */
#include "client-DragFrame.h"


ClientDragFrame::ClientDragFrame() : FrameInterface() {

    QString imagePath(SQUARE_IO::get_ImagePath(QString("_Client")));

    QSize label_size(QSize(50, 20));

    DragFrame *dragframe(new DragFrame()); {

        dragframe->set_ItemSize(QSize(75, 75));

        dragframe->create_ItemFrame(SQUARE_OBJ::button("Service", label_size),
                                    QStringList()
                                    << imagePath + "WS1.png"
                                    << imagePath + "WS2.png"
                                    << imagePath + "WS3.png"
                                    << imagePath + "WS4.png"
                                    << imagePath + "WS5.png");

        dragframe->create_ItemFrame(SQUARE_OBJ::button("Adapter", label_size),
                                    QStringList()
                                    << imagePath + "A1.png"
                                    << imagePath + "A2.png"
                                    << imagePath + "A3.png"
                                    << imagePath + "A4.png"
                                    << imagePath + "A5.png");

        dragframe->create_ItemFrame(SQUARE_OBJ::button("Filter", label_size),
                                    QStringList()
                                    << imagePath + "F1.png"
                                    << imagePath + "F2.png"
                                    << imagePath + "F3.png"
                                    << imagePath + "F4.png"
                                    << imagePath + "F5.png");

        insert_Widget(dragframe);
    }
}