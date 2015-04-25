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
 * Zjisti, zda se nezmenilo znamenko v useku.
 * Pokud ano, usek uzavre, ulozi jeho delku
 * a rozdil krajnich hodnot do vektoru a vrati true.
 * Pokud se znamenko nezmenilo, vrati false
 * @brief TranscriberEKG::isSection
 * @param from index, kde usek zacina
 * @param to index, kde by eventualne mohl usek koncit
 * @return true, byl-li usek ukoncen
 *         false, nebyl-li usek ukoncen
 */
bool TranscriberEKG::isSection(int from, int to) {
    if ((valueDifferences[from] > 0 && valueDifferences[to] < 0) ||
            (valueDifferences[from] < 0 && valueDifferences[to] > 0)) {
        sectionLengths.push_back(to - from);
        sectionDifferences.push_back(data[to] - data[from]);
        return true;
    }
    return false;
}

/**
 * "Prepise" data na charakteristicky retezec znaku.
 * @brief TranscriberEKG::transcribeData
 */
void TranscriberEKG::transcribeData() {
    int i, from = 0;
    bool section;
    char character;

    if (data.empty()) {
        return;
    }

    for (i = 0; i < data.size(); i++) {
        if (i + 1 < data.size()) {
            valueDifferences.push_back(data[i + 1] - data[i]);
            section = isSection(from, i);
            if (section == true) {
                from = i;
            }

            character = valuesToScale(valueDifferences[i]);
            transcribedData.push_back(character);
        }
    }

    if (from < (i - 1) && i > 0) {
        sectionLengths.push_back((i - 1) - from);
        sectionDifferences.push_back(data[i - 1] - data[from]);
    }
}

/**
 * Nastavi data, ktera se maji prepsat na retezec.
 * @brief TranscriberEKG::setData
 * @param data data, ktera se maji prepsat
 */
void TranscriberEKG::setData(vector<float> data) {
    int i;

    for (i = 0; i < data.size(); i++) {
        this->data[i] = data[i];
    }
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

vector<float> TranscriberEKG::getSectionDifferences() {
    return sectionDifferences;
}

vector<int> TranscriberEKG::getSectionLengths() {
    return sectionLengths;
}

TranscriberEKG::~TranscriberEKG() {

}
