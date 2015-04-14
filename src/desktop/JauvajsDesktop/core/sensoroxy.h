#ifndef SENSOROXY_H
#define SENSOROXY_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorOxy : public IDisplayable, IWorking {
public:
    SensorOxy();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);

    ~SensorOxy();
};

#endif // SENSOROXY_H
