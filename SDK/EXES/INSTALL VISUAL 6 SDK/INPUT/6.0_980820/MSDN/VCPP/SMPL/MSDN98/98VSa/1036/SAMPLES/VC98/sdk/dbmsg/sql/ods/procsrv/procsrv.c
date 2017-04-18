//
// This program is an example of an Open Data Services application. It accepts
// requests from clients to execute stored procedures either as language
// events or as remote stored procedure calls.
// It may also be invoked using the Service Control Manager.
//

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <process.h>
#include <srv.h>

#define VERSION "6.00.01"

// Globals
//
BOOL         SrvCtrMan;
HANDLE       hServerDone;
SRV_SERVER * gblServer = NULL;
DBCHAR     * szRegistryName = "PROCSRV";  // Default registry name

SERVICE_STATUS_HANDLE   NTBServiceHandle;
CRITICAL_SECTION        SCMCrtSec;
SERVICE_STATUS          NTBServiceStatus;


// Syscharsets query from DBLIB 4.2 NT clients
//
#define SERVER_INFO_QUERY   "exec sp_server_info 18"

// Define some user message codes.
//
#define     SRV_MAXERROR           20000
#define     SP_UNKNOWN             SRV_MAXERROR + 1
#define     INVALID_SP_SYNTAX      SRV_MAXERROR + 2
#define     BAD_SP_PARAMETER       SRV_MAXERROR + 3
#define     BROADCAST              SRV_MAXERROR + 4
#define     EXEC                   SRV_MAXERROR + 5

// Miscellaneous defines used by sp-handling routines.
//
#define EXEC_CMD            "exec"
#define MAXNAME             31
#define MAXLEN              80
#define MAXPARAMS           4
#define VALUE               0x0000
#define REFERENCE           0x0001
#define CMDSTR              7
#define BUF_SIZE            2048
#define XBASE_HDR_SIZE      32
#define XBASE_MAX_COLUMNS   128

// Standard error macro for reporting API errors
//
#define SETERROR( api, retstring )                          \
    sprintf(retstring,"%s: Error %d from %s on line %d\n",  \
            __FILE__, GetLastError(), api, __LINE__);

// Event handlers for SP requests.
//
SRVRETCODE proclist();         // List SP associated with Server
SRVRETCODE sp_exec();          // Execute the specified command string
SRVRETCODE diskfree();         // Return the space on a given drive
SRVRETCODE disklist();         // List available drives and their space
SRVRETCODE scan_xbase();       // Open and read an xBase file

// Stored Procedure parameter information structure.
//
typedef struct sp_params {
    DBCHAR name[MAXNAME];           // Parameter name
    int    type;                    // Parameter data type
    DBINT  length;                  // Parameter type length
    int    status;                  // Parameter return status
    DBCHAR defaultvalue[MAXLEN *10];// Optional default value
} SP_PARAMS;

// Stored Procedure information structure.
//
typedef struct sp_info {
    DBCHAR      name[MAXNAME];          // Procedure name
    DBCHAR      usage[MAXLEN];          // Usage string
    int         numparams;              // Number of parameters
    SP_PARAMS   params[MAXPARAMS];      // Parameter array
    SRVRETCODE   (*handler)(VOID *, ...);  // Pointer to function with variable arguments
} SP_INFO;

// Array of Stored Procedure handlers.
//
SP_INFO Sps[] =
{
    "proclist",
    "usage: proclist",
    0,
       {
        0
       },
    proclist,

    "sp_exec",              // Procedure name
    "usage: sp_exec <[@command =] command string>", // Procedure usage
    1,                      // Number of parameters
   {    // Parameter definitions
        "command",          // Parameter name
        SRVCHAR,            // Parameter type
        MAXLEN,             // Parameter length (0 if fixed)
        VALUE,              // Pass by value
        "dir *.*",          // Default parameter value
    },
    sp_exec,                // Procedure function pointer

    "disklist",
    "usage: disklist ",
    0,
   {
        0
    },
    disklist,

    "diskfree",
    "usage: diskfree <[@drive =] drive letter> [,] <[@space =] free space>",
    2,
   {
        "drive",
        SRVCHAR,
        1,
        VALUE,              // pass by value
        "c",

        "space",
        SRVINT4,
        8,
        REFERENCE,          // pass by reference
        "0",
    },
    diskfree,

    "scan_xbase",               // rpc name
    "usage: scan_xbase <[@file_name =] xbase file name>",   // rpc usage
    1,                          // number of parameters
   {   // parameter definitions
        "file_name",            // parameter name
        SRVCHAR,                // parameter type
        MAXLEN,                 // parameter length (0 if fixed)
        VALUE,                  // pass by value
        "\\sql\\opends\\samples\\procsrv\\build\\sales.dbf", // default parameter value
    },
    scan_xbase,                 // rpc function pointer

};

#define Rpcnumber sizeof(Sps) / sizeof(SP_INFO)

// Other function prototypes
//
void main( int argc, char **argv );
void WINAPI ProcSrvMain( DWORD argc, char *argv[] );
void initsignal( SRV_SERVER *, char * );
void ctrlc_hndl( ULONG );
void WINAPI NTBServiceCtrlHandler( DWORD );
void completesignal( SRV_SERVER * );
void NTBShutdown( LPVOID );
char * get_last_error_str();

SRVRETCODE chk_err( SRV_SERVER * server,
                 SRV_PROC   * srvproc,
                 int          srverror,
                 BYTE         severity,
                 BYTE         state,
                 int          oserrnum,
                 DBCHAR     * errtext,
                 int          errtextlen,
                 DBCHAR     * oserrtext,
                 int          oserrtextlen );

SRVRETCODE init_remote(SRV_PROC * srvproc);

SRVRETCODE init_server(SRV_SERVER * server);

SRVRETCODE sp_execute(SRV_PROC * srvproc);

SRVRETCODE exit_remote(SRV_PROC *srvproc);

SRVRETCODE lang_execute(SRV_PROC *srvproc);

// Miscellaneous prototypes for sp language events
//
SRVRETCODE lang_parser(SRV_PROC *srvproc, SP_INFO **sp,
                    DBCHAR paramvalues[MAXPARAMS][MAXLEN]);

DBCHAR *scan_next(DBCHAR *string, DBCHAR *word);


// =================================== main ==================================
//
void main( int argc, char *argv[] )
{
    SERVICE_TABLE_ENTRY DispatchTable[] =
    {
        "ProcSrv", ProcSrvMain,
        NULL,      NULL
    };

    // Assume ProcSrv.exe was started from the Service Control Manager or
    // SQL Service Manager.
    //
    SrvCtrMan = TRUE;

    // Check for command line arguments.  The following command line arguments
    // are supported:
    //
    //    -c  Procsrv was started from the command line.  Avoids the timeout
    //        delay when an attempt is made to start procsrv as a service.
    //
    //    -r<registry key name>
    //        Look in Registry under the <registry key name> for the ListenOn
    //        values.  Also assumes procsrv.exe was started from command line.
    //
    //    -?  Displays the command usage information.
    //
    if( argc > 2 )
        goto Usage;

    if( argc == 2 )
    {
        if( !strcmp(argv[1], "-?") )
            goto Usage;

        if( !stricmp(argv[1], "-c") )
            SrvCtrMan = FALSE;
        else if( strlen(argv[1]) < 3 )
            goto Usage;
        else if( !strnicmp(argv[1], "-r", 2) )
        {
            szRegistryName = argv[1] + 2;
            SrvCtrMan = FALSE;
        }
        else
            goto Usage;
    }

    if( SrvCtrMan )
    {
        // Now we will attempt to start the ProcSrv.exe as a service.  The attempt
        // will time out if this process was started from the command line.
        // StartServiceCtrlDispatcher does not return until after ProcSrv has stopped.
        // The ProcSrvMain is called from Service Control Manager within
        // the context of the same process.
        //
        if( StartServiceCtrlDispatcher(DispatchTable) )
        {
            _flushall();
            return;
        }
    }

    // The service was started from the command line or the attempt to
    // start the service failed.  We can assume that this process
    // was started from the command line.
    //
    SrvCtrMan = FALSE;
    ProcSrvMain( argc, argv );
    return;

Usage:
    printf( "Usage: procsrv [-c] | [-r<registry key name>] | [-?]\n"
            "    -c  Procsrv was started from the command line\n"
            "    -r  Look in Registry under <registry key name> for ListenOn values\n"
            "    -?  Displays this help message\n" );
}


