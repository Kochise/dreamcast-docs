
/*	MS DTC Sample
**
**	This example uses MS DTC (distributed transaction
**	coordinator) to perform simultaneous updates on two
**	SQL servers.  The transaction in this example is 
**	client initiated. The client also initiates the
**	commit operation.
**
**  As this sample uses the ODBC interface, you'll need
**  to configure ODBC data source names for 2 SQL servers
**  that you can use to run this sample.  Each DSN; data
**  source name,  must point to the pubs database in
**  a separate SQL server. The authors table in the pubs
**  database is used in this sample.
**
**  Build Instructions:
**  This sample must link with the following files:  xolehlp.lib, odbc32.lib, odbccp32.lib
**
**  Usage Instructions:
**  Please run this program with the '-h' flag.
**
*/

//------------------------------------------------------------------------------
// Include standard header files
//------------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

//------------------------------------------------------------------------------
// Include MS DTC specific header files.
//------------------------------------------------------------------------------
#define INITGUID

#include "txdtc.h"
#include "xolehlp.h"


//------------------------------------------------------------------------------
// Include ODBC specific header file.
//------------------------------------------------------------------------------
#ifndef DBNTWIN32
#define DBNTWIN32

#include <SQL.h>
#include <SQLEXT.h>
#include "odbcss.h"
#include <ODBCINST.h>

#endif /* DBNTWIN32 */

//------------------------------------------------------------------------------
// Define constants
//------------------------------------------------------------------------------
#define STR_LEN	40

//------------------------------------------------------------------------------
// Define datatypes
//------------------------------------------------------------------------------
typedef struct DBCONN
{
	TCHAR	pszSrv	[STR_LEN];			// data source name, configured through control panel
	TCHAR	pszUser [STR_LEN];			// Login user name
	TCHAR	pszPasswd[STR_LEN];			// Login user password
	HDBC	hdbc;						// handle to an ODBC database connection
	HSTMT	hstmt;						// an ODBC statement handle, for use with SQLExecDirect

}	DBCONN;


//------------------------------------------------------------------------------
// Define Globals
//------------------------------------------------------------------------------
static DBCONN	gSrv1, gSrv2;			// global DB connection struct for server 1 and 2

static TCHAR	gAuthorID[STR_LEN];		// use 11 chars only - per Authors table.
static TCHAR	gNewAddress[STR_LEN+1];	// max. address length in the Author's table.

//-------------------------------------------------------------------------------	
//  ODBC specific global vars...
//-------------------------------------------------------------------------------
HENV			gHenv = SQL_NULL_HENV;

//-------------------------------------------------------------------------------	
// Forward declaration of routines used.
//-------------------------------------------------------------------------------	

void InitGlobals(int argc, char **argv);
void LogonToDB(DBCONN *ptr);
void Enlist(DBCONN *ptr, ITransaction *pTransaction);
void ExecuteStatement(DBCONN *ptr, LPTSTR pszBuf);
BOOL ProcessRC(LPTSTR pszFuncName, DBCONN *ptr, RETCODE rc);
void DoSQLError(DBCONN *ptr);
void FreeODBCHandles(DBCONN *ptr);


//-------------------------------------------------------------------------------	
// main()
//-------------------------------------------------------------------------------	

