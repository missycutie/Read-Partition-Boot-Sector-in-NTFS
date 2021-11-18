#ifndef __HELPER_H__
#define __HELPER_H__
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
using namespace std;

uint64_t convertBytesToInt(const BYTE bytes[], int n);
string toBinary(int n); // Convert from int to binary
string bitwise_complement(string strbit);  // Dao bit
string toHex(unsigned int decnum);
wstring convertBytesToWString(const uint8_t bytes[], int n) ;

#endif