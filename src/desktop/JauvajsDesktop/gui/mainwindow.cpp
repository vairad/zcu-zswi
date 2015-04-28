#include <QtWidgets>
#include <QDir>

#include "gui/mainwindow.h"
#include "core/sensorekg.h"
#include "core/sensortemp.h"
#include "core/sensorposition.h"
#include "core/sensoroxy.h"
#include "core/sensorgsr.h"
#include "core/sensorheartrate.h"
#include "core/datamanager.h"
#include "core/iworking.h"

/**
  Vytvori okno
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(DataManager *manager, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), dataManager(manager) {
    ui->setupUi(this);
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    this->showMaximized();

    createToolBar();
    initialWindow = new InitialWindow(dataManager, this);

    // Vytvoreni senzoru
    SensorEKG *ekg = new SensorEKG();
    SensorTemp *temp = new SensorTemp();
    SensorPosition *pos = new SensorPosition();
    SensorOxy *oxy = new SensorOxy();
    SensorGSR *gsr = new SensorGSR();
    SensorHeartRate *hr = new SensorHeartRate();

    // Nastaveni listeneru
    dataManager->setListenerEKG(ekg);
    dataManager->setListenerTemp(temp);
    dataManager->setListenerOxy(oxy);
    dataManager->setListenerPosition(pos);
    dataManager->setListenerGSR(gsr);
    dataManager->setListenerHearthRate(hr);

    /* vytvoreni vsech senzoru a jejich pridani do okna */
    sensors[0] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, ekg, ui->scrollAreaWidgetContents_2);
    sensors[1] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, temp, ui->scrollAreaWidgetContents_2);
    sensors[2] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, pos, ui->scrollAreaWidgetContents_2);
    sensors[3] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, oxy, ui->scrollAreaWidgetContents_2);
    sensors[4] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, gsr, ui->scrollAreaWidgetContents_2);
    sensors[5] = new SensorWidget(ui->verticalLayout_3, ui->menuZobrazit, hr, ui->scrollAreaWidgetContents_2);

    ui->label->setText("");
    ui->label_2->setText("");
}

/**
 * Vytvori listu nastroju
 * @brief MainWindow::createToolBar
 */
void MainWindow::createToolBar() {
    QToolBar *toolbar = addToolBar("main toolbar");

    // akce pro zahajeni snimani
    QAction *startA = new QAction(this);
    startA->setObjectName(QStringLiteral("action"));
    startA->setText("Zahájit snímání");
    QPixmap start("start.png");
    startA->setIcon(QIcon(start));
    connect(startA, SIGNAL(triggered()), this, SLOT(startScanning()));
    toolbar->addAction(startA);

    // akce pro ukonceni snimani
    QAction *stopA = new QAction(this);
    stopA->setObjectName(QStringLiteral("action"));
    stopA->setText("Ukončit snímání");
    QPixmap stop("stop.png");
    stopA->setIcon(QIcon(stop));
    connect(stopA, SIGNAL(triggered()), this, SLOT(stopScanning()));
    toolbar->addAction(stopA);

    // akce pro vycisteni vsech senzoru
    QAction *cleanAllA = new QAction(this);
    cleanAllA->setObjectName(QStringLiteral("action"));
    cleanAllA->setText("Vyčistit vše");
    QPixmap cleanAll("clean.png");
    cleanAllA->setIcon(QIcon(cleanAll));
    connect(cleanAllA, SIGNAL(triggered()), this, SLOT(cleanAll()));
    toolbar->addAction(cleanAllA);

    this->addToolBar(toolbar);
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
        ui->widget_nast->hide();
    }
    else {
        ui->widget_nast->show();
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

/**
 * Zahaji snimani senzoru
 * @brief MainWindow::startScanning
 */
void MainWindow::startScanning() {
    dataManager->draw = true;
}

/**
 * Ukonci snimani senzoru
 * @brief MainWindow::stopScanning
 */
void MainWindow::stopScanning() {
    dataManager->draw = false;
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

/**
 * Dotaz pred zavrenim aplikace
 * @brief MainWindow::closeEvent
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event) {
    int reply = QMessageBox::question(this, "Zavřít", "Opravdu chcete ukončit aplikaci?", "Ano", "Ne");
    if (reply == 0) {
        QApplication::closeAllWindows();
        event->accept();
    } else {
        event->ignore();
    }
}