void main(int argc, char **argv)
{

	ITransactionDispenser	*pTransactionDispenser;
	ITransaction			*pTransaction;
	HRESULT					hr = S_OK ;
	BOOL					tf = 0 ;
	TCHAR					SqlStatement[STR_LEN*2];
	

	// Initialize globals & validate command line arguments
	InitGlobals(argc,argv);


	// Obtain the ITransactionDispenser Interface pointer
	// by calling DtcGetTransactionManager()
	hr = DtcGetTransactionManager(
				NULL,								// LPTSTR	 pszHost,
				NULL,								// LPTSTR	 pszTmName,
				IID_ITransactionDispenser,			// /* in  */ REFIID rid,
				0,									// /* in  */ DWORD	dwReserved1,
				0, 									// /* in  */ WORD	wcbReserved2,
				NULL,								// /* in  */ void FAR * pvReserved2,
				(void **)&pTransactionDispenser 	// /* out */ void** ppvObject
				);

	if (FAILED (hr))
	{
		printf("DtcGetTransactionManager failed: %x\n", hr);
	   	exit (1);
	}

	// Initialize the ODBC environment handle.
	if (SQL_NULL_HENV == gHenv)
	{
		ProcessRC("SQLAllocEnv",0,SQLAllocEnv(&gHenv));
	}

	// Establish connection to database on server#1
	LogonToDB(&gSrv1);
					 
	// Establish connection to database on server#2
	LogonToDB(&gSrv2);


	// Loop performing distributed transactions
	for (INT i = 0; i < 5; i++)
	{

		// Initiate an MS DTC transaction
		hr = pTransactionDispenser->BeginTransaction( 
				NULL,							//	/* [in]  */ IUnknown __RPC_FAR *punkOuter,
				ISOLATIONLEVEL_ISOLATED,		//	/* [in]  */ ISOLEVEL isoLevel,
				ISOFLAG_RETAIN_DONTCARE,		// 	/* [in]  */ ULONG isoFlags,
				NULL,							//	/* [in]  */ ITransactionOptions *pOptions 
				&pTransaction					//	/* [out] */ ITransaction **ppTransaction
				) ;
			
		if (FAILED (hr))
		{	
			printf("BeginTransaction failed: %x\n",hr);
			exit(1);
		}

		// Enlist each of the data sources in the transaction
		Enlist(&gSrv1,pTransaction);
		Enlist(&gSrv2,pTransaction);

		// Generate the SQL statement to execute on each of the databases
		sprintf(SqlStatement,
				"update authors set address = '%s_%d' where au_id = '%s'",
				 gNewAddress,i,gAuthorID);
		
		// Perform updates on both of the DBs participating in the transaction
		ExecuteStatement(&gSrv1,SqlStatement);
		ExecuteStatement(&gSrv2,SqlStatement);

		// Commit the transaction 
		hr = pTransaction->Commit(0,0,0);
		if (FAILED(hr))
		{
			printf("pTransaction->Commit() failed: %x\n",hr);
			exit(1);
		}

		// At end of each transaction, pTransaction-Release() must be called.
		hr = pTransaction->Release();
		if (FAILED(hr))
		{
			printf("pTransaction->Release() failed: %x\n",hr);
			exit(1);
		}

		printf("Successfully committed Transaction #%d\n",i);

	} // for 

	
	// release the transaction dispenser	
	pTransactionDispenser->Release();

	// Free ODBC handles
	FreeODBCHandles(&gSrv1);
	FreeODBCHandles(&gSrv2);

	// Free the global ODBC environment handle.
	SQLFreeEnv(gHenv);
}



//-------------------------------------------------------------------------------	

