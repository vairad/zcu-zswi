#include <QList>
#include <QDir>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <QCoreApplication>
#include <QException>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <QDebug>

#include "datamanager.h"
#include "fileproblemexception.h"
#include "filesaver.h"
#include "idisplayable.h"

DataManager::DataManager() {    
    FOLDER_NAME = "data";
    FILE_METADATA_NAME = "metadata.txt";
    FILE_NAME = "ekg.dat";

    CSV_COMPARER.setPattern(CSV_REG_EXP);

    initPointers(); //nastavi pointery na NULL
    initSenzorListeners(); //všechny listenery nastaví na NULL

    saver = new FileSaver(FILE_METADATA_NAME);
    metadataReader = new MetadataReader(FILE_METADATA_NAME);

    draw = false;

    arduino = new ArduinoMiner();



    // vyprazdneni metadat
    logoutUser();

     loadFile(FILE_NAME);
}

/**
 * Nastaví všechny pointery struktury na NULL
 * @brief DataManager::initPointers
 */
void DataManager::initPointers(){
    fileMiner = NULL;
    saver = NULL;
    metadataReader = NULL;
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
           //split dle tabulatoru "1.769306	F2"
           QStringList cellData = rightBracket[0].split('\t');
           ekgLastValue = cellData.at(0).toFloat(); // priprava ekg hodnoty

           if(cellData.size() > 1) { //pokud mam neco za
            QString sensorFlag = cellData.at(1).left(1);
            QString sensorValue = cellData.at(1);
            sensorValue.replace(sensorFlag, QString(""));

            if(sensorFlag == "T")
               tempLastValue = sensorValue.toFloat();
            else if(sensorFlag == "P")
               heartValue = sensorValue.toFloat();
            else if(sensorFlag == "O")
               oxyLastValue = sensorValue.toFloat();
            else if(sensorFlag == "V")
               gsrLastValue = sensorValue.toFloat();
            else if(sensorFlag == "A"){}
            else if(sensorFlag == "F"){
             //   qDebug() << "Flow transmit";
                positionLastValue = sensorValue.toFloat();
              //  qDebug() << "Flow transmit::" << positionLastValue;
            }
            else {
             //neznamy senzor
            }

          }
          this->listenEKG->transmitData(ekgLastValue);
          this->listenTemp->transmitData(tempLastValue);
          this->listenHeartRate->transmitData(heartValue);
          this->listenOxy->transmitData(oxyLastValue);
          this->listenGSR->transmitData(gsrLastValue);
          this->listenPosition->transmitData(positionLastValue);
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
    int indexOfDate = 13;

    QDateTime dateTime;
    if (!list.isEmpty()) {
        dateTime = QDateTime::fromString(list[indexOfDate]);
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
void DataManager::loadFile(QString filename) {

    if(fileMiner != NULL){ // pokud je otevřený jiý soubor, zavři ho
        delete fileMiner;
    }

    fileMiner = NULL; // není žádný otevřený soubor

    try {
       fileMiner = new FileMiner(filename); // zkus otevřít soubo
    } catch (FileOpenProblemException &e) {
        qDebug() << e.getMessage();
    }
}

/**
 * Nacte vsechna data ze souboru a posle jednotlivym senzorum
 * @brief DataManager::loadDataFromFile
 * @param filename nazev souboru
 */
void DataManager::loadDataFromFile(QString filename) {
    loadFile(FOLDER_NAME + "/" + username + "/" + filename);
    QString data = fileMiner->getLastIncoming();
    QStringList listOfData;

    while (data != NULL) {
        listOfData = data.split(';');

        if(CSV_COLUMN_COUNT < listOfData.size() && validateLineCSV(data)) {
            listenEKG->transmitData(listOfData[0].toFloat());
            listenTemp->transmitData(listOfData[1].toFloat());
            listenOxy->transmitData(listOfData[2].toFloat());
            listenPosition->transmitData(listOfData[3].toFloat());
            listenGSR->transmitData(listOfData[4].toFloat());
            listenHeartRate->transmitData(listOfData[5].toFloat());
        }else{
           // qDebug() << "false";
        }
        data = fileMiner->getLastIncoming();
    }

    //emit ((IDisplayable *)listenEKG)->notHaveData();
    //emit ((IDisplayable *)listenTemp)->notHaveData();
    //emit ((IDisplayable *)listenOxy)->notHaveData();
    //emit ((IDisplayable *)listenPosition)->notHaveData();
    //emit ((IDisplayable *)listenGSR)->notHaveData();
    //emit ((IDisplayable *)listenHeartRate)->notHaveData();
}

void DataManager::run() {
    int count = 0;
    qDebug() << "bezi run";

    while (true) {
        if(arduino->initialization == true) {
            if (count % 80 == 0) {

                QCoreApplication::processEvents();
                QString data = arduino->getLastIncoming();
               // qDebug() << "data" << data;
                    if (data != NULL) {
                        transmitData(data);
                    }
                    else {
                  //  draw = false;
                    }
            }
            for (int i=0; i < 100000; i++) {}
            count++;
        //}
       }
        else {
            //inicializace portu neprobehla
        }
    }

}

/*

void DataManager::run() {
    qDebug() << "run";

    int count = 0;
    while (draw) {
        if (listenEKG != NULL && fileMiner != NULL) {
            if (count % 50 == 0) {
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
        } else {
           if (fileMiner == NULL) {
               draw = false;
           }
        }

        for (int i=0; i < 100000; i++) {}
        count++;
    }
}

*/

bool DataManager::validateLineCSV(QString &line){
   // QRegularExpression expression(CSV_REG_EXP);
    QRegularExpressionMatch match = CSV_COMPARER.match(line);
    if(match.hasMatch()) {
        return true;
    }else{
        return false;
    }
}

DataManager::~DataManager() {
    //qDebug() << "destructor od DataManager";
    if(fileMiner != NULL) {
        delete fileMiner;
        fileMiner = NULL;
    }
    if(saver != NULL) {
        delete saver;
    }
    if(metadataReader != NULL) {
        delete metadataReader;
    }

}

