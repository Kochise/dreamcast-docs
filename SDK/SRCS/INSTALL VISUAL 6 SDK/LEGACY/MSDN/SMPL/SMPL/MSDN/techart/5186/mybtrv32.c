/*************************************************************************
**
**  Copyright 1997 Microsoft Corporation All Rights Reserved
**
*************************************************************************/
/********************************************************************************

   MYBTRV32.C
     This is the wrapper .DLL for the Migrating Btrieve Applications to SQL Server
	 discussion.  It contains all of the Btrieve function stubs that are referenced
	 by BTRVAPP.EXE.  The wrapper allows the BTRVAPP.EXE application to access SQL 
	 Server data tables in the pubs database.  This wrapper .DLL makes SQL Server
	 look like Btrieve to the BTRVAPP.EXE application.  This wrapper uses ODBC 3.0
	 functions and Microsoft Transact SQL to access Microsoft SQL Server.
	 
	 If BTRVAPP.EXE is linked with MYBTRV32.dll it accesses the SQL Server BSALES
	 and TITLEPUBLISHER tables instead of the BSALES.BTR AND TITLEPUB.BTR Btrieve
	 files.

*********************************************************************************/

#define ODBCVER 0x0300  // initialize ODBC 3.0 functionality
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>

/* BTRIEVE RETURN CODE CONSTANTS */

#define B_NO_ERROR				0
#define B_KEY_VALUE_NOT_FOUND	4
#define B_END_OF_FILE			9
#define B_UNRECOVERABLE_ERROR	19
#define NON_MATCH				999


// Define IMPORT and EXPORT macros
#define DllImport	__declspec( dllimport ) 
#define DllExport	__declspec( dllexport ) 


/**************************************************************************
	Btrieve Platform-Independent Data Types
**************************************************************************/
#define BTI_FAR      
#define BTI_PASCAL APIENTRY

#if !defined(USING_REGISTERS)
 #define BTI_API extern BTI_SINT BTI_FAR BTI_PASCAL
#endif

typedef unsigned long      BTI_ULONG;
typedef short int          BTI_SINT;
typedef unsigned short     BTI_WORD;
typedef char               BTI_CHAR;
typedef unsigned char      BTI_BYTE;
typedef void               BTI_VOID;
typedef BTI_CHAR  BTI_FAR* BTI_CHAR_PTR;
typedef BTI_BYTE  BTI_FAR* BTI_BUFFER_PTR;
typedef BTI_SINT  BTI_FAR* BTI_SINT_PTR;
typedef BTI_WORD  BTI_FAR* BTI_WORD_PTR;
typedef BTI_ULONG BTI_FAR* BTI_ULONG_PTR;
typedef BTI_VOID  BTI_FAR* BTI_VOID_PTR;
 

/***************************************************************************
	Btrieve Operation Codes
***************************************************************************/
#define B_OPEN					0
#define B_CLOSE					1
#define B_INSERT				2
#define B_UPDATE				3
#define B_GET_EQUAL				5
#define B_GET_NEXT				6
#define B_GET_PREVIOUS			7
#define B_GET_FIRST				12
#define B_GET_LAST				13
#define B_SET_DIR				17
#define B_BEGIN_TRAN			19
#define B_BEGIN_CONCUR_TRAN		1019
#define B_END_TRAN				20
#define B_ABORT_TRAN			21
#define B_STOP					25
#define B_VERSION				26


/*********************************************
SQL SERVER CURSOR CONSTANTS
**********************************************/
#define ROWS 1



/***********************************************************************
	Function Prototypes
***********************************************************************/

DllExport int __stdcall BTRCALLID (BTI_WORD operation, BTI_VOID_PTR posBlock, 
			   BTI_VOID_PTR dataBuffer, BTI_ULONG_PTR dataLen32,
               BTI_VOID_PTR keyBuffer, BTI_BYTE keyLength, 
			   BTI_CHAR ckeynum, BTI_BUFFER_PTR clientID );

DllExport int __stdcall BTRCALL (BTI_WORD operation, BTI_VOID_PTR posBlock, 
			   BTI_VOID_PTR dataBuffer, BTI_ULONG_PTR dataLen32,
               BTI_VOID_PTR keyBuffer, BTI_BYTE keyLength, 
			   BTI_CHAR ckeynum );