// ================================== ProcSrvMain ============================
//
void WINAPI ProcSrvMain( DWORD argc, char *argv[] )
{
    SRV_CONFIG * config;        // The configuration structure
    DWORD        dwPathLength;
    char         szPath[1024];
    char         szLogBuffer[1024];

    if( !SrvCtrMan )
    {
        printf( "\nProcedure Server, Copyright 1994, Microsoft\n" );
        printf( "              version: %s\n\n", VERSION );
    }

    // Allocate a configuration structure that is used to initialize
    // the Open Data Services application
    //
    config = srv_config_alloc();

    // Allow 20 connections at a time.
    //
    srv_config(config, (DBINT)SRV_CONNECTIONS, "20", SRV_NULLTERM);

    // Set the log file.
    //
    // Get the path of this process.  We'll use it to constuct the path of the
    // log file.
    //
    szPath[0] = '\0';
    dwPathLength = GetModuleFileName( GetModuleHandle(NULL),
                                      szPath,
                                      sizeof(szPath) );

    // Stip off process name (i.e. "ProcSrv.exe")
    //
    while( dwPathLength > 1 )
    {
        --dwPathLength;
        if( szPath[dwPathLength] == '\\' || szPath[dwPathLength] == ':' )
        {
            dwPathLength++;
            szPath[dwPathLength] = '\0';    // Null terminate after back slash
            break;
        }
    }

    // Append "<registryname>.log" to path
    //
    strcat( szPath, szRegistryName );
    strcat( szPath, ".log" );

    srv_config(config, (DBINT)SRV_LOGFILE, szPath, SRV_NULLTERM);

    // All data source strings will be converted from ANSI to the OEM codepage
    // in order to make this application behave like SQL Server.
    //
    srv_config(config, (DBINT)SRV_ANSI_CODEPAGE, "FALSE", SRV_NULLTERM);

    // Install the error handler.
    //
    srv_errhandle(chk_err);

    //  Initialize Procedure Server and save the server handle
    //  so it can be used in later functions.
    //
    gblServer = srv_init(config, szRegistryName, SRV_NULLTERM);

    if( gblServer == NULL )
    {
        printf( "\nUnable to initialize Procedure Server.  "
                "Check Event Log.\n" );
        goto Exit;
    }

    // Create an event flag that will tell us when ProcSrv is completely
    // shut down (srv_run() has returned)
    //
    hServerDone = CreateEvent( NULL, TRUE, FALSE, NULL );
    if( hServerDone == NULL )
    {
        sprintf( szLogBuffer,
                 "Procedure Server Service Manager Failer: %s "
                 "(ProcSrvMain(), line = %d), message = %s",
                 szRegistryName,
                 __LINE__,
                 get_last_error_str() );
        srv_log( gblServer, TRUE, szLogBuffer, SRV_NULLTERM );
        printf( "\n%s\n", szLogBuffer );
        goto Exit;
    }

    // When starting Procedure Server, initialize the remote server structure.
    // This is done in the init_server() function.
    // All the other event handlers are also defined in the init_server()
    // function.
    //
    srv_handle( gblServer, (DBINT)SRV_START, init_server );

    sprintf( szLogBuffer,
             "Procedure Server Starting, name = %s",
             szRegistryName );

    //  Now everything's ready to go with Procedure Server, so we
    //  start it and keep it going until we get a stop request.
    //
    srv_log( gblServer, FALSE, " ", SRV_NULLTERM );    // insert blank line
    srv_log( gblServer, TRUE, szLogBuffer, SRV_NULLTERM );

    // initsignal() notifies the Service Control Manager that the
    // service has been started and sets up the signal handlers.
    //
    initsignal( gblServer, argv[0] );

    // completesignal() notifies the Service Control Manager that the
    // service has completed its startup process.
    //
    completesignal( gblServer );

    // srv_run() does not return until either a FAILure occurs or a SRV_EXIT
    // event has been issued.
    //
    if( srv_run(gblServer) == FAIL )
    {
        printf( "\nProcedure Server Failer, Check logs.\n" );
        goto Exit;
    }

    // Set flag indicating all processing completed
    //
    SetEvent( hServerDone );
    return;

Exit:
    // initsignal() notifies the Service Control Manager that the
    // service has been started and sets up the signal handlers.
    // This must be done even though we have an "error exit" condition.
    //
    initsignal( gblServer, argv[0] );

    // completesignal() notifies the Service Control Manager that the
    // service has completed its startup process.
    //
    completesignal( gblServer );

    // NTBShutdown() sets the SQL Service Manager to "Stop" and terminates
    // the service.
    //
    SetThreadPriority( (HANDLE)_beginthread(NTBShutdown, 0, NULL),
                       THREAD_PRIORITY_HIGHEST );

    // Set flag indicating all processing completed
    //
    SetEvent( hServerDone );
}


// This section defines all the Open Data Services event handler functions for
// the Procedure Server application. The procedures implemented are:
//
//
//  PROCLIST        Returns all the supported procedures and their usuage.
//
//  SP_EXEC         Executes a command string and returns output as a rows
//                  of text.
//
//  DISKFREE        Returns the amount the amount of available space for a given
//                  drive.
//
//  DISKLIST        Returns a row for each defined drive containing its name
//                  and the amount of disk space available.
//
// SCAN_XBASE       Reads an xBase file and sends it to the client as if it
//                  were a SQL Server query result set (the equivalent of a
//                  'SELECT * FROM tablename' SQL statement).
//
//
// ================================== init_server ============================
//
// INIT_SERVER
//    Initialize the server on a SRV_START event.
//    Event handlers for the server are installed.
//
// Parameters:
//    server - Pointer to SRV_SERVER structure
//
// Returns:
//    SRV_CONTINUE
//
SRVRETCODE init_server( SRV_SERVER *server )
{
    char log_buffer[256];

    //  When we get a connection request from a client, we want to
    //  call "init_remote()" to make a connection to the remote
    //  server.
    //
    srv_handle(server, (DBINT)SRV_CONNECT, init_remote);

    // When the client issues a language request, call
    // "lang_execute()" to send the SQL statement to the remote DBMS.
    //
    srv_handle(server, (DBINT)SRV_LANGUAGE, lang_execute);

    // When the client issues an RSP, call "sp_execute()"
    // to send the RSP to the remote DBMS (the SQL Server).
    //
    srv_handle(server, (DBINT)SRV_RPC, sp_execute);

    // When a disconnect request is issued, call "exit_remote()"
    // to close the connection to the remote DBMS.
    //
    srv_handle(server, (DBINT)SRV_DISCONNECT, exit_remote);

    // Log Server information to log file
    //
    sprintf(log_buffer, "Client connections allowed = %s",
            srv_sfield(server, SRV_CONNECTIONS, (int *)NULL));

    srv_log(server, FALSE, log_buffer, SRV_NULLTERM);
    printf("%s\n", log_buffer);

    return SRV_CONTINUE;
}


