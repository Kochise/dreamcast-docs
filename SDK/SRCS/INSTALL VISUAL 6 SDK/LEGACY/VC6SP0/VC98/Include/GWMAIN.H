// --gwmain.h-------------------------------------------------------------------
//
// Gateway shell header file.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _GWMAIN_H
#define _GWMAIN_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <windows.h>

//$--GetGWExchangeServerName------------------------------------------------------
//  Get Exchange server name.
// -----------------------------------------------------------------------------
LPSTR GetGWExchangeServerName(void);

//$--GetGWSession-------------------------------------------------------------
//  Get MAPI session pointer.
// -----------------------------------------------------------------------------
LPMAPISESSION GetGWSession(void);

//$--GetGWDefaultStore------------------------------------------------------------
//  Get default store pointer.
// -----------------------------------------------------------------------------
LPMDB GetGWDefaultStore(void);

//$--GetGWRootFolder-------------------------------------------------------------
//  Get root folder pointer.
// -----------------------------------------------------------------------------
LPMAPIFOLDER GetGWRootFolder(void);

//$--GetGWMtsInFolder-------------------------------------------------------------
//  Get MTS-IN folder pointer.
// -----------------------------------------------------------------------------
LPMAPIFOLDER GetGWMtsInFolder(void);

//$--GetGWMtsOutFolder------------------------------------------------------------
//  Get MTS-OUT folder pointer.
// -----------------------------------------------------------------------------
LPMAPIFOLDER GetGWMtsOutFolder(void);

//$--GetGWGALEntryIdSize--------------------------------------------------------------
//  Get count of bytes in GAL entry ID.
// -----------------------------------------------------------------------------
ULONG GetGWGALEntryIdSize(void);

//$--GetGWGALEntryId------------------------------------------------------------------
//  Get GAL entry ID pointer.
// -----------------------------------------------------------------------------
LPENTRYID GetGWGALEntryId(void);

//$--GetAdrBookPtr--------------------------------------------------------------
//  Get address book pointer pointer.
// -----------------------------------------------------------------------------
LPADRBOOK GetAdrBookPtr(void);

//$--GetGWGAL------------------------------------------------------------------
//  Get GAL pointer.
// -----------------------------------------------------------------------------
LPABCONT GetGWGAL(void);

//$--GetGWNewMailEvent------------------------------------------------------------
//  Get new mail event.
// -----------------------------------------------------------------------------
HANDLE GetGWNewMailEvent(void);

//$--GetGWNewMailStatus-----------------------------------------------------------
//  Get new mail status.
// -----------------------------------------------------------------------------
BOOL GetGWNewMailStatus(void);

//$--HrGWWaitForStop----------------------------------------------------
//  Wait for the gateway to stop.
// -----------------------------------------------------------------------------
HRESULT HrGWWaitForStop(                // RETURNS: return code
    void);                                      // no arguments

//$--HrGWStartNewMailHandler@--------------------------------------------------
//  Start a thread to handle processing of new mail.
// -----------------------------------------------------------------------------
HRESULT HrGWStartNewMailHandlerW(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCWSTR lpszAddrType,                    // address type
    IN LPCWSTR lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress);  // thread function

HRESULT HrGWStartNewMailHandlerA(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCSTR  lpszAddrType,                    // address type
    IN LPCSTR  lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress);  // thread function

#ifdef UNICODE
#define HrGWStartNewMailHandler    HrGWStartNewMailHandlerW
#else
#define HrGWStartNewMailHandler    HrGWStartNewMailHandlerA
#endif

//$--HrGWStartNewFileHandler@--------------------------------------------------
//  Start a thread to handle processing of new files.
// -----------------------------------------------------------------------------
HRESULT HrGWStartNewFileHandlerW(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCWSTR lpszAddrType,                    // address type
    IN LPCWSTR lpszFileMask,                    // file mask
    IN LPCWSTR lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress);  // thread function

HRESULT HrGWStartNewFileHandlerA(
    IN DWORD   dwSubmitInterval,                // submit interval
    IN DWORD   dwPollingInterval,               // polling interval
    IN DWORD   cMessages,                       // #messages/thread
    IN DWORD   cThreads,                        // #threads
    IN LPCSTR  lpszAddrType,                    // address type
    IN LPCSTR  lpszFileMask,                    // file mask
    IN LPCSTR  lpszPath,                        // path
    IN LPTHREAD_START_ROUTINE lpStartAddress);  // thread function

#ifdef UNICODE
#define HrGWStartNewFileHandler    HrGWStartNewFileHandlerW
#else
#define HrGWStartNewFileHandler    HrGWStartNewFileHandlerA
#endif

//$--GetGWPath----------------------------------------------------------------
//  Get a gateway path pointer.
// -----------------------------------------------------------------------------
LPSTR GetGWPath(LPVOID lpParameter);

//$--GetGWSRowSet-----------------------------------------------------------------
//  Get a SRowSet pointer.
// -----------------------------------------------------------------------------
LPSRowSet GetGWSRowSet(LPVOID lpParameter);

//$--GetGWFindData-----------------------------------------------------------
//  Get a WIN32_FIND_DATA pointer.
// -----------------------------------------------------------------------------
LPWIN32_FIND_DATA GetGWFindData(LPVOID lpParameter);

//$--GetGWFindDataSize-------------------------------------------------------
//  Get a WIN32_FIND_DATA size.
// -----------------------------------------------------------------------------
ULONG GetGWFindDataSize(LPVOID lpParameter);

//$--GetGWSubmitInterval----------------------------------------------------------
//  Get the submit interval.
// -----------------------------------------------------------------------------
DWORD GetGWSubmitInterval(LPVOID lpParameter);

//$--FreeThreadParameter--------------------------------------------------------
//  Free the thread parameter.
// -----------------------------------------------------------------------------
VOID FreeThreadParameter(LPVOID lpParameter);

//
//  The following functions are defined by the application writer.
//

//$--GWMain----------------------------------------------------------------
//  This function is given its own thread to execute.
// -----------------------------------------------------------------------------
void GWMain(void);

//$--HrGWLogon-------------------------------------------------------------
//  Logon to the gateway.
// -----------------------------------------------------------------------------
HRESULT HrGWLogon(void);

//$--HrGWLogoff------------------------------------------------------------
//  Logoff of the gateway.
// -----------------------------------------------------------------------------
HRESULT HrGWLogoff(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
