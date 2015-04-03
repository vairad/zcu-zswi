#ifndef TRANSCRIBEREKG_H
#define TRANSCRIBEREKG_H

/**
 * Prepisovac krivky EKG na retezec znaku.
 * @brief The transcriberekg class
 */
class TranscriberEKG {

public:
    TranscriberEKG();
    void setData(float data[]);
    void transcribeData();
    char* getString();
    ~TranscriberEKG();
    float data[];
    char transcribedData[];
};

#endif // TRANSCRIBEREKG_H
