#include "core/sensoroxy.h"

SensorOxy::SensorOxy() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Okysličení";
    unit = "";
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

