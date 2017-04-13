//---------------------------------------------------------------------------------------
//
// PROGRAM: quiktest.c
//        This code is furnished on an as-is basis as part of the ODBC SDK and is
//        intended for example purposes only.
//
//  PURPOSE: This is a Quick Test of the basic functionality of an ODBC driver.
//
//  FUNCTIONS:
//	     QuickTest() - performs the quick test focusing on basic functionalities.
//
//--------------------------------------------------------------------------------------------
#pragma warning (disable : 4703)

#define QUIKTEST

#include "autotest.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
// #include <crtdbg.h>
#include "sql.h"
#include "sqlext.h"
#include "quiktest.h"

//--------------------------------------------------------------------------------------
//	  static
//--------------------------------------------------------------------------------------
static TCHAR  vszFile[]				= TEXT(__FILE__);

static LPTSTR sz07009					= TEXT("07009");
static LPTSTR szIM001					= TEXT("IM001");
static LPTSTR szHYC00					= TEXT("HYC00");
static LPTSTR szHY009					= TEXT("HY009");
static LPTSTR szHY091					= TEXT("HY091");
static LPTSTR szHY092					= TEXT("HY092");
static LPTSTR szISO						= TEXT("ISO 9075");
static LPTSTR szODBC30					= TEXT("ODBC 3.0");
static LPTSTR szNotSupported			= TEXT("did not return Not supported message");
static LPTSTR szSQLSETCONNECTATTR	= TEXT("SQLSetConnectAttr");
static LPTSTR szSQLGETCONNECTATTR	= TEXT("SQLGetConnecTAttr");
static LPTSTR szSQLGETINFO				= TEXT("SQLGetInfo");
static LPTSTR szSQLGETTYPEINFO		= TEXT("SQLGetTypeInfo");
static LPTSTR szSQLALLOCHANDLE		= TEXT("SQLAllocHandle");
static LPTSTR szSQLALLOCSTMT			= TEXT("SQLAllocStmt");
static LPTSTR szSQLALLOCCONNECT		= TEXT("SQLAllocConnect");
static LPTSTR szSQLALLOCENV			= TEXT("SQLAllocEnv");
static LPTSTR szSQLSETSTMTATTR		= TEXT("SQLSetStmtAttr");
static LPTSTR szSQLGETSTMTATTR		= TEXT("SQLGetStmtAttr");
static LPTSTR szSQLSETSTMTOPTION		= TEXT("SQLSetStmtOption");
static LPTSTR szSQLGETSTMTOPTION		= TEXT("SQLGetStmtOption");
static LPTSTR szSQLSETCONNECTOPTION	= TEXT("SQLSetConnectOption");
static LPTSTR szSQLGETCONNECTOPTION	= TEXT("SQLGetConnectOption");
static LPTSTR szSQLFETCH				= TEXT("SQLFetch");
static LPTSTR szSQLBINDCOL				= TEXT("SQLBindCol");
static LPTSTR szSQLFOREIGNKEYS		= TEXT("SQLForeignkeys");
static LPTSTR szSQLFREEHANDLE			= TEXT("SQLFreeHandle");
static LPTSTR szSQLFREECONNECT		= TEXT("SQLFreeConnect");
static LPTSTR szSQLFREEENV				= TEXT("SQLFreeEnv");
static LPTSTR szSQLGETDESCREC			= TEXT("SQLGetDescRec");
static LPTSTR szSQLSETDESCREC			= TEXT("SQLSetDescRec");
static LPTSTR szSQLGETDESCFIELD		= TEXT("SQLGetDescField");
static LPTSTR szSQLSETDESCFIELD		= TEXT("SQLSetDescField");
static LPTSTR szSQLCOPYDESC			= TEXT("SQLCopyDesc");
static LPTSTR szSQLSETENVATTR			= TEXT("SQLSetEnvAttr");
static LPTSTR szSQLGETENVATTR			= TEXT("SQLGetEnvAttr");
static LPTSTR szSQLFREESTMT			= TEXT("SQLFreeStmt");
static LPTSTR szSQLENDTRAN				= TEXT("SQLEndTran");
static LPTSTR szSQLGETCURSORNAME		= TEXT("SQLGetCursorName");
static LPTSTR szSQLEXECDIRECT			= TEXT("SQLExecDirect");
static LPTSTR szSQLPUTDATA				= TEXT("SQLPutData");
static LPTSTR szSQLPARAMDATA			= TEXT("SQLParamData");
static LPTSTR szSQLROWCOUNT			= TEXT("SQLRowCount");
static LPTSTR szSQLSETPARAM			= TEXT("SQLSetParam");
static LPTSTR szSQLBINDPARAMETER		= TEXT("SQLBindParameter");
static LPTSTR szSQLBINDPARAM			= TEXT("SQLBindParam");
static LPTSTR szSQLPREPARE				= TEXT("SQLPrepare");
static LPTSTR szSQLEXECUTE				= TEXT("SQLExecute");
static LPTSTR szSQLCOLATTRIBUTES		= TEXT("SQLColAttributes");
static LPTSTR szSQLGETDATA				= TEXT("SQLGetData");
static LPTSTR szSQLCOLUMNS				= TEXT("SQLColumns");
static LPTSTR szSQLGETFUNCTIONS		= TEXT("SQLGetFunctions");				  
static LPTSTR szSQLDRIVERCONNECT		= TEXT("SQLDriverConnect");
static LPTSTR szSQLDISCONNECT			= TEXT("SQLDisconnect");
static LPTSTR szSQLCONNECT				= TEXT("SQLConnect");
static LPTSTR szSQLCANCEL				= TEXT("SQLCancel");
static LPTSTR szSQLDESCRIBECOL		= TEXT("SQLDescribeCol");
static LPTSTR szSQLTABLES				= TEXT("SQLTables");
static LPTSTR szSQLSPECIALCOLUMNS	= TEXT("SQLSpecialColumns");
static LPTSTR szSQLDESCRIBEPARAM		= TEXT("SQLDescribeParam");
static LPTSTR szSQLNUMPARAMS			= TEXT("SQLNumParams");
static LPTSTR szSQLPARAMOPTIONS		= TEXT("SQLParamOptions");
static LPTSTR szSQLPRIMARYKEYS		= TEXT("SQLPrimaryKeys");
static LPTSTR szSQLEXTENDEDFETCH		= TEXT("SQLExtendedFetch");
static LPTSTR szSELECTSTAR				= TEXT("select * from %s");
static LPTSTR szQUICKREBIND			= TEXT("Quick Rebind");
static LPTSTR szSQLBROWSECONNECT		= TEXT("SQLBrowseConnect");
static LPTSTR szBLANKLINE				= TEXT(" ");
static LPTSTR szTAB						= TEXT("\t");
static LPTSTR szSQLNUMRESULTCOLS		= TEXT("SQLNumResultCols");
static LPTSTR szSQLSETSCROLLOPTIONS	= TEXT("SQLSetScrollOptions");
static LPTSTR szSQLFETCHSCROLL		= TEXT("SQLFetchScroll");
static LPTSTR szSQLSTATISTICS			= TEXT("SQLStatistics");
static LPTSTR szSQLCLOSECURSOR		= TEXT("SQLCloseCursor");
static LPTSTR szSQLGETDIAGREC			= TEXT("SQLGetDiagRec");
static LPTSTR szSQLGETDIAGFIELD		= TEXT("SQLGetDiagField");
static LPTSTR szRETDATA					= TEXT("returned data");
static LPTSTR szINCORRECTOUTLEN		= TEXT("incorrect outlen");
static LPTSTR szSQLNATIVESQL			= TEXT("SQLNativeSql");
static LPTSTR szSQLNATIVESQLW			= TEXT("SQLNativeSqlW");
static LPTSTR szSQLCONNECTW			= TEXT("SQLConnectW");
static LPTSTR szSQLTABLESA				= TEXT("SQLTablesA");
static LPTSTR szSQLTABLESW				= TEXT("SQLTablesW");
static LPTSTR szSQLCOLUMNSA			= TEXT("SQLColumnsA");
static LPTSTR szSQLCOLUMNSW			= TEXT("SQLColumnsW");
static LPTSTR szSQLEXECDIRECTA		= TEXT("SQLExecDirectA");
static LPTSTR szSQLEXECDIRECTW		= TEXT("SQLExecDirectW");

LPTSTR iTestNames[]={
	TEXT("Test Connection Options"),
	TEXT("Test Statement Options"),
	TEXT("Test SQLGetCursorName"),
	TEXT("Test Data"),
	TEXT("Test SQLNumResultCols"),
	TEXT("Test Meta-Data"),
	TEXT("Test Searched Query"),
	TEXT("Test Large Query"),
	TEXT("Test SQLTables"),
	TEXT("Test SQLStatistics"),
	TEXT("Test SQLSpecialColumns"),
	TEXT("Test 'Like' Query"),
	TEXT("Test SQLForeignKeys"),
	TEXT("Test SQLBrowseConnect"),
	TEXT("Test SQLDataSources"),
	TEXT("Test SQLDrivers"),
	TEXT("Test SQLMoreResults"),
	TEXT("Test SQLNativeSQL"),
	TEXT("Test SQLDescribeParam"),
	TEXT("Test SQLNumParams"),
	TEXT("Test SQLParamOptions"),
	TEXT("Test SQLPrimaryKeys"),
	TEXT("Test SQLProcedures"),
	TEXT("Test SQLTablePrivileges"),
	TEXT("Test SQLColumnPrivileges"),
	TEXT("Test SQLSetScrollOptions"),
	TEXT("Test SQLExtendedFetch"),
	TEXT("Test SQL_OJ_CAPABILITIES"),
	TEXT("Test SQLSetConnectAttr"),
	TEXT("Test SQLSetStmtAttr"),
	TEXT("Test Threading"),
	TEXT("Test GetDescField"),
	TEXT("Test SetDescField"),
	TEXT("Test GetDescRec"),
	TEXT("Test SetDescRec"),
	TEXT("Test CopyDesc"),
	TEXT("Test Descriptor Defaults"),
	TEXT("Test Usage of Descriptor"),
	TEXT("Test Environment Attributes"),
	TEXT("Test SQLEndTran"),
	TEXT("Test SQLBindParam"),
	TEXT("Test Quick Rebind"),
	TEXT("Test SQLFetchScroll"),
	TEXT("Test GetDiagRec"),
	TEXT("Test GetDiagField"),
	TEXT("Test MixedAnsiUnicode")
};


typedef struct tagHANDLES
{
	SWORD			fHandleType;
	SQLHANDLE	hHandle;

} HANDLES, *lpHANDLES;

SUPPORTOPTINFO OptionList[] = {SQL_SO_FORWARD_ONLY, SQL_SCROLL_FORWARD_ONLY,
									SQL_SO_KEYSET_DRIVEN, SQL_SCROLL_KEYSET_DRIVEN,
									SQL_SO_DYNAMIC, SQL_SCROLL_DYNAMIC};

SUPPORTCONCURINFO ConcurList[] = {SQL_SCCO_READ_ONLY, SQL_CONCUR_READ_ONLY,
									SQL_SCCO_LOCK, SQL_CONCUR_LOCK,
									SQL_SCCO_OPT_TIMESTAMP, SQL_CONCUR_TIMESTAMP,
									SQL_SCCO_OPT_VALUES, SQL_CONCUR_VALUES};


/*--------------------------------------------------------------------------------------*/
/*	 globals																										 */
/*--------------------------------------------------------------------------------------*/
lpSERVERINFO	lpSI = NULL;
UWORD				fBindParameter=FALSE,
					fDiagRecSupported=FALSE,
					fDiagFieldSupported=FALSE,
					uDriverODBCVer=0;
UWORD				guwRowCount=0;	// Count of rows in the automaketable
  
/* these are globals so that the error functions can access them without
		needing to have them passed to every error check */
static HENV            henv=SQL_NULL_HENV;
static HDBC            hdbc=SQL_NULL_HDBC;
static HSTMT           hstmt=SQL_NULL_HSTMT;
static SQLHDESC        hdesc=SQL_NULL_HDESC;



//globals for test descriptors
TIMESTAMP_STRUCT tsval= {1955, 12, 31, 23, 59, 59, 999};
SQLINTEGER cbtsval=sizeof(TIMESTAMP_STRUCT);
SQLINTEGER cbValueMax, cbValue, swBindOffset=128;
SQLUINTEGER RowsProcessed;
SQLSMALLINT DescBuf[MAX_DESC_BUF]; 
SQLUSMALLINT StatusArray[STATUS_ARRAY_SIZE];
SQLTCHAR buf[MAX_STRING_SIZE];
SQLTCHAR szParamName[MAX_STRING_SIZE]=TEXT("Parameter Name");

struct tagDescType {
	SQLUSMALLINT	uwDescType;
	SQLUSMALLINT	uwTypeMask;
	TCHAR szDescName[4];
} DescTypes[] = {
	SQL_ATTR_APP_ROW_DESC,		DESC_ARD,	TEXT("ARD"),
	SQL_ATTR_APP_PARAM_DESC,	DESC_APD,	TEXT("APD"),
	SQL_ATTR_IMP_ROW_DESC,		DESC_IRD,	TEXT("IRD"),
	SQL_ATTR_IMP_PARAM_DESC,	DESC_IPD,	TEXT("IPD")
};

struct tagDescInfo {
	SQLSMALLINT uwDescField;
	LPTSTR szDescFieldName;
	BOOL fHeader;
	SQLSMALLINT fGettable;	// Can be retrieved for given descriptor types
	SQLSMALLINT fSettable;	// Can be set for given descriptor types
	SQLSMALLINT fDefault;	// Has a default value for the descriptor types
	SQLINTEGER NewValue;
	SQLINTEGER DefaultVal;
	SQLSMALLINT cbValue;
	SQLINTEGER size;
} rgDescInfo[] =	{
	// Test expects all header fields to be listed first.  The TYPE field must be the first record field listed.
	// size should be set to 0 for string fields, since we don't know up front what to set it to
	// Field ID								Field Name											Header	Gettable			Settable		fDefault		New Value							Default Value			Data Size					Data Type

	//Header fields
	SQL_DESC_COUNT,						TEXT("SQL_DESC_COUNT"),						TRUE,	DESC_ALL,		DESC_MOST,	DESC_MOST,	1,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_ALLOC_TYPE,				TEXT("SQL_DESC_ALLOC_TYPE"),				TRUE,	DESC_ALL,		DESC_NONE,	DESC_ALL,	0,								SQL_DESC_ALLOC_AUTO,	sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_ARRAY_SIZE,				TEXT("SQL_DESC_ARRAY_SIZE"),				TRUE,	DESC_AD,		DESC_AD,	DESC_AD,	STATUS_ARRAY_SIZE,				1,						sizeof(SQLUINTEGER),	SQL_IS_UINTEGER,
	SQL_DESC_ARRAY_STATUS_PTR,			TEXT("SQL_DESC_ARRAY_STATUS_PTR"),			TRUE,	DESC_ALL,		DESC_ALL,	DESC_ALL,	(SQLINTEGER)(StatusArray),		(SQLINTEGER)NULL,		sizeof(SQLPOINTER),		SQL_IS_POINTER,
	SQL_DESC_BIND_OFFSET_PTR,			TEXT("SQL_DESC_BIND_OFFSET_PTR"),			TRUE,	DESC_AD,		DESC_AD,	DESC_AD,	(SQLINTEGER)(&swBindOffset),	(SQLINTEGER)NULL,		sizeof(SQLPOINTER),		SQL_IS_POINTER,
	SQL_DESC_BIND_TYPE,					TEXT("SQL_DESC_BIND_TYPE"),					TRUE,	DESC_AD,		DESC_AD,	DESC_AD,	BIND_SIZE,						0,						sizeof(SQLINTEGER),		SQL_IS_INTEGER,
//	SQL_DESC_OUT_OF_LINE_HEAP,			TEXT("SQL_DESC_OUT_OF_LINE_HEAP"),			TRUE,	DESC_AD,		DESC_AD,				(SQLINTEGER)(StatusArray),	sizeof(SQLINTEGER),	SQL_IS_POINTER,
//	SQL_DESC_OUT_OF_LINE_HEAP_OCTET_LENGTH,	TEXT("SQL_DESC_OUT_OF_LINE_HEAP_OCTET_LENGTH"),	TRUE, DESC_AD,	DESC_AD,																sizeof(StatusArray),					sizeof(SQLINTEGER),	SQL_IS_NOT_POINTER,
	SQL_DESC_ROWS_PROCESSED_PTR,		TEXT("SQL_DESC_ROWS_PROCESSED_PTR"),		TRUE,	DESC_ID,		DESC_ID,	DESC_ID,	(SQLINTEGER)(&RowsProcessed),	(SQLINTEGER)NULL,		sizeof(SQLPOINTER),		SQL_IS_POINTER,

	// Record fields
	SQL_DESC_TYPE,						TEXT("SQL_DESC_TYPE"), 						FALSE,	DESC_ALL,		DESC_MOST,	DESC_AD,	SQL_DATETIME,					SQL_C_DEFAULT,			sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_DATETIME_INTERVAL_CODE,	TEXT("SQL_DESC_DATETIME_INTERVAL_CODE"),	FALSE,	DESC_ALL, 		DESC_MOST,	DESC_NONE,	SQL_CODE_TIMESTAMP,				0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_CONCISE_TYPE,				TEXT("SQL_DESC_CONCISE_TYPE"),				FALSE,	DESC_ALL,		DESC_MOST,	DESC_AD,	SQL_TYPE_TIMESTAMP,				SQL_C_DEFAULT,			sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_AUTO_UNIQUE_VALUE,			TEXT("SQL_DESC_AUTO_UNIQUE_VALUE"),			FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLINTEGER),		SQL_IS_INTEGER,
//	SQL_DESC_BIND_OUT_OF_LINE,			TEXT("SQL_DESC_BIND_OUT_OF_LINE"),			FALSE,	DESC_AD,		DESC_AD,				SQL_TRUE,												sizeof(SQLSMALLINT),	SQL_IS_NOT_POINTER,
	SQL_DESC_BASE_COLUMN_NAME,			TEXT("SQL_DESC_BASE_COLUMN_NAME"),			FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_CASE_SENSITIVE,			TEXT("SQL_DESC_CASE_SENSITIVE"),			FALSE,	DESC_ID,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLINTEGER),		SQL_IS_INTEGER,
	SQL_DESC_CATALOG_NAME,				TEXT("SQL_DESC_CATALOG_NAME"),				FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_DATETIME_INTERVAL_PRECISION, TEXT("SQL_DESC_DATETIME_INTERVAL_PRECISION"),	FALSE, DESC_ALL,DESC_MOST,	DESC_NONE,	3,									0,						sizeof(SQLINTEGER),		SQL_IS_INTEGER,
	SQL_DESC_DISPLAY_SIZE,				TEXT("SQL_DESC_DISPLAY_SIZE"),				FALSE,	DESC_IRD,		DESC_NONE, 	DESC_NONE,	0,								0,						sizeof(SQLINTEGER),		SQL_IS_INTEGER,
	SQL_DESC_FIXED_PREC_SCALE,			TEXT("SQL_DESC_FIXED_PREC_SCALE"),			FALSE,	DESC_ID,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_LABEL,						TEXT("SQL_DESC_LABEL"),						FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_LENGTH,					TEXT("SQL_DESC_LENGTH"),					FALSE,	DESC_ALL,		DESC_MOST,	DESC_NONE,	23,								0,						sizeof(SQLUINTEGER),	SQL_IS_UINTEGER,
	SQL_DESC_LITERAL_PREFIX,			TEXT("SQL_DESC_LITERAL_PREFIX"),			FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_LITERAL_SUFFIX,			TEXT("SQL_DESC_LITERAL_SUFFIX"),			FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_LOCAL_TYPE_NAME,			TEXT("SQL_DESC_LOCAL_TYPE_NAME"),			FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_NAME,						TEXT("SQL_DESC_NAME"),						FALSE,	DESC_ID,		DESC_IPD,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_NULLABLE,					TEXT("SQL_DESC_NULLABLE"),					FALSE,	DESC_ID,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_OCTET_LENGTH,				TEXT("SQL_DESC_OCTET_LENGTH"),				FALSE,	DESC_ALL,		DESC_MOST,	DESC_NONE,	sizeof(tsval),					0,						sizeof(SQLINTEGER),		SQL_IS_INTEGER,
	SQL_DESC_OCTET_LENGTH_PTR,			TEXT("SQL_DESC_OCTET_LENGTH_PTR"),			FALSE,	DESC_AD,		DESC_AD,	DESC_AD,	(SQLINTEGER)(&cbtsval),			(SQLINTEGER)NULL,		sizeof(SQLINTEGER),		SQL_IS_POINTER,
	SQL_DESC_PARAMETER_TYPE,			TEXT("SQL_DESC_PARAMETER_TYPE"),			FALSE,	DESC_IPD,		DESC_IPD,	DESC_IPD,	SQL_PARAM_OUTPUT,				SQL_PARAM_INPUT,		sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_PRECISION,					TEXT("SQL_DESC_PRECISION"),					FALSE,	DESC_ALL,		DESC_MOST,	DESC_NONE,	23,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_SCALE,						TEXT("SQL_DESC_SCALE"),						FALSE,	DESC_ALL,		DESC_MOST,	DESC_NONE,	3,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_SCHEMA_NAME,				TEXT("SQL_DESC_SCHEMA_NAME"),				FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_SEARCHABLE,				TEXT("SQL_DESC_SEARCHABLE"),				FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_TABLE_NAME,				TEXT("SQL_DESC_TABLE_NAME"),				FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_TYPE_NAME,					TEXT("SQL_DESC_TYPE_NAME"),					FALSE,	DESC_ID,		DESC_NONE,	DESC_NONE,	(SQLINTEGER)szParamName,		0,						sizeof(SQLCHAR),		0,
	SQL_DESC_UNSIGNED,					TEXT("SQL_DESC_UNSIGNED"),					FALSE,	DESC_ID,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_UPDATABLE,					TEXT("SQL_DESC_UPDATABLE"),					FALSE,	DESC_IRD,		DESC_NONE,	DESC_NONE,	0,								0,						sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_INDICATOR_PTR,				TEXT("SQL_DESC_INDICATOR_PTR"),				FALSE,	DESC_AD,		DESC_AD,	DESC_AD,	SQL_NULL_DATA,					(SQLINTEGER)NULL,		sizeof(SQLPOINTER),		SQL_IS_POINTER,
	SQL_DESC_UNNAMED,					TEXT("SQL_DESC_UNNAMED"),					FALSE,	DESC_ID,		DESC_IPD,	DESC_NONE,	SQL_UNNAMED,					SQL_NAMED,				sizeof(SQLSMALLINT),	SQL_IS_SMALLINT,
	SQL_DESC_DATA_PTR,					TEXT("SQL_DESC_DATA_PTR"),					FALSE,	DESC_AD,		DESC_MOST,	DESC_AD,	(SQLINTEGER)&tsval,				(SQLINTEGER)NULL,		sizeof(SQLPOINTER),		SQL_IS_POINTER
 };

struct tagDIAGINFO {
	SQLSMALLINT uwDescField;
	LPTSTR szDescFieldName;
	SWORD irecRecNumber;
} rgDiagInfo[] =	{
//	SQL_DIAG_CURSOR_ROW_COUNT,			TEXT("SQL_DIAG_CURSOR_ROW_COUNT"),			0,
//	SQL_DIAG_DYNAMIC_FUNCTION,			TEXT("SQL_DIAG_DYNAMIC_FUNCTION"),			0,
//	SQL_DIAG_DYNAMIC_FUNCTION_CODE,	TEXT("SQL_DIAG_DYNAMIC_FUNCTION_CODE"),	0,
	SQL_DIAG_NUMBER,						TEXT("SQL_DIAG_NUMBER"),						0,
	SQL_DIAG_RETURNCODE,					TEXT("SQL_DIAG_RETURNCODE"),					0,
//	SQL_DIAG_ROW_NUMBER,					TEXT("SQL_DIAG_ROW_NUMBER"),					0,
//	SQL_DIAG_COLUMN_NUMBER,				TEXT("SQL_DIAG_COLUMN_NUMBER"),				1,
//	SQL_DIAG_ROW_COUNT,					TEXT("SQL_DIAG_ROW_COUNT"),					0,
	SQL_DIAG_SQLSTATE,					TEXT("SQL_DIAG_SQLSTATE"),						1,
	SQL_DIAG_NATIVE,						TEXT("SQL_DIAG_NATIVE"),						1,
	SQL_DIAG_MESSAGE_TEXT,				TEXT("SQL_DIAG_MESSAGE_TEXT"),				1,
	SQL_DIAG_CLASS_ORIGIN,				TEXT("SQL_DIAG_CLASS_ORIGIN"),				1,
	SQL_DIAG_SUBCLASS_ORIGIN,			TEXT("SQL_DIAG_SUBCLASS_ORIGIN"),			1,
//	SQL_DIAG_CONNECTION_NAME,			TEXT("SQL_DIAG_CONNECTION_NAME"),			1,
	SQL_DIAG_SERVER_NAME,				TEXT("SQL_DIAG_SERVER_NAME"),					1,
};

BOOL	g_f3XDriver=FALSE;

//the insert statement buffer	to hold the insert statement
TCHAR szInsertStmt[MAX_STRING_SIZE];

//-----------------------------------------------------------------------
//      Function:               Supported
//-----------------------------------------------------------------------

_inline UWORD  PASCAL Supported(UWORD uwSQLFunc)
{
	UWORD		fLevel2=FALSE;
	RETCODE	rc=SQL_SUCCESS;

	rc = SQLGetFunctions(hdbc, uwSQLFunc,&fLevel2);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETFUNCTIONS);

	return(fLevel2);

} //Supported()


/*------------------------------------------------------------------------------
 *	Function:	CheckDataResults - To check data returned by Fetch calls 
 *	Checks data at (row, col) in result set against (row, col) in table
 * ----------------------------------------------------------------------------*/
BOOL CheckDataResults(SWORD row, SWORD iTableCol, FIELDINFO*  pField, DSTRUCT* pDataStr,
							 SDWORD cbValue, TCHAR* rgbValue)
{
	if((pField ->nullable)&& (cbValue<1))
	{
		if(cbValue == SQL_NULL_DATA && pDataStr[iTableCol].cb == SQL_NULL_DATA)
			return TRUE;
		return FALSE;
	}

	return CmpODBCtoCHAR(pDataStr, rgbValue, pField->wSQLType, iTableCol);
}


/*------------------------------------------------------------------------------
/	Function:	BinToHex
/	Purpose:	Render a buffer contents as a hexidecimal string.
/*----------------------------------------------------------------------------*/

void PASCAL BinToHex(PTR rgbValue, SWORD cbValue, LPTSTR szHexString)
{
	UWORD ib;
	LPTSTR pch;
	TCHAR rgchDigits[] = TEXT("0123456789ABCDEF");

	lstrcpy(szHexString, TEXT("0x"));
	if(cbValue > (MAX_STRING_SIZE - 3)/2 || cbValue < 0)
		cbValue = (MAX_STRING_SIZE - 3)/2;

	pch = &szHexString[lstrlen(szHexString)];
	for(ib=0; ib < cbValue; ib++)
		{
		*pch++ = rgchDigits[((LPBYTE)rgbValue)[ib] >> 4];
		*pch++ = rgchDigits[((LPBYTE)rgbValue)[ib] & 0xF];
		}
	*pch = TEXT('\0');

} /* BinToHex() */



/*-----------------------------------------------------------------------*/
/*      Function:               SearchForError                           */
/*-----------------------------------------------------------------------*/

