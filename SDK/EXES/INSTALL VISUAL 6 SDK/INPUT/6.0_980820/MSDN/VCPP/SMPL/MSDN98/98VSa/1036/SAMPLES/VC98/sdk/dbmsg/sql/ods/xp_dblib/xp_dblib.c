//	This is an example of an extended procedure DLL built with Open Data
//	Services. The functions within the DLL can be invoked by using the extended
//	stored procedures support in SQL Server.  To register the functions 
//	and allow all users to use them run the ISQL script XP_DBLIB.SQL.
//
//	For further information on Open Data Services refer to the Microsoft Open 
//	Data Services Programmer's Reference.
//
//  The extended procedures implemented in this DLL is:
//
//  XP_GETTABLE		Used to show the creation of a new connection to SQL Server
//					using DBLIB that is bound to the initial client connection;
//					retrieves all rows from the table <table_name>, which is passed 
//					as an input parameter				
//			

#define		DBNTWIN32
		
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include	<ctype.h>
#include	<time.h>
#include    <windows.h>

#include    <sqlfront.h>
#include    <sqldb.h>

#include    <srv.h>


// Miscellaneous defines
//
#define  XP_NOERROR		0
#define  XP_ERROR		1

#define  MAXLEN        255		// Maximum string length
#define  MAXNAME        31		// Maximum name length

// Extended procedure error codes
#define  SRV_MAXERROR           20000
#define	 GETTABLE_ERROR			SRV_MAXERROR + 1
#define	 REMOTE_FAIL				4002
#define	 REMOTE_MSG				SRV_MAXERROR + 3
 

// Stored Procedure information structure.
typedef struct xp_info {
    DBCHAR name[MAXNAME];   	// Extended procedure name
    DBCHAR usage[MAXLEN];   	// Usage string
} XP_INFO;


int err_handler();
int msg_handler();


// Array of Extended Stored Procedures supported by this DLL.
XP_INFO Xps[] = 
{

    "xp_gettable",
    "usage: xp_gettable <table_name>",
};


//
// XP_GETTABLE
//    Returns the result of the SQL statement
//		select * from <table_name>
//
// Parameters:
//    srvproc - the handle to the client connection that got the SRV_CONNECT.
//
// Returns:
//    XP_NOERROR
//    XP_ERROR
//
// Side Effects:
//    Returns messages and/or a result set to client. 
//


RETCODE xp_gettable(srvproc)
SRV_PROC *srvproc;
{

	DBPROCESS	*dbproc;			// DBPROCESS handle for the new connection
	LOGINREC	*loginrec;


    int			paramnum;
	int			bImpersonated;
	DBCHAR		table_name[MAXLEN];
	DBINT		paramtype;

	char		bindtoken[MAXLEN];
	char		SqlStmt[MAXLEN];

	short		cols;					// Data columns returned     
    int			i;						// Index variable            
    DBINT		rows;					// Number of rows sent       
    RETCODE		rc;						// Value returned from DB-Library calls      

    // Get number of parameters
    paramnum = srv_rpcparams(srvproc);

    // Check number of parameters
    if (paramnum != 1) {
        // Send error message and return
        srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0, "Error executing extended stored procedure: Invalid Parameter",
                    SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }

    // Check parameters for correct type
    paramtype = srv_paramtype(srvproc, paramnum);
    if (paramtype != SRVVARCHAR) {
        // Send error message and return
        srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0,
                    "Error executing extended stored procedure: Invalid Parameter Type",
                    SRV_NULLTERM);
	     // A SRV_DONE_MORE instead of a SRV_DONE_FINAL must complete the
	     // result set of an Extended Stored Procedure.
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
	return(XP_ERROR);
    }

	// Terminate parameter string with NULL
	sprintf(table_name, srv_paramdata(srvproc, 1));
	table_name[srv_paramlen(srvproc, 1)] = '\0';

	loginrec = dblogin();

	dbprocerrhandle(loginrec, (DBERRHANDLE_PROC)err_handler);
	dbprocmsghandle(loginrec, (DBMSGHANDLE_PROC)msg_handler);



	// Check for integrated security
	if (strcmp(srv_pfield(srvproc, SRV_LSECURE, (int *)NULL), "TRUE") == 0) {
		// Client has accessed using some form of integrated security
		// Impersonate client and set DBSETLSECURE flag
		
    	bImpersonated = srv_impersonate_client( srvproc );
		DBSETLSECURE(loginrec);
	}
	else {
    	// Client used standard login
    	// Set the user name, password, and application name for the remote

    	DBSETLUSER( loginrec, srv_pfield(srvproc, SRV_USER, (int *)NULL) );
    	DBSETLPWD( loginrec, srv_pfield(srvproc, SRV_PWD, (int *)NULL) );
	}


	DBSETLAPP (loginrec, "xp_gettable");

    // Try to open a connection to the local DBMS.
    // Since the servername parameter is set to NULL, the connection will be
    // opened to the local DBMS

