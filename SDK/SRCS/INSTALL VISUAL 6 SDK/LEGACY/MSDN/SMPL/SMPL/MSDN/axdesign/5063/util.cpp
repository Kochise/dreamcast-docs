//=--------------------------------------------------------------------------=
// Util.C
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// contains routines that we will find useful.
//
#include "IPServer.H"

#include "Globals.H"
#include "Util.H"


// for ASSERT and FAIL
//
SZTHISFILE

//=---------------------------------------------------------------------------=
// this table is used for copying data around, and persisting properties.
// basically, it contains the size of a given data type
//
const BYTE g_rgcbDataTypeSize[] = {
    0,                      // VT_EMPTY= 0,
    0,                      // VT_NULL= 1,
    sizeof(short),          // VT_I2= 2,
    sizeof(long),           // VT_I4 = 3,
    sizeof(float),          // VT_R4  = 4,
    sizeof(double),         // VT_R8= 5,
    sizeof(CURRENCY),       // VT_CY= 6,
    sizeof(DATE),           // VT_DATE = 7,
    sizeof(BSTR),           // VT_BSTR = 8,
    sizeof(IDispatch *),    // VT_DISPATCH    = 9,
    sizeof(SCODE),          // VT_ERROR    = 10,
    sizeof(VARIANT_BOOL),   // VT_BOOL    = 11,
    sizeof(VARIANT),        // VT_VARIANT= 12,
    sizeof(IUnknown *),     // VT_UNKNOWN= 13,
};


//=---------------------------------------------------------------------------=
// overloaded new
//=---------------------------------------------------------------------------=
// for the retail case, we'll just use the win32 Local* heap management
// routines for speed and size
//
// Parameters:
//    size_t         - [in] what size do we alloc
//
// Output:
//    VOID *         - new memoery.
//
// Notes:
//
void * _cdecl operator new
(
    size_t    size
)
{
    if (!g_hHeap)
	g_hHeap = GetProcessHeap();

    return g_hHeap ? HeapAlloc(g_hHeap, 0, size) : NULL;
}

//=---------------------------------------------------------------------------=
// overloaded delete
//=---------------------------------------------------------------------------=
// retail case just uses win32 Local* heap mgmt functions
//
// Parameters:
//    void *        - [in] free me!
//
// Notes:
//
void _cdecl operator delete ( void *ptr)
{
    HeapFree(g_hHeap, 0, ptr);
}

//=--------------------------------------------------------------------------=
// MakeWideFromAnsi
//=--------------------------------------------------------------------------=
// given a string, make a BSTR out of it.
//
// Parameters:
//    LPSTR         - [in]
//    BYTE          - [in]
//
// Output:
//    LPWSTR        - needs to be cast to final desired result
//
// Notes:
//
LPWSTR MakeWideStrFromAnsi
(
    LPSTR psz,
    BYTE  bType
)
{
    LPWSTR pwsz;
    int i;

    // arg checking.
    //
    if (!psz)
	return NULL;

    // compute the length of the required BSTR
    //
    i =  MultiByteToWideChar(CP_ACP, 0, psz, -1, NULL, 0);
    if (i <= 0) return NULL;

    // allocate the widestr
    //
    switch (bType) {
      case STR_BSTR:
	// -1 since it'll add it's own space for a NULL terminator
	//
	pwsz = (LPWSTR) SysAllocStringLen(NULL, i - 1);
	break;
      case STR_OLESTR:
	pwsz = (LPWSTR) CoTaskMemAlloc(i * sizeof(WCHAR));
	break;
      default:
	FAIL("Bogus String Type.");
    }

    if (!pwsz) return NULL;
    MultiByteToWideChar(CP_ACP, 0, psz, -1, pwsz, i);
    pwsz[i - 1] = 0;
    return pwsz;
}

//=--------------------------------------------------------------------------=
// MakeWideStrFromResId
//=--------------------------------------------------------------------------=
// given a resource ID, load it, and allocate a wide string for it.
//
// Parameters:
//    WORD            - [in] resource id.
//    BYTE            - [in] type of string desired.
//
// Output:
//    LPWSTR          - needs to be cast to desired string type.
//
// Notes:
//
LPWSTR MakeWideStrFromResourceId
(
    WORD    wId,
    BYTE    bType
)
{
    int i;

    char szTmp[512];

    // load the string from the resources.
    //
    i = LoadString(GetResourceHandle(), wId, szTmp, 512);
    if (!i) return NULL;

    return MakeWideStrFromAnsi(szTmp, bType);
}

