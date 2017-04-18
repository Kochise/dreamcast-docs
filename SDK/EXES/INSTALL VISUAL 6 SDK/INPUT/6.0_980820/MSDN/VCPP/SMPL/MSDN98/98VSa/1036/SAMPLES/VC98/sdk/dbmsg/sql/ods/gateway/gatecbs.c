// This file defines all the Open Data Services event handler functions for the
// GATEWAY application.
//

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>

// Define some user message codes.
//
#define SRV_MAXERROR    20000
#define RPC_UNKNOWN     SRV_MAXERROR + 1
#define COMPUTE_ROW     SRV_MAXERROR + 2
#define REMOTE_MSG      SRV_MAXERROR + 3
#define SEND_FAILED     SRV_MAXERROR + 4
#define BULK_CMD        "insert bulk"

// This error value must be sent back to the client in the event
// of a failure to login to the target database.  It is used in the
// init_remote() function below.
//
#define REMOTE_FAIL 4002

// Declare the structure to use for our private data area.
// It will be passed to the event handlers in the SRV_PROC structure.
// It contains information to make and use a connection to the remote
// DBMS -- in this case a SQL Server.
//
// A gateway to a non-SQL Server DBMS would contain a different structure.
//
#define MAXPARAMS   255
typedef struct remote_dbms {
    LOGINREC *login;    // The SQL Server login structure
    DBPROCESS *dbproc;  // The connection to the remote SQL Server
    BOOL bulk_mode;         // Flag indicating "bulk insert" mode
    short retparams[MAXPARAMS]; // tag return parameters
} REMOTE_DBMS;

// Declare the structure to be used for packing column metadata into the user datatype
// field.  This is a new feature of SQL Server 6.0.  The additional column metadata
// is available via dbcolinfo() in DB-Lib. 

typedef struct _typeinfo
{
    USHORT  typeid;			// used to hold the real user datatype
    USHORT  nullable:1, 	// TRUE/FALSE
	    case_sensitive:1,	// TRUE, FALSE
	    updateable:2,	// TRUE, FALSE, UNKNOWN
	    identity:1,		// TRUE/FALSE
	    spare1:1,		// spare fields
	    spare2:2,
	    spare3:8;
} TYPEINFO;

// The remote server name of this gateway
//
DBCHAR *remote_server = NULL;
SRV_PROC *Newsrvproc;       // Latest SRV_PROC allocated.

// Mutex used for init_remote()
HANDLE init_remote_mutex = 0;

int dbcolntype(DBPROCESS *dbproc, int column);

int attn_handler(SRV_PROC *srvproc);

int chk_err(SRV_SERVER *server, SRV_PROC *srvproc, int srverror,
            BYTE severity, BYTE state, int oserrnum, DBCHAR *errtext,
            int errtextlen, DBCHAR *oserrtext, int oserrtextlen);

int init_remote(SRV_PROC *srvproc);

int init_server(SRV_SERVER *server);

int rpc_execute(SRV_PROC *srvproc);

int exit_remote(SRV_PROC *srvproc);

int lang_execute(SRV_PROC *srvproc);

int handle_results(DBPROCESS *rmtproc, SRV_PROC *srvproc);

int remotemsgs(DBPROCESS *dbproc, DBINT msgno, INT msgstate,
               INT severity, LPCSTR msgtext, LPCSTR srvname, LPCSTR procname,
					DBUSMALLINT line);

int remoteerr(DBPROCESS *dbproc, INT severity, INT dberr, INT oserr,
              LPCSTR dberrstr, LPCSTR oserrstr);

void set_remote_server_name(char *name);

//
// This section defines the "call-back" functions supplied to the gateway
// application.
//
#pragma check_stack( off )  // turn off stack checking

//
// SET_REMOTE_SERVER_NAME
//
//     This function sets the name of the remote server.
//
// Parameters:
//     name - Pointer to name of server.
//
// Returns:
//     none
//
void set_remote_server_name(name)
char *name;
{
    remote_server = name;
}

//
// INIT_SERVER
//     Initialize the server on a SRV_START event.
//     Event handlers for the server are installed.
//
// Parameters:
//     server - Pointer to SRV_SERVER structure
//
// Returns:
//     SRV_CONTINUE
//
int init_server(server)
SRV_SERVER *server;
{
    char log_buffer[256];

    // When we get a connection request from a client, we want to
    // call "init_remote()" to make a connection to the remote
    // server.
    //
    srv_handle(server, (DBINT)SRV_CONNECT, init_remote);

    // When the client issues a language request, call
    // "lang_execute()" to send the SQL statement to the remote DBMS.
    //
    srv_handle(server, (DBINT)SRV_LANGUAGE, lang_execute);

    // When the client issues an RSP, call "rpc_execute()"
    // to send the RSP to the remote DBMS (the SQL Server).
    //
    srv_handle(server, (DBINT)SRV_RPC, rpc_execute);

    // When a disconnect request is issued, call "exit_remote()"
    // to close the connection to the remote DBMS.
    //
    srv_handle(server, (DBINT)SRV_DISCONNECT, exit_remote);

    // Install the handler that will be called when the
    // gateway receives an attention from one of its
    // clients. 
    //
    srv_handle(server, (DBINT)SRV_ATTENTION, attn_handler);

	 // Initialize dblib and configure for 100 connections
	 //
	 dbinit();
	 dbsetmaxprocs(100);

    // Now we'll install the message and error handlers for any
    // messages from the remote DBMS.
    //
    dberrhandle(remoteerr);
    dbmsghandle(remotemsgs);

	 // Create mutex to serialize init_remote
	 //
	 init_remote_mutex = CreateMutex(NULL, FALSE, NULL);

    //  Log Server information to log file
    //
    sprintf(log_buffer, "Client connections allowed = %s",
            srv_sfield(server, SRV_CONNECTIONS, (int *)NULL));

    srv_log(server, FALSE, log_buffer, SRV_NULLTERM);
    printf("%s\n", log_buffer);

    return(SRV_CONTINUE);
}

