#ifndef SENSORGSR_H
#define SENSORGSR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorGSR : public IDisplayable, public IWorking {
public:
    SensorGSR();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);

    ~SensorGSR();
};

#endif // SENSORGSR_H
