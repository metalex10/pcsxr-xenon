/***************************************************************************
                          draw.c  -  description
                             -------------------
    begin                : Sun Oct 28 2001
    copyright            : (C) 2001 by Pete Bernert
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

#define _IN_DRAW


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <xenos/xe.h>
#include <xenos/xenos.h>
#include <xenos/edram.h>
#include <console/console.h>

#include <ppc/timebase.h>
#include <time/time.h>
#include <time.h>

#include "externals.h"
#include "gpu.h"
#include "draw.h"
#include "prim.h"
#include "menu.h"
#include "interp.h"
#include "swap.h"

// Simple shader
#include "ps.h"
#include "vs.h"
// xbr shader
#include "xbr_5x_ps.h"
#include "xbr_5x_vs.h"
// Shader
//typedef unsigned int DWORD;

#ifdef LZX_GUI
struct XenosDevice * getLzxVideoDevice();
#endif

#define TR {printf("[Trace] in function %s, line %d, file %s\n",__FUNCTION__,__LINE__,__FILE__);}

#ifndef MAX
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#endif

// misc globals
int iResX;
int iResY;
long lLowerpart;
BOOL bIsFirstFrame = TRUE;
BOOL bCheckMask = FALSE;
unsigned short sSetMask = 0;
unsigned long lSetMask = 0;
int iDesktopCol = 16;
int iShowFPS = 0;
int iWinSize;
int iMaintainAspect = 0;
int iUseNoStretchBlt = 0;
int iFastFwd = 0;
int iDebugMode = 0;
int iFVDisplay = 0;
PSXPoint_t ptCursorPoint[8];
unsigned short usCursorActive = 0;

uint32_t dwGPUVersion = 0;
int iGPUHeight = 512;
int iGPUHeightMask = 511;
int GlobalTextIL = 0;
int iTileCheat = 0;

int finalw, finalh;

unsigned char * psxScreen = NULL;
static struct XenosVertexBuffer *vb = NULL;
static struct XenosDevice * g_pVideoDevice = NULL;
static struct XenosShader * g_pVertexShader = NULL;
static struct XenosShader * g_pPixelTexturedShader = NULL;
static struct XenosSurface * g_pTexture = NULL;
static struct XenosSurface * fb = NULL;
static struct XenosDevice _xe;

typedef struct DrawVerticeFormats {
    float x, y, z, w;
    unsigned int color;
    float u, v;
} DrawVerticeFormats;

DrawVerticeFormats Rect[6];

int g_pPitch = 0;
float texturesize[2];

enum {
    UvBottom = 0,
    UvTop,
    UvLeft,
    UvRight
};
/*
float bottom = 0.0f;
float top = 1.0f;
float left = 1.0f;
float right = 0.0f;
 */
float PsxScreenUv[4] = {0.f, 1.0f, 1.0f, 0.f};

float psxRealW = 1024.f;
float psxRealH = 512.f;

// close display

void DestroyDisplay(void) {
}

void CreateTexture(int width, int height) {
    // Create display
    static int old_width = 0;
    static int old_height = 0;

    if ((width != old_width) || (old_height != height)) {

        texturesize[1] = height;
        texturesize[0] = width;

        //printf("Old w:%d - h:%d\r\n", old_width, old_height);
        //printf("New w:%d - h:%d\r\n", width, height);

        PsxScreenUv[UvTop] = (float) width / psxRealW;
        PsxScreenUv[UvLeft] = (float) height / psxRealH;

        // top left
        Rect[0].u = PsxScreenUv[UvBottom];
        Rect[0].v = PsxScreenUv[UvRight];

        // bottom left
        Rect[4].u = Rect[1].u = PsxScreenUv[UvBottom];
        Rect[4].v = Rect[1].v = PsxScreenUv[UvLeft];

        // top right
        Rect[3].u = Rect[2].u = PsxScreenUv[UvTop];
        Rect[3].v = Rect[2].v = PsxScreenUv[UvRight];

        // bottom right
        Rect[5].u = PsxScreenUv[UvTop];
        Rect[5].v = PsxScreenUv[UvLeft];

        vb = Xe_CreateVertexBuffer(g_pVideoDevice, 6 * sizeof (DrawVerticeFormats));
        void *v = Xe_VB_Lock(g_pVideoDevice, vb, 0, 6 * sizeof (DrawVerticeFormats), XE_LOCK_WRITE);
        memcpy(v, Rect, 6 * sizeof (DrawVerticeFormats));
        Xe_VB_Unlock(g_pVideoDevice, vb);

        old_width = width;
        old_height = height;
    }
}

