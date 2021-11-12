#include "PartitionBootSector.h"
#include "Sector.h"
using namespace std;




int main(int argc, char ** argv)
{
    
    BYTE sector1[512];
    BYTE sector2[512];
    BYTE sector3[512];

    ReadSector(L"\\\\.\\PHYSICALDRIVE1",0, sector1);
    cout << endl;
    int APS = addressPartitionSector(sector1,0);
    ReadSector(L"\\\\.\\PHYSICALDRIVE1", APS, sector2);
    cout << endl;
    cout << "--------------------------" << endl;
   
    uint32_t first_MFT_sector;
    uint32_t Sc;
    uint32_t begin_MFT_cluster;
    readBPB(sector2, Sc, begin_MFT_cluster);
    first_MFT_sector = Sc*begin_MFT_cluster;
  
    // ReadSector(L"\\\\.\\PHYSICALDRIVE1", first_MFT_sector , sector3);
    return 0;
}