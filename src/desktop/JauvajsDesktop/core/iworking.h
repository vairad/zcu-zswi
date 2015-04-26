#ifndef IWORKING_H
#define IWORKING_H

#include <QGraphicsScene>

class IWorking
{
public:

    /** Predavani dat senzorum */
    virtual void transmitData(float data) = 0;
    /** posledni prijata data */
    float lastData;

private:

};

#endif // IWORKING_H