// ================================== init_remote ============================
//
// INIT_REMOTE
//    Event handler for a SRV_CONNECT event.
//    A connection is made to the procedure server.
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    SRV_CONTINUE
//
// Side Effects:
//    If the connection to the remote dbms cannot be made, then issue
//    a SRV_DISCONNECT request.
//
//
SRVRETCODE init_remote( SRV_PROC *srvproc )
{
    char *string;
    int   len;

    // Set server name
    //
    srvproc->serverlen = (BYTE)strlen(szRegistryName);
    srvproc->servername = srv_alloc((DBINT)srvproc->serverlen);
    strcpy(srvproc->servername, szRegistryName);

    // Display info on console
    //
    string = srv_pfield(srvproc, SRV_CPID, &len);
    string[len] = '\0';
    printf("\nClient process ID: %s\n", string);

    string = srv_pfield(srvproc,    SRV_USER, &len);
    string[len] = '\0';
    printf("User name: %s\n", string);

    string = srv_pfield(srvproc, SRV_APPLNAME, &len);
    string[len] = '\0';
    if (len > 0)
        printf("Application program name: %s\n", string);

    string = srv_pfield(srvproc, SRV_RMTSERVER, &len);
    string[len] = '\0';
    if (len > 0)
        printf("Remote Server: %s\n", string);

    return SRV_CONTINUE;
}


// ================================ lang_execute =============================
//
// LANG_EXECUTE
//    Execute a client language request on the procedure server.
//
// Parameters:
//    srvproc - process handle to the current client connection.
//
// Returns:
//    SRV_CONTINUE
//
SRVRETCODE lang_execute( SRV_PROC *srvproc )
{
    int      i;
    DBCHAR   paramvalues[MAXPARAMS][MAXLEN];
    BYTE     convertvalues[MAXPARAMS][MAXLEN];
    SP_INFO *sp = NULL;

    // Initialize parameter storage
    //
    for (i = 0; i < MAXPARAMS; i++) {
        memset(paramvalues[i], 0, MAXLEN);
        memset(convertvalues[i], 0, MAXLEN);
    }
    if (lang_parser(srvproc, &sp, paramvalues) == SUCCEED) {
        for (i = 0; i < sp->numparams; i++) {
            if (sp->params[i].status == REFERENCE) {
                srv_sendstatus(srvproc, 1);
                srv_sendmsg(srvproc, SRV_MSG_ERROR, INVALID_SP_SYNTAX,
                            SRV_INFO, (DBTINYINT)0, NULL, 0, 0,
                                    "Procedure contains a return parameter.\
                            Unable to execute as a language event.",
                             SRV_NULLTERM);
                srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0,
                             0);
                return SRV_CONTINUE;

            }
            if (strlen(paramvalues[i]) == 0 &&
                strlen(sp->params[i].defaultvalue) == 0) {
                srv_sendstatus(srvproc, 1);
                srv_sendmsg(srvproc, SRV_MSG_ERROR, INVALID_SP_SYNTAX,
                            SRV_INFO, (DBTINYINT)0, NULL, 0, 0, sp->usage,
                            SRV_NULLTERM);
                srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0,
                             0);
                return SRV_CONTINUE;
            }
            if (strlen(paramvalues[i]) == 0 &&
                strlen(sp->params[i].defaultvalue) != 0)
                strcpy(paramvalues[i], sp->params[i].defaultvalue);

            // convert parameters from character string to parmeter type
            //
            srv_convert(srvproc, SRVCHAR, paramvalues[i], -1,
                        sp->params[i].type, &convertvalues[i],
                        sp->params[i].length);
        }

        // Execute the procedure
        //
        (sp->handler)((VOID *)srvproc, &convertvalues[0], &convertvalues[1],
                      &convertvalues[2], &convertvalues[3]);
    }
    return SRV_CONTINUE;
}


// ================================= lang_parser =============================
//
// LANG_PARSER
//    A procedure server specific language event parser.
//
// Parameters:
//    srvproc - process handle to the current client connection.
//    sp - Pointer to the stored procedure structure
//    paramvalues - An array of the values of the parameters.
//
// Returns:
//    SUCCEED
//
SRVRETCODE lang_parser( SRV_PROC *srvproc,
                     SP_INFO **sp,
                     DBCHAR    paramvalues[MAXPARAMS][MAXLEN] )
{
    DBCHAR *query;      // pointer to language buffer
    int     i;
    int     numparams;
    DBCHAR  msg[MAXLEN *5];
    DBINT   msgnum;
    DBCHAR  spname[MAXLEN];
    BOOL    paramsyntax = FALSE;
    DBCHAR  paramname[MAXLEN];
    DBCHAR  equalstring[2];
    DBCHAR *paramvalue = NULL;

    query = srv_langptr(srvproc);

    // Ignore the syscharsets query from DBLIB 4.2 NT clients
    //
    if (!strncmp(query, SERVER_INFO_QUERY, strlen(SERVER_INFO_QUERY))){
        srv_senddone(srvproc, SRV_DONE_FINAL, 0, 0);
        return FAIL;
    }

    query = scan_next(query, spname);
    if (strlen(spname) == 0) {
        srv_senddone(srvproc, SRV_DONE_FINAL, 0, 0);
        return FAIL;
    }
    if (strnicmp(spname, EXEC_CMD, (sizeof(EXEC_CMD) - 1)) == 0) {
        // stored procedure name
        //
        query = scan_next(query, spname);
        if (strlen(spname) == 0)
            goto syntax_error;
    }

    // Check for existence
    //
    for (i = 0; i < Rpcnumber; i++)
        if (strcmp(Sps[i].name, spname) == 0) {
            *sp = &Sps[i];
            break;
        }
    if (*sp == NULL) {
        sprintf(msg, "Procedure \'%s \' not found.", spname);
        msgnum = SP_UNKNOWN;
        goto error;
    }

    // Parameters
    //
    numparams = 0;
    while (*query != '\0') {
        if (++numparams > (*sp)->numparams) {
            sprintf(msg, (*sp)->usage);
            msgnum = INVALID_SP_SYNTAX;
            goto error;
        }
        if (!paramsyntax && *query == '@')
            paramsyntax = TRUE; // parameter name mode

        if (!paramsyntax)
            if (paramvalue == NULL)
                paramvalue = paramvalues[0];
            else
                paramvalue += MAXLEN;

        if (paramsyntax) {
            if (*query != '@') {
                sprintf( msg,
                         "Once the form '@name = value' has been used, "
                         "all subsequent parameters must be passed in "
                         "the form '@name = value'." );
                msgnum = INVALID_SP_SYNTAX;
                goto error;
            } else
                query++;

            query = scan_next(query,
            paramname);
            if (strlen(paramname) == 0)
                goto syntax_error;

            // Get parameter index
            //
            paramvalue = NULL;
            for (i = 0; i < (*sp)->numparams; i++)
                if (strcmp((*sp)->params[i].name, paramname) == 0) {
                    paramvalue = paramvalues[i];
                    break;
                }
            if (paramvalue == NULL) {
                sprintf( msg,
                         "Procedure '%s' does not recognize parameter name: %s",
                         spname, paramname );
                msgnum = BAD_SP_PARAMETER;
                goto error;
            }

            // Already assigned value
            //
            if (strlen(paramvalue) > 0)
                goto syntax_error;

            // Check for '='
            //
            query = scan_next(query,
            equalstring);
            if (*equalstring != '=')
                goto syntax_error;

        }
        query = scan_next(query,
        paramvalue);
        if (strlen(paramvalue) == 0)
            goto syntax_error;

        if (*query == ',') {
            query++;
            while (*query == ' ' || *query == '\t')
                query++;
        }
    }
    return SUCCEED;

syntax_error:
    sprintf(msg, "Incorrect syntax found near '%s'.", query);
    msgnum = INVALID_SP_SYNTAX;

error:
    srv_sendstatus(srvproc, 1);
    srv_sendmsg(srvproc, SRV_MSG_ERROR, msgnum, SRV_INFO, (DBTINYINT)0, NULL,
                0, 0, msg, SRV_NULLTERM);
    srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0);
    return FAIL;
}


