/*
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: rmfull.h
 *
 */
#ifndef __RMFULL_H__
#define __RMFULL_H__

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <search.h>
#include <ddraw.h>
#include <d3d.h>
#include <direct.h>
#include <d3drmwin.h>
#include "d3dapp.h"	    /* prototypes for D3D helper functions */
#include "rmdemo.h"	    /* prototypes for functions to commumicate
			       with each sample */
#include "rmfullrc.h"	    /* defines constants used in rmfull.rc */
#define START_WIN_SIZE 320  /* initial size of the window */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagrmfullglobals {
    HWND hWndMain;	    /* application window handle */
    HINSTANCE hInstApp;	    /* application instance for dialog boxes */
    LPSTR lpCmdLine;	    /* command line parameters */

    LPDIRECT3DRMDEVICE dev;	/* Direct3DRM device */
    LPDIRECT3DRMVIEWPORT view;	/* Direct3DRM viewport through which we view
				   the scene */
    LPDIRECT3DRMFRAME scene;    /* Master frame in which others are placed */
    LPDIRECT3DRMFRAME camera;	/* Frame describing the users POV */

    BOOL bSingleStepMode;	 /* render one frame at a time */
    BOOL bDrawAFrame;		 /* render on this pass of the main loop */
    BOOL bShowFrameRate;	 /* show the frame rate at the top */
    BOOL bShowInfo;		 /* show window information at the bottom */

    BOOL bResized; /* the window has resized or some other drastic change, the
                      entire client area should be cleared */
    BOOL bQuit;	   /* program is about to terminate */

    BOOL bNoTextures;		/* this sample doesn't use any textures */
    BOOL bConstRenderQuality;	/* this sample is not constructed with
				   MeshBuilders and so the RenderQuality
				   cannot be changed */
    D3DRMRENDERQUALITY RenderQuality;	/* current shade mode, fill mode and
					   lighting state */
    D3DRMTEXTUREQUALITY TextureQuality; /* current texture interpolation */
    BOOL bDithering;			/* is dithering on? */
    BOOL bAntialiasing;			/* is antialiasing on? */

    int mouse_buttons;		/* mouse button state */
    int mouse_x;		/* mouse cursor x position */
    int mouse_y;		/* mouse cursor y position */

    int		    CurrDDDriver;		   /* Current DirectDraw driver */
    int		    NumDDDrivers;		   /* Number of DirectDraw drivers */
    D3DAppDDDriver  DDDriver[D3DAPP_MAXDDDRIVERS]; /* DirectDraw drivers information */

    LPDIRECTDRAWSURFACE lpFrameRateBuffer; /* frame rate surface */
    LPDIRECTDRAWSURFACE lpInfoBuffer;	   /* window info surface */
} rmfullglobals;

void __cdecl Msg( LPSTR fmt, ... );
/*
 * STATS.CPP FUNCTION PROTOTYPES
 */
BOOL InitFontAndTextBuffers(void);
BOOL WriteInfoBuffer(void);
BOOL WriteFrameRateBuffer(float fps, long tps);
void ResetFrameRate(void);
BOOL CalculateFrameRate();
BOOL DisplayFrameRate(int* count, LPD3DRECT lpExtents );

#ifdef __cplusplus
};
#endif

#endif // __RMFULL_H__
