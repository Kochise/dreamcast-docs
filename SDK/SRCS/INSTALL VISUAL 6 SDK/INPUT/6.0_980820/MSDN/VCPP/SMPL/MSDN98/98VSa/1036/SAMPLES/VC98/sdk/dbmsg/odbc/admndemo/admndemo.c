//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   ADMNDEMO.C
//|      This module contains the main interface modules for SATOOL, including
//|         the MDI client support
//*---------------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include "admndemo.h"
#include "sql.h"
#include "sqlext.h"
#include "ini.h"
#include "dialogs.h"
#include "odbcinst.h"
#include "errcheck.h"
#include "strings.h"
VSZFile;



//*---------------------------------------------------------------------------------
//|   Defines
//*---------------------------------------------------------------------------------
#define HLP_ADMNDEMO 50

typedef struct tagCMDLINE {
   BOOL        fOptions;                     // TRUE if there are options
   BOOL        fExit;                        // TRUE if we should exit when done
   char        szDriverConnect[100];         // String for SQLDriverConnect
   char        szExecuteFile[255];           // File to execute
   BOOL        fTrace;                       // TRUE to trace
   char        szTraceFile[255];             // File to log ODBC calls
   char        szTerm[10];                   // Stmt terminator for file
   int         cbStmt;                       // Maximum statement length
   } CMDLINE;


//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
HWND              hwndFrame, hwndClient, hwndOutput;
HINSTANCE         hInst;
HENV              henv=NULL;
HMENU             hMenu=NULL, hSubMenu=NULL;
HICON             hIcon=NULL, hResultsIcon=NULL, hConnectIcon=NULL;
HFONT             hSmallEditFont;
RETCODE           retcode;
int               iHelpCnt=0;                // Tracks the
CHILDINFO FAR *   CreateCI=NULL;
char              OutStr[MAXBUFF];
char              szDirName[_MAX_PATH];
char              szDftFileFilter[MAXBUFF];
CMDLINE           cl;


// Following is an array of connections and a global to track the current
lpCHILDINFO       ConnectStructs[MAXCONNECTS];
lpCHILDINFO       lpActiveConn=NULL;
HWND              hwndCurMDIChild=NULL;

extern UWORD            uMenuIDs[NUM_MENU_FLAGS];
extern lpRESULTSINFO    lpActiveResults;


dCSEG(char) szFrameClass[]                   = "SAMDI:Frame";
dCSEG(char) szChildClass[]                   = "SACLASS:1";
dCSEG(char) szResultsClass[]                 = "SACLASS:2";
dCSEG(char) szWindowTitle[]                  = "ODBC Admin Demo";
dCSEG(char) szHELPFILE[]                     = "..\\doc\\ODBCSMPL.HLP";

dCSEG(char) szOPENFILE[]                     = "Open File";
dCSEG(char) szSAVEFILE[]                     = "Save File";
dCSEG(char) szUID[]                          =  "UID=";
dCSEG(char) szDSN[]                          =  "DSN=";
dCSEG(char) szNewLine[]                      =  "\r\n";
dCSEG(char) szComma[]                        =  ", ";

dCSEG(char) szUserAt[]                       =  "%s@%s";
dCSEG(char) szUserAtFile[]                   =  "%s@%s   File: %s";



//*---------------------------------------------------------------------------------
//|   Local functions
//*---------------------------------------------------------------------------------
BOOL WINAPI Init(HANDLE hInstance,   HANDLE hPrevInstance,
          LPSTR  lpszCmdLine, int    CmdShow);
BOOL WINAPI SetUp(LPSTR szCmdLine, CMDLINE FAR * cl);
void WINAPI CleanUp(void);
long EXTFUN WndProc(HWND hwnd, unsigned msg, WPARAM wParam, LPARAM lParam);
long EXTFUN PASCAL ChildWndProc(HWND hwnd, unsigned msg, WPARAM wParam, LPARAM lParam);
BOOL EXTFUN PASCAL AboutWndProc(HWND hDlg, unsigned msg, WPARAM wParam, LPARAM lParam);

BOOL WINAPI ParseCommandLine(LPSTR szCmdLine, CMDLINE FAR * cl);
BOOL WINAPI ParseOptionsValues(LPSTR instr, LPSTR szTerm, int cbTerm, int FAR * lpMax);
VOID WINAPI DoConnect(HWND hwnd, DWORD dwData);
BOOL WINAPI Connect(CHILDINFO FAR * ci, HWND hwnd, LPSTR szAutoConnect);
VOID WINAPI DoDisconnect(lpCHILDINFO lpci);
BOOL WINAPI Disconnect(CHILDINFO FAR * ci);
void WINAPI DisplayAbout(HWND hwnd, HINSTANCE hInst);
int  WINAPI DoMain(HANDLE hInstance);
HWND INTFUN GetEditWindow(CHILDINFO FAR * ci);


// File functions
VOID WINAPI DoFileOpen(lpCHILDINFO lpci);
VOID WINAPI DoFileSave(lpCHILDINFO lpci);
VOID WINAPI DoFileSaveAs(lpCHILDINFO lpci);




//*------------------------------------------------------------------------
//| WinMain:
//|     Parameters:
//|         hInstance     - Handle to current Data Segment
//|         hPrevInstance - Handle to previous Data Segment (NULL if none)
//|         lpszCmdLine   - Long pointer to command line info
//|         nCmdShow      - Integer value specifying how to start app.,
//|                            (Iconic [7] or Normal [1,5])
//*------------------------------------------------------------------------
int PASCAL WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR  lpszCmdLine,
                    int    nCmdShow)
{
   int         nReturn;

   if (Init(hInstance, hPrevInstance,lpszCmdLine,nCmdShow)) {
      if(!SetUp(lpszCmdLine, &cl))        // Quit on errors
         return 0;
      nReturn = DoMain(hInstance);
      CleanUp();
   }
   return nReturn;
}