// INIT_REMOTE
//    Event handler for a SRV_CONNECT event.
//    A connection is made to the remote DBMS.
//
//    In this example program, the connection is to a SQL Server.
//    If using a non-SQL Server remote DBMS, the connection code
//    would be different, but would probably still occur here.
//
// Parameters:
//      srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//     SRV_CONTINUE
//
// Side Effects:
//     If the connection to the remote dbms cannot be made, then issue
//     a SRV_DISCONNECT request.
//
//
int init_remote(srvproc)
SRV_PROC *srvproc;
{
	 char *string;
	 int len;
    REMOTE_DBMS *remote;    // the private data area to keep
                                // track of the remote DBMS
                                // connection.
	BOOL	bImpersonated;

    // Set Newsrvproc.  This is used if we get an error on
    // the open from DBLIB.  Since there isn't a dbproc,
    // it is clear which srvproc to send the msg back on when the
    // DBLIB error-handler gets called.
    //
    // First lock out any other threads trying to connect using this same
    // function.
    //
    WaitForSingleObject(init_remote_mutex, INFINITE);

    Newsrvproc = srvproc;

	 
	 if (SRV_TDSVERSION(srvproc) != SRV_TDS_6_0) 	 	
	 {
		// Send a message to the client that they must be 4.2 or 6.0 clients.  
		// 4.2 client could be supported by 
		// converting all decimal/numeric values to float before sending to
		// client, and omiting the column metadata packed into srv_setutype in 
		// the handle_results() function.
		//
		srv_sendmsg(srvproc, 
					SRV_MSG_ERROR, 
					(DBINT)REMOTE_FAIL, 
					(DBTINYINT)0,
					(DBTINYINT)0, 
					NULL, 
					0, 
					0, 
					"Gateway sample application only supports version 6.0 clients.",
					SRV_NULLTERM);

		// Now allow other threads to enter this function.
		//
	   ReleaseMutex(init_remote_mutex);
		return(SRV_DISCONNECT);
    }

    // Allocate a REMOTE_DBMS information structure.
    //
    remote = (REMOTE_DBMS *)srv_alloc((DBINT)sizeof(*remote));

    // Try to open a connection to the remote DBMS.
    //
    if (remote == NULL) {
        // Send a message to the client that
        // the remote connection failed.
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_FAIL, (DBTINYINT)0,
                    (DBTINYINT)0, NULL, 0, 0,
                    "Login to remote DBMS failed (srv_alloc).", SRV_NULLTERM);
		 ReleaseMutex(init_remote_mutex);
        return(SRV_DISCONNECT);
    }

    // Set "bulk insert" mode flag to false.
    //
    remote->bulk_mode = FALSE;

    // Allocate the LOGINREC structure used to make connections to the
    // remote server. Open the connection in the SRV_CONNECT handler.
    //
    remote->login = dblogin();

    if (remote->login == NULL) {
        // Send a message to the client that the
        // remote connection failed.
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_FAIL, (DBTINYINT)0,
                    (DBTINYINT)0, NULL, 0, 0,
                    "Login to remote DBMS failed (dblogin).", SRV_NULLTERM);

        // Deallocate the remote structure and set the user data
        // pointer in "srvproc" to null so that the disconnect
        // handler won't try to disconnect from the remote dbms.
        //
        srv_free(remote);
		 ReleaseMutex(init_remote_mutex);
        return(SRV_DISCONNECT);
    }
    remote->dbproc = (DBPROCESS *)NULL;

    // Set the user name, password, and application name for the remote DBMS.
    //
    DBSETLUSER(remote->login, srv_pfield(srvproc, SRV_USER, (int *)NULL));
    DBSETLPWD(remote->login, srv_pfield(srvproc, SRV_PWD, (int *)NULL));
    DBSETLAPP(remote->login, srv_pfield(srvproc, SRV_APPLNAME, (int *)NULL));
    DBSETLNATLANG(remote->login, srv_pfield(srvproc, SRV_NATLANG, (int *)NULL));

	// following will let us pass decimal data back to client
	DBSETLVERSION(remote->login, DBVER60);

	//if client requested a trusted connection, gateway must do so too
	if (srv_pfield(srvproc, SRV_LSECURE, (int *)NULL) == "TRUE")
		DBSETLSECURE(remote->login);

	// Even if client hasn't explicitly requested a trusted connection, he may be
	// using integrated security if the server is set to mixed or integrated mode.
	// To handle this case, always tryy to impersonate the client.

	bImpersonated = srv_impersonate_client(srvproc);

    // See if client has set Bulk Copy flag
    //
    if (strcmp(srv_pfield(srvproc, SRV_BCPFLAG, (int *)NULL), "TRUE") == 0)
        BCP_SETL(remote->login, TRUE);
    else
        BCP_SETL(remote->login, FALSE);

    // If no server name was specified as a parameter to the main program,
    // then assume that the name is coming from the client.
    //
    if (remote_server == NULL || remote_server[0] == '\0') {
        remote_server = srv_pfield(srvproc, SRV_HOST, (int *)NULL);
    }
   
    // Try to open a connection to the remote DBMS.
    //
    if ((remote->dbproc = dbopen(remote->login,
                                 remote_server)) == (DBPROCESS *)NULL) {

			// Send a message to the client that
			// the remote connection failed.
			//
			srv_sendmsg(srvproc, 
					SRV_MSG_ERROR, 
					(DBINT)REMOTE_FAIL, 
					(DBTINYINT)0,
					(DBTINYINT)0, 
					NULL, 
					0, 
					0, 
					"Login to remote DBMS failed (dbopen).",
					SRV_NULLTERM);

        // Deallocate the remote structure and set the user data
        // pointer in "srvproc" to null so that the disconnect
        // handler won't try to disconnect from the remote DBMS.
        //
        srv_free(remote);
        srv_setuserdata(srvproc, (BYTE *)NULL);
	 	ReleaseMutex(init_remote_mutex);
		if( bImpersonated )
        	srv_revert_to_self(srvproc);
        return(SRV_DISCONNECT);
    } else {
        // Connection to the remote DBMS successful.  Save
        // remote data structure in the "srvproc" so it will be
        // available to the other handlers. We'll also map the remote
        // DBMS connection to our "srvproc".
        //
        srv_setuserdata(srvproc, (VOID *)remote);
        dbsetuserdata(remote->dbproc, (VOID *)srvproc);

    }

	 ReleaseMutex(init_remote_mutex);

	// if currently running in user context, don't need to any more
	if( bImpersonated )
       	srv_revert_to_self(srvproc);

    // Display connect info on console
    //
	 string = srv_pfield(srvproc, SRV_CPID, &len);
    string[len] = '\0';
	 printf("\nClient process ID: %s\n", string);

    string = srv_pfield(srvproc, SRV_USER, &len);
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

    return(SRV_CONTINUE);
}

