#include "core/sensortemp.h"

SensorTemp::SensorTemp() {
    minY = 32;
    maxY = 42;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Teplota";
    unit = "°C";
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

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorTemp::transmitData(float data){
    this->validateData(data);
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
void SensorTemp::validateData(float data) {

}

SensorTemp::~SensorTemp() {

}

