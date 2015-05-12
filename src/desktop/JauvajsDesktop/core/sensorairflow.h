#ifndef POSITIONSENSOR_H
#define POSITIONSENSOR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorAirFlow : public IDisplayable, public IWorking {
   const float MINIMAL_CORRECT_VALUE = 0.0;
   const float MAXIMAL_CORRECT_VALUE = 512.0;

    bool validateData(int data);
public:
    SensorAirFlow();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorAirFlow();

};

#endif // POSITIONSENSOR_H
