#ifndef SENSORGSR_H
#define SENSORGSR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorGSR : public IDisplayable, public IWorking {
    static const int ID = 4;
    const float MINIMAL_CORRECT_VALUE = 0.0;
    const float MAXIMAL_CORRECT_VALUE = 10.0;

    bool validateData(float);

public:
    SensorGSR();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorGSR();

};

#endif // SENSORGSR_H
