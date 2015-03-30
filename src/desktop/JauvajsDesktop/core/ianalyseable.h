#ifndef IANALYSEABLE
#define IANALYSEABLE

/**
 * Rozhrani deklarujici metody pro analýzu dat senzoru.
 * @brief The IAnalyseable class
 */
class IAnalyseable {

public:
    IAnalyseable();
    ~IAnalyseable();

    /**
     * Metoda, která zaručuje získání výsledků analýzy.
     * Signalizuje, zda jsou data v normě či znepokojující. Škála jako ve škole.
     * @return int hodnota jako ve škole
     */
   virtual int getResult() = 0;

    /**
     * Metoda, která spustí analýzu dat senzoru.
     * @return informace, zda analýza proběhla bez problémů
     */
    virtual boolean analyse() = 0;

    /**
     * Metoda, která zaručuje předání textové zprávy o výsledku analýzy.
     * @return řetězec informace o analýze
     */
    virtual string getMessage() = 0;

};

#endif // IANALYSEABLE