//
// LANG_EXECUTE
//     Execute a client language request on the remote dbms.
//     Any results from the remote dbms are passed back to the client.
//
//  Parameters:
//     srvproc -  process handle to the current client connection.
//
// Returns:
//     SRV_CONTINUE
//
int lang_execute(srvproc)
SRV_PROC *srvproc;
{
    REMOTE_DBMS *rmt_dbms;  // the remote database pointer
    DBPROCESS *rmtproc; // our DBPROCESS pointer
    DBCHAR *query;      // pointer to language buffer
    int query_len;          // length of query
    int status;             // status of dblib calls

    // Get the remote dbms pointer we saved in the srvproc via
    // srv_setuserdata.
    //
    rmt_dbms = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    // Get the pointer to the remote DBPROCESS
    //
    rmtproc = rmt_dbms->dbproc;

    // Get the pointer to the client language request command buffer.
    //
    query = srv_langptr(srvproc);

    // See if the previous command was a "bulk insert" command
    //
    if (rmt_dbms->bulk_mode) {

        // Get length of the SQL command.
        //
        query_len = srv_langlen(srvproc);

        // If length of data is zero, then send a zero length buffer
        // to the destination SQL Server.  This is required in order to
        // signal the SQL Server that no more data follows.
        //
        if (query_len == -1L)
            query_len = 0L;

        // Place buffer into target SQL server's buffer.  Use
        // dbfcmd() to pass all binary data from the language buffer on to
        // the SQL Server.
        //
        status = dbfcmd(rmtproc, query, query_len);

        rmt_dbms->bulk_mode = FALSE;
    } else {
        // Let's check for "insert bulk" request
        //
        if (srv_langlen(srvproc) > (sizeof(BULK_CMD) - 1))
            if (strnicmp(query, BULK_CMD, (sizeof(BULK_CMD) - 1)) == 0)
                rmt_dbms->bulk_mode = TRUE;

            // Place buffer into target SQL server's buffer.
            //
            status = dbcmd(rmtproc,
            query);
    }

    // If previous DBLIB call successful, send command buffer to SQL Server.
    //
    if (status == SUCCEED) {    // if previous DBLIB call successful
        status = dbsqlexec(rmtproc);
    }
    if (!SRV_GOT_ATTENTION(srvproc) && (status == SUCCEED)) {
        //
        // Get the remote dbms results and pass them back to
        // client.
        //
        handle_results(rmtproc, srvproc);
    } else {
        //
        // If an attention event was issued or the dbsqlexec failed,
        // acknowledge with senddone.
        //
        if (DBDEAD(rmtproc)) {
            printf("thread shutting down");
            srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_FAIL,
                        (DBTINYINT)23, (DBTINYINT)17, NULL, 0, 0, "Remote Server connection no longer active: \
                         thread shutting down"
                        , SRV_NULLTERM);
            srv_senddone(srvproc, SRV_DONE_FINAL | SRV_DONE_ERROR,
                         (DBUSMALLINT)0, (DBINT)0);
            srv_event(srvproc, SRV_DISCONNECT, NULL);
        } else {
            srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0, (DBINT)0);
        }
    }
    return(SRV_CONTINUE);
}

