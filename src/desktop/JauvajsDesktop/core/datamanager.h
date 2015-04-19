#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QObject>
#include "metadatareader.h"
#include "istorable.h"
#include "sensorekg.h"
#include "sensorgsr.h"
#include "sensorheartrate.h"
#include "sensoroxy.h"
#include "sensorposition.h"
#include "sensortemp.h"

/**
 * Sprava dat ziskanych z IMiner a IStorable, predani dat konkretnim senzorum
 * @brief The DataManager class
 */
class DataManager {
public:
    DataManager();
    ~DataManager();

    /** predani dat jednotlivym senzorum */
    void transmitData(QString row);
    /** */
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

    /** Odkaz na senzor EKG */
    SensorEKG *sensorEKG;
    /** Odkaz na senzor GSR */
    SensorGSR *sensorGSR;
    /** Odkaz na senzor HearthRate */
    SensorHeartRate *sensorHeartRate;
    /** Odkaz na senzor Oxy */
    SensorOxy *sensorOxy;
    /** Odkaz na senzor pozice */
    SensorPosition *sensorPosition;
    /** Odkaz na senzor teploty */
    SensorTemp *sensorTemp;
};

#endif // DATAMANAGER_H
