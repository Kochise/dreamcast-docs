/*************************************************************************

SMSVIEW.EXE - This Module creates Views based on the current Group Map in
SMS

Copyright (c), 1994 by Microsoft Corp.

Modified: 7/11/95 a-cvadai  Added error message messageboxes.

*************************************************************************/

#define DBNTWIN32       // must identify operating system environment
#include "windows.h"

#include <ctl3d.h>


#include <sqlfront.h>
#include <sqldb.h>     // DB-LIB header file (should always be included)
#include <stdio.h>
#include <winnt.h>
#include "smsview.h"
#include "smsviews.h"
#include "resource.h"

typedef int (*PFNDLL)();
struct DBLOGIN {
 char ServerName[MAX_NAME];
 char LoginId   [MAX_NAME];
 char Password  [MAX_NAME];
 char DBName    [MAX_NAME];
 int DropOnly;
 } dbLoginInfo;
int CmdComplete;

void ErrorMsg(int ,int);

int PASCAL WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HINSTANCE hInstance;                 /* current instance         */
HINSTANCE hPrevInstance;                 /* previous instance        */
LPSTR lpCmdLine;                 /* command line             */
int nCmdShow;                    /* show-window type (open/icon) */
{

    PFNDLL GenViews = NULL;
    static HANDLE hLib = NULL;



    // Forward declarations of the error handler and message handler.

    if (!hPrevInstance)         /* Has application been initialized? */
      if (!SqlTestInit(hInstance))
        return (0);             /* Exits if unable to initialize     */

    hInst = hInstance;          /* Saves the current instance        */

    Ctl3dRegister( hInst );
    Ctl3dAutoSubclass( hInst );

    CmdComplete = CheckCommandLine(lpCmdLine);
    if ( ! GetConnectionInfo(CmdComplete))
     return(0);

   Ctl3dUnregister( hInst );

   return(1);
}

 int CheckCommandLine(char * lpCmdLine)
 {
  int Len;
  char * pSlash1 = lpCmdLine;

  memset (&dbLoginInfo,'\0',sizeof(dbLoginInfo));

  if ( strlen(lpCmdLine) == 0)
   return(0);
  while ( (pSlash1 = (strchr(pSlash1,'/'))) ) { // Find First Param

       // Find Next Param
  //  pSlash2 = (strchr(pSlash1+1,'/');

   if ( (Len = (strchr(pSlash1,' ') - pSlash1)) < 0 )
     Len = MAX_NAME;
   if ( Len > MAX_NAME){
    ErrorMsg(IDS_ERR_CMD_TOO_LONG,DISP);
    return(0);
   }

    Len-=(strchr(pSlash1,':')-pSlash1)+1;    //Subtract the /?: off the string Length
    if ( Len < 0)  //Invalid switch
     return(0);

    pSlash1++; //Point to First char of the keyword
    switch (toupper(pSlash1[0])) {
     case  SERVERNAMEPARAM :
           strncpy(dbLoginInfo.ServerName,strchr(pSlash1,':')+1,Len);
           break;
     case  LOGINIDPARAM :
           strncpy(dbLoginInfo.LoginId,strchr(pSlash1,':')+1,Len);
           break;
     case  PASSWORDPARAM:
           strncpy(dbLoginInfo.Password,strchr(pSlash1,':')+1,Len);
           break;
     case  DBNAMEPARAM:
           strncpy(dbLoginInfo.DBName,strchr(pSlash1,':')+1,Len);
           break;
    }
  } // End While

   return(1);
 }