_inline int PASCAL SearchForError(HENV henv, HDBC hdbc,HSTMT hstmt,LPTSTR szFindState)
{
	TCHAR buf[MAX_STRING_SIZE];
	RETCODE rc;
	TCHAR szState[6];
	int found = FALSE;

	for(rc = SQLError(henv, hdbc, hstmt, szState, NULL, buf, MAX_STRING_SIZE, NULL)
		; !found && (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
		; rc = SQLError(henv, NULL, NULL, szState, NULL, buf, MAX_STRING_SIZE, NULL)) 
	{
		found = lstrcmp(szState, szFindState) == 0;
	}

	return(found);

} /* SearchForError() */


/*-----------------------------------------------------------------------*/
/*      Function:               szWrite                                  */
/*-----------------------------------------------------------------------*/

_inline VOID WINAPI szWrite(LPTSTR szStr, BOOL fNewLine)
{
	szLogPrintf(lpSI, FALSE, szStr);
	if(fNewLine)
		szLogPrintf(lpSI, FALSE, TEXT("\r\n"));
}

/*-----------------------------------------------------------------------*/
/*      Function:               GetErrors			                         */
/*-----------------------------------------------------------------------*/

VOID PASCAL GetErrors(HENV henv,HDBC hdbc,HSTMT hstmt)
{
	TCHAR buf[MAX_ERROR_SIZE];
	TCHAR largebuf[COMBINED_SIZE];
	TCHAR szState[100];
	RETCODE rc=SQL_SUCCESS;

	for(rc = SQLError(henv, hdbc, hstmt, szState, NULL, buf, MAX_ERROR_SIZE, NULL)
		; RC_SUCCESSFUL(rc)
		; rc = SQLError(henv, NULL, NULL, szState, NULL, buf, MAX_ERROR_SIZE, NULL))
	{
		wsprintf(largebuf,TEXT("\t\t\tState: %s"), szState);
		szWrite(largebuf, TRUE);
		wsprintf(largebuf,TEXT("\t\t\tError: %s"), buf);
		szWrite(largebuf, TRUE);
	}

} /* GetErrors() */


/*-----------------------------------------------------------------------*/
/*      Function:               GetDiagRecs		                         */
/*-----------------------------------------------------------------------*/

VOID PASCAL GetDiagRecs(SWORD fHandleType,SQLHANDLE hHandle)
{
	TCHAR		szMessageText[XLARGEBUFF]=TEXT(""),
				szBuff[XLARGEBUFF]=TEXT("");
	TCHAR		szSQLState[100]=TEXT("");
	RETCODE	rc=SQL_SUCCESS;
	SWORD		irecRecNumber=0;
	SDWORD	fNativeError=0;
	SWORD		cbBufferLength=sizeof(szMessageText),
				cbTextLength=0;
	SDWORD	sdNumRecs=0;

	if (fDiagFieldSupported)
	{
		/* Get number of diag, records */
		rc = SQLGetDiagField(fHandleType, hHandle,0,SQL_DIAG_NUMBER,
			&sdNumRecs,sizeof(sdNumRecs),NULL);
	}


	for(irecRecNumber=1;(irecRecNumber <= sdNumRecs) && RC_SUCCESSFUL(rc);irecRecNumber++)
	{
		rc = SQLGetDiagRec(fHandleType, hHandle, irecRecNumber,szSQLState,&fNativeError,
			szMessageText,cbBufferLength,&cbTextLength);

		if (RC_SUCCESSFUL(rc))
		{
			wsprintf(szBuff,TEXT("\t\t\tState: %s"), szSQLState);
			szWrite(szBuff, TRUE);
			wsprintf(szBuff,TEXT("\t\t\tError: %s"), szMessageText);
			szWrite(szBuff, TRUE);
		}

	}


} /* GetErrors() */



/*-----------------------------------------------------------------------*/
/*      Function:               DisplayAllErrors                         */
/*-----------------------------------------------------------------------*/

void  PASCAL DisplayAllErrors()
{
	if (!fDiagRecSupported)
	{
		GetErrors(henv,NULL,NULL);
		GetErrors(NULL,hdbc,NULL);
		GetErrors(NULL,NULL,hstmt);
	}
	else
	{
		GetDiagRecs(SQL_HANDLE_ENV,henv);
		GetDiagRecs(SQL_HANDLE_DBC,hdbc);
		GetDiagRecs(SQL_HANDLE_STMT,hstmt);
		GetDiagRecs(SQL_HANDLE_DESC,hdesc);
	}

} /* DisplayAllErrors() */


/*-----------------------------------------------------------------------*/
/*      Function:               RetcodeToTCHAR                            */
/*-----------------------------------------------------------------------*/

LPTSTR  PASCAL RetcodeToTCHAR(RETCODE retcode, LPTSTR buf)
{
	switch (retcode) 
		{
		case SQL_SUCCESS:
			lstrcpy (buf,TEXT("SQL_SUCCESS"));
			break;
		case SQL_ERROR:
			lstrcpy (buf,TEXT("SQL_ERROR"));
			break;
		case SQL_SUCCESS_WITH_INFO:
			lstrcpy (buf,TEXT("SQL_SUCCESS_WITH_INFO"));
			break;
		case SQL_NO_DATA_FOUND:
			lstrcpy (buf,TEXT("SQL_NO_DATA_FOUND"));
			break;
		case SQL_NEED_DATA:
			lstrcpy (buf,TEXT("SQL_NEED_DATA"));
			break;
		case SQL_INVALID_HANDLE:
			lstrcpy (buf,TEXT("SQL_INVALID_HANDLE"));
			break;
		case SQL_STILL_EXECUTING:
			lstrcpy (buf,TEXT("SQL_STILL_EXECUTING"));
			break;
		default:
			lstrcpy(buf,TEXT("UNKNOWN rc"));
		}

	return buf;
}



//-----------------------------------------------------------------------
//      Function:               ReturnCheck
//-----------------------------------------------------------------------

int  PASCAL ReturnCheck(RETCODE retExpected, RETCODE retReceived, LPTSTR szFunction, 
								LPTSTR szFile, int iLine,BOOL fDiag)
{
	TCHAR buf[MAX_STRING_SIZE];

	if(retExpected == retReceived)
		return TRUE;

	szWrite(TEXT(""), TRUE);
						
	szWrite(TEXT("\t\t\t"), FALSE);
	szWrite(szFunction, TRUE);

	szWrite(TEXT("\t\t\tExpected: "), FALSE);
	szWrite(RetcodeToTCHAR(retExpected, buf), TRUE);

	szWrite(TEXT("\t\t\tReceived: "), FALSE);
	szWrite(RetcodeToTCHAR(retReceived, buf), TRUE);

	if (!fDiag)
		DisplayAllErrors();

	wsprintf(buf,TEXT("\t\t\t%s: %d"), szFile, iLine);
	szWrite(buf, TRUE);

	szWrite(TEXT("\t\t\t --------  "), TRUE);

	lpSI->failed++;

	return FALSE;
}

//-----------------------------------------------------------------------
//      Function:               ErrsHandle
//-----------------------------------------------------------------------

int  PASCAL ErrsHandle(SWORD fHandleType,SQLHANDLE hHandle, RETCODE retExpected,
	RETCODE retReceived, LPTSTR szFunction, LPTSTR szFile, int iLine,BOOL fDiag)
{
	TCHAR buf[MAX_STRING_SIZE];

	if(retExpected == retReceived)
		return TRUE;

	szWrite(TEXT(""), TRUE);
						
	szWrite(TEXT("\t\t\t"), FALSE);
	szWrite(szFunction, TRUE);

	szWrite(TEXT("\t\t\tExpected: "), FALSE);
	szWrite(RetcodeToTCHAR(retExpected, buf), TRUE);

	szWrite(TEXT("\t\t\tReceived: "), FALSE);
	szWrite(RetcodeToTCHAR(retReceived, buf), TRUE);

	if (!fDiag)
		GetDiagRecs(fHandleType,hHandle);

	wsprintf(buf,TEXT("\t\t\t%s: %d"), szFile, iLine);
	szWrite(buf, TRUE);

	szWrite(TEXT("\t\t\t --------  "), TRUE);

	lpSI->failed++;

	return FALSE;
}

/*------------------------------------------------------------------------------
/	Function:	FindError
/	Purpose:	Find the expected error message. Display a failure if not found.
/*----------------------------------------------------------------------------*/

BOOL PASCAL FindError(SWORD fHandleType, LPTSTR szFindState)
{
	SQLHANDLE handle = SQL_NULL_HANDLE;
	SWORD irec;
	TCHAR szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
	RETCODE rc;
	TCHAR szState[6];

	switch(fHandleType)
	{
		case SQL_HANDLE_ENV:
			handle = henv;
			break;

		case SQL_HANDLE_DBC:
			handle = hdbc;
			break;

		case SQL_HANDLE_STMT:
			handle = hstmt;
			break;

		case SQL_HANDLE_DESC:
			if(!Supported(SQL_API_SQLGETDIAGREC))
				return TRUE;

			handle = hdesc;
			break;

		default:
			DISPLAYERROR(TEXT("FindError"), TEXT("invalid fHandleType"));
			return FALSE;
	}

	for(irec = 1
		; rc = SQLGetDiagRec(fHandleType, handle, irec, szState, NULL, szErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL)
		, RC_SUCCESSFUL(rc)
		; irec++)
	{
		if(lstrcmp(szState, szFindState) == 0)
			return TRUE;
	}
	return FALSE;

} /* FindError() */

/*------------------------------------------------------------------------------
 *	Function:	CompareWithExpected
 *	Checks data in rgbValue against expected value given row, col, and rgFields.
 *	Posts an error if mismatch
 * ----------------------------------------------------------------------------*/
void CompareWithExpected(PTR rgbValue, SDWORD * pcbValue, UWORD row, UWORD icol, FIELDINFO  *rgFields)
{
	LPTSTR   pch=NULL;
	TCHAR szExpBuf[MAX_STRING_SIZE]=TEXT("");
	TCHAR * stopstr;

	pch = qtMakeData(row-1, icol-1, &rgFields[icol-1], szExpBuf);

	// Field is not READ ONLY, compare the value we inserted
	if(pch) 
	{
 		// Where row and column match and field is nullable, a NULL exists
		if (icol-1 == row-1 && rgFields[icol-1].nullable)
		{
			// Post an error if not SQL_NULL_DATA
			if (*pcbValue != SQL_NULL_DATA)
				DISPLAYERROR(TEXT("Simulate BindCol"),TEXT("Didn't return SQL_NULL_DATA"));
		}
		else
		{
			BOOL bCompare;
			TCHAR * pstr=szExpBuf;	// Pointer to start of expected string

			switch(rgFields[icol-1].wSQLType)
			{
				case SQL_BIT:
				case SQL_TINYINT:
				case SQL_SMALLINT:
				case SQL_INTEGER:
					// Compare the data values as long // tcsncmp
					bCompare=(_ttol(rgbValue) == _ttol(pstr));
					break;
				case SQL_NUMERIC:
				case SQL_DECIMAL:
				case SQL_FLOAT:
				case SQL_REAL:
				case SQL_DOUBLE:
					// Compare the data values as doubles strtod
					bCompare=(_tcstod(rgbValue, &stopstr) == _tcstod(pstr, &stopstr));
					break;
				case SQL_DATE:
				case SQL_TIME:
				case SQL_TIMESTAMP:
				case SQL_TYPE_DATE:
				case SQL_TYPE_TIME:
				case SQL_TYPE_TIMESTAMP:
					pstr=szExpBuf+lstrlen(TEXT("{ts '"));
					// Replace second ' with '\0'									'
					_tcstok(pstr, TEXT("'"));
					if (lstrlen(rgbValue) > lstrlen(TEXT("1994-10-10 10:00:00")))
						lstrcat(pstr, TEXT(".000"));
					bCompare=(!_tcsncmp(rgbValue, pstr, rgFields[icol-1].precision));
					break;
				default:
					bCompare=(!_tcsncmp(rgbValue, pstr, lstrlen(pstr)));
			}

			// Compare the data values as char 
			if (!bCompare)
			{
				DISPLAYERROR(TEXT("Simulate BindCol"),TEXT("Returned data didn't match"));
				szWrite(TEXT("\t\t\tExpected: "), FALSE);
				szWrite(pstr, TRUE);
				szWrite(TEXT("\t\t\tReceived: "), FALSE);
				szWrite(rgbValue, TRUE);
			}
		}
	}
} //CompareWithExpected

//-----------------------------------------------------------------------
//      Function:               ResetHstmt
//-----------------------------------------------------------------------
void ResetHstmt(SQLHSTMT * phstmt)
{
	SQLRETURN rc;

	// Free and reallocate stmt handle to clean up
	rc=SQLFreeHandle(SQL_HANDLE_STMT, *phstmt);
	ERRSHANDLE(SQL_HANDLE_STMT, *phstmt, SQL_SUCCESS, rc, szSQLFREESTMT);
	rc=SQLAllocHandle(SQL_HANDLE_STMT, hdbc, phstmt);
	RETCHECK(SQL_SUCCESS, rc,szSQLALLOCHANDLE);
}

/*-----------------------------------------------------------------------*/
/*      Function:               GetSomeData                              */
/*-----------------------------------------------------------------------*/

VOID PASCAL GetSomeData(HSTMT lhstmt, LPTSTR szTableName,BOOL fBindCol,
								FIELDINFO  rgField)
{
	RETCODE	rc=SQL_SUCCESS;
	SDWORD	cbValue=0;
	TCHAR		szQuery[XLARGEBUFF]=TEXT(""),
				szBuff[XLARGEBUFF]=TEXT("");
	TCHAR		szErrMsg[MAX_STRING_SIZE]=TEXT(""),
				szDataItem[XLARGEBUFF]=TEXT("");
	LPTSTR   pch=NULL;

	pch = qtMakeData(0, 0,&rgField, szDataItem);

	wsprintf(szQuery,szSELECTSTAR,szTableName);
	rc=SQLExecDirect(lhstmt,szQuery,SQL_NTS);
//	RETCHECK(SQL_SUCCESS,rc,szSQLEXECDIRECT);

	if (fBindCol)
	{
		rc = SQLBindCol(lhstmt, 1, SQL_C_TCHAR, szBuff, sizeof(szBuff),&cbValue);
//		RETCHECK(SQL_SUCCESS, rc, szSQLBINDCOL);
	}

	rc = SQLFetch(lhstmt);
//	RETCHECK(SQL_SUCCESS, rc,szSQLFETCH);

	if (!fBindCol)
	{
		rc = SQLGetData(lhstmt,1, SQL_C_TCHAR,szBuff, sizeof(szBuff), NULL);
//		RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);
	}

	lstrcmp(szDataItem,szBuff);

} /* GetSomeData() */



/*-----------------------------------------------------------------------*/
/*      Function:               SelectFromTable                          */
/*-----------------------------------------------------------------------*/

_inline RETCODE PASCAL SelectFromTable(QTSTRUCT *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szQuery[LARGEBUFF];

	wsprintf(szQuery,TEXT("select %s from %s"), 
	//wsprintf(szQuery,TEXT("select %s from %s order by %s"), 
		lpqt->szColNames, lpqt->szTableName/*, lpqt->szColNames*/);

	rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

	return(rc);

} /* SelectFromTable() */

/*-----------------------------------------------------------------------*/
/*      Function:               SelectFromTableFetch                     */
/*-----------------------------------------------------------------------*/

_inline RETCODE PASCAL SelectFromTableFetch(QTSTRUCT *lpqt, TCHAR* szColName)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szQuery[LARGEBUFF];

	wsprintf(szQuery,TEXT("select %s from %s order by %s"), 
		lpqt->szColNames, lpqt->szTableName, szColName);

	rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
	if((SQL_SUCCESS!=rc) && (SQL_SUCCESS_WITH_INFO!=rc)){
		RETCHECK(SQL_SUCCESS_WITH_INFO, rc,szSQLEXECDIRECT);
		return SQL_NO_DATA;
	}

	return SQL_SUCCESS;
} /* SelectFromTableFetch() */

//-----------------------------------------------------------------------
//      Function:               AllocHstmt
//-----------------------------------------------------------------------

_inline BOOL PASCAL AllocHstmt()
{
	BOOL		fFailed=FALSE;
	RETCODE	rc=SQL_SUCCESS;

	if (Supported(SQL_API_SQLALLOCHANDLE))
	{
		rc = SQLAllocHandle(SQL_HANDLE_STMT,hdbc, &hstmt);
		if(!RETCHECK(SQL_SUCCESS, rc, szSQLALLOCHANDLE))
			fFailed=TRUE;
	}
	else
	{
		rc = SQLAllocStmt(hdbc, &hstmt);
		if(!RETCHECK(SQL_SUCCESS, rc, szSQLALLOCSTMT))
			fFailed=TRUE;
	}


	return(fFailed);

} //AllocHstmt()



//-----------------------------------------------------------------------
//      Function:               AllocHdbc
//-----------------------------------------------------------------------

_inline BOOL PASCAL AllocHdbc(HDBC *phdbc)
{
	BOOL		fFailed=FALSE;
	RETCODE	rc=SQL_SUCCESS;

	if (Supported(SQL_API_SQLALLOCHANDLE))
	{
		rc = SQLAllocHandle(SQL_HANDLE_DBC,henv, phdbc);
		if(!RETCHECK(SQL_SUCCESS, rc, szSQLALLOCHANDLE))
			fFailed=TRUE;
	}
	else
	{
		rc = SQLAllocConnect(henv, phdbc);
		if(!RETCHECK(SQL_SUCCESS, rc, szSQLALLOCCONNECT))
			fFailed=TRUE;
	}


	return(fFailed);

} //AllocHdbc()


//-----------------------------------------------------------------------
//      Function:					AllocHenv
//-----------------------------------------------------------------------

_inline BOOL PASCAL PASCAL AllocHenv()
{
	BOOL		fFailed=FALSE;
	RETCODE	rc=SQL_SUCCESS;

	rc = SQLAllocEnv(&henv);
	if (!RETCHECK(SQL_SUCCESS, rc,szSQLALLOCENV))
		fFailed=TRUE;

	return(fFailed);

} //AllocHenv()

//-----------------------------------------------------------------------
//      Function:               SetStatementAttributes
//-----------------------------------------------------------------------

_inline BOOL PASCAL SetStatementAttributes(UWORD fAttr, PTR rgbValue)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szAPI[MEDBUFF];
	BOOL		fFailed=FALSE;

	if (Supported(SQL_API_SQLSETSTMTATTR))
	{
		rc = SQLSetStmtAttr(hstmt,(SDWORD)fAttr,rgbValue,sizeof(UDWORD));
		lstrcpy(szAPI,szSQLSETSTMTATTR);
	}
	else
	{
		rc = SQLSetStmtOption(hstmt,fAttr,(UDWORD)rgbValue);
		lstrcpy(szAPI,szSQLSETSTMTOPTION);
	}

	if (rc != SQL_SUCCESS)
	{
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			RETCHECK(SQL_SUCCESS, rc,szAPI);

		fFailed=TRUE;
	}

	return(fFailed);

} //SetStatementAttributes()



//-----------------------------------------------------------------------
//      Function:               SetConnectionAttributes
//-----------------------------------------------------------------------

_inline BOOL PASCAL SetConnectionAttributes(HDBC lhdbc,UWORD fAttr, UDWORD rgbValue)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szAPI[MEDBUFF];
	BOOL		fFailed=FALSE;

	if (Supported(SQL_API_SQLSETCONNECTATTR))
	{
		rc = SQLSetConnectAttr(lhdbc,(SDWORD)fAttr,(PTR)rgbValue,sizeof(UDWORD));
		lstrcpy(szAPI,szSQLSETCONNECTATTR);
	}
	else
	{
		rc = SQLSetConnectOption(lhdbc,fAttr,rgbValue);
		lstrcpy(szAPI,szSQLSETCONNECTOPTION);
	}

	if (rc != SQL_SUCCESS)
	{
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS, rc,szAPI);

		fFailed=TRUE;
	}

	return(fFailed);

} //SetConnectionAttributes()



//-----------------------------------------------------------------------
//      Function:               FreeStmt
//-----------------------------------------------------------------------

_inline BOOL PASCAL FreeStmt(UWORD fOption)
{
	RETCODE	rc=SQL_SUCCESS;

	if (Supported(SQL_API_SQLFREEHANDLE) && (fOption == SQL_DROP))
	{
		rc = SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREEHANDLE);
	}
	else
	{
		rc = SQLFreeStmt(hstmt, fOption);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);
	}

	return(RC_NOTSUCCESSFUL(rc));

} //FreeStmt()

//-----------------------------------------------------------------------
//      Function:               DropHdbc
//-----------------------------------------------------------------------

VOID PASCAL DropHdbc(HDBC hdbc)
{
	RETCODE rc=SQL_SUCCESS;

	if (Supported(SQL_API_SQLFREEHANDLE))
	{
		rc = SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREEHANDLE);
	}
	else
	{
		rc = SQLFreeConnect(hdbc);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREECONNECT);
	}

} //DropHdbc()



//-----------------------------------------------------------------------
//      Function:               DropHenv
//-----------------------------------------------------------------------

_inline VOID PASCAL DropHenv()
{
	RETCODE rc=SQL_SUCCESS;

	if (Supported(SQL_API_SQLFREEHANDLE))
	{
		rc = SQLFreeHandle(SQL_HANDLE_ENV,henv);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREEHANDLE);
	}
	else
	{
		rc = SQLFreeEnv(henv);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREEENV);
	}

} //DropHenv()


//-----------------------------------------------------------------------
//      Function:               ClearErrorQueue
//-----------------------------------------------------------------------

VOID PASCAL ClearErrorQueue()
{
	TCHAR szErrMsg[MAX_STRING_SIZE];
	TCHAR szState[6];

	/* Eat up the SQL_SUCCESS_WITH_INFO error record */
	while (RC_SUCCESSFUL(SQLError(NULL, hdbc,NULL, szState, NULL, 
		szErrMsg, sizeof(szErrMsg), NULL)))
			;
}


//-----------------------------------------------------------------------
//      Function:               Is3XDriver
//-----------------------------------------------------------------------

BOOL PASCAL Is3XDriver(HDBC hdbc,QTSTRUCT *lpqt)
{
	RETCODE		rc=SQL_SUCCESS;
	LPTSTR		pch=NULL;
	BOOL			f3XDriver=FALSE;

	rc = SQLGetInfo(hdbc, SQL_DRIVER_ODBC_VER, lpqt->buf, MAX_STRING_SIZE, NULL);
	if(RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO))
	{
		pch = _tcstok(lpqt->buf,TEXT("."));

		if (!_tcsnccmp(pch,TEXT("02"), 2))
		{
			pch = _tcstok(NULL,TEXT("."));
		
			if(!_tcsnccmp(pch,TEXT("00"), 2))
				DISPLAYERROR(szSQLGETINFO,TEXT("Driver returned ODBC version 2.00 which is no longer supported.  Please upgrade to 2.01"));
			
		}
		else if (!_tcsnccmp(pch,TEXT("03"), 2))
			f3XDriver=TRUE;
	}

	uDriverODBCVer=_ttoi(lpqt->buf);

	return(f3XDriver);

} //Is3XDriver()


//-----------------------------------------------------------------------
//      Function:               Connect
//-----------------------------------------------------------------------

BOOL  PASCAL Connect(lpSERVERINFO lpSI,QTSTRUCT  *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	SDWORD sdwAppVer;

/* The signal for test to use it's
	own allocated handles, is if the a server name is passed in.  If it
	is not, the test should use the hdbc passed in */

	/* ****************** Allocate Env ************************* */
	if (AllocHenv())
		goto ConnectErrorRet;

	/* ****************** Set Application Version ************************* */
	rc = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
		SQL_IS_UINTEGER);
	if(!RETCHECK(SQL_SUCCESS, rc, szSQLSETENVATTR))
		goto ConnectErrorRet;

	/* ****************** Allocate Connection ************************* */

	rc = SQLAllocConnect(henv, &hdbc);
	if(!RETCHECK(SQL_SUCCESS, rc, szSQLALLOCCONNECT))
		goto ConnectErrorRet;

	/* ****************** Set Connection Attributes ************************* */
	rc = SQLSetConnectOption(hdbc,SQL_ODBC_CURSORS,lpSI->vCursorLib);

	if(!FindError(SQL_HANDLE_DBC,szHYC00))
		if (!RETCHECK(SQL_SUCCESS, rc,szSQLSETCONNECTOPTION))
		goto ConnectErrorRet;

	/* create a DriverConnect string */
	wsprintf(lpqt->sz, TEXT("dsn=%s;uid=%s;pwd=%s;"),
		lpSI->szValidServer0,
		lpSI->szValidLogin0,
		lpSI->szValidPassword0);

	/* since SQL_DRIVER_COMPLETE is used, it is possible that the
	driver will bring up a dialog asking for more information. */
	rc = SQLDriverConnect(hdbc, lpSI->hwnd, lpqt->sz,
		SQL_NTS, lpqt->buf, MAX_STRING_SIZE, NULL, SQL_DRIVER_COMPLETE);
	
	if (RC_NOTSUCCESSFUL(rc))
	{
		if (!RETCHECK(SQL_SUCCESS, rc,szSQLDRIVERCONNECT))
			goto ConnectErrorRet;
	}
	else
		ClearErrorQueue();


	rc = SQLDisconnect(hdbc);
	RETCHECK(SQL_SUCCESS, rc,szSQLDISCONNECT);

	rc = SQLConnect(hdbc, lpSI->szValidServer0, SQL_NTS,
						lpSI->szValidLogin0, SQL_NTS,
						lpSI->szValidPassword0, SQL_NTS);

	if (RC_SUCCESSFUL(rc))
		ClearErrorQueue();
	else if (!RETCHECK(SQL_SUCCESS, rc,szSQLCONNECT))
		goto ConnectErrorRet;

	// Set the global 3.0 driver flag
	g_f3XDriver=Is3XDriver(hdbc,lpqt);

	// We're now connected, check application version and adjust expected error
	// states appropriately.
	rc = SQLGetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, &sdwAppVer, SQL_IS_UINTEGER, NULL);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETENVATTR);

	if (RC_SUCCESSFUL(rc) && (SQL_OV_ODBC2 == sdwAppVer))
	{
		lstrcpy(szHY009, TEXT("S1009"));
		lstrcpy(szHYC00, TEXT("S1C00"));
	}

	return(FALSE);

ConnectErrorRet:

	return(TRUE);

} //Connect()


//-----------------------------------------------------------------------
//      Function:               IgnoreType
//-----------------------------------------------------------------------

BOOL  PASCAL IgnoreType(LPTSTR szType,SWORD wSQLType)
{
	BOOL fIgnore=FALSE;

/* If a line below is compiled in, that type will not be used in creating
 the table.  (useful for when one specific type is causing problems in
 a particular test, this way the test can be run for all other types)
*/

	if (!lstrcmp(szType,TEXT("LONG RAW")) ||
		 !lstrcmp(szType,TEXT("LONG VARTCHAR")) ||
	 	 !lstrcmp(szType,TEXT("LONG VARTCHAR FOR BIT DATA")))
		{
	 	fIgnore=TRUE;
		}

	//if (wSQLType != SQL_CHAR)
	//	fIgnore=TRUE;

	return(fIgnore);

} //IgnoreType()
			
	
//-----------------------------------------------------------------------
//      Function:               CheckConformanceLevel
//-----------------------------------------------------------------------

UWORD  PASCAL CheckConformanceLevel()
{
	RETCODE 	rc=SQL_SUCCESS;
	UWORD		fIndex=0;
	SWORD		cb=0;

	rc = SQLGetInfo(hdbc, SQL_ODBC_SQL_CONFORMANCE, &fIndex,
		sizeof (fIndex), &cb);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

	if(fIndex != 0 && fIndex != 1 && fIndex != 2) {
		/* one of these two values should always be returned */
		DISPLAYERROR(szSQLGETINFO,TEXT("SQL_ODBC_API_CONFORMANCE - invalid value"));
	}

	return(fIndex);

} //CheckConformanceLevel()

/*-----------------------------------------------------------------------*/
/*      Function:               TestConnectionOptions							 */
/*-----------------------------------------------------------------------*/

void  PASCAL TestConnectionOptions()
{
	RETCODE	rc=SQL_SUCCESS;
	SDWORD	sdw,
				cbValue=0;
	BOOL		fConnectOption=TRUE;
	TCHAR		szAPI[MEDBUFF];
	HDBC		lhdbc=NULL;


	rc=SQLAllocConnect(henv,&lhdbc);
	RETCHECK(SQL_SUCCESS, rc,szSQLALLOCCONNECT);
	
	SetConnectionAttributes(lhdbc,SQL_ACCESS_MODE,SQL_MODE_READ_WRITE);

	SetConnectionAttributes(lhdbc,SQL_AUTOCOMMIT,TRUE);

	if (SetConnectionAttributes(lhdbc,SQL_LOGIN_TIMEOUT,TEST_CONNECT_OPTION))
		fConnectOption = FALSE;

	if (Supported(SQL_API_SQLGETCONNECTATTR))
	{
		rc = SQLGetConnectAttr(lhdbc, SQL_LOGIN_TIMEOUT, (PTR)&sdw,0,&cbValue);
		lstrcpy(szAPI,szSQLGETCONNECTATTR);
	}
	else
	{
		rc = SQLGetConnectOption(lhdbc, SQL_LOGIN_TIMEOUT, &sdw);
		lstrcpy(szAPI,szSQLSETCONNECTOPTION);
	}


	if(rc != SQL_SUCCESS)
	{
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS, rc,szAPI);
	}
	else
	{
		if(sdw != TEST_CONNECT_OPTION && fConnectOption)
			DISPLAYERROR(szAPI,TEXT("SQL_LOGIN_TIMEOUT returned incorrect value"));
	}

	rc=SQLFreeConnect(lhdbc);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREECONNECT);

} //TestConnectionOptions()



/*-----------------------------------------------------------------------*/
/*      Function:            CanAllocHdesc       								 */
/*-----------------------------------------------------------------------*/

BOOL PASCAL CanAllocHdesc()
{
	BOOL fSupported=FALSE;

	/* Allocate an hdesc: */
	if(Supported(SQL_API_SQLALLOCHANDLE))
		fSupported = RC_SUCCESSFUL(SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc));

	return(fSupported);

}


/*-----------------------------------------------------------------------*/
/*      Function:            SetErrorCondition   								 */
/*-----------------------------------------------------------------------*/

VOID PASCAL SetErrorCondition(SWORD fHandleType)
{
	RETCODE rc=SQL_SUCCESS;

	/* The following are used to produce "(S1)HY009" SQL State */
	switch (fHandleType)
	{
		case SQL_HANDLE_ENV:
			rc = SQLAllocConnect(henv, NULL);
			break;
		case SQL_HANDLE_DBC:
			rc = SQLAllocStmt(hdbc, NULL);
			break;
		case SQL_HANDLE_STMT:
			rc = SQLExecDirect(hstmt, NULL, SQL_NTS);		// Produces a DM error
			break;
		case SQL_HANDLE_DESC:
			rc = SQLGetDescField(hdesc, 0, SQL_DESC_AUTO_UNIQUE_VALUE, NULL, 0, NULL);
			break;
	}

} //SetErrorCondition()



VOID PASCAL CheckData(SWORD fHandleType,UWORD uwDescField, PTR rgbValue,LPTSTR szDataSourceName)
{
	TCHAR			szBuff[MEDBUFF]=TEXT("");
	LPTSTR		pszExpState=szHY009;

	if (fHandleType == SQL_HANDLE_DESC)
		pszExpState=szHY091;

	switch(uwDescField)
	{
		case SQL_DIAG_RETURNCODE:
			{
				RETCODE rcRec=*(RETCODE *)rgbValue;
				
				if (rcRec!= SQL_ERROR)
				{
					wsprintf(szBuff,TEXT("\t\t\tSQL_DIAG_RETURN_CODE\tReceived: %d\tExpected: %d"),rcRec,-1);
				}
			}
			break;
		
		case SQL_DIAG_SQLSTATE:
			{
				if (lstrcmp((LPTSTR)rgbValue,pszExpState))
				{
					wsprintf(szBuff,TEXT("\t\t\tSQL_DIAG_SQLSTATE\tReceived: %s\tExpected: %s"),(LPTSTR)rgbValue,pszExpState);
				}
			}
			break;
		case SQL_DIAG_CLASS_ORIGIN:
			{
				if (lstrcmp((LPTSTR)rgbValue,szISO))
					wsprintf(szBuff,TEXT("\t\t\tSQL_DIAG_CLASS_ORIGIN\tReceived: %s\tExpected: %s"),(LPTSTR)rgbValue,szISO);
			}
			break;
		case SQL_DIAG_SUBCLASS_ORIGIN:
			{
				if (lstrcmp((LPTSTR)rgbValue,szISO))
					wsprintf(szBuff,TEXT("\t\t\tSQL_DIAG_CLASS_ORIGIN\tReceived: %s\tExpected: %s"),(LPTSTR)rgbValue,szISO);
			}
			break;
		case SQL_DIAG_NUMBER:
			{
				SDWORD cRecs=*(SDWORD *)rgbValue;
				if (cRecs != 1)
					wsprintf(szBuff,TEXT("\t\t\tSQL_DIAG_NUMBER\tReceived: %d\tExpected: %d"),cRecs,1);
			}
			break;
		case SQL_DIAG_SERVER_NAME:
			{
				switch(fHandleType)
				{
				case SQL_HANDLE_DBC:
				case SQL_HANDLE_STMT:
					if (lstrcmp((LPTSTR)rgbValue,szDataSourceName))
						wsprintf(szBuff,TEXT("\t\t\tSQL_DIAG_SERVER_NAME\tReceived: %s\tExpected: %s"),(LPTSTR)rgbValue,szDataSourceName);
					break;
				}
			}
			break;
		default:
			break;

	}

	if (*szBuff)
		DISPLAYERROR(szSQLGETDIAGREC,szBuff);

} /* CheckData() */


/*------------------------------------------------------------------------------
/	Function:	TestDiagRec                                              
/	Purpose:	For each type of handle, generate an error. If SQLGetDiagField      
/				is not supported, verify the appropriate DM error is returned.      
/				Otherwise, verify SQLGetDiagField returns the expected error        
/				information. If SQLGetDiagRec is not supported, verify the          
/				appropriate DM error is returned. Otherwise, verify                 
/				SQLGetDiagField returns the expected error information. If          
/				SQLGetDiagRec is supported, compare its output with that of         
/				SQLGetDiagField.                                                    
/*----------------------------------------------------------------------------*/

void PASCAL TestDiagRec()
{
	SQLRETURN	rcFunction, 
					rc=SQL_SUCCESS;
	SWORD			cbErrorMsg;
	SDWORD		fNativeError;
	UWORD			iHandle=0,
					iField=0,
					cHandles;

	SDWORD		*pfNativeError = NULL;
	LPTSTR		pchMessageText = NULL;

	TCHAR			szDataSourceName[MAX_STRING_SIZE] = TEXT("");
	TCHAR			szState[SQL_SQLSTATE_SIZE+1];
	TCHAR			szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
	TCHAR			szAPI[MEDBUFF]=TEXT("");
	TCHAR			szBuff[MEDBUFF]=TEXT("");

	LPTSTR		pszExpState=szHY009;
	RETCODE		rcExp=SQL_SUCCESS;

	HANDLES rgHandles[] = 
	{
		SQL_HANDLE_ENV, henv,
		SQL_HANDLE_DBC, hdbc,
		SQL_HANDLE_STMT, hstmt,
		SQL_HANDLE_DESC, hdesc,
	};

	cHandles=sizeof(rgHandles)/sizeof(HANDLES);

	/* Call SQLGetInfo to get values to compare: */
	rcFunction = SQLGetInfo(hdbc, SQL_DATA_SOURCE_NAME, szDataSourceName, MAX_STRING_SIZE, NULL);
	RETCHECK(SQL_SUCCESS, rcFunction, szSQLGETINFO);

	/* Allocate an hdesc: */
	if(Supported(SQL_API_SQLALLOCHANDLE) && g_f3XDriver)
	{ 
		rcFunction = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);
		RETCHECK(SQL_SUCCESS, rcFunction, szSQLALLOCHANDLE);

		// Update the array entry for the hdesc
		rgHandles[3].hHandle=hdesc;

	}
	else
		cHandles--;

	for (iHandle=0; iHandle < cHandles; iHandle++)
	{

		SetErrorCondition(rgHandles[iHandle].fHandleType);

		rc = SQLGetDiagRec(rgHandles[iHandle].fHandleType, rgHandles[iHandle].hHandle, 
					1,szState,&fNativeError, szErrorMsg,
					SQL_MAX_MESSAGE_LENGTH, &cbErrorMsg);

		if (rgHandles[iHandle].fHandleType == SQL_HANDLE_DESC)
			pszExpState=szHY091;

		rcExp=SQL_SUCCESS;

		if(fDiagRecSupported)
		{

			DIAGRETCHECK(rcExp, rc, szSQLGETDIAGREC);
			if (RC_SUCCESSFUL(rc) && lstrcmp(szState,pszExpState))
			{
				wsprintf(szBuff,TEXT("\t\t\tReceived: %s\tExpected: %s"),szState,	pszExpState);
				DISPLAYERROR(szSQLGETDIAGREC,szBuff);
			}
		}
		else
		{
			if(!FindError(rgHandles[iHandle].fHandleType, szIM001))
				DISPLAYERROR(szSQLGETDIAGREC, szNotSupported);
		}

	}


	/* Free the hdesc: */
	if (hdesc)
	{
		rcFunction = SQLFreeHandle(SQL_HANDLE_DESC, hdesc);
		RETCHECK(rcExp, rcFunction, szSQLFREEHANDLE);
		hdesc = SQL_NULL_HDESC;
	}

//ExitTestDiagRec

	FreeStmt(SQL_CLOSE);

} /* TestDiagRec() */


/*------------------------------------------------------------------------------
/	Function:	TestDiagField		                                               
/	Purpose:	For each type of handle, generate an error. If SQLGetDiagField      
/				is not supported, verify the appropriate DM error is returned.      
/				Otherwise, verify SQLGetDiagField returns the expected error        
/				information. If SQLGetDiagRec is not supported, verify the          
/				appropriate DM error is returned. Otherwise, verify                 
/				SQLGetDiagField returns the expected error information. If          
/				SQLGetDiagRec is supported, compare its output with that of         
/				SQLGetDiagField.                                                    
/*----------------------------------------------------------------------------*/

void PASCAL TestDiagField()
{
	SQLRETURN	rcFunction, 
					rc=SQL_SUCCESS;
	SWORD			cbValue=0;
	UWORD			iHandle=0,
					iField=0,
					cHandles;

	TCHAR			szDataSourceName[MAX_STRING_SIZE] = TEXT("");
	TCHAR			rgbValue[SQL_MAX_MESSAGE_LENGTH];
	TCHAR			szAPI[MEDBUFF]=TEXT("");
	TCHAR			szBuff[MEDBUFF]=TEXT("");
	RETCODE		rcExp=SQL_SUCCESS;

	HANDLES rgHandles[] = 
	{
		SQL_HANDLE_ENV, henv,
		SQL_HANDLE_DBC, hdbc,
		SQL_HANDLE_STMT, hstmt,
		SQL_HANDLE_DESC, hdesc,
	};

	cHandles=sizeof(rgHandles)/sizeof(HANDLES);

	/* Call SQLGetInfo to get values to compare: */
	rcFunction = SQLGetInfo(hdbc, SQL_DATA_SOURCE_NAME, szDataSourceName, MAX_STRING_SIZE, NULL);
	RETCHECK(SQL_SUCCESS, rcFunction, szSQLGETINFO);

	hdesc = SQL_NULL_HDESC;

	/* Allocate an hdesc: */
	if(Supported(SQL_API_SQLALLOCHANDLE) && g_f3XDriver)
	{ 
		rcFunction = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);
		RETCHECK(SQL_SUCCESS, rcFunction, szSQLALLOCHANDLE);

		// Update the array entry for the hdesc
		rgHandles[3].hHandle=hdesc;

	}
	else
		cHandles--;

	for (iHandle=0; iHandle < cHandles; iHandle++)
	{

		SetErrorCondition(rgHandles[iHandle].fHandleType);

		if(fDiagFieldSupported)
		{
			for (iField=0;iField < sizeof(rgDiagInfo)/sizeof(struct tagDIAGINFO);iField++)
			{
				rc = SQLGetDiagField(rgHandles[iHandle].fHandleType, rgHandles[iHandle].hHandle, 
							rgDiagInfo[iField].irecRecNumber, rgDiagInfo[iField].uwDescField,
							rgbValue, SQL_MAX_MESSAGE_LENGTH, &cbValue);
	
				DIAGRETCHECK(rcExp, rc, szSQLGETDIAGFIELD);

				if (RC_SUCCESSFUL(rc))
					CheckData(rgHandles[iHandle].fHandleType,rgDiagInfo[iField].uwDescField, 
						rgbValue,szDataSourceName);
			}
			
		}
		else
		{
			rc = SQLGetDiagField(SQL_HANDLE_ENV, henv, 0, SQL_DIAG_RETURNCODE, rgbValue,SQL_MAX_MESSAGE_LENGTH, &cbValue);

			if(!FindError(rgHandles[iHandle].fHandleType, szIM001))
				DISPLAYERROR(szAPI, szNotSupported);
				
		}

	}


	/* Free the hdesc: */
	if (hdesc)
	{
		rcFunction = SQLFreeHandle(SQL_HANDLE_DESC, hdesc);
		RETCHECK(rcExp, rcFunction, szSQLFREEHANDLE);
		hdesc = SQL_NULL_HDESC;
	}

