/*
    global.h

    Main application header file

*/

#include <windows.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <commdlg.h>
#include <stdlib.h>
#include <memory.h>
#include "dialogs.h"

//
// Menu ids
//

#define IDM_LOADBKGND       0x0100
#define IDM_LOADSPRITE      0x0101
#define IDM_PRINT           0x0103
#define IDM_PRINTSETUP      0x0104
#define IDM_EXIT            0x0105
#define IDM_LOADSCENE       0x0106

#define IDM_DEBUG0          0x0800
#define IDM_DEBUG1          (IDM_DEBUG0+1)
#define IDM_DEBUG2          (IDM_DEBUG0+2)
#define IDM_DEBUG3          (IDM_DEBUG0+3)
#define IDM_DEBUG4          (IDM_DEBUG0+4)
#define IDM_REFRESH         0x0810
#define IDM_FILLBKGND       0x0811
#define IDM_REDRAW          0x0812
#define IDM_SHOWUPDATES     0x0813
#define IDM_AUTOUPDATE      0x0814

#define IDM_HELPCONTENTS    0x0900
#define IDM_ABOUT           0x0901

//
// strings
//

#define SZ_SPRITE   "Sprite"    // clipboard format name

//
// Child window ids
//

//
// Raster ops used in drawing
//

#define DSa     0x008800C6L
#define DSx     0x00660046L
#define DSo     0x00EE0086L
#define DSna    0x00220326L

//
// RGB color values
//

#define rgbWhite    RGB(255,255,255)
#define rgbBlack    RGB(0,0,0)

//
// Flags used for the Redraw function
//

#define UPDATE_SCREEN   TRUE
#define NO_UPDATE       FALSE

//
// update system
//

#define WAIT_LOOP               // comment out to use timer ticks
#ifndef WAIT_LOOP
#define TIMER_TICKS
#endif

//
// Various types
//

typedef char huge *HPSTR;
typedef BYTE huge *HPBYTE;

typedef LPBITMAPINFO PDIB;

typedef struct _SPRITE {
    struct _SPRITE FAR *pNext;  // pointer to the next item
    struct _SPRITE FAR *pPrev;  // pointer to the prev item
    PDIB pDIB;                  // The DIB image of the sprite
    int x;                      // X Coordinate of top-left corner
    int y;                      // Y Coordinate of top-left corner
    int z;                      // Z order for sprite
    int vx;                     // X velocity
    int vy;                     // Y velocity
    int width;                  // width of bounding rectangle
    int height;                 // height of bounding rectangle
    BYTE bTopLeft;              // top left pixel value
    COLORREF rgbTopLeft;        // top left pixel color
    BOOL bSelectable;           // TRUE if sprite can be mouse selected
} SPRITE, FAR *PSPRITE;

//
// define a structure used to maintain rectangle lists
// Note: these are allocated on the local heap and we use
// near pointers deliberately for speed.
//

typedef struct _DRAWRECT {
    struct _DRAWRECT *pPrev;    // pointer to the prev one
    struct _DRAWRECT *pNext;    // pointer to the next one
    RECT rc;                    // the data item
} DRAWRECT, *PDRAWRECT;

typedef struct _DRAWRECTLIST {
    PDRAWRECT pHead;                // pointer to the first item
} DRAWRECTLIST, FAR *PDRAWRECTLIST;


//
// macros to access the fields in a BITMAPINFO struct
// field_value = macro(pBitmapInfo)
//

#define BI_WIDTH(pBI)       (int)((pBI)->bmiHeader.biWidth)
#define BI_HEIGHT(pBI)      (int)((pBI)->bmiHeader.biHeight)
#define BI_PLANES(pBI)      ((pBI)->bmiHeader.biPlanes)
#define BI_BITCOUNT(pBI)    ((pBI)->bmiHeader.biBitCount)
#define BI_CLRUSED(pBI)     ((pBI)->bmiHeader.biClrUsed)

//
// macros to access BITMAPINFO fields in a DIB
// field_value = macro(pDIB)
//

#define DIB_WIDTH(pDIB)     (BI_WIDTH((LPBITMAPINFO)(pDIB)))
#define DIB_HEIGHT(pDIB)    (BI_HEIGHT((LPBITMAPINFO)(pDIB)))
#define DIB_PLANES(pDIB)    (BI_PLANES((LPBITMAPINFO)(pDIB)))
#define DIB_BITCOUNT(pDIB)  (BI_BITCOUNT((LPBITMAPINFO)(pDIB)))
#define DIB_CLRUSED(pDIB)   (BI_CLRUSED((LPBITMAPINFO)(pDIB)))
#define DIB_COLORS(pDIB)    (NumDIBColorEntries((LPBITMAPINFO)(pDIB)))
#define DIB_PCLRTAB(pDIB)   ((LPRGBQUAD)(((LPSTR)((LPBITMAPINFO)(pDIB))) \
                            + sizeof(BITMAPINFOHEADER)))
