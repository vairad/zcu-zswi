#include <math.h>
#include <QDebug>

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
 * @return vektor delek intervalu RR v poctu pismenek pro vsechny cele
 * namerene cykly.
 */
vector<int> AnalyserEKG::getRRIntervalDuration() {
    vector<int> interval;
    int i, counter = 0;
    bool isIn = false;

    for (i = 0; i < (int)string.size(); i++) {
        if (string[i] == 'S' && isIn == false) {
            if (i + 2 < (int)differences.size() && differences[i + 1] > 0 && differences[i + 2] > 0) {
              /* strme stoupani by nemelo trvat dlouho, nesmi se splest s jinou vlnou */
              continue;
            }
            if (i + 1 < (int)differences.size() && differences[i + 1] > 0) {
                i++; /* nekdy R vlna ma delsi trvani, tzn. pocita, dokud se stale stoupa */
            }
            firstRWaveIndex = i;
            isIn = true;
        } else if (string[i] == 'S' && isIn == true) {
            if (i + 2 < (int)differences.size() && differences[i + 1] > 0 && differences[i + 2] > 0) {
              counter++; /* strme stoupani by nemelo trvat dlouho, nesmi se splest s jinou vlnou */
              continue;
            }
            if (i + 1 < (int)differences.size() && differences[i + 1] > 0) {
                counter++;
                i++; /* nekdy R vlna ma delsi trvani, tzn. pocita, dokud se stale stoupa */
            }
            interval.push_back(counter);
            counter = 0;

        } else if (string[i] == 'V' && isIn == false) {
            if (i - 2 > 0 && string[i - 1] == 'U' && string[i - 2] == 'U') {
                counter = 0; /* nekdy velkemu spadu nepredchazi kratke prudke stoupani, ale delsi stredni */
                firstRWaveIndex = i - 1;
                isIn = true;
            }
        } else if (string[i] == 'V' && isIn == true) {
            if (i - 2 > 0 && string[i - 1] == 'U' && string[i - 2] == 'U') {
                interval.push_back(counter - 1);
                counter = 0;
            }
        }
        counter++;
    }
    return interval;
}

/**
 * Spocita indexy vrcholu vsech R vln
 * @brief AnalyserEKG::getRWaveIndex
 * @return vektor indexu vrcholu R vln
 */
vector<int> AnalyserEKG::getRWaveIndex() {
    vector<int> index;
    vector<int> interval = getRRIntervalDuration();
    int i, tmp;

    index.push_back(firstRWaveIndex);

    for (i = 0; i < (int)interval.size(); i++) {
        tmp = index.back();       
        index.push_back(tmp + interval[i]);
    }

    return index;
}

/**
 * Vypocita delku stoupajici R vlny na zadanem indexu
 * @brief getRWaveDuration
 * @param index index vlny v retezci
 * @return delku (pocet pismen) stoupajici R vlny
 */
int AnalyserEKG::getLeftRWaveDuration(int index) {
    int i, counter = 0;
    for (i = index; i >= 0 && differences[i] > 0; i--) {
        counter++;
    }
    return counter;
}

/**
 * Vypocita delku klesajici R vlny na zadanem indexu
 * @brief getRWaveDuration
 * @param index index vlny v retezci
 * @return delku (pocet pismen) klesajici R vlny
 */
int AnalyserEKG::getRightRWaveDuration(int index) {
    int i, counter = 0;
    for (i = index; i < (int)string.size() && differences[i] < 0; i++) {
        counter++;
    }
    return counter;
}

/**
 * Vypocita amplitudu R vlny na zadanem indexu
 * @brief getRWaveAmplitude
 * @param index index vlny v retezci
 * @return amplitudu R vlny
 */
float AnalyserEKG::getRWaveAmplitude(int index) {
    int duration = getLeftRWaveDuration(index);
    float amplitude = differences[index] - differences[index - duration];
    return amplitude;
}


/**
 * Zjisti trvani Q vlny v cyklu dle zadaneho indexu.
 * @brief AnalyserEKG::getQWaveDuration
 * @param index R vlny, kde se ma trvani Q vlny pocitat
 * @return trvani Q vlny (pocet znaku)
 */
int AnalyserEKG::getQWaveDuration(int index) {
    int duration = 0;
    int i;

    for (i = index - getLeftRWaveDuration(index); i >= 0 && differences[i] < 0 && string[i] != 'C'; i--) {
         duration++;
    }

    return duration;
}


/**
 * Zjisti trvani Q vlny ve vsech srdecnich cyklech.
 * @brief AnalyserEKG::getQWaveDuration
 * @return vektor trvani Q vlny ve vsech cyklech (v poctech znaku)
 */
