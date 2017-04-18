/********************************************************************
 *  Copyright (C) 1996 Microsoft Corporation.
 *
 *  File:       DIMAIN.CPP
 *  Content:    Sample DirectInput program - main module
 *  Author:     Peter Donnelly
 *  Tool:       Visual C++ 4.0
 *
 ********************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <dinput.h>
#include "input.h"
#include "resource.h"

#define TITLE "DirectInput Demo"
#define NAME "DInput"


/* *******************                                
   Global variables
 ********************* */

extern LPDIRECTINPUTDEVICE lpdiMouse;   
extern LPDIRECTINPUTDEVICE lpdiKeyboard;   
extern BOOL                MouseAcquired;
extern BOOL                KeyboardAcquired;
HWND                       hMainWindow;              
HDC                        hMainDC;
HINSTANCE                  hTheInstance;
POINT MouseXY;
int MouseRB = IDC_OFF;
int AccessRB = IDC_FOREGROUND;

/* ***************************
   Function prototypes
 ***************************** */

BOOL CALLBACK MouseDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK KeyDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


/* **********************************
   MouseDlgProc()
   Callback for mouse settings dialog
 ************************************ */

BOOL CALLBACK MouseDlgProc(HWND  hwndDlg,
                           UINT  uMsg,
                           WPARAM  wParam,
                           LPARAM  lParam)
  {
  DIDEVCAPS        diMouseCaps;
  DIDEVICEINSTANCE diMouseInstance;
  char             *SubTypes[6] = {"","Unknown", "Traditional", "Fingerstick",
                    "Touchpad", "Trackball"};
  DWORD            TheType;
  char             szShort[2];

  switch (uMsg)
    {
    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
        case (IDOK):
        case (IDCANCEL):
          EndDialog(hwndDlg, TRUE);
          break;

        case (IDC_ABSOLUTE):
          MakeAxesAbsolute(TRUE);
          MouseRB = LOWORD(wParam);
        break; 

        case (IDC_RELATIVE):
          MakeAxesAbsolute(FALSE);
          MouseRB = LOWORD(wParam);
          break;

        case (IDC_OFF):
          MouseRB = LOWORD(wParam);
          break; 

        case (IDC_FOREGROUND):
          AccessRB = IDC_FOREGROUND;
          SetMouseAccess(DISCL_FOREGROUND);
          break; 
           
        case (IDC_BACKGROUND):
          AccessRB = IDC_BACKGROUND;
          SetMouseAccess(DISCL_BACKGROUND);
          break;

        case IDC_CONTROLPANEL: 
          lpdiMouse->RunControlPanel(NULL, 0);
          break;
           
      } 
    break;
      
    case WM_INITDIALOG:
        CheckDlgButton(hwndDlg, MouseRB, 1);
        CheckDlgButton(hwndDlg, AccessRB, 1);

        // show capabilities
        diMouseCaps.dwSize = sizeof(diMouseCaps);
        lpdiMouse->GetCapabilities(&diMouseCaps);
        _itoa(diMouseCaps.dwButtons, szShort, 10);
        SetDlgItemText(hwndDlg, IDC_STATIC_BUTTONS, szShort); 
        _itoa(diMouseCaps.dwAxes, szShort, 10);
        SetDlgItemText(hwndDlg, IDC_STATIC_AXES, szShort);

        // show device info
        diMouseInstance.dwSize = sizeof(diMouseInstance);
        lpdiMouse->GetDeviceInfo(&diMouseInstance);
        TheType = GET_DIDEVICE_SUBTYPE(diMouseInstance.dwDevType);
        if (TheType > 6) TheType = 0;
        SetDlgItemText(hwndDlg, IDC_STATIC_TYPE, 
                       SubTypes[TheType]);
        SetDlgItemText(hwndDlg, IDC_STATIC_PRODUCT, 
                       diMouseInstance.tszProductName);
        SetDlgItemText(hwndDlg, IDC_STATIC_FRIENDLY, 
                       diMouseInstance.tszInstanceName);
        return TRUE;

    }
  return FALSE;
  }  // MouseDlgProc


/* **************************************
   KeyDlgProc()
   Callback for keyboard settings dialog
 **************************************** */

