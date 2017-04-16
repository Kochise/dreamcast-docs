// --edksetup.h-----------------------------------------------------------------
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_EDKSETUP_H)
#define _EDkSETUP_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "msdetect.h"
#include "msregdb.h"
#include "msshared.h"
#include "setupapi.h"

//$--HrSendProgManCommand----------------------------------------------------
//  Send one or more commands to the program manager.
// -----------------------------------------------------------------------------
HRESULT HrSendProgManCommand(    // RETURNS: return code
    LPDWORD lpIdInst,               // pointer to instance ID
    LPSTR lpszCommand);             // pointer to command string

//$--HrGetProgManGroups------------------------------------------------------
//  Get the names of all the program groups.
// -----------------------------------------------------------------------------
HRESULT HrGetProgManGroups(      // RETURNS: return code
    LPDWORD lpIdInst,               // pointer to instance ID
    LPSTR *lppszGroups);            // pointer to groups string address variable

//$--AppendSlash----------------------------------------------------------------
//  This function will append a backslash to a string if one does not
//  already exist.
// -----------------------------------------------------------------------------
void AppendSlash(                       // RETURNS: nothing
    IN OUT LPSTR sz1);                  // string

//$--RemoveTrailingSlash--------------------------------------------------------
//  This function will remove a trailing slash from a string if it exists.
//  It will NOT remove trailing slash from "X:\".
// -----------------------------------------------------------------------------
void RemoveTrailingSlash(               // RETURNS: nothing
    IN OUT LPSTR sz1);                  // string

//$--ShowMessageBox-------------------------------------------------------------
//  This displays a localizable message built by the message compiler in a
//  message box.
// -----------------------------------------------------------------------------
int ShowMessageBox(             // RETURNS: message box result
	IN LPCVOID lpSource,        // source of message resource (NULL = embedded)
	IN DWORD dwMessageID,       // message ID
	IN LPSTR lpszTitle,         // title
	IN DWORD dwMsgBoxFlags,     // message box flags
	IN DWORD dwLanguageID,      // language ID
	IN ...);                    // arguments required for the message resource

//$--ExtractPath----------------------------------------------------------------
//  This routine will give the path portion of a file name.
// -----------------------------------------------------------------------------
void ExtractPath(                       // RETURNS: nothing
	IN  CHAR *pszPathName,              // full path name
	OUT	CHAR *pszPath);                 // path name

//$--FEnumFiles-----------------------------------------------------------------
//  This function provides a wrapper for the FindFirstFile() and FindNextFile()
//  functions. Given a search string [Drive:][PATH\\]SearchPattern this 
//  function will place file names (one per call) in pszFileName. When there
//  are no more files that match the search string it will return FALSE. It
//  will filter out the . and .. directories. This function is generally used
//  like this:
//
//      hEnumFile = NULL;
//	    while(fEnumFiles(&hEnumFile, szSearchString, szFileName, &fDir))
//      {
//	        if(fDir) ProcessDir(szFileName);
//	        else     ProcessFile(szFileName);
//		}
//
// -----------------------------------------------------------------------------
BOOL FEnumFiles(                    // RETURNS: TRUE if a file/dir was found
	IN     CHAR   *pszSearchString, // directory & search pattern
	IN OUT HANDLE *phScan,          // a pointer to EnumFiles instance handle 
    OUT    CHAR   *pszFileName,     // current file name
    OUT    BOOL   *pfDir);          // TRUE if a directory was found

//$--DwConnectNetworkShare------------------------------------------------------
//  Connect a local drive letter to a network disk resource.
// -----------------------------------------------------------------------------
DWORD DwConnectNetworkShare(            // RETURNS: return code
	IN  LPSTR lpszUNCName,              // UNC path to network share
	OUT LPSTR lpszDriveLetter);         // drive letter

