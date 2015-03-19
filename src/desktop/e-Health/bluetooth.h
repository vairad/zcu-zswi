#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <winsock2.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>


class Bluetooth
{

private:
    int _hodnota;

public:
    Bluetooth();
    Bluetooth(int hodnota);
    int getHodnota();
    void setHodnota(int cislo);
};

#endif // BLUETOOTH_H
