#include "core/sensorposition.h"

SensorPosition::SensorPosition() {
    minY = 1;
    maxY = 5;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Poloha";
    unit = "";
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

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorPosition::transmitData(float data){
   emit haveData(data);
    //this->validateData(data);
}

/**
 * vrati posledni prijata data
 * @brief SensorPosition::getLastData
 * @return posledni data
 */
float SensorPosition::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
void SensorPosition::validateData(float data) {

}

SensorPosition::~SensorPosition() {

}

