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
        this->findDevices();
        break;
    case STATUS_SPOJENI:
        this->beginConnection();
        break;
    }
}

void ArduinoMiner::findDevices()
{
    QTime time;
    time.start();
    emit changeStatus("Hledám zařízení...");

    this->deviceHandle = BluetoothFindFirstDevice(&this->btSearchParams, &this->btDeviceInfo);
    while (true || BluetoothFindNextDevice(&this->deviceHandle, &this->btDeviceInfo))
    {
       QString foundDevices = QString::fromWCharArray(this->btDeviceInfo.szName);
       emit changeStatus("Nalezeno: "+foundDevices);
       if(foundDevices != "")
        this->ListFoundDevices.append(foundDevices);
       emit ListChanged(&this->ListFoundDevices);
       msleep(250);
       if(!BluetoothFindNextDevice(deviceHandle, &btDeviceInfo)){ break; }
    }
    int rozdil = time.elapsed();

    QString BTerror;
    if(rozdil < 1000) BTerror = ", problém se zařízením Bluetooth";
    else BTerror = "";

    emit changeStatus("Konec hledání" );
    emit ListChanged(&this->ListFoundDevices);
}

void ArduinoMiner::beginConnection()
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
           emit ConnectionChanged("The user aborted the operation.");// << endl;
        if (res == ERROR_INVALID_PARAMETER)
           emit ConnectionChanged("The device structure specified in pbdti is invalid."); // << endl;
        if (res == ERROR_NO_MORE_ITEMS)
           emit ConnectionChanged("Zařízení je spárované, navazuji spojení...");//
        if (res == ERROR_NOT_AUTHENTICATED)
           emit ConnectionChanged("The operation being requested was not performed because the user has not been authenticated.");//endl;
        if (res == ERROR_SUCCESS)
           emit ConnectionChanged("Spojeni úspěšně navázáno");


       err = 0;

        if (err != ERROR_SUCCESS)
        {
            err = GetLastError();
            emit ConnectionChanged("BluetoothRegisterForAuthentication Error");// << err << endl;
        }
        WSADATA wsaData;
        err = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (err)
            emit ConnectionChanged("WSAStartup error = "+ err);

         emit ConnectionChanged("Vytvářím soket");
        // vytvoření BT socketu
        soket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

        SOCKADDR_BTH btSockAddr;
        btSockAddr.addressFamily = AF_BTH;
        btSockAddr.btAddr = btDeviceInfo.Address.ullLong;
        btSockAddr.serviceClassId = SerialPortServiceClass_UUID; //SerialPortServiceClass_UUID (no difference)
        btSockAddr.port = BT_PORT_ANY;

        err = ::connect(soket, reinterpret_cast<SOCKADDR*>(&btSockAddr), sizeof(SOCKADDR_BTH));

        if (err)
        {
            DWORD wsaErr = WSAGetLastError();
            emit ConnectionChanged("connect error = "+ wsaErr );//<< std::endl;
        }
        else
        {

            emit ConnectionChanged("Připojeno");

            int recvbuflen = 100;
            char recvbuf[100] = "";
            int iResult;

            do{ // smyčka pro příjem dat
              iResult = recv(soket, recvbuf, recvbuflen, 0);

              if (iResult > 0)
                  emit PrijmiData((QString)recvbuf);
              else if ( iResult == 0 )
                  emit changeStatus("Spojení uzavřeno");
              else
                   emit changeStatus("Chyba příjmu dat, "+WSAGetLastError());

              if(this->stav != STATUS_SPOJENI)
                 break;

            } while( iResult > 0); // konec smyčky pro příjem dat

            this->CloseConnection();

            if (err){
                emit changeStatus("Chyba při zavírání soketu: " + err );//<< std::endl;
            }
            emit ConnectionChanged("Nepřipojeno");
        }
        WSACleanup();
    }
    else
    {
       DWORD err = GetLastError();
       emit changeStatus("Chyba při hledání zařízení, Error" + err);
    }
}

int ArduinoMiner::SendData(QString data){

   const char* sendbuf = data.toLatin1().data();
   int iResult = send( this->soket, sendbuf, (int)strlen(sendbuf), 0 );
   if (iResult == SOCKET_ERROR) {
      emit changeStatus("Odesílání selhalo, error: "+QString::number(WSAGetLastError()));
      ::closesocket(this->soket);
      WSACleanup();
      return 1;
   }
   emit changeStatus("Odesláno: "+data);
   return 0;
}

void ArduinoMiner::CloseConnection(){
    this->stav = STATUS_KLID;
    this->err = shutdown(this->soket, SD_BOTH);
}

ArduinoMiner::~ArduinoMiner(){

}

