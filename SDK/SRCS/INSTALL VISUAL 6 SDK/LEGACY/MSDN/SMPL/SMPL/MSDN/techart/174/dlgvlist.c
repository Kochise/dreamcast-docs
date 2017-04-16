#include "windows.h"
#include "windowsx.h"
#include "custcntl.h"
#include "string.h"

#include "vlistint.h"
#include "dlgvlist.h"


typedef struct StylesTable {
   DWORD StyleBit;
   char  szText[32];
   int   nTextLength;
   WORD  wCtlId;
} STYLETABLE;

STYLETABLE   MyStyles[] = {
                {VLBS_NOTIFY,            "VLBS_NOTIFY",            11, DLG_VLBS_NOTIFY},
                {VLBS_USETABSTOPS,       "VLBS_USETABSTOPS",       16, DLG_VLBS_USETABSTOPS},
                {VLBS_NOREDRAW,          "VLBS_NOREDRAW",          13, DLG_VLBS_NOREDRAW},
                {VLBS_DISABLENOSCROLL,   "VLBS_DISABLENOSCROLL",   19, DLG_VLBS_DISABLENOSCROLL},
                {VLBS_NOINTEGRALHEIGHT,  "VLBS_NOINTEGRALHEIGHT",  20, DLG_VLBS_NOINTEGRALHEIGHT},
                {VLBS_WANTKEYBOARDINPUT, "VLBS_WANTKEYBOARDINPUT", 21, DLG_VLBS_WANTKEYBOARDINPUT},
                {VLBS_OWNERDRAWFIXED,    "VLBS_OWNERDRAWFIXED",    20, DLG_VLBS_OWNERDRAWFIXED},
                {VLBS_HASSTRINGS,        "VLBS_HASSTRINGS",        14, DLG_VLBS_HASSTRINGS},
                {0,0,"",0}
             };

STYLETABLE   WinStyles[] = {
                {WS_BORDER,   "", 0, DLG_WS_BORDER},
                {WS_VSCROLL,  "", 0, DLG_WS_VSCROLL},
                {WS_HSCROLL,  "", 0, DLG_WS_HSCROLL},
                {WS_VISIBLE,  "", 0, DLG_WS_VISIBLE},
                {WS_DISABLED, "", 0, DLG_WS_DISABLED},
                {WS_GROUP,    "", 0, DLG_WS_GROUP},
                {WS_TABSTOP,  "", 0, DLG_WS_TABSTOP},
                {0,0,"",0}
             };


static VOID NEAR CenterWindow(HWND hwnd);
static VOID NEAR ReadStyles(HWND hwnd, STYLETABLE *pStyle, LPCTLSTYLE lpCtlStyle);
static VOID NEAR WriteStyles(HWND hwnd, STYLETABLE *pStyle, LPCTLSTYLE lpCtlStyle);

BOOL _export _loadds FAR PASCAL StylesDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LONG lParam);

//
//  Routines to integrate VLIST with the Dialog Editor
//
//


//
// Information about the control
//

HANDLE _export _loadds FAR PASCAL  VListInfo ()
{
   HANDLE    hCtlInfo;
   LPCTLINFO lpCtlInfo;

   // allocate space for information structure

   hCtlInfo = GlobalAlloc(GHND, (DWORD)sizeof(CTLINFO));
   if (hCtlInfo) {
      lpCtlInfo = (LPCTLINFO)GlobalLock(hCtlInfo);
      if (lpCtlInfo) {
         lpCtlInfo->wVersion = 100;

         _fstrcpy(lpCtlInfo->szClass, "VList");
         _fstrcpy(lpCtlInfo->szTitle, "Virtual List Box");

         lpCtlInfo->wCtlTypes = 1;
         lpCtlInfo->Type[0].wWidth =  50;
         lpCtlInfo->Type[0].wHeight = 50;
         lpCtlInfo->Type[0].dwStyle = WS_CHILD | WS_BORDER | VLBS_NOINTEGRALHEIGHT;
         _fstrcpy(lpCtlInfo->Type[0].szDescr, "Virtual List Box");

         GlobalUnlock(hCtlInfo);
      }
      else
      {
         GlobalFree(hCtlInfo);
         hCtlInfo = NULL;
      }
   }

   return (hCtlInfo);
}


