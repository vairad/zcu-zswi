#include <vector>
#include <QList>
#include "datamanager.h"
#include "filesaver.h"
#include <iostream>
#include <QRegExp>

DataManager::DataManager() {
    saver = new FileSaver();

    // zatim docasna testovaci data - BUDOU ODSTRANENA
    name[0] = "Jan";
    name[1] = "Novák";
    username = "novakjan";
}

/**
 * Predani metadat saveru
 * @brief DataManager::transmitMetadata
 */
void DataManager::transmitMetadata() {
    QList<QString> list;

    // vlozeni uzivatelskeho jmena
    list.push_back(username);

    // vlozeni jmena a prijmeni do vectoru
    for (int i = 0; i < 2; i++) {
        list.push_back(name[i]);
    }

    // vlozeni nastavenych senzoru do vectoru
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        list.push_back(QString::number(sensors[i]));
    }

    saver->saveMetadata(list);
}

DataManager::~DataManager() {

}

