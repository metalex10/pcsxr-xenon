#pragma once

#ifdef __cplusplus 
extern "C" 
{ 
#endif

#define MAX_SECTOR_SIZE 4096 // big
#define NTFS_OEM_ID                         (0x4e54465320202020ULL)

#define PARTITION_TYPE_EMPTY                0x00 /* Empty */
#define PARTITION_TYPE_DOS33_EXTENDED       0x05 /* DOS 3.3+ extended partition */
#define PARTITION_TYPE_NTFS                 0x07 /* Windows NT NTFS */
#define PARTITION_TYPE_WIN95_EXTENDED       0x0F /* Windows 95 extended partition */
#define PARTITION_TYPE_LINUX                0x83 /* EXT2/3/4 */

#define PARTITION_STATUS_NONBOOTABLE        0x00 /* Non-bootable */
#define PARTITION_STATUS_BOOTABLE           0x80 /* Bootable (active) */

#define MBR_SIGNATURE                       (0x55AA)
#define EBR_SIGNATURE                       (0x55AA)

#define BPB_FAT16_fileSysType  0x36
#define BPB_FAT32_fileSysType  0x52

#define T_FAT           1
#define T_NTFS          2
#define T_EXT2          3
#define T_ISO9660       4

static const char FAT_SIG[3] = {'F', 'A', 'T'};

void mount_all();

#ifdef __cplusplus
}
#endif