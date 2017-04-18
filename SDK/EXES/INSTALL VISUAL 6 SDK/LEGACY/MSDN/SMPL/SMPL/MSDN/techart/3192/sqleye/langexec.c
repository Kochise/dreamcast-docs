//****************************** Function Header ******************************
//
// Function : LangExecute
//
// Description: Sends a Language request to the server
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define DBNTWIN32

// standard compiler/sql server supplied header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>
#include    <stdio.h>
#include    <stdlib.h>

// Application specific header files
#include    "sqleye.h"
#include    "langexec.h"
#include    "hresults.h"
#include    "rowstuff.h"
#include    "mngeserv.h"
#include    "sqlcbs.h"
#include    "stats.h"

extern LOG Log;
extern HMENU hMenu;
extern RETCODE SQLAPI dbbcmd(DBPROCESS *, CHAR *, ...);


#pragma check_stack( off )  // turn off stack checking

int LangExecute(SRV_PROC  *srvproc)
{
    REMOTE_DBMS *rmt_dbms;
    DBPROCESS   *rmtproc;
    DBCHAR      *query;
    long        query_len;
    int         status = SUCCEED, iOldIconType;

    // Get the remote dbms pointer we saved in the srvproc via
    // srv_setuserdata.
    rmt_dbms = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    // Get the pointer to the remote DBPROCESS
    rmtproc = rmt_dbms->dbproc;

    // Get the pointer to the client language request command buffer.
    query = srv_langptr(srvproc);

    // Make sure the statistics are on/off if necessary
    status = SwitchStats(rmt_dbms,rmtproc,query);

    // store the old icon message, then use the IN icon
    if (Log.MDI) iOldIconType = ChangeIcon(rmt_dbms->hMDI,   IDM_IN_ICON);

    // Check for SQLEYE shutdown by request
    if ( strcmp( srv_pfield(srvproc,SRV_USER,NULL),"sa") == 0 )
    {
        // SHUTDOWN
        if ( strcmp( query,"shutdown sqleye") == 0 ) 
        {
            // Switch off the menu options
            ModifyMenu(hMenu,IDM_INIT_ODS          ,MF_GRAYED,IDM_INIT_ODS,
                (LPSTR)"THE GATEWAY IS CURRENTLY IN THE PROCESS OF SHUTING DOWN");
            ModifyMenu(hMenu,IDM_PAUSE_SERVER  ,MF_GRAYED,IDM_PAUSE_SERVER,
             (LPSTR)"&Pause the gateway (No new connections)");
            ModifyMenu(hMenu,IDM_RESTART_SERVER,MF_GRAYED,IDM_RESTART_SERVER,
                (LPSTR)"&Restart the gateway (Allow new connections)");
            // use the original icon
            if (Log.MDI)     ChangeIcon(rmt_dbms->hMDI,   iOldIconType);
            srv_sendmsg(srvproc,
                SRV_MSG_ERROR,
                (DBINT)REMOTE_MSG,
                (DBTINYINT)0,
                (DBTINYINT)0,
                NULL,
                0,
                0,
                "SQLEYE is Shutting down by your request and your connection has been disconnected",
                SRV_NULLTERM);
            // Tell the client we have finished processing
            srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0, 0);
            srv_event(srvproc,SRV_STOP,NULL);
            return (SRV_DISCONNECT);
        }

        // PAUSE
        if ( strcmp( query,"pause sqleye") == 0 ) 
        {
            // Switch off the menu options
            ModifyMenu(hMenu,IDM_INIT_ODS      ,MF_GRAYED ,IDM_INIT_ODS,
                (LPSTR)"&Start the gateway");
            ModifyMenu(hMenu,IDM_PAUSE_SERVER  ,MF_GRAYED ,IDM_PAUSE_SERVER,
                (LPSTR)"&Pause the gateway (No new connections)");
            ModifyMenu(hMenu,IDM_RESTART_SERVER,MF_ENABLED,IDM_RESTART_SERVER,
                (LPSTR)"&Restart the gateway (Allow new connections)");
            // use the original icon
            if (Log.MDI)     ChangeIcon(rmt_dbms->hMDI,   iOldIconType);
            srv_sendmsg(srvproc,
                SRV_MSG_ERROR,
                (DBINT)REMOTE_MSG,
                (DBTINYINT)0,
                (DBTINYINT)0,
                NULL,
                0,
                0,
                "SQLEYE has been paused",
                SRV_NULLTERM);
            // Tell the client we have finished processing
            srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0, 0);
            ServerSleep(NULL);
            return (SRV_CONTINUE);
        }

        // RESTART
        if ( strcmp( query,"restart sqleye") == 0 ) 
        {
            // Switch off the menu options
            ModifyMenu(hMenu,IDM_INIT_ODS      ,MF_GRAYED ,IDM_INIT_ODS,
                (LPSTR)"&Start the gateway");
            ModifyMenu(hMenu,IDM_PAUSE_SERVER  ,MF_ENABLED,IDM_PAUSE_SERVER,
                (LPSTR)"&Pause the gateway (No new connections)");
            ModifyMenu(hMenu,IDM_RESTART_SERVER,MF_GRAYED ,IDM_RESTART_SERVER,
                (LPSTR)"&Restart the gateway (Allow new connections)");
            // use the original icon
            if (Log.MDI)     ChangeIcon(rmt_dbms->hMDI,   iOldIconType);
            srv_sendmsg(srvproc,
                SRV_MSG_ERROR,
                (DBINT)REMOTE_MSG,
                (DBTINYINT)0,
                (DBTINYINT)0,
                NULL,
                0,
                0,
                "SQLEYE has been restarted",
                SRV_NULLTERM);
            // Tell the client we have finished processing
            srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0, 0);
            ServerRestart(NULL);
            return (SRV_CONTINUE);
        }
    }

    // See if the previous command was a "bulk insert" command
    if (status == SUCCEED && rmt_dbms->bulk_mode)
    {
        // Get length of the SQL command.
        query_len = srv_langlen(srvproc);

        // If length of data is zero, then send a zero length buffer
        // to the destination SQL Server.  This is required in order to
        // signal the SQL Server that no more data follows.
        if (query_len == -1L)
            query_len = 0L;

        // Place buffer into target SQL server's buffer.
        status = dbbcmd(rmtproc, query, query_len);
        query = "RAW BCP DATA (Can't be displayed)";

        rmt_dbms->bulk_mode = FALSE;
    } else {
        // Let's check for "insert bulk" request
        if (srv_langlen(srvproc) > (sizeof(BULK_CMD) - 1))
            if (strnicmp(query, BULK_CMD, (sizeof(BULK_CMD) - 1)) == 0)
            rmt_dbms->bulk_mode = TRUE;

        // Place buffer into target SQL server's buffer.
        status = dbcmd(rmtproc, query);
    }

    // Log info
    if (Log.MDI_Query)
    {
        AddRow(rmt_dbms->hMDI, " ", colorBlack);
        AddRow(rmt_dbms->hMDI, "Query: ", colorBlue);
        AddRow(rmt_dbms->hMDI, query, colorBlack);
    }

    if (Log.FILE_Query)
    {
        char *pszAll=NULL;
        // Allocate space for the whole lot
        pszAll = malloc( strlen(query) + 31 );
        // Make the whole lot
        sprintf(pszAll,
            "==> Query: Client Id: %s - %s",
            srv_pfield(srvproc, SRV_SPID, (int *)NULL),
            query);
        // Write it to disk
        srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, pszAll, SRV_NULLTERM);
        // free the memory
        free(pszAll);
    }

    // Build the scripts
    if (Log.Build_Scripts)
    {
        FILE *fOutput;
        char szFileName[15];
        char * pszMsg;
        sprintf(szFileName,"%s.sql",srv_pfield(srvproc,SRV_SPID,NULL));
        if (fOutput = fopen(szFileName,"a"))
        {
            fprintf(fOutput,"%s \ngo\n",query);
            fclose(fOutput);
        }  else {
            pszMsg = (char *)malloc(
                strlen("Unable to open file ") +
                strlen(szFileName) + 1);
            sprintf(pszMsg,"Unable to open file %s",szFileName);
            srv_log(SRV_GETSERVER((SRV_PROC *)dbgetuserdata(rmtproc)), Log.FILE_Timing, pszMsg, SRV_NULLTERM);
            free(pszMsg);
        }

    }

    // If previous DBLIB call successful, send command buffer to SQL Server.
    if (status == SUCCEED)
    {
        
        status = dbsqlsend(rmtproc);
        if (status)
        {
            // let's open the eyes
            if (Log.MDI) ChangeIcon(rmt_dbms->hMDI,   IDM_ACTIVE_ICON);
            status = dbsqlok(rmtproc);
        }
    }

    // if the user hasn't issued a dbcancel and the call succeded
    if (!SRV_GOT_ATTENTION(srvproc) && (status == SUCCEED))
    {
        // Get the remote dbms results and pass them back to the client
        HandleResults(rmtproc, srvproc);
    } else {
        // If an attention event was issued or the dbsqlexec failed,
        // acknowledge with senddone.
        if (DBDEAD(rmtproc))
        {
            // Let them know it failed
            // they're one loop behind 
            srv_sendmsg(
                srvproc,
                SRV_MSG_ERROR,
                (DBINT)10025,
                (DBTINYINT)9,
                (DBTINYINT)0,
                NULL,
                0,
                0,
                "Possible network error: Write to SQL Server failed.",
                SRV_NULLTERM);
            // try this
            dbclose(rmtproc);
            rmt_dbms->dbproc = NULL;
            srv_senddone(srvproc, SRV_DONE_ERROR, (DBUSMALLINT)0, (DBINT)0);
            srv_event(srvproc, SRV_DISCONNECT, NULL);
            return(SRV_DISCONNECT);
        } else {
            dbcancel(rmtproc);
            srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0, (DBINT)0);
        }
    }
    // use the original icon
    if (Log.MDI)     ChangeIcon(rmt_dbms->hMDI,   iOldIconType);

    return(SRV_CONTINUE);
}

#pragma check_stack()   // set stack checking to its default setting