//*---------------------------------------------------------------------------------
//| Init:
//|   This function will take care of initilization for the application.
//| Parms:
//|   in       hInstance            Data segment for this instance
//|   in       hPrevInstance        Data segment for previous instance
//|   in       lpszCmdLine          Command line parameters
//|   in       nCmdShow             Desired display method
//| Returns:
//|   TRUE     if function was successful
//|   FALSE    if there was an error
//*---------------------------------------------------------------------------------
BOOL WINAPI Init(HANDLE hInstance,   HANDLE hPrevInstance,
          LPSTR  lpszCmdLine, int    nCmdShow)
{
   WNDCLASS wc;


   // Make sure the .ini file is there before creating anything
   ResolveIniFile();

   hInst = hInstance;

   if(!hPrevInstance) {
      // Register the Frame Window first
      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = (WNDPROC)WndProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = hInstance;
      hIcon = wc.hIcon = LoadIcon(hInstance, "BASEICON");
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
      wc.lpszMenuName = NULL;
      wc.lpszClassName = szFrameClass;
      if(!RegisterClass(&wc)) {
         PostError((LPSTR)szRegisterClassFailed);
         return FALSE;
      }

      // Register the child window class
      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = (WNDPROC)ChildWndProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = sizeof(lpCHILDINFO FAR *);
      wc.hInstance = hInstance;
      hConnectIcon = wc.hIcon = LoadIcon(hInstance, "CONNECTICON");
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wc.lpszMenuName = NULL;
      wc.lpszClassName = szChildClass;
      if(!RegisterClass(&wc)) {
         PostError((LPSTR)szRegisterClassFailed);
         return FALSE;
      }

      // Register the results output window class
      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = (WNDPROC)ResultsWndProc;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = sizeof(lpRESULTSINFO);
      wc.hInstance = hInstance;
      hResultsIcon = wc.hIcon = LoadIcon(hInstance, "RSLTICON");
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wc.lpszMenuName = NULL;
      wc.lpszClassName = szResultsClass;
      if(!RegisterClass(&wc)) {
         PostError((LPSTR)szRegisterClassFailed);
         return FALSE;
      }
   }

   hMenu = LoadMenu(hInstance, "BASEMENU");
   hSubMenu = GetSubMenu(hMenu, IDM_WINDOW_POS);

   hwndFrame = CreateWindow(szFrameClass,
                            szWindowTitle,
                            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            NULL,
                            hMenu,
                            hInstance,
                            NULL);

   hwndClient = GetWindow(hwndFrame, GW_CHILD);
   ShowWindow(hwndFrame,
              (GetPrivateProfileInt(szSCREEN, szMAX, 0, szLABINI) == 1)
              ? SW_SHOWMAXIMIZED : nCmdShow);
   UpdateWindow(hwndFrame);

   return (BOOL)(hwndFrame!=NULL);
}

