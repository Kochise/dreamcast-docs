//*---------------------------------------------------------------------------------
//|  Title:		AUTOTEST.H
//|
//|	This file contains constants and prototypes required to compile an 
//|	Auto Test DLL.
//*---------------------------------------------------------------------------------
#ifndef AUTOTEST_DEFS
#define AUTOTEST_DEFS

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "sql.h"
#include "sqlext.h"

#ifdef __cplusplus
extern "C" { 
#endif	/* __cplusplus */


extern HINSTANCE	hLoadedInst;


//----------------------------------------------------------------------------------
//		Defines and Macros
//----------------------------------------------------------------------------------
#define TEST_ABORTED						(-1)

#define AUTO_MAX_TEST_NAME				35
#define AUTO_MAX_TESTCASE_NAME		35
#define AUTO_MAX_TESTDESC_NAME		75

#define MAXFLUSH		 	 			  300
#define MAX_USER_INFO	  				50
#define MAX_KEYWORD_LEN	 			  149

#ifdef WIN32
#define EXTFUNCDECL						_stdcall
#define EXTFUN								_stdcall
#else
#define EXTFUNCDECL
#define EXTFUN								__export FAR PASCAL
#endif


#define InitTest(lps)															\
{ 	lps->cErrors=0; }
#define AbortTest(lps)															\
{ lps->cErrors=TEST_ABORTED; }

#define     AllocateMemory(cb)	\
                (GlobalLock(GlobalAlloc((GMEM_FIXED | GMEM_ZEROINIT), (cb))))
#ifdef WIN32
#define     ReleaseMemory(lp)		\
					 (GlobalUnlock((HGLOBAL)GlobalHandle(lp)), (BOOL)GlobalFree((HGLOBAL)GlobalHandle(lp)))
#else
#define     ReleaseMemory(lp)		\
                (GlobalUnlock(((HGLOBAL)LOWORD(GlobalHandle(SELECTOROF(lp))))), \
                (BOOL)GlobalFree(((HGLOBAL)LOWORD(GlobalHandle(SELECTOROF(lp))))))
#endif

#define NumItems(s) (sizeof(s) / sizeof(s[0]))

// Following will access bit number pos in a bit array and return
//		TRUE if it is set, FALSE if it is not
#define CQBITS (sizeof(UINT) * 8)
#define getqbit(lpa, pos)	\
	(lpa[((pos) / CQBITS)] & (1 << ((pos) - (CQBITS * ((pos) / CQBITS)))))
#define GETBIT(p1,p2) getqbit(p1,(p2)-1)



//
// This structure contains the information found in the .INI file for a 
//	data source.  The filled out structure is in turn passed to AutoTestFunc
//	to drive the individual tests.
//
typedef struct tagSERVERINFO {
	HWND	 		hwnd;								// Output edit window
	TCHAR   		szLogFile[_MAX_PATH];		// Output log file
	HENV 			henv;								// .EXE's henv
	HDBC 			hdbc;								// .EXE's hdbc
	HSTMT			hstmt;							// .EXE's hstmt

	// The following items are gathered from the .INI file and may be defined
	//		via the "Manage Test Sources" menu item from ODBC Test
	TCHAR 			szSource[SQL_MAX_DSN_LENGTH+1];
	TCHAR 			szValidServer0[SQL_MAX_DSN_LENGTH+1];
	TCHAR 			szValidLogin0[MAX_USER_INFO+1];
	TCHAR 			szValidPassword0[MAX_USER_INFO+1];
	TCHAR			szKeywords[MAX_KEYWORD_LEN+1];

	// Following are used for run-time
	UINT FAR * 	rglMask;  						// Run test mask
	int  			failed;							// Track failures on a test case basis
	int  			cErrors;							// Count of errors
	BOOL 			fDebug;							// TRUE if debugging is to be enabled
	BOOL 			fScreen;							// TRUE if test output goes to screen
	BOOL 			fLog;								// TRUE if test output goes to log
	BOOL 			fIsolate;						// TRUE to isolate output
	UDWORD		vCursorLib;						// Value for SQL_ODBC_CURSOR on SQLSetConnectOption
	HINSTANCE	hLoadedInst;					// Instance handle of loaded test

	// Following are used for buffering output to edit window
	TCHAR			szBuff[MAXFLUSH];				// Hold temporary results
	UINT			cBuff;							// Number of TCHARs in szBuff
	} SERVERINFO;
typedef SERVERINFO FAR * lpSERVERINFO;


//----------------------------------------------------------------------------------
// Function prototypes
//----------------------------------------------------------------------------------
BOOL EXTFUNCDECL FAR szLogPrintf(lpSERVERINFO lps, BOOL fForce, LPTSTR szFmt, ...);
int EXTFUNCDECL FAR szMessageBox(HWND hwnd, UINT style, LPTSTR szTitle, LPTSTR szFmt, ...);
LPTSTR EXTFUN GetRCString(HINSTANCE hInst, LPTSTR buf, int cbbuf, UINT ids);


#ifdef __cplusplus
}
#endif

#endif


