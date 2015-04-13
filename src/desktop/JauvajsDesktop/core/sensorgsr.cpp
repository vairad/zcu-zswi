#include "core/sensorgsr.h"

SensorGSR::SensorGSR() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 60;
    time = 0;
    lastValue = -1;

    name = "GSR";
    unit = "V";
}

/**
 * Vrati scenu s grafem
 * @brief SensorGSR::getSceneGraph
 * @return
 */
QGraphicsScene* SensorGSR::getSceneGraph() {
    return NULL;
    //return this->scene;
}

SensorGSR::~SensorGSR() {

}

