#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "core/idisplayable.h"

class SensorTemp : public IDisplayable {
public:
    SensorTemp();
    QGraphicsScene* getSceneGraph();
    ~SensorTemp();
};

#endif // TEMPSENSOR_H