//
// RPC_EXECUTE
//     Execute a client RPC.
//
//     Note that in our example, the remote DBMS is an SQL Server.
//     If our remote DBMS was a foreign DBMS, the code to send
//     the query to the remote DBMS and receive remote results
//     would be different.  In this example, we'll just send
//     the rpc along to the SQL Server.
//
// Parameters:
//    srvproc - The Open Server process handle to use to send results to the
//               client.
//
// Returns:
//     SRV_CONTINUE
//
int rpc_execute(srvproc)
SRV_PROC *srvproc;
{
    DBPROCESS *rmtproc; // Our DBPROCESS pointer
    int i;                  // Index variable
    short params;
    short retparam;
    short *paramarray;
	DBCHAR complete_rpc_name[4 * (MAXNAME + 1)]; //database.owner.name;#
	DBCHAR *rpc_db;
	DBCHAR *rpc_owner;
	DBCHAR *rpc_name;
	int rpc_number;
	char rpc_number_char[17];
	DBCHAR *rpc_paramname;
	BYTE rpc_paramstatus;
	int rpc_paramtype;
	DBINT rpc_parammaxlen;
	DBINT rpc_paramlen;
	void *rpc_paramdata;
	DBNUMERIC  numeric;		//structure to hold numeric params

    rmtproc = ((REMOTE_DBMS *)srv_getuserdata(srvproc))->dbproc;
    paramarray = ((REMOTE_DBMS *)srv_getuserdata(srvproc))->retparams;	

	// initialize numeric structure
	memset (&numeric, 0, sizeof(DBNUMERIC));

   // Construct full RPC name and initialize the RPC to the remote DBMS.
   //
	memset (complete_rpc_name, 0, sizeof(complete_rpc_name));
	rpc_db = srv_rpcdb(srvproc, (int *)NULL);
	rpc_owner = srv_rpcowner(srvproc, (int *)NULL);
	rpc_name = srv_rpcname(srvproc, (int *)NULL);
	
	if (rpc_db != NULL) {
		strcat(complete_rpc_name,rpc_db);
		strcat(complete_rpc_name,".");
	};
	if (rpc_owner != NULL) {
		strcat(complete_rpc_name,rpc_owner);
		strcat(complete_rpc_name,".");
	};
	strcat(complete_rpc_name,rpc_name);

	rpc_number = srv_rpcnumber(srvproc);
	if (rpc_number > 0) {
    	strcat(complete_rpc_name,";");
		itoa(rpc_number,rpc_number_char,10);
		strcat(complete_rpc_name, rpc_number_char);
	};
	
	dbrpcinit(rmtproc, complete_rpc_name, (DBUSMALLINT)srv_rpcoptions(srvproc));

    // Set up any RPC parameters.
    //
    params = srv_rpcparams(srvproc);
    retparam = 1;

    for (i = 1; i <= params; i++) {
		rpc_paramname = srv_paramname(srvproc, i, (int *)NULL);
	    if (!strlen(rpc_paramname)) 
			 rpc_paramname = NULL;
       	rpc_paramstatus = (BYTE)srv_paramstatus(srvproc, i);
       	rpc_paramtype = srv_paramtype(srvproc, i);
       	rpc_parammaxlen = srv_parammaxlen(srvproc, i);
		rpc_paramlen = srv_paramlen(srvproc, i);
       	rpc_paramdata = srv_paramdata(srvproc, i);

		//  DB-Lib requires maxlen of -1 for fixed-length datatypes, but ODS doesn't
		// always return this.   So set it.
	    switch (rpc_paramtype)
    	{
			case SQLDECIMAL:
			case SQLNUMERIC:
			case SQLBIT:
			case SQLINT1:
			case SQLINT2:
			case SQLINT4:
			case SQLFLT4:
			case SQLDATETIM4:
			case SQLMONEY4:
			case SQLMONEY:
			case SQLDATETIME:
			case SQLFLT8:
	    		rpc_parammaxlen = -1;
	    		break ;
			default:
	    		break ;
		}

		// Special handling for decimal types.  DB-Lib treats them as fixed length datatypes
		// that are the full size of a DBNUMERIC.  ODS uses variable-length numeric data
		// and only gives the exact bytes needed to represent the number 

	    switch (rpc_paramtype)
    	{
			case SQLDECIMAL:
			case SQLNUMERIC:
				memset (&numeric, 0, sizeof(DBNUMERIC));
				memmove(&numeric, rpc_paramdata, rpc_paramlen);
				rpc_paramdata = &numeric;
				// ODS says null numeric values have a length of 2, dblib expects them to be 0
				if (rpc_paramlen == 2) 
					rpc_paramlen = 0;
				break;
			default:
				break;
		}
		
		dbrpcparam(rmtproc,rpc_paramname,rpc_paramstatus,rpc_paramtype, 
					 rpc_parammaxlen,rpc_paramlen, rpc_paramdata);

        // The current rpc may have three parameters, but only the
        // first and third are return parameters.  This means that
        // dbnumrets() returns two parameters, not three.  The first
        // call to dbretdata() referes to the rpc's first parameter,
        // and the second call to dbretdata() refers to the rpc's
        // third parameter.  To handle this, we map each return
        // parameter to its original parameter so we can later
        // reset the return value of the correct return parameters
        // in "handle_results()".
        //
        if ((BYTE)srv_paramstatus(srvproc, i) & SRV_PARAMRETURN) {
            paramarray[retparam] = i;
            retparam++;
        }
    }

    // Send the RPC to the remote DBMS.
    //
    dbrpcsend(rmtproc);
    dbsqlok(rmtproc);

    // Now get the remote DBMS results and pass them back to
    // Open Server client.
    //
    handle_results(rmtproc, srvproc);
    return(SRV_CONTINUE);
}

