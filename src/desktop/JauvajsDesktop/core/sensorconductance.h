#ifndef SENSORCON_H
#define SENSORCON_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorConductance : public IDisplayable, public IWorking {
    const float MINIMAL_CORRECT_VALUE = 0.0;
    const float MAXIMAL_CORRECT_VALUE = 10.0;

    bool validateData(float);

public:
    SensorConductance();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorConductance();

};

#endif // SENSORCON_H
