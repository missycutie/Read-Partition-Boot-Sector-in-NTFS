#ifndef __HELPER_H__
#define __HELPER_H__
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
using namespace std;

uint32_t convertBytesToInt(const BYTE bytes[], int n);
string toBinary(int n);
string bitwise_complement(string strbit);
string toHex(unsigned int decnum);
#endif