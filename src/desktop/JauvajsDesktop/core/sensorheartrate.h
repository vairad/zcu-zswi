#ifndef SENSORHEARTRATE_H
#define SENSORHEARTRATE_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorHeartRate : public IDisplayable, public IWorking {    
    const float MINIMAL_CORRECT_VALUE = -1.0;
    const float MAXIMAL_CORRECT_VALUE = 220.0;

    bool validateData(float);

public:
    SensorHeartRate();
    QGraphicsScene* getSceneGraph();
    void transmitData(float);
    float getLastData();

    ~SensorHeartRate();

};

#endif // SENSORHEARTRATE_H
