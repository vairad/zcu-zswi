#include "sensorheartrate.h"

SensorHeartRate::SensorHeartRate() {
    minY = -1;
    maxY = 1;
    minX = 0;
    maxX = 200;
    time = 0;
    lastY = -1;

    name = "Puls";
}

SensorHeartRate::~SensorHeartRate() {

}

