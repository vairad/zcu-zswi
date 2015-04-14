#ifndef SENSORHEARTRATE_H
#define SENSORHEARTRATE_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorHeartRate : public IDisplayable, public IWorking {
public:
    SensorHeartRate();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);

    ~SensorHeartRate();
};

#endif // SENSORHEARTRATE_H
