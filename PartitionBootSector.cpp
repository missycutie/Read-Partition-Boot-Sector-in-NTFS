#include "PartitionBootSector.h"
#include "helper.h"
using namespace std;

void printInfoPartitionBootSector(const PartitionBootSector& PBS) {
    wcout << L"Kich thuoc cua mot sector: " << convertBytesToInt64(PBS.size_of_sector, 2) << L" bytes" << endl;
    wcout << L"So sector trong mot cluster: " << (int)PBS.sectors_per_cluster << L" sectors" << endl;
    wcout << L"So sector/ track: " << convertBytesToInt64(PBS.sector_per_track, 2) << L" sectors " << endl;
    wcout << L"So mat dia (head hay side): " << convertBytesToInt64(PBS.number_of_head, 2) << endl;
    wcout << L"Sector bat dau cua o dia logic: " << convertBytesToInt64(PBS.begin_sector_logic_disk, 4) << endl;
    wcout << L"So sector cua o dia logic: " << convertBytesToInt64(PBS.number_of_sectors_of_logic_disk, 8) << L" sectors" << endl;
    wcout << L"Cluster bat dau cua MFT: " << convertBytesToInt64(PBS.begin_cluster_MFT, 8) << endl;
    wcout << L"Cluster bat dau cua MFT du phong: " << convertBytesToInt64(PBS.begin_cluster_MFTMirror, 8) << endl;
    wstring temp = bitwise_complement(toBinary((int)PBS.size_of_mft_entry - 1)); // Xu li dang bu 2
    wcout << L"Kich thuoc cua mot ban ghi trong MFT (MFT entry): " <<  pow(2,stoi(temp,0,2)) << L" bytes" << endl;
    wcout << L"So cluster cua Index Buffer: " << (int)PBS.number_of_clusters_of_index_buffer << L" clusters" << endl;
    wcout << L"So seri cua o dia: " << convertBytesToInt64(PBS.volume_serial_number, 8) << endl;
    cout << endl;
}





