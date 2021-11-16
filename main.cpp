#include "PartitionBootSector.h"
#include "Sector.h"
#include "HeaderMFT.h"
#include "MFTEntry.h"
#include "FileNameData.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main(int argc, char ** argv)
{
    
    BYTE sector1[512];
    BYTE sector2[512];
    BYTE sector3[512];
    uint32_t first_MFT_sector;
    uint32_t Sc;
    uint32_t begin_MFT_cluster;
    ReadSector(L"\\\\.\\PHYSICALDRIVE1", 0, sector1); // read MBR
    cout << endl;
    uint32_t APS = addressPartitionSector(sector1,0);
    cout << APS << endl;
    ReadSector(L"\\\\.\\PHYSICALDRIVE1", APS*512, sector2); // Read PBS
    cout << endl;
    cout << "--------------------------" << endl;
    readBPB(sector2, Sc, begin_MFT_cluster);
    first_MFT_sector = Sc*begin_MFT_cluster;
    cout << first_MFT_sector << endl;
    ReadSector(L"\\\\.\\F:", first_MFT_sector*512, sector3);
    // BYTE entry[1024];
    BYTE entry1[1024];
    // BYTE entry2[1024];
    cout << endl;
    // ReadMFTEntry(L"\\\\.\\F:", first_MFT_sector*512, entry);
    // cout << endl;
    // readMFTEntryHeader(entry);
    // uint32_t entry1_readpoint = (first_MFT_sector + 2)*512;
    // ReadMFTEntry(L"\\\\.\\F:", entry1_readpoint, entry1);
    // cout << endl;
    // readMFTEntryHeader(entry1);
    // uint32_t entry1_readpoint = (first_MFT_sector + 92)*512;
    // uint32_t entry2_readpoint = (first_MFT_sector + 90)*512;
    vector <int> index;
    vector <FileNameData> vector_FND;
    for (int i = 44; i < 200; i++){
        BYTE entry[1024];
        FileNameData FND;
        headerMFT header_mft_entry;
        uint32_t size_of_name;
        uint32_t entry_readpoint = (first_MFT_sector + i*2)*512;
        ReadMFTEntry(L"\\\\.\\F:", entry_readpoint, entry);
        // cout << endl;
        uint32_t temp = first_MFT_sector+i*2;
        readMFTEntryHeader(entry, first_MFT_sector, temp, FND, header_mft_entry, size_of_name);
        if (checkCondition(convertBytesToInt(header_mft_entry.flags, 2), (int)FND.name_space, convertBytesToInt(FND.value_of_flags,4)) == 1){
            printMFTEntryInfo(FND, header_mft_entry, first_MFT_sector, entry_readpoint, size_of_name);
            index.push_back(first_MFT_sector + convertBytesToInt(FND.parent_folder_MFT_entry, 8)*2);
            vector_FND.push_back(FND);
        } 
    }
    sort(index.begin(), index.end());
    int RDET = index[0];
    // for (auto x:vector_FND)
    // {
    //     if (first_MFT_sector + convertBytesToInt(x.parent_folder_MFT_entry,8)*2 == RDET){
    //         for( int i = 0 ; i < strlen(x.namefile) ; i ++ ){
	// 	        cout << x.namefile[i]; 
	//         }
    //         cout << endl;
    //     }
    // }
   
    // cout << endl;
    // ReadMFTEntry(L"\\\\.\\F:", entry2_readpoint, entry2);
    // cout << endl;
    // readMFTEntryHeader(entry2);
    // cout << endl;
    return 0;
}