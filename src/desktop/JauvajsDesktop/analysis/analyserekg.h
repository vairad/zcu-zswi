#ifndef ANALYSEREKG_H
#define ANALYSEREKG_H
#include <vector>
#include "analysis/transcriberekg.h"

#define DATA_SEC 50 /* pocet prijatych hodnot za sekundu */

using namespace std;

/**
 * Analyzátor EKG.
 * @brief The analyserekg class
 */
class AnalyserEKG {

public:
    explicit AnalyserEKG(vector<float> data);
    void setFlag(char flag[]);
    void monitorFrequency();
    char* identifyDeviation();
    ~AnalyserEKG();

private:
    vector<float> getRRInterval();
    vector<float> getPWave();
    vector<int> getQWaveDuration();

    vector<bool> analyseQWave();
    vector<bool> analysePRInterval();

    TranscriberEKG *transcriber;
    vector<char> string;
};

#endif // ANALYSEREKG_H
