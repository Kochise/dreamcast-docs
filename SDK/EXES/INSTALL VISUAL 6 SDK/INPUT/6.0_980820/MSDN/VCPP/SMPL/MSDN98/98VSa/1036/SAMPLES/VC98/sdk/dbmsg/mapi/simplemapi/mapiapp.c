/* QuickCase:W KNB Version 1.00 */
#include "MAPIAPP.h"
#include <string.h>
#include <stdio.h>
#include "mapi.h"
#define MAIN 1
#include "mapinit.h"


HANDLE hLibrary;
LHANDLE hMAPISession;

MapiMessage mmMapiMessage;

ULONG nMessageSize = 0x000004000;
lpMapiMessage FAR *lppMessage;
lpMapiMessage lpMessage;
char szSeedMessageID[512];
char szMessageID[512];
char szSubject[512];
char szNoteText[4096];

LPSTR lpszSeedMessageID = &szSeedMessageID[0];
LPSTR lpszMessageID = &szMessageID[0];

LPSTR pszSubject = &szSubject[0];
LPSTR pszNoteText = &szNoteText[0];
LPSTR pszDateReceived = "1991/03/23 12:00";
MapiRecipDesc rdOriginator = { 0L,MAPI_ORIG,(LPSTR)"ONE",NULL};

int iFindFirst= TRUE;

void InitMessage(lpMapiMessage pmmMessage)
{
  pmmMessage->ulReserved = 0L;
  pmmMessage->lpszSubject =pszSubject;
  pmmMessage->lpszNoteText =pszNoteText;
  pmmMessage->lpszMessageType = NULL;
  pmmMessage->lpszDateReceived = pszDateReceived;
  pmmMessage->flFlags = MAPI_UNREAD;
  pmmMessage->lpOriginator = &rdOriginator;
  pmmMessage->nRecipCount = 0L;
  pmmMessage->lpRecips = NULL;
  pmmMessage->nFileCount = 0L;
  pmmMessage->lpFiles = NULL;
}

/****************************************************************************

    FUNCTION: OutOfMemory(void)

    PURPOSE:  Displays warning message

****************************************************************************/
void OutOfMemory(void)
{
    MessageBox(
        GetFocus(),
        GetStringRes (IDS_ERR_NO_MEMORY),
        NULL,
        MB_ICONHAND | MB_SYSTEMMODAL);
    return;
}

void mycpystr(char * npszStrg, LPSTR lpszStrg)
{
  if (lpszStrg != NULL)
    strcpy(npszStrg, lpszStrg);
  else
     *npszStrg = '\0';
}