void CreateDisplay(void) {

#ifndef USE_GUI
    g_pVideoDevice = &_xe;
    Xe_Init(g_pVideoDevice);
#else
    // g_video.cpp
    g_pVideoDevice=getVideoDevice();
#endif

    fb = Xe_GetFramebufferSurface(g_pVideoDevice);
    Xe_SetRenderTarget(g_pVideoDevice, fb);

    static const struct XenosVBFFormat vbf = {
        3,
        {
            {XE_USAGE_POSITION, 0, XE_TYPE_FLOAT4},
            {XE_USAGE_COLOR, 0, XE_TYPE_UBYTE4},
            {XE_USAGE_TEXCOORD, 0, XE_TYPE_FLOAT2},
        }
    };

/*
    // simple shader
    void * ps_main = (void*) g_xps_PS;
    void * vs_main = (void*) g_xvs_VS;
*/
    // xbr 5x
    void * ps_main = (void*) g_xps_xbr5x_ps_main;
    void * vs_main = (void*) g_xvs_xbr5x_vs_main;

    g_pPixelTexturedShader = Xe_LoadShaderFromMemory(g_pVideoDevice, (void*) ps_main);
    Xe_InstantiateShader(g_pVideoDevice, g_pPixelTexturedShader, 0);

    g_pVertexShader = Xe_LoadShaderFromMemory(g_pVideoDevice, (void*) vs_main);

    Xe_InstantiateShader(g_pVideoDevice, g_pVertexShader, 0);
    Xe_ShaderApplyVFetchPatches(g_pVideoDevice, g_pVertexShader, 0, &vbf);

#ifndef USE_GUI
    edram_init(g_pVideoDevice);
#endif
    // Create the psxScreen texture
    if (g_pTexture)
        Xe_DestroyTexture(g_pVideoDevice, g_pTexture);

    g_pTexture = Xe_CreateTexture(g_pVideoDevice, psxRealW, psxRealH, 1, XE_FMT_8888 | XE_FMT_ARGB, 0);
    psxScreen = (unsigned char*) Xe_Surface_LockRect(g_pVideoDevice, g_pTexture, 0, 0, 0, 0, XE_LOCK_WRITE);
    g_pPitch = g_pTexture->wpitch;
    Xe_Surface_Unlock(g_pVideoDevice, g_pTexture);

    memset(psxScreen, 0, 1024 * 512 * 2);

    // move it to ini file
    float x = -1.0f;
    float y = -1.0f;
    float w = 2.0f;
    float h = 2.0f;

    // top left
    Rect[0].x = x;
    Rect[0].y = y + h;
    Rect[0].u = PsxScreenUv[UvBottom];
    Rect[0].v = PsxScreenUv[UvRight];
    Rect[0].color = 0;

    // bottom left
    Rect[1].x = x;
    Rect[1].y = y;
    Rect[1].u = PsxScreenUv[UvBottom];
    Rect[1].v = PsxScreenUv[UvLeft];
    Rect[1].color = 0;

    // top right
    Rect[2].x = x + w;
    Rect[2].y = y + h;
    Rect[2].u = PsxScreenUv[UvTop];
    Rect[2].v = PsxScreenUv[UvRight];
    Rect[2].color = 0;

    // top right
    Rect[3].x = x + w;
    Rect[3].y = y + h;
    Rect[3].u = PsxScreenUv[UvTop];
    ;
    Rect[3].v = PsxScreenUv[UvRight];
    Rect[3].color = 0;

    // bottom left
    Rect[4].x = x;
    Rect[4].y = y;
    Rect[4].u = PsxScreenUv[UvBottom];
    Rect[4].v = PsxScreenUv[UvLeft];
    Rect[4].color = 0;

    // bottom right
    Rect[5].x = x + w;
    Rect[5].y = y;
    Rect[5].u = PsxScreenUv[UvTop];
    Rect[5].v = PsxScreenUv[UvLeft];
    Rect[5].color = 0;

    int i = 0;
    for (i = 0; i < 6; i++) {
        Rect[i].z = 0.0;
        Rect[i].w = 1.0;
    }

    CreateTexture(psxRealW, psxRealH);

    Xe_SetClearColor(g_pVideoDevice, 0);
}

