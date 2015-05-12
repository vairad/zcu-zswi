#include <QtWidgets>
#include <QDir>
#include <QSerialPortInfo>

#include "gui/mainwindow.h"
#include "gui/helpwindow.h"
#include "core/sensorekg.h"
#include "core/sensortemp.h"
#include "core/sensorairflow.h"
#include "core/sensoroxy.h"
#include "core/sensorgsr.h"
#include "core/sensorheartrate.h"
#include "core/datamanager.h"
#include "core/iworking.h"
#include "core/arduinominer.h"

/**
  Vytvori okno
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(DataManager *manager, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), dataManager(manager) {
    ui->setupUi(this);
    ui->verticalLayout_3->setAlignment(Qt::AlignTop);
    this->showMaximized();
    this->setWindowTitle("Šejdrem sensor");

    createMenuBar();
    createToolBar();
    createUserPanel();
    initialWindow = new InitialWindow(dataManager, this);

    arduinoMiner = manager->arduino;
    //connectionWindow = new ConnectionWindow(arduinoMiner, this);
    connect(arduinoMiner, SIGNAL(statusChanged(QString, QString)), this, SLOT(on_indicatorChanged(QString, QString)));
    connect(manager, SIGNAL(dataStatusChanged(QString, QString)), this, SLOT(on_indicatorDataChanged(QString, QString)));
    connect(manager, SIGNAL(checkPort()), this, SLOT(on_checkPort()));

    // Vytvoreni senzoru
    SensorEKG *ekg = new SensorEKG();
    SensorTemp *temp = new SensorTemp();
    SensorAirFlow *pos = new SensorAirFlow();
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
    sensors[0] = new SensorWidget(ui->verticalLayout_3, menuDisplay, ekg, ui->scrollAreaWidgetContents_2);
    sensors[1] = new SensorWidget(ui->verticalLayout_3, menuDisplay, temp, ui->scrollAreaWidgetContents_2);
    sensors[2] = new SensorWidget(ui->verticalLayout_3, menuDisplay, pos, ui->scrollAreaWidgetContents_2);
    sensors[3] = new SensorWidget(ui->verticalLayout_3, menuDisplay, oxy, ui->scrollAreaWidgetContents_2);
    sensors[4] = new SensorWidget(ui->verticalLayout_3, menuDisplay, gsr, ui->scrollAreaWidgetContents_2);
    sensors[5] = new SensorWidget(ui->verticalLayout_3, menuDisplay, hr, ui->scrollAreaWidgetContents_2);

    nameL->setText("");
    surnameL->setText("");
    sexL->setText("");
    ageL->setText("");
    weightL->setText("");
    heightL->setText("");
}

/**
 * Vytvori menu aplikace
 * @brief MainWindow::createMenuBar
 */
