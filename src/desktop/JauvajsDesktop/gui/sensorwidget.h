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
#include <QGraphicsLineItem>
#include "core/idisplayable.h"
#include "gui/detailedwindow.h"
#include "gui/graphdescription.h"

/**
 * Reprezentace widgetu - podokno zobrazene ve ScrollArea, obsluhuje akce uzivatele
 * @brief The SensorWidget class
 */
class SensorWidget : public QWidget, public GraphDescription {
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
    IDisplayable *getSensor();
    ~SensorWidget();
    QAction *action1;

signals:

public slots:
    void on_button_clicked();
    void on_action_toggled(bool arg1);

signals:
    void visible(bool arg1);

protected:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

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
    /** detailni okno senzoru */
    DetailedWindow *detailedWindow;
};

#endif // SENSORWIDGET_H
