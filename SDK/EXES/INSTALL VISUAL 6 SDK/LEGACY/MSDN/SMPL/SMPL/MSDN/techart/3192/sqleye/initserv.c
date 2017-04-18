//****************************** Function Header ******************************
//
// Function : InitServer
//
// Description: Sets up call-back functions etc.
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define DBNTWIN32

// Compiler and SQL header files
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    "sqleye.h"
#include    "initserv.h"

// Application specific header files
#include    "rpcexec.h"
#include    "exitremo.h"
#include    "langexec.h"
#include    "rowstuff.h"
#include    "initremo.h"
#include    "mngeserv.h"
#include    "stats.h"

// Forward declarations for the dblib error/msg handlers
int RemoteMsgs(DBPROCESS  *,DBINT,INT,INT,char *);
int RemoteErr(DBPROCESS *,int,int,int,char *,char *);

// Forward declaration for the Attention handler 
// Used if the user isues a dbcancel
int attn_handler(SRV_PROC *);

// The remote server name of this gateway
extern DBCHAR   *remote_server;

// A global for the client trying to connect which we protect
// by using the following semaphore
extern SRV_PROC *Newsrvproc;
extern HANDLE    InitRemote_SEM;

// We the next semaphore to ensure that the MDI windows are
// initialised before we allow the initremo to continue
extern HANDLE    InitMDI_SEM;

// declare the log
extern LOG Log;

// declare the main window handle
extern HWND ghwndMain;

#pragma check_stack( off )  // turn off stack checking