DllExport int __stdcall WBRQSHELLINIT( BTI_CHAR_PTR option );
int GetTitlePublisher(SQLHENV henv1, SQLHDBC hdbc1, SQLHSTMT hstmt8, BTI_WORD operation, BTI_CHAR keyNum, BTI_VOID_PTR keyBuffer);
int GetSales(SQLHENV henv1, SQLHDBC hdbc1, SQLHSTMT hstmt, BTI_WORD operation, BTI_VOID_PTR keyBuffer);
int MakeConn(SQLHENV henv, SQLHDBC *hdbc ,SQLHSTMT *hstmt, char	cServer[31]);
int CursorCreate(SQLHSTMT *hstmt2, LPSTR curname);
int CursorUPD(SQLHSTMT hstmtS, SQLHSTMT hstmtU, BTI_VOID_PTR dataBuffer);
int InsertTP(SQLHSTMT hstmtU, BTI_VOID_PTR dataBuffer);
int InsertSales(SQLHSTMT hstmtU, BTI_VOID_PTR dataBuffer);
BOOL ErrorDump(LPSTR szFuncName, SQLHENV henv, SQLHDBC hdbc, SQLHSTMT hstmt);

/***************************************************************************
	Data Record Structure Type Definitions
****************************************************************************/

  // titlepub record structure (sames as that used by BTRVAPP.C)
  struct
   {
	char	TitleID[ 7 ];	//string
	char	Title[ 81 ];	//string
	char	Type[ 13 ];		//string
	char	PubID[ 5 ];		//string
	float	Price;			//money
	float	Advance;		//money
	int		Royalty;		//integer
	int		YTD_Sales;		//integer
	char	PubName[ 41 ];	//string
	char	City[ 21 ];		//string
	char	State[ 3 ];		//string
	char	Country[ 31 ];	//string
   } tpRec;


  // sales record structure (sames as that used by BTRVAPP.C)
  struct
   {
	char	StorID[ 5 ];	//string
    char	TitleID[ 7 ];	//string
	char	OrdNum[ 21 ];	//string
	int		Qty;			//integer
	char	PayTerms[ 13 ];	//string
   } salesRec;



/***********************************************************************
	DLL Globals
***********************************************************************/


/* ODBC Variables */

SQLHENV henv1;
SQLHDBC hdbc1, hdbc2;
SQLHSTMT   hstmt, hstmt2, hstmt3, hstmt4;

/* Program variables			    */
char		cServer[31]="";			// Server Name
			   

/***********************************************************************
	DllMain
***********************************************************************/


BOOL APIENTRY DllMain( HANDLE hModule, 
                        DWORD ul_reason_for_call, 
                        LPVOID lpReserved )
{
    switch( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH:
		
		// Allocate the ODBC environment handle for this DLL instance
		if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &henv1)) {
			printf("\n\n ODBC SQLAllocHandle PRoblem\n\n");
		return B_UNRECOVERABLE_ERROR;
		}

		// Set the ODBC version to 3.0
		if(SQL_SUCCESS != SQLSetEnvAttr(henv1, SQL_ATTR_ODBC_VERSION,
                                   (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER)) {
			printf("\n\n ODBC SQLSetEnvAttr PRoblem\n\n");
			return B_UNRECOVERABLE_ERROR;
		}

		// Get the name of the Microsoft SQL Server to wrapper will connect with
		printf("\n\nEnter the Server Name: ");
		gets(cServer);
		break;

    case DLL_THREAD_ATTACH:
		break;

    case DLL_THREAD_DETACH:
		break;

	// Release the environment, connection, and statement handles
    case DLL_PROCESS_DETACH:
		SQLFreeStmt(&hstmt, SQL_CLOSE);
		SQLFreeStmt(&hstmt2, SQL_CLOSE);
		SQLFreeHandle(SQL_HANDLE_STMT, &hstmt);
		SQLFreeHandle(SQL_HANDLE_STMT, &hstmt2);
		SQLFreeHandle(SQL_HANDLE_STMT, &hstmt3);
		SQLFreeHandle(SQL_HANDLE_STMT, &hstmt4);
		SQLFreeHandle(SQL_HANDLE_DBC, &hdbc1);
		SQLFreeHandle(SQL_HANDLE_DBC, &hdbc2);
		SQLFreeHandle(SQL_HANDLE_ENV, &henv1);
		printf("\n\nProcess detached\n\n");
		break;
    }
    return TRUE;
}


/***********************************************************************
	BTRCALLID
***********************************************************************/


DllExport int __stdcall BTRCALLID (BTI_WORD operation, BTI_VOID_PTR posBlock, 
			   BTI_VOID_PTR dataBuffer, BTI_ULONG_PTR dataLen32,
               BTI_VOID_PTR keyBuffer, BTI_BYTE keyLength, 
			   BTI_CHAR ckeynum, BTI_BUFFER_PTR clientID )
{

	switch(operation){

	case B_VERSION:
		break;

	case B_STOP:
		break;

	default:
		printf("\n\n BTRCALLid LOOPHOLE\n\n");
		break;
	}	

	return B_NO_ERROR;
}



