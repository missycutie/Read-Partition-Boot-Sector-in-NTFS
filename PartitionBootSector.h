#ifndef __PARTITION_BOOT_SECTOR_H__
#define __PARTITION_BOOT_SECTOR_H__
#include <windows.h>
#include <stdint.h>

#define SIZE_PER_SECTOR 2
#define SIZE_SECTORS_PER_TRACK 2
#define SIZE_NUMBER_OF_HEADS 2
#define SIZE_BEGIN_SECTOR_LOGIC_DISK 4
#define SIZE_SECTOR_LOGIC_DISK 8
#define SIZE_BEGIN_MFT_CLUSTER 8
#define SIZE_BEGIN_MFTMirror_CLUSTER 8
#define SIZE_VOLUME_SERIAL_NUMBER 8


struct PartitionBootSector {
    uint8_t size_of_sector[SIZE_PER_SECTOR];
    uint8_t sectors_per_cluster;
    uint8_t no_use[2];
    uint8_t ntfs_value1;
    uint8_t ntfs_value2[2];
    uint8_t ntfs_value3[2];
    uint8_t id;
    uint8_t ntfs_value4[2];
    uint8_t sector_per_track[SIZE_SECTORS_PER_TRACK];
    uint8_t number_of_head[SIZE_NUMBER_OF_HEADS];
    uint8_t begin_sector_logic_disk[SIZE_BEGIN_SECTOR_LOGIC_DISK];
    uint8_t ntfs_value5[4];
    uint8_t ntfs_value6[4];
    uint8_t number_of_sectors_of_logic_disk[SIZE_SECTOR_LOGIC_DISK];
    uint8_t begin_cluster_MFT[SIZE_BEGIN_MFT_CLUSTER];
    uint8_t begin_cluster_MFTMirror[SIZE_BEGIN_MFTMirror_CLUSTER];
    uint8_t size_of_mft_entry;
    uint8_t ntfs_value7[3];
    uint8_t number_of_clusters_of_index_buffer;
    uint8_t ntfs_value8[3];
    uint8_t volume_serial_number[SIZE_VOLUME_SERIAL_NUMBER];
    uint8_t ntfs_value9[4];
};

void printInfoPartitionBootSector(const PartitionBootSector& PBS); 
#endif

