/*
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: d3dmain.h
 *
 */
#ifndef __D3DMAIN_H__
#define __D3DMAIN_H__

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <search.h>
#include <ddraw.h>
#include <d3d.h>
#include "d3dapp.h"	    /* prototypes for D3D helper functions */
#include "d3dres.h"	    /* defines constants used in d3dmain.rc */
#include "d3ddemo.h"	    /* prototypes for functions to communicate with
			       each sample */
#define START_WIN_SIZE 320  /* initial size of the window */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagd3dmainglobals {
    HWND hWndMain;	    /* application window handle */
    HINSTANCE hInstApp;	    /* application instance for dialog boxes */

    D3DAppRenderState rstate; /* struct describing the current render state */

    BOOL bSingleStepMode;	 /* render one frame at a time */
    BOOL bDrawAFrame;		 /* render on this pass of the main loop */
    BOOL bClearsOn;		 /* clear the back and z-buffer each frame */
    BOOL bShowFrameRate;	 /* show the frame rate at the top */
    BOOL bShowInfo;		 /* show window information at the bottom */
    BOOL bResizingDisabled;	 /* do not allow resizing */

    BOOL bResized; /* the window has resized or some other drastic change, the
                      entire client area should be cleared */
    BOOL bQuit;	   /* program is about to terminate */

    LPDIRECTDRAWSURFACE lpFrameRateBuffer; /* frame rate surface */
    LPDIRECTDRAWSURFACE lpInfoBuffer;	   /* window info surface */
} d3dmainglobals;

void __cdecl Msg( LPSTR fmt, ... );
/*
 * STATS.CPP FUNCTION PROTOTYPES
 */
BOOL InitFontAndTextBuffers(void);
void ReleaseFontAndTextBuffers(void);
BOOL WriteInfoBuffer(void);
BOOL WriteFrameRateBuffer(float fps, long tps);
void ResetFrameRate(void);
BOOL CalculateFrameRate(void);
BOOL DisplayFrameRate(int* count, LPD3DRECT lpExtents );

#ifdef __cplusplus
};
#endif

#endif // __D3DMAIN_H__
