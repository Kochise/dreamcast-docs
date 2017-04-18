/*	MS DTC Sample
**
**	This example uses MS DTC (distributed transaction
**	coordinator) to perform simultaneous updates on two
**	SQL servers.  The transaction in this example is 
**	client initiated. The client also initiates the
**	commit operation.
**
**  This sample uses the DBLib interface to communicate
**  with both MS DTC and SQL server.
**
**	In this particular example, the pre-installed SQL server
**	table "Authors" is used.
**
**  Build Instructions:
**  This sample must link with the following files:  ntwdblib.lib, xolehlp.lib
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
// Include DBLib specific header files
//------------------------------------------------------------------------------
#ifndef DBNTWIN32
#define DBNTWIN32

#include <SQL.h>
#include <SQLEXT.h>
#include <sqlfront.h>
#include <sqldb.h>

#endif /* DBNTWIN32 */

//------------------------------------------------------------------------------
// Define constants
//------------------------------------------------------------------------------
#define STR_LEN	40

#define TABLE_NAME		"Authors"    

//------------------------------------------------------------------------------
// Define datatypes
//------------------------------------------------------------------------------
typedef struct DBCONN
{
	TCHAR	pszSrv	[STR_LEN];			// data source name, configured through control panel
	TCHAR	pszUser [STR_LEN];			// Login user name
	TCHAR	pszPasswd[STR_LEN];			// Login user password
	TCHAR	pszTableName[STR_LEN];		// not used - should remove.

}	DBCONN;


//------------------------------------------------------------------------------
// Define Globals
//------------------------------------------------------------------------------
static DBCONN	gSrv1, gSrv2;		// global DB connection struct for server 1 and 2

static TCHAR gAuthorID[STR_LEN];		// use 11 chars only - per Authors table.
static TCHAR gNewAddress[STR_LEN+1];	// max. address length in the Author's table.

//-------------------------------------------------------------------------------	
//  DBLib specific global vars...
//-------------------------------------------------------------------------------
DBPROCESS	*dbproc_server1;
DBPROCESS	*dbproc_server2;
LOGINREC	*login;


//-------------------------------------------------------------------------------	
// Forward declaration of routines used.
//-------------------------------------------------------------------------------	

void InitGlobals(int argc, char **argv);
void LogonToDB(DBPROCESS **dbp, DBCONN *ptr);
void Enlist(DBCONN *ptr,DBPROCESS *dbp, ITransaction *pTransaction);
void ExecuteStatement(DBCONN *ptr, DBPROCESS *dbp, LPTSTR pszBuf);

//-------------------------------------------------------------------------------
// DBLib error and message handlers
//-------------------------------------------------------------------------------
int err_handler(DBPROCESS*, int, int, int, char*, char*);
int msg_handler(DBPROCESS*, DBINT, int, int, char*);


//-------------------------------------------------------------------------------	
// main()
//-------------------------------------------------------------------------------	

