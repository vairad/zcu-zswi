#include "analyserekg.h"
#include <math.h>

AnalyserEKG::AnalyserEKG(vector<float> data) {
    this->transcriber = new TranscriberEKG(data);
    this->transcriber->transcribeData();
    this->string = transcriber->getString();
}

/**
 * Spocita delku intervalu RR pro kazdy srdecni cyklus
 * @brief AnalyserEKG::getRRInterval
 * @return vektor delek intervalu RR v sekundach pro vsechny cele
 * namerene cykly.
 */
vector<float> AnalyserEKG::getRRInterval() {
    vector<float> interval;
    int i, counter = 0;
    bool isIn = false;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S' && isIn == false) {
            counter = 0;
            isIn = true;
        } else if (string[i] == 'S' && isIn == true) {
            interval.push_back((float)(counter / DATA_SEC));
            counter = 0;

        }
        counter++;
    }

    return interval;
}

vector<float> AnalyserEKG::getPWave() {
    vector<float> pWave;
    int i;

    for (i = 0; i < string.size(); i++) {

    }

    return pWave;
}

/**
 * Analyzuje vlnu Q. Ulozi do vektoru pravdivostni hodnoty
 * dle toho, zda je vlna v danem cyklu normalni.
 * @brief AnalyserEKG::analyseQWave
 * @return vektor pravdivostnich hodnot, zda je vlna v danych cyklech normalni
 */
vector<bool> AnalyserEKG::analyseQWave() {
    vector<bool> qWave;
    vector<float> differences = transcriber->getValueDifferences();
    int i;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S' && i > 0) {
            if (string[i - 1] == 'D' &&
                    fabs(differences[i - 1]) < fabs (0.25 * differences[i])) {
                if (i > 2) {
                    if (differences[i - 3] > 0) {
                        qWave.push_back(true); /* vlna je OK */
                    } else {
                        qWave.push_back(false); /* vlna není OK */
                    }
                }
            }
        }
    }

    return qWave;
}

AnalyserEKG::~AnalyserEKG() {

}

