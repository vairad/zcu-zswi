#ifndef TRANSCRIBEREKG_H
#define TRANSCRIBEREKG_H
#include <vector>

#define SOARING 1 /* prudke stoupani, dolni mez */
#define DIVING -1 /* prudke klesani, horni mez */
#define UP 0.05 /* stoupani, dolni mez */
#define DOWN -0.05 /* klesani, horni mez */

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
    vector<float> getData();
    ~TranscriberEKG();

private:
    char transcribeValue(float value);
    bool isSection(int from, int to);

    vector<float> valueDifferences;
    vector<float> sectionDifferences;
    vector<int> sectionLengths;
    /** Prijata neprepsana data */
    vector<float> data;
    /** Charakteristicky retezec znaku (prepsana data) */
    vector<char> transcribedData;
    /** Velikost prijatych neprepsanych dat (pocet hodnot) */
    int dataSize;
};

#endif // TRANSCRIBEREKG_H
