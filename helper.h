#ifndef __HELPER_H__
#define __HELPER_H__
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
using namespace std;

uint64_t convertBytesToInt64(const BYTE bytes[], int n);
wstring toBinary(int n); // Convert from int to binary
wstring bitwise_complement(wstring strbit);  // Dao bit
wstring toHex(unsigned int decnum);
wstring convertBytesToWString(const uint8_t bytes[], int n) ;
wstring convertUnicodeHexCodeToCodePoint(vector<BYTE> bytes);
int ReadSector(LPCWSTR  drive, uint32_t readPoint, BYTE sector[512]);
void printTab(int tab);
#endif