#ifndef GUILOOP_H
#define GUILOOP_H

#include <QThread>

class GUILoop : public QThread {
Q_OBJECT
public:
    GUILoop();
    ~GUILoop();
    void run();

    bool draw;

signals:
    void updateSignal(double);
};

#endif // GUILOOP_H
