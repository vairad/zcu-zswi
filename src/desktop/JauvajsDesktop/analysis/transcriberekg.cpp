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
 * "Prepise" data na charakteristicky retezec znaku.
 * @brief TranscriberEKG::transcribeData
 */
void TranscriberEKG::transcribeData() {
    int i;
    float difference;
    char character;

    if(data.empty()) {
        return;
    }

    for(i = 0; i < dataSize; i++) {
        if (i+1 < dataSize) {
            difference = data[i+1] - data[i];
            character = transcribeValue(difference);
            transcribedData.push_back(character);
        }
    }
}


void TranscriberEKG::setData(float data[], int size) {
    int i;
    this->dataSize = size;

    for(i = 0; i < dataSize; i++) {
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
