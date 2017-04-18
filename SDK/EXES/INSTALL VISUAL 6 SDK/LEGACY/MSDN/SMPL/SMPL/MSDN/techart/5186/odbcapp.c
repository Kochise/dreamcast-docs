/*************************************************************************
**
**	Copyright 1996  Microsoft Corporation  All Rights Reserved
**
*************************************************************************/
/***************************************************************************
   ODBCApp.C
     This program demonstrates the programming techniques of the last stage
	 in the BTRIEVE migration strategy.  The program utilizes server side 
	 resources for almost aspect and capitlizes on the power and flexibility 
	 of the ODBC API.
   

****************************************************************************/
#define ODBCVER 0x0300
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>

/***************************************************************************
   Constants
****************************************************************************/
#define EXIT_WITH_ERROR    1
#define TRUE               1
#define FALSE              0
#define NON_MATCH          999

/***************************************************************************
   Structure Type Definitions
****************************************************************************/

  // titlepub record structure
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


  // sales record structure
  struct
   {
	char	StorID[ 5 ];	//string
    char	TitleID[ 7 ];	//string
	char	OrdNum[ 21 ];	//string
	int		Qty;			//integer
	char	PayTerms[ 13 ];	//string
   } salesRec;

/***********************************************************************
	Application Globals
***********************************************************************/

/* ODBC Variables */

SQLHENV		henv1;
SQLHDBC		hdbc1;
SQLHSTMT	hstmt;

/* Other variables */
int salesQty;


/***************************************************************************
   Function Prototypes
****************************************************************************/

int GetSalesRec(SQLHSTMT hstmtU, char inval[7]);
int GetTitlePubRec(SQLHSTMT hstmtU, char *inval, int key);
int InsertTP(SQLHSTMT hstmtU);
int InsertSales(SQLHSTMT hstmtS);
int PubYTDSales(SQLHSTMT hstmtU);
int YTDSales(SQLHSTMT hstmtU);
int MakeConn(SQLHENV henv, SQLHDBC *hdbc ,SQLHSTMT *hstmt, char	cServer[31]);
BOOL ErrorDump(LPSTR szFuncName, SQLHENV henv9, SQLHDBC hdbc9, SQLHSTMT hstmt9);


/***************************************************************************
   Main
****************************************************************************/
int main( void )
{
	int			quitnow = 1;
	char		RageOn[]="999";
	char		cServer[31]="";			// Server Name
	SQLRETURN	rc;
	
	//  Allocate and Initialize the Environment 
	if(SQL_SUCCESS != SQLSetEnvAttr(henv1, SQL_ATTR_CONNECTION_POOLING,
          (SQLPOINTER) SQL_CP_ONE_PER_HENV, SQL_IS_INTEGER)) {
		printf("\n\n ODBC SQLSetEnvAttr for connection pooling PRoblem\n\n");
		return FALSE;
	}

	if(SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &henv1)) {
		printf("\n\n ODBC SQLAllocHandle PRoblem\n\n");
		return FALSE;
	}

	if(SQL_SUCCESS != SQLSetEnvAttr(henv1, SQL_ATTR_ODBC_VERSION,
                  (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER)) {
		printf("\n\n ODBC SQLSetEnvAttr PRoblem\n\n");
		return FALSE;
	}

	// Connect to the SQL Server entered by the user.  Quit if there is a problem making the connection
	printf("\n\nEnter the Server Name: ");
	gets(cServer);

	rc=MakeConn(henv1, &hdbc1, &hstmt, cServer);
	if  (rc == FALSE) 
		return FALSE;

	// Perform Operations till quitting time
	while (quitnow > 0 && quitnow <5)
	{
		printf("\n\nENTER DESIRED OPERATION:");
		printf("\n\t1 - SEARCH FOR A TITLE, IT'S SALES INFO, AND DISPLAY IT'S YTD SALES");
		printf("\n\t2 - INSERT TITLE/PUBLISHERS INFO ");
		printf("\n\t3 - INSERT SALES INFO ");
		printf("\n\t4 - UPDATE YTD_SALES FOR EACH TITLE OWNED BY A SPECIFIC PUBLISHER ");
		printf("\n\t0 - QUIT\n"); 
		printf("CHOICE: ");
		gets(RageOn);

		switch((quitnow=atoi(RageOn)))
		{
	  
			case 0:  //quit
			break;

			case 1:  // select a Title, it's current sales, and display a YTD sales total
				YTDSales(hstmt);
			break;

			case 2:  //title/publisher insert
				InsertTP(hstmt);
			break;

			case 3:  //sales insert
				InsertSales(hstmt);
			break;

			case 4:  //UPDATE YTD_SALES for each title owned by a specific publisher
				PubYTDSales(hstmt);
			break;

			default: //shouldn't go here
				printf("\nInvalid choice - Please choose an option from 0 - 4\n\n");
				quitnow = 1;
		} //switch
   } //while

	// Free all HTSTMT resources and release all HSTMT, HDBC, and HENV handles
	SQLFreeStmt(&hstmt, SQL_CLOSE);
	SQLFreeHandle(SQL_HANDLE_STMT, &hstmt);
	SQLFreeHandle(SQL_HANDLE_DBC, &hdbc1);
	SQLFreeHandle(SQL_HANDLE_ENV, &henv1);
	printf("\n\nProcess detached\n\n");

   return( (int) TRUE );
}



