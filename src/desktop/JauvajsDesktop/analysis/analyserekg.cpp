#include <math.h>
#include <QDebug>

#include "analyserekg.h"

/**
 * V konstruktoru se pripravi hodnoty potrebne k analyze.
 * @brief AnalyserEKG::AnalyserEKG
 * @param data namerena data EKG
 */
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
            if (i + 2 < (int)differences.size() && differences[i + 1] > 0 && string[i + 2] != 'C') {
                i++; /* nekdy R vlna ma delsi trvani, tzn. pocita, dokud se stale stoupa */
            }
            firstRWaveIndex = i;
            isIn = true;
            counter = 0;
        } else if (string[i] == 'S' && isIn == true) {
            if (i + 2 < (int)differences.size() && differences[i + 1] > 0 && differences[i + 2] > 0) {
              counter++; /* strme stoupani by nemelo trvat dlouho, nesmi se splest s jinou vlnou */
              continue;
            }
            if (i + 2 < (int)differences.size() && differences[i + 1] > 0 && string[i + 2] != 'C') {
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

    vector<int>().swap(interval);

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
    for (i = index + 1; i < (int)string.size() && differences[i] < 0; i++) {
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
 * Spocita delku S vlny na zadanem indexu
 * @brief AnalyserEKG::getSDuration
 * @param index index vrcholu R vlny
 * @return delka trvani (pocet pismenek) S vlny
 */
int AnalyserEKG::getSWaveDuration(int index) {
    int i, counter = 0;
    for (i = index + getRightRWaveDuration(index) + 1; i < (int)string.size() && differences[i] > 0
         && string[i] != 'C' && string[i] != 'L'; i++) {
        counter++;
    }
    return counter;
}

/**
 * Spocita delku trvani QRS komplexu pro vsechny srdecni cykly.
 * @brief AnalyserEKG::getQRSDuration
 * @return vektor delek trvani vsech QRS komplexu
 */
vector<int> AnalyserEKG::getQRSDuration() {
    vector<int> duration;
    vector<int> rWave = getRWaveIndex();
    int i, countDuration = 0, counterR = 0;

    for (i = 0; i < (int)string.size(); i++) {
        if (counterR < (int)rWave.size()) {
            if (i == rWave[counterR]) {
                countDuration = getLeftRWaveDuration(i) + getQWaveDuration(i)
                        + getRightRWaveDuration(i) + getSWaveDuration(i);
                counterR++;
                duration.push_back(countDuration);
            }
        }
    }

    vector<int>().swap(rWave);

    return duration;
}

/**
 * Analyzuje usek QRS.
 * @brief AnalyserEKG::analyseQRS
 * @return vektor pravdivostnich hodnot, zda je QRS normalni
 */
vector<bool> AnalyserEKG::analyseQRS() {
    vector<bool> qrs;
    vector<int> duration = getQRSDuration();
    vector<int> rWaveIndex = getRWaveIndex();
    int i, counter = 0;

    for (i = 0; i < (int)string.size(); i++) {
        if (counter < (int)rWaveIndex.size()) {
            if (i == rWaveIndex[counter]) {
                if (duration[counter] > QRS_DURATION * DATA_SEC || getRWaveAmplitude(i) < R_AMPLITUDE) {
                    qrs.push_back(false);
                } else {
                    qrs.push_back(true);
                }
                counter++;
            }
        }
    }

    vector<int>().swap(duration);
    vector<int>().swap(rWaveIndex);

    return qrs;
}

/**
 * Vrati pocet celych namerenych srdecnich cyklu (R-R)
 * @brief AnalyserEKG::getNumberOfCycles
 * @return pocet celych namerenych srdecnich cyklu
 */
unsigned int AnalyserEKG::getNumberOfCycles() {
    vector<int> duration = getRRIntervalDuration();
    unsigned int number = (unsigned int)duration.size();
    vector<int>().swap(duration);

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

    if ((int)interval.size() != 0) {
        duration = duration / (float)interval.size();
    }
    vector<int>().swap(interval);

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

/**
 * Vrati procento pravidelnych srdecnich cyklu.
 * @brief AnalyserEKG::getRegularityPercentage
 * @return procento pravidelnych srdecnich cyklu
 */
float AnalyserEKG::getRegularityPercentage() {
    vector<int> duration = getRRIntervalDuration();
    int i;
    int counter = 0;
    float percentage;

    for (i = 0; i < (int)duration.size(); i++) {
        if ((duration[i] / (float)DATA_SEC) * 60.0 < 60.0 ||
                (duration[i] / (float)DATA_SEC) * 60.0 > 100.0) {
            counter++;
        }
    }

    if ((int)duration.size() == 0) {
        percentage = 0;
    } else {
        percentage = 100.0 * (float)counter / (int)duration.size();
    }
    vector<int>().swap(duration);

    return percentage;
}

/**
 * Analyzuje EKG z hlediska delky trvani QRS komplexu
 * a jeho amplitudy.
 * @brief AnalyserEKG::analyse
 */
void AnalyserEKG::analyse() {
    int i, countTrue = 0;
    vector<bool> qrs = analyseQRS();

    int size = (int)qrs.size();
    for (i = 0; i < size; i++) {
        if (qrs[i] == true) {
            countTrue++;
        }
    }

    if (size == 0) {
        normalityPercentage = 0.0;
    } else {
        normalityPercentage = 100.0 * (float)countTrue / (float)size;
    }

    vector<bool>().swap(qrs);
}

AnalyserEKG::~AnalyserEKG() {
    delete transcriber;
}

