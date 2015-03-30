#ifndef SENSORHEARTRATE_H
#define SENSORHEARTRATE_H

#include "core/idisplayable.h"

class SensorHeartRate : public IDisplayable {
public:
    SensorHeartRate();
    QGraphicsScene* getSceneGraph();
    ~SensorHeartRate();
};

#endif // SENSORHEARTRATE_H
