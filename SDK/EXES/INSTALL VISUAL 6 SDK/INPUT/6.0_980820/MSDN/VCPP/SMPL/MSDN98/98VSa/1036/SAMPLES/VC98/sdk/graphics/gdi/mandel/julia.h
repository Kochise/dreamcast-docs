/******************************Module*Header*******************************\
* Module Name: julia.h
*
* Header file for Julia.c
*
* Created: 24-Oct-1991 18:15:12
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* Contains the #define values for the menu items' id and handy globals
*
* Dependencies:
*       none
*
\**************************************************************************/

#include <string.h>
#include <winspool.h>
#include <drivinit.h>
#include "jtypes.h"
#include "bndscan.h"
#include "dibmp.h"
#include "printer.h"

//
// A large number.  Used in all the fix-point versions of the fractal
// generation algorithms.
//
#define FIRST_PIXEL     429496796

//
// Threshold value (pixels) for blting drawing from shadow bitmap to
// screen.  Used in fractal drawing algorithm.  Minimize device access.
//
#define BATCH           25000

//
// menu item IDs
//
#define MM_ABOUT        8000
#define MM_JULIA	8001
#define MM_MANDEL  	8002
#define MM_RLEVIEWER    8006
#define MM_SAVE 	8003
#define MM_SAVE_MONO    8004
#define MM_LOAD 	8005

#define MM_CREATE_JULIA_THREAD	7001
#define MM_SET_XFORM_ATTR	7002
#define MM_CREATE_MANDEL_THREAD	7003

#define MM_FLOAT        7009
#define MM_FIX          7010

#define MM_TP_IDLE              7030
#define MM_TP_LOW               7031
#define MM_TP_BELOW_NORMAL      7032
#define MM_TP_NORMAL            7033
#define MM_TP_ABOVE_NORMAL      7034
#define MM_TP_HIGH              7035
#define MM_TP_TIME_CRITICAL     7036
#define MM_ITERATION_100        7011
#define MM_ITERATION_500        7012
#define MM_ITERATION_1000       7013
#define MM_ITERATION_5000       7014
#define MM_ITERATION_DOUBLE     7015
#define MM_STEP_ONE             7016
#define MM_STEP_TWO             7017
#define MM_STEP_THREE           7018
#define MM_STRETCHBLT           7019
#define MM_BITBLT               7020
#define MM_BLACKONWHITE         7021
#define MM_COLORONCOLOR         7022
#define MM_WHITEONBLACK         7023
#define MM_HALFTONE             7024
#define MM_OPT_4                7025
#define MM_CLIP                 7026
#define MM_RM_CLIP              7027
#define MM_ERASE                7028
#define MM_SETDIB2DEVICE        7029

// defined in bndscan.h
//
// #define MM_SELCLIPRGN           7050

// defined in printer.h
//
// #define MM_PORTRAIT             7040
// #define MM_LANDSCAPE            7041
// #define MM_PRINTER              9000


#define MM_RLELOAD_DEMO     9800
#define MM_RLELOAD          9801
#define MM_RLESAVE          9802
#define MM_CLEAR            9803
#define MM_RLEPLAY          9804
#define MM_RLEPLAYCONT      9805

#define IDM_CASCADE	30
#define IDM_TILE	31
#define IDM_ARRANGE	32
#define IDM_CLOSEALL	33

//
// Resource IDs
//
#define ACCEL_ID        100
#define APPICON         1001
#define VIEWICON        1003
#define PAINTCURSOR     1002

//
// Handy globals
//
extern HPEN   hpnRed;
extern HPEN   hpnBlack;
extern HPEN   hpnGreen;
extern INT    giPen;
 
extern HANDLE ghModule;
extern HWND   ghwndMain;
extern HWND   ghwndClient;
extern HANDLE ghAccel;

extern HMENU  hMenu, hChildMenu, hViewMenu;
extern HMENU  hViewSubOne, hSubMenuOne, hSubMenuThree;
extern HMENU  hPrinterMenu;

extern CHAR   gszFile[20];
extern CHAR   gszMapName[20];
extern char   gtext[256];

extern BOOL   gFloat;
extern LONG   gStep;
extern LONG   gIteration;
extern BOOL   gbStretch;
extern INT    giStretchMode;
extern INT    giDmOrient;
extern INT    giNPrinters;

extern HPALETTE        ghPal, ghPalOld;

extern double xFrom, xTo, yFrom, yTo, c1, c2;
extern LONG   lxFrom, lxTo, lyFrom, lyTo, lc1, lc2;

extern PPRINTER_INFO_1     gpPrinters;
extern PSZ                *gpszPrinterNames;
extern PSZ                *gpszDeviceNames;

BOOL bCycle(HWND);
BOOL bCleanupPrinter(VOID);
INT  iCreatePenFrPal(HDC, PVOID *, INT, HPALETTE *);
BOOL bBoundaryScanFix(PINFO);
BOOL bChangeDIBColor(HDC, PINFO, INT);
BOOL bInitPrinter(HWND);
BOOL bCleanupPrinter(VOID);
BOOL SaveBitmapFile(HDC, HBITMAP, PSTR);
BOOL LoadBitmapFile(HDC, PINFO, PSTR);

HPALETTE CopyPalette(HPALETTE);

//void cdecl ErrorOut(char errstring[30]);
LPTSTR GetStringRes (int id);

#define IDS_NO_BITMAP               100
#define IDS_CYCLE_THREAD_QUIT       101
#define IDS_CYCLE_THREAD            102
#define IDS_IVALID_PEN_WIDTH        103
#define IDS_MANDEL_DREAM            104
#define IDS_JULIA                   105
#define IDS_MANDELBROT              106
#define IDS_VIEWER                  107
#define IDS_CLICK_HERE_VIEW         108
#define IDS_ITER_100                109
#define IDS_ITER_500                110
#define IDS_ITER_1000               111
#define IDS_ITER_5000               112
#define IDS_ITERATION               113
#define IDS_FILE_LIST1              114
#define IDS_FILE_LIST2              115
#define IDS_FILE_LIST3              116
#define IDS_SAVING_MONO_BITMAP      117
#define IDS_BOUNDARY                118
#define IDS_NO_SAVED_BITMAP         119
#define IDS_ELAPSED_TIME            120
#define IDS_STEP                    121
#define IDS_FLOATING_PT             122
#define IDS_FIXED_PT                123
#define IDS_SELECT_DRAW_SET         124
#define IDS_LOADING_BITMAPS         125
#define IDS_SAVING_MEMORY_RLE       126
#define IDS_SAVING_LOADED_BMP       127
#define IDS_DISCARD_LOADED_BMP      128
#define IDS_PLAY_LOADED_BMP         129
#define IDS_PLAY_BMP_CONT           130
#define IDS_FRAMES                  131
#define IDS_FILES                   132
#define IDS_CONT_PLAY               133
#define IDS_SINGLE_PLAY             134
#define IDS_MOUSE                   135
#define IDS_DRAWING                 136
#define IDS_DRAWING_DONE            137
#define IDS_NO_BITMAP_TO_DRAW       138
#define IDS_NO_RLE_TO_SAVE          139
#define IDS_PLAY_THREAD_END         140
#define IDS_PLAY_THREAD             141
#define IDS_ERR_NOT_A_DIB           142
#define IDS_ERR_CANT_ENUM_PRINTERS  143
#define IDS_NO_BITMAP_TO_SAVE       144
#define IDS_FILE_OPEN_FAILED        145
#define IDS_BITMAP_NOT_CREATED      146
