#ifndef POSITIONSENSOR_H
#define POSITIONSENSOR_H

#include "core/idisplayable.h"

class SensorPosition : public IDisplayable {
public:
    SensorPosition();
    QGraphicsScene* getSceneGraph();
    ~SensorPosition();
};

#endif // POSITIONSENSOR_H
