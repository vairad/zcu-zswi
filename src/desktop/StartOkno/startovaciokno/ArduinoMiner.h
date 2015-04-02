#ifndef ARDUINOMINER_H
#define ARDUINOMINER_H

#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QtCore>

#include <Winsock2.h>
#include <Windows.h>
#include <BluetoothAPIs.h>
#include <Ws2bth.h>

class ArduinoMiner: public QThread
{
    Q_OBJECT
public:
    explicit ArduinoMiner(QObject *parent = 0);
    ~ArduinoMiner();
    void run();
    bool stop;
    QStringList ListNalezenychZarizeni;

signals:
    void SeznamChanged(QStringList*);
    void ZmenaStavu(QString);


public slots:


private:
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   BLUETOOTH_DEVICE_INFO btDeviceInfo;


};

#endif // ARDUINOMINER_H
