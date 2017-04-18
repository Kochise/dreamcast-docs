// Registry.cpp -   Implementation of registry functions.
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include <objbase.h>
#include <assert.h>
#include "Registry.h"
#include "util.h"
#include "util.cpp"

////////////////////////////////////////////////////////
//
// Internal helper functions prototypes
//

// Set the given key and its value.
BOOL setKeyAndValue(const char* pszPath,
					const char* szSubkey,
					const char* szValue,
					const char* szName = NULL) ;

// Convert a CLSID into a char string.
void CLSIDtochar(   const CLSID& clsid,
					char* szCLSID,
					int length) ;

// Determine if a particular subkey exists.
BOOL SubkeyExists(const char* pszPath,
				  const char* szSubkey) ;

// Delete szKeyChild and all of its descendents.
LONG recursiveDeleteKey(HKEY hKeyParent, const char* szKeyChild) ;

/////////////////////////////////////////////////////////
//
// Public function implementation
//
/////////////////////////////////////////////////////////
//
// Register the component in the registry.
//
HRESULT RegisterServer( HMODULE hModule,                // DLL module handle
						const CLSID& clsid,             // Class ID
						const char* szFriendlyName,     // Friendly Name
						const char* szVerIndProgID,     // Programmatic
						const char* szProgID)           //  IDs
{
	// Get server location.
	char szModule[512] ;
	DWORD dwResult =
		::GetModuleFileName(hModule,
							szModule,
							sizeof(szModule)/sizeof(char)) ;
	assert(dwResult != 0) ;

	// Convert a CLSID into a char string.
	char szCLSID[CLSID_STRING_SIZE] ;
	CLSIDtochar(clsid, szCLSID, sizeof(szCLSID)) ;

	// Build the key CLSID\\{...}
	char szKey[64] ;
	strcpy(szKey, "CLSID\\");
	strcat(szKey, szCLSID) ;

	// Add the CLSID to the registry.
	setKeyAndValue(szKey, NULL, szFriendlyName) ;

	// Add server filename key
#ifdef _OUTPROC_SERVER_
	setKeyAndValue(szKey, "LocalServer32", szModule) ;
#else
	setKeyAndValue(szKey, "InprocServer32", szModule) ;
#endif

	// Add the ProgID subkey under the CLSID key.
	setKeyAndValue(szKey, "ProgID", szProgID) ;

	// Add the version-independent ProgID subkey under CLSID key.
	setKeyAndValue( szKey, "VersionIndependentProgID",
					szVerIndProgID) ;

	// Add the version-independent ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(szVerIndProgID, NULL, szFriendlyName);
	setKeyAndValue(szVerIndProgID, "CLSID", szCLSID) ;
	setKeyAndValue(szVerIndProgID, "CurVer", szProgID) ;

	// Add the versioned ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(szProgID, NULL, szFriendlyName);
	setKeyAndValue(szProgID, "CLSID", szCLSID) ;

	return S_OK;
}

