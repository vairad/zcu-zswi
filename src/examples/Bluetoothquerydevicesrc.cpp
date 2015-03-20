#include <winsock2.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>
#include <stdio.h>

#define MAX_NAME 248

typedef ULONGLONG bt_addr, *pbt_addr, BT_ADDR, *PBT_ADDR;


union {
	// Storage for returned struct
	CHAR buf[5000];
	// properly align buffer to BT_ADDR requirements
	SOCKADDR_BTH _Unused_;
} butuh;

//------------------------------------------------------------------------
// Function: FindingBtDevices
// Purpose: Performs a device inquiry displays the device name in a console
//------------------------------------------------------------------------
BOOL FindingBtDevices()
{
	WSAQUERYSET wsaq;
	HANDLE hLookup;
	LPWSAQUERYSET pwsaResults;
	DWORD dwSize;
	BOOL bHaveName;
	BT_ADDR btAddr;
	DWORD dwNameSpace;
	
	pwsaResults = (LPWSAQUERYSET) butuh.buf;
	dwSize  = sizeof(butuh.buf);
	
	ZeroMemory(&wsaq, sizeof(wsaq));
	wsaq.dwSize = sizeof(wsaq);
	// namespace MUST be NS_BTH for bluetooth queries
	wsaq.dwNameSpace = NS_BTH;
	wsaq.lpcsaBuffer = NULL;

	printf("\n");
	// initialize searching procedure
	if (WSALookupServiceBegin(&wsaq, LUP_CONTAINERS, &hLookup) == SOCKET_ERROR)
	{
		printf("WSALookupServiceBegin() selhal %d\r\n", WSAGetLastError());
		return FALSE;
	}
	else
		printf("WSALookupServiceBegin() sluzba je OK!\n");

	ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
	pwsaResults->dwSize = sizeof(WSAQUERYSET);
	pwsaResults->dwNameSpace = NS_BTH;
	pwsaResults->lpBlob = NULL;


	wprintf(L"\n\nName\tNAP Address\tSAP Address\tName Space\n");

	// iterate through all found devices, returning name and address
	while (WSALookupServiceNext(hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR,&dwSize, pwsaResults) == 0)
	{
		btAddr = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
		// Verify the returned name
		bHaveName = (pwsaResults->lpszServiceInstanceName) && *(pwsaResults->lpszServiceInstanceName);
		
		dwNameSpace = pwsaResults->dwNameSpace;
		// print name and address
		wprintf (L"%s\t0X%04X\t\t0X%08X\t0X%0X\n", pwsaResults->lpszServiceInstanceName, GET_NAP(btAddr), GET_SAP(btAddr),dwNameSpace);
		
		
		//int neco = strcmp(pwsaResults->lpszServiceInstanceName, "Eflyax");
		//wprintf(L"%s ### %d\n", pwsaResults->lpszServiceInstanceName, neco);

	

	}
	
	if(WSALookupServiceEnd(hLookup) == 0)
		printf("\n\nWSALookupServiceEnd(hLookup) is OK!\n");
	else
		printf("WSALookupServiceEnd(hLookup) failed with error code %ld\n",WSAGetLastError());
	return TRUE;
}

int main(int argc, char **argv)
{
	WSADATA wsd;
	BOOL retVal;
	
	if(WSAStartup(MAKEWORD(2,2), &wsd) != 0)
		printf("WSAStartup() skoncil s chybou %ld\n", WSAGetLastError());
	else
		printf("WSAStartup() je OK!\n");

	retVal = FindingBtDevices();

	if (retVal == FALSE)
		printf("\nNenalezeno zadne zarizeni!\n");
	else
		printf("\nSuper, byla nalezena nejaka zarizeni!\n");

	if(WSACleanup() == 0)
		printf("WSACleanup() je OK!\n");
	else
		printf("WSACleanup() skoncil s chybou %ld\n", WSAGetLastError());

	system("pause"); 
	return 0;
	
}
