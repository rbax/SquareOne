#pragma once

/* |INCLUDES: QT| */

/* |INCLUDES: SQUARE| */
#include "square-FrameInterface.h"

/* |INCLUDES: PROJECT| */
#include "_client_Export.h"


class _CLIENT_EXPORT ClientDragFrame : public FrameInterface {

   Q_INTERFACES(FrameInterface)

      Q_OBJECT

public: /* ---------------------------------------------------------- [PUBLIC] */

	ClientDragFrame();


private: /* --------------------------------------------------------- [PRIVATE] */

};
