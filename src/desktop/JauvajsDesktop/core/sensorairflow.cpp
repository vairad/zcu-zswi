#include <limits>

#include <QDebug>

#include "core/sensorairflow.h"

SensorAirFlow::SensorAirFlow() {
    minY = 0;
    maxY = 512;
    minX = 0;
    maxX = 60;
    time = 0;
    timeInterval = 0.02;

    name = "Dech";
    unit = "";
    isAnalysable = false;
}

/**
 * Vrati scenu s grafem
 * @brief SensorPosition::getSceneGraph
 * @return
 */
QGraphicsScene* SensorAirFlow::getSceneGraph() {
    return NULL;
    //return this->scene;
}

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorAirFlow::transmitData(float data) {
    //qDebug() << data << "Senzor";
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
 * @brief SensorPosition::getLastData
 * @return posledni data
 */
float SensorAirFlow::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorAirFlow::validateData(int data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorAirFlow::~SensorAirFlow() {

}

