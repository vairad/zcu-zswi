#ifndef SENSORGSR_H
#define SENSORGSR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorResistance : public IDisplayable, public IWorking {
    const float MINIMAL_CORRECT_VALUE = 1000.0;
    const float MAXIMAL_CORRECT_VALUE = 3000000.0;

    bool validateData(float);

public:
    SensorResistance();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorResistance();

};

#endif // SENSORGSR_H