BOOL CALLBACK KeyDlgProc(HWND  hwndDlg,
                         UINT  uMsg,
                         WPARAM  wParam,
                         LPARAM  lParam)
  {
  DIDEVICEINSTANCE diKbdInstance;
  char *SubTypes[13] = {"Unknown", "PCXT", "OLIVETTI", "PCAT", "PCENH", "NOKIA1050",
                    "NOKIA9140", "NEC98", "NEC98LAPTOP", "NEC98106",
                    "JAPAN106", "JAPANAX", "J3100"};
  DWORD TheType;

  switch (uMsg)
    {
    case WM_COMMAND:
      switch (LOWORD(wParam))
      {
        case (IDOK):
        case (IDCANCEL):
          EndDialog(hwndDlg, TRUE);
          break;

        case IDC_CONTROLPANEL: 
          lpdiKeyboard->RunControlPanel(NULL, 0);
          break;
           
      } 
    break;
      
    case WM_INITDIALOG:
        CheckDlgButton(hwndDlg, MouseRB, 1);
        CheckDlgButton(hwndDlg, AccessRB, 1);
        diKbdInstance.dwSize = sizeof(diKbdInstance);
        lpdiKeyboard->GetDeviceInfo(&diKbdInstance);
        TheType = GET_DIDEVICE_SUBTYPE(diKbdInstance.dwDevType);
        if (TheType > 13) TheType = 0;
        SetDlgItemText(hwndDlg, IDC_STATIC_TYPE, 
                       SubTypes[TheType]);
        SetDlgItemText(hwndDlg, IDC_STATIC_PRODUCT, 
                       diKbdInstance.tszProductName);
        SetDlgItemText(hwndDlg, IDC_STATIC_FRIENDLY, 
                       diKbdInstance.tszInstanceName);

        return TRUE;

    }
  return FALSE;
  }  // KeyDlgProc



/* ********************************************************* 
   WindowProc()
   This is the function Windows calls in response to messages 
   dispatched in the main loop. 
   ************************************************************ */

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, 
                            WPARAM wParam, LPARAM lParam)
  {
  static HINSTANCE hInstance;
  HRESULT          hres;

  switch( message )
    {
    case WM_CREATE:
      hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
      return 0;

    case WM_COMMAND:
      switch( LOWORD (wParam))
        {
        case ID_SETTINGS_MOUSE:
              DialogBox(hInstance, 
                        MAKEINTRESOURCE(IDD_MOUSEDLG), 
                        hWnd,
                        (DLGPROC) MouseDlgProc);

              break;

        case ID_SETTINGS_KEYBOARD:
              DialogBox(hInstance, 
                        MAKEINTRESOURCE(IDD_KEYDLG), 
                        hWnd,
                        (DLGPROC) KeyDlgProc);

              break;

        case ID_VIEW_KBDBUFFER: 
              hres = FlushKbdBuffer();
              break; 

        case ID_FILE_EXIT:
              SendMessage(hWnd, WM_CLOSE, 0, 0L);
              break;

        }  // switch within WM_COMMAND
        break;

    case WM_ACTIVATE:
      if (!HIWORD(wParam)) ReacquireInputDevices();
      else 
        {
        MouseAcquired = FALSE;                   
        KeyboardAcquired = FALSE;
        }
      return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    } // switch (message)

  return DefWindowProc(hWnd, message, wParam, lParam);

  } /* WindowProc */


/* ******************************************************************
   WinMain()
  ******************************************************************* */

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
  {

  MSG         msg;
  HWND        hwnd;
  WNDCLASS    wc;
  
  hPrevInstance = hPrevInstance;

  // set up and register window class   
  wc.style = 0;
  wc.lpfnWndProc = WindowProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NAME;
  wc.lpszClassName = NAME;
  RegisterClass(&wc);
    
  // Create the window. 
  hwnd = CreateWindow(
    NAME,
    TITLE,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,  // position
    CW_USEDEFAULT, CW_USEDEFAULT,  // size
    HWND_DESKTOP,
    NULL,
    hInstance,
    NULL );

  if(!hwnd) return FALSE;
  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  // get some global handles 
  hMainWindow = hwnd;
  hTheInstance = hInstance;
  hMainDC = GetDC(hwnd);

  // Set up DirectInput and the devices
  if (!InitInput()) 
    {
    MessageBox(hwnd, "Failed to initialize", "Error", 
                           MB_ICONERROR | MB_OK);
    PostQuitMessage(1);
    }

  do
    {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
      if (msg.message == WM_QUIT) break;   // the only way out of the loop
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      }
    else 
      {
      PollMouse();
      PollKeyboard();
      }  
    } // end of loop
  while (1);

  // release the system resources we used
  CleanupInput();

  return msg.wParam;

  } /* WinMain */


/*
   Copyright (c) 1996 Microsoft Corporation
*/