/************************************************************************/
/*                                                                      */
/* Windows 3.0 Main Program Body                                        */
/*                                                                      */
/* The following routine is the Windows Main Program.  The Main Program */
/* is executed when a program is selected from the Windows Control      */
/* Panel or File Manager.  The WinMain routine registers and creates    */
/* the program's main window and initializes global objects.  The       */
/* WinMain routine also includes the applications message dispatch      */
/* loop.  Every window message destined for the main window or any      */
/* subordinate windows is obtained, possibly translated, and            */
/* dispatched to a window or dialog processing function. The dispatch   */
/* loop is exited when a WM_QUIT message is obtained.  Before exiting   */
/* the WinMain routine should destroy any objects created and free      */
/* memory and other resources.                                          */
/*                                                                      */
/************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
 /***********************************************************************/
 /* HANDLE hInstance;       handle for this instance                    */
 /* HANDLE hPrevInstance;   handle for possible previous instances      */
 /* LPSTR  lpszCmdLine;     long pointer to exec command line           */
 /* int    nCmdShow;        Show code for main window display           */
 /***********************************************************************/

 MSG        msg;           /* MSG structure to store your messages        */
 int        nRc;           /* return value from Register Classes          */
 long       nWndunits;     /* window units for size and location          */
 int        nWndx;         /* the x axis multiplier                       */
 int        nWndy;         /* the y axis multiplier                       */
 int        nX;            /* the resulting starting point (x, y)         */
 int        nY;
 int        nWidth;        /* the resulting width and height for this     */
 int        nHeight;       /* window                                      */

 strcpy(szAppName, "MAPIAPP");
 hInst = hInstance;
 if(!hPrevInstance)
   {
    /* register window classes if first instance of application         */
    if ((nRc = nCwRegisterClasses()) == -1)
      {
       /* registering one of the windows failed                         */
       LoadString(hInst, IDS_ERR_REGISTER_CLASS, szString, sizeof(szString));
       MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
       return nRc;
      }
   }

 /* Create a device independant size and location                       */
 nWndunits = GetDialogBaseUnits();
 nWndx = LOWORD(nWndunits);
 nWndy = HIWORD(nWndunits);
 nX = ((60 * nWndx) / 4);
 nY = ((60 * nWndy) / 8);
 nWidth = ((197 * nWndx) / 4);
 nHeight = ((138 * nWndy) / 8);

 /* create application's Main window                                    */
 hWndMain = CreateWindow(
                szAppName,               /* Window class name           */
				GetStringRes (IDS_APP_TITLE),  /* Window's title        */
                WS_CAPTION      |        /* Title and Min/Max           */
                WS_SYSMENU      |        /* Add system menu box         */
                WS_MINIMIZEBOX  |        /* Add minimize box            */
                WS_MAXIMIZEBOX  |        /* Add maximize box            */
                WS_BORDER       |        /* thin frame                  */
                WS_CLIPCHILDREN |        /* don't draw in child windows areas */
                WS_OVERLAPPED,
                nX, nY,                  /* X, Y                        */
                nWidth, nHeight,         /* Width, Height of window     */
                NULL,                    /* Parent window's handle      */
                NULL,                    /* Default to Class Menu       */
                hInst,                   /* Instance of window          */
                NULL);                   /* Create struct for WM_CREATE */


 if (InitMAPI() != 0)
   return ERR_LOAD_LIB;

  InitMessage(&mmMapiMessage);

 if(hWndMain == NULL)
   {
    LoadString(hInst, IDS_ERR_CREATE_WINDOW, szString, sizeof(szString));
    MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
    return IDS_ERR_CREATE_WINDOW;
   }

 EnableMenuItem(GetMenu(hWndMain), IDM_A_LOGOFF, MF_DISABLED | MF_GRAYED);
 EnableMenuItem(GetMenu(hWndMain), IDM_S_MAIL, MF_DISABLED | MF_GRAYED);
 EnableMenuItem(GetMenu(hWndMain), IDM_S_DOCUMENT, MF_DISABLED | MF_GRAYED);
 EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDFIRST, MF_DISABLED | MF_GRAYED);
 EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDNEXT, MF_DISABLED | MF_GRAYED);
 EnableMenuItem(GetMenu(hWndMain), IDM_M_READ, MF_DISABLED | MF_GRAYED);
 EnableMenuItem(GetMenu(hWndMain), IDM_M_DELETE, MF_DISABLED | MF_GRAYED);

 ShowWindow(hWndMain, nCmdShow);            /* display main window      */

 while(GetMessage(&msg, NULL, 0, 0))        /* Until WM_QUIT message    */
   {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
   }

 DeInitMAPI();
 /* Do clean up before exiting from the application                     */
 CwUnRegisterClasses();
 return msg.wParam;
} /*  End of WinMain                                                    */
/************************************************************************/
/*                                                                      */
/* Main Window Procedure                                                */
/*                                                                      */
/* This procedure provides service routines for the Windows events      */
/* (messages) that Windows sends to the window, as well as the user     */
/* initiated events (messages) that are generated when the user selects */
/* the action bar and pulldown menu controls or the corresponding       */
/* keyboard accelerators.                                               */
/*                                                                      */
/* The SWITCH statement shown below distributes the window messages to  */
/* the respective message service routines, which are set apart by the  */
/* CASE statements. The window procedures must provide an appropriate   */
/* service routine for its end user initiated messages, as well as the  */
/* general Windows messages (ie. WM_CLOSE message). If a message is     */
/* sent to this procedure for which there is no programmed CASE clause  */
/* (i.e., no service routine), the message is defaulted to the          */
/* DefWindowProc function, where it is handled by Windows               */
/*                                                                      */
/* For the end-user initiated messages, this procedure is concerned     */
/* principally with the WM_COMMAND message. The menu control ID (or the */
/* corresponding accelerator ID) is communicated to this procedure in   */
/* the first message parameter (wParam). The window procedure provides  */
/* a major CASE statement for the WM_COMMAND message and a subordinate  */
/* SWITCH statement to provide CASE clauses for the message service     */
/* routines for the various menu item's, identified by their ID values. */
/*                                                                      */
/* The message service routines for the individual menu items are the   */
/* main work points in the program. These service routines contain the  */
/* units of work performed when the end user select one of the menu     */
/* controls. The required application response to a menu control is     */
/* programmed in its associated CASE clause. The service routines may   */
/* contain subroutine calls to separately compiled and libraried        */
/* routines, in-line calls to subroutines to be embodied in this source */
/* code module, or program statements entered directly in the CASE      */
/* clauses. Program control is switched to the appropriate service      */
/* routine when Windows recognizes the end user event and sends a WM_COMMAND */
/* message to the window procedure. The service routine provides the    */
/* appropriate application-specific response to the end user initiated  */
/* event, then breaks to return control to the WinMain() routine which  */
/* continues to service the message queue of the window(s).             */
/*                                                                      */
/************************************************************************/