//ExitTestDiagField

	FreeStmt(SQL_CLOSE);

} /* TestDiagField() */

//------------------------------------------------------------------------------
//	Function:	CompareAnsiToUnicode
//		Compares an ANSI string to a Unicode string
//------------------------------------------------------------------------------
BOOL CompareAnsiToUnicode(SQLCHAR * aszBuf, SQLINTEGER cbA, SQLWCHAR * wszBuf,
	SQLINTEGER cbW, SQLTCHAR * szAPI)
{
	SQLCHAR aszConvBuf[MAX_STRING_SIZE];
	SQLINTEGER cbT;
	BOOL bCompare=TRUE;

	// Check ANSI count of bytes returned
	if ((cbA != SQL_NULL_DATA) && (SQLINTEGER)strlen(aszBuf) != cbA)
	{
		wsprintf(buf, TEXT("ANSI count of bytes returned incorrect.")\
			TEXT(" Expected: %d, received: %d"),
			strlen(aszBuf), cbA);
		DISPLAYERROR(szAPI, buf);
		bCompare=FALSE;
	}

	// Compare ANSI count of bytes with Unicode count
	cbT = (cbA > 0) ? (SQLINTEGER)(cbA * sizeof(SQLWCHAR)) : cbA;
	if (cbW != cbT)
	{
		wsprintf(buf, TEXT("Unicode count of bytes returned incorrect.")\
			TEXT(" Expected: %d, received: %d"), cbT, cbW);
		DISPLAYERROR(szAPI, buf);
		bCompare=FALSE;
	}

	// Compare strings if not NULL DATA
	if (cbA != SQL_NULL_DATA)
	{
		// Compare ANSI and Unicode strings returned
		(void)(WideCharToMultiByte(CP_ACP, 0, wszBuf, wcslen(wszBuf), aszConvBuf,
			sizeof(aszConvBuf), NULL, NULL));
		aszConvBuf[wcslen(wszBuf)]=TEXT('\0');

		if (strcmp(aszBuf, aszConvBuf))
		{
			wsprintf(buf, TEXT("Unicode string did not match ANSI string.\r\n")\
				TEXT("\t\t\tExpected: '%hs', Received: '%hs'"), aszBuf, aszConvBuf);
			DISPLAYERROR(szAPI, buf);
			bCompare=FALSE;
		}
	}

	return bCompare;
}

//------------------------------------------------------------------------------
//	Function:	CompareAnsiUnicodeResults
//		Compares an ANSI result set to a Unicode result set
//------------------------------------------------------------------------------
void CompareAnsiUnicodeResults(SQLHSTMT hstmtA, SQLHSTMT hstmtW, SQLTCHAR * szAPI)
{
	SQLCHAR aszBuf[MAX_STRING_SIZE];
	SQLWCHAR wszBuf[MAX_STRING_SIZE];
	SQLINTEGER cbANSI, cbUnicode;
	SQLUSMALLINT	uwCol;
	SQLSMALLINT		swColCountA, swColCountW;
	SQLRETURN rc, rcA, rcW;

	// Check width of result sets
	rc=SQLNumResultCols(hstmtA, &swColCountA);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtA, SQL_SUCCESS, rc, szSQLNUMRESULTCOLS);
	rc=SQLNumResultCols(hstmtW, &swColCountW);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_SUCCESS, rc, szSQLNUMRESULTCOLS);
	if (swColCountA != swColCountW)
		DISPLAYERROR(szAPI,TEXT("ANSI and Unicode result sets different widths."));

	uwCol=1;
	do {
		rc=SQLBindCol(hstmtA, uwCol, SQL_C_CHAR, aszBuf, sizeof(aszBuf), &cbANSI);
		ERRSHANDLE(SQL_HANDLE_STMT, hstmtA, SQL_SUCCESS, rc, szSQLBINDCOL);
		rc=SQLBindCol(hstmtW, uwCol, SQL_C_WCHAR, wszBuf, sizeof(wszBuf), &cbUnicode);
		ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_SUCCESS, rc, szSQLBINDCOL);

		// Copy something into the buffers so we can tell if they were modified
		strcpy(aszBuf, "Untouched");
		wcscpy(wszBuf, L"Untouched");

		// Fetch into the buffers
		rcA=SQLFetch(hstmtA);
		rcW=SQLFetch(hstmtW);


		if (RC_SUCCESSFUL(rcA) && RC_SUCCESSFUL(rcW))
		{
			if (!CompareAnsiToUnicode(aszBuf, cbANSI, wszBuf, cbUnicode, szSQLFETCH))
			{
				rcW=SQL_NO_DATA;	// Abort the loop w/o generating failure
				rcA=SQL_NO_DATA;
			}
		}

		// Unbind the column bound above on each statement
		rc=SQLFreeStmt(hstmtA, SQL_UNBIND);
		ERRSHANDLE(SQL_HANDLE_STMT, hstmtA, SQL_SUCCESS, rc, szSQLFREESTMT);
		rc=SQLFreeStmt(hstmtW, SQL_UNBIND);
		ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_SUCCESS, rc, szSQLFREESTMT);

		// Don't exceed the total number of columns in result set
		uwCol++;
		if (uwCol > (SQLUSMALLINT)swColCountA)
			uwCol=1;
	}
	while (RC_SUCCESSFUL(rcA) && RC_SUCCESSFUL(rcW));

	// Make sure the result sets were the same size
	if (rcW != SQL_NO_DATA)
		ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_NO_DATA, rc, szSQLFETCH);

	// Make sure the result sets were the same size
	if (rcA != rcW)
		DISPLAYERROR(szAPI,TEXT("ANSI and Unicode result sets not the same length."));

	rc=SQLFreeStmt(hstmtA, SQL_CLOSE);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtA, SQL_SUCCESS, rc, szSQLFREESTMT);
	rc=SQLFreeStmt(hstmtW, SQL_CLOSE);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_SUCCESS, rc, szSQLFREESTMT);

}


/*------------------------------------------------------------------------------
/	Function:	TestMixedAnsiUnicode
/	Purpose:	Call several of the Unicode functions mixed with ANSI functions
/				to verify functions succeed in the mixed case.
/*----------------------------------------------------------------------------*/
void PASCAL TestMixedAnsiUnicode(QTSTRUCT * lpqt)
{
	HDBC	hdbcANSI, hdbcUnicode;
	HSTMT hstmtANSIA, hstmtANSIW, hstmtUA, hstmtUW, hstmtW;
	SQLINTEGER cbANSI, cbUnicode;
	SQLWCHAR wszServer[MAX_STRING_SIZE], wszLogin[MAX_STRING_SIZE],
		wszPassword[MAX_STRING_SIZE], wszQuery[MAX_STRING_SIZE],
		wszBuf[MAX_STRING_SIZE], wszTable[MAX_STRING_SIZE];
	SQLCHAR	aszServer[MAX_STRING_SIZE], aszLogin[MAX_STRING_SIZE],
		aszPassword[MAX_STRING_SIZE], aszQuery[MAX_STRING_SIZE],
		aszBuf[MAX_STRING_SIZE], aszTable[MAX_STRING_SIZE];
	SQLUSMALLINT fStmts;
	SQLRETURN rc, rcA=SQL_SUCCESS, rcW=SQL_SUCCESS;
	
	// We've already set the environment attribute to 3.0 by this point
	
#ifdef UNICODE
	// Copy the unicode strings
	lstrcpy(wszServer, lpSI->szValidServer0);
	lstrcpy(wszLogin, lpSI->szValidLogin0);
	lstrcpy(wszPassword, lpSI->szValidPassword0);
	lstrcpy(wszTable, lpqt->szTableName);
	wsprintf(wszQuery,szSELECTSTAR,lpqt->szTableName);

	// Convert and copy to ANSI strings
	/*
	int WideCharToMultiByte(
		 UINT  CodePage,	// code page 
		 DWORD  dwFlags,	// performance and mapping flags 
		 LPCWSTR  lpWideCharStr,	// address of wide-character string 
		 int  cchWideChar,	// number of characters in string 
		 LPSTR  lpMultiByteStr,	// address of buffer for new string 
		 int  cchMultiByte,	// size of buffer 
		 LPCSTR  lpDefaultChar,	// address of default for unmappable characters  
		 LPBOOL  lpUsedDefaultChar 	// address of flag set when default char. used 
		);	
	*/
	// Server
	(void)(WideCharToMultiByte(CP_ACP,
						  0,
						  lpSI->szValidServer0,
						  lstrlen(lpSI->szValidServer0),
						  aszServer,
						  sizeof(aszServer),
						  NULL,
						  NULL));
	aszServer[lstrlen(lpSI->szValidServer0)]=TEXT('\0');

	// UID
	(void)(WideCharToMultiByte(CP_ACP,
						  0,
						  lpSI->szValidLogin0,
						  lstrlen(lpSI->szValidLogin0),
						  aszLogin,
						  sizeof(aszLogin),
						  NULL,
						  NULL));
	aszLogin[lstrlen(lpSI->szValidLogin0)]=TEXT('\0');

	// PWD
	(void)(WideCharToMultiByte(CP_ACP,
						  0,
						  lpSI->szValidPassword0,
						  lstrlen(lpSI->szValidPassword0),
						  aszPassword,
						  sizeof(aszPassword),
						  NULL,
						  NULL));
	aszPassword[lstrlen(lpSI->szValidPassword0)]=TEXT('\0');

	// Select stmt
	(void)(WideCharToMultiByte(CP_ACP,
						  0,
						  wszQuery,
						  lstrlen(wszQuery),
						  aszQuery,
						  sizeof(aszQuery),
						  NULL,
						  NULL));
	aszQuery[lstrlen(wszQuery)]=TEXT('\0');

	// Table name
	(void)(WideCharToMultiByte(CP_ACP,
						  0,
						  wszTable,
						  lstrlen(wszTable),
						  aszQuery,
						  sizeof(aszTable),
						  NULL,
						  NULL));
	aszTable[lstrlen(wszTable)]=TEXT('\0');

#else
	// Copy the ANSI strings
	lstrcpy(aszServer, lpSI->szValidServer0);
	lstrcpy(aszLogin, lpSI->szValidLogin0);
	lstrcpy(aszPassword, lpSI->szValidPassword0);
	lstrcpy(aszTable, lpqt->szTableName);
	wsprintf(aszQuery,szSELECTSTAR,lpqt->szTableName);

	// Convert and copy to Unicode strings
	/*
	int MultiByteToWideChar(
		 UINT  CodePage,	// code page 
		 DWORD  dwFlags,	// character-type options 
		 LPCSTR  lpMultiByteStr,	// address of string to map 
		 int  cchMultiByte,	// number of characters in string 
		 LPWSTR  lpWideCharStr,	// address of wide-character buffer 
		 int  cchWideChar 	// size of buffer 
		);	
	*/

	// Server
	(void) MultiByteToWideChar(CP_ACP,
									0,
									lpSI->szValidServer0,
									lstrlen(lpSI->szValidServer0),
									wszServer,
									sizeof(wszServer)/sizeof(WCHAR)
									);
	wszServer[lstrlen(lpSI->szValidServer0)]=TEXT('\0');

	// UID
	(void) MultiByteToWideChar(CP_ACP,
									0,
									lpSI->szValidLogin0,
									lstrlen(lpSI->szValidLogin0),
									wszLogin,
									sizeof(wszLogin)/sizeof(WCHAR)
									);
	wszLogin[lstrlen(lpSI->szValidLogin0)]=TEXT('\0');

	// PWD
	(void) MultiByteToWideChar(CP_ACP,
									0,
									lpSI->szValidPassword0,
									lstrlen(lpSI->szValidPassword0),
									wszPassword,
									sizeof(wszPassword)/sizeof(WCHAR)
									);
	wszPassword[lstrlen(lpSI->szValidPassword0)]=TEXT('\0');

	// Select stmt
	(void) MultiByteToWideChar(CP_ACP,
									0,
									aszQuery,
									lstrlen(aszQuery),
									wszQuery,
									sizeof(wszQuery)/sizeof(WCHAR)
									);
	wszQuery[lstrlen(aszQuery)]=TEXT('\0');

	// Table name
	(void) MultiByteToWideChar(CP_ACP,
									0,
									aszTable,
									lstrlen(aszTable),
									wszTable,
									sizeof(wszTable)/sizeof(WCHAR)
									);
	wszTable[lstrlen(aszTable)]=TEXT('\0');

#endif

	// Allocate connection for ANSI
	rc = SQLAllocConnect(henv, &hdbcANSI);
	RETCHECK(SQL_SUCCESS, rc, szSQLALLOCCONNECT);

	// Allocate connection for Unicode
	rc = SQLAllocConnect(henv, &hdbcUnicode);
	RETCHECK(SQL_SUCCESS, rc, szSQLALLOCCONNECT);

	// If Unicode is defined, then strings need to be converted to ANSI
	// before calling SQLConnectA
	rc = SQLConnectA(hdbcANSI, (LPSTR)aszServer, SQL_NTS,
						(LPSTR)aszLogin, SQL_NTS,
						(LPSTR)aszPassword, SQL_NTS);
	if (!RC_SUCCESSFUL(rc))
		ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLCONNECT);

	rc = SQLConnectW(hdbcUnicode, (LPWSTR)wszServer, SQL_NTS,
						(LPWSTR)wszLogin, SQL_NTS,
						(LPWSTR)wszPassword, SQL_NTS);
	if (!RC_SUCCESSFUL(rc))
		ERRSHANDLE(SQL_HANDLE_DBC, hdbcUnicode, SQL_SUCCESS, rc,szSQLCONNECTW);

	// Test mixed SQLNativeSQL calls	on the ANSI connection
	rc=SQLNativeSqlA(hdbcANSI, aszQuery, strlen(aszQuery), aszBuf, sizeof(aszBuf), &cbANSI);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLNATIVESQL);
	rc=SQLNativeSqlW(hdbcANSI,	wszQuery, wcslen(wszQuery)*sizeof(WCHAR), wszBuf, sizeof(wszBuf),
		&cbUnicode);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLNATIVESQL);

	CompareAnsiToUnicode(aszBuf, cbANSI, wszBuf, cbUnicode, szSQLNATIVESQLW);

	// Allocate stmt handles for ANSI connection
	rc = SQLAllocStmt(hdbcANSI, &hstmtANSIA);	// Handle for ANSI calls
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLALLOCSTMT);
	rc = SQLAllocStmt(hdbcANSI, &hstmtANSIW);	// Handle for Unicode calls
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLALLOCSTMT);

	// Allocate stmt handles for Unicode connection
	rc = SQLAllocStmt(hdbcUnicode, &hstmtUA); // Handle for ANSI calls
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcUnicode, SQL_SUCCESS, rc,szSQLALLOCSTMT);
	rc = SQLAllocStmt(hdbcUnicode, &hstmtUW); // Handle for Unicode calls
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcUnicode, SQL_SUCCESS, rc,szSQLALLOCSTMT);

	// Call SQLTablesA&W on two different hdbcs
	strcpy(aszBuf,"%");
	wcscpy(wszBuf,L"%");
	rc = SQLTablesA(hstmtANSIA, NULL, 0, NULL, 0, aszBuf, SQL_NTS, NULL, 0);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtANSIA, SQL_SUCCESS, rc, szSQLTABLESA);
	rc = SQLTablesW(hstmtUW, NULL, 0, NULL, 0, wszBuf, SQL_NTS, NULL, 0);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtUW, SQL_SUCCESS, rc, szSQLTABLESW);

	// Compare the two result sets
	CompareAnsiUnicodeResults(hstmtANSIA, hstmtUW, szSQLTABLESW);

	// See if the driver supports multiple active stmts
	rc = SQLGetInfo(hdbcANSI, SQL_ACTIVE_STATEMENTS, &fStmts, 0, NULL);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc, szSQLGETINFO);

	// Create a search string for ANSI
	aszBuf[0]=aszTable[0];
	aszBuf[1]=TEXT('\0');
	strcat(aszBuf,"%");

	// Create a search string for Unicode
	wszBuf[0]=wszTable[0];
	wszBuf[1]=TEXT('\0');
	wcscat(wszBuf,L"%");

	// If the allowed active statements is > 1, then use the same connection
	// otherwise use the other connection
	if (fStmts > 1)
		hstmtW=hstmtUW;
	else
		hstmtW=hstmtANSIW;

	// Call SQLColumnsA&W on two different hstmts (same connection if allowed)
	// Call for only the given table to limit compare errors at this time
	rc = SQLColumnsA(hstmtUA, NULL, 0, NULL, 0, aszTable, SQL_NTS, NULL, 0);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtANSIA, SQL_SUCCESS, rc, szSQLCOLUMNSA);
	
	// Call for only the given table to limit compare errors at this time
	rc = SQLColumnsW(hstmtW, NULL, 0, NULL, 0, wszTable, SQL_NTS, NULL, 0);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_SUCCESS, rc, szSQLCOLUMNSW);

	CompareAnsiUnicodeResults(hstmtUA, hstmtW, szSQLCOLUMNSW);

	rc = SQLExecDirectA(hstmtUA, aszQuery, SQL_NTS);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtUA, SQL_SUCCESS, rc, szSQLEXECDIRECTA);
	
	// Call for only the given table to limit compare errors at this time
	rc = SQLExecDirectW(hstmtW, wszQuery, SQL_NTS);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtW, SQL_SUCCESS, rc, szSQLEXECDIRECTW);

	CompareAnsiUnicodeResults(hstmtUA, hstmtW, szSQLEXECDIRECTW);

	// Disconnect and free ANSI handles
	rc=SQLFreeStmt(hstmtANSIA, SQL_DROP);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtANSIA, SQL_SUCCESS, rc,szSQLFREESTMT);
	rc=SQLFreeStmt(hstmtANSIW, SQL_DROP);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtANSIW, SQL_SUCCESS, rc,szSQLFREESTMT);
	rc=SQLDisconnect(hdbcANSI);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLCONNECT);
	rc=SQLFreeConnect(hdbcANSI);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcANSI, SQL_SUCCESS, rc,szSQLCONNECT);
	// Disconnect and free Unicode handles
	rc=SQLFreeStmt(hstmtUA, SQL_DROP);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtUA, SQL_SUCCESS, rc,szSQLFREESTMT);
	rc=SQLFreeStmt(hstmtUW, SQL_DROP);
	ERRSHANDLE(SQL_HANDLE_STMT, hstmtUW, SQL_SUCCESS, rc,szSQLFREESTMT);
	rc=SQLDisconnect(hdbcUnicode);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcUnicode, SQL_SUCCESS, rc,szSQLCONNECT);
	rc=SQLFreeConnect(hdbcUnicode);
	ERRSHANDLE(SQL_HANDLE_DBC, hdbcUnicode, SQL_SUCCESS, rc,szSQLCONNECT);

} /* TestMixedAnsiUnicode() */

//-----------------------------------------------------------------------
//      Function:               TestStmtOptions
//-----------------------------------------------------------------------

void  PASCAL TestStmtOptions()
{
	UDWORD	dwLen,
				udw;
	BOOL		fConnectOption;
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szAPI[MEDBUFF];
	SDWORD	cbValue=0;

	SetStatementAttributes(SQL_MAX_LENGTH,(PTR)&udw);

	if (SetStatementAttributes(SQL_MAX_LENGTH, (PTR)TEST_STMT_OPTION))
		fConnectOption = TRUE;

	if (Supported(SQL_API_SQLGETSTMTATTR))
	{
		rc = SQLGetStmtAttr(hstmt, SQL_MAX_LENGTH, (PTR)&dwLen,sizeof(dwLen),&cbValue);
		lstrcpy(szAPI,szSQLGETSTMTATTR);
	}
	else
	{
		rc = SQLGetStmtOption(hstmt, SQL_MAX_LENGTH, &dwLen);
		lstrcpy(szAPI,szSQLGETSTMTOPTION);
	}

	if(rc != SQL_SUCCESS)
	{
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTOPTION);
	}
	else
	{
		if(dwLen != TEST_STMT_OPTION && rc == SQL_SUCCESS && fConnectOption)
			DISPLAYERROR(szSQLGETSTMTOPTION,TEXT("incorrect SQL_MAX_LENGTH value returned"));
	}


} //TestStmtOptions()


//-----------------------------------------------------------------------
//      Function:               SetTableName
//-----------------------------------------------------------------------

void  PASCAL SetTableName(QTSTRUCT  *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		cTableName;
	TCHAR		szTime[MEDBUFF]=TEXT(""),
				szTmpBuff[MEDBUFF],
				*pTime=NULL;

	_tstrtime(szTmpBuff);

	/* Remove colons */
	pTime=_tcstok(szTmpBuff, TEXT(":"));
	while (pTime)
	{
		lstrcat(szTime,pTime);
		pTime=_tcstok(NULL, TEXT(":"));		
	}
 	
	rc = SQLGetInfo(hdbc, SQL_MAX_TABLE_NAME_LEN, &cTableName,
		sizeof (int), NULL);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

	rc = SQLGetInfo(hdbc, SQL_QUALIFIER_NAME_SEPARATOR, lpqt->buf,
		MAX_STRING_SIZE, NULL);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

	if(!lstrcmp(TEXT("\\"), lpqt->buf))
		cTableName -= 4;
	
	_sntprintf(lpqt->szTableName, min(cTableName, MAX_TABLE_NAME-1),
				TEXT("q%s"), szTime);

} //SetTableName()


//-----------------------------------------------------------------------
//      Function:               AllowedType
//
//		If swNumTypes > 0, limits SQL types to those in array
//-----------------------------------------------------------------------
BOOL AllowedType(SWORD fType)
{
	SWORD i, swNumTypes=0;
	BOOL bAllowed=TRUE;
	SWORD rgAllowedTypes[MAX_TYPES_SUPPORTED]={
		SQL_CHAR,
		SQL_BINARY
//		SQL_BIT
/*
		SQL_TINYINT
		SQL_NUMERIC,
		SQL_INTEGER,
		SQL_SMALLINT,
		SQL_FLOAT,
		SQL_REAL,
		SQL_TYPE_TIMESTAMP,
		SQL_LONGVARBINARY,
		SQL_LONGVARCHAR
*/
	};

	if (swNumTypes > 0)
	{
		bAllowed=FALSE;

		for (i=0; i < swNumTypes; i++)
		{
			if (fType == rgAllowedTypes[i])
				bAllowed=TRUE;
		}
	}

	return bAllowed;
}

//-----------------------------------------------------------------------
//      Function:               GetTypeInfo
//-----------------------------------------------------------------------

UWORD  PASCAL GetTypeInfo(FIELDINFO  *rgFields,QTSTRUCT  *lpqt)
{
	RETCODE		rc=SQL_SUCCESS;
	UWORD       cFieldName;
	SDWORD      cMaxTypeSize, cMaxRowSize;
	UWORD       i,
					cTypes=0;
	SDWORD      sdw;
	LPTSTR       pch=NULL;
	BOOL			fAutoInc=0;

	/* Get the type information to use in a create statement for a table */

	rc = SQLGetInfo(hdbc, SQL_MAX_COLUMN_NAME_LEN, &cFieldName,
		sizeof cFieldName, NULL);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

	rc = SQLGetInfo(hdbc, SQL_MAX_ROW_SIZE, &cMaxRowSize,
		sizeof cMaxRowSize, NULL);
	/* don't check for SQL_SUCCES here, it's a 2.0 function.  If it's successful
		That's great, if not then no maximum is assumed. */
	
	cMaxTypeSize = cMaxRowSize / MAX_TYPES_SUPPORTED;
	
/* TO DO: add checks in here for dos file types GetInfo SQL_QUALIFIER_NAME_SEPARATER */

	if(cFieldName > MAX_FIELD - 1)
		cFieldName = MAX_FIELD - 1;

	if(cFieldName < PREFIX_SIZE)
	{
		DISPLAYERROR(szSQLGETINFO,TEXT("MAX_COLUMN_NAME_LEN is too small for autotest to run"));
		goto TypeErrorRet;
	}

	rc = SQLGetTypeInfo(hstmt, SQL_ALL_TYPES);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETTYPEINFO);

	for(i = 0; i < MAX_TYPES_SUPPORTED; i++)
	{
	
		rc = SQLFetch(hstmt);
		if(rc != SQL_SUCCESS && rc !=SQL_SUCCESS_WITH_INFO)
			break;

		*rgFields[i].szType = *rgFields[i].szLength = *rgFields[i].szParams = TEXT('\0');

		/* get type name */
		rc = SQLGetData(hstmt, 1, SQL_C_TCHAR,
			rgFields[i].szType, MAX_TYPE_NAME, &sdw);

		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		wsprintf(rgFields[i].szFieldName,TEXT("c%02u"), i+COLNAME_START);
		/* copy first portion of type name for easy reference */
		_tcsnccat(rgFields[i].szFieldName, rgFields[i].szType, TYPE_PORTION);


		/* change spaces in field name to '_' */
		while((pch = (LPTSTR)_tcschr(rgFields[i].szFieldName, TEXT(' '))) != NULL)
			*pch = TEXT('_');

		/* get the SQLType */
		rc = SQLGetData(hstmt, 2, SQL_C_DEFAULT,
			(SWORD  *)&rgFields[i].wSQLType, IGNORED,
			&sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* Max length */
		rc = SQLGetData(hstmt, 3, SQL_C_TCHAR,
			rgFields[i].szLength, MAX_FIELD, &sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* limit the row size for those drivers that don't support a long
			enough row length for all the fields to be at the max length */
		switch(rgFields[i].wSQLType)
		{
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_VARBINARY:
			case SQL_BINARY:
			case SQL_LONGVARCHAR:
			case SQL_LONGVARBINARY:

				if(cMaxTypeSize)
				{
					if(_ttol (rgFields[i].szLength) > cMaxTypeSize)
						_ltot(cMaxTypeSize, rgFields[i].szLength, 10);
				}
		}

		/* prefix */
		rc = SQLGetData(hstmt, 4, SQL_C_TCHAR,
			rgFields[i].szPrefix, MAX_PREFIX, &sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* suffix */
		rc = SQLGetData(hstmt, 5, SQL_C_TCHAR,
			rgFields[i].szSuffix, MAX_SUFFIX, &sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* create params */
		rc = SQLGetData(hstmt, 6, SQL_C_TCHAR,
			rgFields[i].szParams, MAX_PARAM_SIZE, &sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* nullable */
		rc = SQLGetData(hstmt, 7, SQL_C_SHORT, &rgFields[i].nullable, IGNORED,
			&sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* searchable */
		rc = SQLGetData(hstmt, 9, SQL_C_SHORT, &rgFields[i].fSearchable, IGNORED,
			&sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		/* autoincrement */
		rc = SQLGetData(hstmt, 12, SQL_C_SHORT, &rgFields[i].autoinc, IGNORED,
			&sdw);
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA))
			goto TypeErrorRet;

		// Since some data types will have NULL for autoincrement, we need to set to FALSE
		if (SQL_NULL_DATA == sdw)
			rgFields[i].autoinc=FALSE;

		if (IgnoreType(rgFields[i].szType,rgFields[i].wSQLType))
		{
			i--;
			continue;
		}

		/* The following code only allows the first autoincrement column to
			be placed in the table.  Many DBMS's do not allow more than one per table. */
		if(rgFields[i].autoinc == TRUE)
		{
			if(fAutoInc)
			{
				i--;
				continue;
			}
			else
				fAutoInc = TRUE;
		}

		// Limit data types to those desired (use for debugging)
		if (!AllowedType(rgFields[i].wSQLType))
		{
			i--;
			continue;
		}
	}

	cTypes = i;

	/* if the type name contains spaces, replace them with _ because
		most servers don't allow spaces in field names */

	RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);

	SetTableName(lpqt);

	return(cTypes);

TypeErrorRet:

	return(0);

} //GetTypeInfo()




//-----------------------------------------------------------------------
//      Function:               BuildCreateStmt
//-----------------------------------------------------------------------

BOOL  PASCAL BuildCreateStmt(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes)
{
	RETCODE		rc=SQL_SUCCESS;
	TCHAR        szNum[MAX_NUM_BUFFER];   /* used with _ttoi and itoa conversions */
	SWORD       wNum;
	UWORD       i;
	SDWORD      sdw;
	LPTSTR       pch=NULL;


	/* the column names will be ctypname (where typename is the
		type name returned by the source in SQLGetTypeInfo) */

	*lpqt->sz = TEXT('\0');
	lstrcpy(lpqt->sz,TEXT("Create Table "));
	lstrcat(lpqt->sz, lpqt->szTableName);
	lstrcat(lpqt->sz,TEXT(" ("));
	for(i = 0; i < cTypes; i++) {
			TCHAR szParamType[50];
			TCHAR szNotNull[10];
			*lpqt->szParam = TEXT('\0');

		/* if SQLGetTypeInfo returned params they need to be used in
			the create statement */
		
		if(rgFields[i].szParams == NULL || lstrlen(rgFields[i].szParams) == 0)
			*lpqt->szParam = TEXT('\0');
		else if(_tcschr(rgFields[i].szParams, TEXT(',')) == NULL)
			wsprintf(lpqt->szParam,TEXT("(%s)"), rgFields[i].szLength);
		else
			{
			lstrcpy(szNum, rgFields[i].szLength);
			wsprintf(lpqt->szParam,TEXT("(%s, %d)"), rgFields[i].szLength,
				_ttoi(szNum) - SCALEDIFF);
			}

		lstrcpy(szParamType, rgFields[i].szType);
		if(pch = _tcschr((LPTSTR)szParamType, TEXT('('))) 
			{
			*pch = TEXT('\0');
			lstrcat(szParamType, lpqt->szParam);
			lstrcat(szParamType, (LPTSTR)_tcschr(rgFields[i].szType, TEXT(')')) + 1);
			}
		else
			{
			lstrcat(szParamType, lpqt->szParam);
			}

		/* If the field is not nullable, we need to create the table that way */
		rc = SQLGetInfo(hdbc, SQL_NON_NULLABLE_COLUMNS, &wNum,
			sizeof (SWORD), NULL);
		if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
			RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);
		
		if((rgFields[i].nullable == SQL_NO_NULLS) && (wNum != SQL_NNC_NULL))
			lstrcpy(szNotNull,TEXT("NOT NULL"));
		else
			szNotNull[0] = TEXT('\0');
		
		wsprintf(&lpqt->sz[lstrlen(lpqt->sz)],TEXT(" %s %s %s ,"),
			rgFields[i].szFieldName, (LPTSTR)szParamType, (LPTSTR)szNotNull);
	}

	/* remove the last comma and space */
	lpqt->sz[lstrlen(lpqt->sz) - 2] = TEXT('\0');
	lstrcat(lpqt->sz,TEXT(")"));

	rc = SQLExecDirect(hstmt, lpqt->sz, SQL_NTS);
	if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT))
			goto BuildErrorRet;

	/* now that table was created, call SQLColumns.  Both as
		a test and to get necessary information to insert data */

	rc = SQLColumns(hstmt, NULL, SQL_NTS, NULL, SQL_NTS,
		lpqt->szTableName, SQL_NTS, NULL, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLCOLUMNS);

	for(i = 0; i < cTypes; i++) {
		rc = SQLFetch(hstmt);
		RETCHECK(SQL_SUCCESS, rc,szSQLFETCH);

		/* precision */
		rc = SQLGetData(hstmt, 7, SQL_C_LONG, &rgFields[i].precision, IGNORED,
			&sdw);
		RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);

		/* length */
		if((rgFields[i].precision == 0) || (sdw == SQL_NO_TOTAL)){
			rc = SQLGetData(hstmt, 8, SQL_C_LONG, &rgFields[i].precision, IGNORED,
				&sdw);
			RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);
			if(sdw == SQL_NO_TOTAL)		/* precision & length were undetermined */
				rgFields[i].precision = 1000;	/* so set it to an arbitary value */
		}

		/* numeric scale */
		rc = SQLGetData(hstmt, 9, SQL_C_SHORT, &rgFields[i].scale, IGNORED,
			&sdw);
		RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);
		if(sdw == SQL_NO_TOTAL)
			rgFields[i].scale = 0;
	}

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);

	/* look for columns the test should not try to update by running
		a select * query and calling ColAttributes on the result fields */
	/* select * does not return the fields in a defined order, so field order
		must be specified */

	lstrcpy(lpqt->sz,TEXT("select "));
	for(i = 0; i < cTypes; i ++) {
		if(i)
			lstrcat(lpqt->sz,TEXT(","));
		lstrcat(lpqt->sz, rgFields[i].szFieldName);
	}

	lstrcat(lpqt->sz,TEXT(" from "));
	lstrcat(lpqt->sz, lpqt->szTableName);

	rc = SQLExecDirect(hstmt, lpqt->sz, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

	for(i = 1; i <= cTypes; i++) {

		rc = SQLColAttributes(hstmt, i, SQL_COLUMN_UPDATABLE, NULL,
			0, NULL, &sdw);
		RETCHECK(SQL_SUCCESS, rc,szSQLCOLATTRIBUTES);

		rgFields[i - 1].fAutoUpdate = sdw == SQL_ATTR_READONLY;

		rc = SQLColAttributes(hstmt, i, SQL_COLUMN_UNSIGNED, NULL,
			0, NULL, &sdw);
		RETCHECK(SQL_SUCCESS, rc,szSQLCOLATTRIBUTES);

		rgFields[i - 1].fUnsigned = sdw;
	}

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);

	return(FALSE);

