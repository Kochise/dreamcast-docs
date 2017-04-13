
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
*  ttfonts.c -- Font enumeration and manipulation program for Win32/NT.
*
* design:  There is a main frame window (hwndMain) with a child toolbar,
*  two child dialogs, and a child demonstration window.  All window handles
*  are global and are accesible to all modules.  There is a module for each
*  of the classes of windows.  Each module contains an initialization routine
*  to register the class and create the window(s).  Each module also contains
*  a window procedure for that class.  The two windows which list all of the
*  fonts are also children of the main window, and they are hidden and shown
*  as needed.
*
*  Communication between windows is via message passing.  The toolbar passes
*  all of its command messages back to the main window.  Other windows pass
*  information back and forth with the following USER defined messages:
*  WMU_LFTODEMO, WMU_DEMOTOLF, WMU_DEMOTOTM...  Rectangles fly on the screen
*  (c.f. flyWinWin) to mirror message trafic, i.e. data flow.
*
\**************************************************************************/

#include <windows.h>
#include "ttfonts.h"


/* Misc. defines for size, color, and appearance of drawing. */
#define GRIDCOLOR  PALETTEINDEX (6)
#define TICKSPACE  20
#define FWW_STEPS  40



TCHAR szMBERROR     [MAX_PATH];
TCHAR szInitString  [MAX_PATH];
TCHAR szAllocFailed [MAX_PATH];
TCHAR szResetDisplay[MAX_PATH];
TCHAR szNoCMAPTable [MAX_PATH];
TCHAR szFontDataErr [MAX_PATH];
TCHAR szCBDataTooBig[MAX_PATH];
TCHAR szNoTable     [MAX_PATH];
TCHAR szFormatNot4  [MAX_PATH];
TCHAR szEnumPrinterR[MAX_PATH];
TCHAR szHelpPathName[] = TEXT("ttfonts.HLP");



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
    MSG    msg;
    HWND   hwndInfo;
    CLIENTCREATESTRUCT clientcreate;
    RECT   clientRect;
    HANDLE haccel;


    UNREFERENCED_PARAMETER( lpCmdLine );
    UNREFERENCED_PARAMETER(  nCmdShow );
    hInst = hInstance;


    /* Check for previous instance.  If none, then register class. */
    if (!hPrevInstance) {
      WNDCLASS  wc;

      wc.style = 0;
      wc.lpfnWndProc = (WNDPROC)MainWndProc;

      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = hInstance;
      wc.hIcon = LoadIcon(hInstance, TEXT("ttfontsIcon"));
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = NULL;
      wc.lpszMenuName =  TEXT("ttfontsMenu");
      wc.lpszClassName = TEXT("ttfonts");

      if (!RegisterClass(&wc)) return (FALSE);

    }  /* class registered o.k. */


    /* Create the main window.  Return false if CreateWindow() fails */
    hwndMain = CreateWindow(
        TEXT("ttfonts"),
        TEXT("TTFonts"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL, NULL, hInst, NULL);

    if (!hwndMain) return (FALSE);

    /* Initialize global strings that are used later */
    LoadString (hInst, IDS_MBERROR,      szMBERROR,      MAX_PATH);
    LoadString (hInst, IDS_INITSTRING,   szInitString,   MAX_PATH);
    LoadString (hInst, IDS_ALLOCFAILED,  szAllocFailed,  MAX_PATH);
    LoadString (hInst, IDS_RESETDISPLAY, szResetDisplay, MAX_PATH);
    LoadString (hInst, IDS_NOCMAPTABLE,  szNoCMAPTable,  MAX_PATH);
    LoadString (hInst, IDS_CBDATATOOBIG, szCBDataTooBig, MAX_PATH);
    LoadString (hInst, IDS_NOTABLE,      szNoTable,      MAX_PATH);
    LoadString (hInst, IDS_FORMATNOT4,   szFormatNot4,   MAX_PATH);
    LoadString (hInst, IDS_FONTDATAERR,  szFontDataErr,  MAX_PATH);
    LoadString (hInst, IDS_ENUMPRINTERR, szEnumPrinterR,  MAX_PATH);


    /* create temporary window to display while initialization completes */
    hwndInfo = CreateWindow(
        TEXT("EDIT"),
        szInitString,
        WS_CHILD | WS_VISIBLE | ES_READONLY | ES_MULTILINE | ES_CENTER,
        0,0,
        GetSystemMetrics (SM_CXFULLSCREEN),
        GetSystemMetrics (SM_CYFULLSCREEN),
        hwndMain, NULL, hInst, NULL);

    ShowWindow(hwndMain, SW_SHOWMAXIMIZED);
    UpdateWindow(hwndInfo);

    /* create the MDI "client" window. Invisible initially. */
    clientcreate.hWindowMenu  = NULL;  /* don't add window names to menu */
    clientcreate.idFirstChild = 1;
    GetClientRect (hwndMain, &clientRect);
    clientRect.top += TOOLBARHEIGHT;
    hwndClient = CreateWindow(
        TEXT("MDICLIENT"),
        NULL,
        WS_CHILD | WS_CLIPCHILDREN | MDIS_ALLCHILDSTYLES,
        0, clientRect.top,
        clientRect.right, clientRect.bottom - clientRect.top,
        hwndMain, NULL, hInst, (LPVOID)&clientcreate);
    if (!hwndClient) return (FALSE);



    /* perform initialization for other windows...allfont is SLOW */
    if (!initTB(hwndMain))         return FALSE;
    if (!initDisplay(hwndClient))     return FALSE;
    if (!initDlg(hwndClient))      return FALSE;
    if (!initAllFont(hwndClient))  return FALSE;


    SendMessage (hwndMain, WM_COMMAND, IDM_ARRANGE,0);

    /* Load the accelerator table that provides clipboard support. */
    haccel = LoadAccelerators (hInst, TEXT("ttfontsAccel"));

    /* get rid of the temporary "please wait..." window. */
    DestroyWindow (hwndInfo);
    ShowWindow(hwndClient, SW_SHOW);

    /* Loop getting messages and dispatching them. */
    while (GetMessage(&msg,NULL, 0,0)) {
      if (!TranslateAccelerator(hwndMain, haccel, &msg))
      if (!IsDialogMessage (hwndDlgTM, &msg))
      if (!IsDialogMessage (hwndDlgOLTM, &msg))
      if (!IsDialogMessage (hwndDlgLF, &msg))
      if (!IsDialogMessage (hwndDlgFD, &msg)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    return (msg.wParam);
}



/**************************************************************************\
*
*  function:  MainWndProc()
*
*  input parameters:  normal window procedure parameters.
*
\**************************************************************************/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static HANDLE     hPenGrid;
static LOGFONT    lf;
static TEXTMETRIC tm;

  switch (message) {


    /**********************************************************************\
    *  WM_COMMAND
    *
    * The WM_COMMAND messages here are passed up from the toolbar.
    *  Take whatever action is necesarry for the various buttons.
    *  (Either showing/hiding enumeration windows, or moving information
    *  in structures between different windows.)
    \**********************************************************************/
    case WM_COMMAND: {

      switch (LOWORD(wParam)) {
        HDC hdcDemo;

        case TBID_ENUM:
          ShowWindow(hwndDisplayFonts, SW_SHOWMAXIMIZED);
        break;

        case TBID_PRINT:
          ShowWindow(hwndPrinterFonts, SW_SHOWMAXIMIZED);
        break;

        /* Send the LOGFONT dialog a message to fill in a LOGFONT structure,
         *  then pass that structure along to the DEMO window.
         */
        case TBID_CREATE:
          SendMessage (hwndDlgLF, WMU_LFTODEMO, 0, (LONG) &lf);
          flyWinWin (hwndMain, hwndDlgLF, hwndDisplay, FWW_STEPS);
          SendMessage (hwndDisplay , WMU_NEWFONT, 0, (LONG) &lf);
        break;


        /* Same exchange as LOGFONT for the TEXTMETRIC structure.
         *  However, for the OUTLINETEXTMETRIC stucture,
         *  send the DEMO window a message asking for an HDC with the
         *  current font selected into it.  Pass that HDC along to the
         *  OUTLINETEXTMETRIC dialog so that it can query the structure,
         *  and display the values.
         */
        case TBID_GETTM:

          SendMessage (hwndDisplay , WMU_DEMOTOTM, 0, (LONG) &tm);
          flyWinWin (hwndMain, hwndDisplay, hwndDlgTM, FWW_STEPS);
          SendMessage (hwndDlgTM, WMU_DEMOTOTM, 0, (LONG) &tm);

          hdcDemo = (HDC) SendMessage (hwndDisplay , WMU_DEMOGETDC, 0, 0);
          flyWinWin (hwndMain, hwndDisplay, hwndDlgOLTM, FWW_STEPS);
          SendMessage (hwndDlgOLTM, WMU_DEMOTOOLTM, 0, (LPARAM) hdcDemo);
          SendMessage (hwndDisplay , WMU_DEMORELEASEDC, 0, (LPARAM) hdcDemo);

        break;


        /* Send message down to hwndDlgFD w/ HDC from hwndDisplay.
         *  hwndDlgFD will parse its params, and call GetFontData().
         */
        case TBID_GETFONTDATA:

          hdcDemo = (HDC) SendMessage (hwndDisplay , WMU_DEMOGETDC, 0, 0);
          flyWinWin (hwndMain, hwndDisplay, hwndDlgFD, FWW_STEPS);
          SendMessage (hwndDlgFD, WMU_GETFONTDATA, 0, (LPARAM) hdcDemo);
          SendMessage (hwndDisplay , WMU_DEMORELEASEDC, 0, (LPARAM) hdcDemo);

        break;


        /* Send message to display window to fill in LOGFONT, then
         *  send that LOGFONT data back to the logfont dialog.
         */
        case IDM_GETOBJECT:
          flyWinWin (hwndMain, hwndDisplay, hwndDlgLF, FWW_STEPS);
          SendMessage (hwndDisplay , WMU_DEMOTOLF, 0, (LPARAM) &lf);
          SendMessage (hwndDlgLF , WMU_DEMOTOLF, 0, (LPARAM) &lf);
        break;

        /******************************************************************\
        *  WM_COMMAND, IDM_*_FONT
        *
        * Send the display window the proper message for it to use one
        *  of the GetStockObject() fonts.  Then send this window a message
        *  to "getobject" so that the logfont will be copied from the
        *  display window to the logfont dialog.
        \******************************************************************/
        case IDM_ANSI_FIXED_FONT    :
          SendMessage (hwndDisplay , WMU_HFONTTODEMO, 0,
                       (LPARAM) GetStockObject(ANSI_FIXED_FONT));
          SendMessage (hwnd, WM_COMMAND, IDM_GETOBJECT, 0);
        break;
        case IDM_ANSI_VAR_FONT      :
          SendMessage (hwndDisplay , WMU_HFONTTODEMO, 0,
                       (LPARAM) GetStockObject(ANSI_VAR_FONT));
          SendMessage (hwnd, WM_COMMAND, IDM_GETOBJECT, 0);
        break;
        case IDM_DEVICE_DEFAULT_FONT:
          SendMessage (hwndDisplay , WMU_HFONTTODEMO, 0,
                       (LPARAM) GetStockObject(DEVICE_DEFAULT_FONT));
          SendMessage (hwnd, WM_COMMAND, IDM_GETOBJECT, 0);
        break;
        case IDM_OEM_FIXED_FONT     :
          SendMessage (hwndDisplay , WMU_HFONTTODEMO, 0,
                       (LPARAM) GetStockObject(OEM_FIXED_FONT));
          SendMessage (hwnd, WM_COMMAND, IDM_GETOBJECT, 0);
        break;
        case IDM_SYSTEM_FIXED_FONT  :
          SendMessage (hwndDisplay , WMU_HFONTTODEMO, 0,
                       (LPARAM) GetStockObject(SYSTEM_FIXED_FONT));
          SendMessage (hwnd, WM_COMMAND, IDM_GETOBJECT, 0);
        break;
        case IDM_SYSTEM_FONT        :
          SendMessage (hwndDisplay , WMU_HFONTTODEMO, 0,
                       (LPARAM) GetStockObject(SYSTEM_FONT));
          SendMessage (hwnd, WM_COMMAND, IDM_GETOBJECT, 0);
        break;



        /******************************************************************\
        *  WM_COMMAND, IDM_CHOOSEFONT
        *
        * Get the LOGFONT from the dialog, initialize the CHOOSEFONT struct,
        *  put up the ChooseFont() dialog, take the resulting LOGFONT and put
        *  it back in the dialog.  Force a createfont message.
        \******************************************************************/
        case IDM_CHOOSEFONT: {
          CHOOSEFONT   chf;

          /* fill a log font ahead of time to init the common dialog */
          SendMessage (hwndDlgLF , WMU_LFTODEMO, 0, (LPARAM) &lf);

          chf.lStructSize = sizeof(CHOOSEFONT);
          chf.hwndOwner = hwnd;
          chf.hDC = NULL;
          chf.lpLogFont = &lf;
          chf.iPointSize = 0;
          chf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
          // chf.Flags |= CF_EFFECTS; // no support for COLOR yet in TTFONTS.
          chf.rgbColors = RGB(0,0,0);
          chf.lCustData = 0;
          chf.lpfnHook = NULL;
          chf.lpTemplateName = NULL;
          chf.hInstance = hInst;
          chf.lpszStyle = NULL;
          chf.nFontType = SIMULATED_FONTTYPE;
          chf.nSizeMin = 0;
          chf.nSizeMax = 0;

          if( ChooseFont( &chf ) != FALSE ) {
            /* flyWinWin from client to dlgLF since we don't have hwnd
             *  for the common dialog, and since it is not a child window.
             */
            flyWinWin (hwndMain, hwndClient, hwndDlgLF, FWW_STEPS);
            SendMessage (hwndDlgLF , WMU_DEMOTOLF, 0, (LPARAM) chf.lpLogFont);
            SendMessage (hwnd, WM_COMMAND, TBID_CREATE, 0);
          }
        } break;




        /* Simply send message to display window, and it does all work. */
        case IDM_PRINT:
          SendMessage (hwndDisplay , WMU_PRINT, 0, 0);
        break;


        /* No printer, disable menu and button. */
        case IDU_NOPRINTER:
          EnableMenuItem (GetMenu(hwnd), TBID_PRINT, MF_GRAYED);
          EnableMenuItem (GetMenu(hwnd), IDM_PRINT , MF_GRAYED);
          SendMessage (hwndTB , WM_COMMAND, IDU_NOPRINTER, 0);
        break;


        case IDM_HELP:
          WinHelp( hwnd, szHelpPathName, HELP_INDEX, (DWORD) NULL );
        break;


        case IDM_ABOUT:
          DialogBox (hInst, TEXT("aboutBox"), hwnd, (DLGPROC) About);
        break;



        /******************************************************************\
        *  WM_COMMAND, IDM_FLYWINWIN
        *
        * Check menu on and off.  Query state in FlyWinWin() function.
        \******************************************************************/
        case IDM_FLYWINWIN:
          if (GetMenuState (GetMenu (hwnd),IDM_FLYWINWIN, MF_BYCOMMAND)
                == MF_CHECKED) {
            CheckMenuItem(GetMenu (hwnd), LOWORD(wParam) , MF_UNCHECKED);
          } else {
            CheckMenuItem(GetMenu (hwnd), LOWORD(wParam) , MF_CHECKED);
          }
        break;


        /******************************************************************\
        *  WM_COMMAND, IDM_MODE*
        *
        * manage mutually exclusive menu.
        *  inform the window that it has a new mode.
        *  invalidate window to force repaint.
        *  Special case MODEALL to check that it is o.k. first.
        \******************************************************************/
        case IDM_MODEALL    :
          if (!SendMessage (hwndDisplay, WMU_NEWMODEALL, 0,0)) {
            return 0;
          }
          CheckMenuItem(GetMenu (hwnd), IDM_MODEHELLO  , MF_UNCHECKED);
          CheckMenuItem(GetMenu (hwnd), IDM_MODETMRANGE, MF_UNCHECKED);
          CheckMenuItem(GetMenu (hwnd), IDM_MODEALL    , MF_CHECKED);
          InvalidateRect (hwndDisplay, NULL, TRUE);
        return 0;

        case IDM_MODEHELLO  :
          CheckMenuItem(GetMenu (hwnd), IDM_MODEHELLO  , MF_CHECKED);
          CheckMenuItem(GetMenu (hwnd), IDM_MODETMRANGE, MF_UNCHECKED);
          CheckMenuItem(GetMenu (hwnd), IDM_MODEALL    , MF_UNCHECKED);
          SendMessage (hwndDisplay, WMU_NEWMODEHELLO, 0,0);
          InvalidateRect (hwndDisplay, NULL, TRUE);
        return 0;

        case IDM_MODETMRANGE:
          CheckMenuItem(GetMenu (hwnd), IDM_MODEHELLO  , MF_UNCHECKED);
          CheckMenuItem(GetMenu (hwnd), IDM_MODETMRANGE, MF_CHECKED);
          CheckMenuItem(GetMenu (hwnd), IDM_MODEALL    , MF_UNCHECKED);
          SendMessage (hwndDisplay, WMU_NEWMODETMRANGE, 0,0);
          InvalidateRect (hwndDisplay, NULL, TRUE);
        return 0;



        /******************************************************************\
        *  WM_COMMAND, IDM_*
        *
        * misc. MDI responsibilities.  hwndClient does real work.
        \******************************************************************/
        case IDM_CASCADE: SendMessage (hwndClient, WM_MDICASCADE, 0,0); break;
        case IDM_TILE:    SendMessage (hwndClient, WM_MDITILE, 0,0); break;
        case IDM_ARRANGE:
          ShowWindow(hwndDisplayFonts, SW_SHOWMINIMIZED);
          ShowWindow(hwndPrinterFonts, SW_SHOWMINIMIZED);
          ShowWindow(hwndDlgOLTM, SW_SHOWMINIMIZED);
          ShowWindow(hwndDlgFD, SW_SHOWMINIMIZED);
          ShowWindow(hwndDlgTM, SW_RESTORE);
          SetWindowPos (hwndDlgTM, HWND_TOP,
              CHILDLEFT(0), CHILDTOP, 0,0, SWP_NOSIZE);
          ShowWindow(hwndDlgLF, SW_RESTORE);
          SetWindowPos (hwndDlgLF, HWND_TOP,
              CHILDLEFT(1), CHILDTOP, 0,0, SWP_NOSIZE);
          ShowWindow(hwndDisplay, SW_RESTORE);
          SetWindowPos (hwndDisplay, HWND_TOP,
              CHILDLEFT(2), CHILDTOP,
              GetSystemMetrics (SM_CXFULLSCREEN)/3 - 10,
              GetSystemMetrics (SM_CYFULLSCREEN)/3, 0);
          SendMessage (hwndClient, WM_MDIICONARRANGE, 0,0);
        break;




      } /* end switch */
    } break;  /* end WM_COMMAND */





    /**********************************************************************\
    *  WM_CREATE
    *
    * Create pens for drawing with later.
    \**********************************************************************/
    case WM_CREATE:
      hPenGrid   = CreatePen (PS_SOLID, 1, GRIDCOLOR);
      CheckMenuItem (GetMenu (hwnd), IDM_FLYWINWIN, MF_BYCOMMAND | MF_CHECKED);
      CheckMenuItem (GetMenu (hwnd), IDM_MODEHELLO, MF_BYCOMMAND | MF_CHECKED);
      gDisplaymode = IDM_MODEHELLO;
    break;


    /**********************************************************************\
    *  WM_DESTROY
    *
    * Complement of the WM_CREATE message.  Delete the pens that were
    *  created and then call postquitmessage.
    \**********************************************************************/
    case WM_DESTROY:
      DeleteObject (hPenGrid);
      WinHelp( hwnd, szHelpPathName, (UINT) HELP_QUIT, (DWORD) NULL );
      PostQuitMessage(0);
    break;



    /**********************************************************************\
    *  WM_SIZE
    *
    * When the frame is sized, then change the size of the MDI client.
    \**********************************************************************/
    case WM_SIZE: {

      RECT r;
      GetClientRect (hwnd, &r);
      r.top += TOOLBARHEIGHT;
      SetWindowPos (hwndClient, HWND_BOTTOM,
                    r.left, r.top, r.right, r.bottom - r.top, 0);
      return TRUE;

    } break;


    default: break;
    } /* end switch */

  return (DefFrameProc(hwnd, hwndClient, message, wParam, lParam));
}



/***************************************************************************\
*    FUNCTION: About
\***************************************************************************/
LRESULT CALLBACK About(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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





/**************************************************************************\
*  function:  flyWinWin
*
* Send rectangles flying on the screen to indicate data flow.
*
*  input parameters:
*   handParent - parent window in which other two exist (grandchildren o.k.)
*   hwndFrom - rectangles originate here.
*   hwndTo   - and travel here.
*   steps    - number of steps to take.  Fewer is faster.
*
\**************************************************************************/
VOID flyWinWin(HWND handParent, HWND hwndFrom, HWND hwndTo, int steps)
{
RECT rectFrom, rectTo;
RECT rectI;
HDC hdc;
int i, iLeft, iTop, iRight, iBottom;

    /* The menu bar contains a checked/unchecked item which stores the
     *  state of the user's preference on whether this "information flow"
     *  should be done or not.  If unchecked, then return before doing
     *  anything.
     */
    if (GetMenuState (GetMenu (hwndMain),IDM_FLYWINWIN, MF_BYCOMMAND)
                != MF_CHECKED) return;


    /* retrieve the window rects in screen coordinates. */
    GetWindowRect (hwndFrom, &rectFrom);
    GetWindowRect (hwndTo, &rectTo);

    /* convert them to be relative to the parent window. */
    ScreenToClient (handParent,(LPPOINT)&rectFrom.left);
    ScreenToClient (handParent,(LPPOINT)&rectFrom.right);
    ScreenToClient (handParent,(LPPOINT)&rectTo.left);
    ScreenToClient (handParent,(LPPOINT)&rectTo.right);

    /* Get an HDC, set the ROP so that painting twice will restore to the
     *  same state.  Then select in the NULL brush so that the Rectangle()
     *  call will not fill in the interior.
     */
    hdc = GetDC (handParent);
    SetROP2(hdc, R2_NOT);
    SelectObject (hdc, GetStockObject (NULL_BRUSH));

    /* Compute the increment to change on each step.  Notice that round
     *  off loss will cause the target window (hwndTo) to be "missed" if
     *  the windows nearly allign on some edge, and there are a large number
     *  of steps.
     */
    iLeft =   (rectTo.left   - rectFrom.left)   /steps;
    iTop =    (rectTo.top    - rectFrom.top)    /steps;
    iRight =  (rectTo.right  - rectFrom.right)  /steps;
    iBottom = (rectTo.bottom - rectFrom.bottom) /steps;

    /* Draw the series of rectangles the first time. */
    rectI = rectFrom;
    for (i= 0; i<steps; i++) {
      rectI.left += iLeft;
      rectI.top += iTop;
      rectI.right += iRight;
      rectI.bottom += iBottom;

      Rectangle (hdc, rectI.left, rectI.top , rectI.right, rectI.bottom);
    }

    /* start from the same place, and draw them again... this time erases. */
    rectI = rectFrom;
    for (i= 0; i< steps; i++) {
      rectI.left += iLeft;
      rectI.top += iTop;
      rectI.right += iRight;
      rectI.bottom += iBottom;

      Rectangle (hdc, rectI.left, rectI.top , rectI.right, rectI.bottom);
    }

    ReleaseDC (handParent,hdc);
}
