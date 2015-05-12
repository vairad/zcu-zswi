#include <limits>
#include <QDebug>

#include <QApplication>

#include "core/sensorresistance.h"

SensorResistance::SensorResistance() {
    ID = 4;
    minY = 0;
    maxY = 300;
    minX = 0;
    maxX = 120;
    time = 0;
    timeInterval = 0.02;

    name = "Rezistance";
    unit = "kΩ";
    isAnalysable = false;
}

/**
 * Vrati scenu s grafem
 * @brief SensorGSR::getSceneGraph
 * @return
 */
QGraphicsScene* SensorResistance::getSceneGraph() {
    return NULL;
    //return this->scene;
}

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorResistance::transmitData(float data) {
   // qDebug() << "R" << data;
    if (this->validateData(data)) {
        emit haveData(data/1000);
        emit haveDataToSave(ID, data/1000);
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
float SensorResistance::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorResistance::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
        return false;
    }else{
        return true;
    }
}

SensorResistance::~SensorResistance() {

}