BuildErrorRet:

	return(TRUE);

} //BuildCreateStmt()



//-----------------------------------------------------------------------
//      Function:               BuildInsertStmt
//-----------------------------------------------------------------------
										  
BOOL  PASCAL BuildInsertStmt(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
	DSTRUCT  *lpd,SDWORD  *cColsSelected,BOOL fBindParameter)
{
	RETCODE  	rc;
	UWORD    	w;
	UWORD    	i;
	PTR			ptr;
	UWORD    	ind;
	SDWORD   	sdw;
	LPTSTR    	pch=NULL;
	BOOL			fColNames=TRUE,
					fLongData=FALSE;
	SDWORD  		*sdwArray = (SDWORD  *)AllocateMemory(sizeof(SDWORD) * MAX_TYPES_SUPPORTED);
	
	lstrcpy(lpqt->szColNames,TEXT("\0"));
	lstrcpy(lpqt->szValues,TEXT("\0"));
	
	for(i = 0; i < cTypes; i++) {

		for(ind = 0, w = 0; ind < cTypes; ind++) {

			pch = qtMakeData(i, ind,&rgFields[ind], lpqt->szDataItem);

			if(!pch) /* current type is READ_ONLY) */
				continue;

			/* for every nullable type, that field will be set to	 */
			/* null when the row number corresponds with the field */
			/* number */

			if(*pch) 
				{
				lstrcpy(lpd[w].data, pch);
				lpd[w].cb = SQL_NTS;
				}
			else 
				{
				lstrcpy(lpd[w].data,TEXT(""));
				lpd[w].cb = SQL_NULL_DATA;
				}

			if(fColNames) 
				{
				/* the first time throught, the insert */
				/* statement itself is created         */
				lstrcat(lpqt->szColNames, rgFields[ind].szFieldName);
				lstrcat(lpqt->szColNames,TEXT(", "));
				lstrcat(lpqt->szValues,TEXT(" ?, "));

				/* and parameters are set 										*/
				/* set all the parameters using pointers to buffers in*/
				/* the param struct. 											*/
				if(!fBindParameter)
					{
					rc = SQLSetParam(hstmt, (UWORD)(w+1),
						SQL_C_TCHAR, rgFields[ind].wSQLType,
						rgFields[ind].precision, rgFields[ind].scale,
						&lpd[w].data,
						&lpd[w].cb);
					RETCHECK(SQL_SUCCESS, rc,szSQLSETPARAM);
					}
				else
					{
					rc = SQLBindParameter(hstmt, (UWORD)(w+1),
						SQL_PARAM_INPUT,
						SQL_C_TCHAR, rgFields[ind].wSQLType,
						rgFields[ind].precision, rgFields[ind].scale,
						&lpd[w].data, MAX_STRING_SIZE,
						&lpd[w].cb);
					RETCHECK(SQL_SUCCESS, rc,szSQLBINDPARAMETER);
					}
			}
			w++;
			cNumResSetCols=w;
		}

		if(fColNames) 
			{ 
			/* the first time through, the insert			*/
			/* statement needs to be SQLPrepare'd			*/
			/* remove the "," at the end of the string	*/
			lpqt->szColNames[lstrlen(lpqt->szColNames) - 2] = TEXT('\0');
			lpqt->szValues[lstrlen(lpqt->szValues) - 2] = TEXT('\0');

			wsprintf(lpqt->sz,TEXT("insert into %s (%s) VALUES(%s)"),
				lpqt->szTableName, lpqt->szColNames, lpqt->szValues);

			//copy the insert statement, with the column names. 
			//_ASSERTE(lstrlen(lpqt->sz) < MAX_STRING_SIZE);
			lstrcpy(szInsertStmt,lpqt->sz);

			//prepare the statement
			rc = SQLPrepare(hstmt, lpqt->sz, SQL_NTS);
			if(!RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE))
				goto InsertErrorRet;

			fColNames = FALSE; /* no more first times through */
			}

		rc = SQLExecute(hstmt); /* insert a row */

		if(!RETCHECK(SQL_SUCCESS, rc,szSQLEXECUTE))
		{
			if (SQL_SUCCESS_WITH_INFO != rc)		// BANDAID, normally would fail on S.W.I
				goto InsertErrorRet;
		}

		rc = SQLRowCount(hstmt, &sdw);
		RETCHECK(SQL_SUCCESS, rc,szSQLROWCOUNT);

		if(sdw != 1) /* the execute inserted 1 row */
			DISPLAYERROR(szSQLROWCOUNT,TEXT("Insert single row"));

		/* FreeStmt SQL_CLOSE */
		rc = SQLFreeStmt(hstmt, SQL_CLOSE);
		RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);
	}

	/* for the last row use SQLParamData and SQLPutData */

	/* First check to see if the SQL_LEN_DATA_AT_EXEC macro is supported */
	rc = SQLGetInfo(hdbc, SQL_NEED_LONG_DATA_LEN, lpqt->buf, (SWORD)sizeof(lpqt->buf), NULL);
	if(rc == SQL_SUCCESS)
		if(lpqt->buf[0] == TEXT('Y'))
			fLongData = TRUE;
	
	for(ind = 0, w = 0; ind < cTypes; ind++) 
		{ 

		/* set all the params */
		
		if(rgFields[ind].fAutoUpdate)
			continue;

		if(fLongData && ((rgFields[ind].wSQLType == SQL_LONGVARBINARY) || 
			(rgFields[ind].wSQLType == SQL_LONGVARCHAR))){
			/* Make sure we don't exceed the max negative SDWORD value */
			if(rgFields[ind].precision > (MAXSDWORD + SQL_LEN_DATA_AT_EXEC_OFFSET))
				sdwArray[ind] = MINSDWORD - SQL_LEN_DATA_AT_EXEC_OFFSET;
			else
				sdwArray[ind] = SQL_LEN_DATA_AT_EXEC(rgFields[ind].precision);
			}
		else
			sdwArray[ind] = SQL_DATA_AT_EXEC;

		w++;
		if(!fBindParameter){
			rc = SQLSetParam(hstmt, w,
				SQL_C_TCHAR, rgFields[ind].wSQLType,
				rgFields[ind].precision, rgFields[ind].scale,
				(LPTSTR)(UDWORD)ind, &sdwArray[ind]);
			RETCHECK(SQL_SUCCESS, rc,szSQLSETPARAM);
			}
		else{
			rc = SQLBindParameter(hstmt, w, SQL_PARAM_INPUT,
				SQL_C_TCHAR, rgFields[ind].wSQLType,
				rgFields[ind].precision, rgFields[ind].scale,
				(LPTSTR)(((UDWORD)ind)+BIND_PARM_OFFSET), 0, &sdwArray[ind]);
			RETCHECK(SQL_SUCCESS, rc,szSQLBINDPARAMETER);
			}
	}

	*cColsSelected = w;

	rc = SQLExecDirect(hstmt, lpqt->sz, SQL_NTS);
	if (!RETCHECK(SQL_NEED_DATA, rc,szSQLEXECDIRECT))
		goto InsertErrorRet;


	for(ind = 0; ind <= cTypes; ind++) 
		{
		rc = SQLParamData(hstmt, &ptr);
		if(rc != SQL_NEED_DATA)
			break;

		pch = qtMakeData(cTypes, ind, &rgFields[(unsigned long)ptr-BIND_PARM_OFFSET],
			lpqt->szDataItem);

		if(*pch) {
			rc = SQLPutData(hstmt, pch, SQL_NTS);
			RETCHECK(SQL_SUCCESS, rc,szSQLPUTDATA);
		} else {
			rc = SQLPutData(hstmt, (LPTSTR)IGNORED, SQL_NULL_DATA);
			RETCHECK(SQL_SUCCESS, rc,szSQLPUTDATA);
		}
	}
							  
	RETCHECK(SQL_SUCCESS, rc,szSQLPARAMDATA);

	rc = SQLRowCount(hstmt, &sdw);
	RETCHECK(SQL_SUCCESS, rc,szSQLROWCOUNT);

	if(sdw != 1)
		DISPLAYERROR(szSQLROWCOUNT,TEXT("Insert single row"));

	rc = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);



	ReleaseMemory(sdwArray);

	return(FALSE);

InsertErrorRet:

	ReleaseMemory(sdwArray);
 
	return(TRUE);

} //BuildInsertStmt()


//-----------------------------------------------------------------------
//      Function:               FullDisconnect
//-----------------------------------------------------------------------

void  PASCAL FullDisconnect()
{ 
	RETCODE rc=SQL_SUCCESS;

	/* SQLCancel has the same functionality as SQLFreeStmt w/ SQL_CLOSE	*/
	/*	in a non-asynchronous environment 											*/

	rc = SQLCancel(hstmt);
	RETCHECK(SQL_SUCCESS, rc,szSQLCANCEL);

	FreeStmt(SQL_DROP);

	/* if the connection was made in the						*/
	/*	test, it should be disconnected							*/
	/* in the test, otherwise it should be left connected */

	rc = SQLDisconnect(hdbc);
	RETCHECK(SQL_SUCCESS, rc,szSQLDISCONNECT);

	rc = SQLFreeConnect(hdbc);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREECONNECT);

	rc = SQLFreeEnv(henv);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREEENV);


} //FullDisconnect()



//-----------------------------------------------------------------------
//      Function:               DropTable
//-----------------------------------------------------------------------

void  PASCAL DropTable(LPTSTR szTableName, BOOL fSilent)
{		
	TCHAR		szBuff[100];
	RETCODE	rc=SQL_ERROR;

	lstrcpy(szBuff,TEXT("drop table "));
	lstrcat(szBuff, szTableName);

	rc = SQLExecDirect(hstmt, szBuff, SQL_NTS);

	if (!fSilent)
		{
		if(!RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT))
			szWrite(TEXT("Unable to drop table"), TRUE);
		}

} //DropTable()



//-----------------------------------------------------------------------
//    Function:	CleanUp
//		Purpose:		To drop the table,disconnect from data source and
//						release memory.			
//-----------------------------------------------------------------------
	
void  PASCAL CleanUp(DSTRUCT  *lpd,QTSTRUCT  *lpqt,FIELDINFO  *rgFields,
	LPTSTR szTableName,BOOL fSilent,LPTSTR szValidServer)
{

	DropTable(szTableName, fSilent);

	if(szValidServer)
		FullDisconnect();

	ReleaseMemory(lpd);
	ReleaseMemory(lpqt);
	ReleaseMemory(rgFields);

} //CleanUp()


//-----------------------------------------------------------------------
//      Function:               BindAllColumns
//-----------------------------------------------------------------------

BOOL  PASCAL BindAllColumns(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
	DSTRUCT  *lpd)
{
//-----------------------------------------------------------------------
//      Function:               BindAllColumns
	UWORD		i,
				w;
	RETCODE	rc=SQL_SUCCESS;

	for(i = 0, w = 0; i < cTypes; i++) 
		{

		if(!qtMakeData(1, i,&rgFields[i],lpqt->szDataItem))
			continue;

		w++;

		switch(rgFields[i].wSQLType) 
			{
			case SQL_INTEGER:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].sdword, IGNORED, &lpd[i].cb);
				break;
			case SQL_SMALLINT:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].sword, IGNORED, &lpd[i].cb);
				break;
			case SQL_FLOAT:
			case SQL_DOUBLE:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].sdouble, IGNORED, &lpd[i].cb);
				break;
			case SQL_REAL:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].sfloat, IGNORED, &lpd[i].cb);
				break;
			case SQL_DATE:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].date, IGNORED, &lpd[i].cb);
				break;
			case SQL_TIME:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].time, IGNORED, &lpd[i].cb);
				break;
			case SQL_TIMESTAMP:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpd[i].timestamp, IGNORED, &lpd[i].cb);
				break;
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_NUMERIC:
			case SQL_DECIMAL:
			default:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							lpd[i].data, MAX_STRING_SIZE, &lpd[i].cb);
				break;
			}

		if(!RETCHECK(SQL_SUCCESS, rc, szSQLBINDCOL))
			return(FALSE);
		}

	return(TRUE);

} //BindAllColumns()

/*-----------------------------------------------------------------------
 *      Function:               BindFetchColumns
 *  Used for Checking data in Result sets from fetch calls.
 *  Binds Binary data types as SQL_C_CHAR
 *----------------------------------------------------------------------- */

BOOL  PASCAL BindFetchColumns(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
	DSTRUCT  *lpdFetch)
{
	UWORD		i,
				w;
	RETCODE	rc=SQL_SUCCESS;

	for(i = 0, w = 0; i < cTypes; i++) 
		{

		if(!qtMakeData(0, i,&rgFields[i],lpqt->szDataItem))
			continue;

		w++;

		switch(rgFields[i].wSQLType) 
			{
			case SQL_BIGINT:
			case SQL_INTEGER:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].sdword, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_TINYINT:
			case SQL_SMALLINT:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].sword, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_FLOAT:
			case SQL_DOUBLE:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].sdouble, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_REAL:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].sfloat, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_DATE:
			case SQL_TYPE_DATE:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].date, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_TIME:
			case SQL_TYPE_TIME:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].time, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_TIMESTAMP:
			case SQL_TYPE_TIMESTAMP:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							&lpdFetch[i].timestamp, IGNORED, &lpdFetch[i].cb);
				break;
			case SQL_BIT:
			case SQL_BINARY:
			case SQL_VARBINARY:
			case SQL_LONGVARBINARY:
				rc = SQLBindCol(hstmt, w, SQL_C_TCHAR,
							lpdFetch[i].data, MAX_STRING_SIZE, &lpdFetch[i].cb);
				break;
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_NUMERIC:
			case SQL_DECIMAL:
			default:
				rc = SQLBindCol(hstmt, w, SQL_C_DEFAULT,
							lpdFetch[i].data, MAX_STRING_SIZE, &lpdFetch[i].cb);
				break;
			}

		if(!RETCHECK(SQL_SUCCESS, rc, szSQLBINDCOL))
			return(FALSE);
		}

	return(TRUE);

} /*BindFetchColumns() */

//-----------------------------------------------------------------------
//      Function:               TestMetaData
//-----------------------------------------------------------------------

void  PASCAL TestMetaData(lpSERVERINFO lpSI, QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes)
{
	SWORD    wNum;
	UWORD    w;
	UWORD    i;
	UDWORD   dwLen;
	RETCODE	rc=SQL_SUCCESS;
	SWORD		wType;
	SWORD		wNull;

	SelectFromTable(lpqt);

	for(i = 0, w = 0; i < cTypes; i++) 
		{
		dwLen = 0;
		wNum = 0;
		wNull = 0;

		/* information returned by SQLDescribeCol should match info */
		/*	used to create table */

		if(!qtMakeData(1, i,&rgFields[i],lpqt->szDataItem))
			continue;

		w++;
		rc = SQLDescribeCol(hstmt, w, lpqt->buf,
			MAX_STRING_SIZE, NULL, &wType, &dwLen, &wNum, &wNull);
		RETCHECK(SQL_SUCCESS, rc,szSQLDESCRIBECOL);

		/* verify that column name returned is column name created */

		if(0 != lstrcmpi(rgFields[i].szFieldName, lpqt->buf))
			DISPLAYERROR(szSQLDESCRIBECOL,TEXT("incorrect column name"));

		if(wType != rgFields[i].wSQLType)
		{
			// For a 2.x driver, SQLGetTypeInfo result will be SQL_DATE, etc,
			// but 3.0 DM will convert SQLDescribeCol values to TYPE_DATE, ETC.
			if ((uDriverODBCVer < 3) && 
				((SQL_TYPE_DATE == wType && SQL_DATE == rgFields[i].wSQLType) ||
				(SQL_TYPE_TIME == wType && SQL_TIME == rgFields[i].wSQLType) ||
				(SQL_TYPE_TIMESTAMP == wType && SQL_TIMESTAMP == rgFields[i].wSQLType)))
				NULL;
			else
				DISPLAYERROR(szSQLDESCRIBECOL,TEXT("incorrect SQLType"));
		}

		if(dwLen != (UDWORD)rgFields[i].precision)
			DISPLAYERROR(szSQLDESCRIBECOL,TEXT("incorrect precision"));
		
		if(wNum != rgFields[i].scale)
			DISPLAYERROR(szSQLDESCRIBECOL,TEXT("incorrect scale"));
		
		if(wNull != rgFields[i].nullable && wNull != SQL_NULLABLE_UNKNOWN &&
			rgFields[i].nullable != SQL_NULLABLE_UNKNOWN)
			{
			DISPLAYERROR(szSQLDESCRIBECOL,TEXT("incorrect nullable"));
			}
		}

	FreeStmt(SQL_CLOSE);

} //TestMetaData()


//-----------------------------------------------------------------------
//      Function:               RetrieveData
//-----------------------------------------------------------------------

void PASCAL RetrieveData(QTSTRUCT *lpqt,FIELDINFO *rgFields,
	UWORD cTypes,DSTRUCT *lpd)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		ind,
				i;
	int		nSame;
	LPTSTR	pch=NULL;
	TCHAR		szNum[MAX_NUM_BUFFER];   /* used with _ttoi and itoa conversions */
	TCHAR		*stopstring=NULL;
	double	Num=0,
				Num2=0;

	for(ind = 0; ;ind++) 
		{

		/* Get the data back */
		rc = SQLFetch(hstmt);
		if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
			break;

		for(i = 0; i < cTypes; i++) 
			{ 
			/* make sure it's original data placed */
			/* in that field/row location 			*/
			pch = qtMakeData(ind, i,&rgFields[i], lpqt->szDataItem);

			if(!pch)
				continue;

			if(!*pch) {
				if(lpd[i].cb != SQL_NULL_DATA)
					DISPLAYERROR(szRETDATA, TEXT("should have been NULL"));
				continue;
			}
			switch(rgFields[i].wSQLType) 
				{
				/* check the outlen and data	*/
				/* returned for each type. 	*/
				case SQL_INTEGER:
					if(lpd[i].cb != sizeof(SDWORD))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					lstrcpy(szNum, pch);
					nSame = _ttol(szNum) == lpd[i].sdword;
					break;
				case SQL_SMALLINT:
					if(lpd[i].cb != sizeof(SWORD))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					lstrcpy(szNum, pch);
					nSame = _ttoi(szNum) == lpd[i].sword;
					break;

				case SQL_FLOAT:
				case SQL_DOUBLE:
					if(lpd[i].cb != sizeof(SDOUBLE))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					lstrcpy(szNum, pch);
					Num=_tcstod(szNum, &stopstring);
					nSame = Num - lpd[i].sdouble < 0.001 && Num - lpd[i].sdouble > -0.001;

					break;

				case SQL_REAL:
					if(lpd[i].cb != sizeof(SFLOAT))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					lstrcpy(szNum, pch);
					Num=_tcstod(szNum, &stopstring);

					nSame = Num - lpd[i].sfloat < 0.001 && Num - lpd[i].sfloat > -0.001;
					break;

				case SQL_TINYINT:
					if(lpd[i].cb != sizeof(TCHAR))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					lstrcpy(szNum, pch);
					nSame = (TCHAR)_ttoi(szNum) == (TCHAR)lpd[i].data[0];
					break;

				case SQL_DECIMAL:
				case SQL_NUMERIC:
					if(lpd[i].cb > MAX_STRING_SIZE)
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					if(lpd[i].cb > lstrlen(lpd[i].data))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					{
					TCHAR szNum2[MAX_NUM_BUFFER];

					lstrcpy(szNum, pch);
					lstrcpy(szNum2, pch);
					Num=_tcstod(szNum, &stopstring);
					Num2=_tcstod(szNum2, &stopstring);

					nSame = Num - Num2 < 0.001 &&	Num - Num2 > -0.001;
					}

					break;


				case SQL_VARCHAR:
				case SQL_LONGVARCHAR:
					if(lpd[i].cb > MAX_STRING_SIZE)
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					if(lpd[i].cb > lstrlen(lpd[i].data))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					nSame = !!_tcsstr(lpd[i].data, pch);

					break;

				case SQL_VARBINARY:
				case SQL_LONGVARBINARY:
					if(lpd[i].cb > MAX_STRING_SIZE)
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					if(lpd[i].cb  * 2 != lstrlen(pch))
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					nSame = TRUE; /* not checking returned data for binary */

					break;

				case SQL_CHAR:
					if(lpd[i].cb > MAX_STRING_SIZE && rc == SQL_SUCCESS)
						DISPLAYERROR(szRETDATA,TEXT("incorrect return code for outlen"));

					if(lpd[i].cb != rgFields[i].precision && rc == SQL_SUCCESS)
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);

					nSame = !_tcsnccmp(lpd[i].data, pch, lstrlen(pch));

					break;
				case SQL_BINARY:
				default:
					if(lpd[i].cb > MAX_STRING_SIZE && rc == SQL_SUCCESS)
						DISPLAYERROR(szRETDATA,szINCORRECTOUTLEN);
					nSame = TRUE; /* not checking returned data for binary */
				}

		if(!nSame)
			DISPLAYERROR(szRETDATA, TEXT("invalid data"));
		}
	}

	RETCHECK(SQL_NO_DATA_FOUND, rc, szSQLFETCH);

	if(ind != cTypes + 1)
		DISPLAYERROR(szSQLFETCH, TEXT("Incorrect number of result rows"));

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	rc = SQLFreeStmt(hstmt, SQL_UNBIND);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	rc = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

} // RetrieveData()


									  
//-----------------------------------------------------------------------
//      Function:               TestData
//-----------------------------------------------------------------------

void  PASCAL TestData(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,
	UWORD cTypes,DSTRUCT  *lpd)
{

	/* bind all fields to a variable of the correct type for retreiving data */
	if (!BindAllColumns(lpqt,rgFields,cTypes,lpd))
		return;

	SelectFromTable(lpqt);

	RetrieveData(lpqt,rgFields,cTypes,lpd);

} // TestData()


//-----------------------------------------------------------------------
//      Function:               CreateParamQuery
//-----------------------------------------------------------------------

void  PASCAL CreateParamQuery(QTSTRUCT *lpqt, FIELDINFO *rgFields,UWORD cTypes)
{	
	RETCODE	rc=SQL_SUCCESS;
	UWORD		i;
	LPTSTR	pch=NULL;
	TCHAR		szQuery[MAX_QUERY_SIZE];
	SDWORD	sdw = SQL_DATA_AT_EXEC;
	UWORD		w,
				ind;


	wsprintf(szQuery,TEXT("select %s from %s where "), lpqt->szColNames,lpqt->szTableName);


	for(i = 0, w = 0,ind=0; i < cTypes; i++) 
		{
		pch = qtMakeData(ind, i,&rgFields[i], lpqt->szDataItem);

		if ((rgFields[i].fSearchable == SQL_SEARCHABLE ||
			rgFields[i].fSearchable == SQL_ALL_EXCEPT_LIKE) &&
			pch && *pch) 
		{
			w++;

			switch(rgFields[i].wSQLType)
			{
				case SQL_REAL:
				case SQL_FLOAT:
				case SQL_DOUBLE:
					wsprintf(&szQuery[lstrlen(szQuery)],TEXT("%s < ? + 1 and "),
						rgFields[i].szFieldName);
					break;
				default:
					wsprintf(&szQuery[lstrlen(szQuery)],TEXT("%s = ? and "),
						rgFields[i].szFieldName);
			}

			if(!fBindParameter)
			{
				rc = SQLSetParam(hstmt, w,
					SQL_C_TCHAR, rgFields[i].wSQLType,
					rgFields[i].precision, rgFields[i].scale,
					(LPTSTR)(UDWORD)i, &sdw);
				RETCHECK(SQL_SUCCESS, rc,szSQLSETPARAM);
			}
			else
			{
				rc = SQLBindParameter(hstmt, w, SQL_PARAM_INPUT,
					SQL_C_TCHAR, rgFields[i].wSQLType,
					rgFields[i].precision, rgFields[i].scale,
					(LPTSTR)((UDWORD)i+BIND_PARM_OFFSET), 0, &sdw);
				RETCHECK(SQL_SUCCESS, rc,szSQLBINDPARAMETER);
			}

			ind++;
		}
	}

	if (_tcsstr(szQuery,TEXT("and")))
	{
		/* remove the final "and " */
		szQuery[lstrlen(szQuery) - 5] = TEXT('\0');
	}

	lstrcpy(lpqt->szParamQuery, szQuery);

}

//-----------------------------------------------------------------------
//      Function:               TestSearchedQuery
//-----------------------------------------------------------------------

void  PASCAL TestSearchedQuery(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,
	UWORD cTypes,DSTRUCT  *lpd,BOOL fBindParameter)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		i;
	LPTSTR		pch=NULL;
	SDWORD	sdw;
	UWORD		w;
	UDWORD	udw;
	UWORD		ind;


	wsprintf(lpqt->sz, TEXT("select %s from %s where "), lpqt->szColNames,
		lpqt->szTableName);

    sdw = SQL_DATA_AT_EXEC;

	for(i = 0, w = 0,ind=0; i < cTypes; i++) 
		{
		pch = qtMakeData(ind, i,&rgFields[i], lpqt->szDataItem);

		if ((rgFields[i].fSearchable == SQL_SEARCHABLE ||
			rgFields[i].fSearchable == SQL_ALL_EXCEPT_LIKE) &&
			pch && *pch) {
			w++;
			switch(rgFields[i].wSQLType) {
				case SQL_REAL:
				case SQL_FLOAT:
				case SQL_DOUBLE:
					wsprintf(&lpqt->sz[lstrlen(lpqt->sz)], TEXT("%s < ? + 1 and "),
						rgFields[i].szFieldName);
					break;
				default:
					wsprintf(&lpqt->sz[lstrlen(lpqt->sz)], TEXT("%s = ? and "),
					rgFields[i].szFieldName);
			}

			if(!fBindParameter){
				rc = SQLSetParam(hstmt, w,
					SQL_C_TCHAR, rgFields[i].wSQLType,
					rgFields[i].precision, rgFields[i].scale,
					(LPTSTR)(UDWORD)i, &sdw);
				RETCHECK(SQL_SUCCESS, rc, szSQLSETPARAM);
				}
			else{
				rc = SQLBindParameter(hstmt, w, SQL_PARAM_INPUT,
					SQL_C_TCHAR, rgFields[i].wSQLType,
					rgFields[i].precision, rgFields[i].scale,
					(LPTSTR)((UDWORD)i+BIND_PARM_OFFSET), 0, &sdw);
				RETCHECK(SQL_SUCCESS, rc, szSQLBINDPARAMETER);
				}

			ind++;
		}
	}
	/* remove the final "and " */
	lpqt->sz[lstrlen(lpqt->sz) - 5] = TEXT('\0');
	lstrcpy(lpqt->szParamQuery, lpqt->sz);

	rc = SQLPrepare(hstmt, lpqt->sz, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc, szSQLPREPARE);

	rc = SQLExecute(hstmt);
	RETCHECK(SQL_NEED_DATA, rc, szSQLEXECUTE);

	udw = cTypes;

	for(i = 0; ; i++) 
		{
		rc = SQLParamData(hstmt, (PTR *)&udw);
		if(rc != SQL_NEED_DATA)
			break;

		if(udw-BIND_PARM_OFFSET < cTypes)
			pch = qtMakeData(cTypes, i,&rgFields[udw-BIND_PARM_OFFSET], lpqt->szDataItem);
		else
			DISPLAYERROR(szSQLPARAMDATA, TEXT("invalid rgbValue"));

		if(*pch) 
			{
			udw = lstrlen(pch);
			rc = SQLPutData(hstmt, pch, (SDWORD)lstrlen(pch));
			RETCHECK(SQL_SUCCESS, rc, szSQLPUTDATA);
			} 
		else
			{
			rc = SQLPutData(hstmt, (LPTSTR)IGNORED, SQL_NULL_DATA);
			RETCHECK(SQL_SUCCESS, rc, szSQLPUTDATA);
			}
		}

	RETCHECK(SQL_SUCCESS, rc, szSQLPARAMDATA);

	for(i = 0;; i++) 
		{
		rc = SQLFetch(hstmt);

		if(rc != SQL_SUCCESS)
			break;
		}

	RETCHECK(SQL_NO_DATA_FOUND, rc, szSQLFETCH);

	/* should have gotten 1 row back */

	if(i != 1)
		DISPLAYERROR(TEXT("Param/PutData"), TEXT("incorrect number of rows returned"));

	FreeStmt(SQL_CLOSE);

} //TestSearchedQuery()



//-----------------------------------------------------------------------
//      Function:               TestLargeQuery
//-----------------------------------------------------------------------

void  PASCAL TestLargeQuery(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,
	UWORD cTypes,DSTRUCT  *lpd)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		ind=0,
				i;
	LPTSTR	pch=NULL;
	TCHAR		szQuery[2048];


	/* > 1K query */
	wsprintf(szQuery,TEXT("select %s from %s where "), lpqt->szColNames,
		lpqt->szTableName);

	for(i = 0; i < cTypes; i++) 
		{
		if (rgFields[i].fSearchable == SQL_SEARCHABLE ||
			rgFields[i].fSearchable == SQL_ALL_EXCEPT_LIKE)
			break;
		}

	pch = qtMakeData(cTypes, 1, &rgFields[i], lpqt->szDataItem);
	while(lstrlen(szQuery) < 1024L) 
		{
		int li=lstrlen(szQuery);
		switch(rgFields[i].wSQLType) 
			{
			case SQL_REAL:
			case SQL_FLOAT:
			case SQL_DOUBLE:
				wsprintf(&szQuery[lstrlen(szQuery)],TEXT("%s < %s + 1 and "),
					rgFields[i].szFieldName, pch);
				break;
			default:
				wsprintf(&szQuery[lstrlen(szQuery)],TEXT("%s = %s%s%s and "),
				rgFields[i].szFieldName, rgFields[i].szPrefix, pch, rgFields[i].szSuffix);
				break;
			}
		}

	/* remove the final "and " */
	szQuery[lstrlen(szQuery) - 5] = TEXT('\0');
				
	rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

	if (RC_SUCCESSFUL(rc))
		{
		for(i = 0;; i++) 
			{
			rc = SQLFetch(hstmt);

			if(rc != SQL_SUCCESS)
				break;
			}

		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		/* should have gotten at least 1 row back */

		if(i < 1)
			DISPLAYERROR(TEXT("> 1K query"),TEXT("incorrect number of rows returned"));

		}
			
	/* SQLFreeStmt with SQL_CLOSE to re-use the hstmt */

	FreeStmt(SQL_CLOSE);

} //TestLargeQuery()



//-----------------------------------------------------------------------
//      Function:               TestSQLTables
//-----------------------------------------------------------------------

void  PASCAL TestSQLTables(QTSTRUCT  *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	BOOL		fFoundTable=FALSE;	
	UWORD		i;

	/* this call may return many tables, as  */
	/* long as the one created earlier shows */
	/* up it will pass. */
		
	rc = SQLTables(hstmt, NULL, 0, NULL, 0,TEXT("q%"),SQL_NTS,TEXT("'TABLE'"), SQL_NTS); 

	RETCHECK(SQL_SUCCESS, rc,szSQLTABLES);

	for(i = 0;; i++) 
		{
		rc = SQLFetch(hstmt);
		if(rc != SQL_SUCCESS)
			break;

		/* column 3 is tablename */
		rc = SQLGetData(hstmt, 3, SQL_C_TCHAR, lpqt->sz, MAX_STRING_SIZE, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA); /* should not overflow
			and return SQL_SUCCESS_WITH_INFO because the buffer is larger than the
			table name */
		fFoundTable += 0 == lstrcmpi(lpqt->sz, lpqt->szTableName);
		}

	RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

	if(1 != fFoundTable) {
		DISPLAYERROR(szSQLTABLES,TEXT("table not found"));
	}

	FreeStmt(SQL_CLOSE);

} //TestSQLTables()


//-----------------------------------------------------------------------
//      Function:               TestSQLSpecialCols
//-----------------------------------------------------------------------

void  PASCAL TestSQLSpecialCols(QTSTRUCT  *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		i;

	rc = SQLSpecialColumns(hstmt, SQL_BEST_ROWID, NULL, 0, NULL, 0,
		lpqt->szTableName, (SWORD)(lstrlen(lpqt->szTableName)), SQL_SCOPE_TRANSACTION,
		SQL_NULLABLE);
	RETCHECK(SQL_SUCCESS, rc,szSQLSPECIALCOLUMNS);

	for(i = 0;; i++)
		{
		rc = SQLFetch(hstmt);
		if(rc != SQL_SUCCESS)
			break;
		}

	RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

	FreeStmt(SQL_CLOSE);

} //TestSQLSpecialCols()




//-----------------------------------------------------------------------
//      Function:               VerifyIndex
//-----------------------------------------------------------------------

void  PASCAL VerifyIndex(QTSTRUCT  *lpqt,UWORD fIndex)
{
	RETCODE	rc=SQL_SUCCESS;
	BOOL		fFoundTable=FALSE;
	UWORD		i;
	SDWORD	sdw;

	rc = SQLStatistics(hstmt, NULL, 0, NULL, 0, lpqt->szTableName,
	SQL_NTS, SQL_INDEX_ALL, SQL_ENSURE);
	RETCHECK(SQL_SUCCESS, rc,TEXT("SQLStatistics"));

	fFoundTable = 0;
	for(i = 0;; i++) 
		{
		rc = SQLFetch(hstmt);
		if(rc != SQL_SUCCESS)
			break;

		rc = SQLGetData(hstmt, 3, SQL_C_TCHAR, lpqt->sz, MAX_STRING_SIZE,
			&sdw);
		RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);
		if (lstrcmpi(lpqt->sz, lpqt->szTableName) == 0)
			{
			rc = SQLGetData(hstmt, 6, SQL_C_TCHAR, lpqt->sz, MAX_STRING_SIZE,
				&sdw);
			RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);
			fFoundTable += 0 == lstrcmpi(lpqt->sz, lpqt->szDataItem);
			}
		}

	RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

	if(1 != fFoundTable && fIndex)
		DISPLAYERROR(TEXT("SQLStatistics"),TEXT("index not returned"));

	/* one row represents original table, the */
	/* other represents the index 				*/
	if(i > 2 || i < 1) 
		DISPLAYERROR(TEXT("SQLStatistics"),TEXT("too many rows"));

	FreeStmt(SQL_CLOSE);

} //VerifyIndex()

