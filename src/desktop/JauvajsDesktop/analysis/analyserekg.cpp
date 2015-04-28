#include <math.h>

#include "analyserekg.h"


AnalyserEKG::AnalyserEKG(vector<float> data) {
    this->transcriber = new TranscriberEKG(data);
    this->transcriber->transcribeData();
    this->string = transcriber->getString();
    this->differences = transcriber->getValueDifferences();
}

/**
 * Spocita delku intervalu RR pro kazdy srdecni cyklus
 * @brief AnalyserEKG::getRRInterval
 * @return vektor delek intervalu RR v sekundach pro vsechny cele
 * namerene cykly.
 */
vector<float> AnalyserEKG::getRRIntervalDuration() {
    vector<float> interval;
    int i, counter = 0;
    bool isIn = false;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S' && isIn == false) {
            if (i + 2 < differences.size() && differences[i + 1] > 0 && differences[i + 2] > 0) {
              /* strme stoupani by nemelo trvat dlouho, nesmi se splest s jinou vlnou */
              continue;
            }
            if (i + 1 < differences.size() && differences[i + 1] > 0) {
                i++; /* nekdy R vlna ma delsi trvani, tzn. pocita, dokud se stale stoupa */
            }

            isIn = true;
        } else if (string[i] == 'S' && isIn == true) {
            if (i + 2 < differences.size() && differences[i + 1] > 0 && differences[i + 2] > 0) {
              counter++; /* strme stoupani by nemelo trvat dlouho, nesmi se splest s jinou vlnou */
              continue;
            }
            if (i + 1 < differences.size() && differences[i + 1] > 0) {
                counter++;
                i++; /* nekdy R vlna ma delsi trvani, tzn. pocita, dokud se stale stoupa */
            }
            interval.push_back((counter / (float)DATA_SEC));
            counter = 0;

        } else if (string[i] == 'V' && isIn == false) {
            if (i - 2 > 0 && string[i - 1] == 'U' && string[i - 2] == 'U') {
                counter = 0; /* nekdy velkemu spadu nepredchazi kratke prudke stoupani, ale delsi stredni */
                isIn = true;
            }
        } else if (string[i] == 'V' && isIn == true) {
            if (i - 2 > 0 && string[i - 1] == 'U' && string[i - 2] == 'U') {
                interval.push_back(((counter - 1) / (float)DATA_SEC));
                counter = 0;
            }
        }
        counter++;
    }

    return interval;
}

/**
 * Vrati pocet celych namerenych srdecnich cyklu (R-R)
 * @brief AnalyserEKG::getNumberOfCycles
 * @return pocet celych namerenych srdecnich cyklu
 */
unsigned int AnalyserEKG::getNumberOfCycles() {
    unsigned int number = (unsigned int)getRRIntervalDuration().size();
    return number;
}

/**
 * Vypocita prumernou delku srdecniho cyklu
 * @brief AnalyserEKG::getAverageCycleDuration
 * @return prumerna delka srdecniho cyklu v sekundach
 */
float AnalyserEKG::getAverageCycleDuration() {
    vector<float> interval = getRRIntervalDuration();
    int i;
    float duration = 0;

    for (i = 0; i < interval.size(); i++) {
        duration += interval[i];
    }

    duration = duration / (float)interval.size();
    return duration;
}

/**
 * Zjisti trvani PR intervalu ve vsech cyklech
 * @brief AnalyserEKG::getPRIntervalDuration
 * @return vektor trvani PR intervalu ve vsech cyklech (v poctech znaku)
 */
vector<int> AnalyserEKG::getPRIntervalDuration() {
    int i, j, qLength, counter = 0;
    vector<int> prInterval;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S') {
           qLength = getQWaveDuration()[counter];
           prInterval.push_back(0);
           for (j = i - qLength - 1; j >= 0 && string[j] == 'C'; j--) {
               prInterval[counter]++;
           }
           prInterval[counter] += getPWaveDuration()[counter];
           counter++;
        }
    }

    return prInterval;
}

/**
 * Zjisti trvani P vlny ve vsech cyklech.
 * @brief AnalyserEKG::getPWaveDuration
 * @return vektor trvani P vlny ve vsech cyklech (v poctech znaku)
 */
vector<int> AnalyserEKG::getPWaveDuration() {
    int i, j, qLength, counter = 0;
    vector<int> pr;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S') {
           qLength = getQWaveDuration()[counter];
           pr.push_back(0);
           j = i - qLength - 1;
           while (j >= 0 && string[j] == 'C') {
              j--;
           }
           while (j >= 0 && differences[j] < 0) {
               pr[counter]++;
               j--;
           }
           while (j >= 0 && string[j] == 'C') {
               pr[counter]++;
               j--;
           }
           while (j >= 0 && differences[j] > 0 && string[j] != 'C') {
               pr[counter]++;
               j--;
           }
           counter++;
        }
    }

    return pr;
}

vector<bool> AnalyserEKG::analysePWave() {
    vector<bool> pWave;
    int i, counter = 0;

    for (i = 0; i < string.size(); i++) {
        if (string[i] == 'S') {
            if (i - getQWaveDuration()[counter] - getPRIntervalDuration()[counter] > 0) {
                if (getPWaveDuration()[counter] > 0.11 * DATA_SEC) {
                    pWave.push_back(false);
                }  /* amplituda musi byt 0.5 - 2.5 mV */

                //for (j = i - 1; j >= getPWaveDuration; j--) { // zjistit nejvyšší a nejnižší hodnotu v intervalu P vlny, spočítat rozdíl

//qDebug() << "zprava" << j;
                    //}
                //}

            }
        }
    }

    return pWave;
}

/**
 * Analyzuje PR interval v každém cyklu.
 * @brief AnalyserEKG::analysePRInterval
 * @return vektor pravdivostních hodnot, zda je PR interval normální
 */
vector<bool> AnalyserEKG::analysePRInterval() {
    vector<bool> pr;
    int i;

    for (i = 0; i < getPRIntervalDuration().size(); i++) {
        if (getPRIntervalDuration()[i] < 0.12 * DATA_SEC ||
                getPRIntervalDuration()[i] > 0.20 * DATA_SEC) {
            pr.push_back(false); /* interval je moc dlouhy, nebo moc kratky */
        } else {
            pr.push_back(true); /* interval je OK */
        }
    }

    return pr;
}

/**
 * Zjisti trvani Q vlny ve vsech srdecnich cyklech.
 * @brief AnalyserEKG::getQWaveDuration
 * @return vektor trvani Q vlny ve vsech cyklech (v poctech znaku)
 */
vector<int> AnalyserEKG::getQWaveDuration() {
    vector<int> duration;
    int i, j, counter;

    for (i = 0; i < string.size(); i++) {
        counter = 0;
        if (string[i] == 'S') {
            for (j = i; j > 0; j--) {
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

/**
 * Vrati procento normalnich srdecnich cyklu.
 * @brief AnalyserEKG::getNormalityPercentage
 * @return procento normalnich srdecnich cyklu
 */
float AnalyserEKG::getNormalityPercentage() {
    return normalityPercentage;
}

void AnalyserEKG::analyse() {

}

AnalyserEKG::~AnalyserEKG() {

}

