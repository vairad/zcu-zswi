#include <limits>

#include "core/sensorgsr.h"

SensorGSR::SensorGSR() {
    ID = 4;
    minY = 0;
    maxY = 10;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "GSR";
    unit = "S";
    isAnalysable = false;
}

/**
 * Vrati scenu s grafem
 * @brief SensorGSR::getSceneGraph
 * @return
 */
QGraphicsScene* SensorGSR::getSceneGraph() {
    return NULL;
    //return this->scene;
}

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorGSR::transmitData(float data) {
    if (this->validateData(data)) {
        emit haveData(data);
        emit haveDataToSave(ID, data);
    } else {
        emit haveData(minY+((maxY-minY)/2));
        emit haveDataToSave(ID, minY+((maxY-minY)/2));
    }
    //this->validateData(data);
}

/**
 * vrati posledni prijata data
 * @brief SensorGSR::getLastData
 * @return posledni data
 */
float SensorGSR::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorGSR::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorGSR::~SensorGSR() {

}

