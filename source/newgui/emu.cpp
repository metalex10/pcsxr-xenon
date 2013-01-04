/****************************************************************************
 * PCSXR Xenon
 * Based on
 * Snes9x Nintendo Wii/Gamecube Port
 *
 * softdev July 2006
 * crunchy2 May 2007-July 2007
 * Michniewski 2008
 * Tantric 2008-2010
 * Ced2911 2013
 *
 * emu.cpp
 *
 * This file controls overall program flow. Most things start and end here!
 ***************************************************************************/
#include <unistd.h>
#include <xenos/xenos.h>
#include <xenos/xe.h>
#include <xenon_sound/sound.h>
#include <diskio/ata.h>
#include <ppc/cache.h>
#include <ppc/timebase.h>
#include <pci/io.h>
#include <input/input.h>
#include <xenon_smc/xenon_smc.h>
#include <console/console.h>
#include <xenon_soc/xenon_power.h>
#include <usb/usbmain.h>
#include <ppc/timebase.h>
#include <sys/iosupport.h>
 
#include "emu.h"

#include "config.h"
#include "r3000a.h"
#include "psxcommon.h"
#include "debug.h"
#include "sio.h"
#include "misc.h"

static void _SetIso(const char * fname) {
	FILE *fd = fopen(fname, "rb");
	if (fd == NULL) {
		printf("Error loading %s\r\n", fname);
		return;
	}
	uint8_t header[0x10];
	int n = fread(header, 0x10, 1, fd);
/*
	if (header[0] == 0x78 && header[1] == 0xDA) {
		printf("Use CDRCIMG for  %s\r\n", fname);
		strcpy(Config.Cdr, "CDRCIMG");
		cdrcimg_set_fname(fname);
	} else {
		SetIsoFile(fname);
	}
	*/
	SetIsoFile(fname);
	fclose(fd);
}

int SEMUInterface::Reset() {
	EmuReset();
	return 1;
}

int SEMUInterface::Resume() {
	return -1;
}

int SEMUInterface::Pause() {
	return -1;
}

int SEMUInterface::Start(const char * filename) {
	memset(&Config, 0, sizeof (PcsxConfig));
	
	strcpy(Config.Net, "Disabled");
	strcpy(Config.Cdr, "CDR");
	strcpy(Config.Gpu, "GPU");
	strcpy(Config.Spu, "SPU");
	strcpy(Config.Pad1, "PAD1");
	strcpy(Config.Pad2, "PAD2");

	strcpy(Config.Bios, "SCPH1001.BIN"); // Use actual BIOS
	
	strcpy(Config.BiosDir, "sda0:/pcsxr/bios");
	strcpy(Config.PatchesDir, "sda0:/pcsxr/patches_/");

	Config.PsxAuto = 1; // autodetect system
	
	Config.Cpu = CPU_DYNAREC;
	//Config.Cpu =  CPU_INTERPRETER;

	strcpy(Config.Mcd1, "sda0:/pcsxr/memcards/card1.mcd");
	strcpy(Config.Mcd2, "sda0:/pcsxr/memcards/card2.mcd");
	
	_SetIso(filename);
	if (LoadPlugins() == 0) {
		if (OpenPlugins() == 0) {
			if (SysInit() == -1) {
				printf("SysInit() Error!\n");
				return -1;
			}

			SysReset();
			// Check for hle ...
			if (Config.HLE == 1) {
				printf("Can't continue ... bios not found ...\r\n");
				//exit(0);
			}

			CheckCdrom();
			LoadCdrom();

			psxCpu->Execute();
		}
	}
	
	return 0;
}

int SEMUInterface::PowerOff() {
	return -1;
}

int SEMUInterface::LoadStates(const char * filename) {
	return -1;
}

int SEMUInterface::SaveStates(const char * filename) {
	return -1;
}

int SEMUInterface::LoadMCD(const char * filename) {
	return -1;
}

int SEMUInterface::SaveMCD(const char * filename) {
	return -1;
}

extern struct XenosDevice * g_pVideoDevice;
static XenosSurface * surf = NULL;

XenosSurface * SEMUInterface::GetSurface() {
	if (surf == NULL) {
		surf = Xe_CreateTexture(g_pVideoDevice, 1280, 720, 0, XE_FMT_8888 | XE_FMT_ARGB, 1);
	}
	return surf;
}


class SEMUInterface EMUInterface;
struct SROMInfo ROMInfo;

