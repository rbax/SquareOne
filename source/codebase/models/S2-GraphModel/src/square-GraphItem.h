#pragma once

// Includes: Qt
#include <QMetaType>
#include <QColor>
#include <QRectF>

// Includes: Project
#include "S2-GraphModel_Export.h"


struct S2_GRAPHMODEL_EXPORT GraphItem {

    GraphItem() {}

    QColor fillColor = Qt::darkBlue;
    QColor handleColor = Qt::white;
    QColor borderColor = Qt::black;
    QColor textColor = Qt::black;

    qreal penWidth = 1;
    QRectF rect = QRectF(-100 - penWidth / 20,
                         -100 - penWidth / 20,
                         200 + penWidth,
                         200 + penWidth);
};

Q_DECLARE_METATYPE(GraphItem)


struct S2_GRAPHMODEL_EXPORT GraphData {

    GraphData() {}
};

Q_DECLARE_METATYPE(GraphData)