//
// HANDLE_RESULTS
//     Once a command has been sent to the remote DBMS by the
//     SRV_LANGUAGE  handler, this routine processes the results
//     and passes them back to the client.
//
// Parameters:
//     rmtproc - The DBPROCESS handle to the remote DBMS.
//     srvproc - The process handle to use to send results to the client.
//
// Returns:
//     SUCCEED or FAIL.
//
int handle_results(rmtproc, srvproc)
DBPROCESS *rmtproc;
SRV_PROC *srvproc;
{
    short cols;             // data columns returned
    int i;                  // index variable
    BOOL results_sent;      // number of result sets sent
    BOOL gotcompute;        // COMPUTE row indicator
    short *paramarray;
    RETCODE returnvalue;    // value returned from dblib call
	DBCOL	dbcol;			// column metadata structure
	TYPEINFO	typeinfo;	// used to send metadata in usertype 
	int dbcolsize;			// size of DBCOL struct
	BOOL bRowsAffected;		// was command one that affects or returns rows
	DBINT nRowsAffected;	// result of DBCOUNT
	DBNUMERIC numeric;		// structure to hold precision and scale for numeric cols	
	short collen = 0;		// holder for col data length
	DBINT	retlen;			// for sending output params
	DBINT	rpc_paramtype;	// for sending output params

    results_sent = FALSE;
    gotcompute = FALSE;
	bRowsAffected = FALSE;
	nRowsAffected = 0;

    paramarray = ((REMOTE_DBMS *)srv_getuserdata(srvproc))->retparams;

	// initialize the DBCOL structure
	dbcolsize = sizeof(DBCOL);	
	memset(&dbcol, 0, dbcolsize);
	dbcol.SizeOfStruct = dbcolsize;

	// initialize numeric structure
	memset (&numeric, 0, sizeof(DBNUMERIC));

    // Process the results from the remote DBMS.
    // Since a command may consist of multiple commands or a single
    // command that has multiple sets of results, we'll loop through
    // each results set.
    //
    while (TRUE) {

        returnvalue = dbresults(rmtproc);
        if (returnvalue == NO_MORE_RESULTS) {
            break;
        }

        // Check to see if the client has sent an attention event.  If
        // so, simply discard data from remote server
        //
        if (SRV_GOT_ATTENTION(srvproc)) {
    		dbcancel(rmtproc);	// See attn_handler comments
        	continue;
        }

        //
        // If this is the second time through the loop,
        // send a completion message to the client
        // for the previous results sent.
        //
        if (results_sent == TRUE) {

            // If there are some COMPUTE rows, send a message
            // to the client that Data Services Library doesn't yet handle them.
            //
            if (gotcompute == TRUE) {
                gotcompute = FALSE;
                srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)COMPUTE_ROW,
                            (DBTINYINT)0, (DBTINYINT)0, NULL, 0, 0,
                          "Data Services library can't handle COMPUTE rows.",
                            SRV_NULLTERM);
            }

            // If the previous batch was one that may
            // have affected rows, set the DONE status
            // accordingly.
            //
            if (bRowsAffected) {
                srv_senddone(srvproc, SRV_DONE_MORE | SRV_DONE_COUNT,
                             (DBUSMALLINT)0, nRowsAffected);
            } else
                srv_senddone(srvproc, SRV_DONE_MORE, (DBUSMALLINT)0,
                            nRowsAffected);

        }

        // How many data columns are in the row?
        // Non-"select" statements will have 0 columns.
        //
        cols = dbnumcols(rmtproc);

        // Build the row description for the client return.
        //
        for (i = 1; i <= cols; i++) {


            //  Call "srv_describe()" for each column in the row.
			//  dbcolntype is used to preserve the nullability information
			//	that is lost by dbcoltype.
            //
            srv_describe(srvproc, i, (DBCHAR *)dbcolname(rmtproc, i), SRV_NULLTERM,
                         (DBINT)dbcolntype(rmtproc, i), dbcollen(rmtproc, i),
                         (DBINT)dbcolntype(rmtproc, i), dbcollen(rmtproc, i),
                         (BYTE *)NULL);

			// Now pack additional col metadata into the usertype
			// Note this code below does "SQL 6.0" style packing used by DB-Lib, 
			// and the ODS gateway ODBC driver if the resources DLL is set to use it
			// "ODBC-style" metadata encoding uses a different structure, not shown here.
			// See ODS Programmer's Reference for more details.
			// get column metadata
			dbcolinfo(rmtproc, CI_REGULAR, i, 0, &dbcol);

			// reset to 0
			*(DBINT*)&typeinfo = 0;

			/* Set user type */
			if (dbcol.UserType < 0)
				typeinfo.typeid = 0;
			else
				typeinfo.typeid = (USHORT) dbcol.UserType;

			if (dbcol.Identity == TRUE)
			   	typeinfo.identity = TRUE;

			if (dbcol.Null == TRUE)
			   	typeinfo.nullable = TRUE;
			else if (dbcol.Null == DBUNKNOWN)
			   	typeinfo.nullable = DBUNKNOWN;

			if (dbcol.CaseSensitive == TRUE)
			   	typeinfo.case_sensitive = TRUE;
			else if (dbcol.CaseSensitive == DBUNKNOWN)
			   	typeinfo.case_sensitive = DBUNKNOWN;

			if (dbcol.Updatable == TRUE)
				typeinfo.updateable = TRUE;
			else if (dbcol.Updatable == DBUNKNOWN)
				typeinfo.updateable = DBUNKNOWN;
			
			srv_setutype(srvproc, i, *(DBINT*)&typeinfo);

			// If column is a decimal or numeric, need to setup a valid precision and
			// scale.  Normally this would be provided by dbdata() prior to srv_sendrow().
			// But if there are no rows in the result set, srv_sendrow() will not
			// be called, and ODS will send the header when srv_senddone() is called.
			if ((dbcol.Type == SQLNUMERIC) || (dbcol.Type == SQLDECIMAL))
				{
				numeric.precision = dbcol.Precision;
				numeric.scale = dbcol.Scale;
                srv_setcoldata(srvproc, i, &numeric);
				}
        }

        // Send each row from the remote DBMS to the client.
        //
        while (TRUE) {

            returnvalue = dbnextrow(rmtproc);
            if (returnvalue == NO_MORE_ROWS) {
                break;
            }

            // If it's not a regular row, it's a COMPUTE row.
            // This SQL extension is particular to Sybase
            // TRANSACT-SQL and is not yet supported.
            //
            if (DBROWTYPE(rmtproc) != REG_ROW) {
                gotcompute = TRUE;
                continue;
            } else
                gotcompute = FALSE;

            // The row description is built.  Move the
            // rows from the remote server to the client.
            //
            for (i = 1; i <= cols; i++) {
                srv_setcollen(srvproc, i, (collen = (short)dbdatlen(rmtproc, i)));
				// special handling for the srv_setcoldata pointer if the value is null numeric
				// dbdata does not point to a valid numeric structure in this case
				// so point instead to the numeric structure set up at srv_describe time
		 		if (  ((dbcoltype(rmtproc, i) == SQLDECIMAL) || (dbcoltype(rmtproc, i) == SQLNUMERIC))
		 			&& (collen == 0))
					{
					srv_setcoldata(srvproc, i, &numeric);
					}
				else
                	srv_setcoldata(srvproc, i, dbdata(rmtproc, i));				
            }

            // Check to see if the client has issued an attention event.
            // If so, discard data from the remote server.
            //
            if (SRV_GOT_ATTENTION(srvproc)) {
    			dbcancel(rmtproc);	// See attn_handler comments
                continue;
            }

			// Now put the row in the ODS output buffer
			srv_sendrow(srvproc);
        }
        // Check to see if any parameter were returned from
        // the remote DBMS.  If so, pass them through to the
        // client.
        for (i = 1; i <= dbnumrets(rmtproc); i++) {
            //
            // If the return parameters are a result of
            // an rpc, we used srv_paramset() to set the return
            // value.  If the return parameters are not the
            // result of an rpc, we use srv_returnval().
            //
			retlen = dbretlen(rmtproc, i);
			rpc_paramtype = dbrettype(rmtproc, i);

			// special handling for decimal types.  need to add 2 bytes for precision & scale
			// from what is returned by dbretlen
   			if ((rpc_paramtype == SQLNUMERIC)	|| 	(rpc_paramtype == SQLDECIMAL))
					retlen += 2;
																
            if (srv_rpcname(srvproc, NULL) != NULL) {
                //
                // The current rpc may have three parameters, but
                // only the first and third are return parameters.
                // This means that dbnumrets() returns two parameters,
                // not three.  The first call to dbretdata() refers to
                // the rpc's first parameter, and the second call to
                // dbretdata() refers to the rpc's third parameter.
                // To handle this, we map each return parameter to
                // its original parameter so we can later reset the
                // return value of the correct return parameters in
                // handle_results().
                //
                srv_paramset(srvproc, paramarray[i], dbretdata(rmtproc, i), retlen);
				
            } else {
                
                srv_returnval(srvproc, (DBCHAR *)dbretname(rmtproc, i), SRV_NULLTERM,
                              SRV_PARAMRETURN, rpc_paramtype,
                              retlen, retlen,dbretdata(rmtproc, i));


            }
        }
        // Check to see if we got a return status code from the
        // remote DBMS.  Pass it through to the client.
        //
        if (dbhasretstat(rmtproc))
           srv_sendstatus(srvproc, dbretstatus(rmtproc));

        // If the command was one where count is meaningful
        // send the srv_senddone message accordingly.
        //
		bRowsAffected = dbiscount(rmtproc);		
		nRowsAffected = DBCOUNT(rmtproc);
		
        // Set flag so that we will send a completion
        // message for the current set of results.
        //
        results_sent = TRUE;
    }

    // If there are some COMPUTE rows, send a message
    // to the client that Open Services Library doesn't handle them yet.
    //
    if (gotcompute == TRUE) {
        gotcompute = FALSE;
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)COMPUTE_ROW, (DBTINYINT)0,
                    (DBTINYINT)0, NULL, 0, 0,
                    "Data Services Library can't handle COMPUTE rows.",
                    SRV_NULLTERM);
    }

    // Send the final done packet for the execution of the command batch.
    //
    // If the previous batch was one that may
    // have affected rows, set the DONE status
    // accordingly.
    //
	if (bRowsAffected) {
    	srv_senddone(srvproc, SRV_DONE_FINAL | SRV_DONE_COUNT,
                    (DBUSMALLINT)0, nRowsAffected);
   	} else
       	srv_senddone(srvproc, SRV_DONE_FINAL, (DBUSMALLINT)0,
                	nRowsAffected);

    return(SUCCEED);
}

