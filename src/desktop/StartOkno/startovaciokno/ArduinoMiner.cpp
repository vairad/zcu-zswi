#include "ArduinoMiner.h"
#include <Winsock2.h>
#include <Windows.h>
#include <BluetoothAPIs.h>
#include <Ws2bth.h>
#include <QtCore>
#include <QDebug>

ArduinoMiner::ArduinoMiner(QObject *parent): QThread(parent){

    this->btSearchParams.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
    this->btSearchParams.cTimeoutMultiplier = 5;  //5*1.28s search timeout
    this->btSearchParams.fIssueInquiry = true;
    //vyhledání všech známých i neznámých zařízení
    this->btSearchParams.fReturnAuthenticated = true;
    this->btSearchParams.fReturnConnected = true;
    this->btSearchParams.fReturnRemembered = true;
    this->btSearchParams.fReturnUnknown = true;
    this->btSearchParams.hRadio = NULL;
    ZeroMemory(&this->btDeviceInfo, sizeof(BLUETOOTH_DEVICE_INFO));   //"initialize" (&btDeviceInfo)
    this->btDeviceInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

}

void ArduinoMiner::run(){

  emit ZmenaStavu("Začínám hledat zařízení...");
  this->deviceHandle = BluetoothFindFirstDevice(&this->btSearchParams, &this->btDeviceInfo);
  while (true || BluetoothFindNextDevice(&this->deviceHandle, &this->btDeviceInfo))
  {
     this->ListNalezenychZarizeni.append(QString::fromWCharArray(this->btDeviceInfo.szName));
     emit SeznamChanged(&this->ListNalezenychZarizeni);
     msleep(250);
     if(!BluetoothFindNextDevice(deviceHandle, &btDeviceInfo)){ break; }
  }
  emit ZmenaStavu("Konec hledání");
}

ArduinoMiner::~ArduinoMiner(){

}

