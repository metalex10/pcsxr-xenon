#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>
#include <libfat/fat.h>
#if 0 // not yet
#include <libext2/ext2.h>
#include <libntfs/ntfs.h>
#endif
#include <libxtaf/xtaf.h>
#include <iso9660/iso9660.h>
#include <sys/iosupport.h>
#include <diskio/disc_io.h>
#include <byteswap.h>

#include "cmount.h"

/**
 * PRIMARY_PARTITION - Block device partition record
 */
typedef struct _PARTITION_RECORD {
	u8 status; /* Partition status; see above */
	u8 chs_start[3]; /* Cylinder-head-sector address to first block of partition */
	u8 type; /* Partition type; see above */
	u8 chs_end[3]; /* Cylinder-head-sector address to last block of partition */
	u32 lba_start; /* Local block address to first sector of partition */
	u32 block_count; /* Number of blocks in partition */
} __attribute__((__packed__)) PARTITION_RECORD;

/**
 * MASTER_BOOT_RECORD - Block device master boot record
 */
typedef struct _MASTER_BOOT_RECORD {
	u8 code_area[446]; /* Code area; normally empty */
	PARTITION_RECORD partitions[4]; /* 4 primary partitions */
	u16 signature; /* MBR signature; 0xAA55 */
} __attribute__((__packed__)) MASTER_BOOT_RECORD;

extern DISC_INTERFACE xenon_atapi_ops;
extern DISC_INTERFACE xenon_ata_ops;
extern DISC_INTERFACE usb2mass_ops;

int mount_dvd(DISC_INTERFACE *interface, const char * mountprefix) {
	return -1;
}

int mount_interface(DISC_INTERFACE *interface, const char * mountprefix) {
	// mount only iso9660 filesystem
	if (interface == &xenon_atapi_ops) {
		return mount_dvd(interface, mountprefix);
	}
	
	if (interface == &xenon_ata_ops) {
		// try mount xtaf first
		int n = XTAFMount();
		if (n) {
			return 0;
		}
		// classic mount
	}
	
	fatMount(mountprefix, interface, 0, 2, 64);
	
#if 0 // todo
	int i = 0;
	sec_t part_lba = 0;
	PARTITION_RECORD *partition = NULL;
	unsigned char * sector_buffer = memalign(32, MAX_SECTOR_SIZE);
	
	MASTER_BOOT_RECORD * mbr = (MASTER_BOOT_RECORD *)sector_buffer;
	PARTITION_RECORD * pr = (PARTITION_RECORD *)sector_buffer;
	
	// Read 1st sector
	if (!interface->readSectors(0, 1, &sector_buffer)) {
		free(sector_buffer);
		return -1;
	}
	
	if (sector.mbr.signature == MBR_SIGNATURE) {
		// parse primary partition
		for (i = 0; i < 4; i++) {
			partition = &mbr->partitions[i];
			part_lba = bswap_32(partition->lba_start);
			
			switch (partition->type) {
				case PARTITION_TYPE_DOS33_EXTENDED:
				case PARTITION_TYPE_WIN95_EXTENDED:
				
			}
		}
	}
	
	free(sector_buffer);
#endif
	return 0;
}

void mount_all() {
	static int already_mounted = 0;
	if (already_mounted) 
		return;
	
	mount_interface(&xenon_atapi_ops, "dvd");
	mount_interface(&xenon_ata_ops, "sda");
	mount_interface(&usb2mass_ops, "uda");
	
	already_mounted = 1;
}