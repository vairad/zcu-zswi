#include "ArduinoMiner.h"
#include <Winsock2.h>
#include <Windows.h>
#include <BluetoothAPIs.h>
#include <Ws2bth.h>
#include <QtCore>

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

    switch (this->stav)
    {
    case STATUS_HLEDEJ:
        this->hledejOkolniZarizeni();
        break;
    case STATUS_SPOJENI:
        this->navazSpojeni();
        break;
    }

}

void ArduinoMiner::hledejOkolniZarizeni()
{
    QTime time;
    time.start();
    emit ZmenaStavu("Hledám zařízení...");

    this->deviceHandle = BluetoothFindFirstDevice(&this->btSearchParams, &this->btDeviceInfo);
    while (true || BluetoothFindNextDevice(&this->deviceHandle, &this->btDeviceInfo))
    {
       QString nalezeneZarizeni = QString::fromWCharArray(this->btDeviceInfo.szName);
       if(nalezeneZarizeni != "")
        this->ListNalezenychZarizeni.append(nalezeneZarizeni);
       emit SeznamChanged(&this->ListNalezenychZarizeni);
       msleep(250);
       if(!BluetoothFindNextDevice(deviceHandle, &btDeviceInfo)){ break; }
    }
    int rozdil = time.elapsed();

    QString BTerror;
    if(rozdil < 1000) BTerror = ", problém se zařízením Bluetooth";
    else BTerror = "";

    emit ZmenaStavu("Konec hledání" );
    emit SeznamChanged(&this->ListNalezenychZarizeni);
}

void ArduinoMiner::navazSpojeni()
{
    this->deviceHandle = BluetoothFindFirstDevice(&this->btSearchParams, &this->btDeviceInfo);
    while (true || BluetoothFindNextDevice(&this->deviceHandle, &this->btDeviceInfo))
    {
       if(QString::fromWCharArray(this->btDeviceInfo.szName) == this->vybraneZarizeni){
         break;
       }
       if(!BluetoothFindNextDevice(deviceHandle, &btDeviceInfo)){ break; }
    }

    if (this->deviceHandle)
    {
        int res = BluetoothAuthenticateDeviceEx(NULL, NULL, &btDeviceInfo, NULL, MITMProtectionRequiredBonding);

        if (res == ERROR_CANCELLED)
           emit ZmenaSpojeni("The user aborted the operation.");// << endl;
        if (res == ERROR_INVALID_PARAMETER)
           emit ZmenaSpojeni("The device structure specified in pbdti is invalid."); // << endl;
        if (res == ERROR_NO_MORE_ITEMS)
           emit ZmenaSpojeni("Zařízení je spárované, navazuji spojení...");//
        if (res == ERROR_NOT_AUTHENTICATED)
           emit ZmenaSpojeni("The operation being requested was not performed because the user has not been authenticated.");//endl;
        if (res == ERROR_SUCCESS)
           emit ZmenaSpojeni("Spojeni úspěšně navázáno");

        HBLUETOOTH_AUTHENTICATION_REGISTRATION authCallbackHandle = NULL;

        int err = 0;// = BluetoothRegisterForAuthenticationEx(&btDeviceInfo, &authCallbackHandle, auth_callback_ex, NULL);

        if (err != ERROR_SUCCESS)
        {
            err = GetLastError();
            emit ZmenaSpojeni("BluetoothRegisterForAuthentication Error");// << err << endl;
        }

        /////////////// Socket
        WSADATA wsaData;
        err = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (err)
            emit ZmenaSpojeni("WSAStartup error = "+ err);// << endl;

         emit ZmenaSpojeni("Vytvářím soket");// << endl;
        // vytvoření BT socketu
        SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

        SOCKADDR_BTH btSockAddr;
        btSockAddr.addressFamily = AF_BTH;
        btSockAddr.btAddr = btDeviceInfo.Address.ullLong;
        btSockAddr.serviceClassId = RFCOMM_PROTOCOL_UUID; //SerialPortServiceClass_UUID (no difference)
        btSockAddr.port = BT_PORT_ANY;

        err = ::connect(s, reinterpret_cast<SOCKADDR*>(&btSockAddr), sizeof(SOCKADDR_BTH));

        if (err)
        {
            DWORD wsaErr = WSAGetLastError();
            emit ZmenaSpojeni("connect error = "+ wsaErr );//<< std::endl;
        }
        else
        {
            err = shutdown(s, SD_BOTH);

            emit ZmenaSpojeni("Připojeno");

            int recvbuflen = 10;
            char recvbuf[10] = "";
            int iResult;

            do{ // smyčka pro příjem dat
              iResult = recv(s, recvbuf, recvbuflen, 0);
              if (iResult > 0)
                  emit ZmenaSpojeni((QString)recvbuf+" bajtů přjato");
              else if ( iResult == 0 )
                  emit ZmenaSpojeni("Spojení uzavřeno serverem");
              else
                   emit ZmenaSpojeni("Chyba příjmu dat, "+WSAGetLastError());
            } while(iResult > 0);

            emit ZmenaSpojeni("Konec udržování spojení");

            err = closesocket(s);
            if (err)
            {
                emit ZmenaSpojeni("closesocket error = " + err );//<< std::endl;
            }
            emit ZmenaSpojeni("Nepřipojeno");
        }
        WSACleanup();
        ///////////////Socket

        BOOL ok = BluetoothUnregisterAuthentication(authCallbackHandle);
        if (!ok)
        {
            DWORD err = GetLastError();
            emit ZmenaSpojeni("BTUnregisterAuthentication Error" +err);
        }

        ok = BluetoothFindDeviceClose(deviceHandle);
        if (!ok)
        {
            DWORD err = GetLastError();
            emit ZmenaSpojeni("BluetoothDeviceClose Error" + err);
        }
    }
    else
    {
        DWORD err = GetLastError();
       emit ZmenaSpojeni("BluetoothFindFirstDevice Error" + err);
    }
}

ArduinoMiner::~ArduinoMiner(){

}

