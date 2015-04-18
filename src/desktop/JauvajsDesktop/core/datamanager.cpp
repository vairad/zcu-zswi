#include <QList>
#include "datamanager.h"
#include "filesaver.h"
#include <QRegExp>
#include <QStringList>

DataManager::DataManager() {
    saver = new FileSaver();
    metadataReader = new MetadataReader();

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

    // vlozeni jmena a prijmeni do listu
    for (int i = 0; i < 2; i++) {
        list.push_back(name[i]);
    }

    // vlozeni nastavenych senzoru do listu
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        list.push_back(QString::number(sensors[i]));
    }

    saver->saveMetadata(list);
}

/**
 * Ziskani metadat od metadataReaderu
 * @brief DataManager::getMetadata
 * @param username uzivatelske jmeno
 */
void DataManager::getMetadata(QString username) {
    QList<QString> list = metadataReader->loadMetadata(username);

    // ziskani jmena a prijmeni z listu
    for (int i = 0; i < 2; i++) {
        name[i] = list.front();
        list.pop_front();
    }

    // ziskani nastavenych senzoru z listu
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        sensors[i] = list.front().toInt();
        list.pop_front();
    }
}


/**
 * Prijem namerenych dat
 * @brief DataManager::getData
 * @param row prijaty radek
 */
void DataManager::transmitData(QString row) {
    //split dle tabulatoru: [T&28	C&-1.00	R&6017652.50	H&1.241447	P&0	O&0.00	F&7]
    QStringList cellData = row.split('\t');
    foreach (const QString &cell, cellData) {
        //mam data ve formatu (senzor)&(hodnota)
        QStringList sensorData = cell.split('&');
        QString sensorFlag = sensorData.at(0);
        QString sensorValue = sensorData.at(1);
        if(sensorFlag == "T") {
            // senzor teploty
        }
        else if(sensorFlag == "P") {
            //senzor pulsu
        }
        else if(sensorFlag == "O") {
            //senzor okysliceni
        }
        else if(sensorFlag == "V") {
            //senzor vodivosti pokozky
        }
        else if(sensorFlag == "R") {
            //senzor odporu pokozky
        }
        else if(sensorFlag == "H") {
            //senzor ekg
        }
        else if(sensorFlag == "A") {
            //senzor polohy/akcelerometr
        }
        else if(sensorFlag == "F") {
            //senzor proudeni vzduchu
        }
        else {
            // neznamy sensor
        }
    }
}

DataManager::~DataManager() {

}

