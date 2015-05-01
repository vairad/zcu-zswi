#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QtWidgets>
#include <QDialog>

#include "core/datamanager.h"
#include "gui/sensorwidget.h"

class QDialogButtonBox;
class QFileInfo;
class QTabWidget;

/**
 * List hlavni - nastaveni udaju uzivatele
 * @brief The MainTab class
 */
class MainTab : public QWidget {
    Q_OBJECT

public:
    explicit MainTab(DataManager *dataManager, QWidget *parent = 0);
    /** textove pole pro jmeno */
    QLineEdit *nameE;
    /** textove pole pro prijmeni */
    QLineEdit *surnameE;
    /** textove pole pro uzivatelske jmeno */
    QLineEdit *usernameE;  
    /** radio button pro pohlavi - muz */
    QRadioButton *maleR;
    /** radio button pro pohlavi - zena */
    QRadioButton *femaleR;
    /** textove pole pro vek */
    QLineEdit *ageE;
    /** textove pole pro hmotnost */
    QLineEdit *weightE;
    /** textove pole pro vysku */
    QLineEdit *heightE;
    /** textove pole pro poznamku */
    QTextEdit *noteTE;
    /** pole pro informaci o umisteni metadat */
    QLineEdit *pathE;
    /** label pro pole pro informaci o umisteni metadat */
    QLabel *pathL;
};

/**
 * List senzory - nastaveni viditelnych senzoru
 * @brief The SensorsTab class
 */
class SensorsTab : public QWidget {
    Q_OBJECT

public:
    explicit SensorsTab(SensorWidget *sensors[], int numberOfSensors, QCheckBox *sensorCB[], DataManager *dataManager, QWidget *parent = 0);
};

/**
 * Dialog umoznujici nastaveni meta dat
 * @brief The TabDialog class
 */
class MetaDialog : public QDialog {
    Q_OBJECT

public:
    explicit MetaDialog(DataManager *dataManager, SensorWidget *sensors[], int numberOfSensors, QWidget *parent = 0);
    /** hlavni list */
    MainTab *mainTab;
    /** spravce dat */
    DataManager *dataManager;

public slots:
    void checkingInputs();
    void updateMetadata();

private:
    /** widget s listy */
    QTabWidget *tabWidget;
    /** box s tlacitky OK a Cancel */
    QDialogButtonBox *buttonBox;
    /** checkboxy senzoru */
    QCheckBox *sensorCB[6];
    /** true pokud jsou validni vstupy od uzivatele */
    bool isValidInputs;
};

#endif
