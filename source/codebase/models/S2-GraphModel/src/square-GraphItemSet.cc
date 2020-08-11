
#include "square-GraphItemSet.h"

QString ItemSet::uniqueName(const QString& _name) const {

    QString unique;

    //for (int i = 0; ; ++i) {

    //    unique = _name;

    //    if (i > 0) unique += QString::number(i);
    //    if (indexOf(unique) == -1) break;
    //}

    return unique;
}


bool ItemSet::load(QTextStream& stream) {

    /* shapeList_.clear();

    while (!stream.atEnd()) {

    QString shapeType, shapeName, colorName;
    int left, top, width, height;
    stream >> shapeType >> shapeName >> colorName >> left >> top >> width >> height;

    if (stream.status() != QTextStream::Ok) return false;

    bool ok;
    GraphShape::Type type(GraphShape::stringToType(shapeType, &ok));
    if (!ok) return false;

    QColor color(colorName); {

    if (!color.isValid()) return false;
    }

    GraphShape shape(type); {

    shape.name_ = shapeName;
    shape.color_ = color;
    shape.rect_ = QRect(left, top, width, height);
    shapeList_.append(shape);
    }
    }

    currentIndex_ = shapeList_.isEmpty()
    ? -1
    : 0;*/

    return true;
}

void ItemSet::save(QTextStream& stream) {

    //for (int i = 0; i < shapeList_.count(); ++i) {

    //    const GraphShape &shape(shapeList_.at(i));

    //    QRect r(shape.rect()); {

    //        stream << GraphShape::typeToString(shape.type()) << QLatin1Char(' ')
    //            << shape.name() << QLatin1Char(' ')
    //            << shape.color().name() << QLatin1Char(' ')
    //            << r.left() << QLatin1Char(' ')
    //            << r.top() << QLatin1Char(' ')
    //            << r.width() << QLatin1Char(' ')
    //            << r.height();
    //    }

    //    if (i != shapeList_.count() - 1) {

    //        stream << QLatin1Char('\n');
    //    }
    //}

    //undoStack_->setClean();
}


QString ItemSet::fileName() const {
    return fileName_;
}

void ItemSet::setFileName(const QString& fileName) {
    fileName_ = fileName;
}