/*************************************************************************************
	GetSalesRec
/*************************************************************************************/

int GetSalesRec(SQLHSTMT hstmtS, char inval[7])
{
   	SQLINTEGER  cbTitleID, QtyInd;
	SDWORD		cbInval=SQL_NTS;
    SQLRETURN	rc;
    char		TitleID[ 7 ];	//string
	int			Qty;			//integer

	// Initialize pertinent storage variables
	memset( &TitleID, 0, sizeof(TitleID) );
	Qty = 0;
	salesQty = 0;

	// Bind the TitleID input parameter  for the stored procedure
	SQLBindParameter(hstmtS, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 6, 0, inval, 7, &cbInval);

	// Execute the Stored procedure and process the results until SQL_NO_DATA_FOUND
	rc=SQLExecDirect(hstmtS, "{call GetSales(?)}", SQL_NTS);
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
	{
		ErrorDump("SQLEXECUTE GetSales", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtS);
		return FALSE;
	}

	SQLBindCol(hstmtS, 1, SQL_C_CHAR, TitleID, 7, &cbTitleID);
	SQLBindCol(hstmtS, 2, SQL_C_SLONG, &Qty, 0, &QtyInd);

	while (rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO) 
	{
		rc=SQLFetch(hstmtS);
		if (rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO) {
			printf( "\n TITLE ID: %s\t QTY: %i",  TitleID, Qty);
			salesQty = salesQty + Qty;
		}
		else {
			if (rc != SQL_NO_DATA_FOUND) { 
				ErrorDump("SQLFetch ", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtS);
				SQLFreeStmt(hstmtS, SQL_UNBIND);
				SQLFreeStmt(hstmtS, SQL_RESET_PARAMS);
				SQLFreeStmt(hstmtS, SQL_CLOSE);
				return FALSE;
			}
		}	
		
	}

	// Release hstmt handle resources
	SQLFreeStmt(hstmtS, SQL_UNBIND);
	SQLFreeStmt(hstmtS, SQL_RESET_PARAMS);
	SQLFreeStmt(hstmtS, SQL_CLOSE);
	return(TRUE);
}


/*************************************************************************************
	GetTitlePubRec
/*************************************************************************************/