void MainWindow::createMenuBar() {
    QMenuBar *menuBar;
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 756, 21));

    // polozka Soubor
    QMenu *menuFile;
    menuFile = new QMenu(menuBar);
    menuFile->setTitle("Soubor");
    menuBar->addAction(menuFile->menuAction());

    // polozka Upravy
    QMenu *menuEdit;
    menuEdit = new QMenu(menuBar);
    menuEdit->setTitle("Úpravy");
    menuBar->addAction(menuEdit->menuAction());

    // polozka Zobrazit
    menuDisplay = new QMenu(menuBar);
    menuDisplay->setTitle("Zobrazit");
    menuBar->addAction(menuDisplay->menuAction());

    // polozka Nastaveni
    QMenu *menuSettings;
    menuSettings = new QMenu(menuBar);
    menuSettings->setTitle("Nastavení");
    menuBar->addAction(menuSettings->menuAction());

    // polozka Napoveda
    QMenu *menuHelp;
    menuHelp = new QMenu(menuBar);
    menuHelp->setTitle("Nápověda");
    menuBar->addAction(menuHelp->menuAction());


    QAction *actionOpen;
    actionOpen = new QAction(this);
    actionOpen->setText("Otevřít");
    actionOpen->setShortcut(Qt::Key_O | Qt::CTRL);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openFileChooser()));
    menuFile->addAction(actionOpen);

    QAction *actionClose;
    actionClose = new QAction(this);
    actionClose->setText("Zavřít");
    actionClose->setShortcut(Qt::Key_Q | Qt::CTRL);
    connect(actionClose, SIGNAL(triggered()), this, SLOT(close()));
    menuFile->addAction(actionClose);

    QAction *actionCleanAll;
    actionCleanAll = new QAction(this);
    actionCleanAll->setText("Vyčistit vše");
    actionCleanAll->setShortcut(Qt::Key_Delete);
    connect(actionCleanAll, SIGNAL(triggered()), this, SLOT(cleanAll()));
    menuEdit->addAction(actionCleanAll);

    actionUserSettings = new QAction(this);
    actionUserSettings->setText("Uživatelské nastavení");
    actionUserSettings->setShortcut(Qt::Key_P | Qt::ALT);
    connect(actionUserSettings, SIGNAL(triggered()), this, SLOT(openUserSettings()));
    menuSettings->addAction(actionUserSettings);

    actionChangeUser = new QAction(this);
    actionChangeUser->setText("Změna uživatele");
    connect(actionChangeUser, SIGNAL(triggered()), this, SLOT(openInitialWindow()));
    menuSettings->addAction(actionChangeUser);

    QAction *actionHelp;
    actionHelp = new QAction(this);
    actionHelp->setText("Nápověda k aplikaci");
    actionHelp->setShortcut(Qt::Key_F1);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(openHelp()));
    menuHelp->addAction(actionHelp);

    QAction *actionAboutApp;
    actionAboutApp = new QAction(this);
    actionAboutApp->setText("O aplikaci");
    connect(actionAboutApp, SIGNAL(triggered()), this, SLOT(aboutApplication()));
    menuHelp->addAction(actionAboutApp);

    this->setMenuBar(menuBar);
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
    QPixmap start("images/start.png");
    startA->setIcon(QIcon(start));
    connect(startA, SIGNAL(triggered()), this, SLOT(startScanning()));
    toolbar->addAction(startA);

    // akce pro ukonceni snimani
    QAction *stopA = new QAction(this);
    stopA->setObjectName(QStringLiteral("action"));
    stopA->setText("Ukončit snímání");
    QPixmap stop("images/stop.png");
    stopA->setIcon(QIcon(stop));
    connect(stopA, SIGNAL(triggered()), this, SLOT(stopScanning()));
    toolbar->addAction(stopA);

    // akce pro vycisteni vsech senzoru
    QAction *cleanAllA = new QAction(this);
    cleanAllA->setObjectName(QStringLiteral("action"));
    cleanAllA->setText("Vyčistit vše");
    QPixmap cleanAll("images/clean.png");
    cleanAllA->setIcon(QIcon(cleanAll));
    connect(cleanAllA, SIGNAL(triggered()), this, SLOT(cleanAll()));
    toolbar->addAction(cleanAllA);

    toolbar->addSeparator();

    saveCB = new QCheckBox("Ukládat data");
    toolbar->addWidget(saveCB);

    toolbar->addSeparator();

    // akce pro obnoveni portu
    QAction *refreshNow = new QAction(this);
    refreshNow->setObjectName(QStringLiteral("action"));
    refreshNow->setText("Obnovit dostupné porty");
    QPixmap refre("refresh.png");
    refreshNow->setIcon(QIcon(refre));
    connect(refreshNow, SIGNAL(triggered()), this, SLOT(refeshComboBox()));
    toolbar->addAction(refreshNow);

    // combo box na vyber portu
    comboBox = new QComboBox();
    comboBox->setMaximumWidth(200);
    this->refeshComboBox();
    toolbar->addWidget(comboBox);

    // tlacitko pro potvzeni vybraneho portu
    QPushButton *choosePort = new QPushButton(this);
    choosePort->setText("Zvolit port");
    connect(choosePort, SIGNAL(clicked()), this, SLOT(portChoosed()));
    toolbar->addWidget(choosePort);
    this->addToolBar(toolbar);

    QLabel *labelStatusDevice = new QLabel();
    labelStatusDevice->setText("Stav zařízení: ");
    labelStatusDevice->setStyleSheet("QLabel {margin-left:10px; color: gray; font-size: 15px;}");
    toolbar->addWidget(labelStatusDevice);

    // label zobrazujici stav spojeni
    labelStatConn = new QLabel();
    labelStatConn->setText("Nepřipojeno");
    labelStatConn->setMargin(10);
    labelStatConn->setStyleSheet("QLabel { color: red; font-size: 15px;}");
    toolbar->addWidget(labelStatConn);

    QLabel *labelDataStatus = new QLabel();
    labelDataStatus->setText("Stav příchozích dat: ");
    labelDataStatus->setStyleSheet("QLabel {margin-left:10px; color: gray; font-size: 15px;}");
    toolbar->addWidget(labelDataStatus);

    // label znazornujici stav prichozich dat
    labelArduData = new QLabel();
    labelArduData->setText("Žádná data");
    labelArduData->setMargin(10);
    labelArduData->setStyleSheet("QLabel { color: red; font-size: 15px;}");
    toolbar->addWidget(labelArduData);
}