void InitGlobals(INT argc, char **argv)
{

	TCHAR Usage[] = "\n           [-S1  server_1] \n"		\
					"           [-U1  user_name_1]\n"	\
					"           [-P1  passwd_1]\n"		\
					"           [-S2  server_2]\n"		\
					"           [-U2  user_name_2]\n"	\
					"           [-P2  passwd_2]\n"		\
			        "           [-ID  au_id]\n"			\
					"           [-Ad  new_address\n"	\
					"           [-h   Usage]\n";


	// Init ODBC handles to be invalid
    gSrv1.hdbc = SQL_NULL_HDBC;
	gSrv1.hstmt= SQL_NULL_HSTMT;

    gSrv2.hdbc = SQL_NULL_HDBC;
	gSrv2.hstmt= SQL_NULL_HSTMT;

	// Null login info, set defaults as appropriate

	lstrcpy(gSrv1.pszSrv,"");
	lstrcpy(gSrv1.pszUser,"sa");
	lstrcpy(gSrv1.pszPasswd,"");
	lstrcpy(gSrv2.pszSrv,"");
	lstrcpy(gSrv2.pszUser,"sa");
	lstrcpy(gSrv2.pszPasswd,"");

	lstrcpy(gAuthorID,"172-32-1176");	// default au_id value from authors table in pubs db.

	// scan command line arguments for user input.
	for (INT i = 1; i < argc; i++)
	{
		if (*argv[i] == '-' || *argv[i] == '/')
		{
			switch (argv[i][1])
			{
				// get the server or DSN name
				case 's':
				case 'S':
						 switch (argv[i][2])
						 {

						 case '1':
							 lstrcpy(gSrv1.pszSrv,argv[++i]);
							 break;

						 case '2':
							 lstrcpy(gSrv2.pszSrv,argv[++i]);
							 break;

						 default:
							 printf("Invalid Input %s\n",argv[i]);
							 printf("\nUsage: %s %s",argv[0],Usage);
							 exit(1);
						 };
						 break;

				// get user name
				case 'u':
				case 'U':
						 switch (argv[i][2])
						 {

						 case '1':
							 lstrcpy(gSrv1.pszUser,argv[++i]);
							 break;

						 case '2':
							 lstrcpy(gSrv2.pszUser,argv[++i]);
							 break;

						 default:
							 printf("Invalid Input %s\n",argv[i]);
							 printf("\nUsage: %s %s",argv[0],Usage);
							 exit(1);
						 };
						 break;

				// get password
				case 'p':
				case 'P':
						 switch (argv[i][2])
						 {

						 case '1':
							 lstrcpy(gSrv1.pszPasswd,argv[++i]);
							 break;

						 case '2':
							 lstrcpy(gSrv2.pszPasswd,argv[++i]);
							 break;

						 default:
							 printf("Invalid Input %s\n",argv[i]);
							 printf("\nUsage: %s %s",argv[0],Usage);
							 exit(1);
		 				 };
						 break;
				
				// get au_id, overriding default value.
				case 'i':
				case 'I':
							lstrcpy(gAuthorID,argv[++i]);
							break;
				// get new address to associate with the au_id
				case 'a':
				case 'A':
							lstrcpy(gNewAddress,argv[++i]);
							break;
				case '?':
				case 'h':
				case 'H':
						printf("\nUsage: %s %s",argv[0],Usage);
						exit(1);
						break;
						
				default:
						printf("Invalid Input: %s\n",argv[i]);
						printf("\nUsage: %s %s",argv[0],Usage);
						exit(1);
			}
		}
		else 
		{
			printf("Illegal command line argument #%d, %s\n",i,argv[i]);
			printf("\nUsage: %s %s",argv[0],Usage);
			exit(1);
		}
	}

	printf("-----------------------------\n");

	printf("MS DTC/ODBC Sample Configuration parameters\n");
	printf( "server_1:      %s\n"			\
			"user_name_1:   %s\n"			\
			"passwd_1:      %s\n"			\
			"server_2:      %s\n"			\
			"user_name_2:   %s\n"			\
			"passwd_2:      %s\n",

			gSrv1.pszSrv,gSrv1.pszUser,gSrv1.pszPasswd,
			gSrv2.pszSrv,gSrv2.pszUser,gSrv2.pszPasswd);
			
	printf("-----------------------------\n");

}

//-------------------------------------------------------------------------------	

void LogonToDB(DBCONN *ptr)
{
	RETCODE rc = 0;

	rc = SQLAllocConnect(gHenv, &(ptr->hdbc) );

	if (ProcessRC("SQLAllocConnect",ptr,rc))
	{
		rc = SQLConnect(ptr->hdbc, 
						(UCHAR *)(ptr->pszSrv),
						SQL_NTS,
						(UCHAR *)(ptr->pszUser),
						SQL_NTS,
						(UCHAR *)(ptr->pszPasswd),
						SQL_NTS
						);

		ProcessRC("SQLConnect",ptr,rc);
	}
}

//-------------------------------------------------------------------------------	

void Enlist(DBCONN *ptr, ITransaction *pTransaction)
{
	RETCODE rc = 0;

	// Enlist database in the transaction

    rc = SQLSetConnectOption (ptr->hdbc, SQL_COPT_SS_ENLIST_IN_DTC, (UDWORD)pTransaction);

	ProcessRC("SQLSetConnectOption",ptr,rc);
}

