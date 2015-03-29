#include "bluetooth.h"

Bluetooth::Bluetooth(){
}

Bluetooth::Bluetooth(int hodnota){
    this->_hodnota = hodnota;
}

int Bluetooth::getHodnota(){
    return this->_hodnota;
}

void Bluetooth::setHodnota(int cislo){
    this->_hodnota = cislo;
}