//*------------------------------------------------------------------------
//| DoMain:
//|     This is the main loop for the application:
//*------------------------------------------------------------------------
int  WINAPI DoMain(HANDLE hInstance)
{
   MSG msg;
   HANDLE hAccel;


   SendMessage(hwndFrame, USER_INITAPP, 0, 0L);
   hAccel = LoadAccelerators(hInstance,"BASEACCELS");
   while(GetMessage(&msg, NULL, 0, 0)) {
      if(!TranslateAccelerator(hwndFrame,hAccel,&msg) &&
         !TranslateMDISysAccel(hwndClient, &msg)) {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }


   return msg.wParam;
}


//*---------------------------------------------------------------------------------
//| DoCloseDown:
//|   Clean up all of the global windows, handles, etc...   After this function
//|   is called, the application may be killed off.
//| Parms:
//|   hwnd              The window handle being destoryed, send only on main
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
VOID WINAPI DoCloseDown(HWND hwnd)
{
   char     szTempBuf[10];

   // Close all connection windows
   SendMessage(hwnd, WM_COMMAND, IDM_CLOSEALL, 0L);

   // Kill off the help file if we opened it.
   if(iHelpCnt)
      WinHelp(hwnd, szHELPFILE, HELP_QUIT, 0L);

   // Save our max/min state
   wsprintf(szTempBuf, "%d", IsZoomed(hwnd));
   WritePrivateProfileString(szSCREEN, szMAX, szTempBuf, szLABINI);

   // Destroy GDI objects
   DeleteObject(hSmallEditFont);

   DestroyWindow(hwnd);
}


//*------------------------------------------------------------------------
//| WndProc:
//|     Handle requests for action:
//*------------------------------------------------------------------------
long EXTFUN WndProc(HWND      hwnd,
                        unsigned msg,
                        WPARAM     wParam,
                        LPARAM     lParam)
{
   switch(msg) {
     case WM_CREATE:
      {
         LOGFONT                 lf;
         CLIENTCREATESTRUCT         clientcreate;

         memset(&lf, 0, sizeof(LOGFONT));
         lf.lfHeight = -10;
         lf.lfWeight = FW_THIN;
         lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
         lstrcpy(lf.lfFaceName, szMSSansSerif);
         hSmallEditFont = CreateFontIndirect(&lf);

         clientcreate.hWindowMenu = hSubMenu;
         clientcreate.idFirstChild = IDM_FIRSTCHILD;
         hwndClient = CreateWindow("MDICLIENT", NULL,
                                   WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS,
                                   0, 0, 0, 0, hwnd,
                                   (HMENU)(1), hInst,
                                   (LPSTR)&clientcreate);
         if(!hwndClient)
            return -1;
      }
      return 0;


      // This user message is sent to handle any first steps once the
      // application is up and ready for input.  We'll cause a connection
      // to be done.
     case USER_INITAPP:
      SendMessage(hwnd, WM_COMMAND, IDM_CONNECT,
                  (cl.fOptions) ? (LPARAM)(LPSTR)cl.szDriverConnect : 0L);
      if(lpActiveConn &&
         *cl.szExecuteFile)
         ExecuteFile(lpActiveConn, hwnd, cl.szExecuteFile, cl.szTerm, cl.cbStmt);
      if(cl.fExit)
         SendMessage(hwnd, WM_COMMAND, IDM_EXIT, 0L);
      return 0;


      //
      // Hande the WM_INITMENUPOPUP message so that when the user selects
      //    a menu, we enable/disable each item based on our current state.
      //
     case WM_INITMENUPOPUP:
      if(!(BOOL)HIWORD(lParam))        // Not the system menu
         ResetMenu(hMenu, (int)LOWORD(lParam));
      break;

     case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam)) {
         //-------------------------------------------------------------------
         // The F6 key is a virtual key which toggles the cursor
         // location from the input/output window.
         //-------------------------------------------------------------------
        case IDM_MOVE_WINDOW:
         {
            if(lpActiveConn) {
               DWORD    dwActive=SendMessage(hwndClient, WM_MDIGETACTIVE, 0, 0L);
#ifndef WIN32
               HWND     Active = LOWORD(dwActive);
#else
               HWND     Active = (HWND)(dwActive);
#endif

               if(Active != lpActiveConn->hwnd) {
                  SendMessage(hwndClient, WM_MDIACTIVATE,
                              (WPARAM)(HWND)lpActiveConn->hwnd, 0L);
                  return 0;
               }
               if(GetFocus() == lpActiveConn->hwndIn)
                  SetFocus(lpActiveConn->hwndOut);
               else
                  SetFocus(lpActiveConn->hwndIn);
            }
         }
         return 0;


         //-------------------------------------------------------------------
         // Connect Menu
         //-------------------------------------------------------------------
        case IDM_CONNECT:
         DoConnect(hwnd, lParam);
         return 0;

        case IDM_DISCONNECT:
         DoDisconnect(lpActiveConn);
         return 0;

        case IDM_EXECUTE_FILE:
         ExecuteFile(lpActiveConn, hwnd, NULL, NULL, 0);
         return 0;

        case IDM_OPEN:
         DoFileOpen(lpActiveConn);
         return 0;

        case IDM_CLOSE:
         {
            // zzz:  Check for save if modified
            szWrite(lpActiveConn->hwndOut,
                    GetidsString(idsFileClosed, OutStr, sizeof(OutStr)),
                    (LPSTR)lpActiveConn->szFile);

            wsprintf((LPSTR)lpActiveConn->szClientTitle, szUserAt,
                     (LPSTR)lpActiveConn->CurrentUser, (LPSTR)lpActiveConn->CurrentServer);
            lpActiveConn->hFile = 0;
            ReleaseMemory(lpActiveConn->szFileBuff);
            SetWindowText(lpActiveConn->hwnd, lpActiveConn->szClientTitle);
         }
         return 0;

        case IDM_SAVE:
         DoFileSave(lpActiveConn);
         return 0;

        case IDM_SAVEAS:
         DoFileSaveAs(lpActiveConn);
         return 0;

        case IDM_EXIT:
         SendMessage(hwnd, WM_CLOSE, 0, 0L);
         return 0;


         //-------------------------------------------------------------------
         // Edit Menu
         //-------------------------------------------------------------------
        case IDM_UNDO:
        case IDM_CUT:
        case IDM_COPY:
        case IDM_PASTE:
         {
            HWND        fhwnd=GetEditWindow(lpActiveConn);

            if(fhwnd)
               SendMessage(fhwnd,
                           (wParam == IDM_CUT) ? WM_CUT :
                           (wParam == IDM_COPY) ? WM_COPY :
                           (wParam == IDM_PASTE) ? WM_PASTE : WM_UNDO,
                           0, 0L);
         }
         return 0;

        case IDM_SELECT_ALL:
         {
            HWND              fhwnd;

            if(!(fhwnd = GetEditWindow(lpActiveConn)))
               break;
            SetFocus(fhwnd);
            SendMessage(fhwnd, EM_SETSEL, 0, MAKELPARAM(0, -1));
         }
         return 0;



         //-------------------------------------------------------------------
         // Command Menu
         //-------------------------------------------------------------------
        case IDM_EXECUTE_NOW:
         ExecuteCmds(lpActiveConn, NULL);
         return 0;

        case IDM_COMMIT:
        case IDM_ROLLBACK:
         DoCommitRollback(lpActiveConn, wParam);
         return 0;



         //-------------------------------------------------------------------
         // Pipe Menu
         //-------------------------------------------------------------------
        case IDM_PIPE_EDIT:
         EditPipe(lpActiveConn);
         return 0;

        case IDM_PIPE_DO:
         HandlePipe(lpActiveConn, lpActiveResults);
         return 0;



         //-------------------------------------------------------------------
         // Info Menu
         //-------------------------------------------------------------------
        case IDM_MANAGE_DSNS:
         {
            HWND     fHwnd=GetFocus();

            SQLManageDataSources(hwnd);
            if(fHwnd)
               SetFocus(fHwnd);
         }
         return 0;

        case IDM_DATA_TYPES:
         DisplayODBCDataTypes(lpActiveConn);
         return 0;

        case IDM_FUNCTIONS:
         DisplayODBCFunctions(lpActiveConn);
         return 0;

        case IDM_DATA_SOURCES:
         DisplayODBCDataSources(lpActiveConn);
         return 0;

        case IDM_ODBC_INFO:
         DisplayGetInfo(lpActiveConn);
         return 0;



         //-------------------------------------------------------------------
         // Lists Menu
         //-------------------------------------------------------------------
        case IDM_TABLES:
        case IDM_COLUMNS:
        case IDM_STATISTICS:
        case IDM_PRIMARY_KEYS:
        case IDM_FOREIGN_KEYS:
        case IDM_TABLE_PRIVS:
        case IDM_COLUMN_PRIVS:
        case IDM_SPECIAL_COLUMNS:
        case IDM_PROCEDURES:
        case IDM_PROC_COLUMNS:
         DoList(lpActiveConn, wParam);
         return 0;



         //-------------------------------------------------------------------
         // Window Menu
         //-------------------------------------------------------------------
        case IDM_FONT:
         PromptForFontName(hwnd);
         return 0;

        case IDM_CASCADE:
         SendMessage(hwndClient, WM_MDICASCADE, 0, 0L);
         return 0;

        case IDM_TILE:
         SendMessage(hwndClient, WM_MDITILE, 0, 0L);
         return 0;

        case IDM_ARRANGE:
         SendMessage(hwndClient, WM_MDIICONARRANGE, 0, 0L);
         return 0;

        case IDM_CLOSEALL:
         {
            int         idex;
            int         iNum=NumItems(ConnectStructs);

            for(idex=0;  idex<iNum;  idex++)
               if(ConnectStructs[idex] != NULL)
                  DoDisconnect(ConnectStructs[idex]);
         }
         return 0;



         //-------------------------------------------------------------------
         // Help Menu
         //-------------------------------------------------------------------
        case IDM_HELP:
         iHelpCnt += WinHelp(hwnd, szHELPFILE, HELP_INDEX, 0L);
         return 0;

        case IDM_ABOUT:
         DisplayAbout(hwnd, hInst);
         return 0;
      }
      break;




	case WM_CLOSE:
      DoCloseDown(hwnd);
      return 0;

     case WM_DESTROY:
      PostQuitMessage(0);
      return 0;


     default:
      break;
   }

   return DefFrameProc(hwnd, hwndClient, msg, wParam, lParam);
}