// ================================= scan_next ===============================
//
// SCAN_NEXT
//    Reads the next token in a string, ignoring whitespace.
//
// Parameters:
//    string - The language event string
//    word - The next token in the string
//
// Returns:
//    The string incremented passed the token.
//
DBCHAR *scan_next( DBCHAR *string, DBCHAR *word )
{
    DBCHAR *p;

    word[0] = '\0';
    if (*string == '\"' || *string == '\'') {
        // check for unclosed quote
        //
        p = strchr(string + 1,
        *string);
        if (p == NULL)
            return string;
        strncpy(word, string + 1, p - (string + 1));
        word[p - (string + 1)] = '\0';
        string += 2;
    } else {
        // clear proceeding white space
        //
        while (*string == ' ' || *string == '\t' || *string == '\n' ||
               *string == '\r')
            string++;
        sscanf(string, "%s", word);

        // ignore comments
        //
        while (strncmp(word, "/*", 2) == 0) {
            string = strstr(string,
            "*/");
            if (string != NULL) {
                string += 2;
                word[0] = '\0';
                while (*string == ' ' || *string == '\t' || *string == '\n' ||
                       *string == '\r')
                    string++;
                sscanf(string, "%s", word);
            } else
                return string;
        }
    }
    if (strlen(word) > 0)
        string += strlen(word);

    // clear trailing white space
    //
    while (*string == ' ' || *string == '\t' || *string == '\n' ||
           *string == '\r')
        string++;

    return string;
}


// ================================== sp_execute =============================
//
// SP_EXECUTE
//    Execute a client stored procedure.
//
//    Scans the list of defined stored procedures, checks the parameters and
//    executes the procedure. If results are returned it is the responsiblity
//    of the underlying proedure.
//
// Parameters:
//    srvproc - The process handle to use to send results to the client.
//
// Returns:
//    SRV_CONTINUE
//
SRVRETCODE sp_execute( SRV_PROC  *srvproc )
{
    int      i;
    int      x;
    int      y;
    int      len;
    int      numparams;
    SP_INFO *sp = NULL;
    DBCHAR   msg[MAXLEN];
    DBINT    msgnum;
    DBCHAR   paramvalues[MAXPARAMS][MAXLEN];
    BOOL     paramnamemode = FALSE;
    DBCHAR  *paramname;
    DBINT    paramtype;
    DBCHAR  *value;
    DBINT    type;
    DBINT    status;

    // Initialize parameter storage
    //
    for( i = 0; i < MAXPARAMS; i++ )
        memset( paramvalues[i], 0, MAXLEN );

    for( i = 0; i < Rpcnumber; i++ )
    {
        // Create name generated by calling server
        //
        if( strcmp(Sps[i].name, srv_rpcname(srvproc, (int *)NULL)) == 0 )
        {
            sp = &Sps[i];
            break;
        }
    }

    if( sp == NULL )
    {
        sprintf( msg,
                 "Procedure \'%s \' not found.",
                 srv_rpcname(srvproc, (int *)NULL) );

        msgnum = SP_UNKNOWN;
        goto error;
    }

    numparams = srv_rpcparams( srvproc );

    if( srv_paramname(srvproc, 1, &len) && len > 0 )
        paramnamemode = TRUE;

    for( y = 1; y <= numparams; y++ )
    {
        // Find parameter number
        //
        if( paramnamemode )
        {
            paramname = srv_paramname( srvproc,
                                       y,
                                       &len );

            if( strlen(paramname) == 0 )
                goto parameter_error;

            if( *paramname == '@' )
                paramname++;
            else
                goto parameter_error;

            value = NULL
            ;
            for( x = 0; x < sp->numparams; x++ )
            {
                if( strcmp(sp->params[x].name, paramname) == 0 )
                {
                    value  = paramvalues[x];
                    type   = sp->params[x].type;
                    status = sp->params[x].status;
                    break;
                }
            }

            if( value == NULL )
                goto parameter_error;
        }
        else  // if( paramnamemode )
        {
            value  = paramvalues[y - 1];
            type   = sp->params[y - 1].type;
            status = sp->params[y - 1].status;
        }

        // Check parameters for correct type
        //
        paramtype = srv_paramtype( srvproc, y );

        switch( paramtype )
        {
        case SRVVARCHAR:    // Type sent by Servers instead of SRVCHAR
            paramtype = SRVCHAR;
            break;
        case SRVINTN:       // Type sent by Servers instead of SRVINT
            paramtype = SRVINT4;
            break;
        default:
            break;
        }

        if( type != paramtype )
        {
            if( paramnamemode )
                sprintf( msg, "Parameter \'%s \' is incorrect type.",
                         paramname );
            else
                sprintf( msg, "Parameter \'%d \' is incorrect type.", y );

            msgnum = BAD_SP_PARAMETER;
            goto error;
        }

        // Check parameters for correct status
        //
        if( (DBINT)srv_paramstatus(srvproc, y) != status )
        {
            if( paramnamemode )
                sprintf( msg, "Parameter \'%s \' has incorrect status.",
                         paramname);
            else
                sprintf( msg, "Parameter \'%d \' had incorrect status.", y );

            msgnum = BAD_SP_PARAMETER;
            goto error;
        }

        // Move SP parameters to local variables
        //
        srv_bmove( srv_paramdata(srvproc, y), value, srv_paramlen(srvproc, y) );
        value[srv_paramlen(srvproc, y)] = '\0';

    }

    // If unspecified, use default value
    //
    for( i = 0; i < sp->numparams; i++ )
    {
        if( strlen(paramvalues[i]) == 0
        &&  strlen(sp->params[i].defaultvalue) == 0 )
        {
            strcpy( msg, sp->usage );
            msgnum = INVALID_SP_SYNTAX;
            goto error;
        }

        if( strlen(paramvalues[i]) == 0
        &&  strlen(sp->params[i].defaultvalue) != 0 )
            strcpy(paramvalues[i], sp->params[i].defaultvalue);
    }

    // Execute procedure
    //
    (*sp->handler)( (VOID *)srvproc,
                    paramvalues[0],
                    paramvalues[1],
                    paramvalues[2],
                    paramvalues[3] );

    return SRV_CONTINUE;

parameter_error:
    sprintf( msg, "Procedure '%s' does not recognize parameter name: %s",
             sp->name, paramname );
    msgnum = BAD_SP_PARAMETER;

error:
    srv_sendstatus( srvproc, 1 );
    srv_sendmsg( srvproc, SRV_MSG_ERROR, msgnum, SRV_INFO, (DBTINYINT)0, NULL,
                 0, 0, msg, SRV_NULLTERM );
    srv_senddone( srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0 );
    return SRV_CONTINUE;
}


// ================================= exit_remote =============================
//
// EXIT_REMOTE
//    Handler for SRV_DISCONNECT events.
//
//    The code to disconnect from the procedure server.
//
// Parameters:
//    srvproc - the handle to the client connection
//
// Returns:
//    SRV_DISCONNECT
///
SRVRETCODE exit_remote( SRV_PROC  *srvproc )
{
    char *string;
    int len;

    // Display info on console
    //
    string = srv_pfield(srvproc, SRV_CPID, &len);
    string[len] = '\0';
    printf("\nClient connection closed, process ID: %s\n", string);

    return SRV_CONTINUE;
}


