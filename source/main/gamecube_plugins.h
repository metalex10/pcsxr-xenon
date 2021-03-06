/*  Pcsx - Pc Psx Emulator
 *  Copyright (C) 1999-2002  Pcsx Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef GAMECUBE_PLUGINS_H
#define GAMECUBE_PLUGINS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif
#include "decode_xa.h"
#include "psemu_plugin_defs.h"
#include "plugins.h"

#define SYMS_PER_LIB 32

	typedef struct {
		char* lib;
		int numSyms;

		struct {
			char* sym;
			void* pntr;
		} syms[SYMS_PER_LIB];
	} PluginTable;

	long CDRCIMGplay(unsigned char *time);
	long CDRCIMGgetTN(unsigned char *buffer);
	long CDRCIMGgetTD(unsigned char track, unsigned char *buffer);
	long CDRCIMGreadTrack(unsigned char *time);
	unsigned char *CDRCIMGgetBuffer(void);
	long CDRCIMGplay(unsigned char *time);
	long CDRCIMGstop(void);
	unsigned char* CDRCIMGgetBufferSub(void);
	long CDRCIMGgetStatus(struct CdrStat *stat);
	long CDRCIMGclose(void);
	long CDRCIMGshutdown(void);
	long CDRCIMGinit(void);
	long CDRCIMGopen(void);

	void cdrcimg_set_fname(const char *fname);

	/* PAD */
	//typedef long (* PADopen)(unsigned long *);
	extern long PAD__init(long);
	extern long PAD__shutdown(void);
	extern long PAD__open(void);
	extern long PAD__close(void);
	extern long PAD__readPort1(PadDataS*);
	extern long PAD__readPort2(PadDataS*);
	long PAD__query(void);
	void PAD__registerVibration(void (*callback)(unsigned long, unsigned long));
	unsigned char PAD__poll(unsigned char value);
	unsigned char PAD__startPoll(int pad);
	void PAD__setMode(const int pad, const int mode);

	extern long pokomonPADinit(long);
	extern long pokomonPADshutdown(void);
	extern long pokomonPADopen(void);
	extern long pokomonPADclose(void);
	extern long pokomonPADreadPort1(PadDataS*);
	extern long pokomonPADreadPort2(PadDataS*);
	long pokomonPADquery(void);
	void pokomonPADregisterVibration(void (*callback)(unsigned long, unsigned long));
	unsigned char pokomonPADpoll(unsigned char value);
	unsigned char pokomonPADstartPoll(int pad);
	void pokomonPADsetMode(const int pad, const int mode);

	/* SPU NULL */
	//typedef long (* SPUopen)(void);
	void NULL_SPUwriteRegister(unsigned long reg, unsigned short val);
	unsigned short NULL_SPUreadRegister(unsigned long reg);
	unsigned short NULL_SPUreadDMA(void);
	void NULL_SPUwriteDMA(unsigned short val);
	void NULL_SPUwriteDMAMem(unsigned short * pusPSXMem, int iSize);
	void NULL_SPUreadDMAMem(unsigned short * pusPSXMem, int iSize);
	void NULL_SPUplayADPCMchannel(xa_decode_t *xap);
	long NULL_SPUinit(void);
	long NULL_SPUopen(void);
	void NULL_SPUsetConfigFile(char * pCfg);
	long NULL_SPUclose(void);
	long NULL_SPUshutdown(void);
	long NULL_SPUtest(void);
	void NULL_SPUregisterCallback(void (*callback)(void));
	void NULL_SPUregisterCDDAVolume(void (*CDDAVcallback)(unsigned short, unsigned short));
	char * NULL_SPUgetLibInfos(void);
	void NULL_SPUabout(void);
	long NULL_SPUfreeze(unsigned long ulFreezeMode, SPUFreeze_t *);

	/* SPU PEOPS 1.9 */
	unsigned short CALLBACK PEOPS_SPUreadDMA(void);
	void CALLBACK PEOPS_SPUreadDMAMem(unsigned short * pusPSXMem, int iSize);
	void CALLBACK PEOPS_SPUwriteDMA(unsigned short val);
	void CALLBACK PEOPS_SPUwriteDMAMem(unsigned short * pusPSXMem, int iSize);
	void CALLBACK PEOPS_SPUasync(unsigned long cycle);
	void CALLBACK PEOPS_SPUupdate(void);
	void CALLBACK PEOPS_SPUplayADPCMchannel(xa_decode_t *xap);
	long CALLBACK PEOPS_SPUinit(void);
	long PEOPS_SPUopen(void);
	void PEOPS_SPUsetConfigFile(char * pCfg);
	long CALLBACK PEOPS_SPUclose(void);
	long CALLBACK PEOPS_SPUshutdown(void);
	long CALLBACK PEOPS_SPUtest(void);
	long CALLBACK PEOPS_SPUconfigure(void);
	void CALLBACK PEOPS_SPUabout(void);
	void CALLBACK PEOPS_SPUregisterCallback(void (CALLBACK *callback)(void));
	void CALLBACK PEOPS_SPUregisterCDDAVolume(void (CALLBACK *CDDAVcallback)(unsigned short, unsigned short));
	void CALLBACK PEOPS_SPUplayCDDAchannel(short *pcm, int nbytes);
	void CALLBACK PEOPS_SPUwriteRegister(unsigned long reg, unsigned short val);
	unsigned short CALLBACK PEOPS_SPUreadRegister(unsigned long reg);
	long CALLBACK PEOPS_SPUfreeze(unsigned long ulFreezeMode, SPUFreeze_t * pF);
	
	/* XENON REPAIR AUDIO */
	unsigned short CALLBACK XRAUDIO_SPUreadDMA(void);
	void CALLBACK XRAUDIO_SPUreadDMAMem(unsigned short * pusPSXMem, int iSize);
	void CALLBACK XRAUDIO_SPUwriteDMA(unsigned short val);
	void CALLBACK XRAUDIO_SPUwriteDMAMem(unsigned short * pusPSXMem, int iSize);
	void CALLBACK XRAUDIO_SPUasync(unsigned long cycle);
	void CALLBACK XRAUDIO_SPUupdate(void);
	void CALLBACK XRAUDIO_SPUplayADPCMchannel(xa_decode_t *xap);
	long CALLBACK XRAUDIO_SPUinit(void);
	long XRAUDIO_SPUopen(void);
	void XRAUDIO_SPUsetConfigFile(char * pCfg);
	long CALLBACK XRAUDIO_SPUclose(void);
	long CALLBACK XRAUDIO_SPUshutdown(void);
	long CALLBACK XRAUDIO_SPUtest(void);
	long CALLBACK XRAUDIO_SPUconfigure(void);
	void CALLBACK XRAUDIO_SPUabout(void);
	void CALLBACK XRAUDIO_SPUregisterCallback(void (CALLBACK *callback)(void));
	void CALLBACK XRAUDIO_SPUregisterCDDAVolume(void (CALLBACK *CDDAVcallback)(unsigned short, unsigned short));
	void CALLBACK XRAUDIO_SPUplayCDDAchannel(short *pcm, int nbytes);
	void CALLBACK XRAUDIO_SPUwriteRegister(unsigned long reg, unsigned short val);
	unsigned short CALLBACK XRAUDIO_SPUreadRegister(unsigned long reg);
	long CALLBACK XRAUDIO_SPUfreeze(unsigned long ulFreezeMode, SPUFreeze_t * pF);

	/* CDR */
	long CDR__open(void);
	long CDR__init(void);
	long CDR__shutdown(void);
	long CDR__open(void);
	long CDR__close(void);
	long CDR__getTN(unsigned char *);
	long CDR__getTD(unsigned char, unsigned char *);
	long CDR__readTrack(unsigned char *);
	unsigned char *CDR__getBuffer(void);
	unsigned char *CDR__getBufferSub(void);

	/* NULL GPU */
	//typedef long (* GPUopen)(unsigned long *, char *, char *);
	long GPU__open(void);
	long GPU__init(void);
	long GPU__shutdown(void);
	long GPU__close(void);
	void GPU__writeStatus(unsigned long);
	void GPU__writeData(unsigned long);
	unsigned long GPU__readStatus(void);
	unsigned long GPU__readData(void);
	long GPU__dmaChain(unsigned long *, unsigned long);
	void GPU__updateLace(void);

	/* PEOPS GPU */
	long PEOPS_GPUopen(unsigned long *, char *, char *);
	long PEOPS_GPUinit(void);
	long PEOPS_GPUshutdown(void);
	long PEOPS_GPUclose(void);
	void PEOPS_GPUwriteStatus(unsigned long);
	void PEOPS_GPUwriteData(unsigned long);
	void PEOPS_GPUwriteDataMem(unsigned long *, int);
	unsigned long PEOPS_GPUreadStatus(void);
	unsigned long PEOPS_GPUreadData(void);
	void PEOPS_GPUreadDataMem(unsigned long *, int);
	long PEOPS_GPUdmaChain(unsigned long *, unsigned long);
	void PEOPS_GPUupdateLace(void);
	void PEOPS_GPUdisplayText(char *);
	long PEOPS_GPUfreeze(unsigned long, GPUFreeze_t *);
	void PEOPS_GPUvBlank(int val);
	void PEOPS_GPUvisualVibration(uint32_t iSmall, uint32_t iBig);
	void PEOPS_GPUmakeSnapshot(void);
	void PEOPS_GPUcursor(int iPlayer, int x, int y);
	void PEOPS_GPUaddVertex(short sx, short sy, s64 fx, s64 fy, s64 fz);

	/* hw gpu plugins */
	long HW_GPUopen(unsigned long *, char *, char *);
	long HW_GPUinit(void);
	long HW_GPUshutdown(void);
	long HW_GPUclose(void);
	void HW_GPUwriteStatus(unsigned long);
	void HW_GPUwriteData(unsigned long);
	void HW_GPUwriteDataMem(unsigned long *, int);
	unsigned long HW_GPUreadStatus(void);
	unsigned long HW_GPUreadData(void);
	void HW_GPUreadDataMem(unsigned long *, int);
	long HW_GPUdmaChain(unsigned long *, unsigned long);
	void HW_GPUupdateLace(void);
	void HW_GPUdisplayText(char *);
	long HW_GPUfreeze(unsigned long, GPUFreeze_t *);
	void HW_GPUvBlank(int val);
	void HW_GPUvisualVibration(uint32_t iSmall, uint32_t iBig);
	void HW_GPUmakeSnapshot(void);
	void HW_GPUcursor(int iPlayer, int x, int y);
	void HW_GPUaddVertex(short sx, short sy, s64 fx, s64 fy, s64 fz);

	//dfinput
	char *INPUT_PSEgetLibName(void);
	uint32_t INPUT_PSEgetLibType(void);
	uint32_t INPUT_PSEgetLibVersion(void);
	long INPUT_PADinit(long flags);
	long INPUT_PADshutdown(void);
	long INPUT_PADopen(unsigned long *Disp);
	long INPUT_PADclose(void);
	long INPUT_PADquery(void);
	unsigned char INPUT_PADstartPoll(int pad);
	unsigned char INPUT_PADpoll(unsigned char value);
	long INPUT_PADreadPort1(PadDataS *pad);
	long INPUT_PADreadPort2(PadDataS *pad);
	long INPUT_PADkeypressed(void);
	long INPUT_PADconfigure(void);
	void INPUT_PADabout(void);
	long INPUT_PADtest(void);
	void INPUT_PADregisterVibration(void (*callback)(uint32_t, uint32_t));

	void INPUT_PADsetMode(const int pad, const int mode);
	
	#define EMPTY_PLUGIN \
{ NULL,      \
0,         \
{ { NULL,  \
NULL }, } }
	
