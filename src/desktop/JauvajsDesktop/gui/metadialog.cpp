#include "gui/metadialog.h"

/**
 * Vytvori dialog umoznujici nastaveni meta dat
 * @brief MetaDialog::MetaDialog
 * @param sensors widgety senzoru
 * @param numberOfSensors pocet senzoru
 * @param parent
 */
MetaDialog::MetaDialog(SensorWidget *sensors[], int numberOfSensors, QWidget *parent) : QDialog(parent) {
    tabWidget = new QTabWidget;
    mainTab = new MainTab();
    tabWidget->addTab(mainTab, tr("Hlavní"));
    tabWidget->addTab(new SensorsTab(sensors, numberOfSensors), tr("Senzory"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    //connect(this, SIGNAL(accepted()), mainWindow, SLOT(setMetaData()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Nastavení"));
}

/**
 * Vytvori list hlavni - nastaveni udaju uzivatele
 * @brief MainTab::MainTab
 * @param fileInfo
 * @param parent
 */
MainTab::MainTab(QWidget *parent) : QWidget(parent) {
    QFileInfo fileInfo("metadata.txt");

    QLabel *nameL = new QLabel(tr("Jméno:"));
    nameE = new QLineEdit("Jan");

    QLabel *surnameL = new QLabel(tr("Příjmení:"));
    surnameE = new QLineEdit("Novák");

    QLabel *pathL = new QLabel(tr("Cesta k úložišti dat:"));
    QLabel *pathVL = new QLabel(fileInfo.absoluteFilePath());
    pathVL->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nameL);
    mainLayout->addWidget(nameE);
    mainLayout->addWidget(surnameL);
    mainLayout->addWidget(surnameE);

    mainLayout->addWidget(pathL);
    mainLayout->addWidget(pathVL);
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
SensorsTab::SensorsTab(SensorWidget *sensors[], int numberOfSensors, QWidget *parent) : QWidget(parent) {
    // ----------------- skupina senzory
    QGroupBox *sensorsGroup = new QGroupBox(tr("Zobrazené senzory"));

    QCheckBox *sensorCB;
    QVBoxLayout *sensorsLayout = new QVBoxLayout;

    // prochazeni vsech senzoru
    for(int i = 0; i < numberOfSensors; i++) {
        sensorCB = new QCheckBox(sensors[i]->getSensor()->getName().toStdString().c_str());

        if (!sensors[i]->isHidden()) sensorCB->setChecked(true);
        sensorsLayout->addWidget(sensorCB);
        // propojeni checkboxu s akci v SensorWidget
        QObject::connect(sensorCB, SIGNAL(toggled(bool)), sensors[i], SLOT(on_action_toggled(bool)));
        // propojeni zmeny v akci v SensorWidget s checkboxem
        QObject::connect(sensors[i], SIGNAL(visible(bool)), sensorCB, SLOT(setChecked(bool)));

    }
    sensorsGroup->setLayout(sensorsLayout);

    // ----------------- skupina ukladani
    QGroupBox *saveGroup = new QGroupBox(tr("Ukládání dat"));

    QCheckBox *saveCB;
    saveCB = new QCheckBox("Ukládat naměřená data do formátu csv pro další zpracování");

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
