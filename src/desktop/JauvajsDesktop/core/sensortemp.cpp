#include <limits>

#include "core/sensortemp.h"

SensorTemp::SensorTemp() {
    ID = 1;
    minY = 32;
    maxY = 42;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Teplota";
    unit = "°C";
    isAnalysable = false;
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
void SensorTemp::transmitData(float data) {
    if (this->validateData(data)) {
        emit haveData(data);
        emit haveDataToSave(ID, data);
    } else {
        emit haveData(minY+1);
        emit haveDataToSave(ID, (maxY+minY)/2.0);
    }
}

/**
 * vrati posledni prijata data
 * @brief SensorTemp::getLastData
 * @return posledni data
 */
float SensorTemp::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorTemp::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorTemp::~SensorTemp() {

}

