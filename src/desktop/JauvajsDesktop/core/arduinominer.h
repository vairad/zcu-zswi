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
    /** Metoda bezici ve vlaknu (navazuje spojeni, cte data) */
    void run();
    /** Odesilani dat do Arduina */
    int SendData(QString);
    /** Ukonceni BT komunikace */
    void CloseConnection();
    /** Seznam nalezenych zarizeni */
    QStringList ListFoundDevices;
    /** Vybrane zarizeni se kterym se navaze spojeni */
    QString selectedDevice;
    /** Vyctovy typ udavajici stav vlakna */
    typedef enum {STATUS_KLID, STATUS_HLEDEJ, STATUS_SPOJENI } STATUS;
    STATUS status;

signals:
    void ListChanged(QStringList*);
    void changeStatus(QString);
    void ConnectionChanged(QString);
    void PrijmiData(QString);

private:
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   BLUETOOTH_DEVICE_INFO btDeviceInfo;
   /** Vyhledani okolnich zarizeni */
   void findDevices();
   /** Navazani BT komunikace */
   void beginConnection();
   /** Soket pres ktery se komunikuje pres BT */
   SOCKET soket;
   /** Priznak oznacujici stav spojeni */
   int err;
};

#endif // ARDUINOMINER_H
