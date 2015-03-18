 // If you have 1 or more bluetooth dongles attached to the system.

// this will select the first one, then it will perform a scan for

// all devices within range of that dongle and print out all the

// information available about each device. then move on to the next

// dongle and repeat the process, etc. doesn't actually DO much apart

// from find devices and display their information.


#include <stdlib.h>

#include <stdio.h>

// Link to ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#include <Winsock2.h>

#include <Ws2bth.h>

// Link to Bthprops.lib
#pragma comment(lib, "Bthprops.lib")

#include <BluetoothAPIs.h>



BLUETOOTH_FIND_RADIO_PARAMS m_bt_find_radio = {sizeof(BLUETOOTH_FIND_RADIO_PARAMS)};



BLUETOOTH_RADIO_INFO m_bt_info = {sizeof(BLUETOOTH_RADIO_INFO),0,};



BLUETOOTH_DEVICE_SEARCH_PARAMS m_search_params = {

  sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),

  1,

  0,

  1,

  1,

  1,

  15,

  NULL

};



BLUETOOTH_DEVICE_INFO m_device_info = {sizeof(BLUETOOTH_DEVICE_INFO),0,};



// Note:

// Radio - is the thing plugged in/attached to the local machine.

// Device - is the thing that is connected to via the Bluetooth connection.



int main(int argc, char **args)

{

            HANDLE m_radio = NULL;

            HBLUETOOTH_RADIO_FIND m_bt = NULL;

            HBLUETOOTH_DEVICE_FIND m_bt_dev = NULL;

            int m_radio_id;

            int m_device_id;

            DWORD mbtinfo_ret;



            // Iterate for available bluetooth radio devices in range

            // Starting from the local

            while(TRUE)

            {

                        m_bt = BluetoothFindFirstRadio(&m_bt_find_radio, &m_radio);



                        if(m_bt != NULL)

                                    printf("BluetoothFindFirstRadio() is OK!\n");

                        else

                                    printf("BluetoothFindFirstRadio() failed with error code %d\n", GetLastError());



                        m_radio_id = 0;



                        do {

                                    // Then get the radio device info....

                                    mbtinfo_ret = BluetoothGetRadioInfo(m_radio, &m_bt_info);

                                    if(mbtinfo_ret == ERROR_SUCCESS)

                                                printf("BluetoothGetRadioInfo() looks fine!\n");

                                    else

                                                printf("BluetoothGetRadioInfo() failed wit herror code %d\n", mbtinfo_ret);



                                    wprintf(L"Radio %d:\r\n", m_radio_id);

                                    wprintf(L"\tInstance Name: %s\r\n", m_bt_info.szName);

                                    wprintf(L"\tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n", m_bt_info.address.rgBytes[5],

                                                m_bt_info.address.rgBytes[4], m_bt_info.address.rgBytes[3], m_bt_info.address.rgBytes[2],

                                                    m_bt_info.address.rgBytes[1], m_bt_info.address.rgBytes[0]);

                                    wprintf(L"\tClass: 0x%08x\r\n", m_bt_info.ulClassofDevice);

                                    wprintf(L"\tManufacturer: 0x%04x\r\n", m_bt_info.manufacturer);



                                    m_search_params.hRadio = m_radio;

                                    ZeroMemory(&m_device_info, sizeof(BLUETOOTH_DEVICE_INFO));

                                    m_device_info.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);



                                    // Next for every radio, get the device

                                    m_bt_dev = BluetoothFindFirstDevice(&m_search_params, &m_device_info);



                                    if(m_bt_dev != NULL)

                                                printf("\nBluetoothFindFirstDevice() is working!\n");

                                    else

                                                printf("\nBluetoothFindFirstDevice() failed with error code %d\n", GetLastError());



                                    m_radio_id++;

                                    m_device_id = 0;



                                    // Get the device info

                                    do

                                    {

                                                wprintf(L"\n\tDevice %d:\r\n", m_device_id);

                                                wprintf(L"  \tInstance Name: %s\r\n", m_device_info.szName);

                                                wprintf(L"  \tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n", m_device_info.Address.rgBytes[5],

                                                            m_device_info.Address.rgBytes[4], m_device_info.Address.rgBytes[3], m_device_info.Address.rgBytes[2],

                                                            m_device_info.Address.rgBytes[1], m_device_info.Address.rgBytes[0]);

                                                wprintf(L"  \tClass: 0x%08x\r\n", m_device_info.ulClassofDevice);

                                                wprintf(L"  \tConnected: %s\r\n", m_device_info.fConnected ? L"true" : L"false");

                                                wprintf(L"  \tAuthenticated: %s\r\n", m_device_info.fAuthenticated ? L"true" : L"false");

                                                wprintf(L"  \tRemembered: %s\r\n", m_device_info.fRemembered ? L"true" : L"false");

                                                m_device_id++;



                                                // Well, the found device information can be used for further socket

                                                // operation such as creating a socket, bind, listen, connect, send, receive etc..

                                                 // If no more device, exit the loop

                                                if(!BluetoothFindNextDevice(m_bt_dev, &m_device_info))

                                                            break;



                                    } while(BluetoothFindNextDevice(m_bt_dev, &m_device_info));



                                    // NO more device, close the device handle

                                    if(BluetoothFindDeviceClose(m_bt_dev) == TRUE)

                                                printf("\nBluetoothFindDeviceClose(m_bt_dev) is OK!\n");

                                    else

                                                printf("\nBluetoothFindDeviceClose(m_bt_dev) failed with error code %d\n", GetLastError());



                        } while(BluetoothFindNextRadio(&m_bt_find_radio, &m_radio));



                        // No more radio, close the radio handle

                        if(BluetoothFindRadioClose(m_bt) == TRUE)

                                    printf("BluetoothFindRadioClose(m_bt) is OK!\n");

                        else

                                    printf("BluetoothFindRadioClose(m_bt) failed with error code %d\n", GetLastError());



                        // Exit the outermost WHILE and BluetoothFindXXXXRadio loops if there is no more radio

                        if(!BluetoothFindNextRadio(&m_bt_find_radio, &m_radio))

                                    break;



                        // Give some time for the 'signal' which is a typical for crap wireless devices

                        Sleep(1000);

            }

            return 0;

}