//-----------------------------------------------------------------------
//      Function:               TestSQLStatistics
//-----------------------------------------------------------------------

BOOL  PASCAL TestSQLStatistics(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,
	UWORD cTypes,DSTRUCT  *lpd,UWORD fIndex)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		i;

	lstrcpy(lpqt->szDataItem, lpqt->szTableName);
	lpqt->szDataItem[0] = TEXT('i');
	for(i = 1; i < cTypes; i++)
		if(rgFields[i].wSQLType == SQL_INTEGER ||
			rgFields[i].wSQLType == SQL_SMALLINT)
			break;
	if(i == cTypes)
		i = 0;

	lstrcpy(lpqt->buf, rgFields[i].szFieldName);
	wsprintf(lpqt->sz,TEXT("create unique index %s on %s (%s)"),
		lpqt->szDataItem, lpqt->szTableName, lpqt->buf);

	rc = SQLExecDirect(hstmt, lpqt->sz, SQL_NTS);
	if(fIndex < 1)
		/* if this is minimal grammar, don't count on indexes being available */
		fIndex = rc == SQL_SUCCESS;
	else
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

	VerifyIndex(lpqt,fIndex);

	return(fIndex);

} //TestSQLStatistics()


//-----------------------------------------------------------------------
//      Function:               TestLikeQuery
//-----------------------------------------------------------------------

void  PASCAL TestLikeQuery(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,
	UWORD cTypes,DSTRUCT  *lpd)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD	i;
	SDWORD	cbValue=0;

	for(i = 0; i < cTypes; i++) 
		{
		if(rgFields[i].fSearchable == SQL_LIKE_ONLY ||
			rgFields[i].fSearchable == SQL_SEARCHABLE) 
			{
			lstrcpy(lpqt->buf, rgFields[i].szFieldName);
			break;
			}
	}

	if(i < cTypes) 
		{

		/* execute a query using like.  This query should return all records */
		/* this query should return all rows in the table 							*/

		wsprintf(lpqt->sz,TEXT("select * from %s where %s not like 'a'"), lpqt->szTableName,
			lpqt->buf, lpqt->buf);
		rc = SQLExecDirect(hstmt, lpqt->sz, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		for(i = 0;; i++) 
			{
			rc = SQLFetch(hstmt);
			if(rc != SQL_SUCCESS)
				break;

			rc = SQLGetData(hstmt, 1, SQL_C_TCHAR, lpqt->sz, MAX_STRING_SIZE,
				&cbValue);
			if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
				RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);
			}

		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		if(i != cTypes)
			DISPLAYERROR(TEXT("'LIKE' query"),TEXT("incorrect number of result rows"));

		}

	FreeStmt(SQL_CLOSE);

} //TestLikeQuery()


//-----------------------------------------------------------------------
//      Function:               TestLikeQuery
//-----------------------------------------------------------------------

void  PASCAL TestOJCap(QTSTRUCT  *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	UDWORD	udw;

	rc = SQLGetInfo(hdbc, (UWORD)SQL_OJ_CAPABILITIES, &udw, (SWORD)(sizeof(udw)), NULL);
	if(RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO))
	{
		udw &= ~(SQL_OJ_LEFT | SQL_OJ_RIGHT | SQL_OJ_FULL | SQL_OJ_NESTED	|
					SQL_OJ_NOT_ORDERED | SQL_OJ_INNER | SQL_OJ_ALL_COMPARISON_OPS);
		if(udw)
		{
			wsprintf(lpqt->buf,TEXT("Undefined flags return from SQLGetInfo(...SQL_OJ_CAPABILITIES...) = %lX"), udw);
			DISPLAYERROR(szSQLGETINFO, lpqt->buf);
		}
	}

	rc = SQLGetInfo(hdbc, SQL_OUTER_JOINS, lpqt->buf, MAX_STRING_SIZE, NULL);
	if(RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO)){
		*lpqt->buf = toupper(*lpqt->buf);
		if((!_tcsnccmp(lpqt->buf,TEXT("Y"), 1)) && (!_tcsnccmp(lpqt->buf,TEXT("N"), 1)))
			DISPLAYERROR(szSQLGETINFO,TEXT("Driver returned an invalid value for SQLGetInfo(...SQL_OUTER_JOINS...).  The only valid values are \"Y\" and \"N\"."));
		}

} //TestOJCap()


/*-----------------------------------------------------------------------
 *      Function:               TestExtendedFetch
 *-----------------------------------------------------------------------*/

void  PASCAL TestExtendedFetch(QTSTRUCT  *lpqt, FIELDINFO  *rgFields, UWORD cTypes)
{
	RETCODE	rc=SQL_SUCCESS;
	WORD		fLevel2 = FALSE;
	DWORD		dwLen=0;
	SWORD		fSqlType;
	SDWORD	cbValue=0;
	UWORD		iTableCol,row,iCol,uwRowSetSize;
	TCHAR		szQuery[MAX_STRING_SIZE], szColName[SMALLBUFF];
	TCHAR*	rgbValue;
	DSTRUCT*	rgData;
	DSTRUCT*	pDataBuf;
	BOOL		fCol0Bound=TRUE;

	uwRowSetSize=5; /* Cinco seems like a good rowset size */

	/* Only col which might not be bound but might not be AutoUpdateable is col 0 */
	if(!qtMakeData(0, 0, &rgFields[0], szQuery))
		fCol0Bound = FALSE;

	SelectFromTable(lpqt);

	rc = SQLBindCol(hstmt, 1, SQL_C_BINARY, lpqt->sz, MAX_BIND_ARRAY_ELEMENT,
		&cbValue);
	RETCHECK(SQL_SUCCESS, rc,szSQLBINDCOL);

	if (!Supported(SQL_API_SQLEXTENDEDFETCH)) 
	{
		rc = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, IGNORED, NULL, NULL);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLEXTENDEDFETCH, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLEXTENDEDFETCH);

		FreeStmt(SQL_CLOSE);
		return;
	} 

	rc = SQLGetStmtOption(hstmt,SQL_CURSOR_TYPE,&dwLen);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTOPTION);

	if(dwLen != SQL_CURSOR_FORWARD_ONLY)
		{
		rc = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, IGNORED, NULL, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXTENDEDFETCH);
		}
	else
		{
		rc = SQLExtendedFetch(hstmt, SQL_FETCH_FIRST, IGNORED, NULL, NULL);
		RETCHECK(SQL_ERROR, rc,szSQLEXTENDEDFETCH);
		}

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	rc = SQLFreeStmt(hstmt, SQL_UNBIND);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	rc = SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	/* Allocate an area for ExtendedFetch to take place */
	if (!(rgData = AllocateMemory(sizeof(DSTRUCT)*cTypes*uwRowSetSize))){
		DISPLAYERROR(szSQLEXTENDEDFETCH,TEXT("Insufficient Memory Available"));
		return;	
	}

	/* Allocate an area for test data */
	if (!(rgbValue = AllocateMemory(MAX_STRING_SIZE))){
		DISPLAYERROR(szSQLEXTENDEDFETCH,TEXT("Insufficient Memory Available"));
		ReleaseMemory(rgData);
		return;
	}

	/* Get column for "order by" clause: */
	wsprintf(szQuery,TEXT("select %s from %s"),lpqt->szColNames, lpqt->szTableName);
	rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
	if((SQL_SUCCESS!=rc) && (SQL_SUCCESS_WITH_INFO!=rc)){
		RETCHECK(SQL_SUCCESS_WITH_INFO, rc, szSQLEXECDIRECT);
		goto abortxfetch;
	}
	iCol=0;
	do	{
		iCol++;
		rc=SQLDescribeCol(hstmt, iCol, szColName, (SMALLBUFF*sizeof(TCHAR)), 
			NULL, &fSqlType, NULL, NULL, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLDESCRIBECOL);
	} while(fSqlType!=SQL_CHAR && iCol<=cTypes);

	FreeStmt(SQL_CLOSE);
	if(iCol>cTypes){
		DISPLAYERROR(szSQLEXTENDEDFETCH, TEXT("\t\t\tSelect-order by  Failed"));
		goto abortxfetch;
	}

	/* Set rowset size and set to row-wise binding:  */
	rc = SQLSetStmtOption(hstmt, SQL_ROWSET_SIZE, (UDWORD)uwRowSetSize);
	if (SQL_SUCCESS != rc){
		DISPLAYERROR(TEXT("ExtendedFetch...SQLSetStmtOption(Rowset_Size)"),
			TEXT("SQLSetStmtOption Failed"));
		GetErrors(henv, hdbc,hstmt);
	}	
	rc = SQLSetStmtOption(hstmt, SQL_BIND_TYPE, (sizeof(DSTRUCT)*cTypes));
	if (SQL_SUCCESS != rc){
		DISPLAYERROR(TEXT("ExtendedFetch...SQLSetStmtOption(Bind_Type)"),
			TEXT("SQLSetStmtOption Failed"));
		GetErrors(henv, hdbc,hstmt);
	}

	if(SQL_SUCCESS != SelectFromTableFetch(lpqt, szColName)){
		DISPLAYERROR(szSQLEXTENDEDFETCH, TEXT("\t\t\tSelect-order by  Failed"));
		goto abortxfetch;
	}
	if (!BindFetchColumns(lpqt, rgFields, cTypes, rgData)){
		DISPLAYERROR(szSQLEXTENDEDFETCH, szSQLBINDCOL);
		goto abortxfetch;
	}
	/* Fetch into allocated area rowset to be tested */
	rc = SQLExtendedFetch(hstmt, SQL_FETCH_NEXT, 1, NULL, NULL);
	if (SQL_SUCCESS != rc){
		RETCHECK(SQL_SUCCESS, rc,szSQLEXTENDEDFETCH);
		DISPLAYERROR(szSQLEXTENDEDFETCH, TEXT("Fetch Failed"));
		goto abortxfetch;
	}

	rc = SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	rc = SQLFreeStmt(hstmt, SQL_UNBIND);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);
	
	/* Set rowset size to "1" to test each row of rowset independently:  */
	rc = SQLSetStmtOption(hstmt, SQL_ROWSET_SIZE, (UDWORD)(1));
	if (SQL_SUCCESS != rc){
		DISPLAYERROR(TEXT("ExtendedFetch...SQLSetStmtOption(Rowset_Size)"),
			TEXT("SQLSetStmtOption Failed"));
		GetErrors(henv, hdbc,hstmt);
	}	

 	/* Check data in all rows of rowset */ 
	if(SQL_SUCCESS != SelectFromTableFetch(lpqt, szColName)){
		DISPLAYERROR(szSQLEXTENDEDFETCH, TEXT("\t\t\tSelect-order by  Failed"));
		goto abortxfetch;
	}
 
	// Need to change this loop if number of rows in table < uwRowSetSize
	for (row=0; row<uwRowSetSize; row++)
	{
		SWORD iResultSetCol=0;
		if (SQL_SUCCESS != (rc = SQLFetch(hstmt))){
			RETCHECK(SQL_SUCCESS, rc, szSQLFETCH);
			DISPLAYERROR(szSQLEXTENDEDFETCH, TEXT("Fetch Failed"));
			goto abortxfetch;
		}
			
		pDataBuf=rgData+row*cTypes;
		for (iTableCol=0; iTableCol<cTypes; iTableCol++)
		{
			/* Ignore columns which aren't bound as they aren't in the result set */
			if((!iTableCol && !fCol0Bound) || rgFields[iTableCol].fAutoUpdate)
				continue;	

			iResultSetCol++;
			rc = SQLGetData(hstmt, iResultSetCol, SQL_C_TCHAR, rgbValue, MAX_STRING_SIZE,
 				&cbValue);
			if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
				RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);

			if(!CheckDataResults(row, iTableCol, &rgFields[iTableCol], pDataBuf,cbValue,rgbValue))
			{
				wsprintf(lpqt->buf, TEXT("Data Check Failed, Row %d, Table Col %d, DataType %d (%s)"),
					row, iTableCol, rgFields[iTableCol].wSQLType, rgFields[iTableCol].szFieldName) ;
				szWrite(lpqt->buf,FALSE);
				rgbValue[MAX_STRING_SIZE-1]=TEXT('\0');
				wsprintf(lpqt->buf, TEXT("Returned Data: (%s)"), rgbValue);
				DISPLAYERROR(TEXT("ExtendedFetch"),lpqt->buf);
				// goto abortxfetch;
			}
		}
	}

abortxfetch:
	FreeStmt(SQL_CLOSE);
	FreeStmt(SQL_UNBIND);
	ReleaseMemory(rgData);
	ReleaseMemory(rgbValue);
} /* TestExtendedFetch() */




/*------------------------------------------------------------------------------
 *      Function:       TestQuickRebind Feature 
 *      Purpose:        To test this specific feature, not the function(s) using it.
 *      Synopsis:
 *      An area large enough for 12 rows of QRDSTRUCTs will be created. There will 
 * be two rows of the result set per Rowset. Rowset 1 should be duplicated
 * in rows 0,1 and 3,4, while Rowset 2 should be duplicated in rows 6,7 and 9,10. 
 * Thus, rows 0 and 3 will contain the first row of the result set, rows 1 and 
 * 4 will contain the second row of the result set, etc.  Rows 2, 5, 8, and
 * 11 should have their preset condition of all zeroes remain unchanged.
 * ----------------------------------------------------------------------------*/

void  PASCAL TestQuickRebind(QTSTRUCT * lpqt, FIELDINFO  *rgFields, UWORD cTypes,
									  DSTRUCT  *lpd)
{
	RETCODE	rc;
	UWORD		row,iCol,iRowset,uwRowsetSize,iRowsetRow,iTableCol;
	UDWORD	udwRowSize;
	SWORD		fSqlType;
	SDWORD	sdwOffset;
	DSTRUCT	*rgData, *pZeroRow;
	DSTRUCT	*pCurrentRowData;
	TCHAR		szQuery[MAX_STRING_SIZE], szColName[SMALLBUFF];
	SDWORD	cbValue;
	TCHAR*	rgbValue=NULL;
	BOOL		fCol0Bound=TRUE;
																		
	udwRowSize = sizeof(DSTRUCT)*cTypes;
						/* cNumResSetCols is set in BuildInsertStmt() */
	uwRowsetSize = 5;/* uwRowsetSize rows per Rowset */

	/* Only col which might not be bound but might not be AutoUpdateable is col 0 */
	if(!qtMakeData(0, 0, &rgFields[0], szQuery))
		fCol0Bound = FALSE;

	/* Allocate an area for QuickRebind to take place */
	if (!(rgData = AllocateMemory(NUM_QUIKREBIND_ROWSETS*(uwRowsetSize+1)*udwRowSize) )){
		DISPLAYERROR(szQUICKREBIND,TEXT("\t\t\tInsufficient Memory Available"));
		return;
	}

	/* Allocate an area for a row of zeroes to place between each Rowset. */
	if (!(pZeroRow = AllocateMemory(udwRowSize) )){
		DISPLAYERROR(szQUICKREBIND,TEXT("\t\t\tInsufficient Memory Available"));
		goto abortQuikRebind;
	}

	/* Allocate an area for test data */
	if (!(rgbValue = AllocateMemory(MAX_STRING_SIZE))){
		DISPLAYERROR(szSQLEXTENDEDFETCH,TEXT("Insufficient Memory Available"));
		goto abortQuikRebind;
	}

	ResetHstmt(&hstmt);

	/* Get column for "order by" clause: */
	wsprintf(szQuery,TEXT("select %s from %s"),lpqt->szColNames, lpqt->szTableName);
	rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
	if((SQL_SUCCESS!=rc) && (SQL_SUCCESS_WITH_INFO!=rc)){
		RETCHECK(SQL_SUCCESS_WITH_INFO, rc, szSQLEXECDIRECT);
		goto abortQuikRebind;
	}
	iCol=0;
	do	{
		iCol++;
		rc=SQLDescribeCol(hstmt, iCol, szColName, (SMALLBUFF*sizeof(TCHAR)), 
			NULL, &fSqlType, NULL, NULL, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLDESCRIBECOL);
	} while(fSqlType!=SQL_CHAR && iCol<=cTypes);

	FreeStmt(SQL_CLOSE);
	if(iCol>=cTypes){
		DISPLAYERROR(szQUICKREBIND, TEXT("\t\t\tSelect-order by  Failed"));
		goto abortQuikRebind;
	}

	/* Set to row-wise binding and set Rowset size to uwRowsetSize:  */
	rc = SQLSetStmtAttr(hstmt,SQL_ATTR_ROW_BIND_TYPE,(PTR)udwRowSize,SQL_IS_INTEGER);
	if (SQL_SUCCESS != rc){
		_tcscpy(lpqt->buf,TEXT("\t\t\tQuick Rebind FAILED...SQLSetDescField(Bind_Type)"));
		szWrite(lpqt->buf, TRUE);
		goto abortQuikRebind;
	}
	rc = SQLSetStmtAttr(hstmt,SQL_ATTR_ROW_ARRAY_SIZE,(PTR)uwRowsetSize,SQL_IS_INTEGER);
	if (SQL_SUCCESS != rc){
			DISPLAYERROR(szQUICKREBIND,TEXT("\t\t\tSetStmtAttr(Rowset Size)"));
		goto abortQuikRebind;
	}		

	/* Define area storing Quikrebind offset value: */
	rc = SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_OFFSET_PTR, &sdwOffset, SQL_IS_POINTER);
	if (SQL_SUCCESS != rc){
		if(FindError(SQL_HANDLE_STMT,szHYC00)){
			_tcscpy(lpqt->buf,TEXT("\t\t\tQuickRebind Not Supported"));
			szWrite(lpqt->buf, TRUE);
			goto abortQuikRebind;
		}
		_tcscpy(lpqt->buf,TEXT("\t\t\tQuick Rebind FAILED...QuickRebind Not Functional"));
		szWrite(lpqt->buf, TRUE);
		goto abortQuikRebind;
	}

	if(SQL_SUCCESS != SelectFromTableFetch(lpqt, szColName)){
		DISPLAYERROR(szQUICKREBIND, TEXT("\t\t\tSelect-order by  Failed"));
		goto abortQuikRebind;
	}
 
	if (!BindFetchColumns(lpqt, rgFields, cTypes, rgData)){
		DISPLAYERROR(szQUICKREBIND,szSQLBINDCOL);
		goto abortQuikRebind;
	}

	/* Test quick rebind feature with two pairs of Rowsets, all *
	 * rowsets separated by a row of zeroes:                    */
	for (iRowset=0; iRowset<=1; iRowset++)
	{
		if(iRowset)
			if(SQL_SUCCESS != SelectFromTableFetch(lpqt, szColName)){
				DISPLAYERROR(szQUICKREBIND, TEXT("\t\t\tSelect-order by  Failed"));
				goto abortQuikRebind;
			}
 
		/* Set offset value (to 0 or 1  * uwRowsetSize * udwRowSize) for 1st rowset */
		sdwOffset = iRowset*((1+uwRowsetSize)*udwRowSize);

		/* Fetch rowset into desired area */
		rc = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 1);
		if (SQL_SUCCESS != rc){
			ERRSHANDLE(SQL_HANDLE_STMT, hstmt, SQL_SUCCESS, rc, szSQLFETCHSCROLL);
			DISPLAYERROR(szQUICKREBIND,TEXT("Fetch Failed"));
			goto abortQuikRebind;
		}                                                                                                                                                                
																
		/* Set offset value (to 2 or 3 * uwRowsetSize * udwRowSize) for 2nd rowset */
		sdwOffset = (iRowset+2)*(1+uwRowsetSize)*udwRowSize;

		rc = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 1);
		if (SQL_SUCCESS != rc){
			ERRSHANDLE(SQL_HANDLE_STMT, hstmt, SQL_SUCCESS, rc, szSQLFETCHSCROLL);
			DISPLAYERROR(szQUICKREBIND,TEXT("Fetch Failed"));
			goto abortQuikRebind;
		}
		FreeStmt(SQL_CLOSE);
	}
	
	rc = SQLFreeStmt(hstmt, SQL_UNBIND);
	RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	rc = SQLSetStmtAttr(hstmt,SQL_ATTR_ROW_ARRAY_SIZE,(PTR)1,SQL_IS_INTEGER);
	if (SQL_SUCCESS != rc){
			DISPLAYERROR(szQUICKREBIND,TEXT("\t\t\tSetStmtAttr(Rowset Size)"));
		goto abortQuikRebind;
	}

	/* Check stored values: */
	for (iRowset=0; iRowset<=1; iRowset++)
	{
		if(SQL_SUCCESS != SelectFromTableFetch(lpqt, szColName)){
			DISPLAYERROR(szQUICKREBIND, TEXT("\t\t\tSelect-order by  Failed"));
			goto abortQuikRebind;
		}
 
		/* First Rowset starts either in Allocated Row 0 or 3 */
		iRowsetRow= iRowset*(1+uwRowsetSize);  
		//for (row=0; row<NUM_QUIKREBIND_ROWSETS  ;row++,iRowsetRow++)
		for (row=0; row<(uwRowsetSize*2)  ;row++,iRowsetRow++)
		{
			UWORD iResultSetCol=0;
			if(row==uwRowsetSize)     
				iRowsetRow+= 2+uwRowsetSize; /* Jump to 2nd Rowset */

			/* Don't check data in "zero" row, 	*
			 * the spacer row between rowsets:	*/
			if(iRowsetRow%(1+uwRowsetSize) == uwRowsetSize)
				continue;

			/* Fetch next rowset */
			rc = SQLFetch(hstmt);
			if (SQL_SUCCESS != rc){
				ERRSHANDLE(SQL_HANDLE_STMT, hstmt, SQL_SUCCESS, rc, szSQLFETCH);
				DISPLAYERROR(szQUICKREBIND,TEXT("Fetch Failed"));
				goto abortQuikRebind;
			}                      
		
			pCurrentRowData = rgData+iRowsetRow*cTypes;
			for(iTableCol=0; iTableCol<cTypes; iTableCol++)
			{
				/* Ignore columns which aren't bound as they aren't in the result set */
				if((!iTableCol && !fCol0Bound) || rgFields[iTableCol].fAutoUpdate)
					continue;	

				iResultSetCol++;
				rc = SQLGetData(hstmt, iResultSetCol, SQL_C_TCHAR, rgbValue, MAX_STRING_SIZE,
					&cbValue);
				if(rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
					RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);

				if(!CheckDataResults(row, iTableCol, &rgFields[iTableCol], pCurrentRowData,cbValue,rgbValue))
				{
					wsprintf(lpqt->buf, TEXT("Data Check Failed, Row %d, Table Col %d, DataType %d (%s)"),
						row, iTableCol, rgFields[iTableCol].wSQLType, rgFields[iTableCol].szFieldName) ;
					szWrite(lpqt->buf,FALSE);
					rgbValue[MAX_STRING_SIZE-1]=TEXT('\0');
					wsprintf(lpqt->buf, TEXT("Returned Data: (%s)"), rgbValue);
					DISPLAYERROR(szQUICKREBIND,lpqt->buf);
					goto abortQuikRebind; 
				}
			}/* end for(iTableCol) */
		} /* end for(row)			  */
		FreeStmt(SQL_CLOSE);
	} /* end for (iRowset)  */

	/* Check Unused memory areas:    */
	for (iRowsetRow=uwRowsetSize; iRowsetRow<NUM_QUIKREBIND_ROWSETS*(uwRowsetSize+1);  )
	{
		pCurrentRowData = rgData+iRowsetRow*cTypes;
		if(memcmp(pCurrentRowData, pZeroRow, udwRowSize))
			DISPLAYERROR(szQUICKREBIND,
					TEXT("Unused memory areas altered after Quick Rebind."));
		iRowsetRow+=(uwRowsetSize+1);
	}                                                        
							  

abortQuikRebind:
	ResetHstmt(&hstmt);
	if (rgbValue)                             
		ReleaseMemory(rgbValue);
	if (pZeroRow)                             
		ReleaseMemory(pZeroRow);
	ReleaseMemory(rgData);

} /* TestQuickRebind() */

//-----------------------------------------------------------------------
//      Function:               TestSQLForeignKeys
//-----------------------------------------------------------------------

void  PASCAL TestSQLForeignKeys(QTSTRUCT  *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	if (!Supported(SQL_API_SQLFOREIGNKEYS))
		{
		rc = SQLForeignKeys(hstmt, NULL, 0, NULL, 0, lpqt->szTableName, 
			SQL_NTS, NULL, 0, NULL, 0, NULL, 0);

		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLFOREIGNKEYS, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLFOREIGNKEYS);
		}
	else
		{
		rc = SQLForeignKeys(hstmt, NULL, 0, NULL, 0, lpqt->szTableName,
			SQL_NTS, NULL, 0, NULL, 0, NULL, 0);

		RETCHECK(SQL_SUCCESS, rc,szSQLFOREIGNKEYS);

		while(rc == SQL_SUCCESS) 
			rc = SQLFetch(hstmt);

		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		FreeStmt(SQL_CLOSE);

		}

} //TestSQLForeignKeys()


//-----------------------------------------------------------------------
//      Function:               TestSQLBrowseConnect
//-----------------------------------------------------------------------

void  PASCAL TestSQLBrowseConnect(lpSERVERINFO lpSI)
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		cMaxConnections=0;
	TCHAR		szBCString[40];
	TCHAR		szDSN[40];
	HDBC		hdbcb=NULL;

	AllocHdbc(&hdbcb);

	rc = SQLGetInfo(hdbc, SQL_ACTIVE_CONNECTIONS, &cMaxConnections, sizeof(int), NULL);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

	if(cMaxConnections != 1) 
		{
		lstrcpy(szBCString,TEXT("DSN="));
		lstrcat(szBCString, lpSI->szValidServer0);
		
		if(lpSI->szValidServer0[0] == 0)
			{
			rc = SQLGetInfo(hdbc, SQL_DATA_SOURCE_NAME, &szDSN, 40, NULL);
			lstrcat(szBCString, szDSN);
			}

		if(!Supported(SQL_API_SQLBROWSECONNECT))
			{
			HDBC thdbc=NULL;

			rc = SQLBrowseConnect(hdbcb, szBCString, SQL_NTS, NULL, 0, NULL);
			thdbc = hdbc;
			hdbc = hdbcb;
			if(!FindError(SQL_HANDLE_DBC,szIM001))
				DISPLAYERROR(szSQLBROWSECONNECT, szNotSupported);
			RETCHECK(SQL_ERROR, rc,szSQLBROWSECONNECT);
			hdbc = thdbc;

			rc = SQLFreeConnect(hdbcb);
			RETCHECK(SQL_SUCCESS, rc,szSQLFREECONNECT);
		
			}
		else
			{
			rc = SQLBrowseConnect(hdbcb, szBCString, SQL_NTS, NULL, 0, NULL);
			RETCHECK(SQL_NEED_DATA, rc,szSQLBROWSECONNECT);

			rc = SQLDisconnect(hdbcb);
			RETCHECK(SQL_SUCCESS, rc,szSQLDISCONNECT);
			rc = SQLFreeConnect(hdbcb);
			RETCHECK(SQL_SUCCESS, rc,szSQLFREECONNECT);
			}
		}

} //TestSQLBrowseConnect()


//-----------------------------------------------------------------------
//      Function:               TestSQLDataSources
//-----------------------------------------------------------------------

void  PASCAL TestSQLDataSources()
{
	RETCODE rc=SQL_SUCCESS;

	if (!Supported( SQL_API_SQLDATASOURCES))
		{
		rc = SQLDataSources(henv, SQL_FETCH_FIRST, NULL, 0, NULL, NULL, 0, NULL);
	
		if(!FindError(SQL_HANDLE_ENV,szIM001))
			DISPLAYERROR(TEXT("SQLDataSources"), szNotSupported);
	
		RETCHECK(SQL_ERROR, rc,TEXT("SQLDataSources"));
		} 
	else 
		{
		rc = SQLDataSources(henv, SQL_FETCH_FIRST, NULL, 0, NULL, NULL, 0, NULL);
		RETCHECK(SQL_SUCCESS, rc,TEXT("SQLDataSources"));
		}

} //TestSQLDataSources()


//-----------------------------------------------------------------------
//      Function:               TestSQLDataSources
//-----------------------------------------------------------------------