/////////////////////////////////////////////////////////
//
// Remove the component from the registry.
//
LONG UnregisterServer(  const CLSID& clsid,
						const char* szVerIndProgID,
						const char* szProgID)
{
	// Convert the CLSID into a char.
	char szCLSID[CLSID_STRING_SIZE] ;
	CLSIDtochar(clsid, szCLSID, sizeof(szCLSID)) ;

	// Build the key CLSID\\{...}
	char szKey[80] ;
	strcpy(szKey, "CLSID\\");
	strcat(szKey, szCLSID) ;

	// Check for a another server for this component.
#ifdef _OUTPROC_SERVER_
	if (SubkeyExists(szKey, "InprocServer32"))
#else
	if (SubkeyExists(szKey, "LocalServer32"))
#endif
	{
		// Delete only the path for this server.
#ifdef _OUTPROC_SERVER_
		strcat(szKey, "\\LocalServer32") ;
#else
		strcat(szKey, "\\InprocServer32") ;
#endif
		LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey) ;
		assert(lResult == ERROR_SUCCESS) ;
	}
	else
	{
		// Delete all related keys.
		// Delete the CLSID Key - CLSID\{...}
		LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey) ;
		assert((lResult == ERROR_SUCCESS) ||
			   (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

		// Delete the version-independent ProgID Key.
		lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID) ;
		assert((lResult == ERROR_SUCCESS) ||
			   (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

		// Delete the ProgID key.
		lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szProgID) ;
		assert((lResult == ERROR_SUCCESS) ||
			   (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.
	}
	return S_OK;
}

///////////////////////////////////////////////////////////
//
// Internal helper functions
//
/////////////////////////////////////////////////////////
//
// Convert a CLSID to a char string.
//
void CLSIDtochar(   const CLSID& clsid,
					char* szCLSID,
					int length)
{
	assert(length >= CLSID_STRING_SIZE) ;
	// Get CLSID
	LPOLESTR wszCLSID = NULL ;
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID) ;
	assert(SUCCEEDED(hr)) ;

	// Convert from wide characters to non-wide characters.
	wcstombs(szCLSID, wszCLSID, length);

	// Free memory.
	CoTaskMemFree(wszCLSID) ;
}

/////////////////////////////////////////////////////////
//
// Delete a key and all of its descendents.
//
LONG recursiveDeleteKey(HKEY hKeyParent,            // Parent of key to delete.
						const char* lpszKeyChild)   // Key to delete.
{
	// Open the child.
	HKEY hKeyChild;
	LONG lRes = RegOpenKeyEx(   hKeyParent, lpszKeyChild, 0,
								KEY_ALL_ACCESS, &hKeyChild);
	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	// Enumerate all of the decendents of this child.
	FILETIME time;
	char szBuffer[256];
	DWORD dwSize = 256;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
						NULL, NULL, &time) == S_OK)
	{
		// Delete the decendents of this child.
		lRes = recursiveDeleteKey(hKeyChild, szBuffer);
		if (lRes != ERROR_SUCCESS)
		{
			// Cleanup before exiting.
			RegCloseKey(hKeyChild);
			return lRes;
		}
		dwSize = 256;
	}

	// Close the child.
	RegCloseKey(hKeyChild);

	// Delete this child.
	return RegDeleteKey(hKeyParent, lpszKeyChild);
}

/////////////////////////////////////////////////////////
//
// Determine if a particular subkey exists.
//
BOOL SubkeyExists(const char* pszPath,    // Path of key to check
				  const char* szSubkey)   // Key to check
{
	HKEY hKey ;
	char szKeyBuf[80] ;

	// Copy keyname into buffer.
	strcpy(szKeyBuf, pszPath) ;

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
		strcat(szKeyBuf, "\\") ;
		strcat(szKeyBuf, szSubkey ) ;
	}

	// Determine if key exists by trying to open it.
	LONG lResult = ::RegOpenKeyEx(HKEY_CLASSES_ROOT,
								  szKeyBuf,
								  0,
								  KEY_ALL_ACCESS,
								  &hKey) ;
	if (lResult == ERROR_SUCCESS)
	{
		RegCloseKey(hKey) ;
		return TRUE ;
	}
	return FALSE ;
}

/////////////////////////////////////////////////////////
//
// Create a key and set its value.
//
// This helper function was borrowed and modifed from Kraig Brockschmidt's
// book Inside OLE.
//
BOOL setKeyAndValue(const char* szKey,
					const char* szSubkey,
					const char* szValue,
					const char* szName)
{
	HKEY hKey;
	char szKeyBuf[1024] ;

	// Copy keyname into buffer.
	strcpy(szKeyBuf, szKey);

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
		strcat(szKeyBuf, "\\");
		strcat(szKeyBuf, szSubkey );
	}

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(  HKEY_CLASSES_ROOT,
									szKeyBuf,
									0, NULL, REG_OPTION_NON_VOLATILE,
									KEY_ALL_ACCESS, NULL,
									&hKey, NULL) ;
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE ;
	}

	// Set the Value.
	if (szValue != NULL)
	{
		 RegSetValueEx(hKey, szName, 0, REG_SZ,
							(BYTE *)szValue,
							strlen(szValue)+1);
	}

	RegCloseKey(hKey);
	return TRUE;
}
