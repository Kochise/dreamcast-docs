// This is an example of an extended procedure DLL built with Open Data
// Services. The functions within the DLL can be invoked by using the extended
//	stored procedures support in SQL Server.  To register the functions 
// and allow all users to use them run the ISQL script XP_ODBC.SQL.
//
// For further information on Open Data Services refer to the Microsoft Open 
// Data Services Programmer's Reference.
//
//  The extended procedures implemented in this DLL is:
//
//  XP_GETTABLE		Used to show the creation of a new connection to SQL Server
//					using ODBC that is bound to the initial client connection
//			

#define		DBNTWIN32
		
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include	<ctype.h>
#include	<time.h>
#include    <windows.h>
#include    <sql.h>
#include    <sqlext.h>
#include    <srv.h>
#include    <odbcss.h>


// Miscellaneous defines
//
#define XP_NOERROR		0
#define XP_ERROR		1

#define MAXNAME			31	// Maximum extended procedure name length
#define MAXLEN			80	// Maximum string length
#define COMMAND_PARAM	1	// Command Parameter
#define OUTPUT_PARAM	2	// Command Parameter

#define	SQLCHAR 0x2f		//used by srv_describe


// Extended procedure error codes
//
#define SRV_MAXERROR		20000
#define GETTABLE_ERROR	SRV_MAXERROR + 1
#define	COMPUTE_ROW			SRV_MAXERROR + 8
#define	REMOTE_MSG			SRV_MAXERROR + 9
#define	SEND_FAILED			SRV_MAXERROR + 10


#define REMOTE_FAIL				4002

// #define Xpcnumber sizeof(Xps) / sizeof(XP_INFO)

#define NAME_LEN	30
#define MAXCOLS		30

// Stored Procedure information structure.
//
typedef struct xp_info {
    DBCHAR name[MAXNAME];   	// Extended procedure name
    DBCHAR usage[MAXLEN];   	// Usage string
} XP_INFO;

typedef BYTE * dataptr ;

// Array of Extended Stored Procedures supported by this DLL.
//
XP_INFO Xps[] = 
{
    "xp_gettable",
//    "usage: xp_gettable <@pubs_table_name>",
    "usage: xp_gettable",
};