//
// Translate the style bits to strings for the dialog (.dlg) file
//
WORD _export _loadds FAR PASCAL VlistFlags (WORD wFlags, LPSTR lpszString, WORD wMaxString)
{
   WORD wLength;
   STYLETABLE *pStyle;

   lpszString[0] = 0;
   wLength = 0;

   for ( pStyle = &MyStyles[0]; pStyle->StyleBit != 0L; pStyle++ ) {
      if ( wFlags & pStyle->StyleBit && wMaxString > wLength+pStyle->nTextLength+3 ) {
         if ( wLength ) {
            _fstrcat(lpszString," | ");
            wLength += 3;
         }
         _fstrcat(lpszString, pStyle->szText);
         wLength += pStyle->nTextLength;
      }
   }

   return wLength;
}


//
// A Dialog box to set the control's style bits.
//
//

//
// A function the dialog editor can call which will envoke the dialog box
//
//
BOOL _export _loadds FAR PASCAL VlistStyle(HWND hWnd, HANDLE hCtlStyle,
                           LPFNSTRTOID lpfnStrToId, LPFNIDTOSTR lpfnIdToStr)
{
   int        iRet;
   HWND       hwndLook;

   // HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK
   //
   // Disable the Dialog editor's owned windows so Custom Controls
   // act like built in controls.
   //
   // HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK
   //
   // Get the first top level window
   //
   hwndLook = GetWindow(GetDesktopWindow(), GW_CHILD);
   while ( hwndLook ) {
      if ( GetParent(hwndLook) == hWnd )
         EnableWindow(hwndLook, FALSE);
      //
      // Get the next top level window
      //
      hwndLook = GetWindow(hwndLook, GW_HWNDNEXT);
   }

   iRet=DialogBoxParam(hInstance, MAKEINTRESOURCE(100), hWnd, StylesDlgProc,
                       MAKELPARAM(hCtlStyle,0));

   // HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK
   //
   // Enable the Dialog editor's owned windows
   //
   // HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK HACK
   //
   hwndLook = GetWindow(GetDesktopWindow(), GW_CHILD);
   while ( hwndLook ) {
      if ( GetParent(hwndLook) == hWnd )
         EnableWindow(hwndLook, TRUE);
      hwndLook = GetWindow(hwndLook, GW_HWNDNEXT);
   }

   return (iRet);
}

//
// The dialog proc for the dialog box
//
//
BOOL _export _loadds FAR PASCAL StylesDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LONG lParam)
{
    HANDLE hCtlStyle;
    LPCTLSTYLE lpCtlStyle;

    switch (msg) {
        case WM_INITDIALOG:
            //
            // Put Handle in Window Property
            //
            hCtlStyle = LOWORD(lParam);
            SetProp(hwnd, MAKEINTRESOURCE(1), hCtlStyle);

            lpCtlStyle = (LPCTLSTYLE )GlobalLock(hCtlStyle);

            //
            // Interpret current styles
            //

            //
            // control specific styles
            //
            ReadStyles(hwnd, MyStyles, lpCtlStyle);

            //
            // Windows styles
            //
            ReadStyles(hwnd, WinStyles, lpCtlStyle);

            //
            // Do special case items
            //
            // i.e. can't have VLBS_HASSTRINGS without VLBS_OWNERDRAWFIXED
            //
            if ( lpCtlStyle->dwStyle & VLBS_OWNERDRAWFIXED ) {
               Button_Enable(GetDlgItem(hwnd,DLG_VLBS_HASSTRINGS), TRUE);
            }
            else {
               Button_SetCheck(GetDlgItem(hwnd,DLG_VLBS_HASSTRINGS), FALSE);
               Button_Enable(GetDlgItem(hwnd,DLG_VLBS_HASSTRINGS), FALSE);
            }

            GlobalUnlock(hCtlStyle);

            CenterWindow(hwnd);

            return TRUE;

        case WM_COMMAND:
            switch (wParam) {
                case DLG_WS_VSCROLL:
                     Button_SetCheck(GetDlgItem(hwnd,DLG_WS_HSCROLL), Button_GetCheck(GetDlgItem(hwnd,DLG_WS_VSCROLL)));
                   break;

                case DLG_WS_HSCROLL:
                     Button_SetCheck(GetDlgItem(hwnd,DLG_WS_VSCROLL), Button_GetCheck(GetDlgItem(hwnd,DLG_WS_HSCROLL)));
                   break;

                case DLG_VLBS_OWNERDRAWFIXED:
                   if (Button_GetCheck(GetDlgItem(hwnd,DLG_VLBS_OWNERDRAWFIXED))) {
                      Button_Enable(GetDlgItem(hwnd,DLG_VLBS_HASSTRINGS), TRUE);
                   }
                   else {
                      Button_SetCheck(GetDlgItem(hwnd,DLG_VLBS_HASSTRINGS), FALSE);
                      Button_Enable(GetDlgItem(hwnd,DLG_VLBS_HASSTRINGS), FALSE);
                   }

                   break;

                case IDOK:
                    //
                    // Get the style structure handle
                    //
                    hCtlStyle = GetProp(hwnd, MAKEINTRESOURCE(1));
                    lpCtlStyle = (LPCTLSTYLE )GlobalLock(hCtlStyle);

                    //
                    // Interpret new styles
                    //

                    //
                    // control specific styles
                    //
                    WriteStyles(hwnd, MyStyles, lpCtlStyle);

                    //
                    // Windows  styles
                    //
                    WriteStyles(hwnd, WinStyles, lpCtlStyle);

                    GlobalUnlock(hCtlStyle);

                    RemoveProp(hwnd, MAKEINTRESOURCE(1));
                    EndDialog(hwnd, IDOK);
                    return TRUE;

                case IDCANCEL:
                    RemoveProp(hwnd, MAKEINTRESOURCE(1));
                    EndDialog(hwnd, IDCANCEL);
                    return FALSE;

            }

            return FALSE;

        default:
            return FALSE;
    }
}

