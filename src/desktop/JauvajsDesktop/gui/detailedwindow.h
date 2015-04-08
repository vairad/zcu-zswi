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
    explicit DetailedWindow(IDisplayable *sensor, QWidget *parent = 0);
    void update(double value);
    void resizeEvent(QResizeEvent *e);
    void setUp();
    ~DetailedWindow();
};

#endif // DETAILEDWINDOW_H
