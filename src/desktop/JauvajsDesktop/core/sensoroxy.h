#ifndef SENSOROXY_H
#define SENSOROXY_H

#include "core/idisplayable.h"

class SensorOxy : public IDisplayable {
public:
    SensorOxy();
    QGraphicsScene* getSceneGraph();
    ~SensorOxy();
};

#endif // SENSOROXY_H
