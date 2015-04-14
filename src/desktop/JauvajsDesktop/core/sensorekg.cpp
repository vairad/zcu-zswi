#include "core/sensorekg.h"

SensorEKG::SensorEKG() {
    minY = 0;
    maxY = 6;
    minX = 0;
    maxX = 30;
    time = 0;
    timeInterval = 0.02;

    name = "EKG";
    unit = "mV";
}

/**
 * Vrati scenu s grafem
 * @brief EKGSensor::getSceneGraph
 * @return
 */
QGraphicsScene* SensorEKG::getSceneGraph() {
    return NULL;
    //return this->scene;
}

SensorEKG::~SensorEKG() {

}

