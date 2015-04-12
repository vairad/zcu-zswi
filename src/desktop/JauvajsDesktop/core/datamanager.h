#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QObject>
#include "istorable.h"

/**
 * Sprava dat ziskanych z IMiner a IStorable, predani dat konkretnim senzorum
 * @brief The DataManager class
 */
class DataManager {
public:
    DataManager();
    ~DataManager();

    void transmitMetadata();
    /** ukladac dat */
    IStorable *saver;
    /** pocet senzoru */
    static const int NUMBER_OF_SENSORS = 6;
    /** Metadata - jmeno a prijmeni pacienta */
    QString name[2];
    /** Metadata - senzory nastavene danemu pacientovi */
    bool sensors[NUMBER_OF_SENSORS];

};

#endif // DATAMANAGER_H
