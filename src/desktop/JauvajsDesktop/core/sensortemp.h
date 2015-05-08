#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorTemp : public IDisplayable, public IWorking {
    const float MINIMAL_CORRECT_VALUE = 33.0;
    const float MAXIMAL_CORRECT_VALUE = 43.0;

     bool validateData(float data);

public:
    SensorTemp();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorTemp();

private:

};

#endif // TEMPSENSOR_H
