#include "core/sensorgsr.h"

SensorGSR::SensorGSR() {
    minY = 0;
    maxY = 10;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "GSR";
    unit = "S";
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

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorGSR::transmitData(float data){
    data = 42;
}

SensorGSR::~SensorGSR() {

}

