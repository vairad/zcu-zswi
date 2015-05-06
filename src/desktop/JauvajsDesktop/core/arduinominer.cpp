#include <QtSerialPort/QSerialPort>
#include <QStringList>

#include <QDebug>

#include "core/arduinominer.h"


ArduinoMiner::ArduinoMiner() {
    list = new QStringList();
}

void ArduinoMiner::init() {
    serial = new QSerialPort();
    serial->setPortName("COM21");
    serial->open(QIODevice::ReadOnly);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    QObject::connect(serial,SIGNAL(readyRead()),this,SLOT(readSerial()));
    qDebug() << "initialoization of serial";
    emit statusChanged("Port otevřený");
}

void ArduinoMiner::readSerial(){
    int i = 10000000;
    while(--i>0){} // wait loop

    QString line = serial->readLine();
    qDebug() << line;
    list->push_back(line);
}


void ArduinoMiner::closeSerial(){
    serial->close();
    emit statusChanged("Port uzavřen");
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

ArduinoMiner::~ArduinoMiner(){
    delete list;
    delete serial;
}

