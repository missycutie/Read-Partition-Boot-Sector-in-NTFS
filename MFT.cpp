#include "MFT.h"
#include "helper.h"
#include "FileNameData.h"
#include "File.h"
#include <vector>
using namespace std;
void readAttributeHeader(BYTE entry[1024], int firstAttributeOffset,int& sizeofData, int& offsetData, int& length){
    BYTE headerAttr[22]; //size of header attribute = 22
    for (int i = 0, j = firstAttributeOffset;i < 22, j < firstAttributeOffset + 22; i++, j++){
        headerAttr[i] = entry[j];
    }

    headerAttribute header_attribute;
    memcpy(&header_attribute, headerAttr, sizeof(headerAttribute));

    length = convertBytesToInt64(header_attribute.length,4); 
    sizeofData = convertBytesToInt64(header_attribute.size_of_data,4);
    offsetData = convertBytesToInt64(header_attribute.offset_data,2);
}

int checkCondition(int flags,  int value_of_flags){ // Ham kiem tra dieu kien: Chi xuat neu la tap tin archieve hoac thu muc + tap tin chua bi xoa
    if (flags != 0 && flags != 2  && (value_of_flags == 32 || value_of_flags == 268435456)) {
        return 1;
     }
    return 0;
}

void setFileInfo(BYTE entry[1024], FileNameData FND, File& f, uint64_t first_MFT_sector, uint64_t entry_readpoint, uint64_t size_of_name, int attributeData, int size_of_data_data,int offset_data_data){
   
    int length; // length of attribute data
    wstring a = L"";
    a = convertBytesToWString(FND.namefile, size_of_name);
    f.name = a;
    if (convertBytesToInt64(FND.value_of_flags,4) == 32){
        f.state = 32;
        readAttributeHeader(entry, attributeData, size_of_data_data, offset_data_data, length);
        f.size = size_of_data_data;
        if (size_of_data_data == 0) {
            f.content =  L"Tập tin này rỗng !";
        }
        else{
            wstring extension = a.substr(a.size() - 3, 3); // 3 last characters
            if (extension == L"txt" || extension == L"TXT") {
                vector <BYTE> data; 
                int sData = offset_data_data + attributeData;
                int eData = sData + size_of_data_data;
                for (int i = 0, j = sData; i < size_of_data_data, j < eData; i++, j++){
                    data.push_back(entry[j]);
                }    
                f.content = convertUnicodeHexCodeToCodePoint(data);
            }
            else {
                f.content = L"Không phải file txt => cần một phần mềm chuyên dụng để mở";
            }
    
      
        }

    }
    else {
        f.state = 268435456;
        f.size = 0;
        f.content = L"";
    }
   
    f.parentID = int(first_MFT_sector +  convertBytesToInt64(FND.parent_folder_MFT_entry, 4)*2);
    f.ID = (int)entry_readpoint;
}
void printTXTFile(wstring result , int tab) { // print better than function same name
    printTab(tab);
    wcout << L"Nội dung của tập tin txt trên:" << endl;
    printTab(tab);
    for (int i = 0; i < result.size(); i++) {
        wcout << result[i];
        if (result[i] == 0x0a) { // 0ah is end line
            printTab(tab);
        }
    }
    wcout << endl;
}
void printFile(File f, int tab){
    printTab(tab);
    wcout << L"Tên: " <<  f.name << endl;
    printTab(tab);
    if (f.state == 32){
        wcout << L"Trạng thái: Tập tin"  << endl;
    }  
    else {
        wcout << L"Trạng thái: Thư mục" << endl;
    }  
    printTab(tab);

    wcout << L"Kích thước: " << f.size << L" bytes" << endl;
    if (f.state == 32 ){
        if( f.size != 0)  {
            printTXTFile(f.content, tab);}
        else{
            printTab(tab);
            wcout << L"Tập tin này rỗng !" << endl;

        }
    }
   
    printTab(tab);
    wcout << L"Bắt đầu tại sector: " << f.ID << endl;
    printTab(tab);
    wcout << L"Sector của thư mục cha: " << f.parentID << endl;
    wcout << endl;

}

void readMFTEntryInfo(BYTE entry[1024], uint64_t& first_MFT_sector, FileNameData& FND, headerMFT& header_mft_entry, uint64_t& size_of_name,int& attributeData){
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

    int firstAttributeOffset = convertBytesToInt64(header_mft_entry.start_attribute_offset, 2); // attribute standard information
    readAttributeHeader(entry, firstAttributeOffset,size_of_data_standard_information, offset_data_standard_information,length1);
    
    int attributeFileName = firstAttributeOffset + length1;
    readAttributeHeader(entry, attributeFileName, size_of_data_file_name, offset_data_file_name, length2);

    int attributeObjectId = attributeFileName + length2;
    readAttributeHeader(entry, attributeObjectId, size_of_data_object_id, offset_data_object_id, length3);

    attributeData = attributeObjectId + length3;

    size_of_name = size_of_data_file_name - 66;
     
    BYTE* file_name_data = new BYTE[size_of_data_file_name];
    int sFileName = offset_data_file_name + attributeFileName; //start of filename
    int eFileName = sFileName + size_of_data_file_name; // end of filename
   
    for (int i = 0, j = sFileName; i < 66, j < sFileName+66; i++, j++){
        file_name_data[i] = entry[j];
    }

    memcpy(&FND, file_name_data, sizeof(FileNameData));    
    for (int i = 0, j = sFileName + 66; i < size_of_name, j < eFileName; i++, j++){
        FND.namefile[i] = entry[j];
    }

    delete []file_name_data;
}
void printTreeDirectory(vector<File> files, int parentId, int& count, int tab) {
    if (count == 0) {
        return;
    }
    for (auto file : files) {
        if (file.parentID == parentId) {

            printFile(file, tab);

            if (file.state == 268435456) {
                printTreeDirectory(files, file.ID, count, tab+3); 

            }             
            --count;
        }
    }
}

