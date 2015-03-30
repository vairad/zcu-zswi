#ifndef EKGSENSOR_H
#define EKGSENSOR_H

#include "core/idisplayable.h"
#include "gui/sensorwidget.h"

class SensorEKG : public IDisplayable {
public:
    SensorEKG();
    QGraphicsScene* getSceneGraph();
    ~SensorEKG();

};

#endif // EKGSENSOR_H