//=--------------------------------------------------------------------------=
// MakeWideStrFromWide
//=--------------------------------------------------------------------------=
// given a wide string, make a new wide string with it of the given type.
//
// Parameters:
//    LPWSTR            - [in]  current wide str.
//    BYTE              - [in]  desired type of string.
//
// Output:
//    LPWSTR
//
// Notes:
//
LPWSTR MakeWideStrFromWide
(
    LPWSTR pwsz,
    BYTE   bType
)
{
    LPWSTR pwszTmp;
    int i;

    if (!pwsz) return NULL;

    // just copy the string, depending on what type they want.
    //
    switch (bType) {
      case STR_OLESTR:
	i = lstrlenW(pwsz);
	pwszTmp = (LPWSTR)CoTaskMemAlloc((i * sizeof(WCHAR)) + sizeof(WCHAR));
	if (!pwszTmp) return NULL;
	memcpy(pwszTmp, pwsz, (sizeof(WCHAR) * i) + sizeof(WCHAR));
	break;

      case STR_BSTR:
	pwszTmp = (LPWSTR)SysAllocString(pwsz);
	break;
    }

    return pwszTmp;
}

//=--------------------------------------------------------------------------=
// StringFromGuidA
//=--------------------------------------------------------------------------=
// returns an ANSI string from a CLSID or GUID
//
// Parameters:
//    REFIID               - [in]  clsid to make string out of.
//    LPSTR                - [in]  buffer in which to place resultant GUID.
//
// Output:
//    int                  - number of chars written out.
//
// Notes:
//
int StringFromGuidA
(
    REFIID   riid,
    LPSTR    pszBuf
)
{
    return wsprintf((char *)pszBuf, "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", riid.Data1, 
	    riid.Data2, riid.Data3, riid.Data4[0], riid.Data4[1], riid.Data4[2], 
	    riid.Data4[3], riid.Data4[4], riid.Data4[5], riid.Data4[6], riid.Data4[7]);

}

//=--------------------------------------------------------------------------=
// RegisterUnknownObject
//=--------------------------------------------------------------------------=
// registers a simple CoCreatable object.  nothing terribly serious.
// we add the following information to the registry:
//
// HKEY_CLASSES_ROOT\CLSID\<CLSID> = <ObjectName> Object
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\InprocServer32 = <path to local server>
//
// Parameters:
//    LPCSTR       - [in] Object Name
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means couldn't register it all
//
// Notes:
//
BOOL RegisterUnknownObject
(
    LPCSTR   pszObjectName,
    REFCLSID riidObject
)
{
    HKEY  hk = NULL, hkSub = NULL;
    char  szGuidStr[GUID_STR_LEN];
    DWORD dwPathLen, dwDummy;
    char  szScratch[MAX_PATH];
    long  l;

    // clean out any garbage
    //
    UnregisterUnknownObject(riidObject, NULL);

    // HKEY_CLASSES_ROOT\CLSID\<CLSID> = <ObjectName> Object
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\InprocServer32 = <path to local server>
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\InprocServer32  @ThreadingModel = Apartment
    //
    if (!StringFromGuidA(riidObject, szGuidStr)) goto CleanUp;
    wsprintf(szScratch, "CLSID\\%s", szGuidStr);
    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s Object", pszObjectName);
    l = RegSetValueEx(hk, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "InprocServer32", 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    dwPathLen = GetModuleFileName(g_hInstance, szScratch, sizeof(szScratch));
    if (!dwPathLen) goto CleanUp;

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, dwPathLen + 1);
    CLEANUP_ON_ERROR(l);

    l = RegSetValueEx(hkSub, "ThreadingModel", 0, REG_SZ, (BYTE *)"Apartment", sizeof("Apartment"));
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);

    return TRUE;

    // we are not very happy!
    //
  CleanUp:
    if (hk) RegCloseKey(hk);
    if (hkSub) RegCloseKey(hkSub);
    return FALSE;

}

