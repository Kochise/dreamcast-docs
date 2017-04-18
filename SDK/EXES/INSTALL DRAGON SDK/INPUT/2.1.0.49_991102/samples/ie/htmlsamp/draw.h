#ifndef __DRAW_H                // guard against multiple inclusion
#define __DRAW_H

/********************************************************************
 * draw.h
 *
 * Description
 *     DDraw wrappers and helpers
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <ddraw.h>              // DDraw data types and prototypes

/********************************************************************
 * Forward declarations
 ********************************************************************/
class CWindow;                  // window.h

/********************************************************************
 * Defines - Window/Screen
 ********************************************************************/
#define SCREEN_DEFAULT    0

/********************************************************************
 * Public functions - Create/Destroy
 ********************************************************************/
void                CreateDirectDraw(HWND hwndMain);
void                DestroyDirectDraw(void);

/********************************************************************
 * Public functions - Helpers
 ********************************************************************/
LPDIRECTDRAWSURFACE CreateBitmapSurface(LPCTSTR pszResource, WORD nWidth, WORD nHeight, BOOL bTransparent, COLORREF crTransColor);

/********************************************************************
 * Public functions - Window/Screen
 ********************************************************************/
void                SwitchScreen(WORD nScreen);
void                DrawWaitScreen(WORD x, WORD y, WORD w, WORD h, LPDIRECTDRAWSURFACE pDDSBitmap);
void                LockScreen(void);
void                UnlockScreen(void);
BOOL                IsScreenLocked(void);
void                DrawCurrentScreen(void);
void                SetActiveDisplay(WORD x, WORD y, WORD w, WORD h);
void                AddWindow(CWindow *pWindow, WORD nScreen = SCREEN_DEFAULT);
void                RemoveWindow(CWindow *pWindow, WORD nScreen = SCREEN_DEFAULT);
void                EnableModal(CWindow *pWindow, WORD nScreen = SCREEN_DEFAULT);
void                DisableModal(CWindow *pWindow, WORD nScreen = SCREEN_DEFAULT);
void                MoveAllWindows(short xDelta, short yDelta, WORD nScreen = SCREEN_DEFAULT);

/********************************************************************
 * Public functions - Cursor
 ********************************************************************/
void                HideCursor(WORD nScreen = SCREEN_DEFAULT);
void                ShowCursor(WORD nScreen = SCREEN_DEFAULT);
void                SetCursorType(WORD nCursor, WORD nScreen = SCREEN_DEFAULT);
void                SetCursorPosition(WORD x, WORD y, WORD nScreen = SCREEN_DEFAULT);
POINT               QueryCursorPosition(WORD nScreen = SCREEN_DEFAULT);
void                SetCursorCapture(CWindow *pWindow, WORD nScreen = SCREEN_DEFAULT);
void                ReleaseCursorCapture(CWindow *pWindow, WORD nScreen = SCREEN_DEFAULT);
void                SetCurrentScreenCursorPos(WORD x, WORD y);
POINT               QueryCurrentScreenCursorPos(void);
POINT               QueryCurrentScreenCursorOffset(void);

/********************************************************************
 * Public functions - Controller
 ********************************************************************/
void                SendCurrentScreenJoystick(WPARAM wParam, LPARAM lParam);

/********************************************************************
 * Defines for "cursor" display
 ********************************************************************/
#define CURSOR_SIZE         16          // Cursor dimension in pixel
#define CURSOR_FRAME        4           // # of frames per animate cursor
#define CURSOR_RATE         250         // Cursor refresh rate

/********************************************************************
 * Defines for "cursor" type
 ********************************************************************/
#define CURSOR_GAME         0
#define CURSOR_HTML         1
#define CURSOR_POINTER      2
#define CURSOR_MAX          3

/********************************************************************
 * Defines for "cursor" offsets for each type
 ********************************************************************/
#define CURSOR_GAME_OFFSET_X    8
#define CURSOR_GAME_OFFSET_Y    8
#define CURSOR_HTML_OFFSET_X    8
#define CURSOR_HTML_OFFSET_Y    8
#define CURSOR_POINTER_OFFSET_X 2
#define CURSOR_POINTER_OFFSET_Y 2

/********************************************************************
 * Global variables
 ********************************************************************/
extern LPDIRECTDRAW        g_pDD;
extern LPDIRECTDRAWSURFACE g_pDDSPrimary;
extern LPDIRECTDRAWSURFACE g_pDDSBack;

#endif // __DRAW_H
