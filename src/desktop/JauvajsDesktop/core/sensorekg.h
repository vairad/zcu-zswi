#ifndef EKGSENSOR_H
#define EKGSENSOR_H

#include "core/idisplayable.h"
#include "core/iworking.h"

#include "gui/sensorwidget.h"

class SensorEKG : public IDisplayable, public IWorking {
public:
    SensorEKG();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);

    ~SensorEKG();

};

#endif // EKGSENSOR_H