/**
 * Vypise dostupne seriove porty do combo boxu
 * @brief MainWindow::refeshComboBox
 */
void MainWindow::refeshComboBox() {
    comboBox->clear();
    comboBox->addItem("-- Zvolte port --");
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(comboBox->model());
    QModelIndex firstIndex = model->index(0, comboBox->modelColumn(), comboBox->rootModelIndex());
    QStandardItem* firstItem = model->itemFromIndex(firstIndex);
    firstItem->setSelectable(false);

    QList<QSerialPortInfo> listOfPorts = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo port, listOfPorts) {
        // nazev portu + nazev pripojeneho zarizeni
        comboBox->addItem(port.portName()+ " ["+port.description()+"] ");
    }
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
    groupBox = new QGroupBox(userPanel);
    groupBox->setObjectName(QStringLiteral("groupBox"));
    groupBox->setEnabled(true);
    groupBox->setTitle("Uživatel");
    verticalLayout->addWidget(groupBox);

    groupBox->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(groupBox, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(userPanelContextMenu(const QPoint &)));

    // grid layout pro groupBox
    layout = new QGridLayout(groupBox);
    layout->setAlignment(Qt::AlignTop);

    addMetadataToUserPanel();

    // label popisujici ulozena data
    QLabel *labelListOfFiles = new QLabel();
    labelListOfFiles->setText("Uložená data tohoto uživatele: ");
    layout->addWidget(labelListOfFiles, 7, 0, 1, 2);

    // widget pro ulozena data
    listWidget = new QListWidget();
    listWidget->setCursor(Qt::PointingHandCursor);

    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedLoadFile(QListWidgetItem *)));

    layout->addWidget(listWidget, 8, 0, 1, 2);
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

    QFrame* myFrame = new QFrame();
    myFrame->setFrameShape(QFrame::HLine);

    layout->addWidget(myFrame, 6, 0, 1, 2);
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

    // propojeni zmeny udaju v metaDialogu s pravym sloupcem
    QObject::connect(metaDialog, SIGNAL(accepted()), this, SLOT(setMetadata()));

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->setUp();
    }

    cleanAll();

    if (dataManager->isSetMetadata) {
        setMetadata();
    }
    else {
        actionUserSettings->setDisabled(true);
        userPanel->hide();
        saveCB->setDisabled(true);
    }
}

/**
 * Prida data do listWidgetu v pravem sloupci
 * @brief MainWindow::addItemsToListWidget
 */
void MainWindow::addItemsToListWidget() {
    QStringList list = dataManager->listOfFiles();
    listWidget->clear();

    if (!list.isEmpty()) {
        listWidget->setEnabled(true);
        // reverze listu
        QStringList listR;
        listR.reserve(list.size());
        std::reverse_copy(list.begin(), list.end(), std::back_inserter(listR));
        list = listR;

        foreach (QString s, list) {
            QFileInfo fileInfo(s);
            QDateTime dateTime = QDateTime::fromString(fileInfo.completeBaseName(), "yyyyMMddhhmmss");

            QListWidgetItem *item = new QListWidgetItem(dateTime.toString("d. M. yyyy, h:m:s"));
            listWidget->addItem(item);
        }
    }
    else {
        listWidget->setEnabled(false);
    }
}

/**
 * Zahaji snimani senzoru
 * @brief MainWindow::startScanning
 */
void MainWindow::startScanning() {
    dataManager->connectSensorToSaver();
    dataManager->draw = true;
    dataManager->start();
    saveCB->setDisabled(true);
}

/**
 * Ukonci snimani senzoru
 * @brief MainWindow::stopScanning
 */
void MainWindow::stopScanning() {
    dataManager->disconnectSensorToSaver();
    dataManager->draw = false;
    dataManager->arduino->closeSerial();

    addItemsToListWidget();
    if (dataManager->isSetMetadata) {
        saveCB->setDisabled(false);
    }
}