void  PASCAL TestSQLDrivers()
{
	RETCODE rc=SQL_SUCCESS;

	if(!Supported( SQL_API_SQLDRIVERS)) 
		{
		rc = SQLDrivers(henv, SQL_FETCH_FIRST, NULL, 0, NULL, NULL, 0, NULL);
		if(!FindError(SQL_HANDLE_ENV,szIM001))
			DISPLAYERROR(TEXT("SQLDrivers"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLDataSources"));
		}
	else
		{
		rc = SQLDrivers(henv, SQL_FETCH_FIRST, NULL, 0, NULL, NULL, 0, NULL);
		if(rc != SQL_SUCCESS)
			RETCHECK(SQL_SUCCESS_WITH_INFO, rc,TEXT("SQLDrivers"));
		}

} //TestSQLDrivers()


//-----------------------------------------------------------------------
//      Function:               TestSQLMoreResults
//-----------------------------------------------------------------------

void  PASCAL TestSQLMoreResults(QTSTRUCT  *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	if(!Supported( SQL_API_SQLMORERESULTS)) 
		{
		SelectFromTable(lpqt);

		rc = SQLMoreResults(hstmt);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(TEXT("SQLMoreResults"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLMoreResults"));
		}
	else
		{
		SelectFromTable(lpqt);

		rc = SQLMoreResults(hstmt);
		RETCHECK(SQL_NO_DATA_FOUND, rc,TEXT("SQLMoreResults"));
		}

	FreeStmt(SQL_CLOSE);

} //TestSQLMoreResults()


//-----------------------------------------------------------------------
//      Function:               TestSQLMoreResults
//-----------------------------------------------------------------------

void  PASCAL TestSQLNativeSQL(QTSTRUCT  *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szQuery[XLARGEBUFF];
	
	wsprintf(szQuery,TEXT("select * from %s were 0 > 1"),lpqt->szTableName);

	if(!Supported( SQL_API_SQLNATIVESQL))
		{
		rc = SQLNativeSql(hdbc, szQuery, SQL_NTS, NULL, 0, NULL);
		if(!FindError(SQL_HANDLE_DBC,szIM001))
			DISPLAYERROR(TEXT("SQLNativeSql"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLNativeSql"));
		}
	else 
		{
		rc = SQLNativeSql(hdbc, szQuery, SQL_NTS, NULL, 0, NULL);
		RETCHECK(SQL_SUCCESS, rc,TEXT("SQLNativeSql"));
		}

	FreeStmt(SQL_CLOSE);
	
} //TestSQLNativeSQL()


//-----------------------------------------------------------------------
//      Function:               TestSQLDescribeParam
//-----------------------------------------------------------------------

void  PASCAL TestSQLDescribeParam(QTSTRUCT  *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	rc = SQLPrepare(hstmt, lpqt->szParamQuery, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);

	if(!Supported( SQL_API_SQLDESCRIBEPARAM)) 
		{
		rc = SQLPrepare(hstmt, lpqt->szParamQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);
		rc = SQLDescribeParam(hstmt, 1, NULL, NULL, NULL, NULL);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLDESCRIBEPARAM, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLDESCRIBEPARAM);
		}
	else
		{
		rc = SQLPrepare(hstmt, lpqt->szParamQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);
		rc = SQLDescribeParam(hstmt, 1, NULL, NULL, NULL, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLDESCRIBEPARAM);
		}

		FreeStmt(SQL_CLOSE);

} //TestSQLDescribeParam()



//-----------------------------------------------------------------------
//      Function:               TestSQLNumParams
//-----------------------------------------------------------------------

void  PASCAL TestSQLNumParams(QTSTRUCT  *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	rc = SQLPrepare(hstmt, lpqt->szParamQuery, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);

	if(!Supported( SQL_API_SQLNUMPARAMS)) 
		{
		rc = SQLNumParams(hstmt, NULL);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLNUMPARAMS, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLNUMPARAMS);
		}
	else
		{
		rc = SQLNumParams(hstmt, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLNUMPARAMS);
		}

	FreeStmt(SQL_CLOSE);

} //TestSQLNumParams()





//-----------------------------------------------------------------------
//      Function:               TestSQLParamOptions
//-----------------------------------------------------------------------

void  PASCAL TestSQLParamOptions(QTSTRUCT *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	rc = SQLPrepare(hstmt, lpqt->szParamQuery, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);

	if(!Supported( SQL_API_SQLPARAMOPTIONS)) 
		{
		rc = SQLParamOptions(hstmt, 1, NULL);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLPARAMOPTIONS, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLPARAMOPTIONS);
		}
	else
		{
		rc = SQLParamOptions(hstmt, 1, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLPARAMOPTIONS);
		}

	FreeStmt(SQL_CLOSE);

} //TestSQLParamOptions()




//-----------------------------------------------------------------------
//      Function:               TestSQLPrimaryKeys
//-----------------------------------------------------------------------

void  PASCAL TestSQLPrimaryKeys(QTSTRUCT *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	if (!Supported( SQL_API_SQLPRIMARYKEYS))
		{
		rc = SQLPrimaryKeys(hstmt, NULL, 0, NULL, 0, lpqt->szTableName, SQL_NTS);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLPRIMARYKEYS, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLPRIMARYKEYS);
		}
	else
		{
		rc = SQLPrimaryKeys(hstmt, NULL, 0, NULL, 0, lpqt->szTableName, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLPRIMARYKEYS);
		while(rc == SQL_SUCCESS) 
			rc = SQLFetch(hstmt);

		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		FreeStmt(SQL_CLOSE);

		}

} //TestSQLPrimaryKeys()



//-----------------------------------------------------------------------
//      Function:               TestSQLProcedureColumns
//-----------------------------------------------------------------------

void  PASCAL TestSQLProcedureColumns(QTSTRUCT  *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	if(!Supported( SQL_API_SQLPROCEDURECOLUMNS)) 
		{
		rc = SQLProcedureColumns(hstmt, NULL, 0, NULL, 0, NULL, 0, NULL, 0);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(TEXT("SQLProcedureColumns"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLProcedureColumns"));
		}
	else 
		{
		rc = SQLProcedureColumns(hstmt, NULL, 0, NULL, 0, NULL, 0, NULL, 0);
		RETCHECK(SQL_SUCCESS, rc,TEXT("SQLProcedureColumns"));
		while(rc == SQL_SUCCESS)
			rc = SQLFetch(hstmt);

		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		FreeStmt(SQL_CLOSE);
		}

} //TestSQLProcedureColumns()



//-----------------------------------------------------------------------
//      Function:               TestSQLProcedures
//-----------------------------------------------------------------------

void  PASCAL TestSQLProcedures()
{
	RETCODE rc=SQL_SUCCESS;

	if(!Supported( SQL_API_SQLPROCEDURES)) 
		{
		rc = SQLProcedures(hstmt, NULL, 0, NULL, 0, NULL, 0);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(TEXT("SQLProcedures"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLProcedures"));
		}
	else
		{
		rc = SQLProcedures(hstmt, NULL, 0, NULL, 0, NULL, 0);
		RETCHECK(SQL_SUCCESS, rc,TEXT("SQLProcedures"));
		while(rc == SQL_SUCCESS)
			rc = SQLFetch(hstmt);
		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		FreeStmt(SQL_CLOSE);
		}

} //TestSQLProcedures()


//-----------------------------------------------------------------------
//      Function:               TestSQLTablePrivileges
//-----------------------------------------------------------------------

void  PASCAL TestSQLTablePrivileges()
{
	RETCODE rc=SQL_SUCCESS;

	if(!Supported( SQL_API_SQLTABLEPRIVILEGES)) 
		{
		rc = SQLTablePrivileges(hstmt, NULL, 0, NULL, 0, NULL, 0);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(TEXT("SQLTablePrivileges"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLTablePrivileges"));
		}
	else
		{
		rc = SQLTablePrivileges(hstmt, NULL, 0, NULL, 0, NULL, 0);
		RETCHECK(SQL_SUCCESS, rc,TEXT("SQLTablePrivileges"));
		while(rc == SQL_SUCCESS) 
			rc = SQLFetch(hstmt);

		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		FreeStmt(SQL_CLOSE);
		}

} //TestSQLTablePrivileges()



//-----------------------------------------------------------------------
//      Function:               TestSQLColumnPrivileges
//-----------------------------------------------------------------------

void  PASCAL TestSQLColumnPrivileges(QTSTRUCT  *lpqt)
{
	RETCODE rc=SQL_SUCCESS;

	if(!Supported( SQL_API_SQLCOLUMNPRIVILEGES)) 
		{
		rc = SQLColumnPrivileges(hstmt, NULL, 0, NULL, 0, lpqt->szTableName, SQL_NTS,
			NULL, 0);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(TEXT("SQLColummPrivileges"), szNotSupported);
		RETCHECK(SQL_ERROR, rc,TEXT("SQLColumnPrivileges"));
		} 
	else
		{
		rc = SQLColumnPrivileges(hstmt, NULL, 0, NULL, 0, lpqt->szTableName, SQL_NTS,
			NULL, 0);
		RETCHECK(SQL_SUCCESS, rc,TEXT("SQLColumnPrivileges"));
		while(rc == SQL_SUCCESS)
			rc = SQLFetch(hstmt);
	
		RETCHECK(SQL_NO_DATA_FOUND, rc,szSQLFETCH);

		FreeStmt(SQL_CLOSE);
		}

} // TestSQLColumnPrivileges()


//-----------------------------------------------------------------------
//      Function:               TestSQLSetScrollOptions
//-----------------------------------------------------------------------

void  PASCAL TestSQLSetScrollOptions()
{
	RETCODE	rc=SQL_SUCCESS;
	UWORD		i,
				j;
	UDWORD	fSupportedOpt;
	UDWORD	fSupportedCon;
	TCHAR		szState[100]=TEXT(""),
				szErrMsg[XLARGEBUFF]=TEXT("");

	FreeStmt(SQL_CLOSE);

	if(!Supported( SQL_API_SQLSETSCROLLOPTIONS)) 
		{
		rc = SQLSetScrollOptions(hstmt, SQL_CONCUR_READ_ONLY, SQL_SCROLL_FORWARD_ONLY,
			1);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLSETSCROLLOPTIONS, szNotSupported);
		RETCHECK(SQL_ERROR, rc,szSQLSETSCROLLOPTIONS);
		} 
	else
		{
		rc = SQLGetInfo(hdbc, SQL_SCROLL_CONCURRENCY, &fSupportedCon, 4, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);
		rc = SQLGetInfo(hdbc, SQL_SCROLL_OPTIONS, &fSupportedOpt, 4, NULL);
		RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

		for(i = 0; i < sizeof(OptionList) / sizeof(SUPPORTOPTINFO); i ++) 
			{
			for(j = 0; j < sizeof(ConcurList) / sizeof(SUPPORTCONCURINFO); j++) 
				{
				if(fSupportedOpt & OptionList[i].Support && fSupportedCon & ConcurList[j].Support) 
					{
					if(!((ConcurList[j].Option == SQL_CONCUR_VALUES) && ((lpSI->vCursorLib == 
							SQL_CUR_USE_IF_NEEDED) || (lpSI->vCursorLib == SQL_CUR_USE_ODBC))))
						{
						rc = SQLSetScrollOptions(hstmt, ConcurList[j].Option,OptionList[i].Option, 1);
						RETCHECK(SQL_SUCCESS, rc,szSQLSETSCROLLOPTIONS);
						}

					}
				}
			}
		}

	FreeStmt(SQL_CLOSE);

} //TestSQLSetScrollOptions()


//-----------------------------------------------------------------------------
//	Function:  TestConnectAttr
//-----------------------------------------------------------------------------

VOID PASCAL TestConnectAttr(HDBC hdbc,SDWORD fAttribute, UDWORD rgbValue,LPTSTR lpAttr,BOOL fReadOnlyAttr)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szBuff[LARGEBUFF]=TEXT("");
	UDWORD	pvParam=0;
	RETCODE	rcExp=fReadOnlyAttr ? SQL_ERROR : SQL_SUCCESS;

	rc = SQLSetConnectAttr(hdbc,fAttribute,(PTR)rgbValue,sizeof(rgbValue));

	if(!FindError(SQL_HANDLE_DBC,szHYC00))
	{

		RETCHECK(rcExp,rc,szSQLSETCONNECTATTR);
	
		rc = SQLGetConnectAttr(hdbc,fAttribute,&pvParam,sizeof(pvParam),NULL);

		if(!FindError(SQL_HANDLE_DBC,szHYC00))
		{
			RETCHECK(SQL_SUCCESS,rc,szSQLGETCONNECTATTR);

			if(!fReadOnlyAttr && (pvParam != rgbValue))
			{
				wsprintf(szBuff,TEXT("%s returned incorrect value"),lpAttr);
				DISPLAYERROR(szSQLGETCONNECTATTR,szBuff);
			}
		}
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETCONNECTATTR);
	}
	else
		RETCHECK(SQL_ERROR,rc,szSQLSETCONNECTATTR); 

} //TestConnectAttr()


//-----------------------------------------------------------------------------
//	Function:  TestSQLSetConnectAttr
//  		   This function tests both SQLSetConnectAttr and SQLGetConnectAttr
//-----------------------------------------------------------------------------

void  PASCAL TestSQLSetConnectAttr()
{
	RETCODE rc = SQL_SUCCESS;
	UDWORD	pvParam;
	UWORD	rgbValue;
	BOOL	fSupportSetConnectAttr = TRUE;
	BOOL	fSupportGetConnectAttr = TRUE;

	//make sure these APIs are supported before testing
	if(!Supported(SQL_API_SQLSETCONNECTATTR))
		{
		rgbValue = SQL_MODE_READ_WRITE;
		fSupportSetConnectAttr = FALSE;
		rc = SQLSetConnectAttr(hdbc,SQL_ACCESS_MODE,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_DBC,szIM001))
			DISPLAYERROR(szSQLSETCONNECTATTR,TEXT("did not return Not supported message"));
		RETCHECK(SQL_ERROR,rc,szSQLSETCONNECTATTR);
		}

	if(!Supported(SQL_API_SQLGETCONNECTATTR))
		{
		fSupportGetConnectAttr = FALSE;
		rc = SQLGetConnectAttr(hdbc,SQL_ACCESS_MODE,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_DBC,szIM001))
			DISPLAYERROR(szSQLGETCONNECTATTR,TEXT("did not return Not supported message"));
		RETCHECK(SQL_ERROR,rc,szSQLGETCONNECTATTR);
		}

	if(fSupportSetConnectAttr && (!fSupportGetConnectAttr))
		{
		//test SQL_ACCESS_MODE
		rgbValue = SQL_MODE_READ_WRITE;
		rc = SQLSetConnectAttr(hdbc,SQL_ACCESS_MODE,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLSETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLSETCONNECTATTR);
		//test SQL_AUTOCOMMIT		
		rgbValue = SQL_AUTOCOMMIT_ON;
		rc = SQLSetConnectAttr(hdbc,SQL_AUTOCOMMIT,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLSETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLSETCONNECTATTR);
		//test SQL_LOGIN_TIMEOUT
		//the choice of 15 seconds for timeout is arbitrary
		rgbValue = 15;
		rc = SQLSetConnectAttr(hdbc,SQL_LOGIN_TIMEOUT,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLSETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLSETCONNECTATTR);
		}

	if((!fSupportSetConnectAttr) && fSupportGetConnectAttr)
	{
		//test SQL_ACCESS_MODE
		rc = SQLGetConnectAttr(hdbc,SQL_ACCESS_MODE,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETCONNECTATTR);
		//test SQL_AUTOCOMMIT		
		rc = SQLGetConnectAttr(hdbc,SQL_AUTOCOMMIT,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETCONNECTATTR);
		//test SQL_LOGIN_TIMEOUT
		rc = SQLGetConnectAttr(hdbc,SQL_LOGIN_TIMEOUT,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETCONNECTATTR);
		//SQL_ATTR_AUTO_IPD is a read-only attribute		
		rc = SQLGetConnectAttr(hdbc,SQL_ATTR_AUTO_IPD,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_DBC,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETCONNECTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETCONNECTATTR);
	}

	if(fSupportSetConnectAttr && fSupportGetConnectAttr)
	{
		
		//test SQL_ACCESS_MODE
		TestConnectAttr(hdbc,SQL_ACCESS_MODE,SQL_MODE_READ_WRITE,TEXT("SQL_ACCESS_MODE"),FALSE);
		
		//test SQL_AUTOCOMMIT		
		TestConnectAttr(hdbc,SQL_AUTOCOMMIT,SQL_AUTOCOMMIT_ON,TEXT("SQL_AUTOCOMMIT"),FALSE);
			
		//test SQL_LOGIN_TIMEOUT
		//the choice of 15 seconds for timeout is arbitrary
		TestConnectAttr(hdbc,SQL_LOGIN_TIMEOUT,15,TEXT("SQL_LOGIN_TIMEOUT"),FALSE);

		//SQL_ATTR_AUTO_IPD is a read-only attribute		
		TestConnectAttr(hdbc,SQL_ATTR_AUTO_IPD,15,TEXT("SQL_ATTR_AUTO_IPD"),TRUE);
	}

} //TestSQLSetConnectAttr()



//-----------------------------------------------------------------------------
//	Function:  TestSQLSetStmtAttr
//  		   This function tests both SQLSetStmtAttr and SQLGetStmtAttr
//-----------------------------------------------------------------------------

void  PASCAL TestSQLSetStmtAttr()
{
	RETCODE rc = SQL_SUCCESS, rc2= SQL_SUCCESS;
	UDWORD	pvParam;
	UWORD	rgbValue;
	BOOL	fSupportSetStmtAttr = TRUE;
	BOOL	fSupportGetStmtAttr = TRUE;

	//make sure these APIs are supported before testing
	if(!Supported(SQL_API_SQLSETSTMTATTR))
		{
		//the choice of 300 for SQL_MAX_LENGTH is arbitrary
		rgbValue = 300;
		fSupportSetStmtAttr = FALSE;
		rc = SQLSetStmtAttr(hstmt,SQL_MAX_LENGTH,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLSETSTMTATTR,TEXT("did not return Not supported message"));
		RETCHECK(SQL_ERROR,rc,szSQLSETSTMTATTR);
		}

	if(!Supported(SQL_API_SQLGETSTMTATTR))
		{
		fSupportGetStmtAttr = FALSE;
		rc = SQLGetStmtAttr(hstmt,SQL_MAX_LENGTH,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLGETSTMTATTR,TEXT("did not return Not supported message"));
		RETCHECK(SQL_ERROR,rc,szSQLGETSTMTATTR);
		}

	if(fSupportSetStmtAttr && (!fSupportGetStmtAttr))
		{
		//test SQL_MAX_LENGTH
		rgbValue = 300;
		rc = SQLSetStmtAttr(hstmt,SQL_MAX_LENGTH,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLSETSTMTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLSETSTMTATTR);
		//test SQL_ATTR_METADATA_ID -- new in 3.0
		rgbValue = SQL_FALSE;
		rc = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,&rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLSETSTMTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLSETSTMTATTR);
		}

	if((!fSupportSetStmtAttr) && fSupportGetStmtAttr)
		{
		//test SQL_MAX_LENGTH
		rc = SQLGetStmtAttr(hstmt,SQL_MAX_LENGTH,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETSTMTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETSTMTATTR);
		//test SQL_ATTR_METADATA_ID -- new in 3.0
		rc = SQLGetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,&pvParam,sizeof(pvParam),NULL);
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETSTMTATTR);
		else
			RETCHECK(SQL_ERROR,rc,szSQLGETSTMTATTR);
		}
	
	if(fSupportSetStmtAttr && fSupportGetStmtAttr)
		{
		
		//test SQL_MAX_LENGTH
		rgbValue = 300;
		rc = SQLSetStmtAttr(hstmt,SQL_MAX_LENGTH,(PTR)rgbValue,sizeof(rgbValue));
		if(!FindError(SQL_HANDLE_STMT,szHYC00))
			{
			RETCHECK(SQL_SUCCESS,rc,szSQLSETSTMTATTR);
			rc = SQLGetStmtAttr(hstmt,SQL_MAX_LENGTH,&pvParam,sizeof(pvParam),NULL);
			if(!FindError(SQL_HANDLE_STMT,szHYC00))
				{
				RETCHECK(SQL_SUCCESS,rc,szSQLGETSTMTATTR);
				if(pvParam != 300)
					DISPLAYERROR(szSQLGETSTMTATTR,TEXT("SQL_MAX_LENGTH returned incorrect value"));
				}
			else
				RETCHECK(SQL_ERROR,rc,szSQLGETSTMTATTR);
			}
		else
			RETCHECK(SQL_ERROR,rc,szSQLSETSTMTATTR);
		
	
		//test SQL_ATTR_METADATA_ID -- new in 3.0
		rgbValue = SQL_FALSE;
		rc = SQLSetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,(PTR)rgbValue,sizeof(rgbValue));
		if (!FindError(SQL_HANDLE_STMT,szHYC00) && !FindError(SQL_HANDLE_STMT,szHY092))
			RETCHECK(SQL_SUCCESS,rc,szSQLSETSTMTATTR);

		rc2 = SQLGetStmtAttr(hstmt,SQL_ATTR_METADATA_ID,&pvParam,sizeof(pvParam),NULL);
		if (!FindError(SQL_HANDLE_STMT,szHYC00) && !FindError(SQL_HANDLE_STMT,szHY092))
			RETCHECK(SQL_SUCCESS,rc,szSQLGETSTMTATTR);

		if (RC_SUCCESSFUL(rc) && RC_SUCCESSFUL(rc2) && pvParam != SQL_FALSE)
			DISPLAYERROR(szSQLGETSTMTATTR,TEXT("SQL_ATTR_METADATA_ID returned incorrect value"));
	}

} //TestSQLSetStmtAttr()

//--------------------------------------------------------------------------------
// FUNCTION:	TestOneThread
// PURPOSE:		This function allocates the statement handle, performs simple 
//				queries and deallocates the statement handle.  This function is called
//				by testthreading.
//--------------------------------------------------------------------------------
static int TestOneThread(THREAD_STRUCT *ptArg)
{
	HENV		henv0 = ptArg->henv;
	HDBC		hdbc0 = ptArg->hdbc;
	HSTMT		hstmt0 = NULL;
	//RETCODE	rc=SQL_SUCCESS;

	/* allocate new statment handle */
	if (RC_NOTSUCCESSFUL(SQLAllocHandle(SQL_HANDLE_STMT,hdbc0, &hstmt0)))
		return(FALSE);

	/* perform some simple catalog functions */
	if (RC_NOTSUCCESSFUL(SQLStatistics(hstmt0,NULL,SQL_NTS,NULL,SQL_NTS,NULL,SQL_NTS,SQL_INDEX_ALL,SQL_QUICK)))
		return(FALSE);

	if (RC_NOTSUCCESSFUL(SQLCloseCursor(hstmt0)))
		return(FALSE);

	/* Get some data */
	GetSomeData(hstmt0, ptArg->szTableName, TRUE,ptArg->rgFieldInfo);

	if (RC_NOTSUCCESSFUL(SQLGetTypeInfo(hstmt0,SQL_CHAR)))
		return(FALSE);

	// Cleanup
	if (RC_NOTSUCCESSFUL(SQLFreeHandle(SQL_HANDLE_STMT,hstmt0)))
		return(FALSE);

	return(TRUE);

} //end of TestOneThread

//--------------------------------------------------------------------------------
// FUNCTION:	ThreadLoop
// PURPOSE:		This is the main loop for the threads, and it's called by 
//				CreateThread() API.
//--------------------------------------------------------------------------------
DWORD WINAPI ThreadLoop(void *pArg)
{

	THREAD_STRUCT *ptArg = (THREAD_STRUCT *)pArg;
	int i;
	RETCODE	rc;

	for(i=0; i< NUM_THREAD; i++)
		TestOneThread(ptArg);

	// free connection handle for each thread
	rc=SQLDisconnect(ptArg->hdbc);
    RETCHECK(SQL_SUCCESS,rc,szSQLDISCONNECT);
	rc=SQLFreeHandle(SQL_HANDLE_DBC,ptArg->hdbc);
	RETCHECK(SQL_SUCCESS,rc,szSQLFREEHANDLE);

   	return(0);
} //end of ThreadLoop


//-------------------------------------------------------------------------------
// FUNCTION:	TestThreading
// PURPOSE:		This function tests the multi-threading capabilities of the 
//				driver by creating multiple threads that connect to the same data
// 				source.  Once connected, each thread performs simple queries to 
//				test that the driver handles these queries successfully.
//				This function is to be called inside AutoTestFunc() in QuikTest.
//--------------------------------------------------------------------------------
void TestThreading(lpSERVERINFO lpSI,QTSTRUCT  *lpqt,FIELDINFO *rgFieldInfo)
{
	RETCODE rc=SQL_SUCCESS;
   THREAD_STRUCT *pArg;
   HANDLE hThread[NUM_THREAD];
	DWORD dwThreadId;
	UWORD i;
	HENV	henv1;
	HDBC	hdbc1;
	

	// allocate memory for the threads
	pArg = (THREAD_STRUCT *)AllocateMemory((NUM_THREAD) * sizeof(THREAD_STRUCT));

	if(!pArg)
	{
		szWrite(TEXT("\t\t\tMultiThreading Test interrupted due to error in memory allocation"), TRUE);
		return;
	}
	
	// only one environment handle will be needed for all threads
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv1);
	RETCHECK(SQL_SUCCESS, rc,szSQLALLOCHANDLE);

	// Set environment attribute, or we can't allocate connection
	rc = SQLSetEnvAttr(henv1, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,
		SQL_IS_UINTEGER);
	RETCHECK(SQL_SUCCESS, rc,szSQLSETENVATTR);

	for (i=0; i < NUM_THREAD; i++ ) 
	{
		// allocate connection handle for each thread
		rc=SQLAllocHandle(SQL_HANDLE_DBC,henv1, &hdbc1);
		RETCHECK(SQL_SUCCESS, rc,szSQLALLOCHANDLE);

		// create string to be used in connecting
		wsprintf(lpqt->sz,TEXT("dsn=%s;uid=%s;pwd=%s;"),
		lpSI->szValidServer0,
		lpSI->szValidLogin0,
		lpSI->szValidPassword0);

		SQLDriverConnect(hdbc1, lpSI->hwnd, lpqt->sz,
		SQL_NTS, lpqt->buf, MAX_STRING_SIZE, NULL, SQL_DRIVER_COMPLETE);

		// initialize thread structure
		pArg[i].henv = henv1;
		pArg[i].hdbc = hdbc1;
		lstrcpy(pArg[i].szTableName, lpqt->szTableName);
		pArg[i].rgFieldInfo=rgFieldInfo[0];

		// start thread
		hThread[i]= CreateThread(NULL,
							0,
							ThreadLoop,
							&pArg[i],
							0,
							&dwThreadId);

		if(hThread[i]==0)
		{
			DISPLAYERROR(TEXT("TestThread failed:"),TEXT("cannot create thread"));
			break;
		}
	}

	// wait for thread completion
	WaitForMultipleObjects(NUM_THREAD,hThread,TRUE,INFINITE);

	for(i=0; i<NUM_THREAD; i++ )
    	CloseHandle(hThread[i]);

	SQLFreeHandle(SQL_HANDLE_ENV,henv1);
	if (pArg)
		ReleaseMemory(pArg);
}	//end of TestThreading()


//-----------------------------------------------------------------------
//      Function:               CreateDescRecord
//-----------------------------------------------------------------------
SWORD CreateDescRecord(SQLHDESC hdesc, SQLHSTMT hstmt, UWORD uwDescType)
{
	UDWORD cbColDef;
	SWORD swColCount;
	SQLRETURN rc;
	SWORD fType, fSQLType;
	SWORD ibScale;
	TCHAR rgBuf[100];

	switch(uwDescType) {
		case SQL_ATTR_APP_ROW_DESC:
			rc = SQLSetDescField(hdesc, 1, SQL_DESC_TYPE, (SQLPOINTER)SQL_C_DEFAULT,
				SQL_IS_SMALLINT);
			ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD);
			
			if (SQL_SUCCEEDED(rc))
				return 1;

			rc=SQLBindCol(hstmt, 1, SQL_C_TCHAR, rgBuf, sizeof(rgBuf), NULL);
			RETCHECK(SQL_SUCCESS, rc,szSQLBINDCOL);
			if (SQL_SUCCEEDED(rc))
				return 1;	
			break;
		case SQL_ATTR_IMP_PARAM_DESC:
		case SQL_ATTR_APP_PARAM_DESC:
			// Select statement has already been done by this time
			rc=SQLDescribeCol(hstmt, 1, NULL, 0, NULL, &fSQLType, &cbColDef, 
				&ibScale, NULL);
			RETCHECK(SQL_SUCCESS, rc,szSQLDESCRIBECOL);
			if (!SQL_SUCCEEDED(rc))
				return 0;

			if (SQL_ATTR_APP_PARAM_DESC == uwDescType)
				fType=SQL_C_TCHAR;
			else
				fType=fSQLType;

			rc = SQLSetDescField(hdesc, 1, SQL_DESC_TYPE, (SQLPOINTER)fType,
				SQL_IS_SMALLINT);
			ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD);
			
			if (SQL_SUCCEEDED(rc))
				return 1;

			rc=SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_TCHAR,
				fSQLType, cbColDef, ibScale, rgBuf, sizeof(rgBuf), NULL);
			RETCHECK(SQL_SUCCESS, rc,szSQLDESCRIBECOL);
			if (SQL_SUCCEEDED(rc))
				return 1;
			break;
		case SQL_ATTR_IMP_ROW_DESC:
			// Quiktest has already done the select for us
			// Need to find out how many cols in result set
			rc=SQLNumResultCols(hstmt, &swColCount);
			if (SQL_SUCCEEDED(rc))
				return(swColCount);
			break;
	}
	return 0;
}	//CreateDescRecord

//-----------------------------------------------------------------------
//      Function:               CheckDescOp
//-----------------------------------------------------------------------
void CheckDescOp(SQLHDESC hdesc, SQLRETURN rc, SQLUSMALLINT uwDescIndex,
	SQLSMALLINT swDescRecCount, SQLSMALLINT swDescRec, SQLUSMALLINT iDescField,
	SQLINTEGER swUpdateMode)
{
	TCHAR * pszAPI, szOp[10];
	SQLSMALLINT fValidOp;	// Descriptor types operation is valid for

	if (DESC_UPDATE_MODE_READ == swUpdateMode)
	{
		pszAPI=szSQLGETDESCFIELD;
		lstrcpy(szOp, TEXT("read"));
		fValidOp=rgDescInfo[iDescField].fGettable;
	}
	else
	{
		pszAPI=szSQLSETDESCFIELD;
		lstrcpy(szOp, TEXT("write"));
		fValidOp=rgDescInfo[iDescField].fSettable;
	}

	// If we're reading beyond the last record, expect SQL_NO_DATA.
	if (swDescRec > swDescRecCount && DESC_UPDATE_MODE_READ == swUpdateMode)
	{
		wsprintf(buf,TEXT("%s: Able to %s descriptor field %s in the %s beyond last record."),
				pszAPI, szOp, rgDescInfo[iDescField].szDescFieldName, DescTypes[uwDescIndex].szDescName);
		ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_NO_DATA, rc, buf);
	}
	else
	{
		if (fValidOp & DescTypes[uwDescIndex].uwTypeMask)
		{
			wsprintf(buf,TEXT("%s: Unable to %s descriptor field %s in the %s"),
					pszAPI, szOp, rgDescInfo[iDescField].szDescFieldName, DescTypes[uwDescIndex].szDescName);
			ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, buf);
		}
		else
		{
			wsprintf(buf,TEXT("%s: Able to %s descriptor field %s in the %s"),
					pszAPI, szOp, rgDescInfo[iDescField].szDescFieldName, DescTypes[uwDescIndex].szDescName);
			ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_ERROR, rc, buf);
		}
	}
}

//-----------------------------------------------------------------------
//
// Function: CompareDescField
//
// Compares two fields from the given descriptor, or to rgDescInfo if hdesc2
// is NULL.  uwDescField contains the entry in rgDescInfo for the desired field 
//-----------------------------------------------------------------------

void CompareDescField(SQLHDESC hdesc1, SQLHDESC hdesc2, SQLUSMALLINT uwDescIndex,
	SQLSMALLINT swDescRec, SQLSMALLINT swDescRecCount, SQLUSMALLINT uwDescField,
	TCHAR * pszAPI)
{
	SQLRETURN rc;
 	SQLTCHAR DescBuf2[MAX_DESC_BUF];
	SQLINTEGER cbValue2; 

	// Make sure we've got a valid descriptor handle for hdesc1
	// (hdesc2 is allowed to be NULL)
	if (SQL_NULL_HDESC == hdesc1) {
		wsprintf(buf,TEXT("\t\tCompareDescriptor: hdesc1 handle was null!"));
		DISPLAYERROR(pszAPI, buf);
		return;
	}

	// Read the value from hdesc1
	rc = SQLGetDescField(hdesc1, swDescRec, rgDescInfo[uwDescField].uwDescField,
		&DescBuf, sizeof(DescBuf), &cbValue);

	CheckDescOp(hdesc1, rc, uwDescIndex, swDescRecCount, swDescRec, uwDescField, DESC_UPDATE_MODE_READ);

	cbValue2=rgDescInfo[uwDescField].cbValue;

	// Get the value to compare to
	if (SQL_NULL_HDESC == hdesc2) {

		// Compare to rgDescInfo if it's settable
		if (rgDescInfo[uwDescField].fSettable & DescTypes[uwDescIndex].uwTypeMask) {
			
			// Copy the set value into DescBuf2.  For char fields size is 0
			// (unknown), and the new value is actually the pointer to the start
			// of the string.
			SQLPOINTER pNewvalue = &(rgDescInfo[uwDescField].NewValue);
			
			if (!rgDescInfo[uwDescField].size)
			{
				pNewvalue = (SQLPOINTER)rgDescInfo[uwDescField].NewValue;
				cbValue2	= (lstrlen(pNewvalue)+1) * sizeof(TCHAR); 
			}

			memcpy(&DescBuf2, pNewvalue, cbValue2);
		}
	}
	else {

		// Compare to hdesc2
		rc = SQLGetDescField(hdesc2, swDescRec, rgDescInfo[uwDescField].uwDescField,
			&DescBuf2, sizeof(DescBuf2), &cbValue);

		// Since hdesc2 is an unassociated hdesc, treat it as an ARD
		// (uwDescIndex=0)
		CheckDescOp(hdesc2, rc, 0, swDescRecCount, swDescRec, uwDescField, DESC_UPDATE_MODE_READ);
	}

	// Perform the compare if settable in source desc and settable in
	// target desc (application descriptors) when using hdesc2
	if (rgDescInfo[uwDescField].fSettable & DescTypes[uwDescIndex].uwTypeMask)
	{
		if (!hdesc2 || (rgDescInfo[uwDescField].fSettable & DESC_ARD))
		{
			// IPD field SQL_DESC_TYPE is settable for consitency check, but set
			// value can't be retrieved, so skip compare in this case
			if (SQL_ATTR_IMP_PARAM_DESC != DescTypes[uwDescIndex].uwDescType ||
				SQL_DESC_DATA_PTR != rgDescInfo[uwDescField].uwDescField)
			{
				if (memcmp(DescBuf, DescBuf2, cbValue2)) {
					// Compare error, print message
					wsprintf(buf,TEXT("Compare error in %s field %s"),
						DescTypes[uwDescIndex].szDescName,rgDescInfo[uwDescField].szDescFieldName);
					DISPLAYERROR(pszAPI, buf);
				}
			}
		}
	}
}


//-----------------------------------------------------------------------
//
// Function:  CheckDescriptor
//
// Checks all fields in all records of given descriptor.  If swUpdateMode is
// DESC_UPDATE_MODE_READ then all fields are read, otherwise all updatable
// fields are written.
//-----------------------------------------------------------------------
void CheckDescriptor(SQLHDESC hdesc, SQLINTEGER swUpdateMode, SQLHSTMT hstmt, UWORD uwDescIndex)
{
 	SQLINTEGER cbValue2;
	SQLSMALLINT swDescRec=0, swDescRecCount, swAdditionalRecs=0;
	SQLUSMALLINT iDescField, iStartField=0;
	SQLRETURN rc;

	// Get the descriptor record count.
	rc = SQLGetDescField(hdesc, 0, SQL_DESC_COUNT, &swDescRecCount,
		sizeof(swDescRecCount), &cbValue);

	if (SQL_SUCCESS == rc) {

		// In read mode, try to read one past last record
		if (swUpdateMode == DESC_UPDATE_MODE_READ)
			swAdditionalRecs=1;

		// Check all records, including header
		for (swDescRec=0; swDescRec <= swDescRecCount+swAdditionalRecs; swDescRec++) {

			// Check all fields
			for (iDescField=iStartField; iDescField < sizeof(rgDescInfo)/sizeof(rgDescInfo[0]); iDescField++) {

				// If we've gone past the header fields, then break out of loop to check record fields
				if (0 == swDescRec && !rgDescInfo[iDescField].fHeader) {
					iStartField=iDescField;
					break;
				}

				if (DESC_UPDATE_MODE_READ == swUpdateMode)
				{
					// Read from the field
					rc = SQLGetDescField(hdesc, swDescRec, rgDescInfo[iDescField].uwDescField,
						&DescBuf, sizeof(DescBuf), &cbValue);
					
					CheckDescOp(hdesc, rc, uwDescIndex, swDescRecCount, swDescRec, iDescField, swUpdateMode);

					if (RC_SUCCESSFUL(rc))
					{
						// Compare cbValue with expected
						cbValue2=rgDescInfo[iDescField].cbValue; // For most fields

						if (!rgDescInfo[iDescField].size)
							cbValue2 = lstrlen((LPTSTR)DescBuf);  // For string fields

						// Make sure cbValue and cbValue2 agree
						if (cbValue != cbValue2)
						{
							wsprintf(buf,TEXT("Compare error in %s field %s, expected")\
								TEXT(" StringLength %d, received %d"), DescTypes[uwDescIndex].szDescName,
								rgDescInfo[iDescField].szDescFieldName, cbValue2, cbValue);
							DISPLAYERROR(szSQLGETDESCFIELD, buf);
						}
					}
				}
				else
				{
					// Write to the field.  For char fields size is 0 (unknown),
					// so compute the length of the string
					rc = SQLSetDescField(hdesc, swDescRec, rgDescInfo[iDescField].uwDescField,
						(SQLPOINTER)rgDescInfo[iDescField].NewValue,
						(rgDescInfo[iDescField].size) ? rgDescInfo[iDescField].size :
						lstrlen((LPTSTR)rgDescInfo[iDescField].NewValue)*sizeof(TCHAR));

					CheckDescOp(hdesc, rc, uwDescIndex, swDescRecCount, swDescRec, iDescField, swUpdateMode);

					if (RC_SUCCESSFUL(rc))
						CompareDescField(hdesc, NULL, uwDescIndex, swDescRec, swDescRecCount,iDescField, szSQLSETDESCFIELD);
				}
			}
		}
	}
	else {
		// Unable to read record count from descriptor header, can't proceed
		wsprintf(buf,TEXT("\t\tUnable to read record count from descriptor header."));
		ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, buf);
	}
}

//-----------------------------------------------------------------------
//
// Function:  CompareDescriptor
//
// Compares two descriptors, or if hdesc2 is NULL compares hdesc1 to rgDescInfo
// updatable columns
//-----------------------------------------------------------------------

