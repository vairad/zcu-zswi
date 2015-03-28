#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QAction>
#include <QMenu>
#include "idisplayable.h"

/**
 * Reprezentace widgetu - podokno zobrazene ve ScrollArea, obsluhuje akce uzivatele
 * @brief The SensorWidget class
 */
class SensorWidget : public QWidget {
    Q_OBJECT
public:
    explicit SensorWidget(QVBoxLayout *vLayout, QMenu *menuZobrazit, IDisplayable *sensor, QWidget *parent = 0);
    void createLayout();
    void createLeftBox();
    void createGraphicsView();
    void createAction();
    void zobrazit();
    void setUp();
    void update(double value);
    ~SensorWidget();
    QGraphicsView *graphicsView;
    QAction *action1;

signals:

public slots:
    void on_button_clicked();

private slots:
    void on_action_toggled(bool arg1);

protected:
    void resizeEvent(QResizeEvent *event);
    /** scena pro vykresleni grafu */
    QGraphicsScene *scene;

private:
    /** polozka Zobrazit hlavniho menu */
    QMenu *menuZobrazit;
    /** hlavni widget */
    QWidget *widget;
    /** tlacitko zahajeni zaznamu */
    QPushButton *button;
    /** popisek widgetu */
    QLabel *label;
    /** layout widgetu */
    QHBoxLayout *layout;
    /** senzor, ktery widget zobrazuje */
    IDisplayable *sensor;



};

#endif // SENSORWIDGET_H
