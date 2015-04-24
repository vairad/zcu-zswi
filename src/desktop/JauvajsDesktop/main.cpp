#include "core/datamanager.h"
#include "gui/mainwindow.h"
#include <QApplication>
#include <QDebug>

/**
 * Spusti aplikaci
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DataManager manager;

    qDebug()<<"manager loaded";

    MainWindow w(&manager);

    qDebug()<<"main win const";
    w.show();

    qDebug()<<"main win showed";
    w.initialWindow->show();

    qDebug()<<"initial win showed";
    manager.start();

    qDebug()<<"manager started";

    return a.exec();
}


