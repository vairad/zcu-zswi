#ifndef GRAPHDESCRIPTION_H
#define GRAPHDESCRIPTION_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "core/idisplayable.h"

/**
 * Zajistuje vykresleni popisu a mrizky grafu
 * @brief The GraphDescription class
 */
class GraphDescription {
public:
    GraphDescription();
    void drawNumbers();
    void drawVerticalLines();
    void drawHorizontalLines();
    ~GraphDescription();

protected:
    /** senzor, ktery widget zobrazuje */
    IDisplayable *sensor;
    /** komponenta pro zobrazeni sceny grafu */
    QGraphicsView *graphicsView;
    /** scena pro vykresleni grafu */
    QGraphicsScene *scene;
    /** existence popisu */
    bool itemsExist;
    /** popis nejvyssi hodnoty Y */
    QGraphicsTextItem *textMaxY;
    /** popis nejmensi hodnoty Y */
    QGraphicsTextItem *textMinY;
    /** popis nejvyssi hodnoty X */
    QGraphicsTextItem *textMaxX;
    /** popis nejmensi hodnoty X */
    QGraphicsTextItem *textMinX;
    /** osa x */
    QGraphicsLineItem *horizontalLine;
    /** osa y */
    QGraphicsLineItem *verticalLine;
    /** leve odsazeni grafu */
    static const int LEFT_OFFSET = 20;
    /** spodni odsazeni grafu */
    static const int BOTTOM_OFFSET = 15;

    /** interval vertikalnich car */
    int verticalLinesInterval;
    /** interval vertikalnich tucnych car */
    int verticalLinesBoldInterval;
    /** sirka grafu */
    static const int WIDTH = 1500;
    /** minimalni pocet horizontalnich car v grafu */
    int minNumberOfHorizontalLines;
};

#endif // GRAPHDESCRIPTION_H
