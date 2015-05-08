#include <QtSerialPort/QSerialPort>
#include <QStringList>

#include <QDebug>
#include <QSerialPortInfo>

#include "core/arduinominer.h"


ArduinoMiner::ArduinoMiner() {
    list = new QStringList();
    initialization = false;
}

/**
 * Inicializace sériového portu
 * @brief ArduinoMiner::readSerial
 */
void ArduinoMiner::init(QString port) {

    serial = new QSerialPort();
    serial->setPortName(port);
    serial->open(QIODevice::ReadOnly);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial,SIGNAL(readyRead()),this,SLOT(readSerial()));
    initialization = true;
}

/**
 * Čte data ze sériového portu
 * @brief ArduinoMiner::readSerial
 */
void ArduinoMiner::readSerial(){
    emit statusChanged("Připojeno ✓", "green");
    int i = 1000000;
    while(--i>0){} // cekaci smycka
    QString line = serial->readLine();
    list->push_back(line);
}

/**
 * Uzavře sériový port
 * @brief ArduinoMiner::closeSerial
 */
void ArduinoMiner::closeSerial(){
    serial->close();
}

void ArduinoMiner::handleError(QSerialPort::SerialPortError error) {
    qDebug() << error;
}

/**
 * Metoda, která zaručuje odeslání zprávy směrem do zařízení pro získání dat.
 * Formát zpráv viz GitHub Wiki - Referenční příručka Arduino
 *
 * @param line - řádek zprávy pro zdroj dat
 */
void ArduinoMiner::sendMessage(QString line){

}

/**
 * Metoda, která vrátí poslední zprávu datového zdroje nebo nic, pokud není nová zpráva k dispozici.
 *
 * @return řádek poslední zprávy nebo null, pokud není nová zpráva k dispozici.
 */
QString ArduinoMiner::getLastIncoming() {
    if(list->isEmpty()){
        return NULL;
    }
    return list->takeFirst();
}

bool ArduinoMiner::checkYourCOM() {

    list_Of_Ports = QSerialPortInfo::availablePorts();

    foreach (QSerialPortInfo port, list_Of_Ports) {
       if(port.portName() == this->portNumber) {
           if(port.description() == ""){
           // zarizeni odpojeno
               this->serial->close();
               emit statusChanged("Odpojeno", "red");
           }
           else {
              return true;
           }
       }
    }
    return false;
}

/**
 * Destruktor arduinomineru
 *
 */
ArduinoMiner::~ArduinoMiner(){
    delete list;
    delete serial;
}

