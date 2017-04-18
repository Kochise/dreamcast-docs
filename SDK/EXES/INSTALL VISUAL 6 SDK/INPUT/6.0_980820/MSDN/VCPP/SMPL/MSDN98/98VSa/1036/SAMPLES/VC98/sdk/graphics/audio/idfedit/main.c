//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  main.c
//**
//**  DESCRIPTION:
//**     Performs window class registration, creations and message 
//**     polling.
//**
//************************************************************************

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>

#define DECLARE_VARS
#include "idfedit.h"

/*+ ErrorBox ()
 *
 *  bring up a message box with a string from the stringtable
 *
 *-=================================================================*/

#include <stdarg.h>

int WINAPI ErrorBox (UINT wStringID, UINT wType, ...)
{
   char  szFormat[512];
   char  szErr[512];
   int   cbSize;
   va_list va;

   va_start (va, wType);
   cbSize = LoadString (hInst, wStringID, szFormat, NUMELMS(szFormat));
   if (!cbSize)
      wsprintf (szErr, "Error %d", wStringID);
   else
      wvsprintf (szErr, szFormat, va);
   va_end (va);

   return MessageBox (hWndMain, szErr, szApp, wType);
}

/*+ GetWindowPosFromIni
 *
 * retrieve the window position information from IDFEDIT.ini
 *
 *-=================================================================*/

static TCHAR cszProfile[] = TEXT ("MsIdfEd.ini");
static TCHAR cszSection[] = TEXT ("General");
static TCHAR cszWindow[]  = TEXT ("Window");
static TCHAR cszWindowDef[] = TEXT ("");
static TCHAR cszWindowFmt[] = TEXT ("%d,%d,%d,%d");

BOOL WINAPI GetWindowPosFromIni (
   LPRECT lprc)
   {
   TCHAR sz[100];
   RECT  rcScreen;
   RECT  rc;

   GetPrivateProfileString (cszSection, cszWindow, cszWindowDef,
                            sz, NUMELMS (sz), cszProfile);

   if ( ! SystemParametersInfo (SPI_GETWORKAREA, 0, &rcScreen, FALSE))
      {
      rcScreen.top = rcScreen.left = 0;
      rcScreen.right = 640;
      rcScreen.bottom = 480;
      }

   sscanf (sz, cszWindowFmt,
           &lprc->left, &lprc->top,
           &lprc->right, &lprc->bottom);

   if ( ! IntersectRect (&rc, &rcScreen, lprc))
      *lprc = rcScreen;

   return ! IsRectEmpty (lprc);
   }

/*+ SaveWindowPosToIni
 *
 * store the window position information in dragn.ini
 *
 *-=================================================================*/

BOOL WINAPI SaveWindowPosToIni (
   LPRECT lprc)
   {
   TCHAR sz[100];

   wsprintf (sz, cszWindowFmt,
            lprc->left,
            lprc->top,
            lprc->right - lprc->left,
            lprc->bottom - lprc->top);

   WritePrivateProfileString (cszSection, cszWindow, sz, cszProfile);

   return TRUE;
   }

/*+ AboutDlgProc()
 *
 *  callback function for the about dialog
 *
 *-=================================================================*/

BOOL CALLBACK AboutDlgProc (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam)
   {
   BOOL bRet = FALSE;
                         
   switch (wMsgID)
   {                    
      case WM_COMMAND:
      {
         UINT  uID     = GET_WM_COMMAND_ID(wParam, lParam);
         //UINT Notify   = GET_WM_COMMAND_CMD(wParam, lParam);
         //HWND hWndCtl  = GET_WM_COMMAND_HWND(wParam, lParam);

         if (uID == IDOK || uID == IDCANCEL)
         {   
            EndDialog(hWnd, uID);
            bRet = TRUE;
         }
         break;
      }
   }
      
   return bRet;
   }

