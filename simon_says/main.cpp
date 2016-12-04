#include "mainwindow.h"
#include <QApplication>

/**
 * @brief qMain
 * Main for the application. creates the window
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
