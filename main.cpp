#include "PartitionBootSector.h"
#include "MFT.h"
#include "MFTEntry.h"
#include <io.h>
#include "FileNameData.h"
#include "File.h"
#include <vector>

#define _O_U16TEXT 0x20000
using namespace std;

int main(int argc, char ** argv)
{
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
    BYTE pbs[512];
    uint64_t first_MFT_sector;
    uint64_t Sc;
    uint64_t begin_MFT_cluster;
    ReadSector(L"\\\\.\\F:", 0, pbs); // Read Partition Boot Sector
    wcout << endl;
    wcout << L"--------------------------" << endl;

    PartitionBootSector partition;
    memcpy(&partition, pbs + 11, 73); // 73 bytes of BPB, start from 11
    Sc =(int)partition.sectors_per_cluster; // sector per cluster
    begin_MFT_cluster = convertBytesToInt64(partition.begin_cluster_MFT,8); // cluster beginning MFT
    first_MFT_sector = Sc*begin_MFT_cluster; // sector beginning MFT
    printInfoPartitionBootSector(partition); // read info of PBS
    wcout << L"---------------------------" << endl;
   
    vector <File> files;
    int count = 0; // count number of vector FND
    for (int i = 44; i < 100  ; i++){
        BYTE entry[1024];
        FileNameData FND;
        File f;
        headerMFT header_mft_entry;
        uint64_t size_of_name;
        int attributeData;
        int size_of_data_data;
        int offset_data_data;
        uint64_t readpoint = (first_MFT_sector + i*2)*512;
        ReadMFTEntry(L"\\\\.\\F:", readpoint, entry);
        //------------------CHECK IF IT IS THE END OF MFT------------------------
        // if (entry[0] == 0xff){
        //     break;
        // }
        uint64_t temp = first_MFT_sector+i*2; // sector of entry
        readMFTEntryInfo(entry, first_MFT_sector, FND,  header_mft_entry, size_of_name, attributeData);
        if (checkCondition(convertBytesToInt64(header_mft_entry.flags, 2), convertBytesToInt64(FND.value_of_flags,4))){
            setFileInfo(entry, FND, f, first_MFT_sector, temp, size_of_name, attributeData, size_of_data_data, offset_data_data);
            files.push_back(f);
            count++;
        } 
        
    }
    int root = int(first_MFT_sector + 5*2);
    int tab  = 0;
    printTreeDirectory(files, root, count, tab);

    return 0;
}