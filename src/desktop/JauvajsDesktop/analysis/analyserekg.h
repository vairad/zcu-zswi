#ifndef ANALYSEREKG_H
#define ANALYSEREKG_H
#include <vector>

#include "analysis/transcriberekg.h"

/* pocet prijatych hodnot za sekundu */
#define DATA_SEC 50
/* maximum normalniho trvani QRS komplexu */
#define QRS_DURATION 0.12
/* minimalni normalni amplituda R vlny */
#define R_AMPLITUDE 1

using namespace std;

/**
 * Analyzátor EKG.
 * @brief The analyserekg class
 */
class AnalyserEKG {

public:
    explicit AnalyserEKG(vector<float> data);
    unsigned int getNumberOfCycles();
    float getAverageCycleDuration();
    float getNormalityPercentage();
    void analyse();
    ~AnalyserEKG();

private:
    vector<int> getRWaveIndex();

    float getRWaveAmplitude(int index);

    int getLeftRWaveDuration(int index);
    int getRightRWaveDuration(int index);
    int getSWaveDuration(int index);
    int getQWaveDuration(int index);

    vector<int> getRRIntervalDuration();
    vector<int> getQRSDuration();

    vector<bool> analyseQRS();

    float normalityPercentage;
    int firstRWaveIndex;

    TranscriberEKG *transcriber;
    vector<char> string;
    vector<float> differences;
};

#endif // ANALYSEREKG_H
