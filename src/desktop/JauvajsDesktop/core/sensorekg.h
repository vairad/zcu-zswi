#ifndef EKGSENSOR_H
#define EKGSENSOR_H

#include "core/idisplayable.h"
#include "core/iworking.h"

#include "gui/sensorwidget.h"

class SensorEKG : public IDisplayable, public IWorking {
    static const int ID = 0;
    const float MINIMAL_CORRECT_VALUE = 0.0;
    const float MAXIMAL_CORRECT_VALUE = 6.0;

    bool validateData(float);
public:
    SensorEKG();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorEKG();

};

#endif // EKGSENSOR_H

