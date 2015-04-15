#include "core/sensorheartrate.h"

SensorHeartRate::SensorHeartRate() {
    minY = 0;
    maxY = 200;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Puls";
    unit = "PPM";
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

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorHeartRate::transmitData(float data){
    data = 42;
}

SensorHeartRate::~SensorHeartRate() {

}

