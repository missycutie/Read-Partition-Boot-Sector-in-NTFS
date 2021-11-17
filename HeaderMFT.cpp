#include "HeaderMFT.h"
#include "helper.h"
#include "FileNameData.h"
using namespace std;
void readAttributeHeader(BYTE entry[1024], uint32_t firstAttributeOffset,uint32_t& size_of_data, uint32_t& offset_data){
    BYTE headerAttr[22];
    for (int i = 0, j = firstAttributeOffset;i < 22, j < firstAttributeOffset + 22; i++, j++){
        headerAttr[i] = entry[j];
        
    }
    // for (int i = 0; i < 22; i++){
    //     cout << toHex(headerAttr[i]) << " " ;
        
    // }
    headerAttribute header_attribute;
    // cout << endl;
    memcpy(&header_attribute, headerAttr, sizeof(headerAttribute));
    size_of_data = convertBytesToInt(header_attribute.size_of_data,4);
    offset_data = convertBytesToInt(header_attribute.offset_data,2);
}
int checkCondition(uint32_t flags, uint32_t name_space, uint32_t value_of_flags){
    if (flags != 0 && flags != 2 && name_space != 0 && (value_of_flags == 32 || value_of_flags == 268435456)) {
        return 1;
    }
    else return 0;
}
void printMFTEntryInfo(FileNameData FND, uint32_t first_MFT_sector, uint32_t entry_readpoint, uint32_t size_of_name ){
    cout << "ten tap tin la : ";
    for (int i = 0; i < size_of_name; i++){
        cout << FND.namefile[i] << " ";
    }
    cout << endl;
    // cout << size_of_data_file_name << " " << offset_data_file_name << endl;

    cout << "Kieu dinh dang cho namespace: " << (int)FND.name_space << endl;
    cout << "Chieu dai ten tap tin: " << (int)FND.length_of_name << endl;
    cout <<convertBytesToInt(FND.parent_folder_MFT_entry,8) << endl;
    if (convertBytesToInt(FND.value_of_flags,4) == 32) {
        cout << "Trang thai: Tap tin " << endl;
        cout << "co bao: " << convertBytesToInt(FND.value_of_flags, 4) << endl;
        cout << "Index: " << 6480 + convertBytesToInt(FND.parent_folder_MFT_entry, 8)*2 << endl;

    }
    if (convertBytesToInt(FND.value_of_flags,4) == 268435456){
        cout << "Trang thai: Thu muc " << endl;
        cout << "co bao: " << convertBytesToInt(FND.value_of_flags, 4) << endl;
        cout << "Index: " << first_MFT_sector + convertBytesToInt(FND.parent_folder_MFT_entry, 8)*2 << endl;
    }
    // cout << "flag : " << convertBytesToInt(header_mft_entry.flags,2) << endl;
    // cout << "Sequence number : " << convertBytesToInt(header_mft_entry.sequence_number,2) << endl;
    cout << "sector bat dau la : " << entry_readpoint << endl;
    cout << " ----------------------------" << endl;

}
void readMFTEntryHeader(BYTE entry[1024], uint32_t& first_MFT_sector, FileNameData& FND, headerMFT& header_mft_entry, uint32_t& size_of_name){
    BYTE headerMFTEntry[42];
    for (int i = 0; i < 42; i++){
        headerMFTEntry[i] = entry[i];

    }
    memcpy(&header_mft_entry, headerMFTEntry, sizeof(headerMFT));
    uint32_t firstAttributeOffset = convertBytesToInt(header_mft_entry.start_attribute_offset, 2);
    uint32_t size_of_data_standard_information, offset_data_standard_information;
    uint32_t size_of_data_file_name, offset_data_file_name;

    readAttributeHeader(entry, firstAttributeOffset,size_of_data_standard_information, offset_data_standard_information);
    // cout << "\nByte dau tien cua Attribute Standard Information: "<< firstAttributeOffset << endl;
  
    uint32_t attributeFileName = firstAttributeOffset + size_of_data_standard_information + offset_data_standard_information;
    // cout << size_of_data_standard_information << " " << offset_data_standard_information << endl;
    // cout << "Co non-resident-flag: " << (int)header_attribute.non_resident_flag << endl;
    // cout << "Byte dau tien cua file name: " << attributeFileName << endl;
    readAttributeHeader(entry, attributeFileName, size_of_data_file_name, offset_data_file_name);

    size_of_name = size_of_data_file_name - 66;

    BYTE file_name_data[size_of_data_file_name];
    int sD = offset_data_file_name + attributeFileName;
    int eD = sD + size_of_data_file_name;
    for (int i = 0, j = sD; i < size_of_data_file_name, j < eD; i++, j++){
        file_name_data[i] = entry[j];
    }
    memcpy(&FND, file_name_data, sizeof(FileNameData));    
}