// ================================== chk_err =================================================
//
// CHK_ERR
//    Print out errors.
//
// Parameters:
//    server        - pointer to procedure server server structure.
//    srvproc      - pointer to client connection structure
//    errornum     - error number.
//    severity     - error severity.
//    state        - error state.
//    oserrnum     - operating system error number, if any.
//    errtext      - the text of the error message.
//    errtextlen   - length of the errtext message
//    oserrtext    - the text of the operating system error message.
//    oserrtextlen - length of the errtext message
//
// Returns:
//    SRV_CONTINUE, SRV_CANCEL, or SRV_EXIT_PROGRAM
//

SRVRETCODE chk_err( SRV_SERVER *server,
                 SRV_PROC   *srvproc,
                 int         errornum,
                 BYTE        severity,
                 BYTE        state,
                 int         oserrnum,
                 DBCHAR     *errtext,
                 int         errtextlen,
                 DBCHAR     *oserrtext,
                 int         oserrtextlen )
{
    char log_buffer[256];
    char error[256];
    char oserror[256];

    memcpy(error, errtext, errtextlen);
    error[errtextlen] = '\0';
    memcpy(oserror, oserrtext, oserrtextlen);
    oserror[oserrtextlen] = '\0';

    // Strip out resource information. Get the actual error number.
    errornum = (errornum & 0x0000FFFF);

    // Operating system error?
    //
    if (oserrnum != SRV_ENO_OS_ERR) {
        sprintf(log_buffer, "SERVER OS ERROR: %d: %s.", oserrnum, oserror);
        if (server)
            srv_log(server, TRUE, log_buffer, SRV_NULLTERM);
        else    // If application not initialized log to screen
            printf ("%s\n", log_buffer);
    }

    // Is this a fatal error for the server?
    //
    if (severity >= SRV_FATAL_SERVER) {
        sprintf(log_buffer,
                    "SERVER: FATAL SERVER ERROR: errornum = %d, "
                    "severity = %d, state = %d: %s.",
                errornum, severity, state, error);

        if (server)
            srv_log(server, TRUE, log_buffer, SRV_NULLTERM);
        else    // If application not initialized log to screen
            printf ("%s\n", log_buffer);
        return SRV_EXIT;
    } else {
        //
        // Did the "srvproc" get a fatal error?
        //
        if (severity >= SRV_FATAL_PROCESS) {
            sprintf(log_buffer,
                          "SERVER: FATAL CONNECT ERROR: errornum = %d, "
                          "severity = %d, state = %d: %s.",
                     errornum, severity, state, error);

            if (server)
                srv_log(server, TRUE, log_buffer, SRV_NULLTERM);
            else    // If application not initialized log to screen
                printf ("%s\n", log_buffer);

            return SRV_CANCEL;
        }
    }

    // A non-fatal error or an information message received.
    // We'll pass it through to the client.
    //
    if (srvproc != (SRV_PROC *)NULL && (server != NULL))
        if (severity < 10) {    // if informational message
            srv_sendmsg(srvproc, SRV_MSG_INFO, (DBINT)errornum, severity, 0,
                        NULL, 0, 0, error, SRV_NULLTERM);
        } else {            // must be an error message
               srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)errornum, severity, 0,
                           NULL, 0, 0, error, SRV_NULLTERM);
    } else {
        sprintf(log_buffer, "ODS ERROR: errornum = %d, severity = %d: %s",
                errornum, severity, error);
        if (server)
            srv_log(server, TRUE, log_buffer, SRV_NULLTERM);
        else    // If application not initialized log to screen
            printf ("%s\n", log_buffer);
    }
    return SRV_CONTINUE;
}


// The following are the supported store procedure functions
//
// ================================== proclist ===============================
//
// PROCLIST
//    Returns the usage for all defined stored procedures
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    SUCCEED
//
// Side Effects:
//    Returns a result set to client
//
SRVRETCODE proclist( SRV_PROC *srvproc )
{
    DBCHAR colname1[MAXNAME];
    DBCHAR colname2[MAXNAME];
    int i;

    sprintf(colname1, "spname");
    srv_describe(srvproc, 1, colname1, SRV_NULLTERM, SRVCHAR, MAXNAME,
                 SRVCHAR, 0, NULL);

    sprintf(colname2, "spusage");
    srv_describe(srvproc, 2, colname2, SRV_NULLTERM, SRVCHAR, MAXLEN, SRVCHAR,
                 0, NULL);

    // Return each SP handler as a row
    //
    for (i = 0; i < Rpcnumber; i++) {
        srv_setcoldata(srvproc, 1, Sps[i].name);
        srv_setcollen(srvproc, 1, strlen(Sps[i].name));

        srv_setcoldata(srvproc, 2, Sps[i].usage);
        srv_setcollen(srvproc, 2, strlen(Sps[i].usage));

        srv_sendrow(srvproc);
    }
    srv_senddone(srvproc, (SRV_DONE_COUNT | SRV_DONE_FINAL), 0, i);

    return SUCCEED;
}


