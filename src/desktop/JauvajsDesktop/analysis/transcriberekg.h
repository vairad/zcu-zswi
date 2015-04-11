#ifndef TRANSCRIBEREKG_H
#define TRANSCRIBEREKG_H
#include <vector>

#define SOARING 1 /* prudke stoupani, dolni mez */
#define DIVING -1 /* prudke klesani, horni mez */
#define UP 0.1 /* stoupani, dolni mez */
#define DOWN -0. /* klesani, horni mez */

using namespace std;

/**
 * Prepisovac krivky EKG na retezec znaku.
 * @brief The TranscriberEKG class
 */
class TranscriberEKG {

public:
    explicit TranscriberEKG(vector <float> data, int size);
    void setData(vector <float> data, int size);
    void transcribeData();
    vector<char> getString();
    ~TranscriberEKG();
    vector<float> data;
    vector<char> transcribedData;

private:
    int dataSize;
};

#endif // TRANSCRIBEREKG_H
