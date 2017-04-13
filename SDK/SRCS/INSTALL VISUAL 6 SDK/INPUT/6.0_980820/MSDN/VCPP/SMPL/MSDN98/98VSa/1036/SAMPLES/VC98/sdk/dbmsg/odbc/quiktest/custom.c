//*---------------------------------------------------------------------------------
//| Custom Auto Test DLL
//|
//| Title:	CUSTOM.C
//|
//| Purpose:
//|	This sample Auto Test DLL shows how an ODBC auto test may be written and
//|	subsequently run via the ODBC Test application.  To use this DLL:
//|		1) Compile the source code via the BUILD.EXE program
//|					CUSTOM.C		This shource file with test code
//|					CUSTOM.H		Include files with defines, macros, and prototypes
//|					CUSTOM.RC	Resource file for string tables
//|			(Note that .H and .RC files are optional in for an Auto Test)
//|		2) Start the ODBC Test application
//|		3) If you have not done so, choose Tools, Manage Test Sources and define
//|				a test source to run against
//|		4) Choose Tools, Manage Tests and add the CUSTOM.DLL created in step 1
//|				to the list of installed test DLLs
//|		5) Choose Tools, Run Tests and select "Custom Auto Test" and your Test Source
//|				from step #3
//|	For more details, please see the SDK documentation.
//*---------------------------------------------------------------------------------
#include "autotest.h"
#include "custom.h"


//----------------------------------------------------------------------------------
//		Defines and macros
//----------------------------------------------------------------------------------
typedef SWORD (FAR PASCAL *TESTCASEFUNC)(HENV FAR *, HDBC FAR *, HSTMT FAR *, lpSERVERINFO);

#define CHECKTEST(lps, exprc, actrc, func) 			\
{                                                  \
	if(!CheckTest(lps, exprc, actrc, (LPSTR)func))  \
		return TEST_ABORTED;                         \
}
#define CHECKERRS(sErr)										\
	if(!sErr) szLogPrintf(lpSrvr, FALSE, "\t\tPassed\r\n\r\n"); \
	else szLogPrintf(lpSrvr, FALSE, "\t\t%d errors\r\n\r\n", sErr);



//----------------------------------------------------------------------------------
//		Local function prototypes
//----------------------------------------------------------------------------------
SWORD FAR PASCAL DoHelloWorld(HENV FAR * phenv, HDBC FAR * phdbc,
				HSTMT FAR * phstmt, lpSERVERINFO lpSrvr);
SWORD FAR PASCAL DoDisplayInfoDesc(HENV FAR * phenv, HDBC FAR * phdbc,
				HSTMT FAR * phstmt, lpSERVERINFO lpSrvr);
SWORD FAR PASCAL DoSimpleConnect(HENV FAR * phenv, HDBC FAR * phdbc,
				HSTMT FAR * phstmt, lpSERVERINFO lpSrvr);
BOOL FAR PASCAL CheckTest(lpSERVERINFO lps, RETCODE exprc, RETCODE actrc,
				LPSTR	szFuncName);


//
// This structure is declared to describe the test cases and descriptions
//		that this auto test supports.  Note that the strings are stored in
//		the resource fork, but could have been hard coded.
//
struct {
	UINT					uiName;			// Test case name
	UINT					uiDesc;			// Test case description
	TESTCASEFUNC		lpTestFunc;		// Pointer to function to implement test
	} TestCases[] = {
// szName					szDesc						lpTestFunc
// --------------------	-----------------------	------------------------
	idsHelloWorld,			idsHelloWorldDesc,		DoHelloWorld,
	idsDisplayInfo,		idsDisplayInfoDesc,		DoDisplayInfoDesc,
	idsSimpleConnect,		idsSimpleConnectDesc,	DoSimpleConnect,
	};



//**************************************************************************
//***************************  External Interfaces  ************************
//*  These functions are called by ODBC Test to gather run-time information
//**************************************************************************