// ================================== sp_exec ================================
//
// SP_EXEC
//      Execute a given command string and returns any output as rows of
//      text.
//
// Parameters:
//      srvproc - the handle to the client connection that got the SRV_CONNECT.
//      command - the command string to execute
//
// Returns:
//      SUCCEED or FAIL
//
// Side Effects:
//      Returns messages and/or a result set to client
//
SRVRETCODE sp_exec( SRV_PROC *srvproc, DBCHAR *command )
{

    DBCHAR bReadBuffer[MAXLEN];
    DBCHAR bErrorMsg[80];
    int    cbReadBuffer;

    DBINT   cnt;
    DBINT   rows = 0;
    DBCHAR *paramvalue;
    DBINT   paramlength;
    DBINT   cmdlength;
    BOOL    fSuccess;

    STARTUPINFO         si;
    PROCESS_INFORMATION pi;

    SECURITY_ATTRIBUTES saPipe;
    HANDLE              hReadPipe;
    HANDLE              hWritePipe;

    // Allocation local storage for command string.
    //
    paramlength = strlen( command );
    cmdlength   = paramlength + CMDSTR + 1;
    paramvalue  = (DBCHAR *)malloc( cmdlength );

    if( !paramvalue )
    {
        SETERROR( "Malloc", bErrorMsg );
        srv_sendstatus( srvproc, 1 );
        srv_sendmsg( srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                     NULL, 0, 0, bErrorMsg, SRV_NULLTERM );
        srv_senddone( srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0 );
        return FAIL;
    }

    // Cancatenate "cmd /c " to command string so child process will
    // execute the given command and exit.  Move command string to
    // local variable.
    //
    memset( paramvalue, 0, cmdlength );
    srv_bmove( "cmd /c ", paramvalue, CMDSTR );
    srv_bmove( command, &paramvalue[CMDSTR], paramlength );

    // Create child process to execute the command string.  Use an
    // anonymous pipe to read the output from the command and send
    // any results to the client.

    // In order for the child process to be able to write
    // to the anonymous pipe, the handle must be marked as
    // inheritable by child processes by setting the
    // SECURITY_ATTRIBUTES.bInheritHandle flag to TRUE.
    //
    saPipe.nLength              = sizeof( SECURITY_ATTRIBUTES );
    saPipe.lpSecurityDescriptor = NULL;
    saPipe.bInheritHandle       = TRUE;

    fSuccess = CreatePipe( &hReadPipe,      // read handle
                           &hWritePipe,     // write handle
                           &saPipe,         // security descriptor
                           0 );             // use default pipe buffer size
    if( !fSuccess )
    {
        SETERROR( "CreatePipe", bErrorMsg );
        srv_sendstatus( srvproc, 1 );
        srv_sendmsg( srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                     NULL, 0, 0, bErrorMsg, SRV_NULLTERM );
        srv_senddone( srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0 );
        free( paramvalue );
        return FAIL;
    }

    // Now we must set standard out and standard error to the
    // write end of the pipe.  Once standard out and standard
    // error are set to the pipe handle, we must close the pipe
    // handle so that when the child process dies, the write end
    // of the pipe will close, setting an EOF condition on the pipe.
    //
    memset( &si, 0, sizeof(si) );

    si.cb          = sizeof(si);
    si.dwFlags     = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdOutput  = hWritePipe;
    si.hStdError   = hWritePipe;

    // Set the fInheritHandles parameter to TRUE so that open
    // file handles will be inheritied. We can close the child
    // process and thread handles as we won't be needing them.
    // The child process will not die until these handles are
    // closed.
    //
    fSuccess = CreateProcess( NULL,         // filename
                              paramvalue,   // command line for child
                              NULL,         // process security descriptor
                              NULL,         // thread security descriptor
                              TRUE,         // inherit handles?
                              0,            // creation flags
                              NULL,         // inherited environment address
                              NULL,         // startup dir; NULL = start in current
                              &si,          // pointer to startup info (input)
                              &pi );        // pointer to process info (output)
    if( !fSuccess )
    {
        SETERROR( "CreateProcess", bErrorMsg );
        srv_sendstatus( srvproc, 1 );
        srv_sendmsg( srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                     NULL, 0, 0, bErrorMsg, SRV_NULLTERM );
        srv_senddone( srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0 );
        free( paramvalue );
        return FAIL;
    }

    CloseHandle( pi.hThread );
    CloseHandle( pi.hProcess );

    // We need to close our instance of the inherited pipe write
    // handle now that it's been inherited so that it will actually
    // close when the child process ends. This will put an EOF
    // condition on the pipe which we can then detect.
    //
    fSuccess = CloseHandle( hWritePipe );

    if( !fSuccess )
    {
        SETERROR( "CloseHandle", bErrorMsg );

        srv_sendstatus( srvproc, 1 );
        srv_sendmsg( srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                     NULL, 0, 0, bErrorMsg, SRV_NULLTERM );
        srv_senddone( srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0 );

        free( paramvalue );
        return FAIL;
    }

    // Now read from the pipe until EOF condition reached.
    //
    do
    {
        cnt = 0;

        while( fSuccess = ReadFile( hReadPipe,          // read handle
                                    &bReadBuffer[cnt],  // buffer for incoming data
                                    1,                  // number of bytes to read
                                    &cbReadBuffer,      // number of bytes actually read
                                    NULL))
        {
            if( !fSuccess )
            {
                if( GetLastError() == ERROR_BROKEN_PIPE )
                    break;  // child has died
                else
                {
                    SETERROR( "CloseHandle", bErrorMsg );

                    srv_sendstatus( srvproc, 1 );
                    srv_sendmsg( srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO,
                                 (DBTINYINT)0, NULL, 0, 0, bErrorMsg,
                                 SRV_NULLTERM );
                    srv_senddone( srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL),
                                  0, 0 );

                    free( paramvalue );
                    return FAIL;
                }
            }

            if (bReadBuffer[cnt] == '\n')
                break;
            else
                cnt++;
        }

        if( fSuccess && cbReadBuffer )
        {
            if( rows == 0 )
            {
                // Describe result row: it will be one column of size
                // sizeof(buf)  We do this in the retrieval loop to
                // ensure that the row description will occur only if
                // there are rows to be outputted.
                //
                srv_describe( srvproc,
                              1,
                              &paramvalue[CMDSTR],
                              SRV_NULLTERM,
                              SRVCHAR,
                              sizeof(bReadBuffer),
                              SRVCHAR,
                              sizeof(bReadBuffer),
                              bReadBuffer );
            }

            // Make sure we have at least one data
            //
            if( !cnt )
            {
                bReadBuffer[0] = ' ';
                cnt = 1;
            }

            // Remove carriage return if it exists
            //
            if( bReadBuffer[cnt-1] == 0x0D )
                cnt--;

            // Send result rows back to client.
            //
            srv_setcollen( srvproc, 1, cnt );
            srv_sendrow( srvproc );
            rows++;
        }
    } while( fSuccess && cbReadBuffer );

    // close the trace file, pipe handles
    //
    CloseHandle( hReadPipe );

    if( rows == 0 )
    {
        srv_sendstatus( srvproc, 0 );
        srv_sendmsg( srvproc, SRV_MSG_INFO, EXEC, SRV_INFO, (DBTINYINT)0, NULL,
                     0, 0, "Command executed successfully", SRV_NULLTERM );
    }

    srv_senddone( srvproc, (SRV_DONE_COUNT | SRV_DONE_FINAL), 0, rows );
    free( paramvalue );
    return SUCCEED;
}


// =================================== disklist ==============================
//
// DISKLIST
//     Returns a row for each defined drive containing its name and the
//     amount of disk space available.
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    SUCCEED
//
// Side Effects:
//     Returns a result set to client
//
SRVRETCODE disklist( SRV_PROC  *srvproc )
{
    DBCHAR colname1[MAXNAME];
    DBCHAR colname2[MAXNAME];
    DBCHAR drivename;
    DBCHAR rootname[16];
    int    drivenum;
    unsigned    secPerCluster;
    unsigned    bytesPerSector;
    unsigned    freeClusters;
    unsigned    totalClusters;
    int    drivenums;
    int    space_remaining;
    int    i = 0;

    sprintf( colname1, "drive" );
    srv_describe( srvproc, 1, colname1, SRV_NULLTERM, SRVCHAR, 1, SRVCHAR, 1,
                  (BYTE *)&drivename );

    sprintf( colname2, "Kbytes free" );
    srv_describe( srvproc, 2, colname2, SRV_NULLTERM, SRVINT4, 4, SRVINT4, 4,
                  (BYTE *)&space_remaining );

    drivenums = GetLogicalDrives();

    drivenums >>= 2;        // Ignore drives A and B
    for( drivename = 'C', drivenum = 3; drivename <= 'Z';
         drivename++, drivenum++ )
    {
        if( drivenums & 1 )
        {
            i++;

            sprintf( rootname, "%c:\\", drivename );
            GetDiskFreeSpace( rootname, &secPerCluster, &bytesPerSector,
                              &freeClusters, &totalClusters );

            space_remaining = secPerCluster * bytesPerSector * (freeClusters/1000) ;

            srv_sendrow( srvproc );
        }

        drivenums >>= 1;
    }

    srv_senddone( srvproc, (SRV_DONE_COUNT | SRV_DONE_FINAL), 0, i );
    return SUCCEED;
}


// ================================== diskfree ===============================
//
// DISKFREE
//    Returns the amount of space available on a given drive. The value
//     is placed into the defined return parameter of the stored procedure.
//
//     NOTE: This routine can not be called via a language event.
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//     drive - the drive letter to check
//
// Returns:
//    SUCCEED
//
// Side Effects:
//    Returns messages and/or a result set to client. Returns a value in the
//     defined return parameter.
//
SRVRETCODE diskfree( SRV_PROC *srvproc, DBCHAR *drive )
{
    DBCHAR colname1[MAXNAME];
    int    drivenum;
    DBCHAR rootname[16];
    int    drivenums;
    int    secPerCluster;
    int    bytesPerSector;
    int    freeClusters;
    int    totalClusters;
    int    space_remaining = -1;
    int    i = 0;

    drive = strupr( drive );

    sprintf( colname1, "drive" );
    srv_describe( srvproc, 1, colname1, SRV_NULLTERM, SRVCHAR, 1, SRVCHAR, 1,
                  (BYTE *)drive );
    srv_sendrow( srvproc );
    srv_senddone( srvproc, (SRV_DONE_COUNT | SRV_DONE_MORE), 0, 1 );

    drivenums = GetLogicalDrives();

    drivenum = drive[0] - 'A' + 1;

    drivenums >>= drivenum - 1; //Ignore drives A and B
    if( drivenums & 0x01 )
    {
        sprintf( rootname, "%c:\\", drive[0] );
        GetDiskFreeSpace( rootname, &secPerCluster, &bytesPerSector,
                          &freeClusters, &totalClusters );

        space_remaining = secPerCluster * freeClusters * bytesPerSector;

    }

    // Process return parameter
    //
    if( srv_paramstatus(srvproc, 2) & 0x0001 )
        srv_paramset( srvproc, 2, (BYTE *)&space_remaining, 4 );

    srv_senddone( srvproc, SRV_DONE_FINAL, 0, 0 );
    return SUCCEED;
}


