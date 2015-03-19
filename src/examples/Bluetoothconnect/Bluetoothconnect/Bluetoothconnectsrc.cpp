// Link to ws2_32.lib
#include <winsock2.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512

typedef ULONGLONG bt_addr, *pbt_addr, BT_ADDR, *PBT_ADDR;

int main(int argc, char **argv)
{
	WSADATA wsd;
	SOCKET s;
	SOCKADDR_BTH sab;
	// Hard coded directly, got it from the receiver/server

	BT_ADDR aSddr = 0X111AF7D4; // SAP adresa zaøízení (Arduina)

	int iResult;
	// This should be const void * type for non-char data
	char *sendbuf = "Test data from client...";
	int recvbuflen = DEFAULT_BUFLEN;
	// Change the type accordigly for non-char data
	char recvbuf[DEFAULT_BUFLEN] = "";

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("Unable to load Winsock! Error code is %d\n", WSAGetLastError());
		system("pause");
		return 1;
	}
	else
		printf("WSAStartup() is OK, Winsock lib loaded!\n");
	
	s = socket (AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	if (s == INVALID_SOCKET)
	{
		printf ("Socket creation failed, error %d\n", WSAGetLastError ());
	    WSACleanup();
		system("pause");
		return 1;
	}
	else
		printf ("socket() looks fine!\n");

	memset (&sab, 0, sizeof(sab));
	sab.addressFamily  = AF_BTH;
	// Set the btAddr member to a BT_ADDR variable that
	// contains the address of the target device. App
	// can accept the device address as a string but must convert
	// the address and store it in a variable of type BT_ADDR.
	sab.btAddr = aSddr;

	// If the service identifier is available, then set the
	// serviceClassId member of SOCKADDR_BTH to the GUID of
	// the RFCOMM-based service. In this case, the client
	// performs an SDP query and then uses the resulting server channel. 
	// sab.serviceClassId = nguiD;

	// Or If you want to use a hard-coded channel number, set the
	// port member of SOCKADDR_BTH to the server channel number (1-31)
	sab.port = 4;

	// Connect to the Bluetooth socket, created previously
	if (connect (s, (SOCKADDR *)&sab, sizeof(sab)) == SOCKET_ERROR){
		printf("connect() failed with error code %d\n", WSAGetLastError ());
		closesocket(s);
        WSACleanup();
		system("pause");
		return 1;
	}
	else
		printf("connect() should be fine!\n");

	// Send some data
	iResult = send(s, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send() failed with error code %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
		system("pause");
        return 1;
    }
	else
	{
		printf("send() is OK!\n");
		printf("Bytes Sent: %d\n", iResult);
	}

    // shutdown the stream connection since no more data will be sent
    iResult = shutdown(s, SD_SEND);
    if (iResult == SOCKET_ERROR)
	{
		printf("shutdown() failed with error code %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
		system("pause");
        return 1;
    }
	else
		printf("shutdown() is working!\n");
		
	// receive
	// Receive until the peer closes the connection
    do {
		iResult = recv(s, recvbuf, recvbuflen, 0);

        if (iResult > 0)
            printf(" %d Bytes received from sender\n", iResult);
        else if (iResult == 0)
            printf("Connection was closed by peer!\n");
        else
            printf("recv() failed with error code %d\n", WSAGetLastError());

    } while(iResult > 0);

	// Do all the cleanup
	if(closesocket(s) == 0)
		printf("closesocket() pretty fine!\n");
	if(WSACleanup() == 0)
	    printf("WSACleanup() is OK!\n");

	system("pause");
	return 0;
}