#define DF_PAD1_PLUGIN \
{ "/PAD1",      \
10,         \
{ { "PADinit",  \
INPUT_PADinit }, \
{ "PADshutdown",	\
INPUT_PADshutdown}, \
{ "PADopen", \
INPUT_PADopen}, \
{ "PADclose", \
INPUT_PADclose}, \
{ "PADquery", \
INPUT_PADquery}, \
{ "PADpoll", \
INPUT_PADpoll}, \
{ "PADstartPoll", \
INPUT_PADstartPoll}, \
{ "PADregisterVibration", \
INPUT_PADregisterVibration}, \
{ "PADsetMode", \
INPUT_PADsetMode}, \
{ "PADreadPort1", \
INPUT_PADreadPort1} \
} \
}

#define DF_PAD2_PLUGIN \
{ "/PAD2",      \
10,         \
{ { "PADinit",  \
INPUT_PADinit }, \
{ "PADshutdown",	\
INPUT_PADshutdown}, \
{ "PADopen", \
INPUT_PADopen}, \
{ "PADclose", \
INPUT_PADclose}, \
{ "PADquery", \
INPUT_PADquery}, \
{ "PADpoll", \
INPUT_PADpoll}, \
{ "PADstartPoll", \
INPUT_PADstartPoll}, \
{ "PADregisterVibration", \
INPUT_PADregisterVibration}, \
{ "PADsetMode", \
INPUT_PADsetMode}, \
{ "PADreadPort2", \
INPUT_PADreadPort2} \
} \
}

