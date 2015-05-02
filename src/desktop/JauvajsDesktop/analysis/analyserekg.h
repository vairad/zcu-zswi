#ifndef ANALYSEREKG_H
#define ANALYSEREKG_H
#include <vector>

#include "analysis/transcriberekg.h"

/* pocet prijatych hodnot za sekundu */
#define DATA_SEC 50

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
    int getLeftRWaveDuration(int index);
    float getRWaveAmplitude(int index);
    int getRightRWaveDuration(int index);
    int getSDuration(int index);
    int getQWaveDuration(int index);

    vector<int> getRRIntervalDuration();
    vector<int> getQWaveDuration();
    vector<int> getQRSDuration();

    vector<bool> analyseQWave();
    vector<bool> analyseQRS();

    float normalityPercentage;
    int firstRWaveIndex;

    TranscriberEKG *transcriber;
    vector<char> string;
    vector<float> differences;
};

#endif // ANALYSEREKG_H
