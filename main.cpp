#include "PartitionBootSector.h"
#include "Sector.h"
#include "MFT.h"
#include "MFTEntry.h"
#include "FileNameData.h"
#include <vector>
using namespace std;

int main(int argc, char ** argv)
{
    BYTE pbs[512];
    uint64_t first_MFT_sector;
    uint64_t Sc;
    uint64_t begin_MFT_cluster;
    ReadSector(L"\\\\.\\E:", 0, pbs); // Read Partition Boot Sector
    cout << endl;
    cout << "--------------------------" << endl;

    PartitionBootSector partition;
    memcpy(&partition, pbs + 11, 73); // 73 bytes of BPB, start from 11
    Sc =(int)partition.sectors_per_cluster; // sector per cluster
    begin_MFT_cluster = convertBytesToInt(partition.begin_cluster_MFT,8); // cluster beginning MFT
    first_MFT_sector = Sc*begin_MFT_cluster; // sector beginning MFT
    printInfoPartitionBootSector(partition); // read info of PBS
    cout << "---------------------------" << endl;
   
    // vector <FileNameData> vector_FND;
    for (int i = 44; i < 200  ; i++){
        BYTE entry[1024];
        FileNameData FND;
        headerMFT header_mft_entry;
        uint64_t size_of_name;
        int attributeData;
        int size_of_data_data;
        int offset_data_data;
        uint64_t readpoint = (first_MFT_sector + i*2)*512;
        ReadMFTEntry(L"\\\\.\\E:", readpoint, entry);
        uint64_t temp = first_MFT_sector+i*2; // sector of entry
        readMFTEntryHeader(entry, first_MFT_sector, FND, header_mft_entry, size_of_name, attributeData);
        if (checkCondition(convertBytesToInt(header_mft_entry.flags, 2), convertBytesToInt(FND.value_of_flags,4))){
            printMFTEntryInfo(entry, FND, first_MFT_sector, temp, size_of_name, attributeData, size_of_data_data, offset_data_data);
            FND.entry = temp;
            FND.size_name = size_of_name;
            // vector_FND.push_back(FND);
  
        } 
    }

    return 0;
}