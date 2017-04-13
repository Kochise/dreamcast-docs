//=--------------------------------------------------------------------------=
// ToDoSvr.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1997  Microsoft Corporation.  All Rights Reserved.
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
#include "ToDoSvrIfc.H"
#include "CDocObj.H"
#include "Globals.H"
#include "Util.H"
#include "Resource.H"

#include "ToDoCtl.H"
#include "ToDoPPG.H"

// needed for ASSERTs and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// our Libid.  This should be the LIBID from the Type library, or NULL if you
// don't have one.
//
const CLSID *g_pLibid = &LIBID_ToDoSvrObjects;

//=--------------------------------------------------------------------------=
// Set this up if you want to have a window proc for your parking window. This
// is really only interesting for Sub-classed controls that want, in design
// mode, certain messages that are sent only to the parent window.
//
WNDPROC g_ParkingWindowProc = NULL;

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
const VARIANT_BOOL g_fSatelliteLocalization = FALSE;
LCID               g_lcidLocale = MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT);


//=--------------------------------------------------------------------------=
// your license key and where under HKEY_CLASSES_ROOT_LICENSES it's sitting
//
const WCHAR g_wszLicenseKey [] = L"";
const WCHAR g_wszLicenseLocation [] = L"";


//=--------------------------------------------------------------------------=
// This Table describes all the automatible objects in your automation server.
// See AutomationObject.H for a description of what goes in this structure
// and what it's used for.
//
// DOCOBJ: Use DOCOBJECT macro to describe our DocObject, not CONTROLOBJECT
//         as usual.
//
OBJECTINFO g_ObjectInfo[] = {
    DOCOBJECT(ToDo),
    PROPERTYPAGE(ToDoGeneral),
    EMPTYOBJECT
};

const char g_szLibName[] = "ToDoSvr";

//=--------------------------------------------------------------------------=
// InitializeLibrary
//=--------------------------------------------------------------------------=
// called from DllMain:DLL_PROCESS_ATTACH.  allows the user to do any sort of
// initialization they want to.
//
// Notes:
//
void WINAPI InitializeLibrary(void)
{
    // TODO: initialization here.  control window class should be set up in
    // RegisterClassData.
}

//=--------------------------------------------------------------------------=
// UninitializeLibrary
//=--------------------------------------------------------------------------=
// called from DllMain:DLL_PROCESS_DETACH.  allows the user to clean up anything
// they want.
//
// Notes:
//
void WINAPI UninitializeLibrary(void)
{
    // TODO: uninitialization here.  control window class will be unregistered
    // for you, but anything else needs to be cleaned up manually.
    // Please Note that the Window 95 DLL_PROCESS_DETACH isn't quite as stable
    // as NT's, and you might crash doing certain things here ...
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
BOOL WINAPI CheckForLicense(void)
{
    // TODO: you should make sure the machine has your license key here.
    // this is typically done by looking in the registry.
    //
    return TRUE;
}

//=--------------------------------------------------------------------------=
// CheckLicenseKey
//=--------------------------------------------------------------------------=
// when IClassFactory2::CreateInstanceLic is called, a license key is passed
// in, and then passed on to this routine.  users should return a boolean 
// indicating whether it is a valid license key or not
//
// Parameters:
//    LPWSTR          - [in] the key to check
//
// Output:
//    BOOL            - false means it's not valid, true otherwise
//
// Notes:
//
BOOL WINAPI CheckLicenseKey(LPWSTR pwszKey)
{
    // TODO: check the license key against your values here and make sure it's
    // valid.
    //
    return TRUE;
}

//=--------------------------------------------------------------------------=
// GetLicenseKey
//=--------------------------------------------------------------------------=
// returns our current license key that should be saved out, and then passed
// back to us in IClassFactory2::CreateInstanceLic
//
// Parameters:
//    none
//
// Output:
//    BSTR                 - key or NULL if Out of memory
//
// Notes:
//
BSTR WINAPI GetLicenseKey(void)
{
    // TODO: return your license key here.
    //
    return SysAllocString(L"");
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
BOOL WINAPI RegisterData(void)
{
    // DOCOBJ: DocObjects need some additional registry entries.
    //         Register them here!

    // read file extension and file description strings from resources
    char szExt[20];
    if (!LoadString(GetResourceHandle(),  
                    DEFAULTEXTIDOFDOCOBJECT(OBJECT_TYPE_CTLTODO),
                    szExt,
                    sizeof(szExt)))
        szExt[0] = '\0';

    char szDesc[40];
    if (!LoadString(GetResourceHandle(),  
                    FILEDESCRIPTIONIDOFDOCOBJECT(OBJECT_TYPE_CTLTODO),
                    szDesc,
                    sizeof(szDesc)))
        szDesc[0] = '\0';

    // register special docobj keys
    return RegisterDocObject(g_szLibName, NAMEOFOBJECT(OBJECT_TYPE_CTLTODO),
                             CLSIDOFOBJECT(OBJECT_TYPE_CTLTODO), 
                             MISCFLAGSOFDOCOBJECT(OBJECT_TYPE_CTLTODO),
                             PRINTOFDOCOBJECT(OBJECT_TYPE_CTLTODO),
                             szExt, szDesc);
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
BOOL WINAPI UnregisterData(void)
{
    // TODO: any additional registry cleanup that you might wish to do.
    //
    return TRUE;
}


//=--------------------------------------------------------------------------=
// CRT stubs
//=--------------------------------------------------------------------------=
// these two things are here so the CRTs aren't needed. this is good.
//
// basically, the CRTs define this to suck in a bunch of stuff.  we'll just
// define them here so we don't get an unresolved external.
//
// TODO: if you are going to use the CRTs, then remove this line.
//
// extern "C" int _fltused = 1;

extern "C" int _purecall(void)
{
  FAIL("Pure virtual function called.");
  return 0;
}

