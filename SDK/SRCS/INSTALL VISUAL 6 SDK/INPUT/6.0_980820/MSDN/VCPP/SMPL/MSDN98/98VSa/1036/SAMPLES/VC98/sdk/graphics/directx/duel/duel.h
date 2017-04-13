/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:	duel.h
 *  Content:	main include file
 *
 *
 ***************************************************************************/

#ifndef DUEL_INCLUDED
#define DUEL_INCLUDED

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include "resource.h"
#include <tchar.h>

/*
 * Application messages
 */

#define UM_LAUNCH       WM_USER
#define UM_ABORT        WM_USER+1
#define UM_RESTARTTIMER WM_USER+2

// program states
enum
{
    PS_SPLASH,
    PS_ACTIVE,
    PS_REST
};

#define     MAX_SCREEN_X    639
#define     MAX_SCREEN_Y    479
#define     MAX_PLAYERNAME  50
#define		MAX_SESSIONNAME 50
#define		MAX_SPNAME		50
#define		MAX_CLASSNAME	50
#define		MAX_WINDOWTITLE 50
#define		MAX_ERRORMSG	256
#define		MAX_FONTNAME	50
#define		MAX_HELPMSG		512

#define     RECEIVE_TIMER_ID    1
#define     RECEIVE_TIMEOUT     1000    // in milliseconds

#define     ENUM_TIMER_ID    2
#define     ENUM_TIMEOUT     500    // in milliseconds

// default window size
#define		MAX_DEFWIN_X	640
#define		MAX_DEFWIN_Y	480


// tree view image info
#define CX_BITMAP		25
#define CY_BITMAP		25
#define NUM_BITMAPS		 2

// registry info
#define DUEL_KEY (TEXT("Software\\Microsoft\\Duel"))

// macros
#define DEBUG_OUT(s) OutputDebugString(s);

/*
 * fn prototypes
 */

int WINAPI		WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
                        int nCmdShow );
long WINAPI		MainWndproc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
BOOL		    InitApplication(HINSTANCE hinst);
void            CleanupApplication(void);
BOOL            LaunchedByLobby(void);
BOOL			ShowError( int err );
HWND			ShowConnectStatus(void);
void            UpdateTitle(void);

#endif

