#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QObject>
#include "metadatareader.h"
#include "istorable.h"

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
    /** ukladac dat */
    IStorable *saver;

    MetadataReader *metadataReader;
    /** pocet senzoru */
    static const int NUMBER_OF_SENSORS = 6;
    /** Metadata - jmeno a prijmeni pacienta */
    QString name[2];
    /** Metadata - senzory nastavene danemu pacientovi */
    bool sensors[NUMBER_OF_SENSORS];
    /** Metadata - uzivatelske jmeno (pacienta), slouzi k nazvu slozky */
    QString username;

};

#endif // DATAMANAGER_H
