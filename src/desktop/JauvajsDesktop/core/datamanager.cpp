#include <QList>
#include <QDir>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QException>
#include <QDebug>

#include "datamanager.h"
#include "fileproblemexception.h"
#include "filesaver.h"

DataManager::DataManager() {
    FOLDER_NAME = "data";
    FILE_METADATA_NAME = "metadata.txt";
    FILE_NAME = "ekg.dat";

    saver = new FileSaver(FILE_METADATA_NAME);
    metadataReader = new MetadataReader(FILE_METADATA_NAME);

    draw = false;

    initSenzorListeners(); //všechny listenery nastaví na NULL

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

    // vlozeni dalsich metadat
    list.push_back(QString::number(sex));
    list.push_back(age);
    list.push_back(weight);
    list.push_back(height);

    // vlozeni nastavenych senzoru do listu
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        list.push_back(QString::number(sensors[i]));
    }

    // vlozeni nastaveni ukladani
    list.push_back(QString::number(isSaveData));

    // vlozeni aktualniho casu
    list.push_back(QDateTime::currentDateTime().toString());

    // vlozeni poznamky
    list.push_back(note);

    saver->saveMetadata(FOLDER_NAME, list);
}

/**
 * Ziskani metadat od metadataReaderu
 * @brief DataManager::getMetadata
 * @param username uzivatelske jmeno
 */
void DataManager::getMetadata(QString username) {
    QList<QString> list = metadataReader->loadMetadata(FOLDER_NAME, username);

    this->username = username;

    // ziskani jmena a prijmeni z listu
    for (int i = 0; i < 2; i++) {
        name[i] = list.takeFirst();
    }

    // ziskani dalsich metadat
    sex = list.takeFirst().toInt();
    age = list.takeFirst();
    weight = list.takeFirst();
    height = list.takeFirst();

    // ziskani nastavenych senzoru z listu
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        sensors[i] = list.takeFirst().toInt();
    }

    // ziskani nastaveni ukladani dat
    isSaveData = list.takeFirst().toInt();

    // ziskani poznamky
    list.pop_front();
    note = list.takeFirst();

    isSetMetadata = true;
    transmitMetadata();
}

/**
 * Prijem namerenych dat
 * @brief DataManager::getData
 * @param row prijaty radek
 */
void DataManager::transmitData(QString row) {

    QStringList leftBracket = row.split('[');
    if(leftBracket.size() == 2) {
        // leva je nalezena, pracuji s pravou stranou

        QStringList rightBracket = leftBracket[1].split(']');
        if(rightBracket.size() == 2) {

            //split dle tabulatoru: [T&28	C&-1.00	R&6017652.50	H&1.241447	P&0	O&0.00	F&7]
            QStringList cellData = rightBracket[0].split('\t');
            foreach (const QString &cell, cellData) {
                //mam data ve formatu (senzor)&(hodnota)
                QStringList sensorData = cell.split('&');
                char sensorFlag = sensorData.at(0)[0].toLatin1(); // funkce .toAscii je zastaralá
                float sensorValue = sensorData.at(1).toFloat();// hodnota za ampersandem

                switch(sensorFlag)
                {
                    case 'T': this->listenTemp->transmitData(sensorValue);break;
                    case 'P': this->listenHeartRate->transmitData(sensorValue);break;
                    case 'O': this->listenOxy->transmitData(sensorValue);break;
                    case 'V': this->listenGSR->transmitData(sensorValue);break;
                    case 'H': this->listenEKG->transmitData(sensorValue);break;
                    case 'A': this->listenPosition->transmitData(sensorValue);break;
                    case 'F': this->listenOxy->transmitData(sensorValue);break;
                default:
                    // neznamy sensor
                    break;
                }
            }
        }
  }
}

/**
 * Propoji senzory IWorking s transmitDataToSaver
 * @brief DataManager::connectSensorToSaver
 */
void DataManager::connectSensorToSaver() {
    if (isSaveData) {
        connect(listenEKG, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int, float)));
        connect(listenTemp, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int, float)));
        connect(listenPosition, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int, float)));
        connect(listenOxy, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int, float)));
        connect(listenGSR, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int, float)));
        connect(listenHeartRate, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int, float)));

        saver->createFileForData(username);
        numberOfData = 0;
    }
}

/**
 * Predani dat saveru
 * @brief DataManager::transmitDataToSaver
 */
