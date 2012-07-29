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

//*************************************************************************//
// History of changes:
//
// 2002/05/15 - Pete
// - generic cleanup for the Peops release
//
//*************************************************************************//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#define RRand(range) (random()%range)  
#include <string.h> 
#include <sys/time.h>  
#include <math.h>  

#undef CALLBACK
#define CALLBACK
#define DWORD unsigned long
#define LOWORD(l)           ((unsigned short)(l)) 
#define HIWORD(l)           ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF)) 

#define INLINE inline

#define SPUreadDMA				XRAUDIO_SPUreadDMA
#define SPUreadDMAMem			XRAUDIO_SPUreadDMAMem
#define SPUwriteDMA				XRAUDIO_SPUwriteDMA
#define SPUwriteDMAMem			XRAUDIO_SPUwriteDMAMem
#define SPUasync				XRAUDIO_SPUasync
#define SPUupdate				XRAUDIO_SPUupdate
#define SPUplayADPCMchannel		XRAUDIO_SPUplayADPCMchannel
#define SPUinit					XRAUDIO_SPUinit
#define SPUopen					XRAUDIO_SPUopen
#define SPUsetConfigFile		XRAUDIO_SPUsetConfigFile
#define SPUclose				XRAUDIO_SPUclose
#define SPUshutdown				XRAUDIO_SPUshutdown
#define SPUtest					XRAUDIO_SPUtest
#define SPUconfigure			XRAUDIO_SPUconfigure
#define SPUabout				XRAUDIO_SPUabout
#define SPUregisterCallback		XRAUDIO_SPUregisterCallback
#define SPUregisterCDDAVolume   XRAUDIO_SPUregisterCDDAVolume
#define SPUwriteRegister		XRAUDIO_SPUwriteRegister
#define SPUreadRegister			XRAUDIO_SPUreadRegister
#define SPUfreeze				XRAUDIO_SPUfreeze
#define SPUplayCDDAchannel      XRAUDIO_SPUplayCDDAchannel





#define ReadConfig				XRAUDIO_SPUReadConfig
#define ReadConfigFile			XRAUDIO_SPUReadConfigFile
#define iDebugMode				XRAUDIO_SPUiDebugMode

#define PSEgetLibName           XRAUDIO_SPUPSEgetLibName
#define PSEgetLibType           XRAUDIO_SPUPSEgetLibType
#define PSEgetLibVersion        XRAUDIO_SPUPSEgetLibVersion

#define build                   XRAUDIO_SPUbuild
#define revision                XRAUDIO_SPUrevision
#define version                 XRAUDIO_SPUversion

#define iReverbRepeat			XRAUDIO_iReverbRepeat
#define iReverbOff				XRAUDIO_iReverbOff
#define sRVBStart				XRAUDIO_sRVBStart
#define spuCtrl					XRAUDIO_spuCtrl
#define sRVBPlay				XRAUDIO_sRVBPlay
#define sRVBEnd	XRAUDIO_sRVBEnd
#define XAFeed XRAUDIO_XAFeed
#define XAPlay XRAUDIO_XAPlay
#define iLeftXAVol XRAUDIO_iLeftXAVol
#define iRightXAVol XRAUDIO_iRightXAVol
#define XAEnd XRAUDIO_XAEnd
#define XAStart XRAUDIO_XAStart
#define XARepeat XRAUDIO_XARepeat
#define XALastVal XRAUDIO_XALastVal
#define bSPUIsOpen XRAUDIO_bSPUIsOpen
#define xapGlobal XRAUDIO_xapGlobal
#define iXAPitch XRAUDIO_iXAPitch
#define dwNoiseVal XRAUDIO_dwNoiseVal 
#define iUseInterpolation XRAUDIO_iUseInterpolation
#define iSpuAsyncWait XRAUDIO_iSpuAsyncWait
#define bSpuInit XRAUDIO_bSpuInit
#define dwNewChannel XRAUDIO_dwNewChannel
#define bEndThread XRAUDIO_bEndThread
#define irqCallback XRAUDIO_irqCallback
#define pSpuIrq XRAUDIO_pSpuIrq
#define iDisStereo XRAUDIO_iDisStereo
#define pMixIrq XRAUDIO_pMixIrq
#define iCycle XRAUDIO_iCycle
#define irqQSound XRAUDIO_irqQSound
#define bThreadEnded XRAUDIO_bThreadEnded
#define iUseDBufIrq XRAUDIO_iUseDBufIrq
#define spuIrq XRAUDIO_spuIrq
#define spuAddr XRAUDIO_spuAddr
#define cddavCallback XRAUDIO_cddavCallback
#define spuStat XRAUDIO_spuStat
#define iRecordMode XRAUDIO_iRecordMode
#define iSPUIRQWait XRAUDIO_iSPUIRQWait
#define iReverbNum XRAUDIO_iReverbNum
#define iUseReverb XRAUDIO_iUseReverb
#define iUseTimer XRAUDIO_iUseTimer
#define iVolume XRAUDIO_iVolume
#define iUseXA XRAUDIO_iUseXA
		
#define TR {printf("[Trace] in function %s, line %d, file %s\n",__FUNCTION__,__LINE__,__FILE__);}

#include "psemuxa.h"
