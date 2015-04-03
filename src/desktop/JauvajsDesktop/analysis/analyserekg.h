#ifndef ANALYSEREKG_H
#define ANALYSEREKG_H

/**
 * Analyzátor EKG.
 * @brief The analyserekg class
 */
class AnalyserEKG {

public:
    AnalyserEKG();
    void setFlag(char flag[]);
    void monitorFrequency();
    char* identifyDeviation();
    ~AnalyserEKG();
};

#endif // ANALYSEREKG_H
