#include "core/sensorheartrate.h"

SensorHeartRate::SensorHeartRate() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 60;
    time = 0;
    lastValue = -1;

    name = "Puls";
    unit = "";
}

/**
 * Vrati scenu s grafem
 * @brief SensorHeartRate::getSceneGraph
 * @return
 */
QGraphicsScene* SensorHeartRate::getSceneGraph() {
    return NULL;
    //return this->scene;
}

SensorHeartRate::~SensorHeartRate() {

}

