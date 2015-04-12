#include "transcriberekg.h"

/**
 * Konstruktor nastavi data k prepsani.
 * Pri vytvoreni instance Transcriberu nedochazi
 * k samotnemu prepsani na charakteristicky retezec.
 * @brief TranscriberEKG::TranscriberEKG
 * @param data data k prepsani
 * @param size pocet hodnot v poli
 */
TranscriberEKG::TranscriberEKG(float data[], int size) {
    this->dataSize = size;
    setData(data, dataSize);
}

/**
 * "Prepise" rozdil hodnot na jedno pismeno
 * v charakteristickem retezci.
 * @brief TranscriberEKG::transcribeValue
 * @param value rozdil hodnot
 * @return pismeno dle rustu/poklesu krivky
 * S (SOARING) - prudke stoupani
 * V (DIVING) - prudke klesani
 * U (UP) - mirne stoupani
 * D (DOWN) - mirne klesani
 * C (CONSTANT) - temer konstantni
 */
char TranscriberEKG::transcribeValue(float value) {
    if (value >= SOARING) {
        return 'S';
    } else if (value <= DIVING) {
        return 'V';
    } else if (value >= UP && value < SOARING) {
        return 'U';
    } else if (value <= DOWN && value > DIVING) {
        return 'D';
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

    if(data.empty()) {
        return;
    }

    for (i = 0; i < dataSize; i++) {
        if (i+1 < dataSize) {
            valueDifferences.push_back(data[i+1] - data[i]);
            section = isSection(from, i);
            if (section == true) {
                from = i;
            }
          //  character = transcribeValue(valueDifferences[i]);
          //  transcribedData.push_back(character);
        }
    }
}


void TranscriberEKG::setData(float data[], int size) {
    int i;
    this->dataSize = size;

    for (i = 0; i < dataSize; i++) {
        this->data.push_back(data[i]);
    }
}

vector<char> TranscriberEKG::getString() {
    return transcribedData;
}

vector<float> TranscriberEKG::getData() {
    return data;
}

TranscriberEKG::~TranscriberEKG() {

}
