#include "transcriberekg.h"

/**
 * Konstruktor nastavi data k prepsani.
 * Pri vytvoreni instance Transcriberu nedochazi
 * k samotnemu prepsani na charakteristicky retezec.
 * @brief TranscriberEKG::TranscriberEKG
 * @param data data k prepsani
 */
TranscriberEKG::TranscriberEKG(vector <float> data) {
    setData(data);
}

/**
 * "Prepise" rozdil hodnot na jedno pismeno
 * v charakteristickem retezci.
 * @brief TranscriberEKG::transcribeValue
 * @param value rozdil hodnot
 * @return pismeno dle rustu/poklesu krivky
 * S (SOARING) - prudke stoupani
 * V (DIVING) - prudke klesani
 * U (UP) - stredni stoupani
 * D (DOWN) - stredni klesani
 * L (LIGHTLY UP) - mirne stoupani
 * E (EASILY DOWN) - mirne klesani
 * C (CONSTANT) - temer konstantni
 */
char TranscriberEKG::valuesToScale(float value) {
    if (value >= SOARING) {
        return 'S';
    } else if (value <= DIVING) {
        return 'V';
    } else if (value >= UP && value < SOARING) {
        return 'U';
    } else if (value <= DOWN && value > DIVING) {
        return 'D';
    } else if (value >= LIGHTLY_UP && value < UP) {
        return 'L';
    } else if(value <= EASILY_DOWN && value > DOWN) {
        return 'E';
    } else {
        return 'C';
    }
}

/**
 * "Prepise" data na charakteristicky retezec znaku.
 * @brief TranscriberEKG::transcribeData
 */
void TranscriberEKG::transcribeData() {
    int i;
    char character;

    if (data.empty()) {
        return;
    }

    for (i = 0; i < (int)data.size(); i++) {
        if (i + 1 < (int)data.size()) {
            valueDifferences.push_back(data[i + 1] - data[i]);

            character = valuesToScale(valueDifferences[i]);
            transcribedData.push_back(character);
        }
    }
}

/**
 * Nastavi data, ktera se maji prepsat na retezec.
 * @brief TranscriberEKG::setData
 * @param data data, ktera se maji prepsat
 */
void TranscriberEKG::setData(vector<float> data) {
   this->data = data;
}

vector<char> TranscriberEKG::getString() {
    return transcribedData;
}

vector<float> TranscriberEKG::getData() {
    return data;
}

vector<float> TranscriberEKG::getValueDifferences() {
    return valueDifferences;
}

TranscriberEKG::~TranscriberEKG() {
    vector<float>().swap(valueDifferences);
    vector<char>().swap(transcribedData);
}
