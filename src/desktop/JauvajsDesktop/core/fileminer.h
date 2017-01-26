#ifndef FILEMINER_H
#define FILEMINER_H

#include "core/iminer.h"

#include <QString>
#include <QFile>
#include <QTextStream>

class FileMiner : public IMiner{

    /** Opened file */
    QFile sourceFile;
    /** flag if file was opened correctly default false */
    bool opened;
    /** input stream for siply reading file*/
    QTextStream* in;

public:
    /** Constructor opens file and create input stream */
    FileMiner(QString fileName);

    /** Destructor close opened file */
    virtual ~FileMiner();

    /**
     * DO NOTHING ... ONLY READ FILE
     * Metoda, která zaručuje odeslání zprávy směrem do zařízení pro získání dat.
     * Formát zpráv viz GitHub Wiki - Referenční příručka Arduino
     *
     * @param line - řádek zprávy pro zdroj dat
     */
   void sendMessage(QString line);

    /**
     * Metoda, která vrátí poslední zprávu datového zdroje nebo nic, pokud není nová zpráva k dispozici.
     *
     * @return řádek poslední zprávy nebo null, pokud není nová zpráva k dispozici.
     */
    QString getLastIncoming();
};

#endif // FILEMINER_H
