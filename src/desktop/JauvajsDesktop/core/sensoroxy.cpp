#include "core/sensoroxy.h"

SensorOxy::SensorOxy() {
    minY = 0;
    maxY = 100;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Okysličení";
    unit = "%";
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

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorOxy::transmitData(float data){
    this->validateData(data);
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
void SensorOxy::validateData(float data) {

}


SensorOxy::~SensorOxy() {

}



