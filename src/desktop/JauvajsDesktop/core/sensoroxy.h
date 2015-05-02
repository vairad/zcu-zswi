#ifndef SENSOROXY_H
#define SENSOROXY_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorOxy : public IDisplayable, public IWorking {
    static const int ID = 3;
    const float MINIMAL_CORRECT_VALUE = 75.0;
    const float MAXIMAL_CORRECT_VALUE = 100.0;

    bool validateData(float data);

public:
    SensorOxy();
    QGraphicsScene* getSceneGraph();
    void transmitData(float);
    float getLastData();

    ~SensorOxy();

};

#endif // SENSOROXY_H
