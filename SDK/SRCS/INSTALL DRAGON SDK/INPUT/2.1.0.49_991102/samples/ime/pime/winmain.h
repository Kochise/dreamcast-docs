#ifndef WINMAIN_H
#define WINMAIN_H

extern DWORD                       g_dwScreenWidth;            // screen width
extern DWORD                       g_dwScreenHeight;           // screen height
extern HINSTANCE                   g_hinstApp;                 // application's HINSTANCE
extern HWND                        g_hwndApp;                  // application's window handle
extern HWND                        g_hwndappSKB;               // SKB's window handle
extern HWND                        g_hwndappKWND;              // KWND's window handle
extern LPDIRECTDRAW                g_lpdd;                     // pointer to direct draw
extern LPDIRECTDRAWSURFACE         g_lpddsPrimary;             // primary buffer
extern LPDIRECTDRAWSURFACE         g_lpddsBack;                // back buffer
extern LPDIRECTINPUTDEVICE2        g_pdidevice2JoystickApp;

#endif
