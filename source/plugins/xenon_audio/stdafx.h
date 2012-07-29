/***************************************************************************
                           StdAfx.h  -  description
                             -------------------
    begin                : Wed May 15 2002
    copyright            : (C) 2002 by Pete Bernert
    email                : BlackDove@addcom.de
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version. See also the license.txt file for *
 *   additional informations.                                              *
 *                                                                         *
 ***************************************************************************/


#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#define RRand(range) (random()%range)  
#include <string.h> 
#include <sys/time.h>  
#include <math.h>  

#undef CALLBACK
#define CALLBACK
#define DWORD unsigned long
#define LOWORD(l)           ((unsigned short)(l)) 
#define HIWORD(l)           ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF)) 

#ifndef INLINE
#define INLINE inline
#endif



#ifdef LIBXENON
#define SPUreadDMA				XAUDIO_SPUreadDMA
#define SPUreadDMAMem			XAUDIO_SPUreadDMAMem
#define SPUwriteDMA				XAUDIO_SPUwriteDMA
#define SPUwriteDMAMem			XAUDIO_SPUwriteDMAMem
#define SPUasync				XAUDIO_SPUasync
#define SPUupdate				XAUDIO_SPUupdate
#define SPUplayADPCMchannel		XAUDIO_SPUplayADPCMchannel
#define SPUinit					XAUDIO_SPUinit
#define SPUopen					XAUDIO_SPUopen
#define SPUsetConfigFile		XAUDIO_SPUsetConfigFile
#define SPUclose				XAUDIO_SPUclose
#define SPUshutdown				XAUDIO_SPUshutdown
#define SPUtest					XAUDIO_SPUtest
#define SPUconfigure			XAUDIO_SPUconfigure
#define SPUabout				XAUDIO_SPUabout
#define SPUregisterCallback		XAUDIO_SPUregisterCallback
#define SPUregisterCDDAVolume	XAUDIO_SPUregisterCDDAVolume
#define SPUwriteRegister		XAUDIO_SPUwriteRegister
#define SPUreadRegister			XAUDIO_SPUreadRegister
#define SPUfreeze				XAUDIO_SPUfreeze
#define SPUplayCDDAchannel		XAUDIO_SPUplayCDDAchannel


#define ReadConfig				XAUDIO_SPUReadConfig
#define ReadConfigFile			XAUDIO_SPUReadConfigFile
#define iDebugMode				XAUDIO_SPUiDebugMode

#define PSEgetLibName			XAUDIO_SPUPSEgetLibName
#define PSEgetLibType			XAUDIO_SPUPSEgetLibType
#define PSEgetLibVersion		XAUDIO_SPUPSEgetLibVersion
#endif

#include "psemuxa.h"
