#ifndef __FILENAME_DATA_H__
#define __FILENAME_DATA_H__
#include <windows.h>
#include <stdint.h>
#include <string>
#define SIZE_OF_NAME 100

using namespace std;
struct FileNameData {
    uint8_t parent_folder_MFT_entry[8]; //Dia chi entry thu muc cha
    uint8_t create_file_time[8]; //Thoi gian tao tap tin 
    uint8_t change_file_time[8]; //Thoi gian tap tin co thay doi  
    uint8_t change_MFT_entry_time[8]; //Thoi gian MFT entry co thay doi
    uint8_t lastest_access_file_time[8]; // Thoi gian truy cap tap tin moi nhat
    uint8_t no_used[8];
    uint8_t no_used1[8];
    uint8_t value_of_flags[4];
    uint8_t reparse_value[4];
    uint8_t length_of_name;
    uint8_t name_space;
    uint8_t namefile[SIZE_OF_NAME];
    uint8_t entry;
    uint8_t size_name;
};

#endif

