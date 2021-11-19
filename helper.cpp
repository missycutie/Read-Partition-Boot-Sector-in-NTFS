#include "helper.h"
uint64_t convertBytesToInt64(const BYTE bytes[], int n) {
    uint64_t res = 0;
    for (int i = n - 1; i >= 0; i--) {
        res = (res << 8) | bytes[i];
    }
    return res;
}

wstring toBinary(int n)
{
    wstring r;
    while(n!=0) {r=(n%2==0 ? L"0":L"1")+ r; n/=2;}
    return r;
}

wstring bitwise_complement(wstring strbit){
    for (int i = 0; i < strbit.length(); i++){
       strbit[i] = (strbit[i] == L'0' ? L'1' : L'0');
    }
    return strbit;
}



wstring toHex(unsigned int decnum) {
    wstring hexnum =  L"";
    int rem;
    while(decnum != 0)
    {
        rem = decnum % 16;
        if(rem < 10)
            rem = rem + L'0';
        else
            rem = rem - 10 + L'A';
        hexnum = (wchar_t)rem + hexnum;
        decnum = decnum / 16;
    }
    return hexnum.size() >= 2 ? hexnum : hexnum.size() == 1 ? L"0" + hexnum : L"00";
}
wstring convertBytesToWString(const uint8_t bytes[], int n) {
    wstring str = L"";
    for (int i = 0; i < n - 1; i += 2) {
        str += (wchar_t)convertBytesToInt64(bytes + i, 2);
    }
    return str;
}
wstring convertUnicodeHexCodeToCodePoint(vector<BYTE> bytes) {
    wstring result = L"";
    for (int i = 0; i < bytes.size(); i++) {
        if (bytes[i] < 0x80) { // unicode 1 byte
            result += (wchar_t)bytes[i];
        }
        else if (0xc2 <= bytes[i] && bytes[i] <= 0xdf) { // unicode 2 byte
            int number = (bytes[i] - 0xc2) * 64 + bytes[i + 1]; // sau mỗi 64 số thì tăng chỉ sô nhận biết lên 1, mò bảng unicode rồi tính ra được :) 
            wchar_t wch = (wchar_t)(number);
            result += wch;
            ++i;
        }
        else if (0xe0 <= bytes[i] && bytes[i] <= 0xef) { // unicode 3 bytes
            int number = (bytes[i] - 0xe0) * 0x1000 + (bytes[i + 1] - 0x80) * 64 + (bytes[i + 2] - 0x80); // mò bảng unicode rồi tính ra được :) 
            wchar_t wch = (wchar_t)(number);
            result += wch;
            i += 2;
        }
    }
    return result;
}
int ReadSector(LPCWSTR  drive, uint32_t readPoint, BYTE sector[512])
{
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

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
    
        printf("Success!\n");
        wcout << L"OFFSET:   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F" << endl; 
        for (int i = 0; i < 512; i++) {
            if (i % 16 == 0) {
                wcout << endl;
                wcout << toHex(i/16) << L"0   :  ";
            }
             
            wcout << toHex(sector[i]) << L" ";
        }
        
    }
    return 0;
}
void printTab(int tab) {
    for (int i = 0; i < tab; i++) {
        wcout << '\t';
    }
}