/***********************************************************************
	BTRCALL
***********************************************************************/


DllExport int __stdcall BTRCALL (BTI_WORD operation, BTI_VOID_PTR posBlock, 
			   BTI_VOID_PTR dataBuffer, BTI_ULONG_PTR dataLen32,
               BTI_VOID_PTR keyBuffer, BTI_BYTE keyLength, 
			   BTI_CHAR ckeynum)
{
	int pos=0;
	SQLRETURN rc;
	
	switch(operation){

	case B_OPEN:	
	
	/*  Step 1:The same posBlock will from this point forward reference a particular table.  
	/*  The keybuffer contains the file name of the btrieve to be opened when B_OPEN is called.  We will set 
	/*  the posblock equal to the file/table name.  This way we will always know what table/file 
	/*  is being referenced by every command from that point forward.  Because we know the application code
	/*  we will also know what the data structure is like for the file/table being opened and it can be used 
	/*  as appropriate.

	/*  Step 2: Open a cursor on the appropriate table
	*/

		/* Step 1: */

		// Connect to the SQL Server entered by the user.  Quit if there is a problem making one of the connections

		if (strlen((BTI_CHAR *)keyBuffer) <=128)
			memcpy((BTI_CHAR *)posBlock, (BTI_CHAR *)keyBuffer, keyLength);
		else
			memcpy((BTI_CHAR *)posBlock, (BTI_CHAR *)keyBuffer, 128);

		/* Step 2: */
		if (!strcmp(posBlock, "titlepub.btr")){
			rc = MakeConn(henv1, &hdbc1 , &hstmt, cServer);
			if (rc != B_NO_ERROR)
				return FALSE;
			CursorCreate(&hstmt, "TITPUBCURSOR");
		}
		else {
			rc = MakeConn(henv1, &hdbc2 , &hstmt2, cServer);
			if (rc != B_NO_ERROR)
				return FALSE;
			CursorCreate(&hstmt2, "BSALESCURSOR");
		}
	break;
	

	case B_INSERT:   // Insert a record in the appropriate table based on posBlock value
		if (!strcmp(posBlock, "titlepub.btr"))
			rc=InsertTP(hstmt3, dataBuffer);
		else
			rc=InsertSales(hstmt4, dataBuffer);

		if (rc != B_NO_ERROR)
			return rc;
		break;
	

	case B_UPDATE:	
		//  Load the tpRec structure with the data and update the record
		memcpy(&tpRec, dataBuffer, sizeof(tpRec));
		rc=CursorUPD(hstmt, hstmt, dataBuffer);
		if (rc != B_NO_ERROR)
			return rc;
		break;

	
	case B_GET_EQUAL:	
		// Get the first record that matches the search criteria.  Table to be searched 
		// is determined by examining the posBlock value 
		if (!strcmp(posBlock, "titlepub.btr")){
			rc = GetTitlePublisher(henv1, hdbc1, hstmt, B_GET_EQUAL, ckeynum, keyBuffer);
			if (rc == B_NO_ERROR)
				memcpy(dataBuffer, &tpRec, sizeof(tpRec));
			else
				return rc;
		}
		else {
			rc=GetSales(henv1, hdbc2, hstmt2, B_GET_EQUAL, keyBuffer);
			if (rc == B_NO_ERROR)
				memcpy(dataBuffer, &salesRec, sizeof(salesRec));
			else
				return rc;
		}
		break;
	

	case B_GET_NEXT:
		// Get the next record that matches the search criteria.  Table to be searched 
		// is determined by examining the posBlock value 
		if (!strcmp(posBlock, "titlepub.btr")){
			rc=GetTitlePublisher(henv1, hdbc1, hstmt, B_GET_NEXT, ckeynum, keyBuffer);
			if (rc == B_NO_ERROR)
				memcpy(dataBuffer, &tpRec, sizeof(tpRec));
			else
				return rc;
		}
		else {
			rc=GetSales(henv1, hdbc2, hstmt2, B_GET_NEXT, keyBuffer);
			if (rc == B_NO_ERROR)
				memcpy(dataBuffer, &salesRec, sizeof(salesRec));
			else
				return rc;
		}
		break;

	case B_SET_DIR:	
		// Nothing to do here.  No need to perform this in Microsoft SQL Server.  
		break;
	

	case B_BEGIN_TRAN:	
	case B_BEGIN_CONCUR_TRAN:
		// SET IMPLICIT TRANSACTIONS ON within ODBC for the connection.  Table to be referenced 
		// is determined by examining the posBlock value 
		if (!strcmp(posBlock, "titlepub.btr"))
		{
			rc=SQLSetConnectOption(hdbc1, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF); // turn on implicit transactions
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{ // error encountered turn implicit transactions off
				ErrorDump("TITLEPUBLISHER SQL_AUTOCOMMIT_OFF ", SQL_NULL_HENV, hdbc1, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}

			// Allocate connection handle 
			rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt3); 
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){
				ErrorDump("SQLAllocHandle HSTMT", SQL_NULL_HENV, SQL_NULL_HDBC, hstmt3);
				return B_UNRECOVERABLE_ERROR;
			}
		}
		else
		{
			rc=SQLSetConnectOption(hdbc2, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{  // error encountered turn implicit transactions off
				ErrorDump("SALES SQL_AUTOCOMMIT_OFF ", SQL_NULL_HENV, hdbc2, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}

			// Allocate connection handle 
			rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc2, &hstmt4); 
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){
				ErrorDump("SQLAllocHandle HSTMT", SQL_NULL_HENV, SQL_NULL_HDBC, hstmt4);
				return B_UNRECOVERABLE_ERROR;
			}
		}
		break;


	case B_END_TRAN:	
		// Commit the open transaction
		// SET IMPLICIT TRANSACTIONS OFF for the connection

		// TITLEPUBLISHER table
		if (!strcmp(posBlock, "titlepub.btr"))
		{
			rc=SQLTransact(henv1, hdbc1, SQL_COMMIT); // issue BEGIN TRAN
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{ // error encountered turn implicit transactions off
				ErrorDump("TITLEPUBLISHER COMMIT TRANSACTION ", SQL_NULL_HENV, hdbc1, SQL_NULL_HSTMT);
				SQLFreeHandle(SQL_HANDLE_STMT, &hstmt3);
				return B_UNRECOVERABLE_ERROR;
			}
			
			// Issue COMMIT TRAN
			rc=SQLSetConnectOption(hdbc1, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("TITLEPUBLISHER SQL_AUTOCOMMIT_OFF ", SQL_NULL_HENV, hdbc1, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}

			// COMMIT TRAN via SQLTransact will close the cursor so we are reopening
			rc=SQLExecDirect(hstmt,
					"SELECT TITLE_ID, TITLE, TYPE, PUB_ID, PRICE, ADVANCE, ROYALTY, YTD_SALES, PUB_NAME, CITY, STATE, COUNTRY FROM TITLEPUBLISHER ",
						SQL_NTS);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("SQLExecDirect ENDTRAN GetTitlePub", SQL_NULL_HENV, SQL_NULL_HDBC, hstmt);
				return B_UNRECOVERABLE_ERROR;
			}

			SQLFreeHandle(SQL_HANDLE_STMT, &hstmt3);
		}
		else
		{
			// BSALES table
			rc=SQLTransact(henv1, hdbc2, SQL_COMMIT); // issue BEGIN TRAN
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{ // error encountered turn implicit transactions off
				ErrorDump("SALES COMMIT TRANSACTION ", SQL_NULL_HENV, hdbc2, SQL_NULL_HSTMT);
				SQLFreeHandle(SQL_HANDLE_STMT, &hstmt4);
				return B_UNRECOVERABLE_ERROR;
			}

			// Issue COMMIT TRAN
			rc=SQLSetConnectOption(hdbc2, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("TITLEPUBLISHER SQL_AUTOCOMMIT_OFF ", SQL_NULL_HENV, hdbc2, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}
			
			// COMMIT TRAN via SQLTransact will close the cursor so we are reopening it
			rc=SQLExecDirect(hstmt2,
				"SELECT STOR_ID, TITLE_ID, ORDNUM, QTY, PAYTERMS FROM BSALES ",
					SQL_NTS);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("SQLExecDirect ENDTRAN GetBSales", SQL_NULL_HENV, SQL_NULL_HDBC, hstmt2);
				return B_UNRECOVERABLE_ERROR;
			}
			SQLFreeHandle(SQL_HANDLE_STMT, &hstmt4);
		}
		break;


	case B_ABORT_TRAN:	
		// Commit the open transaction
		// SET IMPLICIT TRANSACTIONS ON for the connection

		// TITLEPUBLISHER table
		if (!strcmp(posBlock, "titlepub.btr")){
			rc=SQLTransact(henv1, hdbc1, SQL_ROLLBACK);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("TITLEPUBLISHER ROLLBACK TRANSACTION ", SQL_NULL_HENV, hdbc1, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}
			rc=SQLSetConnectOption(hdbc1, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("TITLEPUBLISHER SQL_AUTOCOMMIT_OFF ", SQL_NULL_HENV, hdbc1, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}
			
			SQLFreeHandle(SQL_HANDLE_STMT, &hstmt3);
		}
		else
		{
			// BSALES
			rc=SQLTransact(henv1, hdbc2, SQL_ROLLBACK);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("SALES ROLLBACK TRANSACTION ", SQL_NULL_HENV, hdbc2, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}
			
			rc=SQLSetConnectOption(hdbc2, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
			if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
			{
				ErrorDump("TITLEPUBLISHER SQL_AUTOCOMMIT_OFF ", SQL_NULL_HENV, hdbc2, SQL_NULL_HSTMT);
				return B_UNRECOVERABLE_ERROR;
			}
			SQLFreeHandle(SQL_HANDLE_STMT, &hstmt4);
		}
		break;


	case B_STOP:	
		// Nothing to do here.  No need to perform this in Microsoft SQL Server.  
		break;

	default:
		printf("\n\n BTRCALL LOOPHOLE\n\n");
		break;
	}	

	return B_NO_ERROR;
}



/***********************************************************************
	WBRQSHELLINIT
***********************************************************************/

DllExport int __stdcall WBRQSHELLINIT( BTI_CHAR_PTR option )
{
	printf("\n\nWBRQSHELLINIT called\n\n");
	return B_NO_ERROR;
}

/***********************************************************************
	GetTitlePublisher
***********************************************************************/
int GetTitlePublisher(SQLHENV henv8, SQLHDBC hdbc8, SQLHSTMT hstmt8, BTI_WORD operation, BTI_CHAR keyNum, BTI_VOID_PTR keyBuffer)
{
	SQLINTEGER  cbTitleID=SQL_NTS, cbTitle=SQL_NTS, cbType=SQL_NTS, cbPubID=SQL_NTS, cbPubName=SQL_NTS;
	SQLINTEGER  cbCity=SQL_NTS, cbState=SQL_NTS, cbCountry=SQL_NTS;
	SQLINTEGER	RoyaltyInd, AdvanceInd, PriceInd, YTDSalesInd;
	SQLUINTEGER FetchOffset;			// Offset within the cursor result set
	SQLSMALLINT FetchOrientation;		// Cursor fetch operation
	SQLRETURN	rc;						// ODBC return code
	int found=0;

			// Determine the type of search within the server cursor result set
			switch(operation) {

				case B_GET_EQUAL:  // Fetch the first record that matches the search criteria
					FetchOrientation = SQL_FETCH_FIRST;
					FetchOffset = 0;
					break;

				case B_GET_NEXT:   // Fetch the next record that matches the search criteria
					FetchOrientation = SQL_FETCH_NEXT;
					FetchOffset = 1;
					break;
			}

			//  Bind TitlePublisher columns to buffers to receive the TitlePublisher record result set
			SQLBindCol(hstmt8, 1, SQL_C_CHAR, tpRec.TitleID, 7, &cbTitleID);
			SQLBindCol(hstmt8, 2, SQL_C_CHAR, tpRec.Title, 81, &cbTitle);
			SQLBindCol(hstmt8, 3, SQL_C_CHAR, tpRec.Type, 13, &cbType);
			SQLBindCol(hstmt8, 4, SQL_C_CHAR, tpRec.PubID, 5, &cbPubID);
			SQLBindCol(hstmt8, 5, SQL_C_FLOAT, &tpRec.Price, 0, &PriceInd);
			SQLBindCol(hstmt8, 6, SQL_C_FLOAT, &tpRec.Advance, 0, &AdvanceInd);
			SQLBindCol(hstmt8, 7, SQL_C_SLONG, &tpRec.Royalty, 0, &RoyaltyInd);
			SQLBindCol(hstmt8, 8, SQL_C_SLONG, &tpRec.YTD_Sales, 0, &YTDSalesInd);
			SQLBindCol(hstmt8, 9, SQL_C_CHAR, tpRec.PubName, 41, &cbPubName);
			SQLBindCol(hstmt8, 10, SQL_C_CHAR, tpRec.City, 21, &cbCity);
			SQLBindCol(hstmt8, 11, SQL_C_CHAR, tpRec.State, 3, &cbState);
			SQLBindCol(hstmt8, 12, SQL_C_CHAR, tpRec.Country, 31, &cbCountry);
			
					
			while (!found)  // fetch a record-at-a-time until desired record is found
			{
				memset( &tpRec, 0, sizeof(tpRec) );			
				rc=SQLFetchScroll(hstmt8, FetchOrientation, FetchOffset);  // Fetch the record
				if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
				{
					if (rc!=SQL_NO_DATA_FOUND){  // Error fetching record return error
						ErrorDump("SQLFetchScroll TitlePub", SQL_NULL_HENV, SQL_NULL_HDBC, hstmt8);
						return B_UNRECOVERABLE_ERROR;
					}
					else {
						return B_END_OF_FILE;}
				}	
				
				switch(keyNum) {
					case 0:			//  TitleID Search
						if (!strcmp(keyBuffer, tpRec.TitleID))
							found=1;
					break;

					case 3:			// PubID Search
						if (!strcmp(keyBuffer, tpRec.PubID))
							found=1;
					break;
				}

				if (!found){
					FetchOrientation = SQL_FETCH_NEXT;
					FetchOffset = 1;
				}
			}

			return B_NO_ERROR;
}


/***********************************************************************
	GetSales
***********************************************************************/

int GetSales(SQLHENV henv1, SQLHDBC hdbc1, SQLHSTMT hstmt, BTI_WORD operation, BTI_VOID_PTR keyBuffer)
{
	SQLINTEGER  cbStorID, cbTitleID, cbOrdNum, cbPayTerms;
	SQLINTEGER	QtyInd;
	SQLUINTEGER FetchOffset;			// Offset within the cursor result set
	SQLSMALLINT FetchOrientation;		// Cursor fetch operation
	SQLRETURN	rc;						// ODBC return code
	int found=0;
			
			// Determine the type of search within the server cursor result set
			switch(operation) {

			case B_GET_EQUAL:	// Fetch the first record that matches the search criteria
				FetchOrientation = SQL_FETCH_FIRST;
				FetchOffset = 0;
			break;

			case B_GET_NEXT:	// Fetch the next record that matches the search criteria
				FetchOrientation = SQL_FETCH_NEXT;
				FetchOffset = 1;
			break;
			}

			//  Bind Sales columns to buffers to receive the Sales record result set
			SQLBindCol(hstmt, 1, SQL_C_CHAR, salesRec.StorID, 5, &cbStorID);
			SQLBindCol(hstmt, 2, SQL_C_CHAR, salesRec.TitleID, 7, &cbTitleID);
			SQLBindCol(hstmt, 3, SQL_C_CHAR, salesRec.OrdNum, 21, &cbOrdNum);
			SQLBindCol(hstmt, 4, SQL_C_SLONG, &salesRec.Qty, 0, &QtyInd);
			SQLBindCol(hstmt, 5, SQL_C_CHAR, salesRec.PayTerms, 13, &cbPayTerms);
				
			while (!found)
			{
				memset( &salesRec, 0, sizeof(salesRec) );			
				rc=SQLFetchScroll(hstmt, FetchOrientation, FetchOffset);	// Fetch the record
				if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
				{
					if (rc!=SQL_NO_DATA_FOUND){	// Error fetching record return error
						ErrorDump("SQLFetchScroll sales", SQL_NULL_HENV, SQL_NULL_HDBC, hstmt);
						return B_UNRECOVERABLE_ERROR;
					}
					else {
						return NON_MATCH;}
				}	

				if (!strcmp(keyBuffer, salesRec.TitleID))
					found=1;
				else {
					FetchOrientation = SQL_FETCH_NEXT;
					FetchOffset = 1;
				}
			}

			return B_NO_ERROR;
}



/***********************************************************************
	MakeConn
***********************************************************************/
int MakeConn(SQLHENV henv, SQLHDBC *hdbc ,SQLHSTMT *hstmt, char	cServer[31])
{
	SQLRETURN  rc;			//ODBC return code

	// Allocate a connection handle and set login timeout to 5 seconds
	rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, hdbc); 
	if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
		rc=SQLSetConnectAttr(*hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER	) 5, 0);
	else{
		ErrorDump("SQLAllocHandle HDBC", SQL_NULL_HENV, *hdbc, SQL_NULL_HSTMT);
		return B_UNRECOVERABLE_ERROR;
	}

	// Connect to SQL Server using the pubsuser Microsoft SQL Server login account
	rc = SQLConnect(*hdbc, (SQLCHAR *) cServer, (SQLSMALLINT) strlen(cServer),
	                            (SQLCHAR *) "pubsuser", (SQLSMALLINT) strlen("pubsuser"),
	                            (SQLCHAR *) "pubsuser", (SQLSMALLINT) strlen("pubsuser"));
	
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){  // Problem making connection return error
		ErrorDump("SQLConnect", SQL_NULL_HENV, *hdbc, SQL_NULL_HSTMT);
		return B_UNRECOVERABLE_ERROR;
	}

	// Allocate a statement handle for use with this connection
	rc = SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, hstmt); 
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){ // Problem allocating statement handle return error
		ErrorDump("SQLAllocHandle HSTMT", SQL_NULL_HENV, SQL_NULL_HDBC, *hstmt);
		return B_UNRECOVERABLE_ERROR;
	}
	
	return B_NO_ERROR;
}

