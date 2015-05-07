#ifndef POSITIONSENSOR_H
#define POSITIONSENSOR_H

#include "core/iworking.h"
#include "core/idisplayable.h"

class SensorAirFlow : public IDisplayable, public IWorking {
   static const int ID = 2;
   const float MINIMAL_CORRECT_VALUE = 0.0;
   const float MAXIMAL_CORRECT_VALUE = 512.0;

    /*  1 == Supine position / na zádech
        2 == Left lateral decubitus / leží na levém boku
        3 == Rigth lateral decubitus / leží na pravém boku
        4 == Prone position /leží na břiše
        5 == Stand or sit position / stojí nebo sedí
    */
    const int POSITION_SUPINE = 1; /*na zádech*/
    const int POSITION_LEFT = 2; /*na levém boku*/
    const int POSITION_RIGHT = 3; /*na pravém boku*/
    const int POSITION_PRONE = 4; /* na břiše*/
    const int POSITION_STAND = 5; /* stojí / sedí */

    bool validateData(int data);
public:
    SensorAirFlow();
    QGraphicsScene* getSceneGraph();
    void transmitData(float data);
    float getLastData();

    ~SensorAirFlow();

};

#endif // POSITIONSENSOR_H
