#include "metadialog.h"

/**
 * Vytvori dialog umoznujici nastaveni meta dat
 * @brief MetaDialog::MetaDialog
 * @param sensors
 * @param parent
 */
MetaDialog::MetaDialog(SensorWidget *sensors[], QWidget *parent) : QDialog(parent) {
    tabWidget = new QTabWidget;
    mainTab = new MainTab();
    tabWidget->addTab(mainTab, tr("Hlavní"));
    tabWidget->addTab(new SensorsTab(sensors), tr("Senzory"));

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
 * Vytvori list senzory - nastaveni viditelnych senzoru
 * @brief SensorsTab::SensorsTab
 * @param sensors
 * @param parent
 */
SensorsTab::SensorsTab(SensorWidget *sensors[], QWidget *parent) : QWidget(parent) {
    QGroupBox *sensorsGroup = new QGroupBox(tr("Zobrazené senzory"));

    QCheckBox *sensorCB;
    QVBoxLayout *permissionsLayout = new QVBoxLayout;

    // prochazeni vsech senzoru
    for(int i = 0; i < 6; i++) {
        sensorCB = new QCheckBox(sensors[i]->getSensor()->getName().toStdString().c_str());

        if (!sensors[i]->isHidden()) sensorCB->setChecked(true);
        permissionsLayout->addWidget(sensorCB);
        QObject::connect(sensorCB, SIGNAL(toggled(bool)), sensors[i], SLOT(on_action_toggled(bool)));

    }
    sensorsGroup->setLayout(permissionsLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(sensorsGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
