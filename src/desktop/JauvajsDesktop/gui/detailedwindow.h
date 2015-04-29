#ifndef DETAILEDWINDOW_H
#define DETAILEDWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "core/idisplayable.h"
#include "gui/graphdescription.h"

/**
 * Detailne zobrazi graf zadaneho senzoru
 * @brief The DetailedWindow class
 */
class DetailedWindow : public QDialog, public GraphDescription {
    Q_OBJECT
public:
    explicit DetailedWindow(IDisplayable *sensor, QList<float> *values, QWidget *parent = 0);
    void update(double value);
    void resizeEvent(QResizeEvent *);
    void setUp();
    void repaintGraph();
    void resetGraph();
    void cleanGraph();
    ~DetailedWindow();
    /** krivka kreslena do grafu */
    QPainterPath *path;
    /** ukazatel na list hodnot v grafu */
    QList<float> *values;
    /** polozka krivky kreslena do sceny */
    QGraphicsPathItem *curve;
    /** polozka krivky z minuleho zaznamu kreslena do sceny */
    QGraphicsPathItem *curve2;
    /** zda je zapnuto prepisovani */
    bool transcription;
    /** prepisovaci index, kde je zrovna provaden */
    int transcriptionIndex;
    /** vlastni cas detailniho okna */
    double time;
};

#endif // DETAILEDWINDOW_H
