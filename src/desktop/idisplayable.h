#ifndef IDISPLAYABLE
#define IDISPLAYABLE

#include <QGraphicsScene>

/**
 * Rozhrani pripravi scenu pro SensorWidget
 * @brief The IDisplayable class
 */
class IDisplayable {
public:
    IDisplayable();
    ~IDisplayable();
    /** vrati vytvoreny graf */
    virtual QGraphicsScene getSceneGraph();
    QString getName();

    /** minimum na ose X */
    int minX;
    /** maximum na ose X */
    int maxX;
    /** minimum na ose Y */
    int minY;
    /** maximum na ose Y */
    int maxY;
    /** cas (osa X) */
    int time;
    /** posledni hodnota Y */
    int lastY;

protected:
    /** nazev senzoru */
    QString name;
};

#endif // IDISPLAYABLE

