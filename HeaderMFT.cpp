#include "HeaderMFT.h"
#include "helper.h"
#include "FileNameData.h"
using namespace std;
void readAttributeHeader(BYTE entry[1024], uint32_t firstAttributeOffset,uint32_t& size_of_data, uint32_t& offset_data){
    BYTE headerAttr[22];
    for (int i = 0, j = firstAttributeOffset;i < 22, j < firstAttributeOffset + 22; i++, j++){
        headerAttr[i] = entry[j];
        
    }
    for (int i = 0; i < 22; i++){
        cout << toHex(headerAttr[i]) << " " ;
        
    }
    headerAttribute header_attribute;
    cout << endl;
    memcpy(&header_attribute, headerAttr, sizeof(headerAttribute));
    size_of_data = convertBytesToInt(header_attribute.size_of_data,4);
    offset_data = convertBytesToInt(header_attribute.offset_data,2);
}
void readMFTEntryHeader(BYTE entry[1024]){
    BYTE headerMFTEntry[42];
    for (int i = 0; i < 42; i++){
        headerMFTEntry[i] = entry[i];

    }
    headerMFT header_MFT_entry;
    memcpy(&header_MFT_entry, headerMFTEntry, sizeof(headerMFT));
    uint32_t firstAttributeOffset = convertBytesToInt(header_MFT_entry.start_attribute_offset, 2);
    uint32_t size_of_data_standard_information, offset_data_standard_information;
    uint32_t size_of_data_file_name, offset_data_file_name;

    readAttributeHeader(entry, firstAttributeOffset,size_of_data_standard_information, offset_data_standard_information);
    cout << "\nByte dau tien cua Attribute Standard Information: "<< firstAttributeOffset << endl;
  
    uint32_t attributeFileName = firstAttributeOffset + size_of_data_standard_information + offset_data_standard_information;
    cout << size_of_data_standard_information << " " << offset_data_standard_information << endl;
    // cout << "Co non-resident-flag: " << (int)header_attribute.non_resident_flag << endl;
    cout << "Byte dau tien cua file name: " << attributeFileName << endl;
    readAttributeHeader(entry, attributeFileName, size_of_data_file_name, offset_data_file_name);
    cout << size_of_data_file_name << " " << offset_data_file_name << endl;

    uint32_t size_of_name = size_of_data_file_name - 66;
    cout << "------------------" << endl;

    BYTE file_name_data[size_of_data_file_name];
    int sD = offset_data_file_name + attributeFileName;
    int eD = sD + size_of_data_file_name;
    for (int i = 0, j = sD; i < size_of_data_file_name, j < eD; i++, j++){
        file_name_data[i] = entry[j];
    }
    for (int i = 0; i <size_of_data_file_name; i++){
        cout << toHex(file_name_data[i]) << " " ;
        
    }
    FileNameData FND;
    cout << endl;
    cout << size_of_name << endl;
    memcpy(&FND, file_name_data, sizeof(FileNameData));
    for (int i = 0; i < size_of_name; i++){
        cout << FND.namefile[i] << " ";
    }
    

}
