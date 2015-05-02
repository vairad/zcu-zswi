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
    createUserPanel();
    initialWindow = new InitialWindow(dataManager, this);


    //  ArduinoMiner arduinoMiner = new ArduinoMiner();
    connectionWindow = new ConnectionWindow();
    // connect(arduinoMiner, SIGNAL(ZmenaStavu(QString)), this, SLOT(on_connection_changed());


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

    nameL->setText("");
    surnameL->setText("");
    sexL->setText("");
    ageL->setText("");
    weightL->setText("");
    heightL->setText("");
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

    toolbar->addSeparator();

    saveCB = new QCheckBox("Ukládat data");
    toolbar->addWidget(saveCB);

    this->addToolBar(toolbar);
}

/**
 * Vytvori pravy panel s informacemi o uzivateli
 * @brief MainWindow::createUserPanel
 */
void MainWindow::createUserPanel() {
    // vytvoreni panelu
    userPanel = new QWidget(ui->centralWidget);
    userPanel->setObjectName(QStringLiteral("widget_nast"));
    userPanel->setMinimumSize(QSize(200, 0));
    userPanel->setMaximumSize(QSize(200, 16777215));
    userPanel->hide();
    ui->horizontalLayout->addWidget(userPanel);

    // layout pro panel
    QVBoxLayout *verticalLayout = new QVBoxLayout(userPanel);

    // skupina pro cely panel umistena do verticalLayout
    QGroupBox *groupBox = new QGroupBox(userPanel);
    groupBox->setObjectName(QStringLiteral("groupBox"));
    groupBox->setEnabled(true);
    groupBox->setTitle("Uživatel");
    verticalLayout->addWidget(groupBox);

    // grid layout pro groupBox
    layout = new QGridLayout(groupBox);
    layout->setAlignment(Qt::AlignTop);

    addMetadataToUserPanel();
}

/**
 * Vytvori labely pro metadata v user panelu
 * @brief MainWindow::addMetadataToUserPanel
 */
void MainWindow::addMetadataToUserPanel() {
    // tucne pismo pro jmeno a prijmeni
    QFont font;
    font.setBold(true);

    // labely metadat uzivatele
    nameL = new QLabel();
    nameL->setFont(font);
    layout->addWidget(nameL, 0, 1);

    surnameL = new QLabel();
    surnameL->setFont(font);
    layout->addWidget(surnameL, 1, 1);

    sexL = new QLabel();
    layout->addWidget(sexL, 2, 1);

    ageL = new QLabel();
    layout->addWidget(ageL, 3, 1);

    weightL = new QLabel();
    layout->addWidget(weightL, 4, 1);

    heightL = new QLabel();
    layout->addWidget(heightL, 5, 1);

    // labely popisujici metadata uzivatele
    QLabel *labelNameL = new QLabel();
    labelNameL->setText("Jméno:");
    layout->addWidget(labelNameL, 0, 0);

    QLabel *labelSurnameL = new QLabel();
    labelSurnameL->setText("Příjmení:");
    layout->addWidget(labelSurnameL, 1, 0);

    QLabel *labelSexL = new QLabel();
    labelSexL->setText("Pohlaví:");
    layout->addWidget(labelSexL, 2, 0);

    QLabel *labelAgeL = new QLabel();
    labelAgeL->setText("Věk:");
    layout->addWidget(labelAgeL, 3, 0);

    QLabel *labelWeightL = new QLabel();
    labelWeightL->setText("Hmotnost:");
    layout->addWidget(labelWeightL, 4, 0);

    QLabel *labelHeightL = new QLabel();
    labelHeightL->setText("Výška:");
    layout->addWidget(labelHeightL, 5, 0);
}

/**
 * Pocatecni nastaveni senzoru
 * @brief MainWindow::setUp
 */
void MainWindow::setUp() {
    metaDialog = new MetaDialog(dataManager, sensors, NUMBER_OF_SENSORS);

    // propojeni zmen s checkboxem pro ulozeni dat v metadialogu oboustrane
    connect(saveCB, SIGNAL(clicked(bool)), metaDialog->sensorsTab->saveCB, SLOT(setChecked(bool)));
    connect(metaDialog->sensorsTab->saveCB, SIGNAL(clicked(bool)), saveCB, SLOT(setChecked(bool)));
    // propoji zmeny checkboxu s dataManagerem
    connect(saveCB, SIGNAL(clicked(bool)), this, SLOT(setSaveData(bool)));
    connect(metaDialog->sensorsTab->saveCB, SIGNAL(clicked(bool)), this, SLOT(setSaveData(bool)));

    saveCB->setChecked(dataManager->isSaveData);

    setMetadata();
    // propojeni zmeny udaju v metaDialogu s pravym sloupcem
    QObject::connect(metaDialog, SIGNAL(accepted()), this, SLOT(setMetadata()));

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->setUp();
    }

    cleanAll();

    if (!dataManager->isSetMetadata) {
        ui->actionU_ivatelsk_nastaven->setDisabled(true);
        userPanel->hide();
    }
    else {
        userPanel->show();
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
    dataManager->connectSensorToSaver();
    dataManager->draw = true;
}

/**
 * Ukonci snimani senzoru
 * @brief MainWindow::stopScanning
 */
void MainWindow::stopScanning() {
    dataManager->disconnectSensorToSaver();
    dataManager->draw = false;
}

void MainWindow::setSaveData(bool save) {
    dataManager->isSaveData = save;
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
    userPanel->show();
    nameL->setText(metaDialog->mainTab->nameE->text());
    surnameL->setText(metaDialog->mainTab->surnameE->text());

    if (metaDialog->mainTab->maleR->isChecked()) {
        sexL->setText("Muž");
    }
    else {
        sexL->setText("Žena");
    }
    ageL->setText(metaDialog->mainTab->ageE->text() + " let");
    weightL->setText(metaDialog->mainTab->weightE->text() + " kg");
    heightL->setText(metaDialog->mainTab->heightE->text() + " cm");
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

/**
 * Otevre dialog pro vyber souboru
 * @brief MainWindow::on_actionOtev_t_triggered
 */
void MainWindow::on_actionOtev_t_triggered() {
    QString file = QFileDialog::getOpenFileName(this, tr("Otevřít soubor"), QDir::homePath());
    dataManager->FILE_NAME = file;
    dataManager->loadFile();
}