int GetTitlePubRec(SQLHSTMT hstmtU, char inval[100], int key)
{
	SQLINTEGER  cbTitleID, cbTitle, cbType, cbPubID, cbPubName;
	SQLINTEGER  cbCity, cbState, cbCountry;
	SQLINTEGER	RoyaltyInd, AdvanceInd, PriceInd, YTDSalesInd;
	SDWORD      cbInval = SQL_NTS;
	char		StoredProc[30];
	SQLRETURN	rc;


	// Bind input parameter for the appropriate stored procedure call based on the key param
	switch(key)
	{
		case 1: // Title_ID search
			strcpy(StoredProc, "{call GetTPByTitleID(?)}");
			SQLBindParameter(hstmtU, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 6, 0, inval, 7, &cbInval);
		break;

		case 3: // Pub_ID search
			strcpy(StoredProc, "{call GetTPByPubID(?)}");
			SQLBindParameter(hstmtU, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 4, 0, inval, 5, &cbInval);
		break;
	}

	// Execute the stored procedure and bind result set row columns to variables
	memset( &tpRec, 0, sizeof(tpRec) );

	rc=SQLExecDirect(hstmtU, StoredProc, SQL_NTS );
	SQLBindCol(hstmtU, 1, SQL_C_CHAR, tpRec.TitleID, 7, &cbTitleID);
	SQLBindCol(hstmtU, 2, SQL_C_CHAR, tpRec.Title, 81, &cbTitle);
	SQLBindCol(hstmtU, 3, SQL_C_CHAR, tpRec.Type, 13, &cbType);
	SQLBindCol(hstmtU, 4, SQL_C_CHAR, tpRec.PubID, 5, &cbPubID);
	SQLBindCol(hstmtU, 5, SQL_C_FLOAT, &tpRec.Price, 0, &PriceInd);
	SQLBindCol(hstmtU, 6, SQL_C_FLOAT, &tpRec.Advance, 0, &AdvanceInd);
	SQLBindCol(hstmtU, 7, SQL_C_SLONG, &tpRec.Royalty, 0, &RoyaltyInd);
	SQLBindCol(hstmtU, 8, SQL_C_SLONG, &tpRec.YTD_Sales, 0, &YTDSalesInd);
	SQLBindCol(hstmtU, 9, SQL_C_CHAR, tpRec.PubName, 41, &cbPubName);
	SQLBindCol(hstmtU, 10, SQL_C_CHAR, tpRec.City, 21, &cbCity);
	SQLBindCol(hstmtU, 11, SQL_C_CHAR, tpRec.State, 3, &cbState);
	SQLBindCol(hstmtU, 12, SQL_C_CHAR, tpRec.Country, 31, &cbCountry);
	
	// Process the results until SQL_NO_DATA_FOUND
	while (rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO) 
	{
		rc=SQLFetch(hstmtU);
		if (rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO) {
   			printf( "Title/Publishers Record is: \n TITLE ID: \t%s\n TITLE: \t%s\n TYPE: \t\t%s", tpRec.TitleID, tpRec.Title, tpRec.Type);
			printf( "\n PUB ID: \t%s\n PUB NAME: \t%s\n PUB CITY: \t%s\n PUB STATE: \t%s", tpRec.PubID, tpRec.PubName, tpRec.City, tpRec.State);
			printf( "\n PUB COUNTRY: \t%s \n PRICE: \t%.2f \n ADVANCE: \t%.2f", tpRec.Country, tpRec.Price, tpRec.Advance);
			printf( "\n ROYALTY: \t%i \n YTD_SALES: \t%i \n\n", tpRec.Royalty, tpRec.YTD_Sales);

			if (key ==3) {
				printf("\n\n UPDATED YTD SALES for %s = %i\n\n", tpRec.TitleID, tpRec.YTD_Sales);
				memset( &tpRec, 0, sizeof(tpRec) );
			}
		}
		else {
			if (rc != SQL_NO_DATA_FOUND) { 
				ErrorDump("SQLFetch ", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
				SQLFreeStmt(hstmtU, SQL_UNBIND);
				SQLFreeStmt(hstmtU, SQL_RESET_PARAMS);
				SQLFreeStmt(hstmtU, SQL_CLOSE);
				return FALSE;
			}
		}	
	}
	
	// Release hstmt handle resources
	SQLFreeStmt(hstmtU, SQL_UNBIND);
	SQLFreeStmt(hstmtU, SQL_RESET_PARAMS);
	SQLFreeStmt(hstmtU, SQL_CLOSE);
	return(TRUE);
}


/*************************************************************************************
	InsertTP
/*************************************************************************************/

int InsertTP(SQLHSTMT hstmtU)
{
	SQLRETURN	rc;
	char		choice[100];
	char		cont[2]="Y";
	SDWORD		cbInval=SQL_NTS;
	SDWORD		cbInval2=0;

	// Prompt for Title information for each record inserted
	while (!strcmp(cont, "Y") || !strcmp(cont, "y"))
	{
		memset( &tpRec, 0, sizeof(tpRec) );
		memset( &choice, 0, sizeof(choice) );

		printf("\n\nENTER TITLE INFO (* denotes optional info):\n");
		printf("TITLE ID [6 CHAR MAX]: ");
		gets(tpRec.TitleID);

		printf("\nTITLE [80 char max]: ");
		gets(tpRec.Title);	  

		printf("\nTYPE [12 char max]: ");
		gets(tpRec.Type);

		printf("\nPUB ID [4 char max]: ");
		gets(tpRec.PubID);

		printf("\n* PRICE [9999.99 format]: ");
		gets(choice);
		tpRec.Price = (float) atof(choice); 

		printf("\n* ADVANCE [9999.99 format]: ");
		gets(choice);
		tpRec.Advance = (float) atof(choice);

		printf("\n* ROYALTY [9999 format]: ");
		gets(choice);
		tpRec.Royalty = atoi(choice);	  

		printf("\n* YTD_SALES [9999 format char max]: ");
		gets(choice);
		tpRec.YTD_Sales = atoi(choice);

		rc=SQLPrepare(hstmtU, "INSERT TITLES(title_id, title, type, pub_id, price, advance, royalty, ytd_sales, pubdate) VALUES(?, ?, ?, ?, ?, ?, ?, ?, GETDATE())", SQL_NTS);
		if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLPrepare for TITLEPUBLISHER INSERT FAILED", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return FALSE;
		}	

		SQLBindParameter(hstmtU, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 6, 0, tpRec.TitleID, 0, &cbInval);
		SQLBindParameter(hstmtU, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 80, 0, tpRec.Title, 0, &cbInval);
		SQLBindParameter(hstmtU, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 12, 0, tpRec.Type, 0, &cbInval);
		SQLBindParameter(hstmtU, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 4, 0, tpRec.PubID, 0, &cbInval);
		SQLBindParameter(hstmtU, 5, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 15, 0, &tpRec.Price, 0, &cbInval2);
		SQLBindParameter(hstmtU, 6, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 15, 0, &tpRec.Advance, 0, &cbInval2);
		SQLBindParameter(hstmtU, 7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 10, 0, &tpRec.Royalty, 0, &cbInval2);
		SQLBindParameter(hstmtU, 8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 10, 0, &tpRec.YTD_Sales, 0, &cbInval2);
	
		if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLBINDPARAMETER UPDATE TITLEPUB", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return FALSE;
		}

		rc=SQLExecute(hstmtU);
		if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLEXECUTE UPDATE TITLEPUB", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return FALSE;
		}


		printf("\n\nContinue adding Title/Publisher Info [Y/N]:");
		gets(cont);
		if ((strcmp(cont,"Y")) && (strcmp(cont,"N"))  && (strcmp(cont,"y")) && (strcmp(cont,"n")))
			strcpy(cont, "N");
	 }
      
}


