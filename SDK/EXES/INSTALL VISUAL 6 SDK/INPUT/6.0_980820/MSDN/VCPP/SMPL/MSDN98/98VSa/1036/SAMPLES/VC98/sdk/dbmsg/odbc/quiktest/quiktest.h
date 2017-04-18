//****************************************************************************
//|   Title:   quiktest.h
//| 
//|   (c) Copyright 1991, 1992, 1993, 1994, 1995
//|       by Microsoft Corp.
//| 
//******************************************************************************
#ifndef quiktest_defs
#define quiktest_defs


/*-----------------------------------------------------------------------------------*/
/*	constants defines																						 */
/*-----------------------------------------------------------------------------------*/
#define MAX_QUERY_SIZE						2048
#define MAX_BIND_ELEMENTS					100
#define MAX_BIND_ARRAY_ELEMENT			MAX_QUERY_SIZE / MAX_BIND_ELEMENTS
#define MAX_STRING_SIZE						350		  // Increased from 255 due to overwrite
#define MAX_PARAM_SIZE						129
#define MAX_DATA_SIZE						45
#define MAX_COLUMN_LIST_SIZE				200
#define MAX_COLUMN_NAME_SIZE				100
#define MAX_INSERT_VALUES_SIZE			200
#define MAX_TYPES_SUPPORTED				25
#define MAX_TYPE_NAME						129
#define MAX_FIELD								40
#define MAX_PREFIX							129
#define MAX_SUFFIX							129
#define MAX_TABLE_NAME						60
#define MAX_NUM_BUFFER						60
#define MAX_ERROR_SIZE						200
#define MAX_ROW_ITEM_LIMIT					4

#define PREFIX_SIZE							3
#define IGNORED								999
#define TEST_CONNECT_OPTION				15
#define TEST_STMT_OPTION					300
#define SCALEDIFF								4
#define ABORT									-1
#define TYPE_PORTION							4
#define MAXUDWORD								((UDWORD)(-1))
#define MINSDWORD								(-(SDWORD)((MAXUDWORD / 2) + 1))
#define MAXSDWORD								((SDWORD)(MAXUDWORD / 2))

#define SMALLBUFF								100
#define MEDBUFF								200
#define LARGEBUFF								300
#define XLARGEBUFF							1024
#define STATE_SIZE							6
#define COMBINED_SIZE						MAX_ERROR_SIZE + 30

// Descriptor type defines
#define DESC_NONE					0		// No descriptor type
#define DESC_APD					1		// APD only
#define DESC_IPD					2		// IPD only
#define DESC_ARD					4		// ARD only
#define DESC_IRD					8		// IRD only
#define DESC_PD					DESC_APD|DESC_IPD		//	Parameter descriptors
#define DESC_RD					DESC_ARD|DESC_IRD		// Row descriptors
#define DESC_ID					DESC_IPD|DESC_IRD		// Implementation descriptors
#define DESC_AD					DESC_APD|DESC_ARD		// Application descriptors
#define DESC_MOST					DESC_AD|DESC_IPD	// This is the most common settable combination
#define DESC_ALL					DESC_APD|DESC_IPD|DESC_ARD|DESC_IRD	// All descriptor types

#define STATUS_ARRAY_SIZE		5		// Array size to use for row and param arrays
#define BIND_SIZE					12		// Bind type size value

/* NUM_THREAD is the number of threads that will be created for multi-thread test */
#define NUM_THREAD							5
#define NUM_QUIKREBIND_ROWSETS			6

/* BIND_PARM_OFFSET specifies the parameter base for DAE bindings. Either 0 */
/* or 1 based.  */
#define BIND_PARM_OFFSET					0

// COLNAME_START specifies the beginning number used in colnames, i.e. c00bit 
// vs. c01bit.
#define COLNAME_START						1
													
/*constants for Descriptor tests */
#define MAX_DESC_BUF							200
#define DESC_UPDATE_MODE_READ				0
#define DESC_UPDATE_MODE_WRITE			1
#define REC_COUNT_UNK						-1		// Unkown record count
// #define DESC_LOCATE_FAIL					-1

/* constants for TestBindParam */
#define INSERT_FAIL	  						-1

