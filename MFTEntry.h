#ifndef __MFT_ENTRY_H__
#define __MFT_ENTRY_H__
#include "helper.h"
using namespace std;
int ReadMFTEntry(LPCWSTR  drive, uint64_t readPoint, BYTE entry[1024])
{
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFileW(drive, // Drive to open
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

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, entry, 1024, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
    
        return 0;
        
    }
    return 0;
}
#endif