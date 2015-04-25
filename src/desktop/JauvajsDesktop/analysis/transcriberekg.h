#ifndef TRANSCRIBEREKG_H
#define TRANSCRIBEREKG_H
#include <vector>

#define SOARING 1 /* prudke stoupani, dolni mez */
#define DIVING -1 /* prudke klesani, horni mez */
#define UP 0.1 /* stoupani, dolni mez */
#define DOWN -0.1 /* klesani, horni mez */
#define LIGHTLY_UP 0.01 /* lehke stoupani, dolni mez */
#define EASILY_DOWN -0.01 /* lehke klesani, horni mez */

#define DATA_SEC 50 /* pocet prijatych hodnot za sekundu */

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
    vector<float> getValueDifferences();
    vector<float> getSectionDifferences();
    vector<int> getSectionLengths();
    ~TranscriberEKG();

private:
    char valuesToScale(float value);
    bool isSection(int from, int to);

    /** Vektor rozdilu mezi dvema sousednimi hodnotami */
    vector<float> valueDifferences;
    /** Vektor rozdilu pocatecnich a koncovych hodnot jednotlivych useku */
    vector<float> sectionDifferences;
    /** Vektor delek jednotlivych useku */
    vector<int> sectionLengths;

    /** Prijata neprepsana data */
    vector<float> data;
    /** Charakteristicky retezec znaku (prepsana data, kde kazde pismeno znamena urcitou zmenu krivky) */
    vector<char> transcribedData;
    /** Velikost prijatych neprepsanych dat (pocet hodnot) */
    int dataSize;
};

#endif // TRANSCRIBEREKG_H