#define UNTOUCHED 0xCA

/*------------------------------------------------------------------------------------*/
/*	macros                                                                             */
/*------------------------------------------------------------------------------------*/

#define RC_SUCCESSFUL(rc)	((rc) == SQL_SUCCESS || \
    (rc) == SQL_SUCCESS_WITH_INFO)

#define RC_NOTSUCCESSFUL(rc) (!(RC_SUCCESSFUL(rc)))

#define RETCHECK(exp, rec, buf) ReturnCheck(exp, rec, buf, TEXT(__FILE__), __LINE__,FALSE)

#define ERRSHANDLE(type, handle, exp, rec, buf) ErrsHandle(type, handle, exp, rec, buf, TEXT(__FILE__), __LINE__,FALSE)

#define DIAGRETCHECK(exp, rec, buf) ReturnCheck(exp, rec, buf, TEXT(__FILE__), __LINE__,TRUE)

#define DISPLAYERROR(func, string) qtDisplayError(func, string, TEXT(__FILE__), __LINE__)

/*--------------------------------------------------------------------------------------*/
/*	Structure definitions																				    */
/*--------------------------------------------------------------------------------------*/

/* Number of Cols in result set of a query: */
UWORD cNumResSetCols;

/* used to store information from GetTypeInfo for table creation */
typedef struct FieldInfo {
		int iField;
		TCHAR szType[MAX_TYPE_NAME];
		TCHAR szFieldName[MAX_FIELD];
		SWORD  wSQLType;
		TCHAR szParams[MAX_PARAM_SIZE];
		TCHAR szLength[MAX_FIELD];
		TCHAR szPrefix[MAX_PREFIX];
		TCHAR szSuffix[MAX_SUFFIX];
		SDWORD precision;
		SWORD scale;
		SWORD nullable;
		UDWORD length;
		int   fAutoUpdate;
		SWORD fSearchable;
		SDWORD fUnsigned;
		SWORD autoinc;
		} FIELDINFO;



/* large buffers allocated as a global used for queries and other*/
/* returned information                                          */
typedef struct  tagQtStruct {
	TCHAR		buf[MAX_STRING_SIZE];
	TCHAR		sz[MAX_QUERY_SIZE];
	TCHAR		szParamQuery[MAX_QUERY_SIZE];
	TCHAR		szParam[MAX_PARAM_SIZE];
	TCHAR		szDataItem[MAX_DATA_SIZE];
	TCHAR		szTableName[MAX_TABLE_NAME];
	TCHAR		szColNames[MAX_COLUMN_LIST_SIZE];
	TCHAR		szColName[MAX_COLUMN_NAME_SIZE];
	TCHAR		szValues[MAX_INSERT_VALUES_SIZE];
}       QTSTRUCT;

/* the storage used for data retreived using bind/fetch sequence  */
/* and data for BindParameter                                     */
/* only cb and one of the types will be used for each entry       */
typedef struct tagDataStruct {
	SDWORD cb;
	TCHAR data[MAX_STRING_SIZE];
	SDWORD sdword;
	UDWORD udword;
	SWORD sword;
	UWORD uword;
	TCHAR	sChar;
	SQLTCHAR uChar;
	SDOUBLE sdouble;
	SFLOAT sfloat;
	TIME_STRUCT time;
	DATE_STRUCT date;
	TIMESTAMP_STRUCT timestamp;
} DSTRUCT;

/* These declarations used to reside locally, but the structures didn't get initialized correctly */
typedef struct SupportOptList {
	UDWORD Support;
	SDWORD Option;
	} SUPPORTOPTINFO;

typedef struct SupportConcurList {
	UDWORD Support;
	UWORD Option;
	} SUPPORTCONCURINFO;



/* Each thread will contain the following information */
typedef struct {
	HENV		henv;
	HDBC		hdbc;
	TCHAR		szTableName[MAX_TABLE_NAME];
	FIELDINFO rgFieldInfo;

} THREAD_STRUCT;


