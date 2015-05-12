#include <limits>

#include "core/sensorheartrate.h"
#include "QDebug"

SensorHeartRate::SensorHeartRate() {
    ID = 5;
    minY = 50;
    maxY = 200;
    minX = 0;
    maxX = 120;
    time = 0;
    timeInterval = 0.02;

    name = "Puls";
    unit = "PPM";
    isAnalysable = false;
}

/**
 * Vrati scenu s grafem
 * @brief SensorHeartRate::getSceneGraph
 * @return
 */
QGraphicsScene* SensorHeartRate::getSceneGraph() {
    return NULL;
    //return this->scene;
}

/**
 * Pracuje s predanymi daty
 * @param data prijata data
 */
void SensorHeartRate::transmitData(float data) {

    if (this->validateData(data)) {
        emit haveData(data);
        emit haveDataToSave(ID, data);
    } else {
        emit haveData(minY);
        emit haveDataToSave(ID, (minY));
    }
}

/**
 * vrati posledni prijata data
 * @brief SensorHeartRate::getLastData
 * @return posledni data
 */
float SensorHeartRate::getLastData() {
    float data = this->lastData;
    this->lastData = std::numeric_limits<float>::quiet_NaN();
    return data;
}

/**
 * Validuje prijata data a odesila je k vykresleni
 * @param data data k zvalidovani
 */
bool SensorHeartRate::validateData(float data) {
    if(data < MINIMAL_CORRECT_VALUE || data > MAXIMAL_CORRECT_VALUE){
     //  qDebug() << "false";
        return false;
    } else {
      //  qDebug() << "true";
        return true;
    }
}


SensorHeartRate::~SensorHeartRate() {

}