void main(int argc, char **argv)
{

	ITransactionDispenser		*pTransactionDispenser;
	ITransaction				*pTransaction;
	HRESULT						hr = S_OK ;
	TCHAR						SqlStatement[STR_LEN*2];


	// Initialize globals & validate command line arguments
	InitGlobals(argc,argv);

	// set error/msg handlers for this program
	dbmsghandle((DBMSGHANDLE_PROC)msg_handler);
	dberrhandle((DBERRHANDLE_PROC)err_handler);

	// initialize LOGINREC structure
	login = dblogin();

	// Obtain the ITransactionDispenser Interface pointer
	// by calling DtcGetTransactionManager()
	hr = DtcGetTransactionManager( 	NULL, 							// LPTSTR	pszHost,
									NULL, 							// LPTSTR	pszTmName,
									IID_ITransactionDispenser,		// /* in */ REFIID	rid,
								    0,								// /* in */ DWORD	dwReserved1,
								    0, 								// /* in */ WORD	wcbReserved2,
								    0,								// /* in */ void	FAR * pvReserved2,
									(void **)&pTransactionDispenser // /*out */ void**	ppvObject
									) ;
	if (FAILED (hr))
    {
		printf("DtcGetTransactionManager failed: %x\n", hr);
	   	exit (1);
    }

	// Establish connection to database on server#1
	LogonToDB(&dbproc_server1,&gSrv1);
					 
	// Establish connection to database on server#2
	LogonToDB(&dbproc_server2,&gSrv2);

	// Loop performing distributed transactions
	for (INT i = 0; i < 5; i++)
	{

		// Initiate an MS DTC transaction
		hr = pTransactionDispenser->BeginTransaction( 
				NULL,							//	/* [in]  */ IUnknown __RPC_FAR *punkOuter,
				ISOLATIONLEVEL_ISOLATED,		//	/* [in]  */ ISOLEVEL isoLevel,
				ISOFLAG_RETAIN_DONTCARE,		// 	/* [in]  */ ULONG isoFlags,
				NULL,							//	/* [in]  */	ITransactionOptions *pOptions 
				&pTransaction					//	/* [out] */ ITransaction **ppTransaction
				) ;
			
		if (FAILED (hr))
		{	
			printf("BeginTransaction failed: %x\n",hr);
			exit(1);
		}

		// Enlist each of the data sources on the transaction
		Enlist(&gSrv1,dbproc_server1,pTransaction);
		Enlist(&gSrv2,dbproc_server2,pTransaction);

		// Generate the SQL statement to execute on each of the databases
		sprintf(SqlStatement,
				"update authors set address = '%s_%d' where au_id = '%s'",
				 gNewAddress,i,gAuthorID);
		
		// Perform updates on both of the DBs participating in the transaction
		ExecuteStatement(&gSrv1,dbproc_server1,SqlStatement);
		ExecuteStatement(&gSrv2,dbproc_server2,SqlStatement);

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

	// release DBLib resources and exit
	dbexit();
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

	// Init Table name 
	lstrcpy(gSrv1.pszTableName,TABLE_NAME);
	lstrcpy(gSrv2.pszTableName,TABLE_NAME);


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

	printf("MS DTC/DBLib Sample Configuration parameters\n");
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

void LogonToDB(DBPROCESS **dbp, DBCONN *ptr)
{

	DBSETLUSER(login, ptr->pszUser);
	DBSETLPWD(login, ptr->pszPasswd);
	DBSETLAPP(login, "example");

	*dbp = dbopen (login, ptr->pszSrv);
	if (*dbp == NULL)
	{
		printf ("\nLogin to server: %s failed, exiting!\n",ptr->pszSrv);
		exit (ERREXIT);
	}

	/* Use the "pubs" database. */
	dbuse(*dbp, "pubs");
}


//-------------------------------------------------------------------------------	

void Enlist(DBCONN *ptr, DBPROCESS *dbp, ITransaction *pTransaction)
{
	RETCODE rc = 0;
	
	rc = dbenlisttrans (dbp, pTransaction);
				
	if (FAIL == rc) 
	{
		printf("\ndbenlisttrans() failed: %x\n",rc);
		exit(1);
	}

}


// ---------------------------------------------------------------------------

void ExecuteStatement(DBCONN *ptr, DBPROCESS *dbp, char *pszBuf)
{
	RETCODE rc = 0;

	dbcmd(dbp,pszBuf);
	
	rc = dbsqlexec(dbp);
	if (FAIL == rc)
	{
		// one or both of the servers failed to prepare
		printf("dbsqlexec() failed\n");
		exit(1);
	}

	rc = dbresults(dbp);
	if (rc != SUCCEED)
	{
		printf("dbresults() failed: %x\n",rc);
		exit(1);
	}
}

// ---------------------------------------------------------------------------

/* Message and error handling functions. */

int msg_handler(DBPROCESS *dbproc, DBINT msgno, int msgstate, int severity, char *msgtext)
{
	/*	Msg 5701 is just a USE DATABASE message, so skip it.	*/
	if (msgno == 5701)
		return (0);

	/*	Print any severity 0 message as is, without extra stuff.	*/
	if (severity == 0)
	{
		printf ("%s\n",msgtext);
		return (0);
	}

	printf("SQL Server message %ld, severity %d:\n\t%s\n",
		msgno, severity, msgtext);

	if (severity >>= 16)
	{
		printf("Program Terminated! Fatal SQL Server error.\n");
		exit(ERREXIT);
	}
	return (0);
}

// ---------------------------------------------------------------------------

int err_handler(DBPROCESS *dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr)
   
{
	if ((dbproc == NULL) || (DBDEAD(dbproc)))
		return (INT_EXIT);
	else
	{
		printf ("DB-LIBRARY error: \n\t%s\n", dberrstr);

		if (oserr != DBNOERR)
			printf ("Operating system error:\n\t%s\n", oserrstr);
	}
	return (INT_CANCEL);
}

// ---------------------------------------------------------------------------