#include "analyserekg.h"

AnalyserEKG::AnalyserEKG(vector<float> data) {
    transcriber = new TranscriberEKG(data);
    transcriber->transcribeData();
}

/**
 * Spocita delku intervalu RR pro kazdy srdecni cyklus
 * @brief AnalyserEKG::getRRInterval
 * @return vektor delek intervalu RR v sekundach pro vsechny cele
 * namerene cykly.
 */
vector<float> AnalyserEKG::getRRInterval() {
    vector<float> interval;
    vector<char> string = transcriber->getString();
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

AnalyserEKG::~AnalyserEKG() {

}