//*------------------------------------------------------------------------
//| ChildWndProc:
//|     Handle all messages which are received for the MDI child
//|         windows.
//*------------------------------------------------------------------------
long EXTFUN ChildWndProc(HWND    hwnd,
                        unsigned msg,
                        WPARAM     wParam,
                        LPARAM     lParam)
{
   switch(msg) {
      //
      // When a successful connection is made, then we are called to
      //    create a window to handle it.  The CHILDINFO structure has
      //    already been allocated.
      //
     case WM_CREATE:
      {
         CREATESTRUCT FAR *      cs;
         MDICREATESTRUCT FAR *   mdi;
         lpCHILDINFO             lpci;

         cs = (CREATESTRUCT FAR *)lParam;
         mdi = (MDICREATESTRUCT FAR *)cs->lpCreateParams;
         lpci = (lpCHILDINFO)mdi->lParam;

         SETCIPOINTER(hwnd, lpci);

         lpci->hwnd = hwnd;
         lpci->hInst = hInst;
         hwndClient = GetParent(hwnd);
         hwndFrame = GetParent(hwndClient);
         if(!(lpci->hwndIn = CreateWindow("edit", NULL,
                                          WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                                          WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
                                          0, 0, 0, 0,
                                          hwnd, (HMENU)(3), hInst, NULL)))
            return -1;
         if(!(lpci->hwndOut = CreateWindow("edit", NULL,
                                           WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                                           WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
                                           0, 0, 0, 0,
                                           hwnd, (HMENU)(4), hInst, NULL)))
            return -1;


         SendMessage(lpci->hwndIn, WM_SETFONT,
                     (WPARAM)hSmallEditFont, (LPARAM)MAKELONG((WORD)TRUE, 0));
         SendMessage(lpci->hwndOut, WM_SETFONT,
                     (WPARAM)hSmallEditFont, (LPARAM)MAKELONG((WORD)TRUE, 0));

         szWrite(lpci->hwndOut,
                 GetidsString(idsSuccessConnect, OutStr, sizeof(OutStr)),
                 (LPSTR)lpci->CurrentUser, (LPSTR)lpci->CurrentServer);
      }
      return 0;

      //
      // NOTE:  We must break to return DefMDIWndProc in order for the menu to
      //    be redrawn when we maximize the child window.
      //
     case WM_SIZE:
      {
         lpCHILDINFO       lpci;
         int               di, dot;

         lpci = GETCIPOINTER(hwnd);

         lpci->dx = LOWORD(lParam);
         lpci->dy = HIWORD(lParam);
         di = lpci->dy * 1 / 2;
         dot = lpci->dy - di;
         MoveWindow(lpci->hwndIn, 0, 0, lpci->dx, di, TRUE);
         MoveWindow(lpci->hwndOut, 0, di, lpci->dx, dot, TRUE);
      }
      break;

	



      //
      // Handle the WM_INITMENUPOPUP message so that when the user selects
      //    a menu, we enable/disable each item based on our current state.
      //
     case WM_INITMENUPOPUP:
      if(!(BOOL)HIWORD(lParam))        // Not the system menu
         ResetMenu((HMENU)wParam, (int)LOWORD(lParam));
      break;


      //
      // All messages are handled in the main wnd proc, so pass them back
      //
     case WM_COMMAND:
      {
         UINT        id=GET_WM_COMMAND_ID(wParam, lParam);

         if(id >= IDM_CONNECT &&
            id <= IDM_MOVE_WINDOW)
            SendMessage(hwndFrame, WM_COMMAND, wParam, lParam);
      }
      break;


      //
      // The WM_MDIACTIVATE message is received first by the child window
      //    which is losing focus, then by the window which is receiving
      //    focus.
      //
     case WM_MDIACTIVATE:
      {
#ifndef WIN32
         if(wParam) {
            lpActiveConn = GETCIPOINTER((HWND)LOWORD(lParam));
         }
#else
         if((HWND)lParam == hwnd) {
            lpActiveConn = GETCIPOINTER((HWND)lParam);
         }
#endif
         else
            lpActiveConn = NULL;

         if(lpActiveConn) {
            hwndCurMDIChild = lpActiveConn->hwnd;
            SetFocus(lpActiveConn->hwndIn);
         }
      }
      return 0;


      //
      // Check for a system close command.  This is the equivalent of a
      //    Disconnect, so process it as such.
      //
     case WM_SYSCOMMAND:
      {
         if(wParam == SC_CLOSE) {
            SendMessage(hwnd, WM_COMMAND, IDM_DISCONNECT, 0L);
            return 0;
         }
      }
      break;

     default:
      break;
   }

   return DefMDIChildProc(hwnd, msg, wParam, lParam);
}



//*---------------------------------------------------------------------------------
//| SetUp:
//|   This function handles one-time setup operations for the app.  This includes
//|   allocating an environment handle for ODBC, and processing the command
//|   line.
//| Parms:
//|   szCmdLine         Command line arguments
//|   cl                Command line strucutre for return
//| Returns:
//|   FALSE if there was an error
//*---------------------------------------------------------------------------------
BOOL WINAPI SetUp(LPSTR szCmdLine, CMDLINE FAR * cl)
{
   LPSTR str;

   // Load default resource strings
   GetidsString(idsDftFileFilter, szDftFileFilter, sizeof(szDftFileFilter));
   str = (LPSTR)szDftFileFilter;
   while((str = strchr(str, '|')))
      *str++ = '\0';

   if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &henv)) {
      szMessageBox(GetActiveWindow(),
                   MB_ICONEXCLAMATION,
                   (LPSTR)szErrTitle,
                   GetidsString(idsSQLAllocHandleFailed, OutStr, sizeof(OutStr)));
      return FALSE;
   }

   if(SQL_SUCCESS != SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
                                   (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER)) {
      DisplayErrors(NULL, GetidsString(idsSQLSetEnvAttr, OutStr, sizeof(OutStr)),
                    SQL_HANDLE_ENV, henv);
      return FALSE;
   }

   if(!ParseCommandLine(szCmdLine, cl))
      return FALSE;

   if(cl->fTrace) {
      if(SQL_SUCCESS !=
         (retcode = SQLSetConnectAttr(NULL, SQL_ATTR_TRACEFILE,
                                      (LPSTR)cl->szTraceFile, SQL_NTS)))
         DisplayErrors(NULL, GetidsString(idsSQLSetConnectAttr, OutStr, sizeof(OutStr)),
                       SQL_HANDLE_ENV, henv);

      if(SQL_SUCCESS !=
         (retcode = SQLSetConnectAttr(NULL, SQL_ATTR_TRACE,
                                      (SQLPOINTER) SQL_TRUE,
                                      SQL_IS_INTEGER)))
         DisplayErrors(NULL, GetidsString(idsSQLSetConnectAttr, OutStr, sizeof(OutStr)),
                       SQL_HANDLE_ENV, henv);
   }

   return TRUE;
}




