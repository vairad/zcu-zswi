#include "mainwindow.h"
#include <QApplication>

/**
 * Spusti aplikaci
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.draw();

    return a.exec();
}


