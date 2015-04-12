#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QtWidgets>
#include <QDialog>
#include "gui/sensorwidget.h"
#include "core/datamanager.h"

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
    explicit MainTab(QWidget *parent = 0);
    QLineEdit *nameE;
    QLineEdit *surnameE;
};

/**
 * List senzory - nastaveni viditelnych senzoru
 * @brief The SensorsTab class
 */
class SensorsTab : public QWidget {
    Q_OBJECT

public:
    explicit SensorsTab(SensorWidget *sensors[], int numberOfSensors, QCheckBox *sensorCB[], QWidget *parent = 0);
};

/**
 * Dialog umoznujici nastaveni meta dat
 * @brief The TabDialog class
 */
class MetaDialog : public QDialog {
    Q_OBJECT

public:
    explicit MetaDialog(SensorWidget *sensors[], int numberOfSensors, QWidget *parent = 0);
    /** hlavni list */
    MainTab *mainTab;
    /** spravce dat */
    DataManager *dataManager;

public slots:
    void updateMetadata();

private:
    /** widget s listy */
    QTabWidget *tabWidget;
    /** box s tlacitky OK a Cancel */
    QDialogButtonBox *buttonBox;
    /** checkboxy senzoru */
    QCheckBox *sensorCB[6];
};

#endif