// EXIT_REMOTE
//     Handler for SRV_DISCONNECT events.
//     Closes remote DBMS connection if appropriate.
//
//    The code to disconnect from the remote DBMS is SQL Server specific. If
//    using a non-SQL Server database, the disconnect from the  remote database
//    would be different but would probably still occur here.
//
// Parameters:
//     srvproc - the handle to the client connection
//
// Returns:
//     SRV_CONTINUE
//
int exit_remote(srvproc)
SRV_PROC *srvproc;
{
	 char *string;
	 int len;
    REMOTE_DBMS *remote;    // pointer to target connect structure

    remote = (REMOTE_DBMS *)srv_getuserdata(srvproc);

    // Is there a REMOTE_DBMS structure to clean-up?
    //
    if (remote != (REMOTE_DBMS *)NULL) {

        // Is there a live dbproc?
        //
        if (remote->dbproc != (DBPROCESS *)NULL) {
            dbclose(remote->dbproc);
        }
        dbfreelogin(remote->login);
        srv_free(remote);
    }

	 // Display info on console
	 //
	 string = srv_pfield(srvproc, SRV_CPID, &len);
    string[len] = '\0';
  	 printf("\nClient connection closed, process ID: %s\n", string);

    return(SRV_CONTINUE);
}

// CHK_ERR
//     Print out errors.
//
// Parameters:
//     server        - pointer to gateway server structure.
//     srvproc      - pointer to client connection structure
//     errornum     - error number.
//     severity     - error severity.
//     state         - error state.
//     oserrnum     - operating system error number, if any.
//     errtext      - the text of the error message.
//     errtextlen   - length of the errtext message
//     oserrtext    - the text of the operating system error message.
//     oserrtextlen - length of the errtext message
//
// Returns:
//     SRV_CONTINUE, SRV_CANCEL, or SRV_EXIT
//

