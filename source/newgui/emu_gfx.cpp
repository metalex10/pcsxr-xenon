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
#define MAXPATHLEN 4096
 
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
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>
#include "emu.h"

extern struct XenosDevice * g_pVideoDevice;
static XenosSurface * surf = NULL;

XenosSurface * SEMUInterface::GetSurface() {
	if (surf == NULL) {
		surf = Xe_CreateTexture(g_pVideoDevice, 1280, 720, 0, XE_FMT_8888 | XE_FMT_ARGB, 1);
		
		u8 * surfbuf;
		surfbuf = (u8*) Xe_Surface_LockRect(g_pVideoDevice, surf, 0, 0, 0, 0, XE_LOCK_WRITE);
		memset(surfbuf, 0xFF, 1280 * 720 * 4);
		Xe_Surface_Unlock(g_pVideoDevice, surf);
		
	}
	return surf;
}


