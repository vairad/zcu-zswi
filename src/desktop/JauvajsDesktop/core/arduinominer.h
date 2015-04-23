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

/** Definice bluetooth protokolu */
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
    typedef enum {STATUS_REST, STATUS_FIND, STATUS_CONNECT } STATUS;
    STATUS status;

signals:
    /** Signal vyvolany pri zmene seznamu nalezenych zarizeni*/
    void ListChanged(QStringList*);
    /** Signal regujici na zmenu stavu*/
    void changeStatus(QString);
    /** Signal reagujici na zmenu spojeni*/
    void ConnectionChanged(QString);
    /** Signal reagujici na prijata data*/
    void PrijmiData(QString);

private:
   /** Vyhledavajici kriteria */
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   /** Handle, pres ktery se pristuju k zarizeni*/
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   /** Informace o nalezenem zarizeni */
   BLUETOOTH_DEVICE_INFO btDeviceInfo;
   /** Vyhledani okolnich zarizeni */
   void findDevices();
   /** Navazani BT komunikace */
   void beginConnection();
   /** Soket pres ktery se komunikuje pres BT */
   SOCKET BTsocket;
   /** Priznak oznacujici stav spojeni */
   int err;
   /** Prvni faze navazini spojeni */
   void connectionStatus();
   /** Otevreni a navazani soketu */
   void openSocket();
   /** Zahajeni naslouchani prichozich dat na soketu */
   void startListening();
};

#endif // ARDUINOMINER_H
