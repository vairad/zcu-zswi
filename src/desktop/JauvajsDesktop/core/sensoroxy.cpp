#include <limits>

#include "core/sensoroxy.h"

SensorOxy::SensorOxy() {
    ID = 3;
    minY = 75;
    maxY = 100;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Okysličení";
    unit = "%";
    isAnalysable = false;
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
void SensorOxy::transmitData(float data) {
    if (this->validateData(data)) {
        emit haveData(data);
        emit haveDataToSave(ID, data);
    } else {
        emit haveData((maxY+minY)/2.0);
        emit haveDataToSave(ID, (maxY+minY)/2.0);
    }
}

/**
 * vrati posledni prijata data
 * @brief SensorOxy::getLastData
 * @return posledni data
 */
float SensorOxy::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorOxy::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}


SensorOxy::~SensorOxy() {

}



