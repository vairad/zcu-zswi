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

signals:
    void SeznamChanged(QStringList*);
    void ZmenaStavu(QString);
    void ZmenaSpojeni(QString);
    void PrijmiData(QString);

private:
   BLUETOOTH_DEVICE_SEARCH_PARAMS btSearchParams;
   HBLUETOOTH_DEVICE_FIND deviceHandle;
   BLUETOOTH_DEVICE_INFO btDeviceInfo;
   void hledejOkolniZarizeni();
   void navazSpojeni();
   SOCKET soket;
   int err; // příznak označující stav spojení
   void navazaniSoketu();
   void otevreniSoketu();
   void zacniNaslouchat();
};

#endif // ARDUINOMINER_H
