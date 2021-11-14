#include "PartitionBootSector.h"
#include "Sector.h"
#include "HeaderMFT.h"
#include "MFTEntry.h"
#include "FileNameData.h"
using namespace std;

int main(int argc, char ** argv)
{
    
    BYTE sector1[512];
    BYTE sector2[512];
    BYTE sector3[512];
    uint32_t first_MFT_sector;
    uint32_t Sc;
    uint32_t begin_MFT_cluster;
    ReadSector(L"\\\\.\\PHYSICALDRIVE1", 0, sector1);
    cout << endl;
    uint32_t APS = addressPartitionSector(sector1,0);
    cout << APS << endl;
    ReadSector(L"\\\\.\\PHYSICALDRIVE1", APS*512, sector2);
    cout << endl;
    cout << "--------------------------" << endl;
    readBPB(sector2, Sc, begin_MFT_cluster);
    first_MFT_sector = Sc*begin_MFT_cluster;
    cout << first_MFT_sector << endl;
    ReadSector(L"\\\\.\\F:", first_MFT_sector*512, sector3);
    BYTE entry[1024];
    BYTE entry1[1024];

    cout << endl;
    ReadMFTEntry(L"\\\\.\\:F", first_MFT_sector*512, entry);
    cout << endl;
    readMFTEntryHeader(entry);
    // int entry1_readpoint = (first_MFT_sector + 2)*512;
    // ReadMFTEntry(L"\\\\.\\F:", entry1_readpoint, entry1);
    // cout << endl;
    // readMFTEntryHeader(entry1);
    uint32_t entry1_readpoint = (first_MFT_sector + 92)*512;
    ReadMFTEntry(L"\\\\.\\F:", entry1_readpoint, entry1);
    readMFTEntryHeader(entry1);
    cout << endl;
    return 0;
}