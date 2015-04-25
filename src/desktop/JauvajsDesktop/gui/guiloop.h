#ifndef GUILOOP_H
#define GUILOOP_H

#include <QThread>
#include "core/datamanager.h"

class GUILoop : public QThread {
Q_OBJECT
public:
    GUILoop(DataManager *manager);
    ~GUILoop();
    void run();

    bool draw;
    DataManager *manager;

signals:
    void updateSignal(double);
};

#endif // GUILOOP_H
