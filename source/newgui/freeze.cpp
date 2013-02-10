/****************************************************************************
 * Snes9x Nintendo Wii/Gamecube Port
 *
 * softdev July 2006
 * crunchy2 May 2007-July 2007
 * Michniewski 2008
 * Tantric 2008-2010
 *
 * freeze.cpp
 ***************************************************************************/
#include <unistd.h>
#include <malloc.h>
#include <xetypes.h>
#include <stdio.h>

#include "emu.h"
#include "fileop.h"
#include "filebrowser.h"
#include "menu.h"
#include "video.h"

/****************************************************************************
 * SaveSnapshot
 ***************************************************************************/

int
SaveSnapshot (char * filepath, bool silent)
{
	int device;
	return EMUInterface.SaveStates(filepath);
}

int
SaveSnapshotAuto (bool silent)
{
	char filepath[1024];
	if(!MakeFilePath(filepath, FILE_SNAPSHOT, ROMInfo.filename, 0))
		return false;
		
	return SaveSnapshot(filepath, silent);
}

/****************************************************************************
 * LoadSnapshot
 ***************************************************************************/
int
LoadSnapshot (char * filepath, bool silent)
{
	return EMUInterface.LoadStates(filepath);;
}

int
LoadSnapshotAuto (bool silent)
{
	char filepath[1024];
	
	if(!MakeFilePath(filepath, FILE_SNAPSHOT, ROMInfo.filename, 0))
		return false;
		
	return LoadSnapshot(filepath, silent);
}
