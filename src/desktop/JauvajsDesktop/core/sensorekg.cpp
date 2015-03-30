#include "core/sensorekg.h"

/*** NEZAPOMENOUT ODEBRAT ***/
#include "loadfile.h"

SensorEKG::SensorEKG() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 200;
    time = 0;
    lastY = -1;

    name = "EKG";
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