/***********************************************************************
	CreateCursor
***********************************************************************/
int CursorCreate(SQLHSTMT *hstmt2, LPSTR curname)
{

	SQLRETURN	rc;			//ODBC return code

	//  Create a dynamic cursor and name it
	SQLSetStmtAttr(*hstmt2, SQL_ATTR_CONCURRENCY, (SQLPOINTER) SQL_CONCUR_VALUES, 0);
	SQLSetStmtAttr(*hstmt2, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) SQL_CURSOR_DYNAMIC, 0);
	SQLSetCursorName(*hstmt2, curname, SQL_NTS);
	
	// Open the appropriate cursor based on curname
	if (!strcmp(curname, "BSALESCURSOR"))
		rc=SQLExecDirect(*hstmt2,
				"SELECT STOR_ID, TITLE_ID, ORDNUM, QTY, PAYTERMS FROM BSALES ",
					SQL_NTS);
	else
		rc=SQLExecDirect(*hstmt2,
				"SELECT TITLE_ID, TITLE, TYPE, PUB_ID, PRICE, ADVANCE, ROYALTY, YTD_SALES, PUB_NAME, CITY, STATE, COUNTRY FROM TITLEPUBLISHER ",
					SQL_NTS);

	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{ // Error creating cursor - return error
			ErrorDump("SQLExecDirect Cursor Create", SQL_NULL_HENV, SQL_NULL_HDBC, *hstmt2);
			return B_UNRECOVERABLE_ERROR;
		}
	return B_NO_ERROR;
}


