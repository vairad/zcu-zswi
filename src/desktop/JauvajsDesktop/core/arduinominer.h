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
#include <QtSerialPort/QSerialPort>


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
    int OdesliData(QString);
    /** Ukonceni BT komunikace */
    void UkonciSpojeni();
    /** Seznam nalezenych zarizeni */
    QStringList ListNalezenychZarizeni;
    QString vybraneZarizeni;
    typedef enum {STATUS_KLID, STATUS_HLEDEJ, STATUS_SPOJENI } STATUS;
    STATUS stav;
    void navazSpojeni();
    void init();

signals:
    void SeznamChanged(QStringList*);
    void ZmenaStavu(QString);
    void ZmenaSpojeni(QString);
    void PrijmiData(QString);

private slots:
    void readSerial();
    void handleError(QSerialPort::SerialPortError);

private:
   QSerialPort *serial;
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   BLUETOOTH_DEVICE_INFO btDeviceInfo;
   void hledejOkolniZarizeni();
   SOCKET soket;
   int err;
   void navazaniSoketu();
   void otevreniSoketu();
   void zacniNaslouchat();
};
#endif // ARDUINOMINER_H