// ================================== scan_xbase =============================
//
// SCAN_XBASE
//    Reads an xBase file and sends it to the client as if it were a SQL
//    Server query result set (the equivalent of a 'SELECT * FROM
//    tablename' SQL statement).
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//    szFileName - dbase file path name
//
// Returns:
//    SUCCEED or FAIL
//
// Side Effects:
//    Returns messages and/or a result set to client
//
SRVRETCODE scan_xbase( SRV_PROC *srvproc, char *filename )
{
    FILE  *xbasefile;
    size_t count;
    char   buffer[BUF_SIZE];
    short  numrecords;
    short  headerlength;
    short  recordlength;
    short  lengthlist[XBASE_MAX_COLUMNS];
    int    i;
    short  j;
    short  position;
    short  numcolumns;

    // now read the database header info
    //
    if ((xbasefile = fopen(filename, "r")) == NULL) {
        srv_sendstatus(srvproc, 1);
        srv_sendmsg(srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0);
        return FAIL;
    }
    count = fread(buffer,
    XBASE_HDR_SIZE,
    1,
    xbasefile);

    if (count == 0) {
        srv_sendstatus(srvproc, 1);
        srv_sendmsg(srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0);
        fclose(xbasefile);
        return FAIL;
    }
    numrecords   = *((short *)&buffer[4]);
    headerlength = *((short *)&buffer[8]);
    recordlength = *((short *)&buffer[10]);
    numcolumns   = (headerlength - 32 - 1) / 32;

    // now get the column header information
    //
    for (j = 0; j < numcolumns; j++) {
        count = fread(buffer,   XBASE_HDR_SIZE, 1, xbasefile);
        if (count == 0) {
            srv_sendstatus(srvproc, 1);
            srv_sendmsg(srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                        NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
            srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0);
            fclose(xbasefile);
            return FAIL;
        }

        // we need to NULL terminate the column name (if it is a
        // full 11 characters int)
        //
        buffer[11] = '\0';

        // now find our the column length for this data buffer
        //
        lengthlist[j] = (short)buffer[16];

        // now 'describe' this column
        //
        srv_describe( srvproc, j + 1,   // column number
                      buffer,           // pointer to column name
                      SRV_NULLTERM,     // column name is NULL terminated
                      SRVCHAR,          // datatype is char (xBase numbers are ASCII)
                      lengthlist[j],    // column length
                      SRVCHAR,          // destination datatype is also char
                      lengthlist[j],    // destination column length
                      NULL);            // pointer to where the data will be

    }

    // now read the one byte 'column header seperator'
    //
    count = fread(buffer, 1, 1,  xbasefile);
    if (count == 0) {
        srv_sendstatus(srvproc, 1);
        srv_sendmsg(srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0);
        fclose(xbasefile);
        return FAIL;
    }
    for (i = 0; i < numrecords; i++) {
        count = fread(buffer, recordlength, 1, xbasefile);
        if (count == 0 && !feof(xbasefile)) {
            srv_sendstatus(srvproc, 1);
            srv_sendmsg(srvproc, SRV_MSG_ERROR, EXEC, SRV_INFO, (DBTINYINT)0,
                        NULL, 0, 0, "Error reading xBase file", SRV_NULLTERM);
            srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_FINAL), 0, 0);
            fclose(xbasefile);
            return FAIL;
        }

        // check to see if this is a deleted row
        //
        if (buffer[0] == '*')
            break;

        // Now set the length and data pointers for each column
        //
        for (j = 0, position = 1; j < numcolumns; j++) {
            srv_setcollen(srvproc, j + 1, lengthlist[j]);
            srv_setcoldata(srvproc, j + 1, &buffer[position]);
            position += lengthlist[j];
        }

        // send the row to the client.
        //
        srv_sendrow(srvproc);
    }
    srv_senddone(srvproc, SRV_DONE_COUNT | SRV_DONE_FINAL, 0, i);
    fclose(xbasefile);
    return SUCCEED;
}


// The following section defines the Service Control Manager support functions.
//
// ================================== initsignal =============================
//
//  initsignal -- Install signal handlers for NTB Server.
//
void initsignal( SRV_SERVER * server, char * szServiceName )
{
    char szLogBuffer[1024];

    if( SrvCtrMan ) // if started from Service Control Manager
    {
        // Use RegisterServiceCtrlHandler() to communicate with
        // the Service Control Manager.
        //
        NTBServiceHandle = RegisterServiceCtrlHandler( "ProcSrv",
                                                       NTBServiceCtrlHandler );
        InitializeCriticalSection( &SCMCrtSec );

        // Now send a START_PENDING message
        //
        NTBServiceStatus.dwServiceType  = SERVICE_WIN32_OWN_PROCESS;
        NTBServiceStatus.dwCurrentState = SERVICE_START_PENDING;

        NTBServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP
                                            | SERVICE_ACCEPT_PAUSE_CONTINUE
                                            | SERVICE_ACCEPT_SHUTDOWN;

        NTBServiceStatus.dwWin32ExitCode           = NO_ERROR;
        NTBServiceStatus.dwServiceSpecificExitCode = 0;
        NTBServiceStatus.dwCheckPoint              = 1;
        NTBServiceStatus.dwWaitHint                = 20000L;   // 20 seconds

        if( !SetServiceStatus(NTBServiceHandle, &NTBServiceStatus) )
        {
            sprintf( szLogBuffer,
                     "Procedure Server Service Manager Failer: %s "
                     "(initsignal(), line = %d), message = %s",
                     szServiceName,
                     __LINE__,
                     get_last_error_str() );
            srv_log( server, TRUE, szLogBuffer, SRV_NULLTERM );

            // Flush all file buffers
            //
            _flushall();
            ExitProcess( 1 );
        }

        // We need to increment checkpoint field in the above structure
        // regularly in order to notify Service Control Manager that
        // we aren't hung.
        //
        ++(NTBServiceStatus.dwCheckPoint);

    } // if( SrvCtrMan )

    // Don't display a message box for hard errors, return the error back
    // to the application instead.
    //
    SetErrorMode( SEM_FAILCRITICALERRORS );

    // Install Ctrl-C handler
    //
    if( !SrvCtrMan )
    {
        if( SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlc_hndl, TRUE)
        != TRUE )
        {
            sprintf( szLogBuffer,
                     "Procedure Server Service Manager Failer: %s "
                     "(SetConsoleCtrlHandler(), line = %d), message = %s",
                     szServiceName,
                     __LINE__,
                     get_last_error_str() );
            srv_log( server, TRUE, szLogBuffer, SRV_NULLTERM );
        }
    }
    return;
}


