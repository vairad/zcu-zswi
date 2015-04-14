#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorTemp : public IDisplayable, public IWorking {
public:
    SensorTemp();
    QGraphicsScene* getSceneGraph();
    void transmitData(float);

    ~SensorTemp();
};

#endif // TEMPSENSOR_H
