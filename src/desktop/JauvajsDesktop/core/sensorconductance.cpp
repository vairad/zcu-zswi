#include <limits>
#include <QDebug>

#include "core/sensorconductance.h"

SensorConductance::SensorConductance() {
    ID = 5;
    minY = 0;
    maxY = 20;
    minX = 0;
    maxX = 120;
    time = 0;
    timeInterval = 0.02;

    name = "Conductance";
    unit = "mV";
    isAnalysable = false;
}

/**
 * Vrati scenu s grafem
 * @brief SensorGSR::getSceneGraph
 * @return
 */
QGraphicsScene* SensorConductance::getSceneGraph() {
    return NULL;
    //return this->scene;
}

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorConductance::transmitData(float data) {
    //qDebug() << "C" << data;
    if (this->validateData(data)) {
        emit haveData(data);
        emit haveDataToSave(ID, data);
    } else {
        emit haveData(minY+1);
        emit haveDataToSave(ID, minY+((maxY-minY)/2));
    }
    //this->validateData(data);
}

/**
 * vrati posledni prijata data
 * @brief SensorGSR::getLastData
 * @return posledni data
 */
float SensorConductance::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorConductance::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorConductance::~SensorConductance() {

}

