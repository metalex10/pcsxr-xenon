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
 * emu.h
 *
 * This file controls overall program flow. Most things start and end here!
 ***************************************************************************/

#pragma once

#include "FreeTypeGX.h"

#define APPNAME 		"PCSXR Xenon"
#define APPVERSION 		"0.7"
#define APPFOLDER 		"pcsxr"
#define PREF_FILE_NAME 	"settings.xml"

#define NOTSILENT 0
#define SILENT 1

// todo dynamic ....
const char pathPrefix[9][8] =
{ "", "uda:/", "sda0:/" };

enum {
	DEVICE_AUTO,
	DEVICE_USB,
	DEVICE_HDD,
	DEVICE_DVD,
	DEVICE_SMB,
};

enum {
	FILE_SRAM,
	FILE_SNAPSHOT,
	FILE_ROM,
	FILE_CHEAT
};

enum
{
	CTRL_PAD,
	CTRL_MOUSE,
	CTRL_SCOPE,
	CTRL_JUST,
	CTRL_PAD2,
	CTRL_PAD4,
	CTRL_LENGTH
};

const char ctrlName[6][24] =
{ "SNES Controller", "SNES Mouse", "Superscope", "Justifier", "SNES Controllers (2)", "SNES Controllers (4)" };

enum {
	LANG_JAPANESE = 0,
	LANG_ENGLISH,
	LANG_GERMAN,
	LANG_FRENCH,
	LANG_SPANISH,
	LANG_ITALIAN,
	LANG_DUTCH,
	LANG_SIMP_CHINESE,
	LANG_TRAD_CHINESE,
	LANG_KOREAN,
	LANG_PORTUGUESE,
	LANG_BRAZILIAN_PORTUGUESE,
	LANG_CATALAN,
	LANG_TURKISH,
	LANG_LENGTH
};

struct SEMUSettings{
    int		AutoLoad;
    int		AutoSave;
    int		LoadMethod; // For ROMS: Auto, SD, DVD, USB, Network (SMB)
	int		SaveMethod; // For SRAM, Freeze, Prefs: Auto, SD, USB, SMB
	char	LoadFolder[MAXPATHLEN]; // Path to game files
	char	SaveFolder[MAXPATHLEN]; // Path to save files
	char	CheatFolder[MAXPATHLEN]; // Path to cheat files

	float	zoomHor; // horizontal zoom amount
	float	zoomVert; // vertical zoom amount
	int		videomode; // 0 - automatic, 1 - NTSC (480i), 2 - Progressive (480p), 3 - PAL (50Hz), 4 - PAL (60Hz)
	int		render;		// 0 - original, 1 - filtered, 2 - unfiltered
	int		FilterMethod; // convert to RenderFilter
	int		Controller;
	int		crosshair;
	int		widescreen;	// 0 - 4:3 aspect, 1 - 16:9 aspect
	int		xshift;	// video output shift
	int		yshift;
	int		ExitAction;
	int		MusicVolume;
	int		SFXVolume;
	int		Rumble;
	int 	language;
};

struct SROMInfo {	
	char filename[MAXPATHLEN];
	char diplayname[MAXPATHLEN];
	unsigned int filesize;
};

#define GetFilterNumber() 0

// Emu interface
class SEMUInterface {
public:
	int Reset();
	int Resume();
	int Pause();
	int Start(const char * filename);
	int PowerOff();
	int LoadStates(const char * filename);
	int SaveStates(const char * filename);
	int LoadMCD(const char * filename);
	int SaveMCD(const char * filename);
	XenosSurface * GetSurface();
};

extern struct SEMUSettings EMUSettings;
extern struct SROMInfo ROMInfo;
extern class SEMUInterface EMUInterface;


void ExitApp();
void Shutdown();
extern int ScreenshotRequested;
extern int ConfigRequested;
extern int ShutdownRequested;
extern int ExitRequested;
extern char appPath[];
extern char loadedFile[];
extern FreeTypeGX *fontSystem[];

extern int exitThreads;

