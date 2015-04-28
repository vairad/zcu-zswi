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

    vector<int> getRRIntervalDuration();
    vector<int> getPWaveDuration();
    vector<int> getQWaveDuration();
    vector<int> getPRIntervalDuration();
    vector<int> getQRSDuration();


    vector<bool> analyseQWave();
    vector<bool> analyseQRS();
    vector<bool> analysePRInterval();
    vector<bool> analysePWave();

    float normalityPercentage;
    int firstRWaveIndex;

    TranscriberEKG *transcriber;
    vector<char> string;
    vector<float> differences;
};

#endif // ANALYSEREKG_H
