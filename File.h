#ifndef __FILE_H__
#define __FILE_H__
#include <windows.h>
#include <stdint.h>
#include <string>
#define SIZE_OF_NAME 100

using namespace std;
struct File {
    int parentID; //Dia chi sector thu muc cha
    int ID; //Dia chi sector chinh no
    wstring name; // Ten tap tin
    wstring content; // Noi dung tap tin
    int size; //Kich thuoc tap tin
    int state; // Trang thai tap tin
};

#endif

