
#include "mainwindow.h"
#include "client-FrameDialog.h"


MainWindow::MainWindow(QWidget* parent):QMainWindow(parent) {
    setCentralWidget(new FrameDialog());
}
