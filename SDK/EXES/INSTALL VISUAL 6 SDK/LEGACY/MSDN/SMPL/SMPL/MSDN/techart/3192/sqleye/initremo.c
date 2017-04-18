//****************************** Function Header ******************************
//
// Function : InitRemote
//
// Description: Connect to remote SQL Server and create an MDI child window
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define DBNTWIN32

// Standard compiler and SQL header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>
#include    <stdio.h>
#include    <stdlib.h>

// Application specific header files
#include    "sqleye.h"
#include    "initremo.h"
#include    "sqlcbs.h"
#include    "rowstuff.h"

extern HWND ghwndMain;
extern LOG  Log;
extern BOOL bAutoTile;

// Used to make sure Newsrvproc is safe
HANDLE    InitRemote_SEM;

// Declare the handle to protect the linked list of remote structures
extern HANDLE    LinkedList_SEM;

DBCHAR   *remote_server = NULL;
SRV_PROC *Newsrvproc;

// The handler used while the server is paused to not allow users to connect
int DoNotInitRemote(SRV_PROC  *srvproc)
{
    // We'll still let the sa log in just in case they want to shutdown the server
    if ( strcmp( srv_pfield(srvproc,SRV_USER,NULL),"sa") == 0 )
        return InitRemote(srvproc);
    else
        // Send a message to the client that
        // the gateway is paused.
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            (DBINT)REMOTE_FAIL,
            (DBTINYINT)14,
            (DBTINYINT)1,
            NULL,
            0,
            0,
            "Login Failed - SQLEYE : Gateway is paused. All new logins have been disabled.",
            SRV_NULLTERM);
    return(SRV_DISCONNECT);
}