LONG FAR PASCAL WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
 HMENU      hMenu=0;            /* handle for the menu                 */
 HBITMAP    hBitmap=0;          /* handle for bitmaps                  */
 HDC        hDC;                /* handle for the display device       */
 PAINTSTRUCT ps;                /* holds PAINT information             */
 int        nRc=0;              /* return code                         */
 FLAGS flFlag = 0L;
 ULONG ulResult;
  char szBuf[32*1024]; // Waste of stack space, but this is only a demo.
  char szTmp[32*1024]; // Waste of stack space, but this is only a demo.

 switch (Message) {
   case WM_COMMAND:
     /* The Windows messages for action bar and pulldown menu items */
     /* are processed here.                                         */
     /* The WM_COMMAND message contains the message ID in its first */
     /* parameter (wParam). This routine is programmed to SWITCH on */
     /* the #define values generated by CASE:W for the menu items   */
     /* in the application's header (*.H) file. The ID values have  */
     /* the format, IDM_itemname. The service routines for the      */
     /* various menu items follow the CASE statements up to the     */
     /* generated BREAK statements.                                 */
     switch (LOWORD(wParam)) {
       case IDM_A_LOGON:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "Log&In" here.                      */
         flFlag =MAPI_NEW_SESSION | MAPI_LOGON_UI;
         ulResult = (*lpfnMAPILogon)(hWnd, NULL, NULL, flFlag, 0L, (LPLHANDLE)&hMAPISession);
         if (ulResult == 0L) {
           EnableMenuItem(GetMenu(hWndMain), IDM_A_LOGOFF, MF_ENABLED);
           EnableMenuItem(GetMenu(hWndMain), IDM_S_MAIL, MF_ENABLED);
           EnableMenuItem(GetMenu(hWndMain), IDM_S_DOCUMENT, MF_ENABLED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDFIRST, MF_ENABLED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDNEXT, MF_ENABLED);
         }
       break;

       case IDM_A_LOGOFF:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "Log&Off" here.                     */
         ulResult = (*lpfnMAPILogoff)(hMAPISession, hWnd, 0L, 0L);
         if (ulResult == 0L) {
            EnableMenuItem(GetMenu(hWndMain), IDM_A_LOGOFF, MF_DISABLED | MF_GRAYED);
             EnableMenuItem(GetMenu(hWndMain), IDM_S_MAIL, MF_DISABLED | MF_GRAYED);
             EnableMenuItem(GetMenu(hWndMain), IDM_S_DOCUMENT, MF_DISABLED | MF_GRAYED);
             EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDFIRST, MF_DISABLED | MF_GRAYED);
             EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDNEXT, MF_DISABLED | MF_GRAYED);
             EnableMenuItem(GetMenu(hWndMain), IDM_M_READ, MF_DISABLED | MF_GRAYED);
             EnableMenuItem(GetMenu(hWndMain), IDM_M_DELETE, MF_DISABLED | MF_GRAYED);
         }
       break;

       case IDM_S_MAIL:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "&Mail" here.                       */
          flFlag =MAPI_DIALOG;
         ulResult = (*lpfnMAPISendMail)(hMAPISession, hWnd, &mmMapiMessage, flFlag, 0L);
       break;

       case IDM_S_DOCUMENT:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "&Document" here.                   */
         ulResult = (*lpfnMAPISendDocuments)(hWnd, ";", "C:\\CONFIG.SYS", "CONFIG.SYS", 0L);
       break;

       case IDM_M_FINDFIRST:
           iFindFirst=TRUE;
       case IDM_M_FINDNEXT:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "&Find Next" here.                  */
         if (iFindFirst) {
           *lpszSeedMessageID = '\0';
           iFindFirst = FALSE;
         }
         else {
           strcpy(lpszSeedMessageID,lpszMessageID);
         }
         ulResult = (*lpfnMAPIFindNext)(hMAPISession, hWnd, NULL, lpszSeedMessageID, flFlag, 0L, lpszMessageID);
         if (ulResult == 0L) {
           EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDNEXT, MF_ENABLED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_READ, MF_ENABLED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_DELETE, MF_ENABLED);
         }
         else {
           EnableMenuItem(GetMenu(hWndMain), IDM_M_FINDNEXT, MF_DISABLED | MF_GRAYED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_READ, MF_DISABLED | MF_GRAYED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_DELETE, MF_DISABLED | MF_GRAYED);
         }
       break;

       case IDM_M_READ:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "&Read" here.                       */

           lppMessage= (lpMapiMessage FAR *) &lpMessage;
           ulResult = (*lpfnMAPIReadMail)(hMAPISession, hWnd, lpszMessageID, flFlag, 0L, lppMessage);
           if (ulResult == 0L) {
             mycpystr(szTmp,lpMessage->lpOriginator->lpszName);
			 sprintf(szBuf, GetStringRes(IDS_FROM), szTmp);
             mycpystr(szTmp,lpMessage->lpRecips[0].lpszName);
             sprintf(szBuf, GetStringRes(IDS_TO), szBuf,szTmp);
             mycpystr(szTmp,lpMessage->lpszDateReceived);
             sprintf(szBuf, GetStringRes(IDS_DATE), szBuf,szTmp);
             mycpystr(szTmp,lpMessage->lpszSubject);
			 sprintf(szBuf, GetStringRes(IDS_SUBJECT), szBuf,szTmp);
			 mycpystr(szTmp,lpMessage->lpszNoteText);
			 sprintf(szBuf,"%s%s",szBuf,szTmp);
             
			 MessageBox(hWnd,szBuf, GetStringRes(IDS_MESSAGE), MB_OK);
             ulResult = lpfnMAPIFreeBuffer((LPVOID)lpMessage);
           }
       break;

       case IDM_M_DELETE:
            /* Place User Code to respond to the                   */
            /* Menu Item Named "&Delete" here.                  */

         ulResult = (*lpfnMAPIDeleteMail)(hMAPISession, hWnd, lpszMessageID, flFlag, 0l);
         if (ulResult == 0L) {
           EnableMenuItem(GetMenu(hWndMain), IDM_M_READ, MF_DISABLED | MF_GRAYED);
           EnableMenuItem(GetMenu(hWndMain), IDM_M_DELETE, MF_DISABLED | MF_GRAYED);
         }
       break;

       default:
         return DefWindowProc(hWnd, Message, wParam, lParam);
     }
     if (ulResult != 0L) {       /** oops **/

       sprintf(szBuf, GetStringRes(IDS_RETURNED_ERROR), ulResult);
       MessageBox(hWnd,szBuf, GetStringRes(IDS_FAILED),MB_OK);
     }
     else {
       sprintf(szBuf, GetStringRes(IDS_GOOD_JOB));
       MessageBox(hWnd,szBuf, GetStringRes(IDS_SUCCESS), MB_OK);
     }
   break;        /* End of WM_COMMAND                             */

   case WM_CREATE:
     /* The WM_CREATE message is sent once to a window when the     */
     /* window is created.  The window procedure for the new window */
     /* receives this message after the window is created, but      */
     /* before the window becomes visible.                          */
     /*                                                             */
     /* Parameters:                                                 */
     /*                                                             */
     /*    lParam  -  Points to a CREATESTRUCT structure with       */
     /*               the following form:                           */
     /*                                                             */
     /*    typedef struct                                           */
     /*              {                                              */
     /*               LPSTR     lpCreateParams;                     */
     /*               HANDLE    hInst;                              */
     /*               HANDLE    hMenu;                              */
     /*               HWND      hwndParent;                         */
     /*               int       cy;                                 */
     /*               int       cx;                                 */
     /*               int       y;                                  */
     /*               int       x;                                  */
     /*               LONG      style;                              */
     /*               LPSTR     lpszName;                           */
     /*               LPSTR     lpszClass;                          */
     /*               DWORD     dwExStyle;                          */
     /*              }  CREATESTRUCT;                               */



   break;       /*  End of WM_CREATE                              */

   case WM_MOVE:     /*  code for moving the window                    */
   break;

   case WM_SIZE:     /*  code for sizing client area                   */
        /* wParam contains a code indicating the requested sizing      */
        /* lParam contains the new height and width of the client area */
   break;       /* End of WM_SIZE                                 */

   case WM_PAINT:    /* code for the window's client area              */
     /* Obtain a handle to the device context                       */
     /* BeginPaint will sends WM_ERASEBKGND if appropriate          */
     memset(&ps, 0x00, sizeof(PAINTSTRUCT));
     hDC = BeginPaint(hWnd, &ps);

     /* Included in case the background is not a pure color         */
     SetBkMode(hDC, TRANSPARENT);

     /* Application should draw on the client window using          */
     /* the GDI graphics and text functions.  'ps' the PAINTSTRUCT  */
     /* returned by BeginPaint contains a rectangle to the          */
     /* area that must be repainted.                                */

     /* Inform Windows painting is complete                         */
     EndPaint(hWnd, &ps);
   break;       /*  End of WM_PAINT                               */

   case WM_CLOSE:  /* close the window                                 */
     /* Destroy child windows, modeless dialogs, then, this window  */
     DestroyWindow(hWnd);
     if (hWnd == hWndMain)
       PostQuitMessage(0);  /* Quit the application                 */
   break;

   default:
        /* For any message for which you don't specifically provide a  */
        /* service routine, you should return the message to Windows   */
        /* for default message processing.                             */
     return DefWindowProc(hWnd, Message, wParam, lParam);
 }
 return 0L;
}     /* End of WndProc                                         */

