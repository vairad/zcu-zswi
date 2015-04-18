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
   this->validateData(data);
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
void SensorPosition::validateData(float data) {

}

SensorPosition::~SensorPosition() {

}

