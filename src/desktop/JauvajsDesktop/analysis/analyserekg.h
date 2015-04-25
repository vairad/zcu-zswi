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

    TranscriberEKG *transcriber;
};

#endif // ANALYSEREKG_H