//	dbproc = dbopen(loginrec, "server_name");
	dbproc = dbopen(loginrec, NULL);

	dbsetuserdata(dbproc, (VOID *)srvproc);

	//get the client session token
	srv_getbindtoken (srvproc, bindtoken);

	// put the SQL statement in the command buffer
	srv_bzero(SqlStmt, MAXLEN);
	sprintf (SqlStmt, "exec sp_bindsession \'%s\' ", bindtoken);

	dbcmd (dbproc, SqlStmt);
	dbsqlexec(dbproc);

	while ((rc = dbresults (dbproc)) == NO_MORE_RESULTS);

	// put the SQL statement in the command buffer
	sprintf (SqlStmt, "select * from %s ", table_name);
	rc=dbcmd (dbproc, SqlStmt);
	
	//send the command buffer to SQL Server for execution
	rc=dbsqlexec(dbproc);

	// Process the results
	while ((rc = dbresults (dbproc)) != NO_MORE_RESULTS)
	{

        // How many data columns are in the row?
		cols = dbnumcols (dbproc);

        // Build the row description for the client return.
		for (i = 1; i <= cols; i++) {
		
			// Call srv_describe for each column that will be sent back via ODS
			//		to the caller of the extended procedure
			srv_describe (srvproc, i, (DBCHAR *)dbcolname (dbproc, i), SRV_NULLTERM,
                   (DBINT)dbcoltype (dbproc, i), dbcollen (dbproc, i),
                   (DBINT)dbcoltype (dbproc, i), dbcollen (dbproc, i),
                   (BYTE *)NULL);

		}
		rows = 0;  // Initialize a counter for the row number.
		while (dbnextrow (dbproc) != NO_MORE_ROWS){

		// For each data field in the current row, fill the structure that will
		//    be sent back to the caller of the extended procedure
			for (i = 1; i <= cols; i++){
				srv_setcollen (srvproc, i, (short)dbdatlen (dbproc, i));
		        srv_setcoldata (srvproc, i, dbdata(dbproc, i));
			}

		// Send the data row back to SQL Server via ODS
			if (srv_sendrow (srvproc) == SUCCEED)
				rows++;                        // Go to the next row. 
		}
	}


	// Send the final done packet for the execution of the command  
	// batch. The previous batch was one that might have returned   
	// rows, so set the DONE status accordingly.                    
	if (rows > 0)
		srv_senddone (srvproc, SRV_DONE_COUNT | SRV_DONE_MORE,
              (DBUSMALLINT) 0, rows);
	else 
		srv_senddone (srvproc, SRV_DONE_MORE, (DBUSMALLINT) 0, (DBINT) 0);


    // Close the connection to SQL Server. 
    dbclose( dbproc );
    dbfreelogin( loginrec );

    // Revert back to SQL Server's user account
    //
    if( bImpersonated )
        srv_revert_to_self(srvproc);

	return(XP_NOERROR);

}


int err_handler(dbproc, severity, dberr, oserr, dberrstr, oserrstr)
DBPROCESS	*dbproc;
int			severity;
int			dberr;
int			oserr;
char		*dberrstr;
char		*oserrstr;
{

SRV_PROC *srvproc = (SRV_PROC *)NULL;

	srvproc = (SRV_PROC *)dbgetuserdata(dbproc);

	srv_sendmsg(srvproc, SRV_MSG_ERROR, (DBINT)REMOTE_MSG,
				(DBTINYINT)severity, (DBTINYINT)0, NULL, 0, 0, dberrstr,
					SRV_NULLTERM);

	if ((dbproc == NULL) || (DBDEAD(dbproc)))
		return(INT_EXIT);

	return(INT_CANCEL);
}


int msg_handler(dbproc, msgno, msgstate, severity, msgtext)
DBPROCESS	*dbproc;
DBINT		msgno;
int			msgstate;
int			severity;
char		*msgtext;
{

SRV_PROC *srvproc = (SRV_PROC *)NULL;

	srvproc = (SRV_PROC *)dbgetuserdata(dbproc);

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



