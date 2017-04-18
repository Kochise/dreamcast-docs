/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    LibMain.cpp

Abstract:

    LibMain for ADsSmp.dll

Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"
#pragma hdrstop


//  Globals
HINSTANCE g_hInst = NULL;

ULONG g_ulObjCount = 0L;        // Number of objects alive in adssmp.dll
ULONG g_ulLockCount = 0L;       // Number of server locks on adssmp.dll


//+------------------------------------------------------------------------
//
//  Macro that calculates the number of elements in a statically-defined
//  array.
//-------------------------------------------------------------------------
#define ARRAY_SIZE(_a)  (sizeof(_a) / sizeof(_a[0]))

//+------------------------------------------------------------------------
// Create static Namespace and Provider class factory objects
//-------------------------------------------------------------------------
CSampleDSProviderCF g_cfProvider;
CSampleDSNamespaceCF g_cfNamespace;


//+------------------------------------------------------------------------
//
//  ads class factory lookup table
//
//-------------------------------------------------------------------------

struct CLSTABLE
{
    const CLSID *   pclsid;
    IClassFactory * pCF;
};



CLSTABLE g_aclscache[] =
{
    &CLSID_SampleDSProvider,                      &g_cfProvider,
    &CLSID_SampleDSNamespace,                     &g_cfNamespace,
};


//+---------------------------------------------------------------
//
//  Function:   DllGetClassObject
//
//  Synopsis:   Standard DLL entrypoint for locating class factories
//
//----------------------------------------------------------------

STDAPI
DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID FAR* ppv)
{
    HRESULT         hr;
    size_t          i;

    for (i = 0; i < ARRAY_SIZE(g_aclscache); i++)
    {
        if (IsEqualCLSID(clsid, *g_aclscache[i].pclsid))
        {
            hr = g_aclscache[i].pCF->QueryInterface(iid, ppv);
            RRETURN(hr);
        }
    }

    *ppv = NULL;

    return E_NOINTERFACE;
}

//+---------------------------------------------------------------
//
//  Function:   DllCanUnloadNow
//
//  Synopsis:   Standard DLL entrypoint to determine if DLL can be unloaded
//
//---------------------------------------------------------------

STDAPI DllCanUnloadNow(void) {
    if (0L==g_ulObjCount && 0L==g_ulLockCount) return ResultFromScode(S_OK);
    else return ResultFromScode(S_FALSE);
}     

//+---------------------------------------------------------------
//
//  Function:   DllMain
//
//  Synopsis:   Standard DLL initialization entrypoint
//
//---------------------------------------------------------------

BOOL WINAPI
LibMain(HINSTANCE hInst, DWORD dwReason, LPVOID pvReserved)
{
        
    // Check our compatibility with the OLE runtime.
    // We are compatible with any later major version,
    // or the same major version with equal or greater minor version.
    if (!IsCompatibleOleVersion(OLE_MAJ_VER, OLE_MIN_VER))
    {
        return FALSE;
    }

    switch (dwReason){
    case DLL_PROCESS_ATTACH:

        g_hInst = hInst;
        break;


    case DLL_PROCESS_DETACH:


    default:
        break;
    }

    return TRUE;
}

BOOL
IsCompatibleOleVersion(WORD wMaj, WORD wMin)
{
    // Check our compatibility with the OLE runtime.
    // We are compatible with any later major version,
    // or the same major version with equal or greater minor version.
    DWORD ov = OleBuildVersion();
    return HIWORD(ov) > wMaj || (HIWORD(ov) == wMaj && LOWORD(ov) >= wMin);
}



//+---------------------------------------------------------------------------
//
//  Function:   DllMain
//
//  Synopsis:   entry point for NT - post .546
//
//----------------------------------------------------------------------------
EXTERN_C BOOL WINAPI
DllMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
    return LibMain((HINSTANCE)hDll, dwReason, lpReserved);
}
