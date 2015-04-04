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
    QStringList ListNalezenychZarizeni;
    QString vybraneZarizeni;
    typedef enum {STATUS_KLID, STATUS_HLEDEJ, STATUS_SPOJENI } STATUS;
    STATUS stav;


signals:
    void SeznamChanged(QStringList*);
    void ZmenaStavu(QString);
    void ZmenaSpojeni(QString);

private:
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   BLUETOOTH_DEVICE_INFO btDeviceInfo;
   void hledejOkolniZarizeni();
   void navazSpojeni();
};

#endif // ARDUINOMINER_H
