#ifndef IWORKING_H
#define IWORKING_H

#include <QGraphicsScene>

class IWorking
{
public:
    IWorking();
    ~IWorking();

    /** Predavani dat senzorum */
    virtual void transmitData(float data) = 0;

private:

};

#endif // IWORKING_H