/***********************************************************************
	CursorUPD
***********************************************************************/
int CursorUPD(SQLHSTMT hstmtS, SQLHSTMT hstmtU, BTI_VOID_PTR dataBuffer)
{
	SQLRETURN	rc;			// ODBC return code
	int	numRows=0;			// Number of rows in resultset

	SQLINTEGER  cbTitleID = SQL_NTS, cbTitle = SQL_NTS, cbType = SQL_NTS, cbPubID = SQL_NTS;
	SQLINTEGER  cbPubName = SQL_NTS, cbCity = SQL_NTS, cbState = SQL_NTS, cbCountry = SQL_NTS;
	SQLINTEGER	RoyaltyInd, AdvanceInd, PriceInd, YTDSalesInd;
	
	// Initialize the tpRec data structure 
	memset( &tpRec, 0, sizeof(tpRec) );
	memcpy(&tpRec, dataBuffer, sizeof(tpRec));
	
	/*  Update the current row within the cursor. We rebind the columns to update the length 
	/*  of the NULL terminated string columns. We are using 0 for the the numRows
	/*  parameter to affect all rows in the rowset.  Since we have a rowset size of 1 
	/*  only the positioned row will be affected. The key value of the current record 
	/*  is not changing so we issue the positioned update using 
	/*  SQLSetPos(SQL_UPDATE, SQL_LOCK_NO_CHANGE)
	*/

	SQLBindCol(hstmtS, 1, SQL_C_CHAR, tpRec.TitleID, 7, &cbTitleID);
	SQLBindCol(hstmtS, 2, SQL_C_CHAR, tpRec.Title, 81, &cbTitle);
	SQLBindCol(hstmtS, 3, SQL_C_CHAR, tpRec.Type, 13, &cbType);
	SQLBindCol(hstmtS, 4, SQL_C_CHAR, tpRec.PubID, 5, &cbPubID);
	SQLBindCol(hstmtS, 5, SQL_C_FLOAT, &tpRec.Price, 0, &PriceInd);
	SQLBindCol(hstmtS, 6, SQL_C_FLOAT, &tpRec.Advance, 0, &AdvanceInd);
	SQLBindCol(hstmtS, 7, SQL_C_SLONG, &tpRec.Royalty, 0, &RoyaltyInd);
	SQLBindCol(hstmtS, 8, SQL_C_SLONG, &tpRec.YTD_Sales, 0, &YTDSalesInd);
	SQLBindCol(hstmtS, 9, SQL_C_CHAR, tpRec.PubName, 41, &cbPubName);
	SQLBindCol(hstmtS, 10, SQL_C_CHAR, tpRec.City, 21, &cbCity);
	SQLBindCol(hstmtS, 11, SQL_C_CHAR, tpRec.State, 3, &cbState);
	SQLBindCol(hstmtS, 12, SQL_C_CHAR, tpRec.Country, 31, &cbCountry);

	rc=SQLSetPos(hstmtS, numRows, SQL_UPDATE,  SQL_LOCK_NO_CHANGE);
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLSetPos SQL_UPDATE for TITLEPUBLISHER FAILED", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtS);
			return B_UNRECOVERABLE_ERROR;
		}

	return B_NO_ERROR;
}