//$--FGetServiceDirectory-------------------------------------------------------
//  Given a service name, gives the directory to the executable image.
// -----------------------------------------------------------------------------
BOOL FGetServiceDirectory(              // RETURNS: TRUE/FALSE
	IN  LPSTR lpszServiceName,          // service name
	OUT LPSTR lpszServiceDir);          // service directory

//$--FServiceExists-------------------------------------------------------------
//  Ask the Service Control Manager if a particular service exists.
// -----------------------------------------------------------------------------
BOOL FServiceExists(                    // RETURNS: TRUE/FALSE
	IN LPSTR lpszServiceName);          // service

//$--FServiceRunning------------------------------------------------------------
//  Ask the Service Control Manager if a particular service is running. If the
//  service is running, this function will attempt to stop it before returning.
// -----------------------------------------------------------------------------
BOOL FServiceRunning(                   // RETURNS: TRUE/FALSE
	IN LPSTR lpszServiceName);          // service

//$--FDirEmpty------------------------------------------------------------------
//  Checks to see if a given directory is empty.
// -----------------------------------------------------------------------------
BOOL FDirEmpty(                         // RETURNS: TRUE/FALSE
	IN LPSTR lpszDirName);              // directory name

//$--EDKDeleteNode--------------------------------------------------------------
//  This deletes a directory and files and directories contained within.
//  NOTE: This is a recursive function.
// -----------------------------------------------------------------------------
void EDKDeleteNode(                     // RETURNS: nothing
    IN LPSTR lpszDirName);              // directory name

//$--FNetworkAvailable----------------------------------------------------------
//  Checks to see that a network is available
// -----------------------------------------------------------------------------
BOOL FNetworkAvailable(                 // RETURNS: TRUE/FALSE
    void);                              // nothing

//$--FRegisterEventLog----------------------------------------------------------
//  This function registers an application with the event log.
// -----------------------------------------------------------------------------
BOOL FRegisterEventLog(                 // RETURNS: TRUE/FALSE
	IN LPSTR lpszServer,		        // server name
	IN LPSTR lpszApplicationName,       // application name
	IN LPSTR lpszMessageDllName,        // message DLL path name
	IN DWORD dwTypesSupported);         // events supported

//$--FDeregisterEventLog--------------------------------------------------------
//  This function deregisters an application with the Event Log.
// -----------------------------------------------------------------------------
BOOL FDeregisterEventLog(               // RETURNS: TRUE/FALSE
    IN LPSTR lpszServer,                // server name
    IN LPSTR lpszApplicationName);      // application Name 

//$--EscapeBackSlashes----------------------------------------------------------
//  This function copies a string, but doubles the number of backslashes.
// -----------------------------------------------------------------------------
void EscapeBackSlashes(                 // RETURNS: nothing
    IN  LPSTR lpszSrcStr,               // source string
	OUT LPSTR lpszDestStr);             // destination string

//$--FLoadCounters--------------------------------------------------------------
//  Loads the counters by creating a LODCTR.EXE process.	
// -----------------------------------------------------------------------------
BOOL FLoadCounters(                     // RETURNS: TRUE/FALSE
    IN LPSTR lpszFileName);             // INI file name

//$--FUnloadCounters------------------------------------------------------------
//  Unloads the counters by creating a UNLODCTR.EXE process.	
// -----------------------------------------------------------------------------
BOOL FUnloadCounters(                   // RETURNS: TRUE/FALSE
    IN LPSTR lpszClassName);            // service class name

//$--FGetDomainAccountName------------------------------------------------------
//  This function gets the current user's domain acount name.
// -----------------------------------------------------------------------------
BOOL FGetDomainAccountName(             // RETURNS: TRUE/FALSE
    IN OUT DWORD *lpdwDomainSize,       // domain name buffer size
    IN OUT DWORD *lpdwAccountSize,      // account name buffer size
    OUT LPSTR lpszDomainName,           // domain name
    OUT LPSTR lpszAccountName);         // account name

#ifdef __cplusplus
}
#endif

#endif