void DataManager::transmitDataToSaver(int id, float data) {
    if (isSaveData) {
        numberOfData++;

        listToFile[id] = data;

        if (numberOfData == NUMBER_OF_SENSORS) {
            saver->saveData(listToFile);
            numberOfData = 0;
        }
    }
}

/**
 * Odpoji senzory IWorking s transmitDataToSaver
 * @brief DataManager::connectSensorToSaver
 */
void DataManager::disconnectSensorToSaver() {
    if (isSaveData) {
        disconnect(listenEKG, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int,float)));
        disconnect(listenTemp, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int,float)));
        disconnect(listenPosition, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int,float)));
        disconnect(listenOxy, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int,float)));
        disconnect(listenGSR, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int,float)));
        disconnect(listenHeartRate, SIGNAL(haveDataToSave(int, float)), this, SLOT(transmitDataToSaver(int,float)));

        saver->closeFileForData();
    }
}

/**
 * Vypise seznam slozek umistenych v datove slozce (workspace)
 * @brief DataManager::listOfFolders
 * @return  seznam slozek
 */
QStringList DataManager::listOfFolders() {
    QDir path(FOLDER_NAME + "/");
    QStringList folders = path.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    return folders;
}

/**
 * Vypise seznam ulozenych csv souboru v slozce uzivatele
 * @brief DataManager::listOfFiles
 * @return
 */
QStringList DataManager::listOfFiles() {
    QDir path(FOLDER_NAME + "/" + username + "/");
    path.setNameFilters(QStringList() << "*.csv");
    QStringList files = path.entryList(QDir::Files);
    return files;
}

/**
 * Vrati jmeno uzivatele nactenim se souboru metadat dle uživatelskeho jmena
 * @brief DataManager::getNameFromMetadata
 * @param username uzivatelske jmeno
 * @return cele jmeno
 */
QString DataManager::getNameFromMetadata(QString username) {
    QList<QString> list = metadataReader->loadMetadata(FOLDER_NAME, username);

    QString name;
    if (!list.isEmpty()) {
        name = list[1]+" "+list[0];
    }
    else {
        name = QString();
    }

    return name;
}

/**
 * Vrati jmeno uzivatele nactenim se souboru metadat dle uživatelskeho jmena
 * @brief DataManager::getNameFromMetadata
 * @param username uzivatelske jmeno
 * @return cele jmeno
 */
QDateTime DataManager::getDateTimeFromMetadata(QString username) {
    QList<QString> list = metadataReader->loadMetadata(FOLDER_NAME, username);

    QDateTime dateTime;
    if (!list.isEmpty()) {
        dateTime = QDateTime::fromString(list[12]);
    }
    else {
        dateTime = QDateTime();
    }

    return dateTime;
}

/**
 * Vyprazdneni metadat
 * @brief DataManager::logoutUser
 */
void DataManager::logoutUser() {
    name[0] = "";
    name[1] = "";
    username = "";
    sex = "";
    age = "";
    weight = "";
    height = "";
    note = "";
    isSaveData = false;
    isSetMetadata = false;

    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
        sensors[i] = true;
    }
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

/**
 * Nacte soubor
 * @brief DataManager::loadFile
 */
void DataManager::loadFile() {
    fileMiner = NULL;
    try {
       fileMiner = new FileMiner(FILE_NAME);
    } catch (FileOpenProblemException &e) {
        qDebug() << e.getMessage();
    }
}

void DataManager::run() {
    loadFile();
    //qDebug() << "run";
    int count = 0;
    while (true) {
        if (listenEKG != NULL && fileMiner != NULL) {
            if (count % 50 == 0) {
                if (draw) {
                    QCoreApplication::processEvents();
                    QString data = fileMiner->getLastIncoming();
                    if (data != NULL) {
                        listenEKG->transmitData(data.toFloat());
                        listenTemp->transmitData(data.toFloat());
                        listenOxy->transmitData(data.toFloat());
                        listenPosition->transmitData(data.toFloat());
                        listenGSR->transmitData(data.toFloat());
                        listenHeartRate->transmitData(data.toFloat());
                    }
                    else {
                        draw = false;
                    }

                }
            }
        } else {
           if (fileMiner == NULL) {
               draw = false;
           }
        }

        for (int i=0; i < 100000; i++) {}
        count++;
    }

}

DataManager::~DataManager() {

}

