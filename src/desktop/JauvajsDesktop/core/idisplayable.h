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
    virtual QGraphicsScene* getSceneGraph() = 0;

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
    double time;
    /** cas, po kterem prichazi hodnoty z Arduina */
    double timeInterval;
    /** jednotka zobrazovane veliciny na ose Y */
    QString unit;

protected:
    /** nazev senzoru */
    QString name;
};

#endif // IDISPLAYABLE

