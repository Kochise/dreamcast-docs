/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include "dyndlg.h"

LRESULT APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
LRESULT APIENTRY About(HWND, UINT, WPARAM, LPARAM );

int Create1(HWND);
int Create2(HWND);

LPWORD lpwAlign (LPWORD);
int nCopyAnsiToWideChar (LPWORD, LPSTR);

HINSTANCE ghInst;


/**************************************************************************\
*
*  function:  WinMain()
*
*  input parameters:  c.f. generic sample
*
\**************************************************************************/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
{
    HWND   hwnd;
    MSG    msg;
    HANDLE hLibrary;

    UNREFERENCED_PARAMETER( lpCmdLine );

    ghInst = hInstance;

    /* Check for previous instance.  If none, then register class. */
    if (!hPrevInstance) {
        WNDCLASS  wc;

        wc.style = 0;
        wc.lpfnWndProc = (WNDPROC)MainWndProc;

        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(hInstance, TEXT("dyndlgIcon"));
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = GetStockObject(LTGRAY_BRUSH);
        wc.lpszMenuName = TEXT("dyndlgMenu");
        wc.lpszClassName = TEXT("dyndlg");

        if (!RegisterClass(&wc)) return (FALSE);
    }  /* class registered o.k. */


    /* Create the main window.  Return false if CreateWindow() fails */
    hwnd = CreateWindow(
        TEXT("dyndlg"),
        TEXT("DynDlg"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hwnd) return (FALSE);


    /***** CUSTOM CONTROL
    * Load the DLL containing the custom control.
    *****/
    hLibrary = LoadLibrary (TEXT("..\\spincube\\SPINCUBE.DLL"));
    if (hLibrary == NULL)
      if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE)
        MessageBox (hwnd, TEXT("LoadLibrary (..\\spincube\\SPINCUBE.DLL) が失敗しました。"),
                  TEXT("エラー, このアプリケーションは spincube が必要です"), MB_OK | MB_ICONEXCLAMATION);
      else
        MessageBox (hwnd, TEXT("LoadLibrary (..\\spincube\\SPINCUBE.DLL) failed"),
                  TEXT("Error, this app requires spincube."), MB_OK | MB_ICONEXCLAMATION);

    /***** CUSTOM CONTROL *****/


    /* Demo: Just for fun, start out with one of the dialogs created. */
    PostMessage (hwnd, WM_COMMAND, IDM_DIALOG2, 0);

    /* Loop getting messages and dispatching them. */
    while (GetMessage(&msg,NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    if (hLibrary != NULL) FreeLibrary (hLibrary);

    return (msg.wParam);
}


/***************************************************************************\
*    FUNCTION: MainWndProc
\***************************************************************************/
LRESULT APIENTRY MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {

    /**********************************************************************\
    *  Menu item support.
    *
    \**********************************************************************/
    case WM_COMMAND:
      switch (LOWORD(wParam)) {

        case IDM_DIALOG1:
          Create1 (hwnd);
        break;

        case IDM_DIALOG2:
          Create2 (hwnd);
        break;

        case IDM_HELP:
          WinHelp( hwnd, TEXT("dyndlg.hlp"), HELP_INDEX, (DWORD) NULL );
        break;

        case IDM_ABOUT:
          DialogBox (GetModuleHandle(NULL), TEXT("aboutBox"), hwnd, (DLGPROC)About);
        return 0;

      }  /* end switch */
    break;  /* end wm_command */



    case WM_DESTROY:
      WinHelp( hwnd,  TEXT("dyndlg.hlp"), (UINT) HELP_QUIT, (DWORD) NULL );
      PostQuitMessage(0);
    break;

    } /* end switch */
    return (DefWindowProc(hwnd, message, wParam, lParam));
}


/****************************************************************************
    FUNCTION: About
****************************************************************************/
LRESULT CALLBACK About(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_INITDIALOG)
    return TRUE;
  if ((message == WM_COMMAND) && (LOWORD(wParam) == IDOK)) {
    EndDialog (hwnd, TRUE);
    return TRUE;
  }
  if ((message == WM_SYSCOMMAND) && (wParam == SC_CLOSE)) {
    EndDialog (hwnd, TRUE);
    return TRUE;
  }
  return FALSE;
}