/*+ GetActiveData
 *
 * helper function, gets data space from the active MDI child
 * window
 *
 *-=================================================================*/

static LPVOID GetActiveData ()
   {
   if (gs.pIDF && gs.pIDF->szFile[0])
      return gs.pIDF;
   return NULL;
   }


/*+
 *
 *-======================================================================*/

STATICFN VOID WINAPI SetStandardCaption (VOID)
   {
   TCHAR sz[MAX_PATH + 20];
   LoadString (hInst, IDS_CAPTION_BAR, sz, NUMELMS (sz));
   lstrcat (sz, TEXT(" - "));
   if (gs.szDefFile[0])
      lstrcat (sz, gs.szDefFile);
   else
      {
      UINT cb = lstrlen(sz);
      LoadString (hInst, IDS_DEF_FILE_NAME, sz + cb, NUMELMS(sz) - cb);
      }
   SetWindowText (hWndMain, sz);
   }

/*+ SaveAndCloseHeader
 *
 *-======================================================================*/

STATICFN BOOL SaveAndCloseHeader (
   HWND hWnd,
   BOOL bSaveAs)
   {
   LPIDFHEAD pIDF = gs.pIDF;
   BOOL      bRet;

   if (!pIDF)
      return TRUE;

   if (!pIDF->szFile[0])
      bSaveAs = TRUE;

   if (pIDF->bReadOnly)
   {
      ErrorBox (IDS_ERR_READONLY, EB_INFO, gs.szDefFile);
      bSaveAs = TRUE;
   }

   if (bSaveAs)
      {  
      if (! PromptForIDFName(hWnd, gs.szDefFile, NULL, TRUE))
         return FALSE;
      }
   else
      lstrcpy (gs.szDefFile, pIDF->szFile);

   if (!(bRet = SaveIDFToFile (pIDF, gs.szDefFile)))
      ErrorBox (IDS_ERR_SAVE, EB_ERROR, gs.szDefFile);

   SetStandardCaption();
   return bRet;
   }

/*+ QuerySaveChanges
 *
 *-======================================================================*/

BOOL QuerySaveChanges (
   HWND hWnd,
   BOOL bSetForeground)
   {
   UINT  idBtn;
   DWORD dwEB = EB_YNC;

   if (!gs.pIDF)
      return TRUE;

   if (bSetForeground)
      dwEB |= MB_SETFOREGROUND;

   idBtn = ErrorBox (IDS_QUERY_SAVE, dwEB, gs.pIDF->szFile);
   if (idBtn == IDYES)
      return SaveAndCloseHeader (hWnd, FALSE);
   else if (idBtn == IDCANCEL)
      return FALSE;
   return TRUE;
   }

/*+ OpenHeader
 *
 *-======================================================================*/

STATICFN LONG WINAPI OpenHeader (
   HWND hWnd,
   BOOL bPrompt)
   {
   TCHAR szFile[MAX_PATH];
   TCHAR szTitle[MAX_PATH];
   LPIDFHEAD pIDF;

   pIDF = gs.pIDF = &gs.idf;
   if (gs.idf.bChanged && ! QuerySaveChanges (hWnd, FALSE))
      return 0;

   FreeIDFFile (gs.pIDF);

   szFile[0] = 0;
   if (bPrompt)
      {
      if ( ! PromptForIDFName (hWnd, szFile, szTitle, FALSE))
         return 0;

      lstrcpy (gs.szDefFile, szFile);
      LoadIDFFromFile (pIDF, szFile);
      }

   if (!pIDF->hWndHead)
      {
      RECT rc;
      GetClientRect (hWnd, &rc);

      pIDF->hWndHead = CreateWindowEx (fdwExStyle | WS_EX_NOPARENTNOTIFY,
                                       cszHdrClass,
                                       "",
                                       WS_CHILD | WS_VISIBLE,
                                       0, 0, rc.right, rc.bottom,
                                       hWnd,
                                       (HMENU)1,
                                       hInst,
                                       pIDF);
      }
   else
      {
      Head_RefreshTree (pIDF->hWndHead);
      }

   SetStandardCaption();

   return (LONG)pIDF->hWndHead;
   }