#define DIB_BISIZE(pDIB)    (sizeof(BITMAPINFOHEADER) \
                            + DIB_COLORS(pDIB) * sizeof(RGBQUAD))
#define DIB_PBITS(pDIB)     (((LPSTR)((LPBITMAPINFO)(pDIB))) \
                            + DIB_BISIZE(pDIB))
#define DIB_PBI(pDIB)       ((LPBITMAPINFO)(pDIB))
#define DIB_STORAGEWIDTH(pDIB) ((DIB_WIDTH(pDIB) + 3) & ~3)


//
// global data
//

char *szAppName;                // App name
HINSTANCE hAppInstance;         // app instance
HWND hwndMain;                  // main window handle
TEXTMETRIC tmSysFont;           // system font metrics
HANDLE hAccTable;               // accelerator table
UINT uiCfSprite;                // private clipboard format
PSPRITE pSpriteList;            // pointer to the list of sprites
PDIB pdibBkGnd;                 // background DIB
PDIB pdibOffScreen;             // off-screen DIB for off-screen DC
HDC hdcOffScreen;               // main off-screen DC
LPBITMAPINFO pPalClrTable;      // A 1:1 color lookup table for the os DC
UINT uiTimer;                   // update timer
HPALETTE hpalCurrent;           // the current application palette
BOOL bShowUpdateRects;          // show update rectangles
char szIniFile[_MAX_PATH];      // INI file name
BOOL bAutoUpdate;

//
// memory allocation macros
//

HANDLE __hMem;

#define ALLOCATE(s) ((__hMem = GlobalAlloc(GHND, (DWORD)(s))) ? GlobalLock(__hMem) : NULL)
#define FREE(p) (GlobalUnlock((HANDLE)HIWORD(p)),GlobalFree((HANDLE)HIWORD(p)))
#define SIZE(p) (GlobalSize((HANDLE)HIWORD(p)))

//
// main.c
//

extern LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern UINT cdecl Message(UINT uiBtns, LPSTR lpFormat, ...) ;

//
// init.c
//

extern BOOL InitFirstInstance(HANDLE hInstance);
extern BOOL InitCurrentInstance(HANDLE hInstance, LPSTR lpszCmdLine, int cmdShow);
extern void Terminate(void);
extern void LoadScene(LPSTR pFileName);

//
// help.c
//

extern void About(HWND hWnd);
extern void Help(HWND hWnd, WORD wParam);

//
// file.c
//

// <dwFlags> for PromptForFileName()
#define PFFN_OPENFILE        0x0001    // prompt to open a file
#define PFFN_SAVEFILE        0x0002    // prompt to save a file
#define PFFN_SHOWDEFAULT     0x0004    // init. show what's in <achFileName>
#define PFFN_OVERWRITEPROMPT 0x0008    // prompt the user about overwriting
#define PFFN_UPPERCASE       0x0010    // make the name uppercase

extern char *szOpenFilter;
extern char *szIniFilter;

extern BOOL PromptForFileName(HWND hwndOwner,
                              HANDLE hInst,
                              LPSTR achFileName,
                              WORD cchFileName,
                              LPSTR szCaption,
                              LPSTR szFilter,
                              LPSTR szDefExt,
                              DWORD dwFlags);

//
// print.c
//

extern void Print(HDC hDC);

//
// Debug support
//