// ---------------------------------------------------------------------------

void ExecuteStatement(DBCONN *ptr, LPTSTR pszBuf)
{
	RETCODE rc = 0;

	// Allocate a statement handle for use with SQLExecDirect
	rc = SQLAllocStmt(ptr->hdbc,&(ptr->hstmt));
	
	ProcessRC("SQLAllocStmt",ptr,rc);

	// Execute the passed string as a SQL statement
    rc = SQLExecDirect(ptr->hstmt,(UCHAR *)pszBuf,SQL_NTS);
	
	ProcessRC("SQLExecDirect",ptr,rc);

	// Free the statement handle 
	rc = SQLFreeStmt(ptr->hstmt, SQL_DROP);
	ptr->hstmt = SQL_NULL_HSTMT;

	ProcessRC("SQLFreeStmt",ptr,rc);
	
}

// ---------------------------------------------------------------------------

void FreeODBCHandles(DBCONN *ptr)
{
	SQLDisconnect(ptr->hdbc);
	
	SQLFreeConnect(ptr->hdbc);
	
	ptr->hdbc   = SQL_NULL_HDBC;
	ptr->hstmt  = SQL_NULL_HSTMT;
}


// ---------------------------------------------------------------------------

BOOL ProcessRC(LPTSTR pszFuncName, DBCONN *ptr,RETCODE rc)
{

	switch (rc)
	{
		
	case SQL_SUCCESS:
			return TRUE;
			break;

	case SQL_SUCCESS_WITH_INFO:
			DoSQLError(ptr);
			return TRUE;
			break;

	case SQL_ERROR:
			printf("%s Failed - see more info\n",pszFuncName);
			DoSQLError(ptr);
			exit(-1);
			return FALSE;
			break;

	case SQL_INVALID_HANDLE:
			printf("%s Failed - SQL_INVALID_HANDLE\n",pszFuncName);
			exit(-1);
			return FALSE;
			break;

	case SQL_NO_DATA_FOUND:
			printf("%s Failed - SQL_NO_DATA_FOUND\n",pszFuncName);
			return FALSE;
			break;

	case SQL_STILL_EXECUTING:
			printf("%s Failed - SQL_STILL_EXECUTING\n",pszFuncName);
			return FALSE;
			break;

	case SQL_NEED_DATA:
			printf("%s Failed - SQL_NEED_DATA\n",pszFuncName);
			return FALSE;
			break;

	default:
			printf("%s Failed - unexpected error, rc = %x\n",pszFuncName,rc);
			DoSQLError(ptr);
			exit(-1);
			return FALSE;
			break;
	}

}

// ---------------------------------------------------------------------------

void DoSQLError(DBCONN *ptr)
{

	const INT				MSG_BUF_SIZE = 300;
	UCHAR 				 	szSqlState[MSG_BUF_SIZE];
	UCHAR					szErrorMsg[MSG_BUF_SIZE];
	
	SQLINTEGER	fNativeError	= 0;
	SWORD		cbErrorMsg		= MSG_BUF_SIZE;
	RETCODE		rc;

	rc = SQLError(gHenv,
				  ptr ? ptr->hdbc : 0,
				  ptr ? ptr->hstmt : 0,
				  szSqlState,
				  &fNativeError,
				  szErrorMsg,
				  MSG_BUF_SIZE,
				  &cbErrorMsg
				  );

	if (rc != SQL_NO_DATA_FOUND || rc != SQL_ERROR)
	{
		if (fNativeError != 0x1645)	// ignore change database to master context message
		{
			printf("SQLError info:\n");
			printf("SqlState: %s, fNativeError: %x\n",szSqlState,fNativeError);
			printf("Error Message: %s\n",szErrorMsg);
		}
	}
	else
	{	
		printf("SQLError() failed: %x, NO_DATA_FOUND OR SQL_ERROR\n",rc);
	}

}
// ---------------------------------------------------------------------------