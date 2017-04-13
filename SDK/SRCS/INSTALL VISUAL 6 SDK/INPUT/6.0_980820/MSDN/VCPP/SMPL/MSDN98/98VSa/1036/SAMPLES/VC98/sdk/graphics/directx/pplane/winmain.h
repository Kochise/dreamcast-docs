#ifndef WINMAIN_H
#define WINMAIN_H
/*
**-----------------------------------------------------------------------------
**  File:       WinMain.h
**  Purpose:    Sample Window code
**  Notes:
**
**  Copyright (c) 1996 by Microsoft
**, all rights reserved
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**  Include files
**-----------------------------------------------------------------------------
*/

#include "Common.h"



/*
**-----------------------------------------------------------------------------
**  Defines
**-----------------------------------------------------------------------------
*/

#define MIN_WIN_SIZE_X	128
#define MIN_WIN_SIZE_Y  128
#define DEF_WIN_SIZE_X	256
#define DEF_WIN_SIZE_Y  256



/*
**-----------------------------------------------------------------------------
**  Global Variables
**-----------------------------------------------------------------------------
*/

extern HINSTANCE    g_hMainInstance;
extern HWND         g_hMainWindow;
extern HACCEL       g_hMainAccel;

extern LPCTSTR      g_szMainName;
extern LPCTSTR      g_szMainClass;
extern LPCTSTR      g_szMainTitle;
extern LPCTSTR      g_szPaused;

extern INT          g_nExitCode;



/*
**-----------------------------------------------------------------------------
**  Function Prototypes
**-----------------------------------------------------------------------------
*/

// Windows routines
BOOL InitMain (void);
void FiniMain (void);

void RunMain (void);
INT  WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, INT nShowCmd);
BOOL InitMainWindow (void);


/*
**-----------------------------------------------------------------------------
**  End of File
**-----------------------------------------------------------------------------
*/
#endif // End WINMAIN_H


