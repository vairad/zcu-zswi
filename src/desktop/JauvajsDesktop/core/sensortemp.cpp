#include "core/sensortemp.h"

SensorTemp::SensorTemp() {
    minY = 32;
    maxY = 42;
    minX = 0;
    maxX = 200;
    time = 0;
    lastValue = -1;

    name = "Teplota";
}

/**
 * Vrati scenu s grafem
 * @brief SensorTemp::getSceneGraph
 * @return
 */
QGraphicsScene* SensorTemp::getSceneGraph() {
    return NULL;
    //return this->scene;
}

SensorTemp::~SensorTemp() {

}

