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

DEFINE_GUID(RFCOMM_PROTOCOL_UUID, 0x00000003, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB);


class ArduinoMiner: public QThread
{
    Q_OBJECT

public:
    explicit ArduinoMiner(QObject *parent = 0);
    ~ArduinoMiner();
    void run();
    int SendData(QString);
    void CloseConnection();
    QStringList ListFoundDevices;
    QString vybraneZarizeni;
    typedef enum {STATUS_KLID, STATUS_HLEDEJ, STATUS_SPOJENI } STATUS;
    STATUS stav;

signals:
    void ListChanged(QStringList*);
    void changeStatus(QString);
    void ConnectionChanged(QString);
    void PrijmiData(QString);

private:
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   BLUETOOTH_DEVICE_INFO btDeviceInfo;
   void findDevices();
   void beginConnection();
   SOCKET soket;
   int err; // příznak označující stav spojení
};

#endif // ARDUINOMINER_H
