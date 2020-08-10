#pragma once

/* |INCLUDES: QT| */
class QTableWidget;
class QStringList;
class QSize;
class QString;
//class QFile;

/*  |INCLUDES: PROJECT| */
#include "S1-DevTools_Export.h"
#include "square-Macros.h"

SQUARE_START

class S1_DEVTOOLS_EXPORT IO {

public:

    /* ---------------------------------------------------------- (PATH FUNCTIONS) */
    static
        void set_DeployPaths(const QString &path);

    static
        QString get_ImagePath(const QString &projectName);

    static
        QString get_DocPath(const QString &projectName);

    static
        QString get_DataPath(const QString &projectName);


    /* ---------------------------------------------------------- (FILE FUNCIONS) */

    static /* Return true if file .exists() && .isFile() */
        bool fileExists(const QString &fullFilePath);

    static /* Parse a CSV file into a QStringList */
        QStringList parse_CSV(const QString &fullFilePath);

    static
        QStringList parse_ByLine(const QString &fullFilePath);
  
    static
       void copy_DataFile(QString &container, const QString &filePath);

    /*   static
           QFile get_File(const QString &fullFilePath);*/

   // static
       // void fill_TextEdit(const QString &filePath);

};

SQUARE_END