/*+++

    Create the first dialog dynamically.  Notice that we are NOT using
    structures here because too many of the fields are of variable length.
    Instead, just allocate some memory to play with, and start filling in
    the data at that pointer.

    p - pointer which is moved down through the DLGTEMPLATE information.
    pdlgtemplate - pointer to the TOP of the DLGTEMPLATE information.

    Here we create a simple dialog with one item.  The dialog has a title,
    the item has text, and the item class is specified by ordinal.  There
    is no font information.

---*/
Create1(HWND hwnd)
{
  WORD  *p, *pdlgtemplate;
  int   nchar;
  DWORD lStyle;


  /* allocate some memory to play with  */
  pdlgtemplate = p = (PWORD) LocalAlloc (LPTR, 1000);


  /* start to fill in the dlgtemplate information.  addressing by WORDs */
  lStyle = DS_MODALFRAME | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;

  *p++ = LOWORD (lStyle);
  *p++ = HIWORD (lStyle);
  *p++ = 0;          // LOWORD (lExtendedStyle)
  *p++ = 0;          // HIWORD (lExtendedStyle)
  *p++ = 1;          // NumberOfItems
  *p++ = 10;         // x
  *p++ = 10;         // y
  *p++ = 100;        // cx
  *p++ = 100;        // cy
  *p++ = 0;          // Menu
  *p++ = 0;          // Class

  /* copy the title of the dialog */
  if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE)
    nchar = nCopyAnsiToWideChar (p, TEXT("タイトル 1"));
  else
    nchar = nCopyAnsiToWideChar (p, TEXT("Title 1"));
  p += nchar;

  /* add in the wPointSize and szFontName here iff the DS_SETFONT bit on */

  /* make sure the first item starts on a DWORD boundary */
  p = lpwAlign (p);


  /* now start with the first item */
  lStyle = BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD;

  *p++ = LOWORD (lStyle);
  *p++ = HIWORD (lStyle);
  *p++ = 0;          // LOWORD (lExtendedStyle)
  *p++ = 0;          // HIWORD (lExtendedStyle)
  *p++ = 10;         // x
  *p++ = 70;         // y
  *p++ = 80;         // cx
  *p++ = 20;         // cy
  *p++ = IDOK;       // ID

  /* fill in class i.d. Button in this case */
  *p++ = (WORD)0xffff;
  *p++ = (WORD)0x0080;

  /* copy the text of the first item */
  nchar = nCopyAnsiToWideChar (p, TEXT("OK"));
  p += nchar;

  *p++ = 0;  // advance pointer over nExtraStuff WORD

  CreateDialogIndirect (ghInst, (LPDLGTEMPLATE) pdlgtemplate, hwnd, (DLGPROC) About);

  LocalFree (LocalHandle (pdlgtemplate));

  return 0;
}




