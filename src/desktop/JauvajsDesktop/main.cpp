#include "core/datamanager.h"
#include "gui/guiloop.h"
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
    //GUILoop loop(&manager);

    qDebug()<<"manager loaded";
    //loop.start();
    MainWindow w(&manager);

    qDebug()<<"main win const";
    w.show();

    qDebug()<<"main win showed";
    w.initialWindow->show();

    qDebug()<<"initial win showed";
    manager.start();

    qDebug()<<"manager started";
    //QObject::connect(&loop, SIGNAL(finished()), &a, SLOT(quit()));

    return a.exec();
}