/*+ MainCommands
 *
 *-=================================================================*/

LONG WINAPI MainCommands (
   HWND   hWnd,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG lRet     = 1;
   WORD wID      = GET_WM_COMMAND_ID (wParam, lParam);
   WORD wNotify  = GET_WM_COMMAND_CMD (wParam, lParam);
   HWND hWndCtl  = GET_WM_COMMAND_HWND (wParam, lParam);

   switch (wID)
      {
      case IDM_ABOUT:
         return DialogBox (hInst,
                           MAKEINTRESOURCE(IDD_ABOUT),
                           hWnd,
                           AboutDlgProc);
         break;

      case IDM_HELP:
         ErrorBox (IDS_ERR_NOHELP, MB_OK);
         break;

      case IDM_FILEOPEN:
         lRet = OpenHeader (hWnd, TRUE);
         break;

      case IDM_FILENEW:
         lRet = OpenHeader (hWnd, FALSE);
         if (gs.pIDF)
         {
            NewIDFInstrum (gs.pIDF, NULL, "<untitled>");
            gs.pIDF->bChanged = FALSE;
            Head_RefreshTree (gs.pIDF->hWndHead);
         }
         break;

      case IDM_FILESAVE:
      case IDM_FILESAVEAS:
         lRet = SaveAndCloseHeader (hWnd, wID == IDM_FILESAVEAS);
         if (lRet)
         {
            // Saving has the side effect of also closing the file
            // so we need to re-open it after the save completes
            //
            LoadIDFFromFile (gs.pIDF, gs.szDefFile);
         }
         Head_RefreshTree (gs.pIDF->hWndHead);
         break;

      case IDM_NEW_INSTRUMENT:
         NewIDFInstrum (gs.pIDF, NULL, "<untitled>");
         Head_RefreshTree (gs.pIDF->hWndHead);
         break;

      case IDM_FILEEXIT:
         PostMessage (hWnd, WM_CLOSE, 0, 0);
         break;

      //case IDM_EDITUNDO:
      //   break;

      case IDM_EDITCUT:
      case IDM_EDITCOPY:
         if (gs.pIDF && gs.pIDF->piSelect)
            {
            CopyInstrumToClip (gs.pIDF);
            if (wID == IDM_EDITCUT)
               DeleteInstrum (gs.pIDF);
            }
         break;

      case IDM_EDITPASTE:
         PasteInstrum (gs.pIDF);
         break;

      case IDM_EDITDELETE:
         if (gs.pIDF && gs.pIDF->piSelect)
            DeleteInstrum (gs.pIDF);
         break;
      }

   return lRet;
   }

/*+ MainWndProc
 *
 *-=================================================================*/