/***********************************************************************
	InsertSales
***********************************************************************/
int InsertSales(SQLHSTMT hstmtU, BTI_VOID_PTR dataBuffer)
{
	SQLRETURN	rc;						// ODBC return code
	char		szStmt[1024];			// The INSERT statement


	// Build the INSERT statement
	static const char gszSALES[]	=
	"INSERT BSALES(stor_id, title_id, ordnum, qty, payterms) "
	"VALUES ('%s', '%s', '%s', %ld, '%s')";


	//copy data to be inserted to our record structure and fill in place holders for the INSERT statement
	memset( &salesRec, 0, sizeof(salesRec) );
	memcpy(&salesRec, dataBuffer, sizeof(salesRec));
	sprintf(szStmt, gszSALES, salesRec.StorID, salesRec.TitleID, salesRec.OrdNum, salesRec.Qty, salesRec.PayTerms);
	

	//execute the INSERT
	rc=SQLExecDirect(hstmtU, szStmt, SQL_NTS);
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLEXECUTE INSERT BSALES", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return B_UNRECOVERABLE_ERROR;
		}
	
	return B_NO_ERROR;
}




/***********************************************************************
	ErrorDump - ERROR HANDLER
***********************************************************************/


BOOL ErrorDump(LPSTR szFuncName, SQLHENV henv9, SQLHDBC hdbc9, SQLHSTMT hstmt9)
{
	UCHAR szSqlState[6];
	UCHAR szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
	SDWORD ErrorCode;
	
	SWORD ErrMsgLen;

	printf("\n\nErrorDump Called!\n");
	printf("\n\tFunction %s failed:\n", szFuncName);
	
	SQLError(henv9, hdbc9, hstmt9, szSqlState, &ErrorCode, szErrorMsg, 
		     SQL_MAX_MESSAGE_LENGTH -1, &ErrMsgLen);

	printf("\t\tState: %s\n", szSqlState);
	printf("\t\tErrorCode: %d\r\n", ErrorCode);
	printf("\t\tMessage: %s\n", szErrorMsg);

   return B_NO_ERROR;
}