RETCODE chk_err(server, srvproc, errornum, severity, state, oserrnum, errtext,
                errtextlen, oserrtext, oserrtextlen)
SRV_SERVER *server;
SRV_PROC *srvproc;
int errornum;
BYTE severity;
BYTE state;
int oserrnum;
DBCHAR *errtext;
int errtextlen;
DBCHAR *oserrtext;
int oserrtextlen;
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
		else	// If application not initialized log to screen
    		printf ("%s\n", log_buffer);
    }

    // Is this a fatal error for the server?
    //
    if (severity >= SRV_FATAL_SERVER) {
        sprintf(log_buffer, 
		  			"SERVER: FATAL SERVER ERROR: errornum = %d, severity = %d, state = %d: %s.",  
					 errornum, severity, state, error);
        if (server)	
			srv_log(server, TRUE, log_buffer, SRV_NULLTERM);
		else	// If application not initialized log to screen
    		printf ("%s\n", log_buffer);
        return(SRV_EXIT);
    } else {
        //
        // Did the "srvproc" get a fatal error?
        //
        if (severity >= SRV_FATAL_PROCESS) {
            sprintf(log_buffer,
						  "SERVER: FATAL CONNECT ERROR: errornum = %d, severity = %d, state = %d: %s.",
                     errornum, severity, state, error);
        	if (server)	
				srv_log(server, TRUE, log_buffer, SRV_NULLTERM);
			else	// If application not initialized log to screen
    			printf ("%s\n", log_buffer);	
            return(SRV_CANCEL);
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
		else	// If application not initialized log to screen
    		printf ("%s\n", log_buffer);	
    }
    return(SRV_CONTINUE);
}

// REMOTEMSGS
//     DBLIB calls this routine when any messages are received
//     from the remote DBMS. It gets the remote message information and
//     sends it back to the client as a message.
//
// Parameters:
//     dbproc    - The handler to the remote DBMS process that sent the message.
//     msgno     - The message number.
//     msgstate  - The message state.
//     severity  - The message severity.
//     msgtext   - The text of the message.
//     srvname   - The server name
//     procname  - The stored procedure name (if there was one)
//     line      - The line number of the procedure
//
//     The following three parameters are available in TDS4.0 and above:
//
//     srvname  - The name of the server that sent the message.
//     procname - The procedure name, if any, of the remote DBMS command.
//     line  - The remote DBMS command buffer line to which the msg applies.
//
// Returns:
//     0
//