/**
 * Zmeni data v pravem sloupci na aktualni metadata
 * @brief MainWindow::setMetaData
 */
void MainWindow::setMetadata() {
    actionUserSettings->setDisabled(false);
    userPanel->show();
    saveCB->setDisabled(false);
    addItemsToListWidget();
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
 * Nacteni souboru po kliknuti na polozku v seznamu v pravem sloupci
 * @brief MainWindow::itemClickedLoadFile
 * @param item
 */
void MainWindow::itemClickedLoadFile(QListWidgetItem *item) {
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->prepareToLoadData();
    }
    QDateTime dateTime = QDateTime::fromString(item->text(), "d. M. yyyy, h:m:s");
    QString filename = dateTime.toString("yyyyMMddhhmmss") + ".csv";

    dataManager->loadDataFromFile(filename, false);

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->cancelLoadData();
    }
}

/**
 * Nastavi ukladani dat
 * @brief MainWindow::setSaveData
 * @param save
 */
void MainWindow::setSaveData(bool save) {
    dataManager->isSaveData = save;
}

/**
 * Otevre dialog pro vyber souboru
 * @brief MainWindow::openFileChooser
 */
void MainWindow::openFileChooser() {
    QString file = QFileDialog::getOpenFileName(this, tr("Otevřít soubor"), QDir::homePath());
    //dataManager->loadFile(file);

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->prepareToLoadData();
    }

    dataManager->loadDataFromFile(file, true);

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
       sensors[i]->cancelLoadData();
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
 * Zobrazi dialog nastaveni metadat
 * @brief MainWindow::openUserSettings
 */
void MainWindow::openUserSettings() {
    metaDialog->show();
}

/**
 * Zobrazi uvodni okno ke zmene uzivatele
 * @brief MainWindow::openInitialWindow
 */
void MainWindow::openInitialWindow() {
    initialWindow->show();
}

/**
 * Zobrazi okno s napovedou k aplikaci
 * @brief MainWindow::openHelp
 */
void MainWindow::openHelp() {
    new HelpWindow();
}

/**
 * Zobrazi informace o aplikaci
 * @brief MainWindow::aboutApplication
 */
void MainWindow::aboutApplication() {
    QMessageBox::about(this, tr("O aplikaci"),
             tr("Aplikace pro vizualizaci signálů z E-health. <br> Projekt Šejdrem Arduino"));
}

/**
 * Kontextove menu pro pravy sloupec
 * @brief MainWindow::userPanelContextMenu
 * @param pos
 */
void MainWindow::userPanelContextMenu(const QPoint &pos) {
    QMenu contextMenu(groupBox);
    contextMenu.addAction(actionUserSettings);
    contextMenu.addAction(actionChangeUser);

    contextMenu.exec(groupBox->mapToGlobal(pos));
}

/**
 * Inicializuje spojeni na vybranem portu
 * @brief MainWindow::on_portChoosed
 */
void MainWindow::portChoosed() {
    qDebug() << "Vybral jsi port";

    this->choosedPort = comboBox->currentText();
    QStringList portInfo = this->choosedPort.split(' ');
    QString portNumber = portInfo[0];
    if(portNumber != NULL) { // pokud je vybrany nejaky port
         qDebug() << "choosed" << portNumber;
        dataManager->arduino->portNumber = portNumber;
        dataManager->arduino->init(portNumber);
    }

    QTime timer;
    timer.start();
    while(timer.elapsed() < 500){
        //loop for 500ms
    }
    startScanning();
}

/**
 * Indikator zobrazujici stav spojeni
 * @brief MainWindow::on_portChoosed
 */
void MainWindow::on_indicatorChanged(QString status, QString color) {
    labelStatConn->setStyleSheet("QLabel { color : "+color+"; font-size: 15px;}");
    labelStatConn->setText(status);
    this->refeshComboBox();
}

/**
 * Indikator zobrazujici stav prichozich dat
 * @brief MainWindow::on_portChoosed
 */
void MainWindow::on_indicatorDataChanged(QString status, QString color) {
    labelArduData->setStyleSheet("QLabel { color : "+color+"; font-size: 15px;}");
    labelArduData->setText(status);
}

/**
 * Volani arduinomineru pro kontrolu komunikacniho oprtu
 * @brief MainWindow::on_checkPort
 */
void MainWindow::on_checkPort() {
    arduinoMiner->checkYourCOM();
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

MainWindow::~MainWindow() {
    delete ui;
}


