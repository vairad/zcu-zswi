#ifndef SENSOROXY_H
#define SENSOROXY_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorOxy : public IDisplayable, public IWorking {
public:
    SensorOxy();
    QGraphicsScene* getSceneGraph();
    void transmitData(float);
    float getLastData();

    ~SensorOxy();

private:
    void validateData(float);
};

#endif // SENSOROXY_H
