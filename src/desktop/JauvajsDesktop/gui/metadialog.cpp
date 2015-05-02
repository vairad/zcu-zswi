#include "gui/metadialog.h"

/**
 * Vytvori dialog umoznujici nastaveni meta dat
 * @brief MetaDialog::MetaDialog
 * @param sensors widgety senzoru
 * @param numberOfSensors pocet senzoru
 * @param parent
 */
MetaDialog::MetaDialog(DataManager *dataManager, SensorWidget *sensors[], int numberOfSensors, QWidget *parent) : QDialog(parent), dataManager(dataManager) {
    tabWidget = new QTabWidget;
    mainTab = new MainTab(dataManager);
    sensorsTab = new SensorsTab(sensors, numberOfSensors, sensorCB, dataManager);
    tabWidget->addTab(mainTab, tr("Hlavní"));
    tabWidget->addTab(sensorsTab, tr("Senzory"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    // kontrola vstupnich dat
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(checkingInputs()));
    // ulozeni metadat do Data manageru
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(updateMetadata()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Nastavení"));
}

/**
 * Kontrola vstupnich dat od uzivatele
 * @brief MetaDialog::checkingInputs
 */
void MetaDialog::checkingInputs() {
    isValidInputs = true;

    // overeni, zda neni prazdne pole uzivatelske jmeno
    if (!QString::compare(mainTab->usernameE->text(), "")) {
        this->show();
        QMessageBox messageBox;
        messageBox.critical(0,"Chyba", "Uživatelské jméno nesmí být prázdné!");
        isValidInputs = false;
    }
    // overeni, zda upravene uzivatelske jmeno (odlisnost v dataManageru od QLineEdit) neni jiz v datove slozce
    else if (QString::compare(mainTab->usernameE->text(), dataManager->username)) {
        QDir dir(dataManager->FOLDER_NAME + "/" + mainTab->usernameE->text());
        if (dir.exists()) {
            this->show();
            QMessageBox messageBox;
            messageBox.critical(0,"Chyba", tr("Zvolené uživatelské jméno už existuje!<br>Zvolte prosím jiné, aby nedošlo k přepsání dat."));
            isValidInputs = false;
        }
    }
}

/**
 * Aktualizace dat v data manageru
 * @brief MetaDialog::updateMetadata
 */
void MetaDialog::updateMetadata() {
    if (isValidInputs) {
        for (int i = 0; i < dataManager->NUMBER_OF_SENSORS; i++) {
            dataManager->sensors[i] = sensorCB[i]->isChecked();
        }

        dataManager->name[0] = mainTab->nameE->text();
        dataManager->name[1] = mainTab->surnameE->text();

        dataManager->username = mainTab->usernameE->text();
        dataManager->sex = !mainTab->femaleR->isChecked();
        dataManager->age = mainTab->ageE->text();
        dataManager->weight = mainTab->weightE->text();
        dataManager->height = mainTab->heightE->text();
        dataManager->note = mainTab->noteTE->toPlainText();

        dataManager->transmitMetadata();

        // aktualizace cesty k souboru
        QFileInfo fileInfo(dataManager->FOLDER_NAME+"/"+dataManager->username+"/metadata.txt");
        mainTab->pathE->setText(fileInfo.absoluteFilePath());
        mainTab->pathL->show();
        mainTab->pathE->show();
    }
}

/**
 * Vytvori list hlavni - nastaveni udaju uzivatele
 * @brief MainTab::MainTab
 * @param fileInfo
 * @param parent
 */
MainTab::MainTab(DataManager *dataManager, QWidget *parent) : QWidget(parent) {
    QFileInfo fileInfo(dataManager->FOLDER_NAME+"/"+dataManager->username+"/metadata.txt");

    QLabel *nameL = new QLabel(tr("Jméno:"));
    nameE = new QLineEdit(dataManager->name[0]);

    QLabel *surnameL = new QLabel(tr("Příjmení:"));
    surnameE = new QLineEdit(dataManager->name[1]);

    QLabel *usernameL = new QLabel(tr("Uživatelské jméno:"));
    usernameE = new QLineEdit(dataManager->username);

    QLabel *sexL = new QLabel(tr("Pohlaví:"));

    maleR = new QRadioButton(tr("Muž"));
    maleR->setChecked(dataManager->sex);
    femaleR = new QRadioButton(tr("Žena"));
    femaleR->setChecked(!dataManager->sex);

    QWidget *radioBox = new QWidget();
    QHBoxLayout *hBox = new QHBoxLayout(radioBox);
    hBox->addWidget(maleR);
    hBox->addWidget(femaleR);
    hBox->addStretch(1);

    QLabel *ageL = new QLabel(tr("Věk:"));
    ageE = new QLineEdit(dataManager->age);

    QLabel *weightL = new QLabel(tr("Hmotnost [kg]:"));
    weightE = new QLineEdit(dataManager->weight);

    QLabel *heightL = new QLabel(tr("Výška [cm]:"));
    heightE = new QLineEdit(dataManager->height);

    QLabel *noteL = new QLabel(tr("Poznámka:"));
    noteTE = new QTextEdit(dataManager->note);

    pathL = new QLabel(tr("Cesta k úložišti dat:"));
    pathE = new QLineEdit(fileInfo.absoluteFilePath());
    pathE->setReadOnly(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nameL);
    mainLayout->addWidget(nameE);
    mainLayout->addWidget(surnameL);
    mainLayout->addWidget(surnameE);
    mainLayout->addWidget(usernameL);
    mainLayout->addWidget(usernameE);
    mainLayout->addWidget(sexL);
    mainLayout->addWidget(radioBox);
    mainLayout->addWidget(ageL);
    mainLayout->addWidget(ageE);
    mainLayout->addWidget(weightL);
    mainLayout->addWidget(weightE);
    mainLayout->addWidget(heightL);
    mainLayout->addWidget(heightE);    
    mainLayout->addWidget(noteL);
    mainLayout->addWidget(noteTE);

    mainLayout->addWidget(pathL);
    mainLayout->addWidget(pathE);
    // pokud se username v dataManageru rovna "", potom skryt cestu k metadatum
    if (!QString::compare(dataManager->username, "")) {
        pathL->hide();
        pathE->hide();
    }

    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

/**
 * Vytvori list senzory - nastaveni viditelnych senzoru + nastaveni ukladani dat
 * @brief SensorsTab::SensorsTab
 * @param sensors widgety senzoru
 * @param numberOfSensors pocet senzoru
 * @param parent
 */
SensorsTab::SensorsTab(SensorWidget *sensors[], int numberOfSensors, QCheckBox *sensorCB[], DataManager *dataManager, QWidget *parent) : QWidget(parent) {
    // ----------------- skupina senzory
    QGroupBox *sensorsGroup = new QGroupBox(tr("Zobrazené senzory"));
    QVBoxLayout *sensorsLayout = new QVBoxLayout;

    // prochazeni vsech senzoru
    for(int i = 0; i < numberOfSensors; i++) {
        sensorCB[i] = new QCheckBox(sensors[i]->getSensor()->getName().toStdString().c_str());

        // nastaveni zaskrtnutych a zobrazenych sensoru dle dataManageru
        if (dataManager->sensors[i]) {
            sensorCB[i]->setChecked(true);
            sensors[i]->isVisible = true;
        }
        else {
            sensorCB[i]->setChecked(false);
            sensors[i]->isVisible = false;
        }

        sensorsLayout->addWidget(sensorCB[i]);
        // propojeni checkboxu s akci v SensorWidget
        QObject::connect(sensorCB[i], SIGNAL(toggled(bool)), sensors[i], SLOT(on_action_toggled(bool)));
        // propojeni zmeny v akci v SensorWidget s checkboxem
        QObject::connect(sensors[i], SIGNAL(visible(bool)), sensorCB[i], SLOT(setChecked(bool)));
    }
    sensorsGroup->setLayout(sensorsLayout);

    // ----------------- skupina ukladani
    QGroupBox *saveGroup = new QGroupBox(tr("Ukládání dat"));

    saveCB = new QCheckBox("Ukládat naměřená data do formátu csv pro další zpracování");
    saveCB->setChecked(dataManager->isSaveData);

    QVBoxLayout *saveLayout = new QVBoxLayout;
    saveLayout->addWidget(saveCB);
    saveGroup->setLayout(saveLayout);

    // -----------------

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sensorsGroup);
    mainLayout->addWidget(saveGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