/************************************************************************/
/*                                                                      */
/* nCwRegisterClasses Function                                          */
/*                                                                      */
/* The following function registers all the classes of all the windows  */
/* associated with this application. The function returns an error code */
/* if unsuccessful, otherwise it returns 0.                             */
/*                                                                      */
/************************************************************************/

int nCwRegisterClasses(void)
{
 WNDCLASS   wndclass;    /* struct to define a window class             */
 memset(&wndclass, 0x00, sizeof(WNDCLASS));


 /* load WNDCLASS with window's characteristics                         */
 wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNWINDOW;
 wndclass.lpfnWndProc = WndProc;
 /* Extra storage for Class and Window objects                          */
 wndclass.cbClsExtra = 0;
 wndclass.cbWndExtra = 0;
 wndclass.hInstance = hInst;
 wndclass.hIcon = LoadIcon(hInst, "MAPIAPP");
 wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
 /* Create brush for erasing background                                 */
 wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
 wndclass.lpszMenuName = szAppName;   /* Menu Name is App Name */
 wndclass.lpszClassName = szAppName; /* Class Name is App Name */
 if(!RegisterClass(&wndclass))
   return -1;


 return(0);
} /* End of nCwRegisterClasses                                          */

/************************************************************************/
/*  CwUnRegisterClasses Function                                        */
/*                                                                      */
/*  Deletes any refrences to windows resources created for this         */
/*  application, frees memory, deletes instance, handles and does       */
/*  clean up prior to exiting the window                                */
/*                                                                      */
/************************************************************************/

void CwUnRegisterClasses(void)
{
 WNDCLASS   wndclass;    /* struct to define a window class             */
 memset(&wndclass, 0x00, sizeof(WNDCLASS));

 UnregisterClass(szAppName, hInst);
}    /* End of CwUnRegisterClasses                                      */


//---------------------------------------------------------------------------
//
// FUNCTION:    GetStringRes (int id INPUT ONLY)
//
// COMMENTS:    Load the resource string with the ID given, and return a
//              pointer to it.  Notice that the buffer is common memory so
//              the string must be used before this call is made a second time.
//
//---------------------------------------------------------------------------

LPTSTR GetStringRes (int id)
{
  static TCHAR buffer[MAX_PATH];

  buffer[0]=0;
  LoadString (GetModuleHandle (NULL), id, buffer, MAX_PATH);
  return buffer;
}
