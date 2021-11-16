#ifndef __HEADER_MFT_H__
#define __HEADER_MFT_H__
#include <windows.h>
#include <stdint.h>
#include "FileNameData.h"


struct headerMFT {
    uint8_t signal_MFT_entry[4]; //dau hieu nhan biet MFT entry: FILE
    uint8_t offset_update_sequence[2];
    uint8_t sizeeof_fixup[2];
    uint8_t LSN[8]; //$LogFile Sequence Number
    uint8_t sequence_number[2];
    uint8_t reference_count[2];
    uint8_t start_attribute_offset[2];
    uint8_t flags[2];
    uint8_t used_byte_in_MFTentry[4];
    uint8_t size_of_disk_for_MFT_entry[4];
    uint8_t base_MFT_record[8];
    uint8_t next_attribute_id[2];
};
struct headerAttribute{
    uint8_t attribute_type[4]; //ma loai attribute
    uint8_t length[4]; //Kich thuoc attribute bao gom ca header
    uint8_t non_resident_flag;
    uint8_t name_length; //Chieu dai ten attribute
    uint8_t offset_to_the_name[2];
    uint8_t flags[2];
    uint8_t attribute_id[2];
    uint8_t size_of_data[4]; //Kich thuoc phan noi dung cua attribute neu attribute kieu resident
    uint8_t offset_data[2]; //Offset bat dau cua phan noi dung
};
void readMFTEntryHeader(BYTE entry[1024], uint32_t& first_MFT_sector, uint32_t& entry_readpoint, FileNameData& FND, headerMFT& header_mft_entry, uint32_t& size_of_name);
void readAttributeHeader(BYTE entry[1024], uint32_t firstAttributeOffset,uint32_t& size_of_data, uint32_t& offset_data);
int checkCondition(uint32_t flags, uint32_t name_space, uint32_t value_of_flags);
void printMFTEntryInfo(FileNameData FND, headerMFT header_mft_entry, uint32_t first_MFT_sector, uint32_t entry_readpoint, uint32_t size_of_name);

#endif

