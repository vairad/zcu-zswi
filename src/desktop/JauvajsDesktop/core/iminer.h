#ifndef IMINER
#define IMINER

#include <QString>

/**
 * Rozhrani deklarujici metody pro získání (dolování) dat a jejich ovlivnění pomocí zpráv.
 * @brief The IMiner class
 */
class IMiner {

public:

    /**
     * Metoda, která zaručuje odeslání zprávy směrem do zařízení pro získání dat.
     * Formát zpráv viz GitHub Wiki - Referenční příručka Arduino
     *
     * @param line - řádek zprávy pro zdroj dat
     */
   virtual void sendMessage(QString line) = 0;

    /**
     * Metoda, která vrátí poslední zprávu datového zdroje nebo nic, pokud není nová zpráva k dispozici.
     *
     * @return řádek poslední zprávy nebo null, pokud není nová zpráva k dispozici.
     */
    virtual QString getLastIncoming() = 0;

};

#endif // IMINER