#define PAD1_PLUGIN \
{ "/PAD1",      \
5,         \
{ { "PADinit",  \
PAD__init }, \
{ "PADshutdown",	\
PAD__shutdown}, \
{ "PADopen", \
PAD__open}, \
{ "PADclose", \
PAD__close}, \
{ "PADreadPort1", \
PAD__readPort1} \
} \
}

#define PAD2_PLUGIN \
{ "/PAD2",      \
5,         \
{ { "PADinit",  \
PAD__init }, \
{ "PADshutdown",	\
PAD__shutdown}, \
{ "PADopen", \
PAD__open}, \
{ "PADclose", \
PAD__close}, \
{ "PADreadPort2", \
PAD__readPort2} \
} \
}

#define SPU_PEOPS_PLUGIN \
{ "/SPU",      \
18,         \
{ { "SPUinit",  \
PEOPS_SPUinit }, \
{ "SPUshutdown",	\
PEOPS_SPUshutdown}, \
{ "SPUopen", \
PEOPS_SPUopen}, \
{ "SPUclose", \
PEOPS_SPUclose}, \
{ "SPUconfigure", \
PEOPS_SPUsetConfigFile}, \
{ "SPUabout", \
PEOPS_SPUabout}, \
{ "SPUtest", \
PEOPS_SPUtest}, \
{ "SPUwriteRegister", \
PEOPS_SPUwriteRegister}, \
{ "SPUreadRegister", \
PEOPS_SPUreadRegister}, \
{ "SPUwriteDMA", \
PEOPS_SPUwriteDMA}, \
{ "SPUreadDMA", \
PEOPS_SPUreadDMA}, \
{ "SPUwriteDMAMem", \
PEOPS_SPUwriteDMAMem}, \
{ "SPUreadDMAMem", \
PEOPS_SPUreadDMAMem}, \
{ "SPUplayADPCMchannel", \
PEOPS_SPUplayADPCMchannel}, \
{ "SPUfreeze", \
PEOPS_SPUfreeze}, \
{ "SPUregisterCallback", \
PEOPS_SPUregisterCallback}, \
{ "SPUregisterCDDAVolume", \
PEOPS_SPUregisterCDDAVolume}, \
{ "SPUasync", \
PEOPS_SPUasync} \
} }
	
	
	
