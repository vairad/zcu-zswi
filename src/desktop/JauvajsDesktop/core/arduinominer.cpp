#include <QtSerialPort/QSerialPort>
#include <QStringList>

#include <QDebug>
#include <QSerialPortInfo>

#include "core/arduinominer.h"


ArduinoMiner::ArduinoMiner() {
    list = new QStringList();
    initialization = false;
    serial = new QSerialPort();
}

/**
 * Inicializace sériového portu
 * @brief ArduinoMiner::readSerial
 */
void ArduinoMiner::init(QString port) {

    serial->setPortName(port);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);

    initialization = serial->open(QIODevice::ReadOnly);

    if(initialization){
        emit statusChanged(port+" připojeno ✓", "green");
        qDebug() << "serial opened";
    }else{
        qDebug() << "serial not opened";
        emit statusChanged("Připojení "+port+" se nezdařilo", "red");
    }

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial,SIGNAL(readyRead()),this,SLOT(readSerial()));

    qDebug() << "end of init ardu reader";
}

/**
 * Čte data ze sériového portu
 * @brief ArduinoMiner::readSerial
 */
void ArduinoMiner::readSerial(){
}

/**
 * Uzavře sériový port
 * @brief ArduinoMiner::closeSerial
 */
void ArduinoMiner::closeSerial(){
    if(serial->isOpen()){
        serial->close();
    }
    initialization = false;
    emit statusChanged("Odpojeno", "red");
}

void ArduinoMiner::handleError(QSerialPort::SerialPortError error) {
    closeSerial();
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
   return serial->readLine();
    /*if(list->isEmpty()){
        return NULL;
    }
    return list->takeFirst();*/
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

