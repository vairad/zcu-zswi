#include "datamanager.h"
#include "filesaver.h"

#include <QList>
#include <QDir>
#include <QRegExp>
#include <QStringList>

DataManager::DataManager() {
    FOLDER_NAME = "data";
    FILE_METADATA_NAME = "metadata.txt";

    saver = new FileSaver(FOLDER_NAME, FILE_METADATA_NAME);
    metadataReader = new MetadataReader(FOLDER_NAME, FILE_METADATA_NAME);

    initSenzorListeners(); //všechny listenery nastaví na NULL

   /* Touto cestou ne... Nastavit pomocí setSenzorXX(&senzor) ... v  místě kde se vytvoří */
   /* this->sensorEKG = new SensorEKG();
    this->sensorGSR = new SensorGSR();
    this->sensorHeartRate = new SensorHeartRate();
    this->sensorOxy = new SensorOxy();
    this->sensorPosition = new SensorPosition();*/

    // vyprazdneni metadat
    logoutUser();
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

    this->username = username;

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
    isSetMetadata = true;
}

/**
 * Prijem namerenych dat
 * @brief DataManager::getData
 * @param row prijaty radek
 */
void DataManager::transmitData(QString row) {
    //split dle tabulatoru: [T&28	C&-1.00	R&6017652.50	H&1.241447	P&0	O&0.00	F&7]
    row.replace("[", "");// odstraneni zavorek
    row.replace("]", "");
    QStringList cellData = row.split('\t');
    foreach (const QString &cell, cellData) {
        //mam data ve formatu (senzor)&(hodnota)
        QStringList sensorData = cell.split('&');
        QString sensorFlag = sensorData.at(0);
        float sensorValue = sensorData.at(1).toFloat();
        if(sensorFlag == "T") {
            this->listenTemp->transmitData(sensorValue);
        }
        else if(sensorFlag == "P") {
            this->listenHeartRate->transmitData(sensorValue);
        }
        else if(sensorFlag == "O") {
            this->listenOxy->transmitData(sensorValue);
        }
        else if(sensorFlag == "V") {
            this->listenGSR->transmitData(sensorValue);
        }
        else if(sensorFlag == "R") {
          //  TO DO
        }
        else if(sensorFlag == "H") {
            this->listenEKG->transmitData(sensorValue);
        }
        else if(sensorFlag == "A") {
            this->listenPosition->transmitData(sensorValue);
        }
        else if(sensorFlag == "F") {
            this->listenOxy->transmitData(sensorValue);
        }
        else {
            // neznamy sensor
        }
    }
}

/**
 * Vypise seznam slozek umistenych v datove slozce data/
 * @brief DataManager::listOfFolders
 * @return  seznam slozek
 */
QStringList DataManager::listOfFolders() {
    QDir path(FOLDER_NAME + "/");
    QStringList folders = path.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    return folders;
}

/**
 * Vrati jmeno uzivatele nactenim se souboru metadat dle uživatelskeho jmena
 * @brief DataManager::getNameFromMetadata
 * @param username uzivatelske jmeno
 * @return cele jmeno
 */
QString DataManager::getNameFromMetadata(QString username) {
    QList<QString> list = metadataReader->loadMetadata(username);

    QString name = list[0]+" "+list[1];
    return name;
}

/**
 * Vyprazdneni metadat
 * @brief DataManager::logoutUser
 */
void DataManager::logoutUser() {
    name[0] = "";
    name[1] = "";
    username = "";
    isSetMetadata = false;
}

/**
 * Nastaví ukazatele všech senzorů na NULL
 * @brief DataManager::initSenzorListeners
 */
void DataManager::initSenzorListeners(){
    listenEKG = NULL;
    listenGSR = NULL;
    listenHeartRate = NULL;
    listenOxy = NULL;
    listenPosition = NULL;
    listenTemp = NULL;
}


/**
 * Nastaví EKG listener
 * @brief DataManager::setListenerEKG
 * @param senzorEKG - IWorking pro předání dat
 */
void DataManager::setListenerEKG(IWorking *senzorEKG){
    listenEKG = senzorEKG;
}

/**
 * Nastaví GSR listener
 * @brief DataManager::setListenerGSR
 * @param senzorGSR - IWorking pro předání dat
 */
void DataManager::setListenerGSR(IWorking *senzorGSR){
    listenGSR = senzorGSR;
}

/**
 * Nastaví HearthRate listener
 * @brief DataManager::setListenerEKG
 * @param senzorHearthRate - IWorking pro předání dat
 */
void DataManager::setListenerHearthRate(IWorking *senzorHearthRate){
    listenHeartRate = senzorHearthRate;
}

/**
 * @brief DataManager::setListenerOxy
 * @param senzorOxy - IWorking pro předání dat
 */
void DataManager::setListenerOxy(IWorking *senzorOxy){
    listenOxy = senzorOxy;
}

/**
 * @brief DataManager::setListenerPosition
 * @param senzorPosition - IWorking pro předání dat
 */
void DataManager::setListenerPosition(IWorking *senzorPosition){
    listenPosition = senzorPosition;
}

/**
 * @brief DataManager::setListenerTemp
 * @param senzorTemp - IWorking pro předání dat
 */
void DataManager::setListenerTemp(IWorking *senzorTemp){
    listenTemp = senzorTemp;
}

DataManager::~DataManager() {

}