#define SPU_XENON_PLUGIN \
{ "/SPU",      \
21,         \
{ { "SPUinit",  \
XRAUDIO_SPUinit }, \
{ "SPUshutdown",	\
XRAUDIO_SPUshutdown}, \
{ "SPUopen", \
XRAUDIO_SPUopen}, \
{ "SPUclose", \
XRAUDIO_SPUclose}, \
{ "SPUconfigure", \
XRAUDIO_SPUsetConfigFile}, \
{ "SPUabout", \
XRAUDIO_SPUabout}, \
{ "SPUtest", \
XRAUDIO_SPUtest}, \
{ "SPUwriteRegister", \
XRAUDIO_SPUwriteRegister}, \
{ "SPUreadRegister", \
XRAUDIO_SPUreadRegister}, \
{ "SPUwriteDMA", \
XRAUDIO_SPUwriteDMA}, \
{ "SPUreadDMA", \
XRAUDIO_SPUreadDMA}, \
{ "SPUwriteDMAMem", \
XRAUDIO_SPUwriteDMAMem}, \
{ "SPUreadDMAMem", \
XRAUDIO_SPUreadDMAMem}, \
{ "SPUplayADPCMchannel", \
XRAUDIO_SPUplayADPCMchannel}, \
{ "SPUfreeze", \
XRAUDIO_SPUfreeze}, \
{ "SPUregisterCallback", \
XRAUDIO_SPUregisterCallback}, \
{ "SPUregisterCDDAVolume", \
XRAUDIO_SPUregisterCDDAVolume}, \
{ "SPUasync", \
XRAUDIO_SPUasync}, \
{ "SPUupdate", \
XRAUDIO_SPUupdate}, \
{ "SPUplayCDDAchannel", \
XRAUDIO_SPUplayCDDAchannel} \
} }