//=--------------------------------------------------------------------------=
// RegisterAutomationObject
//=--------------------------------------------------------------------------=
// given a little bit of information about an automation object, go and put it
// in the registry.
// we add the following information in addition to that set up in
// RegisterUnknownObject:
//
//
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName> = <ObjectName> Object
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CLSID = <CLSID>
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CurVer = <ObjectName>.Object.<VersionNumber>
//
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber> = <ObjectName> Object
// HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber>\CLSID = <CLSID>
//
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\TypeLib = <LibidOfTypeLibrary>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\ProgID = <LibraryName>.<ObjectName>.<VersionNumber>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\VersionIndependentProgID = <LibraryName>.<ObjectName>
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    long         - [in] Version Number
//    REFCLSID     - [in] LIBID of type library
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means not all of it was registered
//
// Notes:
//
BOOL RegisterAutomationObject
(
    LPCSTR   pszLibName,
    LPCSTR   pszObjectName,
    long     lVersion,
    REFCLSID riidLibrary,
    REFCLSID riidObject
)
{
    HKEY  hk = NULL, hkSub = NULL;
    char  szGuidStr[GUID_STR_LEN];
    char  szScratch[MAX_PATH];
    long  l;
    DWORD dwDummy;

    // first register the simple Unknown stuff.
    //
    if (!RegisterUnknownObject(pszObjectName, riidObject)) return FALSE;

    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName> = <ObjectName> Object
    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CLSID = <CLSID>
    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>\CurVer = <ObjectName>.Object.<VersionNumber>
    //
    lstrcpy(szScratch, pszLibName);
    lstrcat(szScratch, ".");
    lstrcat(szScratch, pszObjectName);

    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0L, "",
		       REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE,
		       NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s Object", pszObjectName);
    l = RegSetValueEx(hk, NULL, 0L, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch)+1);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "CLSID", 0L, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    if (!StringFromGuidA(riidObject, szGuidStr))
	goto CleanUp;

    l = RegSetValueEx(hkSub, NULL, 0L, REG_SZ, (BYTE *)szGuidStr, lstrlen(szGuidStr) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    l = RegCreateKeyEx(hk, "CurVer", 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s.%s.%ld", pszLibName, pszObjectName, lVersion);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);

    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber> = <ObjectName> Object
    // HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber>\CLSID = <CLSID>
    //
    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s Object", pszObjectName);
    l = RegSetValueEx(hk, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "CLSID", 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szGuidStr, lstrlen(szGuidStr) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);

    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\ProgID = <LibraryName>.<ObjectName>.<VersionNumber>
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\VersionIndependentProgID = <LibraryName>.<ObjectName>
    // HKEY_CLASSES_ROOT\CLSID\<CLSID>\TypeLib = <LibidOfTypeLibrary>
    //
    if (!StringFromGuidA(riidObject, szGuidStr)) goto CleanUp;
    wsprintf(szScratch, "CLSID\\%s", szGuidStr);

    l = RegCreateKeyEx(HKEY_CLASSES_ROOT, szScratch, 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ|KEY_WRITE, NULL, &hk, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hk, "VersionIndependentProgID", 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s.%s", pszLibName, pszObjectName);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);

    l = RegCreateKeyEx(hk, "ProgID", 0, "", REG_OPTION_NON_VOLATILE,
		       KEY_READ | KEY_WRITE, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szScratch, "%s.%s.%ld", pszLibName, pszObjectName, lVersion);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szScratch, lstrlen(szScratch) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    l = RegCreateKeyEx(hk, "TypeLib", 0, "", REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE,
		       NULL, &hkSub, &dwDummy);

    if (!StringFromGuidA(riidLibrary, szGuidStr)) goto CleanUp;

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szGuidStr, lstrlen(szGuidStr) + 1);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);
    RegCloseKey(hk);
    return TRUE;

  CleanUp:
    if (hk) RegCloseKey(hkSub);
    if (hk) RegCloseKey(hk);
    return FALSE;
}

