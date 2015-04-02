#ifndef DETAILEDWINDOW_H
#define DETAILEDWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "core/idisplayable.h"

/**
 * Detailne zobrazi graf zadaneho senzoru
 * @brief The DetailedWindow class
 */
class DetailedWindow : public QDialog {
    Q_OBJECT
public:
    explicit DetailedWindow(IDisplayable *sensor, QWidget *parent = 0);
    void update(double value);
    void resizeEvent(QResizeEvent *e);
    void drawNumbers();
    void setUp();
    ~DetailedWindow();

private:
    /** senzor, ktery widget zobrazuje */
    IDisplayable *sensor;
    /** komponenta pro kresleni sceny */
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
};

#endif // DETAILEDWINDOW_H
