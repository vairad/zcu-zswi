#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include "core/idisplayable.h"

#include "gui/detailedwindow.h"
#include "gui/graphdescription.h"
#include "gui/guiloop.h"


#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QAction>
#include <QMenu>
#include <QGraphicsLineItem>


/**
 * Reprezentace widgetu - podokno zobrazene ve ScrollArea, obsluhuje akce uzivatele
 * @brief The SensorWidget class
 */
class SensorWidget : public QWidget, public GraphDescription {
    Q_OBJECT
public:
    explicit SensorWidget(QVBoxLayout *vLayout, QMenu *menuZobrazit, IDisplayable *sensor, DataManager *manager, QWidget *parent = 0);
    void createLayout();
    void createLeftBox();
    void createGraphicsView();
    void createAction();
    void zobrazit();
    void setUp();
   // void update(double value);
    void repaintGraph();
    void resetGraph();
    void cleanGraph();
    IDisplayable *getSensor();
    ~SensorWidget();
    QAction *action1;
    /** nastaveni viditelnosti widgetu */
    bool isVisible;

    GUILoop *loop;
    DataManager *manager;

signals:

public slots:
    //void on_button_clicked();
    void on_button2_clicked();
    void on_action_toggled(bool arg1);
    void update2(float value);

signals:
    void visible(bool arg1);

protected:
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);

private:
    /** polozka Zobrazit hlavniho menu */
    QMenu *menuZobrazit;
    /** hlavni widget */
    QWidget *widget;
    /** tlacitko zahajeni zaznamu */
    QPushButton *button;
    /** tlacitko vycisteni sceny */
    QPushButton *button2;
    /** popisek widgetu */
    QLabel *label;
    /** layout widgetu */
    QHBoxLayout *layout;
    /** detailni okno senzoru */
    DetailedWindow *detailedWindow;
    /** krivka kreslena do grafu */
    QPainterPath *path;
    /** list hodnot v grafu */
    QList<double> values;
    /** polozka krivky kreslena do sceny */
    QGraphicsPathItem *curve;
    /** polozka krivky z minuleho zaznamu kreslena do sceny */
    QGraphicsPathItem *curve2;
    /** zda je zapnuto prepisovani */
    bool transcription;
    /** prepisovaci index, kde je zrovna provaden */
    int transcriptionIndex;   
};

#endif // SENSORWIDGET_H
