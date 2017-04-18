//=--------------------------------------------------------------------------=
// Card.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// various routines et all that aren't in a file for a particular automation
// object, and don't need to be in the generic ole automation code.
//
#define INITOBJECTS                // define the descriptions for our objects

#include "IPServer.H"
#include "LocalSrv.H"


#include "LocalObj.H"
#include "CtrlObj.H"
#include "Globals.H"
#include "Util.H"
#include "Resource.H"

#include "CardCtl.H"
#include "CardPPG.H"
#include "cathelp.H"

#include "carddraw.h"

// Control Globals
//
CRITICAL_SECTION drawCritSec;
HBITMAP cardcacheMem[14*4+14];	// 4 suites * 14 cards + 14 card backs

const IID IID_ICatRegister = {0x0002E012,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
const CATID CATID_SafeForScripting = {0x7dd95801,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};
const CATID CATID_SafeForInitializing = {0x7dd95802,0x9882,0x11cf,{0x9f,0xa9,0x00,0xaa,0x00,0x6c,0x42,0xc4}};

// needed for ASSERTs and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// our Libid.  This should be the LIBID from the Type library, or NULL if you
// don't have one.
//
const CLSID *g_pLibid = &LIBID_CardObjects;


//=--------------------------------------------------------------------------=
// Localization Information
//
// We need the following two pieces of information:
//    a. whether or not this DLL uses satellite DLLs for localization.  if
//       not, then the lcidLocale is ignored, and we just always get resources
//       from the server module file.
//    b. the ambient LocaleID for this in-proc server.  Controls calling
//       GetResourceHandle() will set this up automatically, but anybody
//       else will need to be sure that it's set up properly.
//
const VARIANT_BOOL    g_fSatelliteLocalization =  FALSE;
LCID            g_lcidLocale = MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT);


//=--------------------------------------------------------------------------=
// your license key and where under HKEY_CLASSES_ROOT_LICENSES it's sitting
//
const WCHAR g_wszLicenseKey [] = L"";
const WCHAR g_wszLicenseLocation [] = L"";


WNDPROC g_ParkingWindowProc = NULL;

//=--------------------------------------------------------------------------=
// This Table describes all the automatible objects in your automation server.
// See AutomationObject.H for a description of what goes in this structure
// and what it's used for.
//
OBJECTINFO g_ObjectInfo[] = {
    CONTROLOBJECT(Card),
    PROPERTYPAGE(CardGeneral),
    EMPTYOBJECT
};

const char g_szLibName[] = "ActiveXSDKCard";

//=--------------------------------------------------------------------------=
// IntializeLibrary
//=--------------------------------------------------------------------------=
// called from DllMain:DLL_PROCESS_ATTACH.  allows the user to do any sort of
// initialization they want to.
//
// Notes:
//
void WINAPI InitializeLibrary (void )
{
	InitializeCriticalSection( &drawCritSec );
}

//=--------------------------------------------------------------------------=
// UninitializeLibrary
//=--------------------------------------------------------------------------=
// called from DllMain:DLL_PROCESS_DETACH.  allows the user to clean up anything
// they want.
//
// Notes:
//
void WINAPI UninitializeLibrary
(
    void
)
{
	DeleteCriticalSection( &drawCritSec );

	for( int t = 0; t < sizeof(cardcacheMem)/sizeof(cardcacheMem[0]); t++ )
		if( cardcacheMem[t] )
			DeleteObject( cardcacheMem[t] );
}


//=--------------------------------------------------------------------------=
// CheckForLicense
//=--------------------------------------------------------------------------=
// users can implement this if they wish to support Licensing.  otherwise,
// they can just return TRUE all the time.
//
// Parameters:
//    none
//
// Output:
//    BOOL            - TRUE means the license exists, and we can proceed
//                      FALSE means we're not licensed and cannot proceed
//
// Notes:
//    - implementers should use g_wszLicenseKey and g_wszLicenseLocation
//      from the top of this file to define their licensing [the former
//      is necessary, the latter is recommended]
//
BOOL WINAPI CheckForLicense
(
    void
)
{
    // TODO: decide whether or not your server is licensed in this function.
    // people who don't want to bother with licensing should just return
    // true here always.  g_wszLicenseKey and g_wszLicenseLocation are
    // used by IClassFactory2 to do some of the licensing work.
    //
    return TRUE;
}

//=--------------------------------------------------------------------------=
// RegisterData
//=--------------------------------------------------------------------------=
// lets the inproc server writer register any data in addition to that in
// any other objects.
//
// Output:
//    BOOL            - false means failure.
//
// Notes:
//
BOOL WINAPI RegisterData
(
    void
)
{
	HRESULT hr;

	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls that are safely scriptable");
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data");
	hr = RegisterCLSIDInCategory(CLSID_Card, CATID_SafeForScripting);
	hr = RegisterCLSIDInCategory(CLSID_Card, CATID_SafeForInitializing);
    return TRUE;
}

//=--------------------------------------------------------------------------=
// UnregisterData
//=--------------------------------------------------------------------------=
// inproc server writers should unregister anything they registered in
// RegisterData() here.
//
// Output:
//    BOOL            - false means failure.
//
// Notes:
//
BOOL WINAPI UnregisterData
(
    void
)
{
	HRESULT hr;

	hr = UnRegisterCLSIDInCategory(CLSID_Card, CATID_SafeForScripting);
	hr = UnRegisterCLSIDInCategory(CLSID_Card, CATID_SafeForInitializing);
    return TRUE;
}

BOOL WINAPI      CheckLicenseKey(LPWSTR wszCheckme)
{
	return TRUE;
}

BSTR WINAPI      GetLicenseKey(void)
{
	return NULL;
}