/***********************************************************************
	InsertTP
***********************************************************************/
int InsertTP(SQLHSTMT hstmtU, BTI_VOID_PTR dataBuffer)
{
	SQLRETURN	rc;			// ODBC return code
	int	numRows=0;			// Number of rows in resultset
	SDWORD		cbInval=SQL_NTS;
	SDWORD		cbInval2=0;
	

	memcpy(&tpRec, dataBuffer, sizeof(tpRec));

	// Prepare the TitlePublisher Insert
	rc=SQLPrepare(hstmtU, "INSERT TITLEPUBLISHER VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", SQL_NTS);
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLPrepare for TITLEPUBLISHER INSERT FAILED", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return B_UNRECOVERABLE_ERROR;
		}	

	//  Bind input parameter columns to buffers for inserting TitlePublisher data
	SQLBindParameter(hstmtU, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 6, 0, tpRec.TitleID, 0, &cbInval);
	SQLBindParameter(hstmtU, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 80, 0, tpRec.Title, 0, &cbInval);
	SQLBindParameter(hstmtU, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 12, 0, tpRec.Type, 0, &cbInval);
	SQLBindParameter(hstmtU, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 4, 0, tpRec.PubID, 0, &cbInval);
	SQLBindParameter(hstmtU, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 15, 0, &tpRec.Price, 0, &cbInval2);
	SQLBindParameter(hstmtU, 6, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 15, 0, &tpRec.Advance, 0, &cbInval2);
	SQLBindParameter(hstmtU, 7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 10, 0, &tpRec.Royalty, 0, &cbInval2);
	SQLBindParameter(hstmtU, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 10, 0, &tpRec.YTD_Sales, 0, &cbInval2);
	SQLBindParameter(hstmtU, 9, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 40, 0, tpRec.PubName, 0, &cbInval);
	SQLBindParameter(hstmtU, 10, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, tpRec.City, 0, &cbInval);
	SQLBindParameter(hstmtU, 11, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 2, 0, tpRec.State, 0, &cbInval);
	SQLBindParameter(hstmtU, 12, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 30, 0, tpRec.Country, 0, &cbInval);	


	// Execute the INSERT
	rc=SQLExecute(hstmtU);
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLEXECUTE UPDATE TITLEPUB", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return B_UNRECOVERABLE_ERROR;
		}

	return B_NO_ERROR;
}