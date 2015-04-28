#include <limits>

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
    isAnalysable = false;
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
    if(this->validateData(data)){
        emit haveData(data);
    }else{
        emit haveData((maxY+minY)/2.0);
    }
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
bool SensorPosition::validateData(int data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorPosition::~SensorPosition() {

}

