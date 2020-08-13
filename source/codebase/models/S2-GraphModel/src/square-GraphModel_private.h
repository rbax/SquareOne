#pragma once


// Includes: Qt
#include <QWidget>

// Includes: Project
#include "S2-GraphModel_Export.h"
class GraphModel;


class S2_GRAPHMODEL_EXPORT GraphModelPrivate : public QObject {

    Q_OBJECT


public: // ---------------------------------------------------------- PUBLIC

    GraphModelPrivate(GraphModel* q);


private: // --------------------------------------------------------- PRIVATE

    GraphModel* q_ptr_;
};