//*---------------------------------------------------------------------------------
//| AutoTestName:
//|	This function is called to give the name of the auto test (which cannot
//|	exceed AUTO_MAX_TEST_NAME) as well as the number of test cases which
//|	are implemented in this test DLL.
//| Parms:	
//|	szName					The name to be displayed
//|	pcbTestCases			Pointer to count of test cases
//| Returns:
//|	TRUE if successful (pcbTestCases set), FALSE for error
//*---------------------------------------------------------------------------------
BOOL EXTFUN AutoTestName(LPSTR szName, UINT FAR * pcbTestCases)
{
	GetRCString(hLoadedInst, szName, AUTO_MAX_TEST_NAME, idsTestName);
	*pcbTestCases = NumItems(TestCases);

   return TRUE;
}


//*---------------------------------------------------------------------------------
//| AutoTestDesc:
//|	This function is called by ODBC Test when a description of a specific
//|	test case is required.  The returned name must be no larger than
//|	AUTO_MAX_TESTCASE_NAME including the NULL terminator.  The returned
//|	description must be no larger than AUTO_MAX_TESTDESC_NAME including the
//|	NULL.  iTest will be 1-based index of the test required.
//|
//|	Note that iTest will start at 1 and will go to the number of
//|		test cases as specified by the AutoTestName function.
//|
//| Parms:	
//|	iTest						1-based index of test case required
//|	szName					The name of the test case
//|	szDesc					A description of the test case
//| Returns:
//|	TRUE if successful, FALSE for error
//*---------------------------------------------------------------------------------
BOOL EXTFUN AutoTestDesc(UWORD iTest, LPSTR szName, LPSTR szDesc)
{
	// Extra protection should AutoTestName return invalid pcbTestCases
	if(iTest > NumItems(TestCases))
		return FALSE;
		
	// Use GetRCString to retrieve resource string directly into return
	//		values
	GetRCString(hLoadedInst, szName, 
					AUTO_MAX_TESTCASE_NAME, TestCases[(iTest-1)].uiName);
	GetRCString(hLoadedInst, szDesc, 
					AUTO_MAX_TESTDESC_NAME, TestCases[(iTest-1)].uiDesc);

   return TRUE;
}
 
 
//*---------------------------------------------------------------------------------
//| AutoTestFunc:
//|	This function is called to execute a test case selected by the user for
//|	execution.  The lpSrvr structure contains the information required for
//|	connected (as defined in the chosen Test Source), as well as other
//|	usefull information.  See the AUTOTEST.H file for the structure
//|	declaration.
//|
//|	Use the GETBIT macro to determine which test should be executed.
//|
//| Parms:	
//|	lpSrvr					Information required for running the test
//| Returns:
//|	Nothing
//*---------------------------------------------------------------------------------
void EXTFUN AutoTestFunc(lpSERVERINFO lpSrvr)
{
	HENV 		henv=NULL;
	HDBC 		hdbc=NULL;
	HSTMT 	hstmt0=NULL;
	int		iDex;
	SWORD		cErrCnt;										// Count errors
	char		szName[AUTO_MAX_TESTCASE_NAME+6];	// Room for NULL and \r\n


	// Sets the error count to 0
	InitTest(lpSrvr);

	// Loop through the count of test cases looking for set bits via GETBIT.
	//		When a bit is set, that test is to be run.  We've stored the
	//		function address which will implement the test, so simply call it.
	for(iDex=1;  iDex<=NumItems(TestCases);  iDex++)
		if(GETBIT(lpSrvr->rglMask, iDex)) {
			// Print out title of test
			GetRCString(hLoadedInst, szName, 
					AUTO_MAX_TESTCASE_NAME, TestCases[(iDex-1)].uiName);
			szLogPrintf(lpSrvr, FALSE, "%s:\r\n", (LPSTR)szName);

			// Call the test case and add errors
			cErrCnt = 
				(*TestCases[(iDex-1)].lpTestFunc)(&henv, &hdbc, &hstmt0, lpSrvr);
			if(cErrCnt != TEST_ABORTED)
				lpSrvr->cErrors += cErrCnt;
			else
				goto abort;
			}
	return;


	// When a test must abort, the test case should call the AbortTest
	//		macro which sets lpSrvr->cErrors to TEST_ABORTED.
abort:
	return;
}
 





//**************************************************************************
//*****************************  Test Cases  *******************************
//*  The following functions implement the tests
//**************************************************************************

