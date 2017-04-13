//=--------------------------------------------------------------------------=
// DOReg.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implementation of registry manipulation functions for DocObject servers
//

#include "CDocObj.H"
#include <util.h>

// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// RegisterDocObject.
//=--------------------------------------------------------------------------=
// This function writes out some values specific to a DocObject. You should
// call this from your RegisterData function. You don't need to do anything
// special for UnregisterData, because the framework already deletes the
// entire <LibraryName>.<ObjectName> and CLSID\<CLSID> keys.
//
// What we add here:
//
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\DocObject = <MISCDOCOBJ>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\DocObject = <MISCDOCOBJ>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\Printable
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\DefaultExtension = <EXT>, <DESCRIPTION>
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    REFCLSID     - [in] CLSID of the object
//    DWORD        - [in] misc DocObject status flags
//    BOOL         - [in] whether IPrint is supported
//    LPCSTR       - [in] default file extension
//    LPCSTR       - [in] file description for File Open, File Save As
//
// Output:
//    BOOL
//
// Notes:
//    - not the most terribly efficient routine.
//
BOOL RegisterDocObject(LPCSTR pszLibName, LPCSTR pszObjectName,
                       REFCLSID riidObject, DWORD dwMiscDocObj,
	                   BOOL bPrint, LPCSTR szExt, LPCSTR szDescription)
{
    HKEY    hk, hkSub = NULL;
    char    szTmp[MAX_PATH];
    char    szGuidStr[GUID_STR_LEN];
    DWORD   dwDummy;
    LONG    l;

    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\DocObject = <MISCDOCOBJ>
    //
    lstrcpy(szTmp, pszLibName);
    lstrcat(szTmp, ".");
    lstrcat(szTmp, pszObjectName);

    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szTmp, 0L, "",
                       REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE,
                       NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "DocObject", 0L, "", REG_OPTION_NON_VOLATILE,
                       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%d", dwMiscDocObj);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    CLEANUP_ON_ERROR(l);
    RegCloseKey(hkSub);
    RegCloseKey(hk);

    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\  
    //
    StringFromGuidA(riidObject, szGuidStr);
    wsprintf(szTmp, "CLSID\\%s", szGuidStr);
    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, szTmp, 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    // create the Printable key, if printing supported.
    //
	if (bPrint)
	{
       l = RegCreateKeyEx(hk, "Printable", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
       CLEANUP_ON_ERROR(l);
       RegCloseKey(hkSub);
       hkSub = NULL;
	}

    // now set up the DocObject key...
    //
    l = RegCreateKeyEx(hk, "DocObject", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%d", dwMiscDocObj);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
	hkSub = NULL;

    // now set up the DefaultExtension key
    //
    l = RegCreateKeyEx(hk, "DefaultExtension", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%s,%s", szExt, szDescription);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    CLEANUP_ON_ERROR(l);

  CleanUp:
    if (hk)
        RegCloseKey(hk);
    if (hkSub)
        RegCloseKey(hkSub);

    return (l == ERROR_SUCCESS) ? TRUE : FALSE;
}
