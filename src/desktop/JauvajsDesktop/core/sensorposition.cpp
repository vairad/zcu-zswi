#include "core/sensorposition.h"

SensorPosition::SensorPosition() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 200;
    time = 0;
    lastValue = -1;

    name = "Poloha";
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

SensorPosition::~SensorPosition() {

}

