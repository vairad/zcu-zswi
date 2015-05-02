#include <limits>

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
    isAnalysable = true;
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
void SensorEKG::transmitData(float data) {
    if (this->validateData(data)) {
        //this->lastData = data;
        emit haveData(data);
        emit haveDataToSave(ID, data);
    } else {
        emit haveData((maxY+minY)/2.0);
        emit haveDataToSave(ID, (maxY+minY)/2.0);
    }
    // this->validateData(data);
}

/**
 * vrati posledni prijata data
 * @brief SensorEKG::getLastData
 * @return posledni data
 */
float SensorEKG::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorEKG::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorEKG::~SensorEKG() {

}

