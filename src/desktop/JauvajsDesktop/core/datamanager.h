#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QObject>
#include "metadatareader.h"
#include "istorable.h"

#include "core/iworking.h"

/**
 * Sprava dat ziskanych z IMiner a IStorable, predani dat konkretnim senzorum
 * @brief The DataManager class
 */
class DataManager {

    /** Privátní odkazy na senzory */
     IWorking *sensorEKG;
     IWorking *sensorGSR;
     IWorking *sensorHeartRate;
     IWorking *sensorOxy;
     IWorking *sensorPosition;
     IWorking *sensorTemp;

public:
    DataManager();
    ~DataManager();

    /** predani dat jednotlivym senzorum */
    void transmitData(QString row);
    void transmitMetadata();    
    void getMetadata(QString username);
    QString getNameFromMetadata(QString username);
    QStringList listOfFolders();
    /** ukladac dat */
    IStorable *saver;
    /** cteni metadat */
    MetadataReader *metadataReader;
    /** nasev souboru pro metadata */
    QString FILE_METADATA_NAME;
    /** nazev slozky pro ukladani dat */
    QString FOLDER_NAME;
    /** pocet senzoru */
    static const int NUMBER_OF_SENSORS = 6;
    /** Metadata - jmeno a prijmeni pacienta */
    QString name[2];
    /** Metadata - senzory nastavene danemu pacientovi */
    bool sensors[NUMBER_OF_SENSORS];
    /** Metadata - uzivatelske jmeno (pacienta), slouzi k nazvu slozky */
    QString username;
    /** zda jsou nacetena metadata */
    bool isSetMetadata;
};

#endif // DATAMANAGER_H
