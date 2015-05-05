#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QObject>
#include <QThread>
#include <QDateTime>

#include "core/metadatareader.h"
#include "core/istorable.h"
#include "core/iworking.h"
#include "core/fileminer.h"

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
    void initSenzorListeners();

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
    void loadDataFromFile(QString filename);

private:
    /** Ukazatel na načítač datového souboru */
    FileMiner *fileMiner;
    int numberOfData;

    float listToFile[NUMBER_OF_SENSORS];

    /** Nastaví námi ovládané pointery na NULL*/
    void initPointers();

public slots:
    void transmitDataToSaver(int, float);
};

#endif // DATAMANAGER_H