//*---------------------------------------------------------------------------------
//| DoHelloWord:
//|	This is a simple test which uses the szLogPrintf and szMessageBox
//|	functions defined in GATORTST.DLL.
//|
//|	Note that this test also simulates an error by returning a count
//|	of 1.  This value is then totaled by ODBC Test and displayed as
//|	part of the grand total.
//|
//| Returns:
//|	Number of Errors or TEST_ABORTED
//*---------------------------------------------------------------------------------
SWORD FAR PASCAL DoHelloWorld(HENV FAR * phenv, HDBC FAR * phdbc,
				HSTMT FAR * phstmt, lpSERVERINFO lpSrvr)
{
	SWORD		sErr=1;						// Pretend there was 1 error

	// The szMessageBox function will display a formatted message via the
	//		Windows MessageBox function.  This function should not be used
	//		for standard testing since a good test will run unattended.
	szMessageBox(lpSrvr->hwnd, 
				MB_ICONINFORMATION | MB_OK,
				"Hello World",
				"This is a sample message.");
				
	// The szLogPrintf function is preferred for output operations.  It will
	//		format your string using wvsprintf (which has a limit of 2000 characters)
	//		and log the result both to the output window and to a file per
	//		user instructions.
	szLogPrintf(lpSrvr, FALSE, "\tHello World!!\r\n");


	// check for errors
	CHECKERRS(sErr);

	
	return sErr;
}


//*---------------------------------------------------------------------------------
//| DoDisplayInfoDesc:
//|	This test case will use the szLogPrintf function to dump the contents
//|	of the lpSrvr structure.
//|
//| Returns:
//|	Number of Errors or TEST_ABORTED
//*---------------------------------------------------------------------------------
SWORD FAR PASCAL DoDisplayInfoDesc(HENV FAR * phenv, HDBC FAR * phdbc,
				HSTMT FAR * phstmt, lpSERVERINFO lpSrvr)
{
	SWORD		sErr=0;

#ifndef WIN32
#define szAddress "%04X:%04X\r\n"
#else
#define szAddress "%08X\r\n"
#endif

	// The hwnd parameter is the window of style "edit" which is used for output.
	//	The szLogFile parameter is used for file logging of output.
	szLogPrintf(lpSrvr, FALSE,
				"\thwnd:\t\t\t\t\t\t\t%04X\r\n", lpSrvr->hwnd);
	szLogPrintf(lpSrvr, FALSE,
				"\tszLogFile:\t\t\t\t%s\r\n", (LPSTR)lpSrvr->szLogFile);

	// Print out address information.  Note that szAddress is conditionaly compiled
	//		to handle 16 and 32-bit.  It will be concatenated to the format string
	//		by the compiler to create a file platform correct string.
	szLogPrintf(lpSrvr, FALSE,
				"\thenv:\t\t\t\t\t\t\t" szAddress, 
#ifndef WIN32
				HIWORD(lpSrvr->henv), LOWORD(lpSrvr->henv));
#else
				lpSrvr->henv);
#endif
	szLogPrintf(lpSrvr, FALSE,
				"\thdbc:\t\t\t\t\t\t\t" szAddress, 
#ifndef WIN32
				HIWORD(lpSrvr->hdbc), LOWORD(lpSrvr->hdbc));
#else
				lpSrvr->hdbc);
#endif
	szLogPrintf(lpSrvr, FALSE,
				"\thstmt:\t\t\t\t\t\t\t" szAddress, 
#ifndef WIN32
				HIWORD(lpSrvr->hstmt), LOWORD(lpSrvr->hstmt));
#else
				lpSrvr->hstmt);
