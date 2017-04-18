#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <ddraw.h>
#include <keybd.h>

#include "generic.h"
#include "softkbd.h"
#include "imeui.h"
#include "editbox.h"
#include "shared.h"
#include "indicator.h"
#include "romakana.h"
#include "inputskb.h"
#include "inputkwnd.h"
#include "inputswnd.h"
#include "katakana.h"
#include "swnd.h"
#include "symbols.h"
#include "displayswnd.h"
#include "hiragana.h"
#include "input.h"
#include "kwnd.h"
#include "romanji.h"
#include "display.h"
#include "displaykwnd.h"
#include "displayskb.h"
#include "tkime.h"
#include "ddutil.h"

extern DWORD                       g_dwScreenWidth;            // screen width
extern DWORD                       g_dwScreenHeight;           // screen height
extern HINSTANCE                   g_hinstApp;                 // application's HINSTANCE
extern HWND                        g_hwndApp;                  // application's window handle
extern HWND                        g_hwndappSKB;               // SKB's window handle
extern HWND                        g_hwndappKWND;              // KWND's window handle
extern LPDIRECTDRAW               g_lpdd;                     // pointer to direct draw
extern LPDIRECTDRAWSURFACE        g_lpddsPrimary;             // primary buffer
extern LPDIRECTDRAWSURFACE        g_lpddsBack;                // back buffer
extern LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickApp;
extern LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickAcquired;
