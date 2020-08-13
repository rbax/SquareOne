#pragma once

// Includes: Qt
class QLineEdit;
class QTableWidget;

// Includes: Project
#include "S3-TableFrame_Export.h"
class TableFrame;


class S3_TABLEFRAME_EXPORT TableFramePrivate {

public: // ---------------------------------------------------------- PUBLIC

    TableFramePrivate(TableFrame* q);

    QLineEdit* searchLineEdit_;
    QTableWidget* tableWidget_;
    QStringList columnNamesList_;

private: // --------------------------------------------------------- PRIVATE

    TableFrame* q_ptr_;

};
