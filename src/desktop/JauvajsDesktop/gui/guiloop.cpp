#include "guiloop.h"
#include "gui/sensorwidget.h"
#include <QDebug>
#include <QCoreApplication>

GUILoop::GUILoop(DataManager *manager) {
    draw = false;
    this->manager = manager;
}

/*void GUILoop::run() {
    qDebug() << "run GUI loop";

    int count = 0;
    while (true) {
        if (count == 20) {
            if (draw) {
                manager->draw = true;
                QCoreApplication::processEvents();
                //emit updateSignal(2.5);
            }
            count = 0;
        }
        //qDebug() << count;

        for(int i=0; i < 100000; i++) {}
        count++;
    }
}*/

GUILoop::~GUILoop() {

}

