#include "transcriberekg.h"

TranscriberEKG::TranscriberEKG(float data[], int size) {
    this->dataSize = size;
    setData(data, dataSize);
}

void TranscriberEKG::setData(float data[], int size) {
    int i;
    this->dataSize = size;

    for(i = 0; i < dataSize; i++) {
        this->data.push_back(data[i]);
    }
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

void TranscriberEKG::transcribeData() {
    int i;
    float difference = 0.0;
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

vector<char> TranscriberEKG::getString() {
    return transcribedData;
}


TranscriberEKG::~TranscriberEKG() {

}