/*************************************************************************************
	InsertSales
/*************************************************************************************/

int InsertSales(SQLHSTMT hstmtS)
{
	
	SQLRETURN	rc;						// ODBC return code
	char		choice[10];
	char		cont[2]="Y";
	SDWORD		cbInval=SQL_NTS;
	SDWORD		cbInval2=0;


	// Prompt for Sales information for each record inserted
	while (!strcmp(cont, "Y")  || !strcmp(cont, "y"))
	{
		memset( &salesRec, 0, sizeof(salesRec) );

		printf("\n\nENTER SALE INFO:\n");
		printf("STORE ID [4 CHAR]: ");
		gets(salesRec.StorID);

		printf("\nORDER NUMBER [20 char max]: ");
		gets(salesRec.OrdNum);	  

		printf("\nQUANTITY [99999 format]: ");
		gets(choice);
		salesRec.Qty = atoi(choice);
		memset( &choice, 0, sizeof(choice) );

		printf("\nPAY TERMS  [13 char max]: ");
		gets(salesRec.PayTerms);	  

		printf("\nTitle ID [6 char ]: ");
		gets(salesRec.TitleID);	  

		rc=SQLPrepare(hstmtS, "INSERT SALES VALUES (?, ?, GETDATE(), ?, ?, ?)", SQL_NTS);
		if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLPrepare for SALES INSERT FAILED", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtS);
			return FALSE;
		}	

		SQLBindParameter(hstmtS, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 4, 0, salesRec.StorID, 0, &cbInval);
		SQLBindParameter(hstmtS, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 20, 0, salesRec.OrdNum, 0, &cbInval);
		SQLBindParameter(hstmtS, 3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 10, 0, &salesRec.Qty, 0, &cbInval2);
		SQLBindParameter(hstmtS, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 13, 0, salesRec.PayTerms, 0, &cbInval);
		SQLBindParameter(hstmtS, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 6, 0, salesRec.TitleID, 0, &cbInval);

		rc=SQLExecute(hstmtS);
		if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO))
		{
			ErrorDump("SQLEXECUTE INSERT SALES", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtS);
			return FALSE;
		}

		printf("\n\nContinue adding Sales Info [Y/N]:");
		gets(cont);
		if ((strcmp(cont,"Y")) && (strcmp(cont,"N")) && (strcmp(cont,"y")) && (strcmp(cont,"n")))
			strcpy(cont, "N");
	}

	return(TRUE);
}