void handle_odbc_err(char *,	RETCODE ,DBINT ,HENV ,	HDBC ,	HSTMT ,	SRV_PROC *);


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

	HENV	henv		= SQL_NULL_HENV;
	HDBC 	hdbc		= SQL_NULL_HDBC;
	HSTMT	hstmt		= SQL_NULL_HSTMT;
	SWORD	ColNameLen[MAXCOLS];
	SDWORD	cbName		= SQL_NTS;
	UDWORD	FAR ColLen[MAXCOLS];
	UDWORD	FAR ColLenT[MAXCOLS];
	UCHAR	ColName[NAME_LEN];
	RETCODE	rc;
	SDWORD	nresultcols;			// number of result columns
	dataptr	data[MAXCOLS];
	DBINT	rows		=	0L;		// number of rows sent
	char	bindtoken[256];
    UWORD	i;						// Index variable         
	UCHAR FAR *	DSN		= "local";	// for integrated security to work you need to 
									//	   specify a local server in the ODBC setting
									//     in the Control Panel in Windows
	char	SqlStmt[500];
	int		bImpersonated;

	PTR			rgbDesc;			// pointer to storage for descriptor info
	SWORD		cbDescMax = 2550;	// max length of rgbDesc buffer
	SWORD FAR	pcbDesc;			// number of bytes returned in rgbDesc
	SDWORD FAR	pfdesc;				// pointer to storage info for numeric descriptor types
	SDWORD FAR	SqlType[MAXCOLS];	// storage info for SQL data types


	UCHAR FAR 	uid[50];
	UCHAR FAR 	pwd[50];



	int		paramnum;
	DBCHAR	table_name[500];
	DBINT	paramtype;

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
	

	// Allocate an ODBC environment handle
	rc = SQLAllocEnv(&henv);              // Environment handle 
	if (rc != SQL_SUCCESS) {
		handle_odbc_err("SQLConnect",
			rc, 
			(DBINT)REMOTE_FAIL,
			henv,
			hdbc, 
			hstmt, 
			srvproc);
		return(XP_ERROR);
    }

	// Allocate an ODBC connection handle
	rc = SQLAllocConnect(henv, &hdbc); // Connection handle 
	if (rc != SQL_SUCCESS) {
		handle_odbc_err("SQLConnect",
			rc, 
			(DBINT)REMOTE_FAIL,
			henv,
			hdbc, 
			hstmt, 
			srvproc);
		return(XP_ERROR);

	}

	// Check for integrated security
	if (strcmp(srv_pfield(srvproc, SRV_LSECURE, (int *)NULL), "TRUE") == 0) {
		// Client has accessed using some form of integrated security
		// Impersonate client and set SQL_INTEGRATED_SECURITY option
		
    	bImpersonated = srv_impersonate_client(srvproc);

		rc=SQLSetConnectOption(hdbc, SQL_INTEGRATED_SECURITY, SQL_IS_ON);

		// Connect to DSN using integrated security
		rc = SQLConnect(hdbc, DSN, SQL_NTS, NULL, SQL_NTS, NULL, SQL_NTS);

	}
	else {
    	// Client used standard login
    	// Set the user name, password, and application name for the remote
		sprintf(uid, srv_pfield(srvproc, SRV_USER, (int*)NULL));
		sprintf(pwd, srv_pfield(srvproc, SRV_PWD, (int*)NULL));
		rc = SQLConnect(hdbc, DSN, SQL_NTS, uid, SQL_NTS, pwd, SQL_NTS);

	}
	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
	{
		handle_odbc_err("SQLConnect",
			rc, 
			(DBINT)REMOTE_FAIL,
			henv,
			hdbc, 
			SQL_NULL_HSTMT, 
			srvproc);
		return(XP_ERROR);

	} 


	// Process data after successful connection 
	rc = SQLAllocStmt(hdbc, &hstmt); // Statement handle 
	if (rc != SQL_SUCCESS) {
		handle_odbc_err("SQLConnect",
			rc, 
			(DBINT)REMOTE_FAIL,
			henv,
			hdbc, 
			hstmt, 
			srvproc);
		return(XP_ERROR);
    }

	
	//get the client session token
	rc = srv_getbindtoken(srvproc, bindtoken);
	if (rc == FAIL){
		srv_sendmsg(srvproc, SRV_MSG_ERROR, GETTABLE_ERROR, SRV_INFO, (DBTINYINT)0,
                    NULL, 0, 0,
                    "Error with srv_getbindtoken",
                    SRV_NULLTERM);
        srv_senddone(srvproc, (SRV_DONE_ERROR | SRV_DONE_MORE), 0, 0);
		return(XP_ERROR);
	}

	// put the SQL statement in the command buffer
	sprintf (SqlStmt, "exec sp_bindsession \'%s\' ", bindtoken);

	rc=SQLExecDirect(hstmt, SqlStmt, SQL_NTS);
	if (!((rc == SQL_SUCCESS) ||(rc == SQL_SUCCESS_WITH_INFO)))
	{
		// if query failed, notify user & acknowledge with senddone.
		handle_odbc_err("SQLExecDirect",
			rc, 
			(DBINT)SEND_FAILED,
			henv,
			hdbc, 
			hstmt, 
			srvproc);
		return(XP_ERROR);
	}

	// SELECT the result set and bind its columns to local storage
	sprintf (SqlStmt, "SELECT * FROM  %s ", table_name);
	rc=SQLExecDirect(hstmt, SqlStmt, SQL_NTS);
	if (rc != SQL_SUCCESS) {
		handle_odbc_err("SQLExecDirect",
			rc, 
			(DBINT)SEND_FAILED,
			henv,
			hdbc, 
			hstmt, 
			srvproc);
		return(XP_ERROR);
    }
	
	// if returnvalue was successful, must have results rows
	SQLColAttributes(hstmt, 
			0, 
			SQL_COLUMN_COUNT, 
			rgbDesc, 
			cbDescMax,				// max length of rgbDesc buffer
			&pcbDesc,				// number of bytes returned in rgbDesc
			&nresultcols);
	
	// Build the column description for this results set.
	for (i = 1; i <= nresultcols; i++) 
	{
		// get the column description
		SQLColAttributes(hstmt, 
			i, 
			SQL_CA_SS_COLUMN_SSTYPE, 
			rgbDesc, 
			cbDescMax,					// max length of rgbDesc buffer
			&pcbDesc,					// number of bytes returned in rgbDesc
			&SqlType[i]);


		SQLColAttributes(hstmt, 
			i, 
			SQL_COLUMN_NAME, 
			&ColName[i],				// returned column name
			NAME_LEN,					// max length of rgbDesc buffer
			&ColNameLen[i],				// number of bytes returned in rgbDesc
 			&pfdesc);

		SQLColAttributes(hstmt, 
			i, 
			SQL_COLUMN_LENGTH, 
			rgbDesc, 
			cbDescMax,					// max length of rgbDesc buffer
			&pcbDesc,					// number of bytes returned in rgbDesc
			&ColLen[i]);				// returned column length
	
		// Over-write the column length returned by ODBC with the correct value
		//    to be used by ODS

		switch( SqlType[i] ){

			case SQLMONEY:				//money
			case SQLDATETIME:			//datetime
				ColLen[i] = 8;
				break;

			case SQLMONEYN:				//moneyn
				if (21 == ColLen[i])
					ColLen[i] = 8;
				else
					ColLen[i] = 4;
				break;
				
			case SQLDATETIMN:			//datetimn
				if (23 == ColLen[i])
					ColLen[i] = 8;
				else
					ColLen[i] = 4;
				break;
				
			case SQLNUMERIC:			//numeric
			case SQLNUMERICN:			//numericn
			case SQLDECIMAL:			//decimal
			case SQLDECIMALN:			//decimaln
				ColLen[i] = sizeof(DBNUMERIC);
				break;


			case SQLMONEY4:				//smallmoney
			case SQLDATETIM4:			//smalldatetime
				ColLen[i] = 4;
				break;

		}


		// allocate memory to hold each filed of data in a row
		data[i] = (dataptr) malloc(ColLen[i]);
		srv_bzero (data[i], ColLen[i] );

		
		// Bind column 
		SQLBindCol(hstmt, 
			i, 
			SQL_C_BINARY,			// no data conversion
			data[i], 				// will hold 'fetched' data
			ColLen[i], 				// max bytes to store in 'data'
			&ColLenT[i]);			// actual bytes stored by 'fetch'
	
		
		// Prepare structure that will be sent via ODS back to the caller of the 
		//		extended procedure
		srv_describe(srvproc, 
			i, 
			&ColName[i], 
			SRV_NULLTERM,
			SqlType[i],					// dest	data type 
			(DBINT) ColLen[i],			// dest data length
			SqlType[i], 				// source data type 
			(DBINT) ColLen[i],			// source data length
			(BYTE *)NULL);

	}

	// initialize the row counter
 	rows = 0;

	// get each row of data from ODBC until there are no more rows
	while((rc = SQLFetch(hstmt)) != SQL_NO_DATA_FOUND)
	{
		if (!((SQL_SUCCESS == rc) ||(SQL_SUCCESS_WITH_INFO == rc)))
		{
			handle_odbc_err("SQLExecDirect",
				rc, 
				(DBINT)SEND_FAILED,
				henv,
				hdbc, 
				hstmt, 
				srvproc);
			return(XP_ERROR);
		}

		// For each data field in the current row, fill the structure that will
		//    be sent back to the caller of the extended procedure
 		for (i = 1; i <= nresultcols; i++) 
		{
			if (SQL_NULL_DATA == ColLenT[i])
				ColLenT[i] = 0;
			srv_setcollen(srvproc, i, (int)ColLenT[i]);
			srv_setcoldata(srvproc, i, data[i]);
		}

		// Send the data row back to SQL Server via ODS
		if (srv_sendrow(srvproc) == SUCCEED)
			rows++;
	}


	// free the data buffers 
	for (i=1; i<=nresultcols; i++)
		(void)free(data[i]);
	
	// free handles
	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);


	if (rows > 0)
		srv_senddone(srvproc, SRV_DONE_MORE | SRV_DONE_COUNT, (DBUSMALLINT)0, rows);
	else
		srv_senddone(srvproc, SRV_DONE_MORE, (DBUSMALLINT)0, (DBINT)0);
	return(XP_NOERROR);

    
	// Revert back to SQL Server's user account
    //
    if( bImpersonated )
        srv_revert_to_self(srvproc);

}