// ================================== ctrlc_hndl =============================
//
//  ctrlc_hndl(ulong) -- Handles Ctrl-C and Ctrl-Break events received
//  by NTB Server.
//
void ctrlc_hndl( ULONG CtrlTyp )
{
    char c;
    char szLogBuffer[1024];

    switch( CtrlTyp )
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:

        printf( "Terminate Procedure Server? (y/n): ");

        do
        {
            c = getch();
        } while( c != 'y' && c != 'Y' && c != 'n' && c != 'N' );

        printf( "%c\n", c );

        if( c == 'y' || c == 'Y' )
        {
            sprintf( szLogBuffer,
                     "Procedure Server terminated by Ctrl-C or Ctrl-Break, name = %s",
                     szRegistryName );

            if( gblServer ) {
                srv_log( gblServer, TRUE, szLogBuffer, SRV_NULLTERM );
                srv_setevent( gblServer, SRV_EXIT );
            }
            WaitForSingleObject(hServerDone, INFINITE );

            _flushall();
            ExitProcess( 0 );
        }

        break;

    default:
        break;
    }
    return;
}


// ============================== NTBServiceCtrlHandler ======================
//
//  NTBServiceCtrlHandler(DWORD) -- Responds to START, STOP, etc..
//  requests of Service Control Manager.
//
void WINAPI NTBServiceCtrlHandler( DWORD dwCtrl )
{
    char szLogBuffer[1024];

    switch( dwCtrl )
    {
    case SERVICE_CONTROL_SHUTDOWN:
        //
        // NT is shutting down.
        //
        // Fall through

    case SERVICE_CONTROL_STOP:

        EnterCriticalSection( &SCMCrtSec );

        NTBServiceStatus.dwCurrentState            = SERVICE_STOP_PENDING;
        NTBServiceStatus.dwWin32ExitCode           = NO_ERROR;
        NTBServiceStatus.dwServiceSpecificExitCode = 0;
        NTBServiceStatus.dwCheckPoint              = 1;
        NTBServiceStatus.dwWaitHint                = 60000L;   // 60 seconds

        SetServiceStatus( NTBServiceHandle, &NTBServiceStatus );
        LeaveCriticalSection( &SCMCrtSec );

        // NTBShutdown() sets the SQL Service Manager to "Stop" and terminates
        // the service.
        //
        SetThreadPriority( (HANDLE)_beginthread(NTBShutdown, 0, NULL),
                           THREAD_PRIORITY_HIGHEST );
        break;

    case SERVICE_CONTROL_INTERROGATE:

        // Serialize with increment signal thread
        //
        EnterCriticalSection( &SCMCrtSec );

        SetServiceStatus( NTBServiceHandle, &NTBServiceStatus );
        LeaveCriticalSection( &SCMCrtSec );
        break;

    case SERVICE_CONTROL_PAUSE:

        // Serialize with increment signal thread
        //
        EnterCriticalSection( &SCMCrtSec );

        srv_setevent( gblServer, SRV_SLEEP );

        NTBServiceStatus.dwCurrentState            = SERVICE_PAUSED;
        NTBServiceStatus.dwWin32ExitCode           = NO_ERROR;
        NTBServiceStatus.dwServiceSpecificExitCode = 0;
        NTBServiceStatus.dwCheckPoint              = 1;
        NTBServiceStatus.dwWaitHint                = 60000L;   // 60 seconds

        SetServiceStatus( NTBServiceHandle, &NTBServiceStatus );
        LeaveCriticalSection( &SCMCrtSec );

        sprintf( szLogBuffer,
                 "Procedure Server PAUSED, name = %s",
                 szRegistryName );

        if( gblServer )
            srv_log( gblServer, TRUE, szLogBuffer, SRV_NULLTERM );
        break;

    case SERVICE_CONTROL_CONTINUE:

        EnterCriticalSection( &SCMCrtSec );

        srv_setevent( gblServer, SRV_RESTART );

        NTBServiceStatus.dwCurrentState            = SERVICE_RUNNING;
        NTBServiceStatus.dwWin32ExitCode           = NO_ERROR;
        NTBServiceStatus.dwServiceSpecificExitCode = 0;
        NTBServiceStatus.dwCheckPoint              = 1;
        NTBServiceStatus.dwWaitHint                = 60000L;   // 60 seconds

        SetServiceStatus(NTBServiceHandle, &NTBServiceStatus);
        LeaveCriticalSection( &SCMCrtSec );

        sprintf( szLogBuffer,
                 "Procedure Server CONTINUED, name = %s",
                 szRegistryName );

        if( gblServer )
            srv_log( gblServer, TRUE, szLogBuffer, SRV_NULLTERM );
        break;

    default:
        // Values 128-255 can be user app defined
        //
        ;
    } // switch( dwCtrl )

    return;
}


// ================================= completesignal ==========================
//
// completesignal() -- Notifies Service Control Manager that NTB Server
//  has started.
//
void completesignal( SRV_SERVER * server )
{
    char szLogBuffer[1024];

    if( !SrvCtrMan )
        return;

    EnterCriticalSection( &SCMCrtSec );

    NTBServiceStatus.dwCurrentState = SERVICE_RUNNING;
    NTBServiceStatus.dwCheckPoint   = 0;
    NTBServiceStatus.dwWaitHint     = 0;

    if( !SetServiceStatus(NTBServiceHandle, &NTBServiceStatus) )
    {
        sprintf( szLogBuffer,
                 "Procedure Server Service Manager Failer: %s, (completesignal(), line = %d), message = %s",
                     szRegistryName,
                     __LINE__,
                 get_last_error_str() );

        srv_log( server, TRUE, szLogBuffer, SRV_NULLTERM );
    }

    LeaveCriticalSection( &SCMCrtSec );
    return;
}


// ==================================== NTBShutdown ==========================
//
//  NTBShutdown() -- This routine notifies ODS to terminate.  After ODS has terminate,
//                   the Service Control Manager is notified that everything has shut down.
//
void NTBShutdown( LPVOID notused )
{
    char szLogBuffer[1024];

    // Flush all file buffers
    //
    _flushall();

    // Tell ODS to terminate...
    //
    srv_setevent( gblServer, SRV_EXIT );

    do
    {
        // Start the checkpoint incrementer
        //
        ++(NTBServiceStatus.dwCheckPoint);

    } while( WaitForSingleObject(hServerDone, 1000) == WAIT_TIMEOUT );

    sprintf( szLogBuffer,
             "Procedure Server STOPPED, name = %s",
             szRegistryName );

    if( gblServer )
        srv_log( gblServer, TRUE, szLogBuffer, SRV_NULLTERM );

    _flushall();

    EnterCriticalSection( &SCMCrtSec );

    NTBServiceStatus.dwCurrentState            = SERVICE_STOPPED;
    NTBServiceStatus.dwWin32ExitCode           = NO_ERROR;
    NTBServiceStatus.dwServiceSpecificExitCode = 0;
    NTBServiceStatus.dwCheckPoint              = 0;
    NTBServiceStatus.dwWaitHint                = 0;

    SetServiceStatus( NTBServiceHandle, &NTBServiceStatus );
    LeaveCriticalSection( &SCMCrtSec );

    // Flush all file buffers
    //
    _flushall();

    ExitProcess( 0 );
}


// ============================== get_last_error_str =========================
//
// This function returns the Operating System message text and length
// associated with the error value sent to it.
//
//      Inputs:
//              iOSerror = value of message to be returned
//
//      Outputs:
//              pointer to message string (NULL if message not found)
//
char * get_last_error_str()
{
    static char * szBuffer = NULL;
    DWORD dwLastError = GetLastError();

    if( szBuffer )
        LocalFree( szBuffer );

    szBuffer = NULL;

    //  Attempt retrieving the message from system resource table
    //
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM    |
                   FORMAT_MESSAGE_ALLOCATE_BUFFER,
                   NULL,
                   dwLastError,
                   (DWORD)GetSystemDefaultLangID(),
                   (LPSTR)&szBuffer,
                   255,            // maximum message length allowed
                   (LPVOID)NULL );
    return szBuffer;
}