void CompareDescriptor(SQLHDESC hdesc1, SQLHDESC hdesc2, UWORD uwDescIndex, TCHAR * pszAPI)
{
 	SQLSMALLINT swDescRec, swDescRecCount;
	SQLUSMALLINT iDescField, iStartField=0;
	SQLRETURN rc;

	// Make sure we've got a valid descriptor handle for hdesc1
	// (hdesc2 is allowed to be NULL)
	if (SQL_NULL_HDESC == hdesc1) {
		wsprintf(buf,TEXT("\t\thCompareDescriptor: hdesc1 handle was null!"));
		DISPLAYERROR(szSQLGETDESCFIELD, buf);
		return;
	}

	// Get the descriptor record count.
	rc = SQLGetDescField(hdesc1, 0, SQL_DESC_COUNT, &swDescRecCount,
		sizeof(swDescRecCount), &cbValue);

	if (SQL_SUCCESS == rc) {

		// Check all records, including header
		for (swDescRec=0; swDescRec <= swDescRecCount; swDescRec++) {

			// Check all fields
			for (iDescField=iStartField; iDescField < sizeof(rgDescInfo)/sizeof(rgDescInfo[0]); iDescField++) {

				// If we've gone past the header fields, then break out of loop to check record fields
				if (0 == swDescRec && !rgDescInfo[iDescField].fHeader) {
					iStartField=iDescField;
					break;
				}

				CompareDescField(hdesc1, hdesc2, uwDescIndex, swDescRec, swDescRecCount, iDescField, pszAPI);
			}
		}
	}
	else {
		// Unable to read record count from descriptor header, can't proceed
		wsprintf(buf,TEXT("\t\tUnable to read record count from descriptor header."));
		ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_SUCCESS, rc, buf);
	}
}


void CheckDescRecord(SQLHDESC hdesc, SQLSMALLINT swDescRec, SQLSMALLINT fType,
           SQLSMALLINT fSubType, SQLINTEGER cbLength, SQLSMALLINT ibPrecision, SQLSMALLINT ibScale,
           SQLPOINTER pData, SQLINTEGER *pcbValue, SQLINTEGER *pIndicator, SQLUSMALLINT iDescType)
{
	SQLINTEGER Length, * pIndicator2;
	PTR pDescPtr;
	SQLRETURN rc;
	SQLSMALLINT fType2, fSubType2, cbName, Precision, Scale, Nullable;
	TCHAR	szName[MAX_DESC_BUF]=TEXT("");

	// Write the record
	rc = SQLSetDescRec(hdesc, swDescRec, fType, fSubType, cbLength, ibPrecision, 
		ibScale, pData, pcbValue, pIndicator);

	// Can't set IRD, so it should error
	if (SQL_ATTR_IMP_ROW_DESC == DescTypes[iDescType].uwDescType)
		ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_ERROR, rc, szSQLSETDESCREC);
	else
	{
		wsprintf(buf,TEXT("%s: Unable to write record %d in %s"),
			szSQLSETDESCREC, swDescRec, DescTypes[iDescType].szDescName);
		ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, buf);
	}

	if (RC_SUCCESSFUL(rc))
	{
		// Read it again
		rc = SQLGetDescRec(hdesc, swDescRec, szName, sizeof(szName), &cbName, &fType2,
			&fSubType2, &Length, &Precision, &Scale, &Nullable);

		wsprintf(buf,TEXT("%s: Unable to read record %d in %s"),
			szSQLGETDESCREC, swDescRec, DescTypes[iDescType].szDescName);
		ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, buf);

		if (RC_SUCCESSFUL(rc))
		{
			// Compare values
			if (fType2 != fType)
				DISPLAYERROR(szSQLSETDESCREC,TEXT("fType not set correctly"));
			
			if (Precision != ibPrecision)
				DISPLAYERROR(szSQLSETDESCREC,TEXT("ibPrecision not set correctly"));

			switch(fType)
			{
				case SQL_DECIMAL:
				case SQL_NUMERIC:
				case SQL_C_DOUBLE:
				case SQL_C_FLOAT:
					// Scale is only defined for NUMERIC or DECIMAL types
					if (Scale != ibScale)
						DISPLAYERROR(szSQLSETDESCREC,TEXT("ibScale not set correctly"));
					break;
				case SQL_DATETIME:
				case SQL_INTEGER:
					// Subtype is only valid for DATETIME or INTERVAL types
					if (fSubType2 != fSubType)
						DISPLAYERROR(szSQLSETDESCREC,TEXT("fSubType not set correctly"));
					break;
			}

			// For application descriptors, compare the Length and get the
			// data ptr value to check for accuracy
			switch(DescTypes[iDescType].uwDescType)
			{
				case SQL_ATTR_APP_ROW_DESC:
				case SQL_ATTR_APP_PARAM_DESC:

					if (Length != cbLength)
						DISPLAYERROR(szSQLSETDESCREC,TEXT("cbLength not set correctly"));

					rc = SQLGetDescField(hdesc, swDescRec, SQL_DESC_DATA_PTR,
						&pDescPtr, sizeof(PTR), &cbValue);
					ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, szSQLGETDESCFIELD);

					if (pDescPtr != pData)
						DISPLAYERROR(szSQLSETDESCREC,TEXT("rgbValue not set correctly"));

					// Get the octet length ptr value and check for accuracy
					rc = SQLGetDescField(hdesc, swDescRec, SQL_DESC_OCTET_LENGTH_PTR,
						&pDescPtr, sizeof(PTR), &cbValue);
					ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, szSQLGETDESCFIELD);

					if (pDescPtr != pcbValue)
						DISPLAYERROR(szSQLSETDESCREC,TEXT("cbValue not set correctly"));

					rc = SQLGetDescField(hdesc, swDescRec, SQL_DESC_INDICATOR_PTR,
						&pIndicator2, sizeof(PTR), &cbValue);
					ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, szSQLGETDESCFIELD);

					if (pIndicator2 != pIndicator)
						DISPLAYERROR(szSQLSETDESCREC,TEXT("Indicator not set correctly"));
					
					break;
				case SQL_ATTR_IMP_ROW_DESC:
				case SQL_ATTR_IMP_PARAM_DESC:
					break;
				default:
					DISPLAYERROR(szSQLSETDESCREC,TEXT("Unknown descriptor type."));
			}
		}
	}

}

SQLRETURN DescBindParameter(SQLHSTMT hstmt, SQLUSMALLINT ipar,
    SQLSMALLINT fParamType, SQLSMALLINT fCType, SQLSMALLINT fSqlType,
    SQLUINTEGER cbColDef, SQLSMALLINT ibScale, SQLPOINTER rgbValue,
    SQLINTEGER cbValueMax, SQLINTEGER  *pcbValue)
{
	SQLHDESC hdescAPD, hdescIPD;
	SQLRETURN rc;

	rc = SQLGetStmtAttr(hstmt, SQL_ATTR_APP_PARAM_DESC, &hdescAPD, sizeof(hdescAPD), NULL);  
	if (!RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR))
		return rc;

	rc = SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_PARAM_DESC, &hdescIPD, sizeof(hdescIPD), NULL);  
	if (!RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR))
		return rc;

	// Parameter type
	rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_PARAMETER_TYPE, (SQLPOINTER)fParamType,
		SQL_IS_SMALLINT);		// Set ipar and fParamType for IPD
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;
	
	// C type
	rc = SQLSetDescField(hdescAPD, ipar, SQL_DESC_CONCISE_TYPE, (SQLPOINTER)fCType,
		SQL_IS_SMALLINT);		// Set ipar and fCType of APD
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescAPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	// Sql type
	rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_CONCISE_TYPE, (SQLPOINTER)fSqlType,
		SQL_IS_SMALLINT);		// Set fSqlType of IPD
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	// Column Size (Length or Precision)
	if (fSqlType == SQL_CHAR ||
		fSqlType == SQL_VARCHAR ||
		fSqlType == SQL_LONGVARCHAR ||
		fSqlType == SQL_BINARY ||
		fSqlType == SQL_VARBINARY ||
		fSqlType == SQL_LONGVARBINARY ||
		fSqlType == SQL_TYPE_DATE ||
		fSqlType == SQL_TYPE_TIME ||
		fSqlType == SQL_TYPE_TIMESTAMP ||
		(fSqlType >= SQL_INTERVAL_YEAR &&
		 fSqlType <= SQL_INTERVAL_MINUTE_TO_SECOND))
	{
		rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_LENGTH, (SQLPOINTER)cbColDef,
			SQL_IS_UINTEGER);		// Set cbColDef (Length) of IPD
		if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
			return rc;
	}
	else if (fSqlType == SQL_DECIMAL ||
			 fSqlType == SQL_NUMERIC ||
			 fSqlType == SQL_FLOAT ||
			 fSqlType == SQL_REAL ||
			 fSqlType == SQL_DOUBLE)
	{
		rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_PRECISION, (SQLPOINTER)cbColDef,
			SQL_IS_SMALLINT);		// Set cbColDef (Precision) of IPD
		if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
			return rc;
	}

	// Scale
	if (fSqlType == SQL_TYPE_DATE ||
		fSqlType == SQL_TYPE_TIME ||
		fSqlType == SQL_TYPE_TIMESTAMP ||
		(fSqlType >= SQL_INTERVAL_YEAR &&
		 fSqlType <= SQL_INTERVAL_MINUTE_TO_SECOND))
	{
		switch(fSqlType)
		{
			case SQL_TYPE_TIME:
			case SQL_TYPE_TIMESTAMP:
			case SQL_INTERVAL_SECOND:
			case SQL_INTERVAL_DAY_TO_SECOND:
			case SQL_INTERVAL_HOUR_TO_SECOND:
			case SQL_INTERVAL_MINUTE_TO_SECOND:
				rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_PRECISION, (SQLPOINTER)ibScale,
					SQL_IS_SMALLINT);		// Set scale of IPD
				if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
					return rc;
				break;
			default:
				rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_PRECISION, (SQLPOINTER)0,
					SQL_IS_SMALLINT);		// Set scale of IPD
				if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
					return rc;
		}
	}
	else
	{
		rc = SQLSetDescField(hdescIPD, ipar, SQL_DESC_SCALE, (SQLPOINTER)ibScale,
			SQL_IS_SMALLINT);		// Set scale of IPD
		if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescIPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
			return rc;
	}

	// cbValueMax
	rc = SQLSetDescField(hdescAPD, ipar, SQL_DESC_OCTET_LENGTH, (SQLPOINTER)cbValueMax,
		SQL_IS_INTEGER);		// Set cbValueMax of APD
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescAPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	// pcbValue
	rc = SQLSetDescField(hdescAPD, ipar, SQL_DESC_OCTET_LENGTH_PTR, (SQLPOINTER)pcbValue,
		SQL_IS_POINTER);		// Set pcbValue/octet length
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescAPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	rc = SQLSetDescField(hdescAPD, ipar, SQL_DESC_INDICATOR_PTR, (SQLPOINTER)pcbValue,
		SQL_IS_POINTER);		// Set pcbValue/indicator
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdescAPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	// Data ptr
	rc = SQLSetDescField(hdescAPD, ipar, SQL_DESC_DATA_PTR, (SQLPOINTER)rgbValue,
		SQL_IS_POINTER);		// Set rgbValue
	ERRSHANDLE(SQL_HANDLE_DESC, hdescAPD, SQL_SUCCESS, rc,szSQLSETDESCFIELD);

	return rc;

}

SQLRETURN DescBindCol(SQLHSTMT hstmt, SQLSMALLINT icol,
           SQLSMALLINT fCType, SQLPOINTER rgbValue,
           SQLINTEGER cbValueMax, SQLINTEGER *pcbValue)
{
	SQLHDESC hdesc;
	SQLRETURN rc;

	rc = SQLGetStmtAttr(hstmt, SQL_ATTR_APP_ROW_DESC, &hdesc, sizeof(hdesc), NULL);  
	if (!RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR))
		return rc;

	rc = SQLSetDescField(hdesc, icol, SQL_DESC_CONCISE_TYPE, (SQLPOINTER)fCType,
		SQL_IS_SMALLINT);		// Set icol and fCType
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;
	
	rc = SQLSetDescField(hdesc, icol, SQL_DESC_OCTET_LENGTH, (SQLPOINTER)cbValueMax,
		SQL_IS_INTEGER);		// Set cbValueMax
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	rc = SQLSetDescField(hdesc, icol, SQL_DESC_OCTET_LENGTH_PTR, (SQLPOINTER)pcbValue,
		SQL_IS_POINTER);		// Set pcbValue/octet length
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	rc = SQLSetDescField(hdesc, icol, SQL_DESC_INDICATOR_PTR, (SQLPOINTER)pcbValue,
		SQL_IS_POINTER);		// Set pcbValue/indicator
	if (!ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD))
		return rc;

	rc = SQLSetDescField(hdesc, icol, SQL_DESC_DATA_PTR, (SQLPOINTER)rgbValue,
		SQL_IS_POINTER);		// Set rgbValue
	ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc,szSQLSETDESCFIELD);

	return rc;
}

//-----------------------------------------------------------------------
//      Function:               TestGetDescField
//-----------------------------------------------------------------------

void  PASCAL TestGetDescField(QTSTRUCT * lpqt)
{
	SQLRETURN rc=SQL_SUCCESS;
	SQLUSMALLINT iDescType;

	SQLHDESC hdesc1=NULL, hdesc2=NULL;
	PTR rgbValue=NULL;
	SQLSMALLINT swDescRecCount, swExpRecCount;
	SQLINTEGER cbValue;
	TCHAR	szName[MAX_DESC_BUF]=TEXT("");
	TCHAR	szQuery[XLARGEBUFF]=TEXT("");

	if (!Supported(SQL_API_SQLGETDESCFIELD))
	{
		// Allocate a default descriptor
		rc = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);  

		if (RC_SUCCESSFUL(rc))
		{
 			rc = SQLGetDescField(hdesc, 0, SQL_DESC_COUNT, &DescBuf, sizeof(DescBuf),
				&cbValue);

			if(!FindError(SQL_HANDLE_DESC,szIM001))
				DISPLAYERROR(szSQLGETDESCFIELD, szNotSupported);
			RETCHECK(SQL_ERROR, rc,szSQLGETDESCFIELD);
		}
	}
	else
	{
		// Make sure all parameters and columns are unbound
		ResetHstmt(&hstmt);

		// Perform a select stmt
		wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
		rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		// For each descriptor type
		for (iDescType=0; iDescType < sizeof(DescTypes)/sizeof(DescTypes[0]); iDescType++)
		{

			// Get the handle for the automatically allocated descriptor
			rc = SQLGetStmtAttr(hstmt, DescTypes[iDescType].uwDescType, &hdesc1, sizeof(hdesc1), &cbValue);  
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);

			// Create a descriptor record so we have something to read besides header
			swExpRecCount=CreateDescRecord(hdesc1, hstmt, DescTypes[iDescType].uwDescType);

			// Get the count of descriptor records (iRecord ignored for header fields)
			rc = SQLGetDescField(hdesc1, 0, SQL_DESC_COUNT, &swDescRecCount,
				sizeof(swDescRecCount), &cbValue);

			if (SQL_SUCCEEDED(rc)) 
			{
				// Check count value for expected
				if (swExpRecCount != swDescRecCount)
				{
					wsprintf(buf,TEXT("Expected record count %d, found %d"),
						swExpRecCount, swDescRecCount);
					DISPLAYERROR(szSQLGETDESCFIELD, buf);
				}

				CheckDescriptor(hdesc1, DESC_UPDATE_MODE_READ, hstmt, iDescType);
			}
			else
			{
				// Unable to read record count from descriptor header, can't proceed
				wsprintf(buf,TEXT("Unable to read record count from descriptor header for descriptor type %d"),
					DescTypes[iDescType].szDescName);
				ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_SUCCESS, rc, buf);
			}
		}

		rc=SQLCloseCursor(hstmt);
		RETCHECK(SQL_SUCCESS, rc,szSQLCLOSECURSOR);
	}


} // TestGetDescField()

//-----------------------------------------------------------------------
//      Function:               TestSetDescField
//-----------------------------------------------------------------------

void  PASCAL TestSetDescField(QTSTRUCT * lpqt)
{
	SQLRETURN rc=SQL_SUCCESS;
	SQLUSMALLINT iDescType;

	SQLHDESC hdesc1=NULL, hdesc2=NULL;
	PTR rgbValue=NULL;
	SQLSMALLINT swDescRecCount, swExpRecCount;
	SQLINTEGER cbValue;
	TCHAR	szName[MAX_DESC_BUF]=TEXT("");
	TCHAR	szQuery[XLARGEBUFF]=TEXT("");


	if (!Supported(SQL_API_SQLSETDESCFIELD))
	{
		// Allocate a default descriptor
		rc = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);  

		if (RC_SUCCESSFUL(rc))
		{
			rc = SQLSetDescField(hdesc, 0, SQL_DESC_COUNT, &swDescRecCount,
				sizeof(swDescRecCount));

			if(!FindError(SQL_HANDLE_DESC,szIM001))
				DISPLAYERROR(szSQLSETDESCFIELD, szNotSupported);
			RETCHECK(SQL_ERROR, rc,szSQLSETDESCFIELD);
		}
	}
	else
	{
		// Make sure all parameters and columns are unbound
		ResetHstmt(&hstmt);
		
		// Perform a select stmt
		wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
		rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		// For each descriptor type
		for (iDescType=0; iDescType < sizeof(DescTypes)/sizeof(DescTypes[0]); iDescType++)
		{

			// Get the handle for the automatically allocated descriptor
			rc = SQLGetStmtAttr(hstmt, DescTypes[iDescType].uwDescType, &hdesc1, sizeof(hdesc1), &cbValue);  
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);

			// Create a descriptor record so we have something to read besides header
			swExpRecCount=CreateDescRecord(hdesc1, hstmt, DescTypes[iDescType].uwDescType);

			// Update all descriptor records to new values
			CheckDescriptor(hdesc1, DESC_UPDATE_MODE_WRITE, hstmt, iDescType);

			// Compare the descriptor with the update values
			// CompareDescriptor(hdesc1, NULL, iDescType, szSQLSETDESCFIELD);
		}

		ResetHstmt(&hstmt);
	}

} //TestSetDescField()

//-----------------------------------------------------------------------
//      Function:               TestGetDescRec
//-----------------------------------------------------------------------

void  PASCAL TestGetDescRec(QTSTRUCT * lpqt)
{
	SQLRETURN rc=SQL_SUCCESS;
	SQLUSMALLINT iDescType;

	SQLHDESC hdesc1=NULL, hdesc2=NULL;
	PTR rgbValue=NULL;
	SQLSMALLINT swDescRec, swDescRecCount, iRecord, cbNameMax, cbName, fType, fSubType,
		Precision, Scale, Nullable, swExpRecCount;
	SQLINTEGER Length, cbValue;
	TCHAR	szName[MAX_DESC_BUF]=TEXT("");
	TCHAR	szQuery[XLARGEBUFF]=TEXT("");


	if (!Supported(SQL_API_SQLGETDESCREC))
	{
		// Allocate a default descriptor
		rc = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);  

		if (RC_SUCCESSFUL(rc))
		{
			rc = SQLGetDescRec(hdesc, iRecord, szName, cbNameMax, &cbName, &fType,
				&fSubType, &Length, &Precision, &Scale, &Nullable);

			if(!FindError(SQL_HANDLE_DESC,szIM001))
				DISPLAYERROR(szSQLGETDESCREC, szNotSupported);
			RETCHECK(SQL_ERROR, rc,szSQLGETDESCREC);
		}
	}
	else
	{
		// Make sure all parameters and columns are unbound
		ResetHstmt(&hstmt);

		// Turn on bookmarks so we can retrieve from record 0 of ARD
		rc = SQLSetStmtAttr(hstmt, SQL_ATTR_USE_BOOKMARKS, (SQLPOINTER)SQL_UB_ON, SQL_IS_INTEGER);
		RETCHECK(SQL_SUCCESS, rc,szSQLSETSTMTATTR);
		
		// Perform a select stmt
		wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
		rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		// For each descriptor type
		for (iDescType=0; iDescType < sizeof(DescTypes)/sizeof(DescTypes[0]); iDescType++)
		{

			// Get the handle for the automatically allocated descriptor
			rc = SQLGetStmtAttr(hstmt, DescTypes[iDescType].uwDescType, &hdesc1, sizeof(hdesc1), &cbValue);  
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);

			// Create a descriptor record so we have something to read besides header
			swExpRecCount=CreateDescRecord(hdesc1, hstmt, DescTypes[iDescType].uwDescType);

			// Get the count of descriptor records
			// Count for automatically allocated descriptors is written in
			// SetDescField test.
			rc = SQLGetDescField(hdesc1, 0, SQL_DESC_COUNT, &swDescRecCount,
				sizeof(swDescRecCount), &cbValue);

			if (SQL_SUCCESS == rc) 
			{

				// For all descriptor records	
				for (swDescRec=0; swDescRec <= swDescRecCount+1; swDescRec++)
				{
						// Read the record
						rc = SQLGetDescRec(hdesc1, swDescRec, szName, sizeof(szName), &cbName, &fType,
							&fSubType, &Length, &Precision, &Scale, &Nullable);

						if (swDescRec <= swDescRecCount)
						{
							// Retrieving bookmark on IPD is an error
							if (SQL_ATTR_IMP_PARAM_DESC == DescTypes[iDescType].uwDescType && 0 == swDescRec)
							{
								wsprintf(buf,TEXT("%s: Able to read record %d from %s"),
									szSQLGETDESCREC, swDescRec, DescTypes[iDescType].szDescName);
								ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_ERROR, rc, buf);
							}
							else
							{
								wsprintf(buf,TEXT("%s: Unable to read record %d from %s"),
									szSQLGETDESCREC, swDescRec, DescTypes[iDescType].szDescName);
								ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_SUCCESS, rc, buf);
							}
						}
						else
						{
							wsprintf(buf,TEXT("%s: Did not receive SQL_NO_DATA reading record %d from %s"),
								szSQLGETDESCREC, swDescRec, DescTypes[iDescType].szDescName);
							ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_NO_DATA, rc, buf);
						}
				}
			}
			else
			{
				// Unable to read record count from descriptor header, can't proceed
				wsprintf(buf,TEXT("\t\tUnable to read record count from descriptor header for %s"),
					DescTypes[iDescType].szDescName);
				ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_SUCCESS, rc, buf);
			}
		}

		rc=SQLCloseCursor(hstmt);
		RETCHECK(SQL_SUCCESS, rc,szSQLCLOSECURSOR);

	}

} //TestGetDescRec()

//-----------------------------------------------------------------------
//      Function:               TestSetDescRec
//-----------------------------------------------------------------------

void  PASCAL TestSetDescRec(QTSTRUCT * lpqt)
{
	SQLRETURN rc=SQL_SUCCESS;
	SQLINTEGER cbLength, cbValue, Indicator;
	SQLUSMALLINT iDescType;

	SQLHDESC hdesc1=NULL, hdesc2=NULL;
	PTR rgbValue=NULL;
	SQLSMALLINT swDescRec, swDescRecCount, swStartRec=1, iRecord, fType, fSubType,
		ibPrecision, ibScale;
	SQLSMALLINT swExpRecCount;
	TCHAR	szQuery[XLARGEBUFF]=TEXT("");


	if (!Supported(SQL_API_SQLSETDESCREC))
	{
		// Allocate a default descriptor
		rc = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);  

		if (RC_SUCCESSFUL(rc))
		{
			rc = SQLSetDescRec(hdesc, iRecord, fType, fSubType, cbLength,
				ibPrecision, ibScale, &DescBuf, &cbValue, &Indicator);

			if(!FindError(SQL_HANDLE_DESC,szIM001))
				DISPLAYERROR(szSQLSETDESCREC, szNotSupported);
			RETCHECK(SQL_ERROR, rc,szSQLSETDESCREC);
		}
	}
	else
	{
		// Make sure all parameters and columns are unbound
		ResetHstmt(&hstmt);
		
		// Perform a select stmt
		wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
		rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		// If bookmarks are supported, then we want to try to set record 0
		rc = SQLSetStmtAttr(hstmt, SQL_ATTR_USE_BOOKMARKS,
			(PTR)SQL_UB_VARIABLE, SQL_IS_INTEGER);
		if (RC_SUCCESSFUL(rc))
			swStartRec=0;

		// For each descriptor type
		for (iDescType=0; iDescType < sizeof(DescTypes)/sizeof(DescTypes[0]); iDescType++)
		{

			// Get the handle for the automatically allocated descriptor
			rc = SQLGetStmtAttr(hstmt, DescTypes[iDescType].uwDescType, &hdesc1, sizeof(hdesc1), &cbValue);  
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);

			// Create a descriptor record so we have something to read besides header
			swExpRecCount=CreateDescRecord(hdesc1, hstmt, DescTypes[iDescType].uwDescType);

			// Get the count of descriptor records
			rc = SQLGetDescField(hdesc1, 0, SQL_DESC_COUNT, &swDescRecCount,
				sizeof(swDescRecCount), &cbValue);

			if (SQL_SUCCESS == rc) 
			{

				// For all descriptor records	
				for (swDescRec=swStartRec; swDescRec <= swDescRecCount; swDescRec++)
				{
					// Test with a DATETIME record so we can check the subtype field.
					SQLINTEGER Indicator=0;
					fType=SQL_DATETIME;
					fSubType=SQL_CODE_TIMESTAMP;
					cbLength=sizeof(TIMESTAMP_STRUCT);
					ibPrecision=5; 	// For DATETIME, SQL_CODE_DATE data
											// precision defaults to 0, but it implies it can be set otherwise.
					ibScale=0;		// Only used for DECIMAL or NUMERIC types, otherwise undefined

					CheckDescRecord(hdesc1, swDescRec, fType, fSubType, cbLength, ibPrecision, 
						ibScale, &tsval, &cbValue, &Indicator, iDescType);					

					// Test with a numeric record to test scale
					Indicator=0;
					fType=SQL_NUMERIC;
					fSubType=SQL_CODE_TIMESTAMP;
					cbLength=sizeof(TIMESTAMP_STRUCT);
					ibPrecision=5; 	// For DATETIME, SQL_CODE_DATE data
											// precision defaults to 0, but it implies it can be set otherwise.
					ibScale=0;		// Only used for DECIMAL or NUMERIC types, otherwise undefined

					CheckDescRecord(hdesc1, swDescRec, fType, fSubType, cbLength, ibPrecision, 
						ibScale, &tsval, &cbValue, &Indicator, iDescType);
				}
			}
			else
			{
				// Unable to read record count from descriptor header,
				// can't proceed
				wsprintf(buf,TEXT("\t\tUnable to read record count from descriptor header for  %s"),
					DescTypes[iDescType].szDescName);
				ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_SUCCESS, rc, buf);
			}
		}
		ResetHstmt(&hstmt);
	}

} //TestSetDescRec()

//-----------------------------------------------------------------------
//      Function:               TestCopyDesc
//-----------------------------------------------------------------------

void  PASCAL TestCopyDesc(QTSTRUCT * lpqt)
{
	SQLRETURN rc=SQL_SUCCESS;
	SQLUSMALLINT iDescType;
	SQLSMALLINT swExpRecCount;

	SQLHDESC hdesc1=NULL, hdesc2=NULL;
	PTR rgbValue=NULL;
	TCHAR	szName[MAX_DESC_BUF]=TEXT("");
	TCHAR	szQuery[XLARGEBUFF]=TEXT("");


	// Allocate a default descriptor
	rc = SQLAllocHandle(SQL_HANDLE_DESC, hdbc, &hdesc);  

	if (RC_SUCCESSFUL(rc))
	{

		if (!Supported(SQL_API_SQLCOPYDESC))
		{
			rc = SQLCopyDesc(hdesc, hdesc1);

			if(!FindError(SQL_HANDLE_DESC,szIM001))
				DISPLAYERROR(szSQLCOPYDESC, szNotSupported);
			RETCHECK(SQL_ERROR, rc,szSQLCOPYDESC);
		}
		else
		{
			ResetHstmt(&hstmt);
			
			// Perform a select stmt
			wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
			rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
			RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

			// For each descriptor type
			for (iDescType=0; iDescType < sizeof(DescTypes)/sizeof(DescTypes[0]); iDescType++)
			{
				// Get the handle for the automatically allocated descriptor
				rc = SQLGetStmtAttr(hstmt, DescTypes[iDescType].uwDescType, &hdesc1, sizeof(hdesc1), &cbValue);  
				RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);

				// Create a descriptor record so we have something to read besides header
				swExpRecCount=CreateDescRecord(hdesc1, hstmt, DescTypes[iDescType].uwDescType);

				// Update all descriptor records to new values
				CheckDescriptor(hdesc1, DESC_UPDATE_MODE_WRITE, hstmt, iDescType);

				// Copy the descriptor to the newly allocated descriptor
				rc = SQLCopyDesc(hdesc1, hdesc);
				ERRSHANDLE(SQL_HANDLE_DESC, hdesc1, SQL_SUCCESS, rc, szSQLCOPYDESC);
				ERRSHANDLE(SQL_HANDLE_DESC, hdesc, SQL_SUCCESS, rc, szSQLCOPYDESC);

				// Compare each field in the copied descriptor to the original
				if (RC_SUCCESSFUL(rc))
					CompareDescriptor(hdesc1, hdesc, iDescType, szSQLCOPYDESC);
			}

			ResetHstmt(&hstmt);
		}

		// Free descriptor handle
		if (hdesc)
		{
			rc = SQLFreeHandle(SQL_HANDLE_DESC, hdesc); 
			RETCHECK(SQL_SUCCESS, rc,szSQLFREEHANDLE);
		}
	}

} //TestCopyDesc()


//-----------------------------------------------------------------------
//      Function:               TestDescDefaults
//-----------------------------------------------------------------------
void  PASCAL TestDescDefaults(QTSTRUCT * lpqt)
{
	SQLRETURN rc=SQL_SUCCESS;
 	SQLINTEGER cbValue;
	SQLSMALLINT swDescRec;
	SQLUSMALLINT iDescField, iStartField=0, iDescType;

	if (Supported(SQL_API_SQLGETDESCFIELD))
	{

		// Reallocate hstmt to check defaults against
		ResetHstmt(&hstmt);

		// For each descriptor type
		for (iDescType=0; iDescType < sizeof(DescTypes)/sizeof(DescTypes[0]); iDescType++)
		{
			// Get the handle for the descriptor
			rc = SQLGetStmtAttr(hstmt, DescTypes[iDescType].uwDescType, &hdesc, sizeof(hdesc), NULL);  
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);

			swDescRec=0;

			// For each descriptor field, read the value
			for (iDescField=iStartField; iDescField < sizeof(rgDescInfo)/sizeof(rgDescInfo[0]); iDescField++) {

				// If we've gone past the header fields, then create a record and check record fields
				if (0 == swDescRec && !rgDescInfo[iDescField].fHeader) {
					iStartField=iDescField;
					// Make sure we're not on the IRD, 'cause you can't modify an IRD
					if (SQL_ATTR_IMP_ROW_DESC != DescTypes[iDescType].uwDescType)
					{
						// Create a record with all default values
						rc = SQLSetDescField(hdesc, 0, SQL_DESC_COUNT, (SQLPOINTER)1,
							SQL_IS_SMALLINT);
						RETCHECK(SQL_SUCCESS, rc,szSQLSETDESCFIELD);

						swDescRec++;
					}
					continue;
				}

				// If the field has a default value
				if (rgDescInfo[iDescField].fDefault & DescTypes[iDescType].uwTypeMask)
				{
					// Read from the field
					rc = SQLGetDescField(hdesc, swDescRec, rgDescInfo[iDescField].uwDescField,
						&DescBuf, sizeof(DescBuf), &cbValue);
					RETCHECK(SQL_SUCCESS, rc,szSQLGETDESCFIELD);
					
					if (RC_SUCCESSFUL(rc))
					{
						// Perform the compare
						if (memcmp(DescBuf, &rgDescInfo[iDescField].DefaultVal, cbValue)) 
						{
							// Compare error, print message
							wsprintf(buf,TEXT("Error in %s field %s default value"),
								DescTypes[iDescType].szDescName,rgDescInfo[iDescField].szDescFieldName);
							DISPLAYERROR(szSQLGETDESCFIELD, buf);
						}
					}
				}
			}
		}
	}
} // TestDescDefaults
 
