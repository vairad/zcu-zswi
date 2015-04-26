#include "core/datamanager.h"
#include "gui/mainwindow.h"
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

    DataManager manager;

    MainWindow w(&manager);
    w.show();
    w.initialWindow->show();
    manager.start();

    return a.exec();
}