vector<int> AnalyserEKG::getQWaveDuration() {
    vector<int> duration;
    vector<int> rWaveIndex = getRWaveIndex();
    int i, j, counterQ, counterR = 0;
    qDebug() << "metoda getQWaveDuration";
    for (i = 0; i < (int)string.size(); i++) {
        counterQ = 0;
        qDebug() << "zacal cyklus qWaveDuration";
        if (i < (int)rWaveIndex.size()) {
            if (i == rWaveIndex[counterR]) {
                j = i - getLeftRWaveDuration(i);
                qDebug() << "j = " << j;
                while (j >= 0) {
                    if (differences[j] < 0 && string[j] != 'C') { /* pocita, dokud vlna klesa */
                        counterQ++;
                        qDebug() << "counterQ = " << counterQ;
                    } else {
                        break;
                    }
                    j--;
                }
                duration.push_back(counterQ);
                counterR++;
                qDebug() << "counterR = " << counterR;
            }
        }
    }
    qDebug() << "skoncil cyklus qWaveDuration";
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
    vector<int> rWaveIndex = getRWaveIndex();
    int i, j, counter = 0;


    for (i = 0; i < (int)string.size(); i++) {
        if (i == rWaveIndex[counter]) {
            j = i - getLeftRWaveDuration(i);
            if (j >= 0 && getQWaveDuration()[counter] == 1 && /* amplituda musi byt mensi nez 1/4 R vlny */
                    fabs(differences[j]) < fabs (0.25 * getRWaveAmplitude(i))) {
                qWave.push_back(true); /* vlna je OK */
            } else if (j > 0 && getQWaveDuration()[counter] == 2 &&
                    fabs(differences[j] + differences[j - 1]) < fabs(0.25 * getRWaveAmplitude(i))) {
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
 * Spocita delku S vlny na zadanem indexu
 * @brief AnalyserEKG::getSDuration
 * @param index index vrcholu R vlny
 * @return delka trvani (pocet pismenek) S vlny
 */
int AnalyserEKG::getSDuration(int index) {
    int i, counter = 0;
    for (i = index + getRightRWaveDuration(index); i < (int)string.size() && differences[i] > 0 && string[i] != 'C'; i++) {
        counter++;
    }
    return counter;
}

vector<int> AnalyserEKG::getQRSDuration() {
    vector<int> duration;
    vector<int> rWave = getRWaveIndex();
    qDebug() << "Metoda getQRSDuration";
    int i, countDuration = 0, counterR = 0;

    for (i = 0; i < (int)string.size(); i++) {
        if (counterR < (int)rWave.size()) {
            if (i == rWave[counterR]) {
                countDuration = getLeftRWaveDuration(i) + getQWaveDuration(i)
                        + getRightRWaveDuration(i) + getSDuration(i);
                counterR++;
                duration.push_back(countDuration);
                qDebug() << "duration QRS = " << countDuration;
            }
        }
    }

    return duration;
}

/**
 * Analyzuje usek QRS.
 * @brief AnalyserEKG::analyseQRS
 * @return vektor pravdivostnich hodnot, zda je QRS normalni
 */
vector<bool> AnalyserEKG::analyseQRS() {
    vector<bool> qrs;
    qDebug() << "Metoda analyseQRS";
    vector<int> duration = getQRSDuration();
    qDebug() << "QRSDuration vypoctena";
    vector<int> rWaveIndex = getRWaveIndex();
    qDebug() << "rWaveIndex vypocten";
    int i, counter = 0;

    for (i = 0; i < (int)string.size(); i++) {
        if (counter < (int)rWaveIndex.size()) {
            if (i == rWaveIndex[counter]) {
                if (duration[counter] > 0.12 * DATA_SEC || getRWaveAmplitude(i) < 0.5) {
                    qrs.push_back(false);
                } else {
                    qrs.push_back(true);
                }
                counter++;
            }
        }
    }

    return qrs;
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
    vector<int> interval = getRRIntervalDuration();
    int i;
    float duration = 0;

    for (i = 0; i < (int)interval.size(); i++) {
        duration += interval[i] / (float)DATA_SEC;
    }

    duration = duration / (float)interval.size();
    return duration;
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
    qDebug() << "Metoda analyze";
    vector<bool> qrs = analyseQRS();
    qDebug() << "vektor připraven";

    int i, countTrue = 0;

    int size = (int)qrs.size();
    for (i = 0; i < size; i++) {
        if (qrs[i] == true) {
            countTrue++;
        }
    }

    normalityPercentage = 100 * (float)countTrue / (int)qrs.size();
}

AnalyserEKG::~AnalyserEKG() {
}

