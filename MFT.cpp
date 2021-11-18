#include "MFT.h"
#include "helper.h"
#include "FileNameData.h"
using namespace std;
void readAttributeHeader(BYTE entry[1024], int firstAttributeOffset,int& sizeofData, int& offsetData, int& length){
    BYTE headerAttr[22]; //size of header attribute = 22
    for (int i = 0, j = firstAttributeOffset;i < 22, j < firstAttributeOffset + 22; i++, j++){
        headerAttr[i] = entry[j];
    }

    headerAttribute header_attribute;
    memcpy(&header_attribute, headerAttr, sizeof(headerAttribute));

    length = convertBytesToInt(header_attribute.length,4); 
    sizeofData = convertBytesToInt(header_attribute.size_of_data,4);
    offsetData = convertBytesToInt(header_attribute.offset_data,2);
}

int checkCondition(int flags, int value_of_flags){ // Ham kiem tra dieu kien: Chi xuat neu la tap tin archieve hoac thu muc + tap tin chua bi xoa
    if (flags != 0 && flags != 2  && (value_of_flags == 32 || value_of_flags == 268435456)) {
        return 1;
     }
    return 0;
}
void printMFTEntryInfo(BYTE entry[1024],FileNameData FND, uint64_t first_MFT_sector, uint64_t entry_readpoint, uint64_t size_of_name, int attributeData, int size_of_data_data,int offset_data_data){
    int length; // length of attribute data
    cout << "Ten : ";
    for (int i = 0; i < size_of_name; i++){
        cout << FND.namefile[i] << " ";
    }
    cout << endl;
    if (convertBytesToInt(FND.value_of_flags,4) == 32){
        readAttributeHeader(entry, attributeData, size_of_data_data, offset_data_data, length);
        cout << "Kich thuoc tap tin la: " << size_of_data_data << " bytes" << endl;
        if (size_of_data_data == 0) {
            cout << "Tap tin nay rong !" << endl;
        }
        else{
            
            BYTE data[size_of_data_data];
            int sData = offset_data_data + attributeData;
            int eData = sData + size_of_data_data;
            for (int i = 0, j = sData; i < size_of_data_data, j < eData; i++, j++){
                data[i] = entry[j];
            }    
            char str[(sizeof data) + 1];
            memcpy(str, data, sizeof data);
            str[sizeof data] = 0; // Null termination.
            printf("Noi dung tap tin la: %s", str);
            cout<< endl;
        }

    }
    else {
        cout << "Kich thuoc thu muc = 0" << endl;
    }
    cout << "Kieu dinh dang cho namespace: " << (int)FND.name_space << endl;
    cout << "Chieu dai ten tap tin: " << (int)FND.length_of_name << endl;
    if (convertBytesToInt(FND.value_of_flags,4) == 32) {
        cout << "Trang thai: Tap tin " << endl;
    }
    if (convertBytesToInt(FND.value_of_flags,4) == 268435456){
        cout << "Trang thai: Thu muc " << endl;
        
    }
    cout << "Parent sector: " << first_MFT_sector +  convertBytesToInt(FND.parent_folder_MFT_entry, 4)*2<< endl;
    cout << "sector bat dau la : " << entry_readpoint << endl;
    cout << " ----------------------------" << endl;
}
void readMFTEntryHeader(BYTE entry[1024], uint64_t& first_MFT_sector, FileNameData& FND, headerMFT& header_mft_entry, uint64_t& size_of_name,int& attributeData){
    BYTE headerMFTEntry[42];
    for (int i = 0; i < 42; i++){
        headerMFTEntry[i] = entry[i];

    }
    memcpy(&header_mft_entry, headerMFTEntry, sizeof(headerMFT));

    int size_of_data_standard_information, offset_data_standard_information;
    int size_of_data_file_name, offset_data_file_name;
    int size_of_data_object_id, offset_data_object_id;

    int length1; // length of attribute standard information
    int length2; // length of attribute file name
    int length3; // length of attribute object id

    int firstAttributeOffset = convertBytesToInt(header_mft_entry.start_attribute_offset, 2); // attribute standard information
    readAttributeHeader(entry, firstAttributeOffset,size_of_data_standard_information, offset_data_standard_information,length1);

    int attributeFileName = firstAttributeOffset + length1;
    readAttributeHeader(entry, attributeFileName, size_of_data_file_name, offset_data_file_name, length2);

    int attributeObjectId = attributeFileName + length2;
    readAttributeHeader(entry, attributeObjectId, size_of_data_object_id, offset_data_object_id, length3);

    attributeData = attributeObjectId + length3;

    size_of_name = size_of_data_file_name - 66;
     
    BYTE file_name_data[size_of_data_file_name];
    int sFileName = offset_data_file_name + attributeFileName; //start of filename
    int eFileName = sFileName + size_of_data_file_name; // end of filename
    for (int i = 0, j = sFileName; i < 66, j < sFileName+66; i++, j++){
        file_name_data[i] = entry[j];
    }
    memcpy(&FND, file_name_data, sizeof(FileNameData));    
    for (int i = 0, j = sFileName + 66; i < size_of_name, j < eFileName; i++, j++){
        FND.namefile[i] = entry[j];
    }
}


