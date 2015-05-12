#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QRegularExpression>

#include "core/metadatareader.h"
#include "core/istorable.h"
#include "core/iworking.h"
#include "core/fileminer.h"
#include "core/arduinominer.h"

/**
 * Sprava dat ziskanych z IMiner a IStorable, predani dat konkretnim senzorum
 * @brief The DataManager class
 */
class DataManager : public QThread {
Q_OBJECT
public:
    DataManager();
    ~DataManager();
    /** predani dat jednotlivym senzorum */
    void transmitData(QString row);
    void transmitMetadata();
    void connectSensorToSaver();
    void disconnectSensorToSaver();
    void getMetadata(QString username);
    QString getNameFromMetadata(QString username);
    QDateTime getDateTimeFromMetadata(QString username);
    QStringList listOfFolders();
    QStringList listOfFiles();
    void logoutUser();
    void createMiner();
    ArduinoMiner *arduino;

    /** Privátní odkazy na senzory */
    IWorking *listenEKG;
    IWorking *listenGSR;
    IWorking *listenHeartRate;
    IWorking *listenOxy;
    IWorking *listenPosition;
    IWorking *listenTemp;

    /** ukladac dat */
    IStorable *saver;
    /** cteni metadat */
    MetadataReader *metadataReader;
    /** nasev souboru pro metadata */
    QString FILE_METADATA_NAME;
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** nazev souboru dat */
    QString FILE_NAME;
    /** pocet senzoru */
    static const int NUMBER_OF_SENSORS = 6;
    /** Metadata - jmeno a prijmeni pacienta */
    QString name[2];
    /** Metadata - senzory nastavene danemu pacientovi */
    bool sensors[NUMBER_OF_SENSORS];
    /** Metadata - uzivatelske jmeno (pacienta), slouzi k nazvu slozky */
    QString username;   
    /** Metadata - pohlavi pacienta */
    bool sex;
    /** Metadata - vek pacienta */
    QString age;
    /** Metadata - hmotnost pacienta */
    QString weight;
    /** Metadata - vyska pacienta */
    QString height;
    /** Metadata - poznamka */
    QString note;
    /** Metadata - zda je nastaveno ukladani dat */
    bool isSaveData;
    /** zda jsou nacetena metadata */
    bool isSetMetadata;

    bool draw;
    void run();

    /** Nastavení listenerů patřičným senzorům */
    void setListenerEKG(IWorking *senzorEKG);
    void setListenerGSR(IWorking *senzorGSR);
    void setListenerHearthRate(IWorking *senzorHearthRate);
    void setListenerOxy(IWorking *senzorOxy);
    void setListenerPosition(IWorking *senzorPosition);
    void setListenerTemp(IWorking *senzorTemp);
    void loadFile(QString filename);
    void loadDataFromFile(QString filename, bool isPath);

private:
    /** Ukazatel na načítač datového souboru */
    FileMiner *fileMiner;
    /** porovnávač dle regularního výrazu csv */
    QRegularExpression CSV_COMPARER;

    /** Poslední hodnota na senzoru */
    float tempLastValue = 0;
    float heartValue = 0;
    float oxyLastValue = 0;
    float gsrLastValue = 0;
    float positionLastValue = 0;
    float ekgLastValue = 0;

    int numberOfData;

    float listToFile[NUMBER_OF_SENSORS];

    /** Nastaví námi ovládané pointery na NULL*/
    void initPointers();
    /** Nastaví posluchače senzorů na NULL */
    void initSenzorListeners();
    /** Kontroluje zda QString odpovídá patternu CSV_REG_EXP */
    bool validateLineCSV(QString &line);

//Privátní konstanty
    /** počet sloupců očekávaných v souboru .csv*/
    const int CSV_COLUMN_COUNT = 6;
    /** regulární výraz popisující řádek csv. souboru
     *  krajní vzhled akceptované řádky:
     *  d.dddddd;ddd;d.dddddd;ddd.dddddd;d.dddddd;ddd
     */
    const QString CSV_REG_EXP = "^\\d[.]{0,1}[\\d]{0,6};[\\d]{1,3};\\d[.]{0,1}[\\d]{0,6};\\d{1,3}[.]{0,1}[\\d]{0,6};\\d[.]{0,1}[\\d]{0,6};[\\d]{1,3}";


public slots:
    void transmitDataToSaver(int, float);

signals:
    void dataStatusChanged(QString, QString);
    void statusChanged(QString, QString);

    void checkPort();
};

#endif // DATAMANAGER_H
