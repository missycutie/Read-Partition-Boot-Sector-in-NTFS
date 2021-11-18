#include "PartitionBootSector.h"
#include "helper.h"
using namespace std;

void printInfoPartitionBootSector(const PartitionBootSector& PBS) {
    cout << "Kich thuoc cua mot sector: " << convertBytesToInt(PBS.size_of_sector, 2) << " bytes" << endl;
    cout << "So sector trong mot cluster: " << (int)PBS.sectors_per_cluster << " sectors" << endl;
    cout << "So sector/ track: " << convertBytesToInt(PBS.sector_per_track, 2) << " sectors " << endl;
    cout << "So mat dia (head hay side): " << convertBytesToInt(PBS.number_of_head, 2) << endl;
    cout << "Sector bat dau cua o dia logic: " << convertBytesToInt(PBS.begin_sector_logic_disk, 4) << endl;
    cout << "So sector cua o dia logic: " << convertBytesToInt(PBS.number_of_sectors_of_logic_disk, 8) << " sectors" << endl;
    cout << "Cluster bat dau cua MFT: " << convertBytesToInt(PBS.begin_cluster_MFT, 8) << endl;
    cout << "Cluster bat dau cua MFT du phong: " << convertBytesToInt(PBS.begin_cluster_MFTMirror, 8) << endl;
    string temp = bitwise_complement(toBinary((int)PBS.size_of_mft_entry - 1)); // Xu li dang bu 2
    cout << "Kich thuoc cua mot ban ghi trong MFT (MFT entry): " <<  pow(2,stoi(temp,0,2)) << " bytes" << endl;
    cout << "So cluster cua Index Buffer: " << (int)PBS.number_of_clusters_of_index_buffer << " clusters" << endl;
    cout << "So seri cua o dia: " << convertBytesToInt(PBS.volume_serial_number, 8) << endl;
    cout << endl;
}