//*------------------------------------------------------------------------
//| CleanUp:
//|     Any last-minute application cleanup activities are done here:
//*------------------------------------------------------------------------
void WINAPI CleanUp(void)
{
   retcode = SQLFreeHandle(SQL_HANDLE_ENV, henv);

#ifdef DEBUGGING
   {
      retcode = SQLSetConnectAttr(NULL, SQL_ATTR_TRACE, SQL_FALSE, SQL_IS_INTEGER);
      WinAssert(retcode == SQL_SUCCESS, (LPSTR)"SetConnectAttr: SQL_ATTR_TRACE");
   }
#endif
}


//*---------------------------------------------------------------------------------
//| ParseCommandLine:
//|   This function will break down the command line and look for common elements.
//| Parms:
//|   instr             The input string to look at
//|   cl                Command line strucutre to store info
//| Returns:
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL WINAPI ParseCommandLine(LPSTR instr, CMDLINE FAR * cl)
{
   LPSTR    str=instr;
   LPSTR    endstr=str;

   if(!str)
      return TRUE;

   // Assume some defaults
   memset(cl, 0, sizeof(CMDLINE));
   cl->cbStmt = 1000;
   lstrcpy(cl->szTerm, (LPSTR)"\r\n");
   cl->fExit = FALSE;

   // Look for each / value.  Spaces are allowed.  Any other character
   // at this level is a syntax error
   while(endstr && *str)
      switch(*str) {
         // We have encountered a command line switch.  See which it is
        case '/':
        case '-':
         ++str;
         switch(*str) {
            // /D[] for driver connection string
           case 'D':
           case 'd':
            ++str;
            if(*str != '[' ||
               !(endstr = strchr(str, ']')))
               goto tokenerr;
            *endstr = '\0';
            if(lstrlen(cl->szDriverConnect) > sizeof(cl->szDriverConnect))
               goto toobig;
            lstrcpy(cl->szDriverConnect, str + 1);
            str = endstr + 1;
            cl->fOptions = TRUE;
            break;

            // /F for file name to execute
           case 'F':
           case 'f':
            if((endstr = strchr(++str, ' ')))
               *endstr = '\0';
            if(lstrlen(cl->szExecuteFile) > sizeof(cl->szExecuteFile))
               goto toobig;
            lstrcpy(cl->szExecuteFile, str);
            str = endstr + 1;
            break;

            // /O for options
           case 'O':
           case 'o':
            if((endstr = strchr(++str, ' ')))
               *endstr = '\0';
            if(!ParseOptionsValues(str, cl->szTerm, sizeof(cl->szTerm), &cl->cbStmt))
               goto tokenerr;
            str = endstr + 1;
            break;

            // /T for a trace file name
           case 'T':
           case 't':
            if((endstr = strchr(++str, ' ')))
               *endstr = '\0';
            if(lstrlen(cl->szTraceFile) > sizeof(cl->szTraceFile))
               goto toobig;
            lstrcpy(cl->szTraceFile, str);
            str = endstr + 1;
            cl->fTrace = TRUE;
            break;

            // /X for exit option
           case 'X':
           case 'x':
            ++str;
            if(str &&
               (*str == 'Y' || *str == 'y'))
               cl->fExit = TRUE;
            else if(*str == 'N' || *str == 'n')
               cl->fExit = FALSE;
            else
               goto tokenerr;
            ++str;
            break;

            // Not a valid argument, error
           default:
            goto tokenerr;
         }
         break;   // End of '/' or '-'

        case ' ':
         ++str;
         break;

        default:
         goto tokenerr;
      }
   return TRUE;

  tokenerr:
   szMessageBox(GetActiveWindow(),
                MB_ICONEXCLAMATION,
                (LPSTR)szErrTitle,
                GetidsString(idsInvalidCmdLine, OutStr, sizeof(OutStr)));
   return FALSE;

  toobig:
   szMessageBox(GetActiveWindow(),
                MB_ICONEXCLAMATION,
                (LPSTR)szErrTitle,
                GetidsString(idsCmdLineTooBig, OutStr, sizeof(OutStr)));
   return FALSE;
}


//*---------------------------------------------------------------------------------
//| ParseOptionsValues:
//|   This function breaks down the /O switch by returning the invidual elements.
//| Parms:
//|   instr             The string to parse
//|   szTerm            Terminator value
//|   cbTerm            Max for terminator value
//|   lpMax             Maximum size for statement execution
//| Returns:
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL WINAPI ParseOptionsValues(LPSTR instr, LPSTR szTerm, int cbTerm, int FAR * lpMax)
{
   LPSTR str=instr;
   LPSTR endstr=instr;
   char  cApost = '\'';

   // Now look for user specific values
   while(endstr && *str)
      switch(*str) {
         // Found the terminator
        case 'T':
        case 't':
         // Could be a Carriage return or a string
         ++str;
         if(*str == cApost) {
            if(!(endstr = strchr(++str, cApost)))
               return FALSE;
            *endstr = '\0';
            if(lstrlen(str) > cbTerm)
               return FALSE;
            lstrcpy(szTerm, str);
            str = endstr + 1;
         }
         else if(strncmp(str, "CR", 2) != 0)
            return FALSE;
         else {
            lstrcpy(szTerm, (LPSTR)"\r\n");
            str += 2;
         }
         break;

         // Found the Maximum length value
        case 'M':
        case 'm':
         ++str;
         if((endstr = strchr(str, ':')))
            *endstr = '\0';
         *lpMax = lpatoi(str);
         if(*lpMax < MINSTMTSIZE ||
            *lpMax > MAXSTMTSIZE)
            return FALSE;
         str = endstr + 1;
         break;

         // Ignore delimiter
        case ':':
         ++str;
         break;

         // This is an error
        default:
         return FALSE;
         break;
      }
   return TRUE;
}


