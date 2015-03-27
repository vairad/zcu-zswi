#include <QtWidgets>
#include "mainwindow.h"
#include "sensorekg.h"
#include "sensortemp.h"
#include "sensorposition.h"
#include "sensoroxy.h"
#include "sensorgsr.h"
#include "sensorheartrate.h"

/**
  Vytvori okno
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QSizePolicy sizePolicy = ui->scrollAreaWidgetContents_2->sizePolicy();

    /* vytvoreni vsech senzoru a jejich pridani do okna */
    sensors[0] = new SensorWidget(sizePolicy, ui->menuZobrazit, new SensorEKG(), ui->scrollAreaWidgetContents_2);
    ui->verticalLayout_3->addWidget(sensors[0], 0, Qt::AlignTop);
    sensors[1] = new SensorWidget(sizePolicy, ui->menuZobrazit, new SensorTemp(), ui->scrollAreaWidgetContents_2);
    ui->verticalLayout_3->addWidget(sensors[1], 0, Qt::AlignTop);
    sensors[2] = new SensorWidget(sizePolicy, ui->menuZobrazit, new SensorPosition(), ui->scrollAreaWidgetContents_2);
    ui->verticalLayout_3->addWidget(sensors[2], 0, Qt::AlignTop);
    sensors[3] = new SensorWidget(sizePolicy, ui->menuZobrazit, new SensorOxy(), ui->scrollAreaWidgetContents_2);
    ui->verticalLayout_3->addWidget(sensors[3], 0, Qt::AlignTop);
    sensors[4] = new SensorWidget(sizePolicy, ui->menuZobrazit, new SensorGSR(), ui->scrollAreaWidgetContents_2);
    ui->verticalLayout_3->addWidget(sensors[4], 0, Qt::AlignTop);
    sensors[5] = new SensorWidget(sizePolicy, ui->menuZobrazit, new SensorHeartRate(), ui->scrollAreaWidgetContents_2);
    ui->verticalLayout_3->addWidget(sensors[5], 0, Qt::AlignTop);
}

/**
 * Pocatecni nastaveni senzoru
 * @brief MainWindow::draw
 */
void MainWindow::draw() {
    sensors[0]->setUp();
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * Zavre aplikaci
 * @brief MainWindow::on_actionZav_t_triggered
 */
void MainWindow::on_actionZav_t_triggered() {
    this->close();
}

/**
 * Zobrazi informace o aplikaci
 * @brief MainWindow::on_actionO_aplikaci_triggered
 */
void MainWindow::on_actionO_aplikaci_triggered() {
    QMessageBox::about(this, tr("O aplikaci"),
             tr("Aplikace pro vizualizaci signálů z E-health. <br> Projekt Šejdrem Arduino"));
}
