#ifndef POSITIONSENSOR_H
#define POSITIONSENSOR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorPosition : public IDisplayable, public IWorking {
public:
    SensorPosition();
    QGraphicsScene* getSceneGraph();
    void transmitData(float);

    ~SensorPosition();
};

#endif // POSITIONSENSOR_H
