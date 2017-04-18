// --edkevent.h-----------------------------------------------------------------
//
// Header file for module containing event logging functions.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#if !defined(_EDKEVENT_H)
#define _EDKEVENT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//$--EDKEVENTCOUNT--------------------------------------------------------------
//  Structure to hold the counts of the number of each type of event that has 
//  been logged.
// -----------------------------------------------------------------------------
typedef struct _EDKEventCount {
	DWORD	cError;
	DWORD	cWarning;
	DWORD	cInformation;
} EDKEVENTCOUNT, *LPEDKEVENTCOUNT;


//$--HrEventOpenLog----------------------------------------------------------
//  Initialize event logging for the EDK.
// -----------------------------------------------------------------------------
HRESULT HrEventOpenLog(				// RETURNS: HRESULT
	IN LPSTR pszApplicationName,		// name of this application
	IN LPSTR pszExecutableName,		    // name of executable
    IN LPSTR pszEventMessageFile,       // name of event message file
    IN LPSTR pszParameterMessageFile,   // name of parameter message file
    IN LPSTR pszCategoryMessageFile,    // name of category message file
	OUT LPHANDLE phEventSourceOut);		// [returns event logging handle]

//$--HrEventUseExisting---------------------------------------------------
//  Initialize event logging for the EDK by connecting to an already open 
//  event log handle.  This allows EventLogMsg() to log events to a handle 
//  that was opened elsewhere.  Calling HrEventCloseLog() after calling 
//  this routine will do internal cleanup but will not close the event log 
//  handle.  One example of where this routine is useful is within a DLL 
//  that is called by EDK code in which event logging has already been 
//  initialized.
// -----------------------------------------------------------------------------
HRESULT HrEventUseExisting(		// RETURNS: HRESULT
	IN HANDLE hExistingEventSource);		// previously opened event log handle


//$--EventLogMsg----------------------------------------------------------------
//
//  EventLogMsgA -- byte string version
//  EventLogMsgW -- word string version
//
//  Log an event to the event log, and optionally, log the original error(s) 
//  that caused the event.  It has the following parameters:
//
//   DWORD    dwEvent
//   DWORD    cStrings
//  [LPSTR   pszString1]
//  [LPSTR   pszString2]
//  [...................]
//  [LPSTR   pszStringN]
//   DWORD    cErrorCodes
//  [DWORD    dwErrorCode1]
//  [DWORD    dwErrorCode2]
//  [.....................]
//  [DWORD    dwErrorCodeN]
//
//  Each of the above strings and error codes are used as parameters to the 
//  message in the order they appear.  This means that in event messages, 
//  all of the  error message replacement parameters must have higher numbers 
//  than all of the string replacement parameters.  For example:
//
//      EventLogMsg(
//          MYAPP_CANNOT_COPY_FILE, 
//          2, pszSourceFile, pszDestFile, 
//          1, dwError);
//
//  And the message would be defined as:
//
//      MessageId=
//      Severity=Error
//      Facility=Application
//      SymbolicName=MYAPP_CANNOT_COPY_FILE
//      Language=English
//      Cannot copy file from %1 to %2 due to the following error:%n%3.
//      .
//
//  Note: This routine preserves the last error value returned by 
//        GetLastError().
//
// -----------------------------------------------------------------------------

//$--EventLogMsgA---------------------------------------------------------------
//  Byte string version of EventLogMsg().
//
//  IMPORTANT!!! The error code count [and error code list] is REQUIRED after 
//  the text string count [and text string list].  Failure to include the 
//  error code argument(s) may cause unexpected results.
// -----------------------------------------------------------------------------
VOID EventLogMsgA(						// RETURNS: nothing
	IN DWORD dwEvent,					// error code of event to log
	IN DWORD cStrings,					// number of text string parameters
	IN ...								// text string parameters
//	IN DWORD cErrors,					// number of error code parameters
//	IN ...								// error code parameters
);

//$--EventLogMsgW---------------------------------------------------------------
//  Word string version of EventLogMsg().
//
//  IMPORTANT!!! The error code count [and error code list] is REQUIRED after 
//  the text string count [and text string list].  Failure to include the 
//  error code argument(s) may cause unexpected results.
// -----------------------------------------------------------------------------
VOID EventLogMsgW(						// RETURNS: nothing
	IN DWORD dwEvent,					// error code of event to log
	IN DWORD cStrings,					// number of text string parameters
	IN ...								// text string parameters
//	IN DWORD cErrors,					// number of error code parameters
//	IN ...								// error code parameters
);

#ifdef UNICODE
#define EventLogMsg  EventLogMsgW
#else
#define EventLogMsg  EventLogMsgA
#endif // !UNICODE


//$--HrEventGetCounts--------------------------------------------------------
//  Returns the number of Error, Warning, and Information events logged (by the 
//  current executable).
// -----------------------------------------------------------------------------
HRESULT HrEventGetCounts(			// RETURNS: HRESULT
	OUT LPEDKEVENTCOUNT lpsEventCount);	// structure to return event counts


//$--HrEventCloseLog---------------------------------------------------------
//  Shut down event logging for the EDK.
// -----------------------------------------------------------------------------
HRESULT HrEventCloseLog();			// RETURNS: HRESULT

// $--HrEventGetHandle------------------------------------------------------
//
// DESCRIPTION: Retrieve event handle for this executable.
//
// OUTPUT:  phEventLog   --  event log handle pointer
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// Notes:  
//
// 1) The event handle returned will be NULL if there is
// no open event log.
//
// 2) DLLs may not call this function to retrieve the event handle
// which their parent executable set.  If the parent executable sets
// an event handle, then it must pass the event handle to the DLL.
//
// ----------------------------------------------------------------------------
HRESULT HrEventGetHandle(
        IN HANDLE * phEventLog);       // event log handle pointer

#ifdef __cplusplus
}   // end extern "C"
#endif // __cplusplus

#endif
