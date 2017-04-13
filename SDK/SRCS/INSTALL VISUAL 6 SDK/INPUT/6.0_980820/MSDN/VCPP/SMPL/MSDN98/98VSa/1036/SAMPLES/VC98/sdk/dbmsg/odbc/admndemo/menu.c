//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   MENU.C
//|      This module will take care of enabling and disabling menus.
//*---------------------------------------------------------------------------------
#include <windows.h>
#include "menu.h"
#include "standard.h"
#include "child.h"
#include "admndemo.h"




//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
extern lpCHILDINFO      lpActiveConn;
extern lpRESULTSINFO    lpActiveResults;
extern HWND             hwndCurMDIChild;


extern dCSEG(char)   szChildClass[];



UWORD uMenuIDs[] = {
   SQL_API_SQLTABLES,
   SQL_API_SQLCOLUMNS,
   SQL_API_SQLSTATISTICS,
   SQL_API_SQLPRIMARYKEYS,
   SQL_API_SQLFOREIGNKEYS,
   SQL_API_SQLTABLEPRIVILEGES,
   SQL_API_SQLCOLUMNPRIVILEGES,
   SQL_API_SQLSPECIALCOLUMNS,
   SQL_API_SQLPROCEDURES,
   SQL_API_SQLPROCEDURECOLUMNS,
   SQL_API_SQLTRANSACT,
   };




//*---------------------------------------------------------------------------------
//| ResetMenu:
//|   When user drops the menu, determine what items are to be enabled/disabled.
//| Parms:
//|   hMenu                Handle to the menu being displayed
//|   iMenu                Index to the menu
//|   iCalledFrom          Where were we called from?
//|                           1     From main WndProc
//|                           2     From connection window
//|                           3     Test output window
//| Returns:
//|   Nothing.
//*---------------------------------------------------------------------------------
VOID INTFUN ResetMenu(HMENU hMenu, int iMenu)
{
   switch(GETMENUNUM(iMenu)) {
     case IDM_FILE_MENU:
      {
         UINT        uMnuFlag;
         HWND        hwnd = GetEditWindow(lpActiveConn);

         uMnuFlag = MNU_HAVE_CONNECTS;

         // Is there an active connection
         EnableMenuItem(hMenu, IDM_DISCONNECT, uMnuFlag);
         EnableMenuItem(hMenu, IDM_EXECUTE_FILE, uMnuFlag);
         EnableMenuItem(hMenu, IDM_OPEN,
                        (uMnuFlag == MF_ENABLED && !lpActiveResults) ?
                        MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_CLOSE,
                        (lpActiveConn && lpActiveConn->hFile && !lpActiveResults) ?
                        MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_SAVE,
                        (lpActiveConn && lpActiveConn->hFile && !lpActiveResults) ?
                        MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_SAVEAS,
                        (lpActiveConn &&
                         SendMessage(lpActiveConn->hwndIn, WM_GETTEXTLENGTH, 0, 0L) &&
                         !lpActiveResults) ?
                        MF_ENABLED : MF_GRAYED);
      }
      break;

     case IDM_EDIT_MENU:
      {
         HWND     hwnd = GetEditWindow(lpActiveConn);
         DWORD    sel=0;

         if(hwnd)
            sel = SendMessage(hwnd, EM_GETSEL, 0, 0L);

         EnableMenuItem(hMenu, IDM_UNDO,
                        (lpActiveConn && hwnd &&
                         SendMessage(hwnd, EM_CANUNDO, 0, 0L)) ? MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_CUT,
                        (lpActiveConn && hwnd &&
                         HIWORD(sel) != LOWORD(sel)) ? MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_COPY,
                        (lpActiveConn && hwnd &&
                         HIWORD(sel) != LOWORD(sel)) ? MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_PASTE,
                        (lpActiveConn && hwnd &&
                         IsClipboardFormatAvailable(CF_TEXT)) ? MF_ENABLED : MF_GRAYED);
         EnableMenuItem(hMenu, IDM_SELECT_ALL,
                        (lpActiveConn && hwnd &&
                         SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0L)) ? MF_ENABLED : MF_GRAYED);
      }
      break;

     case IDM_EXECUTE_MENU:
      {
         HWND     hwnd = GetEditWindow(lpActiveConn);
         DWORD    sel=0;
         UINT     utmp;

         if(hwnd)
            sel = SendMessage(hwnd, EM_GETSEL, 0, 0L);

         EnableMenuItem(hMenu, IDM_EXECUTE_NOW,
                        (lpActiveConn && hwnd &&
                         hwnd == lpActiveConn->hwndIn &&
                         SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0L)) ? MF_ENABLED : MF_GRAYED);


         // Need to support commit and rollback to call them
         utmp = (lpActiveConn && BitGet(lpActiveConn->fFunctions, MENU_SQLTRANSACT)) ?
            MF_ENABLED : MF_GRAYED;
         EnableMenuItem(hMenu, IDM_COMMIT, utmp);
         EnableMenuItem(hMenu, IDM_ROLLBACK, utmp);
      }
      break;

     case IDM_PIPE_MENU:
      {
         // Just look for active connection
         UINT utmp = MNU_HAVE_CONNECTS;

         // Just look for active connections and results
         EnableMenuItem(hMenu, IDM_PIPE_EDIT, utmp);
         EnableMenuItem(hMenu, IDM_PIPE_DO,
                        (lpActiveResults) ? MF_ENABLED : MF_GRAYED);
      }
      break;

     case IDM_INFO_MENU:
      {
         // Just look for active connection
         UINT utmp = MNU_HAVE_CONNECTS;

         EnableMenuItem(hMenu, IDM_DATA_SOURCES, utmp);
         EnableMenuItem(hMenu, IDM_DATA_TYPES, utmp);
         EnableMenuItem(hMenu, IDM_FUNCTIONS, utmp);
         EnableMenuItem(hMenu, IDM_ODBC_INFO, utmp);
      }
      break;

     case IDM_LIST_MENU:
      {
         int   idex;

         for(idex=0;  idex<NUM_MENU_FLAGS;  idex++)
            EnableMenuItem(hMenu, (IDM_TABLES + idex),
                           (lpActiveConn &&
                            BitGet(lpActiveConn->fFunctions, idex)) ?
                           MF_ENABLED : MF_GRAYED);
      }
      break;

     case IDM_WINDOW_MENU:
      {
         // Just look for active connection
         UINT utmp = MNU_HAVE_CONNECTS;

         EnableMenuItem(hMenu, IDM_CASCADE, utmp);
         EnableMenuItem(hMenu, IDM_TILE, utmp);
         EnableMenuItem(hMenu, IDM_ARRANGE, utmp);
         EnableMenuItem(hMenu, IDM_CLOSEALL, utmp);
      }
      break;
   }
}
