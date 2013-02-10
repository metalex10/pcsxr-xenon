/****************************************************************************
 * Snes9x Nintendo Wii/Gamecube Port
 *
 * crunchy2 April 2007-July 2007
 * Michniewski 2008
 * Tantric 2008-2010
 *
 * sram.cpp
 *
 * SRAM save/load/import/export handling
 ***************************************************************************/
#include <unistd.h>
#include <xetypes.h>
#include <stdio.h>
#include <string.h>

#include "emu.h"
#include "menu.h"
#include "fileop.h"
#include "filebrowser.h"
#include "input.h"

/****************************************************************************
 * Load SRAM
 ***************************************************************************/
bool
LoadSRAM (char * filepath, bool silent)
{
	int len = 0;
	int device;
	bool result = false;

	result = (EMUInterface.LoadMCD(filepath) == 0);
	
	return result;
}

bool
LoadSRAMAuto (bool silent)
{
	char filepath[MAXPATHLEN];
	
	// look for Auto save file
	if(!MakeFilePath(filepath, FILE_SRAM, ROMInfo.filename, 0))
		return false;

	if (LoadSRAM(filepath, silent))
		return true;

	// look for file with no number or Auto appended
	if(!MakeFilePath(filepath, FILE_SRAM, ROMInfo.filename, -1))
		return false;

	if(LoadSRAM(filepath, silent))
		return true;
		
	return false;
}

/****************************************************************************
 * Save SRAM
 ***************************************************************************/
bool
SaveSRAM (char * filepath, bool silent)
{
	bool retval = false;
	int offset = 0;
	int device;
	
	retval = EMUInterface.SaveMCD(filepath) == 0;
	
	return retval;
}

bool
SaveSRAMAuto (bool silent)
{
	char filepath[1024];

	// look for file with no number or Auto appended
	if(!MakeFilePath(filepath, FILE_SRAM, ROMInfo.filename, -1))
		return false;

	FILE * fp = fopen (filepath, "rb");

	if(fp) // file found
	{
		fclose (fp);
	}	
	else
	{
		if(!MakeFilePath(filepath, FILE_SRAM, ROMInfo.filename, 0))
			return false;
	}
	return SaveSRAM(filepath, silent);
}