int remotemsgs(dbproc, msgno, msgstate, severity, msgtext, srvname, procname, line)
DBPROCESS *dbproc;
DBINT msgno;
INT msgstate;
INT severity;
LPCSTR msgtext;
LPCSTR srvname;
LPCSTR procname;
DBUSMALLINT line;
{
    SRV_PROC *srvproc;

    // If a remote DBMS error was received during the remote
    // open, the dbproc is NULL and a message is sent back on the
    // most recent srvproc.
    //
    if (dbproc == (DBPROCESS *)NULL) {
        srvproc = Newsrvproc;
    } else {
        if ((srvproc = (SRV_PROC *)dbgetuserdata(dbproc)) == NULL) {
            //
            // An error was received after the dbproc was assigned, but
            // before we were able to associate our srvproc.
            //
            srvproc = Newsrvproc;
        }
    }
    if (severity < 10) {    // if informational message

        srv_sendmsg(srvproc, SRV_MSG_INFO, msgno, (DBTINYINT)severity,
                    (DBTINYINT)msgstate, NULL, 0, 0, (DBCHAR *)msgtext, SRV_NULLTERM);
    	return(0);
    } 

	// Trap login fail message
	if (msgno == REMOTE_FAIL){
        // Send a message to the client that
        // the remote connection failed.
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)msgno, (DBTINYINT)severity,
                    (DBTINYINT)msgstate, NULL, 0, 0,
                    "Login to remote DBMS failed (dbopen).", SRV_NULLTERM);
	}

	// must be an error message
    srv_sendmsg(srvproc, SRV_MSG_ERROR, msgno, (DBTINYINT)severity,
    	(DBTINYINT)msgstate, NULL, 0, 0, (DBCHAR *)msgtext, SRV_NULLTERM);

    return(0);
}

// REMOTEERR
//     This is the handler for error messages from the remote DBMS, in this
//     case DBLIB.  It gets called whenever a DBLIB error occurs.  It takes
//     the error message and passes it back to the client.
//
// Parameters:
//     dbproc - The process handle for the remote DBMS.
//     severity - The severity of the error.
//     dberr - The DBLIB error number.
//     oserr - The operating system error, if any.
//     dberrstr - The text of the DBLIB error.
//     oserrstr - The text of operating system error, if any.
//
// Returns:
//     INT_EXIT to exit the program.
//     INT_CANCEL to cause a FAIL return from the DBLIB routine that got
//     the error.
//
int remoteerr(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS *dbproc;
INT severity;
INT dberr;
INT oserr;
LPCSTR dberrstr;
LPCSTR oserrstr;
{
    SRV_PROC *srvproc = (SRV_PROC *)NULL;

    // If the DBLIB process is dead or we get a DBLIB error SQLESMSG
	// ("General SQL Server Error:...") then simply ignore it.  The error
    // message has already been sent to the client.
    //
    if (dberr == SQLESMSG) {
        return(INT_CANCEL);
    }

    //
    // A remote DBMS error may have been issued during the remote
    // open. In this case, the dbproc will be NULL and a message
    // will be sent on the most recent srvproc.
    //
    if (dbproc == (DBPROCESS *)NULL) {
        srvproc = Newsrvproc;
    } else {
        if ((srvproc = (SRV_PROC *)dbgetuserdata(dbproc)) == NULL) {
            // An error was issued after the dbproc was assigned but before
            // we were able to associate our srvproc.
            //
            srvproc = Newsrvproc;
        }
    }

	// Trap connection failure error
	if (dberr == SQLECONN){
        // Send a message to the client that
        // the remote connection failed.
        //
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_FAIL, (DBTINYINT)severity,
                    (DBTINYINT)0, NULL, 0, 0,
                    "Unable to establish connection to remote DBMS (dbopen).", SRV_NULLTERM);

        return(INT_CANCEL);
	}

    //
    // Send error message to client.
    //
    srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_MSG,
                (DBTINYINT)severity, (DBTINYINT)0, NULL, 0, 0,
					 (DBCHAR *)dberrstr, SRV_NULLTERM);

    if (oserr != DBNOERR) {
        srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_MSG,
                    (DBTINYINT)severity, (DBTINYINT)0, NULL, 0, 0,
						  (DBCHAR *)oserrstr, SRV_NULLTERM);
    }
    return(INT_CANCEL);
}

// ATTN_HANDLER
//     This is an event handler that will be called when the gateway receives
//     an attention from a client.
//
// Parameters:
//     srvproc - Pointer to the client connection structure
//               receiving the attention.
//
// Returns:
//     SRV_CONTINUE
//
int attn_handler(srvproc)
SRV_PROC *srvproc;
{
	// Open Data Services NT receives client attention events asynchronously.
  	// Being handle_results may be calling dbresults or dbnextrow, we can not
	// process the attention with the dbcancel call here. Instead dbcancel
	// will be called after the attention has been detected using 
	// SRV_GOT_ATTENTION.

    return(SRV_CONTINUE);
}


#pragma check_stack()   // set stack checking to its default setting
