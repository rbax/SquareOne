// Includes: Qt
#include <QtDebug>
#include <QCommandLineParser>
#include <QLoggingCategory>
#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include <QMessageBox>

// Includes: Square
#include <square.h>

// Includes: Project
#include "mainwindow.h"


/* Attributes set BEFORE constructing Q(Gui)Application. */
void pre_settings_QT() {

    /* App Settings */
    QCoreApplication::setOrganizationName("Square");
    QCoreApplication::setOrganizationDomain("SquareOne.com");
    QCoreApplication::setApplicationName("SquareOne");
    QCoreApplication::setApplicationVersion("1.0.0");

    /* High DPI Display Support */
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);

    /* Turn off network ssl warnings */
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

/* CLI or GUI */
QCoreApplication* createApplication(int& argc, char* argv[]) {

    for (int i = 1; i < argc; ++i) {
        if (!qstrcmp(argv[i], "-cli")) return new QCoreApplication(argc, argv);
    }
    return new QApplication(argc, argv);
}


int main(int argc, char** argv) {

    pre_settings_QT();
    QScopedPointer<QCoreApplication> app(createApplication(argc, argv));
    QT_REQUIRE_VERSION(argc, argv, "5.2.0")

    QDir path(QDir(qApp->applicationDirPath()));
    // @TODO: use library paths instead (kludge)
    path.cdUp();
    path.cdUp();
    SQUARE_IO::set_DeployPaths(path.canonicalPath());

    // ---------------------------------------------------------- (GUI)

    if (qobject_cast<QApplication*>(app.data())) {
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette palette(qApp->palette());
        SQUARE_STYLES::set_PaletteStyle(palette);
        qApp->setPalette(palette);

        MainWindow mainWindow;
        mainWindow.setGeometry(100, 100, 800, 500);
        mainWindow.show();

        return app->exec();
    }

    // ---------------------------------------------------------- CLI

    else {
        return app->exec();
    }
}
