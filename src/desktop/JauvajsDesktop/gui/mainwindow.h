#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/ui_mainwindow.h"
#include "gui/sensorwidget.h"
#include "gui/metadialog.h"
#include "initialwindow.h"

namespace Ui {
class MainWindow;
}

/**
 * Hlavni GUI trida
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setUp();
    /** uvodni okno */
    InitialWindow *initialWindow;
    static const int NUMBER_OF_SENSORS = 6;
    /** senzory */
    SensorWidget *sensors[NUMBER_OF_SENSORS];
    /** spravce dat */
    DataManager *dataManager;

public slots:
    void setMetadata();

private slots:
    void on_actionZav_t_triggered();
    void on_actionO_aplikaci_triggered();
    void on_actionU_ivatelsk_nastaven_triggered();

private:
    Ui::MainWindow *ui;
    MetaDialog *metaDialog;
};

#endif // MAINWINDOW_H
