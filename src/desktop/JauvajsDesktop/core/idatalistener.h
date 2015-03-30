#ifndef IWORKABLE
#define IWORKABLE

/**
 * Rozhrani deklarujici metody pro předání a validaci dat.
 * (Například pomocí DataManageru)
 * @brief The IWorkable class
 */
class IDataListener {

public:
    IDataListener();
    ~IDataListener();

    /**
     * Metoda zaručuje předání dat této třídě (například z DataManageru)
     * @param new_value - poslední hodnota ke zpracování
     * @return informace, zda předání proběhlo korektně
     */
    virtual boolean passData(double new_value) = 0;

    /**
     * Metoda, která zaručuje základní validaci dat dle reálného rozsahu hodnot.
     * @return informace, zda zpracovávaná data mohou být daty senzoru
     */
    virtual boolean validateData() = 0;

};


#endif // IWORKABLE

