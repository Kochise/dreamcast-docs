
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/**************************************************************************\
*  toolbar.c -- module for the "toolbar" on top of the main window.
*   Includes the window procedure and an initialization routine.
\**************************************************************************/

#include <windows.h>
#include "ttfonts.h"


/* for the initial positioning of the buttons within the toolbar. */
#define SPACEBUTTON 8
#define CXBUTTON ((GetSystemMetrics (SM_CXFULLSCREEN)) /5 -2*SPACEBUTTON)
#define BUTTONTOP    TOOLBARHEIGHT/8
#define BUTTONHEIGHT TOOLBARHEIGHT*3/4
#define BUTTONLEFT(x) ((2*x+1)*SPACEBUTTON + x*CXBUTTON)

#define BORDER     2



int initTB (HWND hwndParent)
{
WNDCLASS  wc;

  wc.style = 0;
  wc.lpfnWndProc = (WNDPROC)ToolBarWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInst;
  wc.hIcon = NULL;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = GetStockObject(LTGRAY_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = TEXT("ToolBar");

  if (!RegisterClass(&wc)) return (FALSE);

  hwndTB = CreateWindow(
      TEXT("ToolBar"),
      NULL,
      WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
      0,0,
      GetSystemMetrics (SM_CXFULLSCREEN),
      TOOLBARHEIGHT,
      hwndParent, NULL, hInst, NULL);

  if (!hwndTB) return (FALSE);

  return TRUE;
}


/**************************************************************************\
*
*  function:  ToolBarWndProc
*
*  input parameters:  normal window procedure parameters.
*
*  global variables:
*   hwndMain - parent of the toolbar.
*
* When the window is created, create the various buttons.  When those
*  buttons send WM_COMMAND messages later, send the messages back to hwndMain.
*
\**************************************************************************/
LRESULT CALLBACK ToolBarWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static HWND  hwndButton, hwndEnumPrinter;
  switch (message) {

    /**********************************************************************\
    *  WM_CREATE
    *
    * Create the various buttons which are on the toolbar.  Once the buttons
    *  are created, set the window ID so that the WM_COMMANDS may be
    *  distinguished.
    \**********************************************************************/
    case WM_CREATE: {
      hwndButton = CreateWindow(
        TEXT("BUTTON"),TEXT("EnumFonts"),
        WS_CHILD | WS_VISIBLE,
        BUTTONLEFT(0),BUTTONTOP, CXBUTTON, BUTTONHEIGHT,
        hwnd, NULL, hInst, NULL);
      SetWindowLong (hwndButton, GWL_ID, TBID_ENUM);

      hwndButton = CreateWindow(
        TEXT("BUTTON"),TEXT("CreateFont"),
        WS_CHILD | WS_VISIBLE,
        BUTTONLEFT(1),BUTTONTOP, CXBUTTON, BUTTONHEIGHT,
        hwnd, NULL, hInst, NULL);
      SetWindowLong (hwndButton, GWL_ID, TBID_CREATE);

      hwndButton = CreateWindow(
        TEXT("BUTTON"),TEXT("GetMetrics"),
        WS_CHILD | WS_VISIBLE ,
        BUTTONLEFT(2),BUTTONTOP, CXBUTTON, BUTTONHEIGHT,
        hwnd, NULL, hInst, NULL);
      SetWindowLong (hwndButton, GWL_ID, TBID_GETTM);

      hwndButton = CreateWindow(
        TEXT("BUTTON"),TEXT("GetFontData"),
        WS_CHILD | WS_VISIBLE ,
        BUTTONLEFT(3),BUTTONTOP, CXBUTTON, BUTTONHEIGHT,
        hwnd, NULL, hInst, NULL);
      SetWindowLong (hwndButton, GWL_ID, TBID_GETFONTDATA);

      hwndEnumPrinter = CreateWindow(
        TEXT("BUTTON"),TEXT("Enum(Printer)"),
        WS_CHILD | WS_VISIBLE,
        BUTTONLEFT(4),BUTTONTOP, CXBUTTON, BUTTONHEIGHT,
        hwnd, NULL, hInst, NULL);
      SetWindowLong (hwndEnumPrinter, GWL_ID, TBID_PRINT);

    } break;


    /**********************************************************************\
    *  WM_COMMAND
    *
    * Send the command messages back to hwndMain.
    *  except for the one to disable the printer button.
    \**********************************************************************/
    case WM_COMMAND:
      if (wParam == IDU_NOPRINTER)
        EnableWindow (hwndEnumPrinter, FALSE);
      else
        PostMessage (hwndMain,message, wParam, lParam);
    break;


    /**********************************************************************\
    *  WM_PAINT
    *
    * Paint two rectangular strips, one on top, one on bottom.
    \**********************************************************************/
    case WM_PAINT : {
      PAINTSTRUCT ps;
      RECT rect;
      HDC hdc;

      hdc = BeginPaint(hwnd, &ps);
      GetClientRect (hwnd, &rect);
      rect.right --;
      rect.bottom --;

      SelectObject (hdc, GetStockObject (BLACK_PEN));
      MoveToEx (hdc, rect.right, rect.top, NULL);
      LineTo (hdc, rect.right, rect.bottom);
      LineTo (hdc, rect.left, rect.bottom);
      SelectObject (hdc, GetStockObject (WHITE_PEN));
      LineTo (hdc, rect.left, rect.top);
      LineTo (hdc, rect.right, rect.top);

      EndPaint (hwnd, &ps);
    } break;


  } /* end switch */
  return (DefWindowProc(hwnd, message, wParam, lParam));
}
