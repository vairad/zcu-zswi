#include "sensorposition.h"

SensorPosition::SensorPosition() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 200;
    time = 0;
    lastY = -1;

    name = "Poloha";
}

SensorPosition::~SensorPosition() {

}

