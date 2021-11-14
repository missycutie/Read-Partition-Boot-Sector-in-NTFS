#include "PartitionBootSector.h"
#include "helper.h"
using namespace std;


int addressPartitionSector(BYTE sector[512], int partitionOrder){
    int start = 457 + partitionOrder*16;
    int end = 454 + partitionOrder*16;
    string a;
    for (int i = start ; i >= end; i--)
        {
            a+=toHex(sector[i]);
            
        }
   
    return stoi(a,0,16);
}

void readBPB(BYTE sector[512], uint32_t& Sc, uint32_t& begin_MFT_cluster){
    BYTE BPB[73];
    int begin = 11;
    for (int i = 0, begin = 11;i<73, begin < 84;i++, begin++){
        BPB[i] = sector[begin];
    }
    cout << "BPB: " << endl;
    for (int i = 0; i< 73; i++){
        cout << toHex(BPB[i]) << " ";
    }
    cout << "\nThong tin cua Partition Boot Sector cua NTFS: " << endl;
    PartitionBootSector PBS;
    memcpy(&PBS, BPB, sizeof(PartitionBootSector));
    printInfoPartitionBootSector(PBS);
    Sc = (long int)PBS.sectors_per_cluster;
    begin_MFT_cluster = convertBytesToInt(PBS.begin_cluster_MFT, 8);
}


void printInfoPartitionBootSector(const PartitionBootSector& PBS) {
    cout << "Kich thuoc cua mot sector: " << convertBytesToInt(PBS.size_of_sector, 2) << " bytes" << endl;
    cout << "So sector trong mot cluster: " << (int)PBS.sectors_per_cluster << " sectors" << endl;
    cout << "So sector/ track: " << convertBytesToInt(PBS.sector_per_track, 2) << " sectors " << endl;
    cout << "So mat dia (head hay side): " << convertBytesToInt(PBS.number_of_head, 2) << endl;
    cout << "Sector bat dau cua o dia logic: " << convertBytesToInt(PBS.begin_sector_logic_disk, 4) << endl;
    cout << "So sector cua o dia logic: " << convertBytesToInt(PBS.number_of_sectors_of_logic_disk, 8) << " sectors" << endl;
    cout << "Cluster bat dau cua MFT: " << convertBytesToInt(PBS.begin_cluster_MFT, 8) << endl;
    cout << "Cluster bat dau cua MFT du phong: " << convertBytesToInt(PBS.begin_cluster_MFTMirror, 8) << endl;
    string temp = bitwise_complement(toBinary((int)PBS.size_of_mft_entry - 1));
    cout << "Kich thuoc cua mot ban ghi trong MFT (MFT entry): " <<  pow(2,stoi(temp,0,2)) << " bytes" << endl;
    cout << "So cluster cua Index Buffer: " << (int)PBS.number_of_clusters_of_index_buffer << " clusters" << endl;
    cout << "So seri cua o dia: " << convertBytesToInt(PBS.volume_serial_number, 8) << endl;
    cout << endl;
}





