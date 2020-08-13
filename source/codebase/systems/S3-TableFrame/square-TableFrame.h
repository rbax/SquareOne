#pragma once

// Includes: Square
#include "square-FrameInterface.h"

// Includes: Project
#include "S3-TableFrame_Export.h"
class TableFramePrivate;


class S3_TABLEFRAME_EXPORT TableFrame : public FrameInterface {

    Q_INTERFACES(FrameInterface)

        Q_OBJECT

public: // ---------------------------------------------------------- PUBLIC

    TableFrame(const QStringList& columnNameList);


private: // --------------------------------------------------------- PRIVATE

    TableFramePrivate* z_ptr_;
};
