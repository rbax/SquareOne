#pragma once

/* |INCLUDES: QT| */
#include <QWidget>

/* |INCLUDES: SQUARE| */
#include "S2-GraphModel_Export.h"

/* |INCLUDES: PROJECT| */
class GraphModel;




class S2_GRAPHMODEL_EXPORT GraphModelPrivate : public QObject {

    Q_OBJECT



public: /* ---------------------------------------------------------- [PUBLIC] */

    GraphModelPrivate(GraphModel *q);

    /* ------------------------------------------ (ACTIONS) */



    /* ------------------------------------------ (OBJECTS) */





private: /* --------------------------------------------------------- [PRIVATE] */

    GraphModel *q_ptr_;
};