//*---------------------------------------------------------------------------------
//| DoConnect:
//|   Handle the structures involved in creating a connection window.  Invoke the
//|   Connect function to do the actual ODBC work.
//| Parms:
//|   hwnd              The parent window handle for the new child
//|   dwData            Indicates a start code or string.
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
VOID WINAPI DoConnect(HWND hwnd, DWORD dwData)
{
   lpCHILDINFO       citmp;
   MDICREATESTRUCT   mdicreate;
   int               idex;

   for(idex=0;  idex<MAXCONNECTS;  idex++)
      if(!ConnectStructs[idex])
         break;

   // See if we have exceeded the max connects
   if(idex >= MAXCONNECTS) {
      szMessageBox(hwnd,
                   MB_ICONINFORMATION | MB_OK,
                   (LPSTR)szErrTitle,
                   GetidsString(idsTooManyConnects, OutStr, sizeof(OutStr)),
                   MAXCONNECTS);
      return;
   }

   citmp = (lpCHILDINFO)GetMemory(sizeof(CHILDINFO));
   if(!citmp)
      return;

   memset(citmp, 0, sizeof(CHILDINFO));

   if(Connect(citmp, hwnd,
              (HIWORD(dwData) == 1) ? NULL : (LPSTR)dwData)) {  // Pass NULL if accelerator used
      // We are connected, save the handle
      ConnectStructs[idex] = citmp;

      // Now fill out the rest
      citmp->hwndClient = hwndClient;
      citmp->henv = henv;                    // Keep local copy of global

      wsprintf((LPSTR)citmp->szClientTitle, szUserAt, (LPSTR)citmp->CurrentUser,
               (LPSTR)citmp->CurrentServer);
      mdicreate.szClass = szChildClass;
      mdicreate.szTitle = citmp->szClientTitle;
      mdicreate.hOwner  = hInst;
      mdicreate.x       = CW_USEDEFAULT;
      mdicreate.y       = CW_USEDEFAULT;
      mdicreate.cx      = CW_USEDEFAULT;
      mdicreate.cy      = CW_USEDEFAULT;
      mdicreate.style   = (hwndCurMDIChild) ? ((IsZoomed(hwndCurMDIChild)) ? WS_MAXIMIZE : 0) : 0;
      mdicreate.lParam  = (LPARAM)citmp;
      SendMessage(hwndClient, WM_MDICREATE, 0,
                  (LPARAM)(LPMDICREATESTRUCT)&mdicreate);
   }
   else {
      // No connect made, so release all memory
      retcode = SQLFreeHandle(SQL_HANDLE_DBC, citmp->hdbc);
      ReleaseMemory(citmp);
   }
}


//*---------------------------------------------------------------------------------
//| Connect:
//|   This function attempts to make a connection.  If the user has specified the
//|   /D command line option, then we will simply use the connection string.
//| Parms:
//|   ci                Connection window information
//|   hwnd              Window handle for any prompting
//|   szAutoConnect     NULL if prompt, else pointer to szConnStrIn
//| Returns:
//|   FALSE on error
//*---------------------------------------------------------------------------------
BOOL WINAPI Connect(CHILDINFO FAR * ci, HWND hwnd, LPSTR szAutoConnect)
{
   SWORD       cb;
   RETCODE     rc;
   UWORD       fExists;
   int         idex;

   if(SQL_SUCCESS != (retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &ci->hdbc))) {
      szMessageBox(GetActiveWindow(),
                   MB_ICONEXCLAMATION | MB_OK,
                   (LPSTR)szErrTitle,
                   GetidsString(idsSQLAllocHandleFailed, OutStr, sizeof(OutStr)));
      return FALSE;
   }


   // Do the connection
   if(!szAutoConnect)
      retcode = SQLDriverConnect(ci->hdbc, hwnd, NULL, 0, ci->szConnStrOut,
                                 MAXBUFF, &cb, SQL_DRIVER_COMPLETE);
   else
      retcode = SQLDriverConnect(ci->hdbc, hwnd, szAutoConnect, SQL_NTS,
                                 ci->szConnStrOut, MAXBUFF, &cb, SQL_DRIVER_NOPROMPT);
   if(retcode == SQL_NO_DATA)
      return FALSE;
   else if(retcode == SQL_ERROR) {
      PrintErrors(ci, SQL_HANDLE_DBC);
      return FALSE;
   }

   if(RC_SUCCESSFUL(retcode)) {
      SWORD len;

      retcode = SQLGetInfo(ci->hdbc, SQL_USER_NAME, ci->CurrentUser,
                           sizeof(ci->CurrentUser), &len);
      if(retcode == SQL_ERROR || len == 0)   // Assume driver not capable
         *ci->CurrentUser = '\0';

      retcode = SQLGetInfo(ci->hdbc, SQL_DATA_SOURCE_NAME, ci->CurrentServer,
                           sizeof(ci->CurrentServer), NULL);
   }

   if(SQL_SUCCESS != (retcode = SQLAllocHandle(SQL_HANDLE_STMT, ci->hdbc, &ci->hstmt))) {
      szMessageBox(GetActiveWindow(),
                   MB_ICONEXCLAMATION,
                   (LPSTR)szErrTitle,
                   GetidsString(idsSQLAllocHandleFailed, OutStr, sizeof(OutStr)));
      return FALSE;
   }

   //
   // Find out what functions are supported and store them in a bitmask
   //
   memset(&ci->fFunctions, 0, sizeof(ci->fFunctions));
   for(idex=0;  idex<NUM_MENU_FLAGS;  idex++) {
      rc = SQLGetFunctions(ci->hdbc,
                           uMenuIDs[idex],
                           &fExists);
      if(RC_NOTSUCCESSFUL(rc)) {
         fExists = FALSE;
         PrintErrors(ci, SQL_HANDLE_DBC);
      }

      if(fExists)
         BitSet(ci->fFunctions, idex);
   }

   return TRUE;
}


int WINAPI GetConnDex(lpCHILDINFO lpci)
{
   int idex;

   for(idex=0;  idex<MAXCONNECTS;  idex++)
      if(lpci == ConnectStructs[idex])
         return idex;

   return -1;
}