#define R(x)    ((x << 19) & 0xf80000)
#define B(x)    ((x << 6) & 0xf800)
#define G(x)    ((x >> 7) & 0xf8)
#define RGB(x)  (R(x)|B(x)|G(x))

#define GCC_SPLIT_BLOCK __asm__ ("");
#define SIZE_OF_BUFFERS   (512*32)        // 512 cache lines


void BlitScreen32(unsigned char * _surf, int32_t x, int32_t y) {
    uint8_t * __restrict  surf = _surf;
    uint8_t * __restrict pD;
    uint32_t * __restrict rdest;
    uint32_t * __restrict destpix;

    uint32_t startxy;
    uint32_t lu;
    uint16_t s,s0, s1, s2, s3, s4, s5, s6, s7;
    uint32_t d0, d1, d2, d3, d4, d5, d6, d7;

    uint16_t row, column;
    uint16_t dx = PreviousPSXDisplay.Range.x1;
    uint16_t dy = PreviousPSXDisplay.DisplayMode.y;

    if (PreviousPSXDisplay.Range.y0) // centering needed?
    {
        memset(surf, 0, (PreviousPSXDisplay.Range.y0 >> 1) * g_pPitch);

        dy -= PreviousPSXDisplay.Range.y0;
        surf += (PreviousPSXDisplay.Range.y0 >> 1) * g_pPitch;

        memset(surf + dy * g_pPitch,
                0, ((PreviousPSXDisplay.Range.y0 + 1) >> 1) * g_pPitch);
    }

    if (PreviousPSXDisplay.Range.x0) {
        for (column = 0; column < dy; column++) {
            destpix = (uint32_t *) (surf + (column * g_pPitch));
            memset(destpix, 0, PreviousPSXDisplay.Range.x0 << 2);
        }
        surf += PreviousPSXDisplay.Range.x0 << 2;
    }

    if (PSXDisplay.RGB24) {
        for (column = 0; column < dy; column++) {
            startxy = ((1024) * (column + y)) + x;
            pD = (uint8_t *) &psxVuw[startxy];
            destpix = (uint32_t *) (surf + (column * g_pPitch));
            for (row = 0; row < dx; row++) {

                lu = *((uint32_t *) pD);
                destpix[row] =
                        0xff000000 | (RED(lu) << 16) | (GREEN(lu) << 8) | (BLUE(lu));
                pD += 3;

            }
        }
    }

    else {
#if 1
        for (column = 0; column < dy; column++) {
            startxy = (1024 * (column + y)) + x;
            destpix = (uint32_t *) (surf + (column * g_pPitch));

            // Prefetch to give us a running start on the first 8 sets of cache lines
            int loop;
            for(loop=0; loop < 1024; loop += 128)
                __asm__ __volatile__("dcbt 0,%0" : : "r" (&psxVuw[startxy]+loop));

            __asm__ __volatile__("dcbz 0,%0" : : "r" (destpix));

            for (row = 0; row < dx; row += 8) {
                rdest = &destpix[row];

                GCC_SPLIT_BLOCK

                s0 = GETLE16(&psxVuw[startxy++]);
                s1 = GETLE16(&psxVuw[startxy++]);
                s2 = GETLE16(&psxVuw[startxy++]);
                s3 = GETLE16(&psxVuw[startxy++]);
                s4 = GETLE16(&psxVuw[startxy++]);
                s5 = GETLE16(&psxVuw[startxy++]);
                s6 = GETLE16(&psxVuw[startxy++]);
                s7 = GETLE16(&psxVuw[startxy++]);

                GCC_SPLIT_BLOCK

                d0 = RGB(s0) | 0xff000000;
                d1 = RGB(s1) | 0xff000000;
                d2 = RGB(s2) | 0xff000000;
                d3 = RGB(s3) | 0xff000000;
                d4 = RGB(s4) | 0xff000000;
                d5 = RGB(s5) | 0xff000000;
                d6 = RGB(s6) | 0xff000000;
                d7 = RGB(s7) | 0xff000000;

                GCC_SPLIT_BLOCK

                rdest[0] = d0;
                rdest[1] = d1;
                rdest[2] = d2;
                rdest[3] = d3;
                rdest[4] = d4;
                rdest[5] = d5;
                rdest[6] = d6;
                rdest[7] = d7;
            }
        }
#else
        for(column=0;column<dy;column++)
        {
            startxy=((1024)*(column+y))+x;
            for(row=0;row<dx;row++)
            {
                s=psxVuw[startxy++];
                *((unsigned long *)((surf)+(column*g_pPitch)+row*4))=
                ((((s<<19)&0xf80000)|((s<<6)&0xf800)|((s>>7)&0xf8))&0xffffff)|0xff000000;
            }
        }

#endif
    }

}