LRESULT CALLBACK MainWndProc (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG  lRet = 0;         // return value from this routine

   switch (wMsgID)
      {
      case WM_COMMAND:
         lRet = MainCommands (hWnd, wParam, lParam);
         break;

      case WM_NOTIFY:
         break;

      case WM_SIZE:
         if (gs.idf.hWndHead)
            SetWindowPos (gs.idf.hWndHead, NULL,
                          0, 0, LOWORD(lParam), HIWORD(lParam),
                          SWP_NOZORDER);
         break;

      case WM_CREATE:
         {
         // send ourselves a command to create a document window.
         //
         PostMessage (hWnd, WM_COMMAND, IDM_FILEOPEN, 0);
         }
         break;

      case WM_INITMENUPOPUP:
         {
         HMENU  hPopup = (HMENU)wParam;
         UINT   uPos   = (UINT) LOWORD (lParam);
         BOOL   fSystemMenu = HIWORD (lParam);
         UINT   uFirstID;

         // if this is for the system menu, go no further.
         //
         if (fSystemMenu)
            break;

         // if this is the 'File' popup, do menu initialization
         //
         uFirstID = GetMenuItemID (hPopup, 0);
         if (uFirstID == IDM_FILENEW)
            {
            EnableMenuItem (hPopup, IDM_FILESAVE, gs.pIDF ? MF_ENABLED : MF_GRAYED);
            EnableMenuItem (hPopup, IDM_FILESAVEAS, gs.pIDF ? MF_ENABLED : MF_GRAYED);
            }
         else if (uFirstID == IDM_EDITCUT)
            {
            BOOL bCanPaste = IsClipboardFormatAvailable(CF_RIFF);
            BOOL bCanCut = (gs.idf.piSelect != NULL);
            // BOOL bCanUndo = FALSE;

            // EnableMenuItem (hPopup, IDM_EDITUNDO, bCanUndo ? MF_ENABLED : MF_GRAYED);
            EnableMenuItem (hPopup, IDM_EDITCUT, bCanCut ? MF_ENABLED : MF_GRAYED);
            EnableMenuItem (hPopup, IDM_EDITDELETE, bCanCut ? MF_ENABLED : MF_GRAYED);
            EnableMenuItem (hPopup, IDM_EDITCOPY, bCanCut ? MF_ENABLED : MF_GRAYED);
            EnableMenuItem (hPopup, IDM_EDITPASTE, bCanPaste ? MF_ENABLED : MF_GRAYED);
            }
         break;
         }

      case WM_CLOSE:
      case WM_QUERYENDSESSION:
         {
         WINDOWPLACEMENT wpl;

         if (gs.idf.bChanged &&
             !QuerySaveChanges (hWnd, wMsgID == WM_QUERYENDSESSION))
            break;

         //
         // before we shutdown, save the current size and position
         // of the window to the INI file.
         //
         ZeroMemory (&wpl, sizeof(wpl));
         wpl.length = sizeof(wpl);
         GetWindowPlacement (hWnd, &wpl);

         SaveWindowPosToIni (&wpl.rcNormalPosition);

         lRet = DefWindowProc (hWnd, wMsgID, wParam, lParam);
         break;
         }

      case WM_DESTROY:
         // close the app (by causing an exit from the message loop)
         PostQuitMessage (0);
         break;

      default:
         lRet = DefWindowProc (hWnd, wMsgID, wParam, lParam);
      }
   return lRet;
   }

/*+ RegClasses ()
 *
 *  Registers all window classes that will be
 *   used in this application.
 *
 *  Called from WinMain
 *
 *  returns: the return value of the call to RegisterClass ()
 *          TRUE   if successful registration
 *          FALSE  if registration failed
 *
 *-=================================================================*/

static CONST TCHAR cszMainClass[] = "Main";

extern LRESULT WINAPI ViewWndProc (HWND, UINT, WPARAM, LPARAM);

