#include "PartitionBootSector.h"
#include "Sector.h"
#include "HeaderMFT.h"
#include "MFTEntry.h"
#include "FileNameData.h"
#include <bits/stdc++.h>
#include <vector>
using namespace std;
// void printTab(int tab) {
//     for (int i = 0; i < tab; i++) {
//         cout << '\t';
//     }
// }
// void read_and_print_TMG(vector<FileNameData>FND, uint32 root, int tab){
//     sort(index.begin(), index.end());
//     int RDET = index[0];printTab(tab);
//     if (convertBytesToInt(x.value_of_flags,4) == 32){
//         printMFTEntryInfo(x, first_MFT_sector, x.entry, x.size_name);

//      }
//     else {
//         printMFTEntryInfo(x, first_MFT_sector, x.entry, x.size_name);
//         // for (auto y:vector_FND){
//         //     if ((first_MFT_sector + convertBytesToInt(y.parent_folder_MFT_entry,8)*2) == (int)x.entry){
//         //         printTab(tab+2);
//         //         printMFTEntryInfo(x, first_MFT_sector, x.entry, x.size_name);
//         read_and_print_TMG();
//             }
//         }
//     }
//     }
// }
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
    BYTE entry1[1024];
    cout << endl;
  
    vector <int> index;
    vector <uint32_t> sizeName;
    // vector <headerMFT> headerMFTEntry;
    // vector <uint32_t> entryReadpoint;
    vector <FileNameData> vector_FND;
    vector <FileNameData> vector_TMG; // vector thu muc goc

    for (int i = 44; i < 200; i++){
        BYTE entry[1024];
        FileNameData FND;
        headerMFT header_mft_entry;
        uint32_t size_of_name;
        uint32_t entry_readpoint = (first_MFT_sector + i*2)*512;
        ReadMFTEntry(L"\\\\.\\F:", entry_readpoint, entry);
        // cout << endl;
        uint32_t temp = first_MFT_sector+i*2;
        readMFTEntryHeader(entry, first_MFT_sector, FND, header_mft_entry, size_of_name);
        if (checkCondition(convertBytesToInt(header_mft_entry.flags, 2), (int)FND.name_space, convertBytesToInt(FND.value_of_flags,4)) == 1){
            // printMFTEntryInfo(FND, header_mft_entry, first_MFT_sector, entry_readpoint, size_of_name);
            index.push_back(first_MFT_sector + convertBytesToInt(FND.parent_folder_MFT_entry, 8)*2); // mang cac index 
            FND.entry = temp;
            FND.size_name = size_of_name;
            vector_FND.push_back(FND);
            // sizeName.push_back(size_of_name);

            // headerMFTEntry.push_back(header_mft_entry);
            // entryReadpoint.push_back(temp);
        } 
    }
  
    //Xay dung cay thu muc goc
 
    // for (auto x:vector_FND)
    // {
    //     if (first_MFT_sector + convertBytesToInt(x.parent_folder_MFT_entry,8)*2 == RDET){
    //         // printMFTEntryInfo(x, first_MFT_sector, x.entry, x.size_name);
    //         vector_TMG.push_back(x);
    //         cout << endl;
    //     }
    //     // j++;
    //     // k++;
    //     // g++;
    // }
    // // In cay thu muc 
    // for (auto x:vector_TMG){
    //     if (convertBytesToInt(x.value_of_flags,4) == 32) {
    //         printMFTEntryInfo(x, first_MFT_sector, x.entry, x.size_name);

    //     }
    //     else{
            
    //     }

    // }

    return 0;
}