//
// Read the style bit, if bit is set, set control on, otherwise set it off
//
static VOID NEAR ReadStyles(HWND hwnd, STYLETABLE *pStyle, LPCTLSTYLE lpCtlStyle)
{
   for ( ; pStyle->StyleBit != 0L; pStyle++ ) {
      if ( lpCtlStyle->dwStyle & pStyle->StyleBit )
          Button_SetCheck(GetDlgItem(hwnd,pStyle->wCtlId), TRUE);
      else
          Button_SetCheck(GetDlgItem(hwnd,pStyle->wCtlId), FALSE);
   }
}

//
// Read the control, if control on, set bit, otherwise clear bit
//
static VOID NEAR WriteStyles(HWND hwnd, STYLETABLE *pStyle, LPCTLSTYLE lpCtlStyle)
{
   for ( ; pStyle->StyleBit != 0L; pStyle++ ) {
       if ( Button_GetCheck(GetDlgItem(hwnd,pStyle->wCtlId)))
           lpCtlStyle->dwStyle |= pStyle->StyleBit;
       else
           lpCtlStyle->dwStyle &= ~pStyle->StyleBit;
   }
}

static VOID NEAR CenterWindow(HWND hwnd)
{
    RECT rc;
    RECT rcOwner;
    RECT rcCenter;
    HWND hwndOwner;
    int cxScreen;
    int cyScreen;
    int delta;

    GetWindowRect(hwnd, &rc);

    if (!(hwndOwner = GetWindow(hwnd, GW_OWNER)))
        hwndOwner = GetDesktopWindow();

    GetWindowRect(hwndOwner, &rcOwner);

    rcCenter.left = rcOwner.left +
            (((rcOwner.right - rcOwner.left) -
            (rc.right - rc.left))
            / 2);

    rcCenter.top = rcOwner.top +
            (((rcOwner.bottom - rcOwner.top) -
            (rc.bottom - rc.top))
            / 2);

    rcCenter.right = rcCenter.left + (rc.right - rc.left);
    rcCenter.bottom = rcCenter.top + (rc.bottom - rc.top);

    cxScreen = GetSystemMetrics(SM_CXSCREEN);

    if (rcCenter.right > cxScreen) {
        delta = rcCenter.right - rcCenter.left;
        rcCenter.right = cxScreen;
        rcCenter.left = rcCenter.right - delta;
    }

    if (rcCenter.left < 0) {
        delta = rcCenter.right - rcCenter.left;
        rcCenter.left = 0;
        rcCenter.right = rcCenter.left + delta;
    }

    cyScreen = GetSystemMetrics(SM_CYSCREEN);

    if (rcCenter.bottom > cyScreen) {
        delta = rcCenter.bottom - rcCenter.top;
        rcCenter.bottom = cyScreen;
        rcCenter.top = rcCenter.bottom - delta;
    }

    if (rcCenter.top < 0) {
        delta = rcCenter.bottom - rcCenter.top;
        rcCenter.top = 0;
        rcCenter.bottom = rcCenter.top + delta;
    }

    SetWindowPos(hwnd, NULL, rcCenter.left, rcCenter.top, 0, 0,
            SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
}