static union
{
	BYTE rgb[max(max(max(sizeof (HENV),sizeof (HDBC)),
					max(sizeof (HSTMT), sizeof (SQLHDESC))),sizeof (UDWORD))];
	SWORD sw;
	UWORD uw;
	SDWORD sdw;
	UDWORD udw;
	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	SQLHDESC hdesc;
} Untouched = {UNTOUCHED, UNTOUCHED, UNTOUCHED, UNTOUCHED};
														 


int  PASCAL ReturnCheck(RETCODE retExpected, RETCODE retReceived, LPTSTR szFunction, 
								LPTSTR szFile, int iLine,BOOL fDiag);
void PASCAL qtDisplayError(LPTSTR szFunction, LPTSTR buf, LPTSTR szFile, int iLine);
LPTSTR PASCAL qtMakeData(int row, int col,FIELDINFO * rgField, LPTSTR buf);

BOOL PASCAL CmpODBCtoCHAR(DSTRUCT * rgTestValue, TCHAR * szTrueValue,
	SWORD fSqlType, SWORD iResSetCol);

void* PASCAL CvtCHARtoODBC(void * odbcValue, TCHAR * buf, SWORD fSqlType)
{
	if(!buf)
		return NULL;

	switch (fSqlType) {
		case SQL_DATE: 
		case SQL_TYPE_DATE: 
		{
			TCHAR szDATEDELIM[] = TEXT("d{}'- ");
			TCHAR szTempBuff[30];
			LPTSTR   tmpstr=szTempBuff;
			_tcscpy((LPTSTR) szTempBuff, buf);

			((DATE_STRUCT *)odbcValue)->year = _ttoi(_tcstok(tmpstr, szDATEDELIM));
			((DATE_STRUCT *)odbcValue)->month = _ttoi(_tcstok(NULL, szDATEDELIM));
			((DATE_STRUCT *)odbcValue)->day = _ttoi(_tcstok(NULL, szDATEDELIM));
			break;
		}


		case SQL_TIME: 
		case SQL_TYPE_TIME: 
		{
			TCHAR szTIMEDELIM[] = TEXT("t{}': ");
			TCHAR szTempBuff[30];
			LPTSTR   tmpstr=szTempBuff;
			_tcscpy((LPTSTR) szTempBuff, buf);

			((TIME_STRUCT *)odbcValue)->hour = _ttoi(_tcstok(tmpstr, szTIMEDELIM));
			((TIME_STRUCT *)odbcValue)->minute = _ttoi(_tcstok(NULL, szTIMEDELIM));
			((TIME_STRUCT *)odbcValue)->second = _ttoi(_tcstok(NULL, szTIMEDELIM));

			break;
		}

		case SQL_TIMESTAMP:
		case SQL_TYPE_TIMESTAMP:
		{
			TCHAR szDATETIMEDELIM[] = TEXT("ts'{}-:. ");
			TCHAR szTempBuff[30];
			LPTSTR   tmpstr=szTempBuff;
			LPTSTR	endstr, frstr;
			_tcscpy((LPTSTR) szTempBuff, buf);

			/* First the date */
			((TIMESTAMP_STRUCT *)odbcValue)->year = _ttoi(_tcstok(tmpstr, szDATETIMEDELIM));
			((TIMESTAMP_STRUCT *)odbcValue)->month = _ttoi(_tcstok(NULL, szDATETIMEDELIM));
			((TIMESTAMP_STRUCT *)odbcValue)->day = _ttoi(_tcstok(NULL, szDATETIMEDELIM));
			/* Then the complete time */
			((TIMESTAMP_STRUCT *)odbcValue)->hour = _ttoi(_tcstok(NULL, szDATETIMEDELIM));
			((TIMESTAMP_STRUCT *)odbcValue)->minute = _ttoi(_tcstok(NULL, szDATETIMEDELIM));
			((TIMESTAMP_STRUCT *)odbcValue)->second = _ttoi(_tcstok(NULL, szDATETIMEDELIM));
			if(frstr = _tcstok(NULL, szDATETIMEDELIM))
				((TIMESTAMP_STRUCT *)odbcValue)->fraction = (_tcstoul(frstr, &endstr, 10) * 1000000);
			else
				((TIMESTAMP_STRUCT *)odbcValue)->fraction = 0;

			break;
		}

	}
	return odbcValue;
}