void DoBufferSwap(void) {
    if (bDoVSyncUpdate == FALSE)
        return;

    //printf("DoBufferSwap\r\n");
    finalw = PSXDisplay.DisplayMode.x;
    finalh = PSXDisplay.DisplayMode.y;

    if (finalw == 0 || finalh == 0)
        return;
    // sync
    Xe_Sync(g_pVideoDevice);

    CreateTexture(finalw, finalh);

    BlitScreen32((unsigned char *) psxScreen, PSXDisplay.DisplayPosition.x, PSXDisplay.DisplayPosition.y);

    // refresh texture cache
    Xe_Surface_LockRect(g_pVideoDevice, g_pTexture, 0, 0, 0, 0, XE_LOCK_WRITE);
    Xe_Surface_Unlock(g_pVideoDevice, g_pTexture);

    // disable filter for xbr effect
    g_pTexture->use_filtering = 0;

    Xe_InvalidateState(g_pVideoDevice);
    Xe_SetClearColor(g_pVideoDevice, 1);

    Xe_SetBlendOp(g_pVideoDevice, XE_BLENDOP_ADD);
    Xe_SetSrcBlend(g_pVideoDevice, XE_BLEND_SRCALPHA);
    Xe_SetDestBlend(g_pVideoDevice, XE_BLEND_INVSRCALPHA);

    Xe_SetCullMode(g_pVideoDevice, XE_CULL_NONE);
    Xe_SetStreamSource(g_pVideoDevice, 0, vb, 0, sizeof (DrawVerticeFormats));
    Xe_SetTexture(g_pVideoDevice, 0, g_pTexture);
    Xe_SetShader(g_pVideoDevice, SHADER_TYPE_PIXEL, g_pPixelTexturedShader, 0);
    Xe_SetShader(g_pVideoDevice, SHADER_TYPE_VERTEX, g_pVertexShader, 0);

    // set texture size
    float settings_texture_size[2] = {g_pTexture->width, g_pTexture->height};
    Xe_SetVertexShaderConstantF(g_pVideoDevice, 0, settings_texture_size, 1);
    Xe_SetPixelShaderConstantF(g_pVideoDevice, 0, settings_texture_size, 1);

    Xe_DrawPrimitive(g_pVideoDevice, XE_PRIMTYPE_RECTLIST, 0, 1);

    Xe_Resolve(g_pVideoDevice);
    // while (!Xe_IsVBlank(g_pVideoDevice));//slowdown ...
    Xe_Execute(g_pVideoDevice);
}

void DoClearScreenBuffer(void) // CLEAR DX BUFFER
{
    memset(psxScreen, 0, 1024 * 512 * 2);

    Xe_InvalidateState(g_pVideoDevice);
    Xe_SetClearColor(g_pVideoDevice, 0xFF000000);

    Xe_Resolve(g_pVideoDevice);
    Xe_Sync(g_pVideoDevice);
}

void DoClearFrontBuffer(void) // CLEAR DX BUFFER
{
    memset(psxScreen, 0, 1024 * 512 * 2);

    Xe_InvalidateState(g_pVideoDevice);
    Xe_SetClearColor(g_pVideoDevice, 0xFF000000);

    Xe_Resolve(g_pVideoDevice);
    Xe_Sync(g_pVideoDevice);
}

unsigned long ulInitDisplay(void) {
    CreateDisplay(); // x stuff
    bUsingTWin = FALSE;
    bIsFirstFrame = FALSE; // done

    Xe_InvalidateState(g_pVideoDevice);
    Xe_SetClearColor(g_pVideoDevice, 0xFF000000);

    Xe_Resolve(g_pVideoDevice);
    Xe_Sync(g_pVideoDevice);

    return 100;
}

void CloseDisplay(void) {
    DestroyDisplay();
}

void CreatePic(unsigned char * pMem) {

}

void DestroyPic(void) {

}

void DisplayPic(void) {

}

void ShowGpuPic(void) {
}

void ShowTextGpuPic(void) {
}
