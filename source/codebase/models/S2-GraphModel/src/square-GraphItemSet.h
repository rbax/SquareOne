#pragma once

// Includes: Qt
#include <QString>
class QTextStream;

// Includes: Project
#include "S2-GraphModel_Export.h"


//QT_FORWARD_DECLARE_CLASS(QTextStream)


class S2_GRAPHMODEL_EXPORT ItemSet {

public: // ---------------------------------------------------------- PUBLIC

    ItemSet() {}

private: // --------------------------------------------------------- PRIVATE

    QString uniqueName(const QString& name) const; // fix

    bool load(QTextStream& stream); // fix this
    void save(QTextStream& stream); // fix this

    QString fileName() const; // fix this
    void setFileName(const QString& fileName); // fix this

    QString fileName_; // inspect
};
