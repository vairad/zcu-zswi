#include "transcriberekg.h"

TranscriberEKG::TranscriberEKG(vector<float> data, int size) {
    this->dataSize = size;
    setData(data, dataSize);
}

void TranscriberEKG::setData(vector<float> data, int size) {
    int i;
    for(i = 0; i < size; i++) {
        this->data.push_back(data[i]);
    }
}

void TranscriberEKG::transcribeData() {

}

vector<char> TranscriberEKG::getString() {
    return transcribedData;
}


TranscriberEKG::~TranscriberEKG() {

}
