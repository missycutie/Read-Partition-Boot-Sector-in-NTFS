#ifndef __SECTOR_H__
#define __SECTOR_H__
#include "helper.h"
using namespace std;
int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFileW(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descrptori
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, readPoint*512, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        string a;
        int j = 0;
        printf("Success!\n");
        cout << "OFFSET:   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F" << endl; 
        for (int i = 0; i < 512; i++) {
            if (i % 16 == 0) {
                cout << endl;
                cout << toHex(i/16) <<"0   :  ";
            }
             
            cout << toHex(sector[i]) << " ";
        }
        
    }
    return 0;
}
#endif