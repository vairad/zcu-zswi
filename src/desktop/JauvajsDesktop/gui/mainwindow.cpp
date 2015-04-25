#include <QtWidgets>
#include "gui/mainwindow.h"
#include "core/sensorekg.h"
#include "core/sensortemp.h"
#include "core/sensorposition.h"
#include "core/sensoroxy.h"
#include "core/sensorgsr.h"
#include "core/sensorheartrate.h"
#include "core/datamanager.h"
#include "core/iworking.h"
#include <QDebug>

/**
  Vytvori okno
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(DataManager *manager, GUILoop *loop, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), dataManager(manager) {
    this->loop = loop;
    ui->setupUi(this);
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
   // dataManager = new DataManager();
   // dataManager = manager;
    initialWindow = new InitialWindow(dataManager, this);

    SensorEKG *ekg = new SensorEKG();
    dataManager->setListenerEKG(ekg);   

    /* vytvoreni vsech senzoru a jejich pridani do okna */
    sensors[0] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, ekg, loop, ui->scrollAreaWidgetContents_2);
    sensors[1] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, new SensorTemp(), loop, ui->scrollAreaWidgetContents_2);
    sensors[2] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, new SensorPosition(), loop, ui->scrollAreaWidgetContents_2);
    sensors[3] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, new SensorOxy(), loop, ui->scrollAreaWidgetContents_2);
    sensors[4] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, new SensorGSR(), loop, ui->scrollAreaWidgetContents_2);
    sensors[5] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, new SensorHeartRate(), loop, ui->scrollAreaWidgetContents_2);

    //loop->sensorEKG = sensors[0];
    qDebug() << "loop < sensorEKG";
    connect(loop, SIGNAL(updateSignal(double)), sensors[0], SLOT(update(double)));
    qDebug() << "connect";

    ui->label->setText("");
    ui->label_2->setText("");
}

/**
 * Pocatecni nastaveni senzoru
 * @brief MainWindow::setUp
 */
void MainWindow::setUp() {
    metaDialog = new MetaDialog(dataManager, sensors, NUMBER_OF_SENSORS);
    setMetadata();
    // propojeni zmeny udaju v metaDialogu s pravym sloupcem
    QObject::connect(metaDialog, SIGNAL(accepted()), this, SLOT(setMetadata()));

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->setUp();
    }

    if (!dataManager->isSetMetadata) {
        ui->actionU_ivatelsk_nastaven->setDisabled(true);
    }

}

/**
 * Odstraneni vykreslene krivky a resetovani hodnot v grafech vsech senzoru
 * @brief MainWindow::cleanAll
 */
void MainWindow::cleanAll() {
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->cleanGraph();
    }
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

/**
 * Zobrazi dialog nastaveni metadat
 * @brief MainWindow::on_actionU_ivatelsk_nastaven_triggered
 */
void MainWindow::on_actionU_ivatelsk_nastaven_triggered() {
    metaDialog->show();
}

/**
 * Zmeni data v pravem sloupci na aktualni metadata
 * @brief MainWindow::setMetaData
 */
void MainWindow::setMetadata() {
    ui->actionU_ivatelsk_nastaven->setDisabled(false);
    ui->label->setText(metaDialog->mainTab->nameE->text());
    ui->label_2->setText(metaDialog->mainTab->surnameE->text());
}

/**
 * Zobrazi uvodni okno ke zmene uzivatele
 * @brief MainWindow::on_actionZm_na_u_ivatele_triggered
 */
void MainWindow::on_actionZm_na_u_ivatele_triggered() {
    initialWindow->show();
}

/**
 * Volani cleanAll pro vycisteni grafi vsech sensoru
 * @brief MainWindow::on_actionVy_istit_v_e_triggered
 */
void MainWindow::on_actionVy_istit_v_e_triggered() {
    cleanAll();
}
