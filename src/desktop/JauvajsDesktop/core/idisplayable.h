#ifndef IDISPLAYABLE
#define IDISPLAYABLE

#include <QGraphicsScene>
#include <QObject>

/**
 * Rozhrani pripravi scenu pro SensorWidget
 * @brief The IDisplayable class
 */
class IDisplayable : public QObject {
Q_OBJECT
public:
    IDisplayable();
    ~IDisplayable();

    /** vrati vytvoreny graf */
    virtual QGraphicsScene* getSceneGraph() = 0;
    /** vrati posledni prijata data */
    virtual float getLastData() = 0;

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
    /** true pokud je senzor analyzovatelny */
    bool isAnalysable;
    /** id senzoru */
    int ID;

protected:
    /** nazev senzoru */
    QString name;

signals:
    void haveData(float);
    //void notHaveData();

};

#endif // IDISPLAYABLE

