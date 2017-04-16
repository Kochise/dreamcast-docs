// --edkutils.h-----------------------------------------------------------------
//  EDK utility functions.
//
//  Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _EDKUTILS_H_
#define _EDKUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define EXCHANGE_DS     1
#define EXCHANGE_IS     2
#define EXCHANGE_MTA    3
#define EXCHANGE_SA     4

//$--_HrWriteFile-------------------------------------------------------------
//  Transfer contents from a given memory location & length to an open file.
// -----------------------------------------------------------------------------
HRESULT _HrWriteFile(                   // RETURNS: return code
    IN HANDLE hFile,                    // file handle
    IN ULONG cbmem,                     // count of bytes of memory
    IN LPBYTE lpbmem);                  // pointer to memory

//$--HrCreateDirEntryId------------------------------------------------------
//  Create a directory entry ID given the address of the object
// -----------------------------------------------------------------------------
HRESULT HrCreateDirEntryId(          // RETURNS: return code
    IN LPSTR lpszAddress,               // pointer to address
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID

//$--_HrMemoryToFile----------------------------------------------------------
//  Transfer contents from a given memory location & length to a given file.
// -----------------------------------------------------------------------------
HRESULT _HrMemoryToFile(              // RETURNS: return code
    IN ULONG cbmem,                     // count of bytes of memory
    IN LPBYTE lpbmem,                   // pointer to memory
    IN LPSTR lpszFilename);             // pointer to destination file name

//$--_HrFileToMemory----------------------------------------------------------
//  Transfer contents from a given file to memory.
// -----------------------------------------------------------------------------
HRESULT _HrFileToMemory(              // RETURNS: return code
    IN LPSTR lpszFilename,              // pointer to source file name
    OUT ULONG *lpcbmem,                 // pointer to count of bytes of memory
                                        // variable
    OUT LPBYTE *lppbmem);               // pointer to bytes of memory address
                                        // variable

//$--HrGetMailboxDN----------------------------------------------------------
//  Retrieves mailbox distinguished name from current session object.
//  Example output: /O=Enterprise/OU=Site/CN=Recipients/CN=MailboxName
// -----------------------------------------------------------------------------
HRESULT HrGetMailboxDN(
    IN  LPMAPISESSION lphSession,       // current session handle
    OUT LPSTR*  ppszMailboxDN);         // distinguished name of mailbox.

//$--HrGetServerDN----------------------------------------------------------
//  Retrieves server distinguished name from current session object.
//  Example output: /O=Enterprise/OU=Site/CN=Configuration/CN=Servers/CN=ServerName
// -----------------------------------------------------------------------------
HRESULT HrGetServerDN(
    IN  LPMAPISESSION lphSession,       // current session handle
    OUT LPSTR*  ppszServerDN);          // distinguished name of server. 

//$--_HrFindArrayValue--------------------------------------------------------
// Scan through an array of string pointers searching for a value string that
// matches up to the length of the value string.  Case INSENSITIVE.
//
// OUTPUT:  pnIndex will contain the index into the array of the match.  It will
//          contain ~0 if no match was found.  
//
// RETURNS: NOERROR
//          EDK_E_NOT_FOUND if match was not found.
//          EDK_E_AMBIGUOUS if more than one match found.
//          E_INVALIDARG
// -----------------------------------------------------------------------------
HRESULT _HrFindArrayValue(// RETURNS: return code
    IN  LPSTR  pszValue,    // string value to find.
    IN  LPSTR* rgpszArray,  // array of strings containing known values.
    IN  ULONG  nArraySize,  // number of known values.
    OUT ULONG* pnIndex);    // index of known value, ~0 if no match found.

//$--_HrExpandCommandLineArgument---------------------------------------------
//  Expands abbreviated command line flags of the form -FLAG=VALUE (or
//  /FLAG=VALUE) to their full text forms returning the index of the  
//  matching flag and a pointer to the data part of the flag (ie the 
//  part after the equals sign).  The caller passes an array of known 
//  flag names, and the function tries to make an unambiguous match 
//  with one of the names.  In this way users can be offered the 
//  convenience of entering /V=Foo, instead of
//  /VERY-LONG-AND-CLUMSY-NAME=Foo (assuming no other flag begins with
//  V, otherwise the user might have to enter more letters).
//
//  The comparison is not case sensitive; the flag names /BLUTO and
//  -bluto are not distinguished, and /b might match on either of them.
//
//  To maintain greater compatibility with other Microsoft NT and DOS
//  command line applications, the ":" character may be substituted 
//  for the "=".  So /FLAG:VALUE or -FLAG:VALUE are also valid.
// -----------------------------------------------------------------------------

HRESULT _HrExpandCommandLineArgument(
    IN  LPSTR  pszArg,          // flag user entered
    IN  LPSTR* rgpszArgArray,   // array of known flag names (w/o leading dashes)
    IN  ULONG  nArraySize,      // number of known flags
    OUT ULONG* pnFlagIndex,     // index of known flag, -1 if no match found.
	OUT LPSTR* ppszFlagName,	// known flag name
    OUT LPSTR* ppszArgData);    // user data for flag

//$--_nEcFromHr---------------------------------------------------------------
//  Convert an HRESULT to an exit code suitable for return
//  from a console application.
//
//  NOTE:
//
//      EDK HRESULTS get converted to their "code" (current 1 - 4).
//      Any successful HRESULT converts to zero.
//      Any EDK "approved" Win32 or OLE HRESULT gets converted
//      to its EDK exit code (currently 101 - 105).
//      Any non-EDK approved HRESULT gets converted to the negative
//      of its "code" (e.g. -8).
//-----------------------------------------------------------------------------
INT _nEcFromHr(                       // RETURNS: INT
    IN HRESULT hr);                     // HRESULT to convert to exit code

//$--HrIdentifyRegistryRootKey--------------------------------------------------
//  Checks that a fully qualified key name begins with one of the four
//	predefined NT Registry keys: HKEY_LOCAL_MACHINE, HKEY_CLASSES_ROOT,
//	HKEY_CURRENT_USER, or HKEY_USERS.  The output from this function
//	can be passed to registry functions like RegOpenKeyEx().
//
//  NOTE:
//
//	    Successful completion.  hkKey is the Registry key handle,
//	    pszSubKey points to the remainder of the subkey string.  Note
//	    that it is legitimate for pszSubKey to be NULL, meaning that
//	    the user is trying to access values in the root of one of the
//	    predefined registry keys.
// -----------------------------------------------------------------------------
HRESULT HrIdentifyRegistryRootKey(  // RETURNS: return code
    IN  LPSTR pszKey,               // pointer to fully qualified key name
    OUT HKEY *phkKeyHandle,         // pointer to key handle
    OUT LPSTR *ppszSubKey);         // pointer to subkey section

//$--_HrReadRegistrySZ--------------------------------------------------------
//  Read a string from the registry.
// -----------------------------------------------------------------------------
HRESULT _HrReadRegistrySZ(		    // RETURNS: return code
	IN HKEY hRegistryKey,				// registry key to read value from
	IN LPSTR lpszValueName,		    	// name of value to read
	OUT LPSTR lpszBuffer,				// buffer to read value into
	IN OUT DWORD *lpcbBufferSize);		// size of buffer to read value into

//$--_HrReadRegistryDWORD-----------------------------------------------------
//  Read a DWORD integer from the registry.
// -----------------------------------------------------------------------------
HRESULT _HrReadRegistryDWORD(			// RETURNS: return code
	IN HKEY hRegistryKey,				// registry key to read value from
	IN LPSTR lpszValueName,			    // name of value to read
	OUT LPDWORD lpdwBuffer);			// address of DWORD to read value into

//$--_HrWriteRegistrySZ-------------------------------------------------------
//  Write a string to the registry.
// -----------------------------------------------------------------------------
HRESULT _HrWriteRegistrySZ(			// RETURNS: return code
	IN HKEY hRegistryKey,				// registry key to write value to
	IN LPSTR lpszValueName,		    	// name of value to write
	IN LPCSTR lpszValue);				// string value to write

//$--_HrWriteRegistryDWORD----------------------------------------------------
//  Write a DWORD integer to the registry.
// -----------------------------------------------------------------------------
HRESULT _HrWriteRegistryDWORD(		// RETURNS: return code
	IN HKEY hRegistryKey,				// registry key to write value to
	IN LPSTR lpszValueName,			    // name of value to write
	IN DWORD dwValue);					// DWORD value to write

//$--_HrInputCommandLinePassword---------------------------------------------------------
//  Input password and echo *'s.
// -----------------------------------------------------------------------------
HRESULT _HrInputCommandLinePassword(				// RETURNS: return code
	IN DWORD dwFlags,					// reserved--must be zero
	IN DWORD cbLength,		  		    // size of the buffer in bytes
	OUT LPSTR pszBuffer);				// buffer to write string into

//$--HrStrAToStrW---------------------------------------------------------------
//  Convert a byte string to a word string.  The resulting string is placed in 
//  a buffer allocated using MAPIAllocateBuffer.
// -----------------------------------------------------------------------------
HRESULT HrStrAToStrW(                   // RETURNS: return code
    IN  LPCSTR          lpszSource,     // source string
    OUT LPWSTR *        lppwszDest);    // destination string

//$--HrStrWToStrA---------------------------------------------------------------
//  Convert a word string to a byte string.  The resulting string is placed in 
//  a buffer allocated using MAPIAllocateBuffer.
// -----------------------------------------------------------------------------
HRESULT HrStrWToStrA(                   // RETURNS: return code
    IN  LPCWSTR         lpwszSource,    // source string
    OUT LPSTR *         lppszDest);     // destination string

//$--HrStrAToStrA---------------------------------------------------------------
//  Create an allocated copy of a byte string using MAPIAllocateBuffer.
//  This is useful for creating macros involving TCHAR strings.
// -----------------------------------------------------------------------------
HRESULT HrStrAToStrA(                   // RETURNS: return code
    IN  LPCSTR          lpszSource,     // source string
    OUT LPSTR *         lppszDest);     // destination string

//$--HrStrWToStrW---------------------------------------------------------------
//  Create an allocated copy of a word string using MAPIAllocateBuffer.
//  This is useful for creating macros involving TCHAR strings.
// -----------------------------------------------------------------------------
HRESULT HrStrWToStrW(                   // RETURNS: return code
    IN  LPCWSTR         lpwszSource,    // source string
    OUT LPWSTR *        lppwszDest);    // destination string

//$--HrStr*ToStr*---------------------------------------------------------------
//  Macros that implement string conversion for TCHAR strings.
// -----------------------------------------------------------------------------

#ifdef UNICODE

#define HrStrToStr(Source,Dest)     HrStrWToStrW(Source,Dest)
#define HrStrToStrA(Source,Dest)    HrStrWToStrA(Source,Dest)
#define HrStrToStrW(Source,Dest)    HrStrWToStrW(Source,Dest)
#define HrStrAToStr(Soruce,Dest)    HrStrAToStrW(Source,Dest)
#define HrStrWToStr(Source,Dest)    HrStrWToStrW(Source,Dest)

#else // UNICODE

#define HrStrToStr(Source,Dest)     HrStrAToStrA(Source,Dest)
#define HrStrToStrA(Source,Dest)    HrStrAToStrA(Source,Dest)
#define HrStrToStrW(Source,Dest)    HrStrAToStrW(Source,Dest)
#define HrStrAToStr(Soruce,Dest)    HrStrAToStrA(Source,Dest)
#define HrStrWToStr(Source,Dest)    HrStrWToStrA(Source,Dest)

#endif // UNICODE

//$--HrGetServiceStatus------------------------------------------------------
//  Get the current state of a service on a given machine.
// -----------------------------------------------------------------------------
HRESULT HrGetServiceStatus(          // RETURNS: return code
    IN LPSTR lpszMachineName,           // machine name
    IN LPSTR lpszServiceName ,          // service name
    OUT DWORD *lpdwCurrentState);       // current state

//$--HrGetExchangeStatus-----------------------------------------------------
//  Get the current state of the Exchange server on a given machine.
// -----------------------------------------------------------------------------
HRESULT HrGetExchangeStatus(         // RETURNS: return code
    IN LPSTR lpszMachineName,           // machine name
    OUT DWORD *lpdwService,             // service
    OUT DWORD *lpdwCurrentState);       // current state

//$--HrGetExchangeServiceStatus----------------------------------------------
//  Get the current state of an Exchange service on a given machine.
// -----------------------------------------------------------------------------
HRESULT HrGetExchangeServiceStatus(  // RETURNS: return code
    IN LPSTR lpszMachineName,           // machine name
    IN  DWORD dwService,                // service
    OUT DWORD *lpdwCurrentState);       // current state

//$--FMachineExists---------------------------------------------------------
//  Returns TRUE if the computer exists.
// -----------------------------------------------------------------------------
BOOL FMachineExists(                // RETURNS: TRUE/FALSE
    IN LPSTR  lpszComputerName);        // address of name of remote computer 

//$--_HrFindFile--------------------------------------------------------------
//  Find a file in a directory subtree.
// -----------------------------------------------------------------------------
HRESULT _HrFindFile(                  // RETURNS: return code
    IN LPSTR lpszInPathName,            // starting path name
    IN LPSTR lpszInFileName,            // file name
    OUT LPSTR lpszOutPathName);         // path name where file first found

//$--GetSystemEnvironmentVariable-----------------------------------------------
//  Gets a system environment variable.
// -----------------------------------------------------------------------------
DWORD GetSystemEnvironmentVariable(     // RETURNS: size of value
    IN LPSTR  lpszName,                 // environment variable name 
    OUT LPSTR  lpszValue,               // buffer for variable value 
    OUT DWORD  cchValue);               // size of buffer, in characters 

//$--SetSystemEnvironmentVariable-----------------------------------------------
//  Sets a system environment variable permanently.
// -----------------------------------------------------------------------------
BOOL SetSystemEnvironmentVariable(      // RETURNS: TRUE/FALSE
    IN LPCSTR  lpszName,                // environment variable name  
    IN LPCSTR  lpszValue);              // new value for variable 

//$--GetUserEnvironmentVariable-------------------------------------------------
//  Gets a user environment variable.
// -----------------------------------------------------------------------------
DWORD GetUserEnvironmentVariable(       // RETURNS: size of value
    IN LPSTR  lpszName,                 // environment variable name 
    OUT LPSTR  lpszValue,               // buffer for variable value 
    OUT DWORD  cchValue);               // size of buffer, in characters 

//$--SetUserEnvironmentVariable-------------------------------------------------
//  Sets a user environment variable permanently.
// -----------------------------------------------------------------------------
BOOL SetUserEnvironmentVariable(        // RETURNS: TRUE/FALSE
    IN LPCSTR  lpszName,                // environment variable name  
    IN LPCSTR  lpszValue);              // new value for variable 

//$--HrTextToRTFCompressed---------------------------------------------------
//  Convert plain ANSI text to its RTF compressed equivalent for a message.
// -----------------------------------------------------------------------------
HRESULT HrTextToRTFCompressed(       // RETURNS: return code
    IN ULONG cchText,                   // # of characters of text
    IN LPSTREAM lpText,                 // plain text stream pointer
	IN ULONG cAttachments,	            // # of message attachments
	IN ULONG * rgiRendering,            // attachment rendering positions
    IN LPMESSAGE lpMsg,                 // message pointer
	IN ULONG cpid);                     // code page for the text stream

//$--HrRTFCompressedToText---------------------------------------------------
//  Convert message's compressed RTF to its ANSI equivalent.
// -----------------------------------------------------------------------------
HRESULT HrRTFCompressedToText(       // RETURNS: return code
            IN LPMESSAGE lpMsg,         // MAPI message pointer
            IN LPSTREAM pText,          // stream to copy ANSI text to
			IN ULONG cpid,				// code page for  the text stream
            OUT ULONG * pcb);           // # bytes copied to stream

//$--HrStrTokAll@---------------------------------------------------------------
//  Splits string lpsz at token separators and points elements of array
//  *lpppsz to string components.
//------------------------------------------------------------------------------
HRESULT HrStrTokAllW(                   // RETURNS: return code
    IN LPCWSTR lpsz,                    // separated string
    IN LPCWSTR lpszEOT,                 // pointer to string containing separators
    OUT ULONG * lpcpsz,                 // count of string pointers
    OUT LPWSTR ** lpppsz);              // pointer to list of strings

HRESULT HrStrTokAllA(                   // RETURNS: return code
    IN LPCSTR lpsz,                     // separated string
    IN LPCSTR lpszEOT,                  // pointer to string containing separators
    OUT ULONG * lpcpsz,                 // count of string pointers
    OUT LPSTR ** lpppsz);               // pointer to list of strings

#ifdef UNICODE
#define HrStrTokAll HrStrTokAllW
#else
#define HrStrTokAll HrStrTokAllA
#endif

//$--HrCreateProfileName-----------------------------------------------------
//  Create a unique profile name.
// -----------------------------------------------------------------------------
HRESULT HrCreateProfileName(         // RETURNS: return code
    IN  LPSTR lpszPrefix,               // prefix of profile name
    IN  ULONG  cBufferSize,             // size of buffer in bytes
    IN OUT LPSTR lpszBuffer);           // buffer

//$--HrGetFileVersionInfo----------------------------------------------------
//  Get the file version information.
// -----------------------------------------------------------------------------
HRESULT HrGetFileVersionInfo(        // RETURNS: return code
    IN  LPSTR lpszFileName,             // file name
    OUT LPVOID *lppVersionInfo);        // file version information

//$--_GetFileNameFromFullPath--------------------------------------------------
//  Return a pointer to the file name.
// -----------------------------------------------------------------------------
LPSTR _GetFileNameFromFullPath(       // RETURNS: file name
    IN LPSTR lpszFullPath);            // full path name

//$--HrCreateDirEntryIdEx-------------------------------------------------------
//  Create a directory entry ID given the address of the object
//  in the directory.
// -----------------------------------------------------------------------------
HRESULT HrCreateDirEntryIdEx(			// RETURNS: HRESULT
	IN	LPADRBOOK	lpAdrBook,			// address book (directory) to look in
	IN	LPSTR		lpszDN,				// object distinguished name
	OUT	ULONG *		lpcbEntryID,		// count of bytes in entry ID
	OUT	LPENTRYID * lppEntryID);	    // pointer to entry ID

#ifdef __cplusplus
}
#endif

#endif