// The normal handler to allow users to connect
int InitRemote(SRV_PROC  *srvproc)
{
    char          szBuf[250];
    REMOTE_DBMS  *remote;
    char         *plog_buffer;
    DBCHAR        TempServer[MAXSVR+1],
                  TempUser[MAXUSR+1+MAXSVR+1],
                  TempAppName[MAXAPPNAME+1],
                  TempLanguage[MAXLANGUAGE+1],
                  TempPassword[MAXPASSWORD+1],
                  TempHostName[MAXHOSTNAME+1],
                  *charpointer;
    HANDLE        hMDI;
    PCLIENTINFO   pInfo;
    char          szTitle[MAXUSR + MAXAPPNAME + MAXPASSWORD + 15];
    HWND          hwndQuery;

    // First let's work out what we're trying to achieve

    // Set the initial server value
    strncpy(TempServer,(const char *)remote_server,MAXSVR);
    strcat(TempServer,"\0");

    // Set the user name, password, and application name for the remote DBMS.
    // We'll parse the userid for a @ and if it has one we'll
    // use a different server <userid>@<server name> . 
    strncpy(TempUser,srv_pfield(srvproc, SRV_USER, (int *)NULL),MAXUSR+1+MAXSVR);
    strcat(TempUser,"\0");
    charpointer = TempUser;
    while ( *charpointer && *charpointer != '@')
        charpointer++;
    if (*charpointer == '@')
        {
        *charpointer = '\0';
        strncpy(TempServer,++charpointer,MAXSVR);
        strcat(TempServer,"\0");
        }

    // Note: if the fields contain data of length 30 srv_pfield 
    // returns a string that is NOT null terminated
    // This next section is in order to work around it.
    strncpy(TempPassword,srv_pfield(srvproc, SRV_PWD, (int *)NULL),MAXPASSWORD);
    strcat(TempPassword,"\0");
    strncpy(TempAppName,srv_pfield(srvproc, SRV_APPLNAME, (int *)NULL),MAXAPPNAME);
    strcat(TempAppName,"\0");
    strncpy(TempLanguage,srv_pfield(srvproc, SRV_NATLANG, (int *)NULL),MAXLANGUAGE);
    strcat(TempLanguage,"\0");
    strncpy(TempHostName,srv_pfield(srvproc, SRV_HOST, (int *)NULL),MAXHOSTNAME);
    strcat(TempHostName,"\0");

    
    // Allocate a REMOTE_DBMS information structure.
    remote = (REMOTE_DBMS *)srv_alloc((DBINT)sizeof(*remote));

    // Set up the remote DBMS structure.
    if (remote == NULL)
    {
        // Send a message to the client that
        // the remote connection failed.
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            (DBINT)REMOTE_FAIL,
            (DBTINYINT)14,
            (DBTINYINT)1,
            NULL,
            0,
            0,
            "Login Failed - SQLEYE : Unable to allocate memory for REMOTE_DBMS structure. Disconnecting.",
            SRV_NULLTERM);
        // Nothing for exit remo to clean up
        srv_setuserdata(srvproc, (BYTE *)NULL);
        return(SRV_DISCONNECT);
    } 
    // Connection to the remote DBMS successful.  Save
    // remote data structure in the "srvproc" so it will be
    // available to the other handlers. We'll also map the remote
    // DBMS connection to our "srvproc".
    srv_setuserdata(srvproc, (BYTE *)remote);

    // Set "bulk insert" mode flag to false.
    remote->bulk_mode = FALSE;
    // Set "STATISTICS IO" and "STATISTICS TIME" flags to false.
    // We may switch this on to collect stats but we need to have a flag
    // to tell us whether or not to pass this back to the client application
    remote->bStatisticsIO = FALSE;
    remote->bStatisticsTime = FALSE;
    // The next two tell us the state of the connection so we can decide what
    // action to take e.g. if the user wants to turn one of them on but SQLEYE
    // has already turned it on then we don't need to.
    // Also don't allow the user to turn it off if SQLEYE still needs it.
    remote->bStatisticsIO_On = FALSE;
    remote->bStatisticsTime_On = FALSE;
    // Set the dblib stuff to NULL
    remote->login = NULL;
    remote->dbproc = (DBPROCESS *)NULL;
    // Make sure we can get the svr_proc back from the remote_dbms structure
    remote->srvproc = srvproc;
    // No window yet
    remote->hMDI = NULL;

    // Now ready to Add the srvproc to the start off the list
    // as the remote structure is in consistant state
    {
        LONG OldHead;
        // CRITICAL SECTION
        WaitForSingleObject(LinkedList_SEM, (DWORD)SRV_INDEFINITE_WAIT);
        OldHead = GetWindowLong(ghwndMain, GWL_USERDATA);
        SetWindowLong(ghwndMain, GWL_USERDATA, (LONG)remote);
        remote->Next = (void *)OldHead;
        // END OF CRITICAL SECTION
        ReleaseSemaphore(LinkedList_SEM, 1, NULL);
    }

    // We might as well create the window now.
    // The earlier we create it the more responsive we look.
    // If the connection later fails then Exitremo will clear up
    // for us.
    // Create MDI window for logging
    if (Log.MDI)
    {
        hMDI = LocalAlloc(LHND, (WORD) sizeof(CLIENTINFO));
        if (!hMDI)
        {
            // Couldn't allocate the memory for the info
            ERRBOX("Failed to Allocate CLient Info structure");
            return(SRV_DISCONNECT);
        } else {
            if ((pInfo = (PCLIENTINFO)LocalLock(hMDI))==NULL)
            {
                 ERRBOX("Failed to Lock hMDI! Can't initialise new session.");
                 // Clean up
                 LocalFree(hMDI);
                 return(SRV_DISCONNECT);
             } else {
                 pInfo->iIconType = IDM_INACTIVE_ICON;
                 // Build window title
                 sprintf(szTitle, "%s - %s - %s", 
                     TempUser,
                     // You may or may not want to display the password
                     // If so you need to add an extra ' - %s' to the above
                     // Also watch out for the size of szTitle
                     // TempPassword,
                     TempAppName,
                     srv_pfield(srvproc, SRV_SPID    ,(int *)NULL));

                 LocalUnlock(hMDI);
                 if ( (hwndQuery=CreateMDI(
                     hMDI, 
                     szTitle,
                     TempAppName)
                     ))
                 {
                     remote->hMDI = hMDI;
                     // display some info in the window
                     sprintf(szBuf, "Client ID: %s", srv_pfield(srvproc, SRV_SPID, (int *)NULL));
                     AddRow(hMDI, szBuf,colorBlue);
                     sprintf(szBuf, "User name: %s", TempUser);
                     AddRow(hMDI, szBuf, colorBlue);
                 } else {
                      ERRBOX("Failed to Create window! Can't initialise new session.");
                      // Clean up
                      LocalFree(hMDI);
                      return(SRV_DISCONNECT);
                 }
            }
        }
    }

    // NOW LET'S CONNECT and 
    // keep the CRITICAL SECTION AS SHORT AS POSSIBLE

    // Set Newsrvproc.  This is used if we get an error on
    // the open from DBLIB.  Since there isn't a dbproc,
    // it is clear which srvproc to send the msg back on when the
    // DBLIB error-handler gets called.
    //
    // First lock out any other threads trying to connect using
    // this same function or we'll get problems with Newsrvproc.
    // CRITICAL SECTION
    WaitForSingleObject(InitRemote_SEM, (DWORD)SRV_INDEFINITE_WAIT);
    Newsrvproc = srvproc;

    // Allocate the LOGINREC structure used to make connections to the
    // remote server.
    remote->login = dblogin();

    if (remote->login == NULL)
    {
        // Send a message to the client that the
        // remote connection failed.
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            (DBINT)REMOTE_FAIL,
            (DBTINYINT)14,
            (DBTINYINT)1,
            NULL,
            0,
            0,
            "Login Failed - SQLEYE : dblogin() failed. Disconnecting.",
            SRV_NULLTERM);

        // Now allow other threads to enter this function.
        // END OF CRITICAL SECTION (conditional)
        ReleaseSemaphore(InitRemote_SEM, 1, NULL);
        return(SRV_DISCONNECT);
    }

    // Uncomment this section if you don't want applications
    // to connect with the bulk copy flag set.
    // Beware this may also stop apps like SQLADMIN.EXE
    // and SQLOBJ.EXE from connecting
    /*
    if (strcmp(srv_pfield(srvproc, SRV_BCPFLAG, (int *)NULL), "TRUE") == 0)
    {
        // Send a message to the client that the
        // remote connection failed.
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            (DBINT)REMOTE_FAIL,
            (DBTINYINT)14,
            (DBTINYINT)1,
            NULL,
            0,
            0,
            "Login Failed - SQLEYE : Doesn't support Bulk Copy operations. Disconnecting.",
            SRV_NULLTERM);
        // Now allow other threads to enter this function.
        // END OF CRITICAL SECTION (conditional)
        ReleaseSemaphore(InitRemote_SEM, 1, NULL);
        return(SRV_DISCONNECT);
    }
    */

    // See if client has set Bulk Copy flag
    if (strcmp(srv_pfield(srvproc, SRV_BCPFLAG, (int *)NULL), "TRUE") == 0)
        BCP_SETL(remote->login, TRUE);
    else
        BCP_SETL(remote->login, FALSE);

    // Set the connection info
    DBSETLUSER(remote->login,    TempUser );
    DBSETLPWD(remote->login,     TempPassword);
    DBSETLAPP(remote->login,     TempAppName);
    DBSETLNATLANG(remote->login, TempLanguage);
    DBSETLHOST(remote->login,    TempHostName);

    // Try to open a connection to the remote DBMS.
    if ((remote->dbproc = dbopen(remote->login, TempServer))
        == (DBPROCESS *)NULL)
    {
        // Send a message to the client that the remote
        // connection failed.
        // They will already get a message from the error 
        // handler but this extra one lets them know
        // that the problem is between SQLEYE and the
        // server. Rather than between their app and SQLEYE
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            (DBINT)REMOTE_FAIL,
            (DBTINYINT)14,
            (DBTINYINT)1,
            NULL,
            0,
            0,
            "Login Failed - SQLEYE : dbopen to remote server failed.",
            SRV_NULLTERM);

        // Now allow other threads to enter this function.
        // END OF CRITICAL SECTION (conditional)
        ReleaseSemaphore(InitRemote_SEM, 1, NULL);
        return(SRV_DISCONNECT);
    }

    dbsetuserdata(remote->dbproc, (SRV_PROC *)srvproc);

    // Now allow other threads to enter this function.
    // We've finished with Newsrvproc
    // END OF CRITICAL SECTION
    ReleaseSemaphore(InitRemote_SEM, 1, NULL);

    // Now set the icon to inactive
    if (Log.MDI) ChangeIcon(remote->hMDI, IDM_INACTIVE_ICON);

    if (Log.FILE_Connections)
    {
        // Display connect info
        plog_buffer = (char *)malloc(
            strlen("=>Connect: Client ID: , User name: , Application program name: ") +
            strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) +
            strlen(TempUser) +
            strlen(TempAppName) + 1);
        sprintf(plog_buffer, "=>Connect: Client ID: %s, User name: %s, Application program name: %s",
            srv_pfield(srvproc, SRV_SPID, (int *)NULL),
            TempUser,
            TempAppName);
        srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
        free(plog_buffer);
    }

    // Tile if necessary
    if (bAutoTile) PostMessage(ghwndMain,WM_COMMAND,IDM_TILE,0L);

    return(SRV_CONTINUE);
}
