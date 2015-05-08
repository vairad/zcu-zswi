#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui/ui_mainwindow.h"
#include "gui/sensorwidget.h"
#include "gui/metadialog.h"
#include "gui/initialwindow.h"
#include "gui/connectionwindow.h"
#include "core/arduinominer.h"

namespace Ui {
class MainWindow;
}

/**
 * Hlavni GUI trida
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(DataManager *manager, QWidget *parent = 0);
    ~MainWindow();
    void createToolBar();
    void createUserPanel();
    void addMetadataToUserPanel();
    void addItemsToListWidget();
    void setUp();
    void closeEvent(QCloseEvent *event);
    /** uvodni okno */
    InitialWindow *initialWindow;
    /** Okno se spojenim */
    ConnectionWindow *connectionWindow;
    /** pocet sensoru */
    static const int NUMBER_OF_SENSORS = 6;
    /** senzory */
    SensorWidget *sensors[NUMBER_OF_SENSORS];
    /** spravce dat */
    DataManager *dataManager;
    /** dialog metadat */
    MetaDialog *metaDialog;
    /** komunikator s arduinem */
    ArduinoMiner *arduinoMiner;

public slots:
    void setMetadata();

private slots:
    void on_actionZav_t_triggered();
    void on_actionO_aplikaci_triggered();
    void on_actionU_ivatelsk_nastaven_triggered();
    void on_actionZm_na_u_ivatele_triggered();
    void on_actionVy_istit_v_e_triggered();
    void startScanning();
    void stopScanning();
    void cleanAll();
    void setSaveData(bool save);
    void itemClickedLoadFile(QListWidgetItem *item);
    void on_actionOtev_t_triggered();
    void portChoosed();
    void on_indicatorChanged(QString status, QString color);
    void on_indicatorDataChanged(QString status, QString color);


private:
    Ui::MainWindow *ui;
    /** Panel uzivatel s informacemi o uzivateli */
    QWidget *userPanel;
    /** grid layout pro groupBox v user panelu */
    QGridLayout *layout;
    /** Panel uzivatel - label pro jmeno */
    QLabel *nameL;
    /** Panel uzivatel - label pro prijmeni */
    QLabel *surnameL;
    /** Panel uzivatel - label pro pohlavi */
    QLabel *sexL;
    /** Panel uzivatel - label pro vek */
    QLabel *ageL;
    /** Panel uzivatel - label pro hmotnost */
    QLabel *weightL;
    /** Panel uzivatel - label pro vyska */
    QLabel *heightL;
    /** Indikator stavu spojeni */
    QLabel *labelStatConn;
    /** stav prichozich dat */
    QLabel *labelArduData;
    /** Checkbox pro nastaveni ukladani metadat */
    QCheckBox *saveCB;
    /** widget pro vypis ulozenych dat v pravem sloupci */
    QListWidget *listWidget;
    /** vybrany seriovy port */
    QString choosedPort;


};

#endif // MAINWINDOW_H