BOOL WINAPI RegClasses (
   HANDLE hInstance)
   {
   WNDCLASS  wc;
   TCHAR     ach[2];

   LoadString(hInstance, IDS_IS_RTL, ach, sizeof(ach)/sizeof(ach[0]));
   fdwExStyle = (ach[0] == '1') ? WS_EX_LEFTSCROLLBAR | WS_EX_RIGHT | WS_EX_RTLREADING : 0;

   //InitCommonControls();

   // register the main window class
   //
   ZeroMemory (&wc, sizeof(wc));
   wc.lpszClassName = cszMainClass;
   wc.lpfnWndProc   = MainWndProc;
   wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
   wc.hIcon         = LoadIcon (hInst, MAKEINTRESOURCE (IDR_MAIN));
   wc.lpszMenuName  = MAKEINTRESOURCE (IDR_MAIN);
   wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
   wc.hInstance     = hInstance;
   if (!RegisterClass (&wc))
       return FALSE;

   // register the idf instrument window class
   //
   ZeroMemory (&wc, sizeof(wc));
   wc.lpszClassName = cszHdrClass;
   wc.lpfnWndProc   = HeadWndProc;
   wc.style         = CS_VREDRAW | CS_HREDRAW  | CS_DBLCLKS;
   wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
   wc.hIcon         = LoadIcon (hInst, MAKEINTRESOURCE (IDR_MAIN));
   wc.lpszMenuName  = NULL;
   wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE+1);
   wc.hInstance     = hInstance;
   if (!RegisterClass (&wc))
       return FALSE;

   ZeroMemory (&wc, sizeof(wc));
   wc.lpszClassName = cszInstrumClass;
   wc.lpfnWndProc   = ViewWndProc;
   wc.style         = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
   wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
   wc.hIcon         = LoadIcon (hInst, MAKEINTRESOURCE (IDR_INSTRUM));
   wc.lpszMenuName  = NULL;
   wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
   wc.hInstance     = hInstance;
   if (!RegisterClass (&wc))
       return FALSE;

   return TRUE;
   }

/*+ CreateMainWindow ()
 *
 *  Creates the main window for the application.
 *
 *  Called from WinMain
 *
 *  returns:  a valid window handle if CreateWindow succeeds
 *            or NULL if CreateWindow Fails
 *
 *-=================================================================*/

HWND WINAPI CreateMainWindow (
   int nCmdShow)
   {
   HWND   hWnd;
   TCHAR  szTitle[100];
   RECT   rc;

   LoadString (hInst, IDS_CAPTION_BAR, szTitle, NUMELMS (szTitle));

   // get x, y, cx, cy positions from ini files
   //
   if ( ! GetWindowPosFromIni (&rc))
      rc.left = rc.right = CW_USEDEFAULT;

   hWnd = CreateWindowEx (fdwExStyle,        // RTL style
                       cszMainClass,         // class
                       szTitle,              // title
                       WS_OVERLAPPEDWINDOW,
                       rc.left,
                       rc.top,               // position: x,y
                       rc.right,
                       rc.bottom,            // size: width, height
                       NULL,                 // parent
                       NULL,                 // menu or child id
                       hInst,                // instance
                       NULL);                // params to pass on to WM_CREATE

   if (hWnd)
      ShowWindow (hWnd, nCmdShow);

   return hWnd;
   }

/*+ WinMain ()
 *
 *-=================================================================*/

int WINAPI WinMain (
   HINSTANCE hInstance,
   HINSTANCE hPrevInstance,
   LPSTR lpszCmdLine,
   int nCmdShow)
   {
   MSG     msg;      // temp for current message
   HACCEL  hAccel;

   // save off instance handle in a global. THIS MUST BE DONE FIRST!
   // also load the application name into a global string
   //
   hInst = hInstance;
   LoadString (hInst, IDS_APPNAME, szApp, NUMELMS (szApp));

   // if this is not the first instance, register the class
   // if class registration fails, put up a message box and quit
   if (!RegClasses (hInstance))
       return ErrorBox (IDS_ERR_REGCLASSES, EB_FATAL);

   hAccel = LoadAccelerators (hInst, MAKEINTRESOURCE(IDR_MAIN));

   // create the main window and save it's window handle in a global
   // if the creation fails, put up a message box and quit.
   //
   hWndMain = CreateMainWindow (nCmdShow);
   if ( !hWndMain)
      return ErrorBox (IDS_ERR_CREATEMAIN, EB_FATAL);

   // loop forever getting messages and dispatching them
   // to the appropriate window.
   //
   while (GetMessage (&msg, NULL, 0,0))
   {
      if (TranslateAccelerator (hWndMain, hAccel, &msg))
         continue;

      TranslateMessage (&msg);
      DispatchMessage (&msg);
   }

   // return the wParam of the last message (the QUIT message)
   //
   return msg.wParam;
   }
