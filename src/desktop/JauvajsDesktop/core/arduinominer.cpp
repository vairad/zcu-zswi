#include "ArduinoMiner.h"
#include <Winsock2.h>
#include <Windows.h>
#include <BluetoothAPIs.h>
#include <Ws2bth.h>
#include <QtCore>
#include <QtSerialPort/QSerialPort>


ArduinoMiner::ArduinoMiner(QObject *parent): QThread(parent){

}

void ArduinoMiner::init(){
    serial = new QSerialPort(this);
    serial->setPortName("COM21");
    serial->open(QIODevice::ReadOnly);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    QObject::connect(serial,SIGNAL(readyRead()),this,SLOT(readSerial()));
    //connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
    emit ZmenaStavu("Port otevřený");
}

void ArduinoMiner::readSerial(){

    qDebug() << "###"+serial->readAll()+"###";

   // QByteArray byteArray =
   //     emit ZmenaStavu(QString(byteArray.length()));
   // else
       // emit ZmenaStavu("nic");
}

void ArduinoMiner::navazSpojeni()
{

}

void ArduinoMiner::UkonciSpojeni(){
    serial->close();
    emit ZmenaStavu("Port uzavřen");
}

void ArduinoMiner::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
       // m_standardOutput << QObject::tr("An I/O error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
       emit ZmenaStavu("Chyba");
       QCoreApplication::exit(1);
    }
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
       emit ZmenaStavu("Nalezeno: "+nalezeneZarizeni);
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

void ArduinoMiner::otevreniSoketu(){
    WSADATA wsaData;
    err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (err)
     emit ZmenaSpojeni("WSAStartup error = "+ err);// << endl;

     emit ZmenaSpojeni("Vytvářím soket");// << endl;
    // vytvoření BT socketu
    soket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    SOCKADDR_BTH btSockAddr;
    btSockAddr.addressFamily = AF_BTH;
    btSockAddr.btAddr = btDeviceInfo.Address.ullLong;
    btSockAddr.serviceClassId = RFCOMM_PROTOCOL_UUID; //SerialPortServiceClass_UUID (no difference)
    btSockAddr.port = BT_PORT_ANY;
    err = ::connect(soket, reinterpret_cast<SOCKADDR*>(&btSockAddr), sizeof(SOCKADDR_BTH));
}


void ArduinoMiner::navazaniSoketu(){
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


   err = 0;

    if (err != ERROR_SUCCESS)
    {
        err = GetLastError();
        emit ZmenaSpojeni("BluetoothRegisterForAuthentication Error");// << err << endl;
    }
}

void ArduinoMiner::zacniNaslouchat(){
    if (err)
    {
        DWORD wsaErr = WSAGetLastError();
        emit ZmenaSpojeni("connect error = "+ wsaErr );//<< std::endl;
    }
    else
    {

        emit ZmenaSpojeni("Připojeno");

        int recvbuflen = 100;
        char recvbuf[100] = "";
        int iResult;

        do{ // smyčka pro příjem dat
          //emit PrijmiData("Test naslouchání je úspěšný");
          iResult = recv(soket, recvbuf, recvbuflen, 0);

          if (iResult > 0)
              emit PrijmiData((QString)recvbuf);
          else if ( iResult == 0 )
              emit ZmenaStavu("Spojení uzavřeno");
          else
               emit ZmenaStavu("Chyba příjmu dat, "+WSAGetLastError());

          if(this->stav != STATUS_SPOJENI)
             break;

        } while( iResult > 0); // konec smyčky pro příjem dat

        this->UkonciSpojeni();

        if (err){
            emit ZmenaStavu("Chyba při zavírání soketu: " + err );//<< std::endl;
        }
        emit ZmenaSpojeni("Nepřipojeno");
    }
    WSACleanup();
}

int ArduinoMiner::OdesliData(QString data){

   const char* sendbuf = data.toLatin1().data();
   int iResult = send( this->soket, sendbuf, (int)strlen(sendbuf), 0 );
   if (iResult == SOCKET_ERROR) {
      emit ZmenaStavu("Odesílání selhalo, error: "+QString::number(WSAGetLastError()));
      ::closesocket(this->soket);
      WSACleanup();
      return 1;
   }
   emit ZmenaStavu("Odesláno: "+data);
   return 0;
}



ArduinoMiner::~ArduinoMiner(){

}

