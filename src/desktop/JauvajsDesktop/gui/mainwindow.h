#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gui/ui_mainwindow.h"
#include "gui/guiloop.h"
#include "gui/sensorwidget.h"
#include "gui/metadialog.h"
#include "gui/initialwindow.h"
#include <QMainWindow>

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
    explicit MainWindow(DataManager *manager, QWidget *parent = 0);
    ~MainWindow();
    void createToolBar();
    void setUp();
    void closeEvent(QCloseEvent *event);
    /** uvodni okno */
    InitialWindow *initialWindow;
    static const int NUMBER_OF_SENSORS = 6;
    /** senzory */
    SensorWidget *sensors[NUMBER_OF_SENSORS];
    /** spravce dat */
    DataManager *dataManager;
    /** dialog metadat */
    MetaDialog *metaDialog;

public slots:
    void setMetadata();

private slots:
    void on_actionZav_t_triggered();
    void on_actionO_aplikaci_triggered();
    void on_actionU_ivatelsk_nastaven_triggered();
    void on_actionZm_na_u_ivatele_triggered();
    void on_actionVy_istit_v_e_triggered();
    void startScanning();
    void stopScanning();
    void cleanAll();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