//GetConnectionInfo
GetConnectionInfo(CmdComplete)
 int CmdComplete;
{
    DWORD Er;
    if(  !CmdComplete ) {
         if( DialogBoxParam(hInst, TEXT("IDD_ConnectionDlg"), NULL,
                              (DLGPROC)dbConnect, 2 )== -1){
                    Er = GetLastError();
                    return(0);
         }
     }
     else
        if ( SetupDbConnection() == FAIL)
             return(FAIL);

     return(1);
}
/***************************************************************************\
* dbConnect()
*
* GetConnection Details from DLG Box
*
* History:
* 6/5/92  2am
*   Created.
\***************************************************************************/
LRESULT WINAPI dbConnect(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

    static char ServerName[MAX_NAME]  ;
    static char * lpszHold = ServerName;
    HCURSOR CurArrow,CurWait;

    switch (message){
      case WM_INITDIALOG:{

             // Set Default Server Name
        SendDlgItemMessage( hDlg, IDC_SERVERNAME, MAX_NAME,
                            (WPARAM)MAX_NAME, (LPARAM)0);

        if( SendDlgItemMessage( hDlg, IDC_SERVERNAME, WM_SETTEXT, 0,
                                (LPARAM)lpszHold) == LB_ERR ){
            //ErrorMsg(TEXT("Rename: Add Source String failure."),DISP);
            return(1);
        }
        //Set default Login ID
        lstrcpy(lpszHold,"sa");

         SendDlgItemMessage( hDlg, IDC_LOGINID, MAX_NAME,
                            (WPARAM)MAX_NAME, (LPARAM)0);

        if( SendDlgItemMessage( hDlg, IDC_LOGINID, WM_SETTEXT, 0,
                                (LPARAM)lpszHold) == LB_ERR ){
            //ErrorMsg(TEXT("Rename: Add Source String failure."),DISP);
            return(1);
        }
         // Set deafult Data Base Name
         lstrcpy (lpszHold,"SMS");

         SendDlgItemMessage( hDlg, IDC_DBNAME, MAX_NAME,
                            (WPARAM)MAX_NAME, (LPARAM)0);

        if( SendDlgItemMessage( hDlg, IDC_DBNAME ,WM_SETTEXT, 0,
                                (LPARAM)lpszHold) == LB_ERR ){
            //ErrorMsg(TEXT("Rename: Add Source String failure."),DISP);
            return(1);
        }
        //Set Deafult password length
         SendDlgItemMessage( hDlg, IDC_PASSWORD, MAX_NAME,
                            (WPARAM)MAX_NAME, (LPARAM)0);

        return(1);
      }
      case WM_COMMAND:{
        switch(LOWORD(wParam)){
            case IDOK:{

                if( SendDlgItemMessage( hDlg, IDC_SERVERNAME, WM_GETTEXT,
                                        MAX_NAME,
                                        (LPARAM)lpszHold) == LB_ERR ){
                    //ErrorMsg(TEXT("Rename: Get Source String failure."),DISP);
                    EndDialog(hDlg, wParam);
                    return(1);
                }
                lstrcpy(dbLoginInfo.ServerName,lpszHold);
                if( SendDlgItemMessage( hDlg, IDC_LOGINID, WM_GETTEXT,
                                        MAX_NAME,
                                        (LPARAM)lpszHold) == LB_ERR ){
                    //ErrorMsg(TEXT("Rename: Get Source String failure."),DISP);
                    EndDialog(hDlg, wParam);
                    return(1);
                }
                lstrcpy(dbLoginInfo.LoginId,lpszHold);
                if( SendDlgItemMessage( hDlg, IDC_DBNAME, WM_GETTEXT,
                                        MAX_NAME,
                                        (LPARAM)lpszHold) == LB_ERR ){
                    //ErrorMsg(TEXT("Rename: Get Source String failure."),DISP);
                    EndDialog(hDlg, wParam);
                    return(1);
                }
                lstrcpy(dbLoginInfo.DBName,lpszHold);
                if( SendDlgItemMessage( hDlg, IDC_PASSWORD, WM_GETTEXT,
                                        MAX_NAME,
                                        (LPARAM)lpszHold) == LB_ERR ){
                    //ErrorMsg(TEXT("Rename: Get Source String failure."),DISP);
                    EndDialog(hDlg, wParam);
                    return(1);
                }
                lstrcpy(dbLoginInfo.Password,lpszHold);

                if ( (dbLoginInfo.DropOnly = SendDlgItemMessage( hDlg, IDC_DROPONLY, BM_GETCHECK,
                                        MAX_NAME,
                                        (LPARAM)0)) == LB_ERR ){
                    //ErrorMsg(TEXT("Rename: Get Source String failure."),DISP);
                    EndDialog(hDlg, wParam);
                    return(1);
                }
                CurWait = LoadCursor(NULL, IDC_WAIT);
                CurArrow = SetCursor(CurWait);
                if ( SetupDbConnection() == FAIL){
                    SetCursor(CurArrow);
                 break;
                 }
              SetCursor(CurArrow);
            }
            case IDCANCEL:{

                EndDialog(hDlg, wParam);
                return(1);
            }
        }
        return(1);
      } // WM_COMMAND
    }

    return(0);
}