/* Compares the value stored at location (row,col) in the array of 
 * DSTRUCT's with the value created by qtMakeData							*/
BOOL PASCAL CmpODBCtoCHAR(DSTRUCT * rgTestValue, TCHAR * szTrueValue,
	SWORD fSqlType, SWORD iCol)
{
	BOOL fTestPass=TRUE;
	SWORD test1,test2;
	TCHAR	*pStop=NULL;

	switch (fSqlType) {
		case SQL_BIGINT:
		case SQL_INTEGER:
			if(_ttoi(szTrueValue) == (int)rgTestValue[iCol].sdword) 
				return TRUE;
			return FALSE;

		case SQL_DECIMAL:
		case SQL_NUMERIC:
				return  (_tcstod(szTrueValue,&pStop) == 
					(float)_tcstod(rgTestValue[iCol].data,&pStop));
		case SQL_TINYINT:
		case SQL_SMALLINT:
			if(_ttoi(szTrueValue) == (int)rgTestValue[iCol].sword)
				return TRUE;
			return FALSE;

		case SQL_FLOAT:
		case SQL_DOUBLE: 
				return  (_tcstod(szTrueValue,&pStop) == (float)rgTestValue[iCol].sdouble);

		case SQL_REAL:
				/* Need to account for round-off errors in _tcstod conversions: */
				test1 = (SWORD)(1000*_tcstod(szTrueValue,&pStop));
				test1 = (SWORD)((test1>0) ? (test1+5)/10 : (test1-5)/10);
				test2 = (SWORD)(1000*rgTestValue[iCol].sfloat);
				test2 = (SWORD)((test2>0) ? (test2+5)/10 : (test2-5)/10);
				return  (test1 == test2);

		case SQL_TIMESTAMP: 
		case SQL_TYPE_TIMESTAMP: 
		{
			TIMESTAMP_STRUCT tss;
			CvtCHARtoODBC(&tss, szTrueValue, SQL_TYPE_TIMESTAMP);

			fTestPass= ((rgTestValue[iCol].timestamp.month == tss.month)
				&& (rgTestValue[iCol].timestamp.day == tss.day)
				&& (rgTestValue[iCol].timestamp.year == tss.year)
				&& (rgTestValue[iCol].timestamp.hour == tss.hour)
				&& (rgTestValue[iCol].timestamp.minute == tss.minute)
				&& (rgTestValue[iCol].timestamp.fraction ==
					tss.fraction));
			/* Seconds value is zero for small timestamp, so to keep it from always failing... */
			if(0 != rgTestValue[iCol].timestamp.second)
				fTestPass= (fTestPass && rgTestValue[iCol].timestamp.second == tss.second);
			return fTestPass;
		}

		case SQL_TIME: 
		case SQL_TYPE_TIME: 
		{
			TIME_STRUCT tss;

			CvtCHARtoODBC(&tss, szTrueValue, SQL_TYPE_TIME);
			fTestPass=  ((rgTestValue[iCol].time.hour == tss.hour)
				&& (rgTestValue[iCol].time.minute == tss.minute));
			/* Seconds value is zero for small timestamp, so to keep it from always failing... */
			if(0 != rgTestValue[iCol].time.second)
				fTestPass= (fTestPass && rgTestValue[iCol].time.second == tss.second);
			return fTestPass;
		}

		case SQL_DATE: 
		case SQL_TYPE_DATE: 
		{
			DATE_STRUCT tss;
			CvtCHARtoODBC(&tss, szTrueValue, SQL_TYPE_DATE);

			return ((rgTestValue[iCol].date.month == tss.month)
				&& (rgTestValue[iCol].date.day == tss.day)
				&& (rgTestValue[iCol].date.year == tss.year));
		}

 		case SQL_BIT: 
 		case SQL_CHAR: 
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
		case SQL_BINARY:								  
		case SQL_VARBINARY:					  
		case SQL_LONGVARBINARY: 
		default:
			return !(_tcsncmp(szTrueValue, rgTestValue[iCol].data, 
				_tcslen(szTrueValue)));

	}
}


#endif 												
														
														
														
														