//*---------------------------------------------------------------------------------
//| DoDisconnect:
//|   Look for the handle passed in and then disconnect it.  The Disconnect function
//|   is used to do the ODBC portion.
//| Parms:
//|   lpci              Connect window to free
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
VOID WINAPI DoDisconnect(lpCHILDINFO lpci)
{
   int         idex;

   idex = GetConnDex(lpci);
   if(idex == -1)
      return;

   if(Disconnect(lpci)) {
      FreeConnectWindowResults(lpci);
      SendMessage(hwndClient, WM_MDIDESTROY, (WPARAM)(HWND)lpci->hwnd, 0L);
      ConnectStructs[idex] = NULL;
   }
}


//*------------------------------------------------------------------------
//| Disconnect:
//|     Make a connection to a server.
//*------------------------------------------------------------------------
BOOL WINAPI Disconnect(CHILDINFO FAR * ci)
{
   if(SQL_SUCCESS != (retcode = SQLFreeHandle(SQL_HANDLE_STMT, ci->hstmt)))
      DisplayErrors(ci->hwnd, GetidsString(idsSQLFreeHandle, OutStr, sizeof(OutStr)),
                    SQL_HANDLE_STMT, ci->hstmt);
   if(SQL_SUCCESS != (retcode = SQLDisconnect(ci->hdbc)))
      DisplayErrors(ci->hwnd, GetidsString(idsSQLDisconnect, OutStr, sizeof(OutStr)),
                    SQL_HANDLE_DBC, ci->hdbc);
   if(SQL_SUCCESS != (retcode = SQLFreeHandle(SQL_HANDLE_DBC, ci->hdbc)))
      DisplayErrors(ci->hwnd, GetidsString(idsSQLFreeHandle, OutStr, sizeof(OutStr)),
                    SQL_HANDLE_DBC, ci->hstmt);

   ci->hstmt = ci->hdbc = NULL;
   szWrite(ci->hwndOut,
           GetidsString(idsDisconnectSuccess, OutStr, sizeof(OutStr)));

   return TRUE;
}







//*------------------------------------------------------------------------
//| DisplayAbout:
//|     Display the about box for this app.
//*------------------------------------------------------------------------
void WINAPI DisplayAbout(HWND hwnd, HINSTANCE hInst)
{
   HWND     fHwnd=GetFocus();

   if(-1 == DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, (DLGPROC)AboutWndProc,
                           (LPARAM)(HINSTANCE FAR * )&hInst))
      MessageBox(hwnd, "Could not open dialog box.",
                 "About", MB_ICONEXCLAMATION);

   if(fHwnd)
      SetFocus(fHwnd);
}



//*------------------------------------------------------------------------
//| AboutWndProc:
//|     Handle the About messages
//*------------------------------------------------------------------------
BOOL EXTFUN AboutWndProc(HWND    hDlg,
                              unsigned msg,
                              WPARAM     wParam,
                              LPARAM     lParam)
{
   int x=10,y=30;
   static HINSTANCE FAR *  lpHINST;

   switch(msg) {
     case WM_INITDIALOG:
      lpHINST = (HINSTANCE FAR *)lParam;
      CenterDialog(hDlg);
      return TRUE;

     case WM_COMMAND:
      SendMessage(hDlg, WM_CLOSE, 0, 0L);
      return TRUE;


     case WM_CLOSE:
      EndDialog(hDlg, FALSE);
      return TRUE;


     default:
      return FALSE;
   }
}



//*------------------------------------------------------------------------
//| Busy:
//|     Display the hour glass cursor when we are working
//|         flag = TRUE means we are busy to so display it
//|         flag = FALSE means go back to old cursor
//*------------------------------------------------------------------------
void Busy(int flag)
{
   static HCURSOR hCursor;                // Save old cursor handle

   ShowCursor(FALSE);
   if(flag)
      hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
   else
      SetCursor(hCursor);
   ShowCursor(TRUE);
}



//*---------------------------------------------------------------------------------
//| iLoadString:
//|   This function will retrieve a string from our resource fork and place it
//|      in the buffer provided.  If the string is not found, an empty string
//|      is returned.
//| Parms:
//|   in       id                   String number to retrieve
//|   in       str                  Output string
//|   in       len                  Lenth of possible output
//| Returns:
//|   Pointer to buffer str
//*---------------------------------------------------------------------------------
LPSTR iLoadString(int id, LPSTR str, int len)
{
   if(!str ||
      len <= 0)
      return str;

   if(!LoadString(hInst, id, str, len))
      *str = '\0';
   return str;
}


//*---------------------------------------------------------------------------------
//| GetEditWindow:
//|   This function will get the current focus window and verify that it is
//|   an edit window which is valid for one of the Edit menu items.
//| Parms:
//|   lpci                 Connection window information
//| Returns:
//|   Edit window handle if valid, NULL if not valid
//*---------------------------------------------------------------------------------
HWND INTFUN GetEditWindow(lpCHILDINFO lpci)
{
   HWND hwnd;
   hwnd = GetFocus();

   if(hwnd && lpci) {
      if(hwnd == lpci->hwndIn ||
         hwnd == lpci->hwndOut)
         return hwnd;
   }

   return NULL;
}


//*------------------------------------------------------------------------
//| CenterDialog:
//|      Center the dialog over the parent window.  It is possible that
//|         their is not a parent window, since the Translate DLL was
//|         never meant to display data.  For this reason, we may just
//|         center over the entire screen.
//*------------------------------------------------------------------------
void WINAPI  CenterDialog(HWND hdlg)
{
   RECT  rcParent;                         // Parent window client rect
   RECT  rcDlg;                            // Dialog window rect
   int   nLeft, nTop;                      // Top-left coordinates
   int   cWidth, cHeight;                  // Width and height
   HWND  hwnd;

   // Get frame window client rect in screen coordinates
   if((hwnd = GetParent(hdlg)) == NULL) {
      rcParent.top = rcParent.left = 0;
      rcParent.right = GetSystemMetrics(SM_CXFULLSCREEN);
      rcParent.bottom = GetSystemMetrics(SM_CYFULLSCREEN);
   }
   else
      GetWindowRect(hwnd, &rcParent);

   // Determine the top-left point for the dialog to be centered
   GetWindowRect(hdlg, &rcDlg);
   cWidth  = rcDlg.right  - rcDlg.left;
   cHeight = rcDlg.bottom - rcDlg.top;
   nLeft   = rcParent.left +
      (((rcParent.right  - rcParent.left) - cWidth ) / 2);
   nTop    = rcParent.top  +
      (((rcParent.bottom - rcParent.top ) - cHeight) / 2);
   if (nLeft < 0) nLeft = 0;
   if (nTop  < 0) nTop  = 0;

   // Place the dialog
   MoveWindow(hdlg, nLeft, nTop, cWidth, cHeight, TRUE);
   return;
}


