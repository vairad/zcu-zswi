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

vector<bool> AnalyserEKG::analysePRInterval() {
    vector<bool> pr;

    return pr;
}

/**
 * Zjisti trvani Q vlny ve vsech srdecnich cyklech.
 * @brief AnalyserEKG::getQWaveDuration
 * @return vektor trvani Q vlny ve vsech cyklech
 */
vector<int> AnalyserEKG::getQWaveDuration() {
    vector<int> duration;
    vector<float> differences = transcriber->getValueDifferences();
    int i, j, counter;

    for(i = 0; i < string.size(); i++) {
        counter = 0;
        if (string[i] == 'S') {
            for(j = i; j > 0; j--) {
                if (differences[j-1] < 0) { /* pocita, dokud vlna klesa */
                    counter++;
                } else {
                    break;
                }
            }
            duration.push_back(counter);
        }
    }

    return duration;
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
    int i, counter = 0;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S' && i > 0) {
            if (getQWaveDuration()[counter] == 1 && /* amplituda musi byt mensi nez 1/4 R vlny */
                    fabs(differences[i - 1]) < fabs (0.25 * differences[i])) {
                qWave.push_back(true); /* vlna je OK */
            } else if (getQWaveDuration()[counter] == 2 &&
                       fabs(differences[i - 1] + differences[i - 2]) < fabs(0.25 * differences[i])) {
                qWave.push_back(true); /* vlna je OK */
            } else { /* klesani nesmi byt delsi nez 2 pismenka (0,04 s) */
                qWave.push_back(false); /* vlna neni OK */
            }
            counter++;
        }
    }

    return qWave;
}

AnalyserEKG::~AnalyserEKG() {

}