/*********************************************************************
* Connect to the DataBase with Indo supplied                         *
**********************************************************************/

int SetupDbConnection()
{
    DBPROCESS *dbproc;      // allocate a DB-LIB process structure
    DBPROCESS *dbprocView;  // Allocate a proc to create the Views
    LOGINREC  *login;       // allocate a DB-LIB login structure
    static HANDLE hLib = NULL;
    PFNDLL GenViews = NULL;
    char CreateGroupName[MAX_COLUMN_NAME];
    int RetCode;

    CreateGroupName[0] = '\0';

    if (dbinit() == (char *)NULL)
    {
        ErrorMsg(IDS_ERR_COM_NOT_LOADED, DISP);
        return(1);
    }

    // Install the user-supplied error-handling and message-handling
    // routines. They are defined at the bottom of this source file.

    dberrhandle((void *)err_handler);
    dbmsghandle((void *)err_handler);

    login = dblogin();                   // get login record from DB-LIB
    DBSETLUSER (login, (char *)dbLoginInfo.LoginId); // set the username
    DBSETLAPP (login, (char *)"smsview");              // set the application name
    DBSETLPWD (login, (char *)dbLoginInfo.Password); // set the SQL Server password

    // Now attempt to create and initialize a DBPROCESS structure
    if ((dbproc = dbopen (login, dbLoginInfo.ServerName)) == NULL)
        return (FAIL);

    // and another one for The Create View Process
    if ((dbprocView = dbopen (login, dbLoginInfo.ServerName)) == NULL)
        return (FAIL);


    if ( dbuse (dbproc, dbLoginInfo.DBName) == FAIL) {     // use the "SMS" database
        dbexit();
      return(FAIL);
    }
    if ( dbuse (dbprocView,dbLoginInfo.DBName) == FAIL) {
        dbexit();
      return(FAIL);
    }

    if (!(hLib = LoadLibrary ("VIEWDLL.DLL")))
            ErrorMsg(IDS_ERR_LOAD_VIEWDLL, DISP);
    else {
       GenViews = (PFNDLL) GetProcAddress (hLib,"GenViews");
       RetCode = (GenViews)(dbproc,dbprocView,CreateGroupName,dbLoginInfo.DropOnly,CmdComplete);
       GenResults(RetCode);
     }
    // Close the connection and exit
    dbexit();

   return(1);
  }
//GenResults

void GenResults(int RetCode)
{
    char szMsg[MAX_PATH];
    char szMsgTitle[32];

    LoadString(hInst, IDS_MSC_CREATE_VIEWS, szMsgTitle, 32);

    if (RetCode == SUCCEED) {
        if ( !dbLoginInfo.DropOnly) {
            LoadString(hInst, IDS_MSG_CREATE_VIEW, szMsg, MAX_PATH);
        }
        else {
            LoadString(hInst, IDS_MSG_DROP_VIEW, szMsg, MAX_PATH);
        }
    }
    else {
        if ( !dbLoginInfo.DropOnly) {
            LoadString(hInst, IDS_ERR_CREATE_VIEW, szMsg, MAX_PATH);
        }
        else {
            LoadString(hInst, IDS_ERR_DROP_VIEW, szMsg, MAX_PATH);
        }
    }

    MessageBox(NULL, szMsg, szMsgTitle, MB_ICONINFORMATION );

}






