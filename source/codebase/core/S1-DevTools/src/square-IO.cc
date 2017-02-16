
/* |INCLUDES: QT| */
#include <QTableWidget>
#include <QDebug>
#include <QDir>
#include <QSize>
#include <QFile>
#include <QTextStream>
#include <QFile>

/* |INCLUDES: SQUARE| */
#include "square.h"

/* |INCLUDES: PROJECT| */

SQUARE_START

/* --------------------------------------------------------------- (PATH FUNCTIONS) */

void IO::set_DeployPaths(const QString &_path) {

    QDir::setSearchPaths("assets", QStringList(_path + "/assets"));
    QDir::setSearchPaths("docs", QStringList(_path + "/docs"));
}

QString IO::get_ImagePath(const QString &_projectName) {

    return QString("assets:").append(_projectName).append("/images/");
}

QString IO::get_DocPath(const QString &_projectName) {

    return QString("assets:").append(_projectName).append("/docs/");
}

QString IO::get_DataPath(const QString &_projectName) {

    return QString("assets:").append(_projectName).append("/data/");
}

/* --------------------------------------------------------------- [FILE FUNCIONS] */

bool IO::fileExists(const QString &_filePath) {

    QFileInfo file(_filePath);

    if (file.exists() && file.isFile()) return true;

    else return false;
}

QStringList IO::parse_CSV(const QString &_filePath) {

    QStringList tokenList;

    if (fileExists(_filePath)) {

        QFile file(_filePath); {

            if (!file.open(QIODevice::ReadOnly)) {

//                qDebug() << "Error: failed to open csv " << _filePath;
                return tokenList;
            }
        }

        QTextStream textStream(&file);
        QString data = textStream.readAll();

        tokenList = QStringList(data.split("\n"));
    }

    return tokenList;
}

QStringList IO::parse_ByLine(const QString &_filePath) {

    QStringList tokenList;

    if (fileExists(_filePath)) {

        QFile file(_filePath); {

            if (!file.open(QIODevice::ReadOnly)) {

               // qDebug() << "Error: failed to open file " << _filePath;
                return tokenList;
            }
        }

        QTextStream textStream(&file);
        QString line;

        do {
            line = textStream.readLine();
            tokenList.append(textStream.readLine());
            if (textStream.atEnd())break;
        }
        while (!line.isNull());
    }

    return tokenList;
}

void IO::copy_DataFile(QString &_container, const QString &_filePath) {

    if (!fileExists(_filePath)) return;

    QFile file(_filePath); {

        if (!file.open(QIODevice::ReadOnly)) {

           // qDebug() << "Error: failed to open file " << _filePath;
        }

        _container.append(file.readAll());

        file.close();
    }
}

SQUARE_END