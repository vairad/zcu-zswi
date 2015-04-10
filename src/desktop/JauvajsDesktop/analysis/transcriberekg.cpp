#include "transcriberekg.h"

TranscriberEKG::TranscriberEKG(float data[], int size) {
    this->dataSize = size;
    setData(data, dataSize);
}

void TranscriberEKG::setData(float data[], int size) {
    int i;
    for(i = 0; i < size; i++) {
        this->data.push_back(data[i]);
    }
}

void TranscriberEKG::transcribeData() {

}

<<<<<<< HEAD
vector<char> TranscriberEKG::getString() {
    return transcribedData;
}
=======
//char* getString() {

//}
>>>>>>> 3dc8e5b5580f10b96d039bbae8c9aa02a4dd0da5

TranscriberEKG::~TranscriberEKG() {

}

