#include "core/sensorposition.h"

SensorPosition::SensorPosition() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Poloha";
    unit = "";
}

/**
 * Vrati scenu s grafem
 * @brief SensorPosition::getSceneGraph
 * @return
 */
QGraphicsScene* SensorPosition::getSceneGraph() {
    return NULL;
    //return this->scene;
}

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorPosition::transmitData(float data){
    data = 42;
}

SensorPosition::~SensorPosition() {

}