//ErrorMsg
void ErrorMsg(int iString, int Disp)
{
#if 0
  static HANDLE hEventLog = NULL;
  char *pErrorStrings[1];

  pErrorStrings[0] = errorString;

  if (hEventLog == (HANDLE) NULL)
     hEventLog = RegisterEventSource((HANDLE)NULL,"SMS View");


  if (! CmdComplete && Disp)  // is it run with command line parameters
   MessageBox( NULL, errorString, "Data Base Error", MB_ICONSTOP );

  if ( hEventLog != NULL)
   ReportEvent(hEventLog, EVENTLOG_INFORMATION_TYPE, (WORD)0, (DWORD) 0, NULL
   ,1,0, pErrorStrings, NULL);
#endif

    char    szString[MAX_PATH];
    char    szMsgTitle[32];

    if (Disp == DISP) {
        LoadString(hInst, iString, szString, MAX_PATH);
        LoadString(hInst, IDS_MSC_DBERROR, szMsgTitle, 32);
        MessageBox(NULL, szString, szMsgTitle, MB_ICONSTOP);
    }
  }



/****************************************************************************

    FUNCTION: SqlTestInit(HANDLE)

    PURPOSE: Initializes window data and registers window class

    COMMENTS:

    Sets up a structure to register the window class.  Structure includes
    such information as what function will process messages, what cursor
    and icon to use, etc.

****************************************************************************/

BOOL SqlTestInit(hInstance)
HANDLE hInstance;                  /* current instance       */
{
    HANDLE hMemory;                /* handle to allocated memory */
    PWNDCLASS pWndClass;               /* structure pointer      */
    BOOL bSuccess;                 /* RegisterClass() result     */

    hMemory = LocalAlloc(LPTR, sizeof(WNDCLASS));
    pWndClass = (PWNDCLASS)hMemory;

    pWndClass->style = 0; /*CS_HREDRAW | CS_VREDRAW; */
    pWndClass->lpfnWndProc = (WNDPROC)NULL;
    pWndClass->hInstance = hInstance;
    pWndClass->hIcon = LoadIcon(hInstance,MAKEINTRESOURCE( IDI_SMSVIEW));
    pWndClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    pWndClass->hbrBackground = GetStockObject(WHITE_BRUSH);
    pWndClass->lpszMenuName = (LPSTR)"SMS Views";
    pWndClass->lpszClassName = (LPSTR)"SMS Views";

    bSuccess = RegisterClass(pWndClass);

    LocalFree(hMemory);                 /* Returns it to NT */
    return (bSuccess);       /* Returns result of registering the window */
}

//
int err_handler(DBPROCESS * dbproc, int severity, int dberr, int oserr, char * dberrstr, char * oserrstr)
{
    char    szString[512];
    char    szMsgTitle[32];
    int     iString;

    // Ignore any 'Changed context' errors. (#5701 dec)

    if (severity == 0x00001645) {
        return 0;
    }

    LoadString(hInst, IDS_ERR_SQL_ERROR, szString, MAX_PATH);
    LoadString(hInst, IDS_MSC_DBERROR, szMsgTitle, 32);

    iString = sizeof(szString) - strlen(szString);
    if (dberrstr != NULL) {
        strncpy(szString, dberrstr, iString);
    }
    else if (oserr != DBNOERR && oserrstr != NULL) {
        strncpy(szString, oserrstr, iString);
    }
    szString[sizeof(szString)-1] = 0;

    if (strstr(szString, "General SQL Server") == NULL) {
        MessageBox(NULL, szString, szMsgTitle, MB_ICONSTOP);
    }

    return(INT_CANCEL);
}