#endif


	// The following are defined via the Tools, Manage Test Sources dialog in
	//		the ODBC Test application.
	szLogPrintf(lpSrvr, FALSE,
				"\tszSource:\t\t\t\t\t%s\r\n", (LPSTR)lpSrvr->szSource);
	szLogPrintf(lpSrvr, FALSE,
				"\tszValidServer0:\t\t\t\t\t\t%s\r\n", (LPSTR)lpSrvr->szValidServer0);
	szLogPrintf(lpSrvr, FALSE,
				"\tszValidLogin0:\t\t\t\t\t\t%s\r\n", (LPSTR)lpSrvr->szValidLogin0);
	szLogPrintf(lpSrvr, FALSE,
				"\tszValidPassword0:\t\t\t%s\r\n", (LPSTR)lpSrvr->szValidPassword0);
	szLogPrintf(lpSrvr, FALSE,
				"\tszKeywords:\t\t\t%s\r\n", (LPSTR)lpSrvr->szKeywords);

	// The following elements describe the run-time environment	
	szLogPrintf(lpSrvr, FALSE,
				"\tcErrors:\t\t\t\t\t\t%d\r\n", (LPSTR)lpSrvr->cErrors);
	szLogPrintf(lpSrvr, FALSE,
				"\tfDebug:\t\t\t\t\t\t%d\r\n", (LPSTR)lpSrvr->fDebug);
	szLogPrintf(lpSrvr, FALSE,
				"\tfScreen:\t\t\t\t\t\t%d\r\n", (LPSTR)lpSrvr->fScreen);
	szLogPrintf(lpSrvr, FALSE,
				"\tfLog:\t\t\t\t\t\t\t\t%d\r\n", (LPSTR)lpSrvr->fLog);
	szLogPrintf(lpSrvr, FALSE,
				"\tfIsolate:\t\t\t\t\t\t%d\r\n", (LPSTR)lpSrvr->fIsolate);
	szLogPrintf(lpSrvr, FALSE,
				"\tvCursorLib:\t\t\t\t%lu\r\n", (LPSTR)lpSrvr->vCursorLib);
	szLogPrintf(lpSrvr, FALSE,
				"\thLoadedInst:\t\t\t%04X\r\n", (LPSTR)lpSrvr->hLoadedInst);
	
	// check for errors
	CHECKERRS(sErr);

	return sErr;
}


//*---------------------------------------------------------------------------------
//| DoSimpleConnect:
//|	This test case will use the information in SERVERINFO to make a connection
//|		to the chosen test source.
//|
//| Returns:
//|	Number of Errors or TEST_ABORTED
//*---------------------------------------------------------------------------------
SWORD FAR PASCAL DoSimpleConnect(HENV FAR * phenv, HDBC FAR * phdbc,
				HSTMT FAR * phstmt, lpSERVERINFO lpSrvr)
{
	RETCODE			rc;
	SWORD				sErr=0;

	// This test will assume that the ODBC handles passed in
	//		are NULL.  One could have this function do a connection
	//		and pass the handles to other test functions.
	rc = SQLAllocEnv(phenv);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLAllocEnv");
	
	rc = SQLAllocConnect(*phenv, phdbc);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLAllocConnect");
	
	rc = SQLConnect(*phdbc, lpSrvr->szValidServer0, SQL_NTS,
									lpSrvr->szValidLogin0, SQL_NTS,
									lpSrvr->szValidPassword0, SQL_NTS);
	CHECKTEST(lpSrvr,
			(RETCODE)((rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
						? rc : SQL_SUCCESS),
			rc, "SQLConnect");
	
	rc = SQLAllocStmt(*phdbc, phstmt);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLAllocStmt");
	
	rc = SQLFreeStmt(*phstmt, SQL_DROP);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLFreeStmt");
	
	rc = SQLDisconnect(*phdbc);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLDisconnect");
	
	rc = SQLFreeConnect(*phdbc);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLFreeConnect");
	
	rc = SQLFreeEnv(*phenv);
	CHECKTEST(lpSrvr, SQL_SUCCESS, rc, "SQLFreeEnv");


	// check for errors
	CHECKERRS(sErr);

	
	return sErr;
}

 
 
 





//**************************************************************************
//*************************  Utility Functions  ****************************
//*  This section contains internal utility functions
//**************************************************************************




//*---------------------------------------------------------------------------------
//| CheckTest:
//|	This function will do a simple comparison of return codes and issue
//|	erros on failure.  Use the CHECKTEST macro to invoke.
//|
//| Returns:
//|	TRUE if the codes match, FALSE on error
//*---------------------------------------------------------------------------------
BOOL FAR PASCAL CheckTest(lpSERVERINFO lps, RETCODE exprc, RETCODE actrc,
				LPSTR	szFuncName)
{
	if(exprc != actrc) {
		szLogPrintf(lps, FALSE, "\t%s failed:\r\n", (LPSTR)szFuncName);
		szLogPrintf(lps, FALSE, "\t\tExpected: %d\r\n", exprc);
		szLogPrintf(lps, FALSE, "\t\tActual:   %d\r\n", actrc);
		return FALSE;
		}
	else
		return TRUE;
}

