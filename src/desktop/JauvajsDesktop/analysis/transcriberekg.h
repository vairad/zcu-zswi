#ifndef TRANSCRIBEREKG_H
#define TRANSCRIBEREKG_H
#include <vector>

/* prudke stoupani, dolni mez */
#define SOARING 0.5
/* prudke klesani, horni mez */
#define DIVING -0.5
/* stoupani, dolni mez */
#define UP 0.1
/* klesani, horni mez */
#define DOWN -0.1
 /* lehke stoupani, dolni mez */
#define LIGHTLY_UP 0.05
/* lehke klesani, horni mez */
#define EASILY_DOWN -0.05

using namespace std;

/**
 * Prepisovac krivky EKG na retezec znaku.
 * @brief The TranscriberEKG class
 */
class TranscriberEKG {

public:
    explicit TranscriberEKG(vector<float> data);
    void transcribeData();
    void setData(vector<float> data);
    vector<char> getString();
    vector<float> getData();
    vector<float> getValueDifferences();
    ~TranscriberEKG();

private:
    char valuesToScale(float value);

    /** Vektor rozdilu mezi dvema sousednimi hodnotami */
    vector<float> valueDifferences;
    /** Prijata neprepsana data */
    vector<float> data;
    /** Charakteristicky retezec znaku (prepsana data, kde kazde pismeno znamena urcitou zmenu krivky) */
    vector<char> transcribedData;
};

#endif // TRANSCRIBEREKG_H