#define GPU_PEOPS_PLUGIN \
{ "/GPU",      \
18,         \
{ { "GPUinit",  \
PEOPS_GPUinit }, \
{ "GPUshutdown",	\
PEOPS_GPUshutdown}, \
{ "GPUopen", \
PEOPS_GPUopen}, \
{ "GPUclose", \
PEOPS_GPUclose}, \
{ "GPUwriteStatus", \
PEOPS_GPUwriteStatus}, \
{ "GPUwriteData", \
PEOPS_GPUwriteData}, \
{ "GPUwriteDataMem", \
PEOPS_GPUwriteDataMem}, \
{ "GPUreadStatus", \
PEOPS_GPUreadStatus}, \
{ "GPUreadData", \
PEOPS_GPUreadData}, \
{ "GPUreadDataMem", \
PEOPS_GPUreadDataMem}, \
{ "GPUdmaChain", \
PEOPS_GPUdmaChain}, \
{ "GPUdisplayText", \
PEOPS_GPUdisplayText}, \
{ "GPUfreeze", \
PEOPS_GPUfreeze}, \
{ "GPUmakeSnapshot", \
PEOPS_GPUmakeSnapshot}, \
{ "GPUvBlank", \
PEOPS_GPUvBlank}, \
{ "GPUvisualVibration", \
PEOPS_GPUvisualVibration}, \
{ "GPUcursor", \
PEOPS_GPUcursor}, \
{ "GPUupdateLace", \
PEOPS_GPUupdateLace} \
} }

	// HW GPU
#define GPU_HW_PEOPS_PLUGIN \
{ "/GPU",      \
18,         \
{ { "GPUinit",  \
HW_GPUinit }, \
{ "GPUshutdown",	\
HW_GPUshutdown}, \
{ "GPUopen", \
HW_GPUopen}, \
{ "GPUclose", \
HW_GPUclose}, \
{ "GPUwriteStatus", \
HW_GPUwriteStatus}, \
{ "GPUwriteData", \
HW_GPUwriteData}, \
{ "GPUwriteDataMem", \
HW_GPUwriteDataMem}, \
{ "GPUreadStatus", \
HW_GPUreadStatus}, \
{ "GPUreadData", \
HW_GPUreadData}, \
{ "GPUreadDataMem", \
HW_GPUreadDataMem}, \
{ "GPUdmaChain", \
HW_GPUdmaChain}, \
{ "GPUdisplayText", \
HW_GPUdisplayText}, \
{ "GPUfreeze", \
HW_GPUfreeze}, \
{ "GPUmakeSnapshot", \
HW_GPUmakeSnapshot}, \
{ "GPUvisualVibration", \
HW_GPUvisualVibration}, \
{ "GPUcursor", \
HW_GPUcursor}, \
{ "GPUupdateLace", \
HW_GPUupdateLace}, \
{ "GPUaddVertex", \
HW_GPUaddVertex}, \
{ "GPUvBlank", \
HW_GPUvBlank}, \
} }
	/*
	{ "GPUaddVertex", \
	PEOPS_GPUaddVertex} \
	 */

#define CDRCIMG_PLUGIN \
{ "/CDRCIMG",      \
13,         \
{ { "CDRinit",  \
CDRCIMGinit }, \
{ "CDRshutdown",	\
CDRCIMGshutdown}, \
{ "CDRopen", \
CDRCIMGopen}, \
{ "CDRclose", \
CDRCIMGclose}, \
{ "CDRgetStatus", \
CDRCIMGgetStatus}, \
{ "CDRgetTN", \
CDRCIMGgetTN}, \
{ "CDRgetTD", \
CDRCIMGgetTD}, \
{ "CDRplay", \
CDRCIMGplay}, \
{ "CDRstop", \
CDRCIMGstop}, \
{ "CDRreadTrack", \
CDRCIMGreadTrack}, \
{ "CDRgetBuffer", \
CDRCIMGgetBuffer}, \
{ "CDRgetBufferSub", \
CDRCIMGgetBufferSub} \
} \
}

#define POKOMON_PAD1_PLUGIN \
{ "/PAD1",      \
8,         \
{ { "PADinit",  \
pokomonPADinit }, \
{ "PADshutdown",	\
pokomonPADshutdown}, \
{ "PADopen", \
pokomonPADopen}, \
{ "PADclose", \
pokomonPADclose}, \
{ "PADreadPort1", \
pokomonPADreadPort1}, \
{ "PADstartPoll", \
pokomonPADstartPoll}, \
{ "PADpoll", \
pokomonPADpoll}, \
{ "PADquery", \
pokomonPADquery}, \
} \
}

#define POKOMON_PAD2_PLUGIN \
{ "/PAD2",      \
8,         \
{ { "PADinit",  \
pokomonPADinit }, \
{ "PADshutdown",	\
pokomonPADshutdown}, \
{ "PADopen", \
pokomonPADopen}, \
{ "PADclose", \
pokomonPADclose}, \
{ "PADreadPort2", \
pokomonPADreadPort2}, \
{ "PADstartPoll", \
pokomonPADstartPoll}, \
{ "PADpoll", \
pokomonPADpoll}, \
{ "PADquery", \
pokomonPADquery}, \
} \
}


#ifdef __cplusplus
}
#endif

#endif
