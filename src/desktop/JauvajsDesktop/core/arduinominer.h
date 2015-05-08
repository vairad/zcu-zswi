#ifndef ARDUINOMINER_H
#define ARDUINOMINER_H

#include <QStringList>
#include <QtSerialPort/QSerialPort>

#include "core/iminer.h"

class ArduinoMiner : public QObject, public IMiner {
    Q_OBJECT
public:
    ArduinoMiner();
    ~ArduinoMiner();

    /** Uzavreni serioveho portu */
    void closeSerial();
    /** inicializace serioveho portu */
    void init(QString port);
    /** posilani zprav pres eriovy port */
    void sendMessage(QString line);
    /** navrat posledni prichozi zpravy */
    QString getLastIncoming();
    /** provedeni inicializace*/
    bool initialization;

signals:
    void statusChanged(QString, QString);

private slots:
    void readSerial();

private:
   QSerialPort *serial;
   QStringList *list;
};
#endif // ARDUINOMINER_H