//-----------------------------------------------------------------------
//      Function:               TestUseDesc
//-----------------------------------------------------------------------
void  PASCAL TestUseDesc(QTSTRUCT * lpqt, FIELDINFO  *rgFields)
{
	LPTSTR   pch=NULL;
	SDWORD crow=0;
	TCHAR	szQuery[XLARGEBUFF]=TEXT("");
	SQLRETURN rc;
	UWORD	row, icol, paramno;
	SWORD	ccol;
	TCHAR * rgbMemBuf=NULL, * rgbValue=NULL;
	SDWORD * pcbValueBuf=NULL, * pcbValue=NULL;

	if (Supported(SQL_API_SQLSETDESCFIELD))
	{

		// Test descriptor bindcol
		
		// Reallocate hstmt to set to defaults
		ResetHstmt(&hstmt);
		
		// Perform a select stmt
		wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
		rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		rc=SQLNumResultCols(hstmt, &ccol);
		RETCHECK(SQL_SUCCESS, rc, szSQLNUMRESULTCOLS);

		rc=SQLFreeStmt(hstmt, SQL_CLOSE); // Close the cursor so we can insert 
		RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);

		rgbMemBuf=AllocateMemory(ccol*MAX_STRING_SIZE*sizeof(TCHAR));

		if (!rgbMemBuf)
		{
			DISPLAYERROR(TEXT("Simulate BindCol"),TEXT("Out of memory!"));
			goto ExitUseDesc;
		}

		pcbValueBuf=(SDWORD *)AllocateMemory(ccol*sizeof(SDWORD));

		if (!pcbValueBuf)
		{
			DISPLAYERROR(TEXT("Simulate BindCol"),TEXT("Out of memory!"));
			goto ExitUseDesc;
		}

		// Bind a parameter for each column in the result set using descriptors
		paramno=0;
		for (icol=1, rgbValue=rgbMemBuf, pcbValue=pcbValueBuf;
			icol <= ccol;
			icol++, rgbValue+=MAX_STRING_SIZE*sizeof(TCHAR), pcbValue++)
		{
			pch = qtMakeData(guwRowCount, icol-1, &rgFields[icol-1], rgbValue);

			// Field is not READ ONLY
			if(pch) 
			{
 				// Where row and column match and field is nullable, make NULL
				if (icol == guwRowCount && rgFields[icol-1].nullable)
					*pcbValue=SQL_NULL_DATA;
				else
					*pcbValue=SQL_NTS;

				paramno++;
//				rc=SQLBindParameter(hstmt, paramno, SQL_PARAM_INPUT, SQL_C_CHAR, 
				rc=DescBindParameter(hstmt, paramno, SQL_PARAM_INPUT, SQL_C_CHAR, 
					rgFields[icol-1].wSQLType, rgFields[icol-1].precision,
					rgFields[icol-1].scale, rgbValue, 0, pcbValue);
				RETCHECK(SQL_SUCCESS, rc,TEXT("DescBindParameter"));
			}
		}

		// Insert the new row.  Note that the inserted row will be checked
		// for accuracy below.
		rc = SQLExecDirect(hstmt, szInsertStmt, SQL_NTS);
		ERRSHANDLE(SQL_HANDLE_STMT, hstmt, SQL_SUCCESS, rc, szSQLEXECDIRECT);

		if (RC_SUCCESSFUL(rc))
			guwRowCount++;

		// Perform the select stmt again
		wsprintf(szQuery,szSELECTSTAR,lpqt->szTableName);
		rc = SQLExecDirect(hstmt, szQuery, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

		// Bind all the columns to char
		for (icol=1, rgbValue=rgbMemBuf, pcbValue=pcbValueBuf;
			icol <= ccol;
			icol++, rgbValue+=MAX_STRING_SIZE*sizeof(TCHAR), pcbValue++)
		{
			// Bind to next column
			rc = DescBindCol(hstmt, icol, SQL_C_CHAR, rgbValue, MAX_STRING_SIZE*sizeof(TCHAR), pcbValue);
//			rc = SQLBindCol(hstmt, icol, SQL_C_CHAR, rgbValue, MAX_STRING_SIZE*sizeof(TCHAR), pcbValue);
			RETCHECK(SQL_SUCCESS, rc, TEXT("DescBindCol"));
		}

		// Fetch all the rows and check the bound value with MakeAData for
		// each column
		for (row=1; rc == SQL_SUCCESS; row++)
		{
			rc=SQLFetch(hstmt); // Will return SQL_NO_DATA after last row

			if (SQL_SUCCESS == rc)
			{

				// Compare all the columns
				for (icol=1, rgbValue=rgbMemBuf, pcbValue=pcbValueBuf;
					icol <= ccol;
					icol++, rgbValue+=MAX_STRING_SIZE*sizeof(TCHAR), pcbValue++)
				{

					CompareWithExpected(rgbValue, pcbValue, row, icol, rgFields);
				}
			}
			else
				ERRSHANDLE(SQL_HANDLE_STMT, hstmt, SQL_NO_DATA, rc, szSQLFETCH);

		}

	}

ExitUseDesc:
	rc=SQLFreeStmt(hstmt, SQL_CLOSE);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREESTMT);

	if (rgbMemBuf)
		ReleaseMemory(rgbMemBuf);
	if (pcbValueBuf)
		ReleaseMemory(pcbValueBuf);


} // TestUseDesc

//-----------------------------------------------------------------------
//      Function:               TestEnvAttr
//
// Note:	Only one environment attribute (SQL_ATTR_OUTPUT_NTS) exists at this
// 		time.  The default value is SQL_TRUE.
//
//	For the Environment attributes we assume support if DM version >= 3.00
//-----------------------------------------------------------------------

void  PASCAL TestEnvAttr()
{
	SQLINTEGER	sdwEnvAttr;
	SQLRETURN	rc;
	HENV			tshenv;
	BOOL			fSetSupported = Supported(SQL_API_SQLSETENVATTR),
					fGetSupported = Supported(SQL_API_SQLGETENVATTR);


	//allocate an enviroment handle
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &tshenv);
	RETCHECK(SQL_SUCCESS, rc,szSQLALLOCHANDLE);


	//-------------------------------
	//-------- SQLSetEnvAttr --------
	//-------------------------------
	// Set to SQL_FALSE
	rc = SQLSetEnvAttr(tshenv, SQL_ATTR_ODBC_VERSION, (PTR)SQL_OV_ODBC3,
		SQL_IS_UINTEGER);

	if(!fSetSupported)
	{
		if (!FindError(SQL_HANDLE_ENV,szIM001))
			DISPLAYERROR(szSQLSETENVATTR, szNotSupported);

		RETCHECK(SQL_ERROR, rc,szSQLSETENVATTR);
	}
	else
		RETCHECK(SQL_SUCCESS, rc,szSQLSETENVATTR);

	if (RC_SUCCESSFUL(rc))
	{
		// Read it again
		rc = SQLGetEnvAttr(tshenv, SQL_ATTR_ODBC_VERSION, &sdwEnvAttr,
			sizeof(sdwEnvAttr), NULL);

		if(!fGetSupported)
		{
			if (!FindError(SQL_HANDLE_ENV,szIM001))
				DISPLAYERROR(szSQLGETENVATTR, szNotSupported);

			RETCHECK(SQL_ERROR, rc,szSQLGETENVATTR);
		}
		else
			RETCHECK(SQL_SUCCESS, rc,szSQLGETENVATTR);

		if (RC_SUCCESSFUL(rc) && (SQL_OV_ODBC3 != sdwEnvAttr))
		{
			// New value wrong
			DISPLAYERROR(szSQLSETENVATTR,TEXT("Unable to set environment attribute SQL_ATTR_ODBC_VERSION to SQL_OV_ODBC3."));
		}
	}

	rc = SQLFreeHandle(SQL_HANDLE_ENV,tshenv);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREEHANDLE);

	//-------------------------------
	//-------- SQLGetEnvAttr --------
	//-------------------------------
	rc = SQLAllocEnv(&tshenv);
	RETCHECK(SQL_SUCCESS, rc,szSQLALLOCENV);

	rc = SQLGetEnvAttr(tshenv, SQL_ATTR_ODBC_VERSION, &sdwEnvAttr,
		sizeof(sdwEnvAttr), NULL);

	if(!fGetSupported)
	{
		if (!FindError(SQL_HANDLE_ENV,szIM001))
			DISPLAYERROR(szSQLGETENVATTR, szNotSupported);

		RETCHECK(SQL_ERROR, rc,szSQLGETENVATTR);
	}
	else
		RETCHECK(SQL_SUCCESS, rc,szSQLGETENVATTR);

	
	if (RC_SUCCESSFUL(rc) && (SQL_OV_ODBC2 != sdwEnvAttr))
	{
		// Default value wrong
		DISPLAYERROR(szSQLGETENVATTR,TEXT("Value was not SQL_OV_ODBC3!"));
	}


	rc = SQLFreeHandle(SQL_HANDLE_ENV,tshenv);
	RETCHECK(SQL_SUCCESS, rc,szSQLFREEHANDLE);

} //TestEnvAttr()


//-----------------------------------------------------------------------
//    Function: GetRowCnt
//
//		Get the row count of the table lpqt->szTalbeName
//-----------------------------------------------------------------------
SWORD  PASCAL GetRowCnt(QTSTRUCT  *lpqt)
{
 	SWORD 		sRowCnt;
	RETCODE		rc;

	// free the statment handle for a fresh start
	FreeStmt(SQL_DROP);

	AllocHstmt();

	//get row count for the table
	wsprintf(lpqt->sz,TEXT("select count(*) from %s"), lpqt->szTableName);

	rc = SQLExecDirect(hstmt, lpqt->sz, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLEXECDIRECT);

	rc = SQLFetch(hstmt);
	RETCHECK(SQL_SUCCESS, rc,szSQLFETCH);

	rc = SQLGetData(hstmt,1, SQL_C_SSHORT, &sRowCnt, sizeof(sRowCnt), NULL);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETDATA);

	FreeStmt(SQL_CLOSE);

	return sRowCnt;
}//GetRowCount


//-----------------------------------------------------------------------
//    Function: InsertOneRow
//
//		Insert one row into the table.
//
//			lpqt:			temp place to hold data genrated
//			rgFields:	hold info about each data type in the dbs
//			cTypes;		the count of data types
//			lpd:			buffer used for SQLBindParam
//			cSeed;		the seed used to generate data
//			fFreeHsmt:	if the hstmt should be freed 	  
//
//		Return TRUE: the insertion was successful
//				 FALSE: otherwise
//-----------------------------------------------------------------------
										  
BOOL  PASCAL InsertOneRow(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
										DSTRUCT  *lpd,UWORD cSeed,BOOL fFreeHstmt)
{
	RETCODE  			rc;
	UWORD    			w;
	UWORD    			ind;
	LPTSTR    			pch=NULL;
	SQLHDESC				hdesc;
   SQLSMALLINT      	fParamType = SQL_PARAM_INPUT;
	TCHAR					szDataItem[150];


	//prepare the insert statement
	rc = SQLPrepare(hstmt, szInsertStmt, SQL_NTS);
	RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);

	//going through each data type, call SQLBindParam
	for(ind = 0, w = 0; ind < cTypes; ind++) 
	{

		//make data according to data type description in rgFields[], cSeed is the seed
		pch = qtMakeData(cSeed,ind,&rgFields[ind], szDataItem);

		//if the data type is READ_ONLY, skip
		if(!pch) 
			continue;

		//populate the NULL data
		if(*pch) 
		{
			lstrcpy(lpd[w].data, pch);
			lpd[w].cb = SQL_NTS;
		}
		else 
		{
			lstrcpy(lpd[w].data,TEXT(""));
			lpd[w].cb = SQL_NULL_DATA;
		}

		if (g_f3XDriver && Supported(SQL_API_SQLSETDESCFIELD))
//		if (0)	//DEBUG
		{
			//bind the data buffer in lpd[] to each column of the table
			rc = SQLBindParam(hstmt, (SQLSMALLINT)(w+1),SQL_C_TCHAR, rgFields[ind].wSQLType,
									rgFields[ind].precision, rgFields[ind].scale,
									&lpd[w].data, &lpd[w].cb);
			RETCHECK(SQL_SUCCESS, rc,szSQLBINDPARAM);

			if(rc!= SQL_SUCCESS)
				return FALSE;

			//get the driver parameter descriptor handle
			rc = SQLGetStmtAttr(hstmt,SQL_ATTR_IMP_PARAM_DESC, &hdesc, sizeof(hdesc),NULL);
			RETCHECK(SQL_SUCCESS, rc,szSQLGETSTMTATTR);
			if(rc!= SQL_SUCCESS)
				return FALSE;

			//set the parameter type field in the descriptor
			rc = SQLSetDescField(hdesc, (SQLSMALLINT)(w+1), SQL_DESC_PARAMETER_TYPE, 
										(PTR)fParamType, sizeof(fParamType));
			RETCHECK(SQL_SUCCESS, rc,szSQLSETDESCFIELD);

		}
		else
		{
			rc = SQLBindParameter(hstmt, (UWORD)(w+1),SQL_PARAM_INPUT,SQL_C_TCHAR, 
							rgFields[ind].wSQLType,	rgFields[ind].precision, 
							rgFields[ind].scale,&lpd[w].data, 100, &lpd[w].cb);
				
			RETCHECK(SQL_SUCCESS, rc,szSQLBINDPARAMETER);

			if(rc!= SQL_SUCCESS)
				return FALSE;
		}


		//go on to next column
		w++;
	}

	// insert a row 
	rc = SQLExecute(hstmt); 
	RETCHECK(SQL_SUCCESS, rc,szSQLEXECUTE);
	if(rc!= SQL_SUCCESS)
		return FALSE;

	//free the hstmt if required
	if(fFreeHstmt)
	{
		if (FreeStmt(SQL_CLOSE))
			return FALSE;

	}

	return TRUE;

}	//InsertOneRow

//-----------------------------------------------------------------------
//    Function: ExecEndTran
//
//		Execute EndTran statement, return the row count of the table
//-----------------------------------------------------------------------
SWORD  PASCAL ExecEndTran(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
								DSTRUCT  *lpd,SQLSMALLINT fHandleType, SQLSMALLINT fMode,
								UWORD cSeed)
{
  		RETCODE rc;

		//does not free the hstmt
		if(!InsertOneRow(lpqt,rgFields,cTypes,lpd,cSeed, FALSE))
				return (INSERT_FAIL);

		switch(fHandleType)
		{
			case SQL_HANDLE_ENV:
				rc= SQLEndTran(fHandleType,henv,fMode);
				break;
			case SQL_HANDLE_DBC:
				rc= SQLEndTran(fHandleType,hdbc,fMode);
				break;
			default:	
				DISPLAYERROR(TEXT("ExecEndTran"),TEXT("Did not recieve correct handle type"));
				break;
		}
		RETCHECK(SQL_SUCCESS, rc,szSQLENDTRAN);

		if (SQL_COMMIT == fMode && SQL_SUCCESS == rc)
			guwRowCount++;	// We inserted a row, increment global row count

		//free the hstmt handle
		FreeStmt(SQL_CLOSE);

		return(GetRowCnt(lpqt));
} //ExecEndTran

//-----------------------------------------------------------------------
//    Function: TestEndTran
//
//		Test the SQLEndTran for SDK 3.0
//-----------------------------------------------------------------------
void  PASCAL TestEndTran(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
										DSTRUCT  *lpd)
{
	SWORD				i;
	RETCODE 			rc;
	SWORD				sTXN;
	SWORD				sRowCnt_Pre;
	SWORD				sRowCnt_Aft;
	SQLSMALLINT	 	fHandleType[]={SQL_HANDLE_ENV, SQL_HANDLE_DBC};
	SDWORD			cbValue=0;

	//check if transaction is supported
	rc = SQLGetInfo(hdbc, SQL_TXN_CAPABLE, &sTXN, sizeof(sTXN), NULL);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);

	//check both henv and hdbc handle
	for(i=0; i<=1; i++)
	{ 

		//get the row count of the table
		sRowCnt_Pre = GetRowCnt(lpqt);

		//check if SQLEndTran is supported
		if(Supported(SQL_API_SQLENDTRAN))
		{
			if(sTXN != SQL_TC_NONE)
			{
				//set the autocommit to off
				SetConnectionAttributes(hdbc,SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
				
				//insert one row, and call SQLEndTran to roll back the transction
				sRowCnt_Aft = ExecEndTran(lpqt,rgFields,cTypes,lpd,fHandleType[i],SQL_ROLLBACK,(UWORD)(guwRowCount));
				
				//the row count should be the same
				if(sRowCnt_Aft != sRowCnt_Pre)
					DISPLAYERROR(szSQLENDTRAN,TEXT("Did not Roll Back the insert transaction"));
			}
				
			//insert one row, and call SQLEndTran to commit the transction
			sRowCnt_Aft = ExecEndTran(lpqt,rgFields,cTypes,lpd,fHandleType[i],SQL_COMMIT,(UWORD)(guwRowCount));

			//the row count should be increased by 1
			if(sRowCnt_Aft != (sRowCnt_Pre+1) )
				DISPLAYERROR(szSQLENDTRAN,TEXT("Did not commit the insert transaction"));

			if( sTXN != SQL_TC_NONE)
			{
				//set the autocommit to off
				SetConnectionAttributes(hdbc,SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
			}

		}//end of the situation where SQLEndTran is supported
		else
		{

			switch(fHandleType[i])
			{
				case SQL_HANDLE_ENV: 
					rc= SQLEndTran(fHandleType[i],henv,SQL_COMMIT);
					break;
				case SQL_HANDLE_DBC: 
					rc= SQLEndTran(fHandleType[i],hdbc,SQL_ROLLBACK);
					break;
			}

			//check error msg
			if(!FindError(fHandleType[i],szIM001))
				DISPLAYERROR(szSQLENDTRAN,TEXT("Did not return not Supported Message"));

			RETCHECK(SQL_ERROR, rc,szSQLENDTRAN);

			//free the hstmt handle
			FreeStmt(SQL_CLOSE);

		}//end of error msg checking

	}//end of the loop to check both henv and hdbc

	// Commit the transaction started in GetRowCnt inside ExecEndTran
	rc= SQLEndTran(SQL_HANDLE_ENV,henv,SQL_COMMIT);
	RETCHECK(SQL_SUCCESS, rc,szSQLENDTRAN);

	SetConnectionAttributes(hdbc,SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);

	//free the hstmt handle
	FreeStmt(SQL_CLOSE);

} // TestEndTran()


//-----------------------------------------------------------------------
//    Function: TestBindParam
//
//		Test the SQLBindParam for SDK 3.0
//-----------------------------------------------------------------------
void  PASCAL TestBindParam(QTSTRUCT  *lpqt,FIELDINFO  *rgFields,UWORD cTypes,
										DSTRUCT  *lpd)
{
 	RETCODE 			rc;
	SQLINTEGER		cbValue = SQL_NTS;
	TCHAR				szDataItem[150];

	if(Supported(SQL_API_SQLBINDPARAM))
	{
		//test SQLBindParam by inserting one row, do not free the hstmt handle
		if (InsertOneRow(lpqt,rgFields,cTypes,lpd,(UWORD)(guwRowCount),FALSE))
			guwRowCount++; // We've inserted a row
	}
	else
	{
	 	//prepare the insert statement
		rc = SQLPrepare(hstmt, szInsertStmt, SQL_NTS);
		RETCHECK(SQL_SUCCESS, rc,szSQLPREPARE);

		//make data according to data type description in rgFields[0], cSeed is the seed
		qtMakeData(cTypes+1,0,&rgFields[0],szDataItem);

		//try to bind lpqt->szDataItem to the first column of the table
		rc = SQLBindParam(hstmt,1,SQL_C_TCHAR, rgFields[0].wSQLType, rgFields[0].precision,
								rgFields[0].scale,lpqt->szDataItem, &cbValue);

		//check error msg
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLBINDPARAM,TEXT("Did not return Not Supported Message"));

		RETCHECK(SQL_ERROR, rc,szSQLBINDPARAM);
	}

	//free the hstmt handle
	FreeStmt(SQL_CLOSE);

} // TestBindParam()






//-----------------------------------------------------------------------
//    Function: TestFetchScroll
//
//		Test the SQLFetchScroll for SDK 3.0
//-----------------------------------------------------------------------

void PASCAL TestFetchScroll(QTSTRUCT *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szSave[MAX_QUERY_SIZE];
	DWORD		dwLen=0;
	SDWORD	cbValue=0;

	/* check if SQLGetFunctions says your API is supported */
	if(!Supported( SQL_API_SQLFETCHSCROLL))
	{
		/* Call your 3.0 API here and verify that the correct state is returned */
		rc = SQLFetchScroll(hstmt,SQL_FETCH_FIRST, 0);
		if(!FindError(SQL_HANDLE_STMT,szIM001))
			DISPLAYERROR(szSQLFETCHSCROLL, szNotSupported);
		RETCHECK(SQL_ERROR, rc, szSQLFETCHSCROLL);
	}
	else
	{
		ResetHstmt(&hstmt);

		/* Valid Testing of SQLFetchScroll */
		SelectFromTable(lpqt);

		rc = SQLBindCol(hstmt, 1, SQL_C_TCHAR, lpqt->sz, MAX_BIND_ARRAY_ELEMENT,
			&cbValue);
		RETCHECK(SQL_SUCCESS, rc, szSQLBINDCOL);

		rc = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 3);
		RETCHECK(SQL_SUCCESS, rc, szSQLFETCHSCROLL);
		lstrcpy(szSave,lpqt->sz);

		rc = SQLFetchScroll(hstmt, SQL_FETCH_PRIOR, 1);
		RETCHECK(SQL_ERROR, rc, szSQLFETCHSCROLL);

		rc = SQLFetchScroll(hstmt, SQL_FETCH_FIRST, 0);
		RETCHECK(SQL_ERROR, rc, szSQLFETCHSCROLL);

		rc = SQLFetchScroll(hstmt, SQL_FETCH_LAST, 0);
		RETCHECK(SQL_ERROR, rc, szSQLFETCHSCROLL);

		rc = SQLFreeStmt(hstmt, SQL_CLOSE);
		RETCHECK(SQL_SUCCESS, rc, szSQLFREESTMT);

	}

	//free the hstmt handle
	FreeStmt(SQL_CLOSE);

} // TestFetchScroll()



/*-----------------------------------------------------------------------*/
/*      Function:               qtDisplayError                           */
/*-----------------------------------------------------------------------*/

void  PASCAL qtDisplayError(LPTSTR szFunction, LPTSTR buf, LPTSTR szFile, int iLine)
{
	TCHAR szTmp[MAX_STRING_SIZE];

	szWrite(TEXT(""), TRUE);
	szWrite(TEXT("\t\t\t"), FALSE);
	szWrite(szFunction, FALSE);
	szWrite(TEXT("  FAILED"), TRUE);
	szWrite(TEXT("\t\t\t"), FALSE);
	szWrite(buf, TRUE);

	wsprintf(szTmp,TEXT("\t\t\t%s: %d"), szFile, iLine);
	szWrite(szTmp, TRUE);

	szWrite(TEXT("\t\t\t  --------  "), TRUE);

	lpSI->failed++;

	return;
}


/*-----------------------------------------------------------------------*/
/*      Function:               qtMakeData                               */
/*-----------------------------------------------------------------------*/

LPTSTR  PASCAL qtMakeData(int row, int col,FIELDINFO  *rgField, LPTSTR buf)
{
	if(rgField->fAutoUpdate)
		return NULL;

	if(rgField->nullable && (row==col)) 
		{
		lstrcpy(buf,TEXT(""));
		return buf;
		}

	switch(rgField->wSQLType) {
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
		case SQL_BINARY:
		case SQL_VARBINARY:
		case SQL_LONGVARBINARY:
			if(rgField->precision < 4)
				wsprintf(buf,TEXT("%d"), 1);
			else
				wsprintf(buf,TEXT("%d%d"), row, row);
			break;
		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_REAL:
		case SQL_FLOAT:
		case SQL_DOUBLE:
			if(row == 2 && !rgField->fUnsigned) /* make the second row negative for variety */
				wsprintf(buf,TEXT("-%d.%d"), row, row);
			else
				wsprintf(buf,TEXT("%d.%d"), row, row);
			break;

		case SQL_BIT:
			if(row > 2)
				wsprintf(buf,TEXT("%d"), 1);
			else
				wsprintf(buf,TEXT("%d"), 0);

			break;

		case SQL_SMALLINT:
		case SQL_INTEGER:
		case SQL_TINYINT:
		case SQL_BIGINT:
			if(row == 2 && !rgField->fUnsigned) /* make the second row negative for variety */
				wsprintf(buf,TEXT("-%d"), row);
			else
				wsprintf(buf,TEXT("%d"), row);
			break;

		case SQL_TIME:
		case SQL_TYPE_TIME:
			wsprintf(buf,TEXT("{t '01:%02d:%02d'}"), row % 60, row % 60);
			break;
		case SQL_DATE:
		case SQL_TYPE_DATE:
			wsprintf(buf,TEXT("{d '1994-%02d-%02d'}"), (row % 12) + 1, (row % 30) + 1);
			break;
		case SQL_TIMESTAMP:
		case SQL_TYPE_TIMESTAMP:
			wsprintf(buf,TEXT("{ts '1994-%02d-%02d 01:%02d:%02d'}"), (row % 12) + 1, (row % 30) + 1, row % 60, row % 60);
			break;
	}
	return buf;
}




/*-----------------------------------------------------------------------*/
/*      Function:               TestNumResCols                           */
/*-----------------------------------------------------------------------*/

VOID PASCAL TestNumResCols(SDWORD cColsSelected,QTSTRUCT *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	SWORD		wNum;

	SelectFromTable(lpqt);

	rc = SQLNumResultCols(hstmt, &wNum);
	RETCHECK(SQL_SUCCESS, rc,szSQLNUMRESULTCOLS);

	if(wNum != cColsSelected)
		DISPLAYERROR(szSQLNUMRESULTCOLS,TEXT("incorrect value returned"));

	FreeStmt(SQL_CLOSE);

} /* TestNumResCols() */



/*-----------------------------------------------------------------------*/
/*      Function:               TestNumResCols                           */
/*-----------------------------------------------------------------------*/

VOID PASCAL TestCursorName(QTSTRUCT *lpqt)
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szCursorName[MEDBUFF];
	SWORD		cb=0;

	SelectFromTable(lpqt);

	/* the cursor name should be created by the driver since one was	*/
	/* not specified																	*/

	rc = SQLGetCursorName(hstmt, szCursorName, MAX_STRING_SIZE, &cb);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETCURSORNAME);

	if(cb > MAX_STRING_SIZE)
	{
		DISPLAYERROR(szSQLGETCURSORNAME,TEXT("invalid cb"));
		cb = MAX_STRING_SIZE;
	}

	/* don't check the name itself, just make sure that	*/
	/*	something was returned 										*/
	if(!*szCursorName) 
		DISPLAYERROR(szSQLGETCURSORNAME,TEXT("no name returned"));

	FreeStmt(SQL_CLOSE);

} /* TestCursorName() */


//-----------------------------------------------------------------------
//      Function:               GetDMVersion
//-----------------------------------------------------------------------

UWORD PASCAL GetDMVersion()
{
	RETCODE	rc=SQL_SUCCESS;
	TCHAR		szNum[MAX_NUM_BUFFER];

	rc = SQLGetInfo(hdbc, SQL_ODBC_VER, &szNum, MAX_NUM_BUFFER, NULL);
	RETCHECK(SQL_SUCCESS, rc,szSQLGETINFO);
	
	return((UWORD)_ttoi(_tcstok(szNum,TEXT("."))));

} /* GetDMVersion() */


//-----------------------------------------------------------------------
//      Function:               DisplayTestName
//-----------------------------------------------------------------------

VOID PASCAL DisplayTestName(UWORD i)
{
	szWrite(szBLANKLINE,TRUE);
	szWrite(szTAB,FALSE);
	szWrite(iTestNames[i-1], TRUE);

} /* DisplayTestName() */



/***************************  External Interfaces  *************************/
/*  These functions are called by Gator to envoke the tests.               */
/***************************************************************************/

BOOL CALLBACK AutoTestName(LPTSTR szName, UINT  * cbTestCases)
{
	static TCHAR szTestName[] = TEXT("Quick Test");
	
	lstrcpy(szName, szTestName);
	
	*cbTestCases = sizeof(iTestNames)/sizeof(LPTSTR);

	return TRUE;
}

//-----------------------------------------------------------------------
//      Function:               AutoTestDesc
//      Purpose:                        Provides gator with a list of tests which can be run.
//-----------------------------------------------------------------------
BOOL CALLBACK AutoTestDesc(UWORD iTest, LPTSTR szName, LPTSTR szDesc)
{
			
	UWORD len=0;

	if (iTest > (sizeof(iTestNames)/sizeof(LPTSTR)))
		return FALSE;

	if (szName)
     	lstrcpy(szName,iTestNames[iTest-1]);
	
	if (szDesc)
        lstrcpy(szDesc,TEXT(" "));
	
	return TRUE;

}

//-----------------------------------------------------------------------
//      Function:               AutoTestFunc
//-----------------------------------------------------------------------

void CALLBACK AutoTestFunc(lpSERVERINFO pTestSource)
{

	RETCODE			rc;
	UWORD				cTypes;
	UDWORD			dwLen;
	UWORD				fIndex;
	SDWORD			cColsSelected;
	FIELDINFO		*rgFields = (FIELDINFO  *)AllocateMemory(sizeof(FIELDINFO) * MAX_TYPES_SUPPORTED);
	QTSTRUCT			*lpqt = (QTSTRUCT  *)AllocateMemory(sizeof (QTSTRUCT));
	DSTRUCT			*lpd = (DSTRUCT  *)AllocateMemory(sizeof (DSTRUCT) * MAX_TYPES_SUPPORTED);
	UWORD				uDMVer;
	SDWORD			cbValue=0;
	TCHAR				szAPI[MEDBUFF];
	UWORD				i;
	TCHAR		szState[100]=TEXT(""),
				szErrMsg[XLARGEBUFF]=TEXT("");


	lpSI = pTestSource;
	lpSI->failed = 0;
	henv = NULL;
	hdbc = NULL;
	hstmt = NULL;
	hdesc = NULL;

	if(lpSI->szValidServer0)
	{
		if (Connect(lpSI,lpqt))
			goto ErrorRet;
	}
	else 
	{
		henv = lpSI->henv;
		hdbc = lpSI->hdbc;
		
		rc = SQLSetConnectOption(hdbc,SQL_ODBC_CURSORS,dwLen);
		lstrcpy(szAPI,szSQLSETCONNECTOPTION);

		if(RETCHECK(SQL_SUCCESS, rc,szAPI))
			lpSI->vCursorLib = dwLen;
	}

 	uDMVer=GetDMVersion();

	fIndex=CheckConformanceLevel();

	fBindParameter=Supported(SQL_API_SQLBINDPARAMETER);
	fDiagRecSupported=Supported(SQL_API_SQLGETDIAGREC);
	fDiagFieldSupported=Supported(SQL_API_SQLGETDIAGFIELD);


	AllocHstmt();

	if (!(cTypes=GetTypeInfo(rgFields,lpqt)))
		goto ErrorRet;

	guwRowCount=cTypes+1;	// Extra row inserted with DAE.

	// cTypes=20;			  //DEBUG

	/* build create statement */
	if (BuildCreateStmt(lpqt,rgFields,cTypes))
		goto ErrorRet;

	/* put together the insert statement, and set the parameters   */
	/* parameters are only set the first time through, after which */
	/* the contents of the pointers is changed                     */
	if (BuildInsertStmt(lpqt, rgFields,cTypes,lpd,&cColsSelected,fBindParameter))
		goto ErrorRet;

	CreateParamQuery(lpqt,rgFields,cTypes);
	
	for(i=1;i <= (sizeof(iTestNames)/sizeof(LPTSTR));i++)
	{
		lpqt->sz[0] = TEXT('\0');

		if(GETBIT(pTestSource->rglMask,i))
		{
			/* Display current Test */
			DisplayTestName(i);

			switch(i)
			{
				case 1:
					TestConnectionOptions();
					break;
				case 2:
					TestStmtOptions();
					break;
				case 3:
					TestCursorName(lpqt);
					break;
				case 4:
					TestData(lpqt,rgFields,cTypes,lpd);
					break;
				case 5:
					TestNumResCols(cColsSelected,lpqt);
					break;
				case 6:
					TestMetaData(lpSI,lpqt,rgFields,cTypes);
					break;
				case 7:
					TestSearchedQuery(lpqt,rgFields,cTypes,lpd,fBindParameter);
					break;
				case 8:
					TestLargeQuery(lpqt,rgFields,cTypes,lpd);
					break;
				case 9:
					TestSQLTables(lpqt);
					break;
				case 10:
					TestSQLStatistics(lpqt,rgFields,cTypes,lpd,fIndex);
					break;
				case 11:
					TestSQLSpecialCols(lpqt);
					break;
				case 12:
					TestLikeQuery(lpqt,rgFields,cTypes,lpd);
					break;
				case 13:
					TestSQLForeignKeys(lpqt);
					break;
				case 14:
					TestSQLBrowseConnect(lpSI);
					break;
				case 15:
					TestSQLDataSources();
					break;
				case 16:
					TestSQLDrivers();
					break;
 				case 17:
					TestSQLMoreResults(lpqt);
					break;
 				case 18:
					TestSQLNativeSQL(lpqt);
					break;
				case 19:
					TestSQLDescribeParam(lpqt);
					break;
				case 20:
					TestSQLNumParams(lpqt);
					break;
				case 21:
					TestSQLParamOptions(lpqt);
					break;
				case 22:
					TestSQLPrimaryKeys(lpqt);
					break;
				case 23:
					TestSQLProcedures();
					break;
				case 24:
					TestSQLTablePrivileges();
					break;
				case 25:
					TestSQLColumnPrivileges(lpqt);
					break;
				case 26:
					TestSQLSetScrollOptions();
					break;
				case 27:
					TestExtendedFetch(lpqt,rgFields,cTypes);
					break;
				case 28:
					TestOJCap(lpqt);
					break;
				case 29:
					TestSQLSetConnectAttr();
					break;
				case 30:
					TestSQLSetStmtAttr();
					break;
				case 31:
					TestThreading(lpSI,lpqt,rgFields);
					break;
				case 32:
					TestGetDescField(lpqt);
					break;
				case 33:
					TestSetDescField(lpqt);
					break;
				case 34:
					TestGetDescRec(lpqt);
					break;
				case 35:
					TestSetDescRec(lpqt);
					break;
				case 36:
					TestCopyDesc(lpqt);
					break;
				case 37:
					TestDescDefaults(lpqt);
					break;
				case 38:
					TestUseDesc(lpqt, rgFields);
					break;
				case 39:
					TestEnvAttr();
					break;
				case 40:
					TestEndTran(lpqt,rgFields,cTypes,lpd);
					break;
				case 41:
					TestBindParam(lpqt,rgFields,cTypes,lpd);
					break;
				case 42:
					TestQuickRebind(lpqt,rgFields,cTypes,lpd);
					break;
				case 43:
					TestFetchScroll(lpqt);
					break;
				case 44:
					TestDiagRec();
					break;
				case 45:
					TestDiagField();
					break;
				case 46:
					TestMixedAnsiUnicode(lpqt);
					break;
	
			} /* switch(i) */

		} /* if(GETBIT(pTestSource->rglMask,i)) */
	
	}

	//the end of test cases for ODBC SDK 3.0

	/* finished testing, clean up */
	CleanUp(lpd,lpqt,rgFields,lpqt->szTableName,FALSE,lpSI->szValidServer0);

	szWrite(szBLANKLINE,TRUE);

	lpSI->cErrors = lpSI->failed;

	return;

ErrorRet:
	/* a failure in an ODBC function that prevents completion of the	*/
	/* test - for example, connect to the server 							*/

	szWrite(TEXT("\t\t *** Unrecoverable Quick Test FAILURE ***"), TRUE);

	/* finished testing, clean up */
	CleanUp(lpd,lpqt,rgFields,lpqt->szTableName,FALSE,lpSI->szValidServer0);

	lpSI->cErrors = ABORT;

	return;
}
