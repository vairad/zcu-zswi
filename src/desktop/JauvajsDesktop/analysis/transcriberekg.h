#ifndef TRANSCRIBEREKG_H
#define TRANSCRIBEREKG_H
#include <vector>

using namespace std;

/**
 * Prepisovac krivky EKG na retezec znaku.
 * @brief The TranscriberEKG class
 */
class TranscriberEKG {

public:
    explicit TranscriberEKG(float data[], int size);
    void setData(float data[], int size);
    void transcribeData();
    vector<char> getString();
    ~TranscriberEKG();
<<<<<<< HEAD
    vector<float> data;
    vector<char> transcribedData;

private:
    int dataSize;
    float soaring; /* prudke stoupani */
    float diving; /* prudke klesani */
    float up; /* stoupani */
    float down; /* klesani */
=======
    float data[];
    //char transcribedData[];
>>>>>>> 3dc8e5b5580f10b96d039bbae8c9aa02a4dd0da5
};

#endif // TRANSCRIBEREKG_H
