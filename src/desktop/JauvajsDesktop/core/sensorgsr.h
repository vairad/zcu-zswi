#ifndef SENSORGSR_H
#define SENSORGSR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorGSR : public IDisplayable, public IWorking {
public:
    SensorGSR();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorGSR();

private:
    void validateData(float);
};

#endif // SENSORGSR_H
