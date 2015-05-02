#ifndef IWORKING_H
#define IWORKING_H

#include <QGraphicsScene>

class IWorking : public QObject {
Q_OBJECT
public:

    /** Predavani dat senzorum */
    virtual void transmitData(float data) = 0;
    /** posledni prijata data */
    float lastData;

private:

signals:
    void haveDataToSave(int, float);

};

#endif // IWORKING_H