// HANDLE_ODBC_ERR
//	This routine is called to send messages to clients when an ODBC function
//	returns what could be considered an error (e.g., SQL_ERROR,
//	SQL_INVALID_HANDLE).
//
// Parameters:
//	rc	- The return code of the function that did not SUCCESS.
//	msgnum		- The ODS user message code.
//	connection		- The ODBC connection handle.
//	statement		- The ODBC statement handle.
//	srvproc			- Contains additional client information.
//
// Returns:
//	none
//

void handle_odbc_err(char *szODBCApi,
	RETCODE rc,
	DBINT msgnum,
	HENV henv,
	HDBC hdbc,
	HSTMT hstmt,
	SRV_PROC *srvproc)
{
	UCHAR szSQLState[6], szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
	SDWORD NativeError;
	SWORD cbErrorMsg;
	RETCODE retcode;

	// if rc is SQL_SUCCESS, return without doing anything
	if (rc == SQL_SUCCESS)
		return;

	retcode = SQLError(henv,
		hdbc,
		hstmt,
		szSQLState,
		&NativeError,
		szErrorMsg,
		SQL_MAX_MESSAGE_LENGTH-1,
		&cbErrorMsg);

	// if rc is informational, sned message, else send error to client
	if (rc == SQL_SUCCESS_WITH_INFO)
	{
		srv_sendmsg(srvproc, 
			SRV_MSG_INFO, 
			msgnum, 
			(DBTINYINT)0,
			(DBTINYINT)0, 
			NULL, 
			0, 
			0, 
			szErrorMsg,
			SRV_NULLTERM);

		printf("ODBC message(%s) = %d:%s\n", szODBCApi,rc, szErrorMsg);
	}
	else
	{	
		srv_sendmsg(srvproc, 
			SRV_MSG_ERROR, 
			msgnum, 
			(DBTINYINT)11,
			(DBTINYINT)0, 
			NULL, 
			0, 
			0, 
			szErrorMsg,
			SRV_NULLTERM);

		printf("ODBC error(%s) = %d:%s\n", szODBCApi,rc, szErrorMsg);
	}
}

