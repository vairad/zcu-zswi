#include "core/sensorekg.h"

#include <QDebug>

SensorEKG::SensorEKG() {
    minY = 0;
    maxY = 5;
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

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorEKG::transmitData(float data){
   // this->validateData(data);
    qDebug() << "přijatá data" << data ;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
void SensorEKG::validateData(float data) {

}

SensorEKG::~SensorEKG() {

}

