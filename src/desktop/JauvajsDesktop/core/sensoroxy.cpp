#include "core/sensoroxy.h"

SensorOxy::SensorOxy() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 200;
    time = 0;
    lastValue = -1;

    name = "Okysličení";
}

/**
 * Vrati scenu s grafem
 * @brief SensorOxy::getSceneGraph
 * @return
 */
QGraphicsScene* SensorOxy::getSceneGraph() {
    return NULL;
    //return this->scene;
}

SensorOxy::~SensorOxy() {

}

