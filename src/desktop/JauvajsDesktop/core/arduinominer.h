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
    void init();
    /** posilani zprav pres eriovy port */
    void sendMessage(QString line);
    QString getLastIncoming();

signals:
    void statusChanged(QString);

private slots:
    void readSerial();

private:
   QSerialPort *serial;
   QStringList *list;
};
#endif // ARDUINOMINER_H