//=--------------------------------------------------------------------------=
// RegisterControlObject.
//=--------------------------------------------------------------------------=
// in addition to writing out automation object information, this function
// writes out some values specific to a control.
//
// What we add here:
//
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\Control
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\MiscStatus\1 = <MISCSTATUSBITS>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\ToolboxBitmap32 = <PATH TO BMP>
// HKEY_CLASSES_ROOT\CLSID\<CLSID>\Version = <VERSION>
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    long         - [in] Version Number
//    REFCLSID     - [in] LIBID of type library
//    REFCLSID     - [in] CLSID of the object
//    DWORD        - [in] misc status flags for ctl
//    WORD         - [in] toolbox id for control
//
// Output:
//    BOOL
//
// Notes:
//    - not the most terribly efficient routine.
//
BOOL RegisterControlObject
(
    LPCSTR   pszLibName,
    LPCSTR   pszObjectName,
    long     lMajorVersion,
    long     lMinorVersion,
    REFCLSID riidLibrary,
    REFCLSID riidObject,
    DWORD    dwMiscStatus,
    WORD     wToolboxBitmapId
)
{
    HKEY    hk, hkSub = NULL, hkSub2 = NULL;
    char    szTmp[MAX_PATH];
    char    szGuidStr[GUID_STR_LEN];
    DWORD   dwDummy;
    LONG    l;

    // first register all the automation information for this sucker.
    //
    if (!RegisterAutomationObject(pszLibName, pszObjectName, lMajorVersion, riidLibrary, riidObject)) return FALSE;

    // then go and register the control specific stuff.
    //
    StringFromGuidA(riidObject, szGuidStr);
    wsprintf(szTmp, "CLSID\\%s", szGuidStr);
    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, szTmp, 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    // create the control flag.
    //
    l = RegCreateKeyEx(hk, "Control", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    // now set up the MiscStatus Bits...
    //
    RegCloseKey(hkSub);
    hkSub = NULL;
    l = RegCreateKeyEx(hk, "MiscStatus", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    szTmp[0] = '0';
    szTmp[1] = '\0';
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, 2);
    CLEANUP_ON_ERROR(l);

    l = RegCreateKeyEx(hkSub, "1", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub2, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%d", dwMiscStatus);
    l = RegSetValueEx(hkSub2, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    RegCloseKey(hkSub2);
    CLEANUP_ON_ERROR(l);

    RegCloseKey(hkSub);

    // now set up the toolbox bitmap
    //
    GetModuleFileName(g_hInstance, szTmp, MAX_PATH);
    wsprintf(szGuidStr, ", %d", wToolboxBitmapId);
    lstrcat(szTmp, szGuidStr);

    l = RegCreateKeyEx(hk, "ToolboxBitmap32", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);
    CLEANUP_ON_ERROR(l);

    // now set up the version information
    //
    RegCloseKey(hkSub);
    l = RegCreateKeyEx(hk, "Version", 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkSub, &dwDummy);
    CLEANUP_ON_ERROR(l);

    wsprintf(szTmp, "%ld.%ld", lMajorVersion, lMinorVersion);
    l = RegSetValueEx(hkSub, NULL, 0, REG_SZ, (BYTE *)szTmp, lstrlen(szTmp) + 1);

  CleanUp:
    if (hk)
	RegCloseKey(hk);
    if (hkSub)
	RegCloseKey(hkSub);

    return (l == ERROR_SUCCESS) ? TRUE : FALSE;
}

//=--------------------------------------------------------------------------=
// UnregisterUnknownObject
//=--------------------------------------------------------------------------=
// cleans up all the stuff that RegisterUnknownObject puts in the
// registry.
//
// Parameters:
//    REFCLSID     - [in] CLSID of the object
//    BOOL         - [out] Returns TRUE if all keys were deleted for the 
//                         given CLSID.  Returns FALSE if only the
//                         InprocServer32 key or no keys were deleted.
//                         The caller can pass NULL if they don't care
//                         about what set of keys were removed.
//
// Output:
//    BOOL         - FALSE means not all of it was registered
//
// Notes:
//      WARNING! This routine assumes that all framework built components
//               and their predessors are in-process server 32-bit DLLs.
//               If other server types exist for control's CLSID
//               the CLSID entry will be blown away for these server types.
//
//               If the framework and the control are built as 16-bit components
//               and you unregister the control, the information will be left
//               in the registry.  You're on your own to make this work for 16-bit.
//
//               This routine *only* preserves the CLSID section if
//               a 16-bit InprocServer key is found.
//
BOOL UnregisterUnknownObject
(
    REFCLSID riidObject,
    BOOL *pfAllRemoved
)
{
    char szScratch[MAX_PATH];
    HKEY hk;
    BOOL f;
    long l;

    // Start on the assumption that we are going to blow away the entire section
    // for the given CLSID.  If this turns out to be a false assumption we'll
    // reset this to FALSE.
    //
    if (pfAllRemoved)
	*pfAllRemoved = TRUE;

    // delete everybody of the form
    //   HKEY_CLASSES_ROOT\CLSID\<CLSID> [\] *
    //
    if (!StringFromGuidA(riidObject, szScratch))
	return FALSE;

    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, "CLSID", 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    // See if a 16-bit in-proc server is register for this object
    // If so, then we don't want to disturb any of the keys except
    // the 32-bit in-proc server key
    //
    if (ExistInprocServer(hk, szScratch))
    {
	// Move one more level down to the InprocServer32 key and only delete it
	// We need to preserve the other keys for the InprocServer.
	//
	lstrcat(szScratch, "\\InprocServer32");
	if (pfAllRemoved)
		*pfAllRemoved = FALSE;
    }

    f = DeleteKeyAndSubKeys(hk, szScratch);

    RegCloseKey(hk);

    return f;                              
}

//=--------------------------------------------------------------------------=
// UnregisterAutomationObject
//=--------------------------------------------------------------------------=
// unregisters an automation object, including all of it's unknown object
// information.
//
// Parameters:
//    LPCSTR       - [in] Library Name
//    LPCSTR       - [in] Object Name
//    long         - [in] Version Number
//    REFCLSID     - [in] CLSID of the object
//
// Output:
//    BOOL         - FALSE means couldn't get it all unregistered.
//
// Notes:
//
BOOL UnregisterAutomationObject
(
    LPCSTR   pszLibName,
    LPCSTR   pszObjectName,
    long     lVersion,
    REFCLSID riidObject
)
{
    char szScratch[MAX_PATH];
    BOOL f;
    BOOL fAllRemoved;

    // first thing -- unregister Unknown information
    //
    f = UnregisterUnknownObject(riidObject, &fAllRemoved);
    if (!f) return FALSE;

    if (fAllRemoved)
    {
	// delete everybody of the form:
	//   HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName> [\] *
	//
	wsprintf(szScratch, "%s.%s", pszLibName, pszObjectName);
	f = DeleteKeyAndSubKeys(HKEY_CLASSES_ROOT, szScratch);
	if (!f) return FALSE;

	// delete everybody of the form
	//   HKEY_CLASSES_ROOT\<LibraryName>.<ObjectName>.<VersionNumber> [\] *
	//
	wsprintf(szScratch, "%s.%s.%ld", pszLibName, pszObjectName, lVersion);
	f = DeleteKeyAndSubKeys(HKEY_CLASSES_ROOT, szScratch);
	if (!f) return FALSE;
    }

    return TRUE;
}

//=--------------------------------------------------------------------------=
// UnregisterTypeLibrary
//=--------------------------------------------------------------------------=
// blows away the type library keys for a given libid.
//
// Parameters:
//    REFCLSID        - [in] libid to blow away.
//
// Output:
//    BOOL            - TRUE OK, FALSE bad.
//
// Notes:
//    - WARNING: this function just blows away the entire type library section,
//      including all localized versions of the type library.  mildly anti-
//      social, but not killer.
//
BOOL UnregisterTypeLibrary
(
    REFCLSID riidLibrary
)
{
    HKEY hk;
    char szScratch[GUID_STR_LEN];
    long l;
    BOOL f;

    // convert the libid into a string.
    //
    if (!StringFromGuidA(riidLibrary, szScratch))
	return FALSE;

    l = RegOpenKeyEx(HKEY_CLASSES_ROOT, "TypeLib", 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    f = DeleteKeyAndSubKeys(hk, szScratch);
    RegCloseKey(hk);
    return f;
}


//=--------------------------------------------------------------------------=
// DeleteKeyAndSubKeys
//=--------------------------------------------------------------------------=
// deletes a key and all of its subkeys.
//
// Parameters:
//    HKEY                - [in] delete the descendant specified
//    LPCSTR              - [in] i'm the descendant specified
//
// Output:
//    BOOL                - TRUE OK, FALSE baaaad.
//
// Notes:
//    - I don't feel too bad about implementing this recursively, since the
//      depth isn't likely to get all the great.
//    - Despite the win32 docs claiming it does, RegDeleteKey doesn't seem to
//      work with sub-keys under windows 95.
//
BOOL DeleteKeyAndSubKeys
(
    HKEY    hkIn,
    LPCSTR  pszSubKey
)
{
    HKEY  hk;
    char  szTmp[MAX_PATH];
    DWORD dwTmpSize;
    long  l;
    BOOL  f;

    l = RegOpenKeyEx(hkIn, pszSubKey, 0, KEY_ALL_ACCESS, &hk);
    if (l != ERROR_SUCCESS) return FALSE;

    // loop through all subkeys, blowing them away.
    //
    f = TRUE;
    while (f) {
	dwTmpSize = MAX_PATH;
	// We're deleting keys, so always enumerate the 0th
	l = RegEnumKeyEx(hk, 0, szTmp, &dwTmpSize, 0, NULL, NULL, NULL);
	if (l != ERROR_SUCCESS) break;
	f = DeleteKeyAndSubKeys(hk, szTmp);
    }

    // there are no subkeys left, [or we'll just generate an error and return FALSE].
    // let's go blow this dude away.
    //
    RegCloseKey(hk);
    l = RegDeleteKey(hkIn, pszSubKey);

    return (l == ERROR_SUCCESS) ? TRUE : FALSE;
}

//=--------------------------------------------------------------------------=
// GetHelpFilePath [RegisterTypeLib helper]
//=--------------------------------------------------------------------------=
// Returns the path to the Windows\Help directory
//
// Parameters:
//      char * - [in/out] Pointer to buffer that will contain
//                         the HELP path we will return to the caller
//      UINT   - [in] Number of bytes in the buffer
//
// Output:
//      UINT    - Returns the number of bytes actually copied to the buffer
// 
UINT GetHelpFilePath(char *pszPath, UINT cbPath)
{
	UINT cb;
	char szHelp[] = "\\HELP";

	// No need to continue if specified buffer size is zero or less
	//
	if (cbPath == 0)
		return 0;

	cb = GetWindowsDirectory(pszPath, cbPath);
	ASSERT(cb > 0, "Windows path is zero length");
	
	// Concatenate "\HELP" onto the Windows directory
	//
	cb += lstrlen(szHelp);
	if (cb < cbPath)
		lstrcat(pszPath, szHelp);
	else
		FAIL("Unable to add HELP path to Windows, buffer too small");

	return cb;              
}

//=--------------------------------------------------------------------------=
// ExistInprocServer [UnregisterUnknownObject Helper]
//=--------------------------------------------------------------------------=
// Checks for other servers such as (16-bit) InProcServer under the
// CLSID section for a given CLSID guid.
//
// Parameters:
//      HKEY    - [in]  HKEY top-level key where to look for the given
//                      CLSID
//      char *  - [in]  CLSID of server that we want to see if there
//                      is an (16-bit) InProcServer registered.
//
// Output:
//      BOOL    - Returns TRUE if a 16-bit in-proc server is registered
//                Returns FALSE if no 16-bit in-proc server is registered
//
BOOL ExistInprocServer(HKEY hkCLSID, char *pszCLSID)
{       
	HKEY hkInProcServer;
	LONG l;
	char szInprocServer[MAX_PATH];

	wsprintf(szInprocServer, "%s\\InprocServer", pszCLSID);
	
	// Attempt to open the 16-bit 'InProcServer' key
	//
	l = RegOpenKeyEx(hkCLSID, szInprocServer, 0, KEY_ALL_ACCESS, &hkInProcServer);
	if (l != ERROR_SUCCESS) return FALSE;   
	RegCloseKey(hkInProcServer);

	// If we made it this far, then the 'InProcServer' key must have been found
	//      
	return TRUE;
}

//=--------------------------------------------------------------------------=
// Conversion Routines
//=--------------------------------------------------------------------------=
// the following stuff is stuff used for the various conversion routines.
//
#define HIMETRIC_PER_INCH   2540
#define MAP_PIX_TO_LOGHIM(x,ppli)   ( (HIMETRIC_PER_INCH*(x) + ((ppli)>>1)) / (ppli) )
#define MAP_LOGHIM_TO_PIX(x,ppli)   ( ((ppli)*(x) + HIMETRIC_PER_INCH/2) / HIMETRIC_PER_INCH )

static  int     s_iXppli;            // Pixels per logical inch along width
static  int     s_iYppli;            // Pixels per logical inch along height
static  BYTE    s_fGotScreenMetrics; // Are above valid?

//=--------------------------------------------------------------------------=
// GetScreenMetrics
//=--------------------------------------------------------------------------=
// private function we call to set up various metrics the conversion routines
// will use.
//
// Notes:
//
static void GetScreenMetrics
(
    void
)
{
    HDC hDCScreen;

    // we have to critical section this in case two threads are converting
    // things at the same time
    //
    EnterCriticalSection(&g_CriticalSection);
    if (s_fGotScreenMetrics)
	goto Done;

    // we want the metrics for the screen
    //
    hDCScreen = GetDC(NULL);

    ASSERT(hDCScreen, "couldn't get a DC for the screen.");
    s_iXppli = GetDeviceCaps(hDCScreen, LOGPIXELSX);
    s_iYppli = GetDeviceCaps(hDCScreen, LOGPIXELSY);

    ReleaseDC(NULL, hDCScreen);
    s_fGotScreenMetrics = TRUE;

    // we're done with our critical seciton.  clean it up
    //
  Done:
    LeaveCriticalSection(&g_CriticalSection);
}

//=--------------------------------------------------------------------------=
// HiMetricToPixel
//=--------------------------------------------------------------------------=
// converts from himetric to Pixels.
//
// Parameters:
//    const SIZEL *        - [in]  dudes in himetric
//    SIZEL *              - [out] size in pixels.
//
// Notes:
//
void HiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix)
{
    GetScreenMetrics();

    // We got logical HIMETRIC along the display, convert them to pixel units
    //
    lpSizeInPix->cx = MAP_LOGHIM_TO_PIX(lpSizeInHiMetric->cx, s_iXppli);
    lpSizeInPix->cy = MAP_LOGHIM_TO_PIX(lpSizeInHiMetric->cy, s_iYppli);
}

//=--------------------------------------------------------------------------=
// PixelToHiMetric
//=--------------------------------------------------------------------------=
// converts from pixels to himetric.
//
// Parameters:
//    const SIZEL *        - [in]  size in pixels
//    SIZEL *              - [out] size in himetric
//
// Notes:
//
void PixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric)
{
    GetScreenMetrics();

    // We got pixel units, convert them to logical HIMETRIC along the display
    //
    lpSizeInHiMetric->cx = MAP_PIX_TO_LOGHIM(lpSizeInPix->cx, s_iXppli);
    lpSizeInHiMetric->cy = MAP_PIX_TO_LOGHIM(lpSizeInPix->cy, s_iYppli);
}

//=--------------------------------------------------------------------------=
// _MakePath
//=--------------------------------------------------------------------------=
// little helper routine for RegisterLocalizedTypeLibs and GetResourceHandle.
// not terrilby efficient or smart, but it's registration code, so we don't
// really care.
//
// Notes:
//
void _MakePath
(
    LPSTR pszFull,
    const char * pszName,
    LPSTR pszOut
)
{
    LPSTR psz;
    LPSTR pszLast;

    lstrcpy(pszOut, pszFull);
    psz = pszLast = pszOut;
    while (*psz) {
	if (*psz == '\\')
	    pszLast = AnsiNext(psz);
	psz = AnsiNext(psz);
    }

    // got the last \ character, so just go and replace the name.
    //
    lstrcpy(pszLast, pszName);
}

// from Globals.C
//
extern HINSTANCE    g_hInstResources;

//=--------------------------------------------------------------------------=
// GetResourceHandle
//=--------------------------------------------------------------------------=
// returns the resource handle.  we use the host's ambient Locale ID to
// determine, from a table in the DLL, which satellite DLL to load for
// localized resources.  If a satellite .DLL is not supported or not found
// the instance handle of the object is returned.
//
// Input:
//              lcid = 0 - [in, optional] Locale id that caller wants resource handle for
//                                                This overrides the default lcid.  If no lcid
//                                                                is provided or its 0, then the default lcid is used.
//
// Output:
//    HINSTANCE
//
// Notes:
//  The localized .DLL must be at the same location as the client object or control.
//  If the .DLL is not in the same location it will not be found and the resource
//  handle of the client object or control will be returned.
//
//  If a localized .DLL containing the full language abbreviation is not found,
//  the language abbreviation is truncated to two characters and the satellite
//  DLL with that name is attempted.  For example, the name MyCtlJPN.DLL and
//  MyCtlJP.DLL are both valid.
//
// If an lcid is passed in then we will attempt to find a satellite DLL matching 
// the desired lcid.  If the lcid is not 0, doesn't match the default lcid and a 
// library is found and loaded for it, we don't cache the library's instance handle.  
// Its up to the caller to call FreeLibrary on the returned handle.  The caller should
// compare the returned handle against g_hInstResources and g_hInstance.  If its not 
// equal to either of these handles then call FreeLibrary on it.  If it is equal to 
// either of these handles then the call must *not* call FreeLibrary on it.
//
HINSTANCE GetResourceHandle
(
    LCID lcid /* = 0 */
)
{
    int i;
    char szExtension[5], szModuleName[MAX_PATH];
    char szDllName[MAX_PATH], szFinalName[MAX_PATH];
    char szBaseName[MAX_PATH];
    HINSTANCE hInstResources;

    // crit sect this so that we don't screw anything up.
    //
    EnterCriticalSection(&g_CriticalSection);
    
    // If we fall out, we need to make sure we're returning the cached resource handle
    //
    hInstResources = g_hInstResources;

    // don't do anything if we don't have to
    // If the resource handle has already been cached and the passed in lcid matches the 
    // cached lcid or its the default, we just use the saved instance.
    //
    if ((hInstResources && (lcid == 0 || lcid == g_lcidLocale)) || !g_fSatelliteLocalization)
	goto CleanUp;
    
    if (lcid == 0)
		// Passed in LCID is zero so we want the instance for the default lcid.
		lcid = g_lcidLocale;

    // we're going to call GetLocaleInfo to get the abbreviated name for the
    // LCID we've got.
    //
    i = GetLocaleInfo(lcid, LOCALE_SABBREVLANGNAME, szExtension, sizeof(szExtension));
    if (!i) goto CleanUp;

    // we've got the language extension.  go and load the DLL name from the
    // resources and then tack on the extension.
    // please note that all inproc sers -must- have the string resource 1001
    // defined to the base name of the server if they wish to support satellite
    // localization.
    //
    i = LoadString(g_hInstance, 1001, szBaseName, sizeof(szBaseName));
    ASSERT(i, "This server doesn't have IDS_SERVERBASENAME defined in their resources!");
    if (!i) goto CleanUp;

    // got the basename and the extention. go and combine them, and then add
    // on the .DLL for them.
    //
    wsprintf(szDllName, "%s%s.DLL", szBaseName, szExtension);

    // try to load in the DLL
    //
    GetModuleFileName(g_hInstance, szModuleName, MAX_PATH);
    _MakePath(szModuleName, szDllName, szFinalName);

    hInstResources = LoadLibrary(szFinalName);

#if DEBUG

	// This will help diagnose problems where a machine may contain two satellite .DLLs
	// one using the long extension name and the other the short extension name.
	// We'll at least get a warning under DEBUG that we've got two plausible satellite
	// DLLs hanging around, but we're only going to use one of them:  the one with the long name.
	//
	if (hInstResources && lstrlen(szExtension) > 2)
	{
		HINSTANCE hinstTemp;
		char szExtTemp[MAX_PATH];

		// Truncate the language extension to the first two characters
		lstrcpy(szExtTemp, szExtension);        // Don't want to whack the extension as this will cause
											// the next if statement to always fail if we truncate it here.
											// Make a copy and use it.

		szExtTemp[2] = '\0';
		wsprintf(szDllName, "%s%s.DLL", szBaseName, szExtTemp);         
		_MakePath(szModuleName, szDllName, szFinalName);

		// Try loading the localized .DLL using the truncated lang abbreviation
		hinstTemp = LoadLibrary(szFinalName);
		ASSERT(hinstTemp == NULL, "Satellite DLLs with both long and short language abbreviations found.  Using long abbreviation.");
	}

#endif   // DEBUG

    if (!hInstResources && lstrlen(szExtension) > 2)
    {
		// Truncate the language extension to the first two characters
		szExtension[2] = '\0';  
		wsprintf(szDllName, "%s%s.DLL", szBaseName, szExtension);               
		   _MakePath(szModuleName, szDllName, szFinalName);

		// Try loading the localized .DLL using the truncated lang abbreviation
		hInstResources = LoadLibrary(szFinalName);
    }

    // if we couldn't find it with the entire LCID, try it with just the primary
    // langid
    //
    if (!hInstResources) {
	LPSTR psz;
	LCID lcid;
	lcid = MAKELCID(MAKELANGID(PRIMARYLANGID(LANGIDFROMLCID(g_lcidLocale)), SUBLANG_DEFAULT), SORT_DEFAULT);
	i = GetLocaleInfo(lcid, LOCALE_SABBREVLANGNAME, szExtension, sizeof(szExtension));
	if (!i) goto CleanUp;

	// reconstruct the DLL name.  the -7 is the length of XXX.DLL. mildly
	// hacky, but it should be fine.  there are no DBCS lang identifiers.
	// finally, retry the load
	//
	psz = szFinalName + lstrlen(szFinalName);
	memcpy((LPBYTE)psz - 7, szExtension, 3);
	hInstResources = LoadLibrary(szFinalName);
    }

  CleanUp:

    // if we couldn't load the DLL for some reason, then just return the
    // current resource handle, which is good enough.
    //
    if (!hInstResources) hInstResources = g_hInstance;

    if (!g_hInstResources && (lcid == 0 || lcid == g_lcidLocale))
		// We only cache the instance handle for the default LCID.
		// For all other passed in lcid values we will LoadLibrary on the satellite DLL each time.
		// Its recommended that the calling app cache the returned instance handle for the given
		// lcid passed in.
		//
		g_hInstResources = hInstResources;

    LeaveCriticalSection(&g_CriticalSection);

    return hInstResources;
}

