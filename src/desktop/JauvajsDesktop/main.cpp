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

    qDebug() << "App started";

    DataManager manager;

    qDebug() << "Manager created";

    MainWindow w(&manager);

    qDebug() << "Main window constructed";

    w.show();

    qDebug() << "Main window showed";

    w.initialWindow->show();

    qDebug() << "Initial window showed";

    manager.start();

    qDebug() << "Manager working";

    return a.exec();
}
