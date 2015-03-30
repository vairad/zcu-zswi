#ifndef SENSORGSR_H
#define SENSORGSR_H

#include "core/idisplayable.h"

class SensorGSR : public IDisplayable {
public:
    SensorGSR();
    QGraphicsScene* getSceneGraph();
    ~SensorGSR();
};

#endif // SENSORGSR_H