/*+++

    Create the second dialog dynamically.

    Here we create a dialog which has font information (DS_SETFONT),
    and which has two items with the item class specified by name.

---*/
Create2(HWND hwnd)
{
  WORD  *p, *pdlgtemplate;
  int   nchar;
  DWORD lStyle;

  /* allocate some memory to play with  */
  pdlgtemplate = p = (PWORD) LocalAlloc (LPTR, 1000);


  /* start to fill in the dlgtemplate information.  addressing by WORDs */
  lStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | DS_SETFONT;
  *p++ = LOWORD (lStyle);
  *p++ = HIWORD (lStyle);
  *p++ = 0;          // LOWORD (lExtendedStyle)
  *p++ = 0;          // HIWORD (lExtendedStyle)
  *p++ = 2;          // NumberOfItems
  *p++ = 210;        // x
  *p++ = 10;         // y
  *p++ = 100;        // cx
  *p++ = 100;        // cy
  *p++ = 0;          // Menu
  *p++ = 0;          // Class


  /* copy the title of the dialog */
  if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE)
    nchar = nCopyAnsiToWideChar (p, TEXT("タイトル 2"));
  else
    nchar = nCopyAnsiToWideChar (p, TEXT("Title 2"));
  p += nchar;

  /* Font information because of DS_SETFONT */
  *p++ = 18;     // point size
  nchar = nCopyAnsiToWideChar (p, TEXT("Times New Roman"));  // Face name
  p += nchar;


  /* make sure the first item starts on a DWORD boundary */
  p = lpwAlign (p);

  /* now start with the first item */
  lStyle = BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP;
  *p++ = LOWORD (lStyle);
  *p++ = HIWORD (lStyle);
  *p++ = 0;          // LOWORD (lExtendedStyle)
  *p++ = 0;          // HIWORD (lExtendedStyle)
  *p++ = 10;         // x
  *p++ = 60;         // y
  *p++ = 80;         // cx
  *p++ = 20;         // cy
  *p++ = IDOK;       // ID


  /* fill in class i.d., this time by name */
  nchar = nCopyAnsiToWideChar (p, TEXT("BUTTON"));
  p += nchar;


  /* copy the text of the first item */
  nchar = nCopyAnsiToWideChar (p, TEXT("OK"));
  p += nchar;

  *p++ = 0;  // advance pointer over nExtraStuff WORD

  /* make sure the second item starts on a DWORD boundary */
  p = lpwAlign (p);

#define SS_INMOTION 0x0002  /* from spincube.h */
  lStyle = WS_VISIBLE | WS_CHILD | SS_INMOTION;
  *p++ = LOWORD (lStyle);
  *p++ = HIWORD (lStyle);
  *p++ = 0;          // LOWORD (lExtendedStyle)
  *p++ = 0;          // HIWORD (lExtendedStyle)
  *p++ = 20;         // x
  *p++ = 5;          // y
  *p++ = 65;         // cx
  *p++ = 45;         // cy
  *p++ = 57;         // ID


  /* fill in class i.d., this time by name */

  /***** CUSTOM CONTROL
  * Fill in the class name that is specified in the DLL
  *  See the \q_a\samples\spincube sample for the source to this.
  *****/
  nchar = nCopyAnsiToWideChar (p, TEXT("Spincube"));
  p += nchar;

  /* copy the text of the second item, null terminate the string. */
  nchar = nCopyAnsiToWideChar (p, TEXT(""));
  p += nchar;

  *p++ = 0;  // advance pointer over nExtraStuff WORD

  CreateDialogIndirect (ghInst, (LPDLGTEMPLATE) pdlgtemplate, hwnd, (DLGPROC) About);

  LocalFree (LocalHandle (pdlgtemplate));

  return 0;
}




/*+++

    Helper routine.  Take an input pointer, return closest
     pointer that is aligned on a DWORD (4 byte) boundary.

---*/
LPWORD lpwAlign ( LPWORD lpIn)
{
  ULONG ul;

  ul = (ULONG) lpIn;
  ul +=3;
  ul >>=2;
  ul <<=2;
  return (LPWORD) ul;
}



/*+++

    Helper routine.  Takes second parameter as Ansi string, copies
     it to first parameter as wide character (16-bits / char) string,
     and returns integer number of wide characters (words) in string
     (including the trailing wide char NULL).

---*/
int nCopyAnsiToWideChar (LPWORD lpWCStr, LPSTR lpAnsiIn)
{
  int cchAnsi = lstrlen(lpAnsiIn);

  return MultiByteToWideChar(GetACP(), MB_PRECOMPOSED, lpAnsiIn, cchAnsi, lpWCStr, cchAnsi) + 1;
}
