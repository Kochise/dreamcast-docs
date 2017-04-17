/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Keyboard.hpp

Abstract:

   Include file for Keyboard

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++

#include <tchar.h>
#include <windows.h>
#include <ddraw.h>
#include <dinput.h>
#include <maplusag.h>
#include "CKeyboard.hpp"

// ++++ Classes +++++++++++++++++++++++++++++++++++++++++++++++++++++

// Simple TextBox class to demonstrate Text entry\output
class CTextBox {
public:
    CTextBox(int nX, int nY, int nW, int nH);
    void AddChar(char ch);
    void Output(BOOL fActive);
    void BackSpace();

private:
    char m_rgText[2048];
    int m_iChar;
    int m_nX, m_nY, m_nW, m_nH;
    int m_nCharWidth;
    int m_iMaxChars;

    // Cursor variables
    BOOL m_fDrawCursor;
    int m_nLastCursorFlash;
};

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Output types
enum toutputlevel { OUTPUT_ALL = 0, OUTPUT_FAILURESONLY };

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Error type
typedef int terr;

// ++++ Defines +++++++++++++++++++++++++++++++++++++++++++++++++++++

// DIUtil.cpp defines
#define MAX_CONTROLLERS    4                            // Maximum number of controllers

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

// Keyboard.cpp variables
extern HWND                g_hwndApp;                   // HWND of the application
extern HINSTANCE           g_hinst;                     // HINSTANCE of the application
extern LPDIRECTDRAWSURFACE g_pddsButtons;               // Contains button images
extern CTextBox            *g_ptextbox[MAX_CONTROLLERS];// One textbox per port

// Error.cpp variables
extern toutputlevel g_outputlevel;                      // Amount of detail in error messages
extern terr g_errLast;                                  // Error return code of last function

// DDUtil.cpp variables
extern LPDIRECTDRAW        g_pdd;                       // The DirectDraw object
extern LPDIRECTDRAWSURFACE g_pddsPrimary;               // Primary directdraw surface
extern LPDIRECTDRAWSURFACE g_pddsBack;                  // Back buffer directdraw surface

// DIUtil.cpp variables
extern LPDIRECTINPUT       g_pdi;                       // The DirectInput object
extern CKeyboard           *g_rgpcont[MAX_CONTROLLERS]; // The list of active input devices

// ++++ Global Functions ++++++++++++++++++++++++++++++++++++++++++++

// DDUtil.cpp functions
void FlipBuffers();
BOOL InitDirectDraw();
LPDIRECTDRAWSURFACE LoadBitmapToDDS(LPTSTR tszBitmap);
HRESULT GetSurfaceDesc(LPDDSURFACEDESC pddsurfdesc, LPDIRECTDRAWSURFACE pddsurf);

// DIUtil.cpp functions
BOOL InitDirectInput();
void PollDevices();
void GetDeviceData();
void CheckNewDevices();

// CKeyboard.cpp functions
void OutputKeyboardState(int iPort, CKeyboard *pcont);

// Error.cpp functions
BOOL CheckError(TCHAR *tszErr);
void RetailOutput(TCHAR *tszErr, ...);
#ifdef DEBUG
void DebugOutput(TCHAR *tszErr, ...);
#else
__inline void DebugOutput(TCHAR *tszErr, ...) {};
#endif
