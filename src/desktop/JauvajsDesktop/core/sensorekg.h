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
    float getLastData();

    ~SensorEKG();

private:
    void validateData(float);
};

#endif // EKGSENSOR_H