extern LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#ifdef DEBUG

    DWORD   __dwEval;
    int __iDebugLevel;

    extern void SetDebugLevel(int i);
    extern void __AssertMsg(LPSTR exp ,LPSTR file, int line);
    extern void cdecl DbgOut(LPSTR lpFormat, ...);

    #define ASSERT(exp) \
        ((exp) ? (void)0 : __AssertMsg((LPSTR)(#exp), (LPSTR)__FILE__, __LINE__))
    #define EVAL(exp) \
        (__dwEval=(DWORD)(exp), (__dwEval) ? (void)0 : __AssertMsg((LPSTR)(#exp), (LPSTR)__FILE__, __LINE__), __dwEval)

    #define dprintf                          DbgOut
    #define dprintf1 if (__iDebugLevel >= 1) DbgOut
    #define dprintf2 if (__iDebugLevel >= 2) DbgOut
    #define dprintf3 if (__iDebugLevel >= 3) DbgOut
    #define dprintf4 if (__iDebugLevel >= 4) DbgOut

#else // not DEBUG

    #define ASSERT(exp) 0
    #define EVAL(exp) (exp)

    #define dprintf  if (0) ((int (*)(char *, ...)) 0)
    #define dprintf1 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf2 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf3 if (0) ((int (*)(char *, ...)) 0)
    #define dprintf4 if (0) ((int (*)(char *, ...)) 0)

#endif // DEBUG

//
// ppdbg.asm
// Debug macros which set, pulse or clear printer port bits
// see ppdbg.asm for details
//

#ifdef PPDBG

    extern void FAR PASCAL ppdbgSet(BYTE mask);
    extern void FAR PASCAL ppdbgClear(BYTE mask);
    extern void FAR PASCAL ppdbgPulse(BYTE mask);

    #define DBGSET(x)   ppdbgSet(x)
    #define DBGCLEAR(x) ppdbgClear(x)
    #define DBGPULSE(x) ppdbgPulse(x)

#else // PPDBG

    #define DBGSET(x)   0
    #define DBGCLEAR(x) 0
    #define DBGPULSE(x) 0

#endif // PPDBG

//
// bkgnd.c
//

extern void LoadBackground(LPSTR pszPath, BOOL bUpdateScreen);

//
// palette.c
//

extern HPALETTE CreateDIBPalette(LPBITMAPINFO lpBmpInfo);
extern LRESULT PaletteMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern HPALETTE CopyPalette(HPALETTE hSrcPal);
extern void SetSysPalColors(HPALETTE hPal);

//
// draw.c
//

extern void RenderDIBOffScreen(PDIB pDIB, int iX, int iY, LPRECT prcClip);
extern void Paint(HDC hDC, LPRECT prcClip);
extern void UpdatePositions(void);
extern void FillBkGnd(void);
extern void Redraw(LPRECT prcClip, BOOL bUpdateScreen);
extern PDRAWRECTLIST CreateDrawRectList(void);
extern void DeleteDrawRectListItem(PDRAWRECTLIST pList, PDRAWRECT pItem);
extern void EmptyDrawRectList(PDRAWRECTLIST pList);
extern void AddDrawRectItem(PDRAWRECTLIST pList, LPRECT pRect);
extern void MergeDrawRectList(PDRAWRECTLIST pList);




//
// sprite.c
//

extern PSPRITE SpriteHitTest(int x, int y);
extern void SetSpritePosition(PSPRITE pSprite, int x, int y, BOOL bUpdate);
extern void GetSpriteRect(PSPRITE pSprite, LPRECT prcSprite);
extern PSPRITE LoadSprite(LPSTR pszPath, BOOL bRedraw);
extern void DeleteSprite(PSPRITE pSprite);
extern void DeleteSpriteList(void);
extern void SetSpriteZOrder(PSPRITE pSprite, WORD z, BOOL bUpdate);
extern void SpriteDialog(PSPRITE pSprite);
extern BOOL IsSpriteSelectable(PSPRITE pSprite);

//
// dib.c
//

extern PDIB LoadDIB(LPSTR pszPath);
extern void DeleteDIB(PDIB pDIB);
extern BYTE GetDIBPixelValue(PDIB pDIB, int x, int y);
extern COLORREF GetDIBPixelColor(PDIB pDIB, int x, int y);
extern BOOL IsWinDIB(LPBITMAPINFOHEADER pBI);
extern void ShowInfo(LPBITMAPINFO lpBmpInfo);
extern WORD NumDIBColorEntries(LPBITMAPINFO lpBmpInfo);
extern PDIB CreateCompatibleDIB(PDIB pOld);
extern HPSTR GetDIBPixelAddress(PDIB pDIB, int x, int y);
extern void MapDIBColorTable(PDIB pdibObj, PDIB pdibRef);

//
// fast.asm
//

extern FAR PASCAL TransCopyDIBBits(HPBYTE pD, 
                                   HPBYTE pS, 
                                   DWORD dwWidth, 
                                   DWORD dwHeight,
                                   DWORD dwScanD,
                                   DWORD dwScanS,
                                   BYTE bTranClr);

extern FAR PASCAL CopyDIBBits(HPBYTE pD, 
                              HPBYTE pS, 
                              DWORD dwWidth, 
                              DWORD dwHeight,
                              DWORD dwScanD,
                              DWORD dwScanS);