/*************************************************************************************
	  PubYTDSales
/*************************************************************************************/

int PubYTDSales(SQLHSTMT hstmtU)
{
	SQLRETURN	rc;				// ODBC return code
	int			numRows=0;		// Number of rows in resultset  	
	int			salesQty=0;
	char		choice[5];
	SDWORD      cbInval = SQL_NTS;
	

	// Prompt for PubID information to drive the UPDATE
    printf("\n\nENTER THE 4 CHAR PUBLISHER ID: ");
    gets(choice);
    printf("\n\n");
	
	memset( &tpRec, 0, sizeof(tpRec) );

	// Bind the PubID input parameter  for the stored procedure
	rc = SQLBindParameter(hstmtU, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 4, 0, choice, 5, &cbInval);
	if  (rc!=SQL_SUCCESS && rc!=SQL_SUCCESS_WITH_INFO) {
		ErrorDump("SQLBIND SELECT TITLEPUB 1", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
		SQLFreeStmt(hstmtU, SQL_RESET_PARAMS);
		SQLFreeStmt(hstmtU, SQL_CLOSE);
		return FALSE;
	}	

	// Execute the UPDATE
	rc=SQLExecDirect(hstmtU, "{call UpdtTitlesByPubID(?)}", SQL_NTS);
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){
			ErrorDump("SQLEXECUTE UPDATE TITLEPUB", SQL_NULL_HENV, SQL_NULL_HDBC, hstmtU);
			return FALSE;
	}
	
	// Print of the UPDATEd titles
	GetTitlePubRec(hstmtU, &choice, 3);	

	return TRUE;		
}


/*************************************************************************************
	  YTDSales
/*************************************************************************************/

//int YTDSales(SQLHSTMT hstmtU, SQLHSTMT hstmtS)
int YTDSales(SQLHSTMT hstmtU)
{
	char	choice[100];
	SQLRETURN rc;
	 
	// Prompt for TitleID information to drive the SELECT queries for TITLES and SALES
	printf("\n\nENTER THE 6 CHAR TITLE ID: ");
    gets(choice);
    printf("\n\n");

	// Get the TITLES and SALES records
	rc=GetTitlePubRec(hstmtU, choice, 1);	

	if (rc == TRUE)
		rc=GetSalesRec(hstmtU, choice);
	else
		return FALSE;

	// Print out YTD_SALES total for the TitleID
	if (rc == TRUE){
		salesQty = tpRec.YTD_Sales + salesQty;
		printf("\n\n YTD SALES for %s = %i\n\n", tpRec.TitleID, salesQty);
	}
	return TRUE;
}


/***********************************************************************
	MakeConn
/***********************************************************************/

int MakeConn(SQLHENV henv, SQLHDBC *hdbc ,SQLHSTMT *hstmt, char	cServer[31])
{
	SQLRETURN  rc;			//ODBC return code

	// Allocate a connection handle and set login timeout to 5 seconds and connect to SQL Server
	rc = SQLAllocHandle(SQL_HANDLE_DBC, henv, hdbc); 
	if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) 
		rc=SQLSetConnectAttr(*hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER	) 5, 0);		
	else{
		ErrorDump("SQLAllocHandle HDBC", SQL_NULL_HENV, *hdbc, SQL_NULL_HSTMT);
		return FALSE;
	}

	// Make the connection to cServer SQL Server
	rc = SQLConnect(*hdbc, (SQLCHAR *) cServer, (SQLSMALLINT) strlen(cServer),
	                            (SQLCHAR *) "pubsuser", (SQLSMALLINT) strlen("pubsuser"),
	                            (SQLCHAR *) "pubsuser", (SQLSMALLINT) strlen("pubsuser"));
	
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){
		ErrorDump("SQLConnect", SQL_NULL_HENV, *hdbc, SQL_NULL_HSTMT);
		return FALSE;
	}

	// Allocate a statement handle for use with this connection
	rc = SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, hstmt); 
	if ((rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)){
		ErrorDump("SQLAllocHandle HSTMT", SQL_NULL_HENV, SQL_NULL_HDBC, *hstmt);
		return FALSE;
	}
	
	return TRUE;
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

   return TRUE;
}