int InitServer(SRV_SERVER *server)
{
    char *plog_buffer;

    // When we get a connection request from a client, we want to
    // call "InitRemote()" to make a connection to the remote
    // server.
    srv_handle(server, (DBINT)SRV_CONNECT, InitRemote);

    // When the client issues a language request, call
    // "LangExecute()" to send the SQL statement to the remote DBMS.
    srv_handle(server, (DBINT)SRV_LANGUAGE, LangExecute);

    // When the client issues an RSP, call "RPCExecute()"
    // to send the RSP to the remote DBMS (the SQL Server).
    srv_handle(server, (DBINT)SRV_RPC, RPCExecute);

    // When a disconnect request is issued, call "ExitRemote()"
    // to close the connection to the remote DBMS.
    srv_handle(server, (DBINT)SRV_DISCONNECT, ExitRemote);

    // Install the handler that will be called when the
    // gateway receives an attention from one of its
    // clients. An attention gets received anytime a client
    // calls dbcancel().
    srv_handle(server, (DBINT)SRV_ATTENTION, attn_handler);

    // Now install the handlers for the control services
    // these are here ready for when we make SQLEYE a service
    srv_handle(server, (DBINT)SRV_SLEEP  , ServerSleep);
    srv_handle(server, (DBINT)SRV_RESTART, ServerRestart);

    // Now we'll install the message and error handlers for any
    // messages from the remote DBMS.
    dberrhandle(RemoteErr);
    dbmsghandle(RemoteMsgs);

    // Create semaphore objects

    // This one used for a critical section to protect Newsrvproc
    InitRemote_SEM  = CreateSemaphore(NULL, 1, 1, NULL);
    // This one used by CreateMDI to wait for WM_CREATE to complete
    InitMDI_SEM     = CreateSemaphore(NULL, 1, 1, NULL);

    // Log Server information to log file
    plog_buffer = (char *)malloc(
        strlen("SQLEYE started... Registry Key = , Remote Server = , Client Connections: ") +
        strlen(srv_sfield(server,SRV_SERVERNAME, (int *)NULL)) +
        strlen(remote_server) +
        strlen(srv_sfield(server, SRV_CONNECTIONS, (int *)NULL)) +
        1);
    sprintf(plog_buffer,
        "SQLEYE started... Registry Key = %s, Remote Server = %s, Client Connections: %s",
        srv_sfield(server,SRV_SERVERNAME, (int *)NULL),
        remote_server,
        srv_sfield(server, SRV_CONNECTIONS, (int *)NULL));
    srv_log(server, Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
    free(plog_buffer);

    return(SRV_CONTINUE);
}

//****************************** Function Header ******************************
//
// Function : ChkErr
//
// Description: Checks for errors!
//
//*****************************************************************************
int ChkErr(SRV_SERVER *server,
           SRV_PROC   *srvproc,
           int         errornum,
           BYTE        severity,
           BYTE        state,
           int         oserrnum,
           DBCHAR     *errtext,
           int         errtextlen,
           DBCHAR     *oserrtext,
           int         oserrtextlen)
{
    char * plog_buffer;

    // Operating system error? Record in the log file
    if (oserrnum != SRV_ENO_OS_ERR && oserrtextlen > 0)
    {
        plog_buffer = (char *)malloc(
            strlen("SERVER OS ERROR: : .") +
            strlen(oserrtext) +
            11);
        sprintf(plog_buffer, "SERVER OS ERROR: %d: %s.", oserrnum, oserrtext);
        srv_log(server, Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
        free(plog_buffer);
    }

    // Is this a fatal error for the gateway?
    if (severity >= SRV_FATAL_SERVER )
    {        
        plog_buffer = (char *)malloc(
            strlen("SERVER: FATAL SERVER ERROR: errornum = , severity = , state = : .") +
            strlen(errtext) +
            31);
        sprintf(plog_buffer,
            "SERVER: FATAL SERVER ERROR: errornum = %d, severity = %d, state = %d: %s.",
            errornum,
            severity,
            state,
            errtext);
        srv_log(server, Log.FILE_Timing, plog_buffer, SRV_NULLTERM);

        MessageBox(ghwndMain,
            plog_buffer,
            "Error from Server Process",
            MB_ICONSTOP | MB_OK | MB_TASKMODAL);

        free(plog_buffer);

        return(SRV_STOP);
    } else {
        // Did the "srvproc" get a fatal error? 
        if (severity >= SRV_FATAL_PROCESS)
        {
            plog_buffer = (char *)malloc(
                strlen("SERVER: FATAL CONNECT ERROR: errornum = , severity = , state = : .") +
                strlen(errtext) +
                31);
            sprintf(plog_buffer,
                "SERVER: FATAL CONNECT ERROR: errornum = %d, severity = %d, state = %d: %s.",
                errornum,
                severity,
                state,
                errtext);

            srv_log(server, Log.FILE_Timing, plog_buffer, SRV_NULLTERM);

            free(plog_buffer);

            return(SRV_CANCEL);
        }
    }

    // A non-fatal error or an information message received.
    // We'll pass it through to the client.
    if (srvproc != (SRV_PROC *)NULL && (server != NULL))
        if (severity < 10)
        {   
            // If informational message
            // Want the user to know it's from SQLEYE
            // Otherwise get problems deciding whether the problem
            // is on the gateway or the server
            plog_buffer = (char *)malloc(
                strlen("SQLEYE ODS : ") +
                strlen(errtext) +
                1);
            strcpy(plog_buffer,"SQLEYE ODS : ");
            strcat(plog_buffer,errtext);
            srv_sendmsg(srvproc,
                SRV_MSG_INFO,
                (DBINT)errornum,
                severity,
                0,
                NULL,
                0,
                0,
                plog_buffer,
                SRV_NULLTERM);
            free(plog_buffer);
        } else {
            // Must be an error message
            // Want the user to know it's from SQLEYE
            // Otherwise get problems deciding whether the problem
            // is on the gateway or the server
            plog_buffer = (char *)malloc(
                strlen("SQLEYE ODS : ") +
                strlen(errtext) +
                1);
            strcpy(plog_buffer,"SQLEYE ODS : ");
            strcat(plog_buffer,errtext);
            srv_sendmsg(srvproc,
                SRV_MSG_ERROR,
                (DBINT)errornum,
                severity,
                0,
                NULL,
                0,
                0,
                plog_buffer,
                SRV_NULLTERM);
            free(plog_buffer);
        } else {
            plog_buffer = (char *)malloc(
                strlen("GATEWAY ERROR: errornum = , severity = : ") +
                strlen(errtext) +
                21);
            sprintf(plog_buffer,
                "GATEWAY ERROR: errornum = %d, severity = %d: %s",
                errornum, severity, errtext);

            srv_log(server, Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
            free(plog_buffer);
        }
    return(SRV_CONTINUE);
}

//****************************** Function Header ******************************
//
// Function : RemoteMsgs
//
// Description: Handles messages from remote DBLIB / Remote SQL Server
//
// All of the performacnce
//*****************************************************************************
int RemoteMsgs(DBPROCESS  *dbproc,
               DBINT      msgno,
               INT        msgstate,
               INT        severity,
               char       *msgtext)
{
    REMOTE_DBMS *remote;
    SRV_PROC    *srvproc;
    char        *plog_buffer;

    // If a remote DBMS error was received during the remote
    // open, the dbproc is NULL and a message is sent back on the
    // most recent srvproc.
    if (dbproc == (DBPROCESS *)NULL)
        srvproc = Newsrvproc;
    else
        if ((srvproc = (SRV_PROC *)dbgetuserdata(dbproc)) == NULL)
        // An error was received after the dbproc was assigned, but
        // before we were able to associate our srvproc.
        srvproc = Newsrvproc;

    remote = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    // check for a stats message
    // if FALSE then the client doesn't want the message
    if ( CatchStats(msgno,msgtext,dbproc,remote) == FALSE )
        return(0);

    if (severity < 10)
    {
        // An informational message
        srv_sendmsg(srvproc,
            SRV_MSG_INFO,
            msgno,
            (DBTINYINT)severity,
            (DBTINYINT)msgstate,
            NULL,
            0,
            0,
            msgtext,
            SRV_NULLTERM);
        // Display messages on screen ?
        if (remote && Log.MDI_Message)
        {
            plog_buffer = (char *)malloc(
                strlen("DB-Library Message: ") + 11);
            sprintf(plog_buffer,"DB-Library Message: %d",msgno);
            AddRow(remote->hMDI, plog_buffer, colorRed);
            free(plog_buffer);
            AddRow(remote->hMDI, msgtext, colorBlack);
        }
        // Log the messages ?
        if (Log.FILE_Message)
        {
            plog_buffer = (char *)malloc(
                strlen("DBLIB MSG: Client ID:   ") +
                strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) +
                strlen(msgtext) +
                11);
            sprintf(plog_buffer,
                "DBLIB MSG: Client ID: %s %d %s",
                srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                msgno,
                msgtext);
            srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
            free(plog_buffer);
        }
    } else {
        // must be an error message
        srv_sendmsg(srvproc,
            SRV_MSG_ERROR,
            msgno,
            (DBTINYINT)severity,
            (DBTINYINT)msgstate,
            NULL,
            0,
            0,
            msgtext,
            SRV_NULLTERM);
        // Display erros on screen ?
        if (remote && Log.MDI_Error)
        {
            plog_buffer = (char *)malloc(
                strlen("DB-Library Error: ") + 11);
            sprintf(plog_buffer,"DB-Library Error: %d",msgno);
            AddRow(remote->hMDI, plog_buffer, colorRed);
            free(plog_buffer);
            AddRow(remote->hMDI, msgtext, colorBlack);
        }
        // Log the errors ?
        if (Log.FILE_Error)
        {
            plog_buffer = (char *)malloc(
                strlen("DBLIB ERR: Client ID:   ") +
                strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) +
                strlen(msgtext) +
                11);
            sprintf(plog_buffer,
                "DBLIB ERR: Client ID: %s %d %s",
                srv_pfield(srvproc, SRV_SPID, (int *)NULL),
                msgno,
                msgtext);
            srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
            free(plog_buffer);
        }
    }

    return(0);
}

//****************************** Function Header ******************************
//
// Function : RemoteErr
//
// Description: Handles errors from remote SQL Server
//
//*****************************************************************************
int RemoteErr(DBPROCESS  *dbproc,
              int severity,
              int dberr,
              int oserr,
              char  *dberrstr,
              char  *oserrstr)
{
    REMOTE_DBMS *remote;
    SRV_PROC    *srvproc = (SRV_PROC *)NULL;
    char        *plog_buffer;


    // If we get a DBLIB error 10007
    // ("General SQL Server Error:...") then simply ignore it.  The error
    // message has already been sent to the client.
    if (dberr == 10007)
        return(INT_CANCEL);

    // If the dbprocess is dead then we can't get back any info from the
    // dbgetuser. So there is no way of knowing which connection this is
    // therefore we'll just cancel the operation and have done with it.
    // (The next time they issus a langexec (or an rpc) we'll pick up the
    // fact the the dbproc is dead and kill the session.
    if ( DBDEAD(dbproc) )
        return(INT_CANCEL);
        
    // A remote DBMS error may have been issued during the remote
    // open. In this case, the dbproc will be NULL and a message
    // will be sent on the most recent srvproc.
    if (dbproc == (DBPROCESS *)NULL)
        srvproc = Newsrvproc;
    else
        if ((srvproc = (SRV_PROC *)dbgetuserdata(dbproc)) == NULL)
            // An error was issued after the dbproc was assigned but before
            // we were able to associate our srvproc.
            srvproc = Newsrvproc;

    // Send error message to client.
    srv_sendmsg(srvproc,
        SRV_MSG_ERROR,
        dberr,
        (DBTINYINT)severity,
        (DBTINYINT)oserr,
        NULL,
        0,
        0,
        dberrstr,
        SRV_NULLTERM);

    remote = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    if (remote && Log.MDI_Error)
    {
        plog_buffer = (char *)malloc(
            strlen("DB-Library Error: ") + 11);
        sprintf(plog_buffer,"DB-Library Error: %d",dberr);
        AddRow(remote->hMDI, plog_buffer, colorRed);
        free(plog_buffer);
        AddRow(remote->hMDI, dberrstr, colorBlack);
    }

    if (Log.FILE_Error)
    {
        plog_buffer = (char *)malloc(
            strlen("DBLIB ERR: Client ID:   ") +
            strlen(srv_pfield(srvproc, SRV_SPID, (int *)NULL)) +
            strlen(dberrstr) + 11);
        sprintf(plog_buffer,
            "DBLIB ERR: Client ID: %s %d %s",
            srv_pfield(srvproc, SRV_SPID, (int *)NULL),
            dberr,
            dberrstr);
        srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, plog_buffer, SRV_NULLTERM);
        free(plog_buffer);
    }


    if (oserr != DBNOERR)
    {
    srv_sendmsg(srvproc,
        SRV_MSG_ERROR,
        oserr,
        (DBTINYINT)severity,
        (DBTINYINT)0,
        NULL,
        0,
        0,
        oserrstr,
        SRV_NULLTERM);
    }
    return(INT_CANCEL);
}

//****************************** Function Header ******************************
//
// Function : AttnHandler
//
// Description: Handles "attention" events (dbcancel)
//
//*****************************************************************************
int attn_handler(SRV_PROC  *srvproc)
{
    REMOTE_DBMS *remote;
    char        log_buffer[26];

    remote = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    if (Log.MDI_Attention)
    {
        AddRow(remote->hMDI, "===> Attention received <===", colorRed);
    }

    if (Log.FILE_Attention)
    {
        sprintf(
            log_buffer,
            "Attention: Client Id: %s",
            srv_pfield(srvproc, SRV_SPID, (int *)NULL) );
        srv_log(SRV_GETSERVER(srvproc), Log.FILE_Timing, log_buffer, SRV_NULLTERM);
    }
                            
    // We actually do the dbcancel from within langexec,rpcexec 
    // or hresults in order to keep in synch with dblib.
    return(SRV_CONTINUE);
}

                                         
//****************************** Function Header ******************************
//
// Function : SetRemoteServerName
//
// Description: Sets server name to redirect queries to
//
//*****************************************************************************
void SetRemoteServerName(char *name)
{
    remote_server = name;
}

   
#pragma check_stack()   // set stack checking to its default setting

