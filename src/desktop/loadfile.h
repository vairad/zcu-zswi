#ifndef LOADFILE_H
#define LOADFILE_H

#include <QtCore>
#include "sensorekg.h"

/**
 * Simuluje ziskavani dat z e-health
 * @brief The LoadFile class
 */
class LoadFile : public QThread {
public:
    LoadFile(SensorWidget *g);
    ~LoadFile();
    void run();
    void setGraph(SensorWidget *g);
    void setScene(QGraphicsScene *s);

private:
    SensorWidget *g;
    QGraphicsScene *s;
};

#endif // LOADFILE_H