//*---------------------------------------------------------------------------------
//| DoFileOpen:
//|   Use the commond dialog functions to open a file.
//| Parms:
//|   lpci                    Connection window information
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
VOID WINAPI DoFileOpen(lpCHILDINFO lpci)
{
   OPENFILENAME      ofn;
   HWND              fHwnd=GetFocus();


   // If user has a file open already, verify that we should continue
   if(lpci->hFile) {
      if(IDYES == szMessageBox(lpci->hwnd,
                               MB_YESNO,
                               (LPSTR)szOPENFILE,
                               GetidsString(idsCloseFile, OutStr, sizeof(OutStr)),
                               (LPSTR)lpci->szFile))
         SendMessage(lpci->hwnd, WM_COMMAND, IDM_CLOSE, 0L);
      else
         return;
   }

   // Now ask to open a file
   lpci->szFileBuff = (LPSTR)GetMemory(MAXFILEBUFF);
   if(!lpci->szFileBuff)
      return;

   if(!*szDirName)
      GetWindowsDirectory(szDirName, sizeof(szDirName));

   // Fill out the struct
   memset(&ofn, 0, sizeof(OPENFILENAME));
   lpci->szFile[0] = '\0';
   ofn.lStructSize =          sizeof(OPENFILENAME);
   ofn.hwndOwner =            lpci->hwnd;
   ofn.lpstrFilter =          szDftFileFilter;
   ofn.nFilterIndex =         1;
   ofn.lpstrFile =            lpci->szFile;
   ofn.nMaxFile =             sizeof(lpci->szFile);
   ofn.lpstrInitialDir =      szDirName;
   ofn.Flags =                OFN_HIDEREADONLY |
      OFN_PATHMUSTEXIST |
         OFN_FILEMUSTEXIST;

   // Try to open the file
   if(GetOpenFileName(&ofn)) {
      if(fHwnd)
         SetFocus(fHwnd);

      if(HFILE_ERROR == (lpci->hFile = _lopen(ofn.lpstrFile, OF_READ))) {
         szMessageBox(lpci->hwnd,
                      MB_ICONEXCLAMATION,
                      (LPSTR)szOPENFILE,
                      GetidsString(idsOpenFileFailed, OutStr, sizeof(OutStr)),
                      (LPSTR)ofn.lpstrFile);
         return;
      }

      lpci->cbFileSize = _lread(lpci->hFile,
                                (void FAR *)lpci->szFileBuff, MAXFILEBUFF);
      _lclose(lpci->hFile);
      szWrite(lpci->hwndIn, (LPSTR)lpci->szFileBuff);
      SendMessage(lpci->hwndIn, EM_SETMODIFY, FALSE, 0L);
      wsprintf((LPSTR)lpci->szClientTitle, szUserAtFile,
               (LPSTR)lpci->CurrentUser, (LPSTR)lpci->CurrentServer,
               (LPSTR)ofn.lpstrFile);
      SetWindowText(lpci->hwnd, lpci->szClientTitle);
      GetNewDirectory(szDirName, ofn.lpstrFile);
   }

   if(fHwnd)
      SetFocus(fHwnd);
}


//*---------------------------------------------------------------------------------
//| DoSave:
//|   Save the current file.
//| Parms:
//|   lpci                    Connection window information
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
VOID WINAPI DoFileSave(lpCHILDINFO lpci)
{
   OFSTRUCT       ofs;

   ofs.cBytes = sizeof(OFSTRUCT);

   lpci->cbFileSize = GetWindowText(lpci->hwndIn,
                                    (LPSTR)lpci->szFileBuff, MAXFILEBUFF);
   if(HFILE_ERROR == (lpci->hFile =
                      OpenFile(lpci->szFile, &ofs, OF_CREATE))) {
      szMessageBox(lpci->hwnd,
                   MB_ICONEXCLAMATION,
                   (LPSTR)szSAVEFILE,
                   GetidsString(idsSaveFileFailed, OutStr, sizeof(OutStr)),
                   (LPSTR)lpci->szFile);
      return;
   }

   _lwrite(lpci->hFile, (void FAR *)lpci->szFileBuff, lstrlen(lpci->szFileBuff));
   _lclose(lpci->hFile);
}


//*---------------------------------------------------------------------------------
//| DoFileSaveAs:
//|   Use the commond dialog functions to save a file.
//| Parms:
//|   lpci                    Connection window information
//| Returns:
//|   Nothing
//*---------------------------------------------------------------------------------
VOID INTFUN DoFileSaveAs(lpCHILDINFO lpci)
{
   OPENFILENAME         ofn;
   HWND                 fHwnd=GetFocus();
   char                 szSaveFile[_MAX_PATH];

   // Fill out struct
   szSaveFile[0] = '\0';
   memset(&ofn, 0, sizeof(OPENFILENAME));
   ofn.lStructSize =          sizeof(OPENFILENAME);
   ofn.hwndOwner =            lpci->hwnd;
   ofn.lpstrFilter =          szDftFileFilter;
   ofn.nFilterIndex =         1;
   ofn.lpstrFile =            szSaveFile;
   ofn.nMaxFile =             sizeof(lpci->szFile);
   ofn.lpstrInitialDir =      szDirName;
   ofn.Flags =                OFN_HIDEREADONLY |
      OFN_PATHMUSTEXIST |
         OFN_OVERWRITEPROMPT;


   // See if user selects a file
   if(GetSaveFileName(&ofn)) {
      lstrcpy(lpci->szFile, szSaveFile);
      wsprintf((LPSTR)lpci->szClientTitle, szUserAtFile,
               (LPSTR)lpci->CurrentUser, (LPSTR)lpci->CurrentServer,
               (LPSTR)szSaveFile);
      SetWindowText(lpci->hwnd, lpci->szClientTitle);
      DoFileSave(lpci);
   }

   if(fHwnd)
      SetFocus(fHwnd);
}
