/********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * dllmain.cpp
 *
 * Description
 *   The implementation for DllMain, DllGetClassObject, and 
 *   DllCanUnloadNow (exported functions).
 ********************************************************************/

#include <windows.h>
#include "global.h"
#include "ieui.h"

/********************************************************************
 * Global Variables
 ********************************************************************/
HINSTANCE         g_hinst               = NULL; // Instance of DLL
HINSTANCE         g_hinstURLMON         = NULL; // Instance of URLMON
HINSTANCE         g_hinstMSHTML         = NULL; // Instance of MSHTML
CREATEURLMONIKER *g_pfnCreateUrlMoniker = NULL; // CreateUrlMoniker function
SHOWHTMLDIALOGFN *g_pfnShowHTMLDialog   = NULL; // ShowHTMLDialog function
ULONG             g_ulLocks             = 0;    // Number of server locks

/********************************************************************
 * DllMain 
 *
 * Description
 *    Handle initialization and shutdown of DLL. It loads the DLLs 
 *    and functions that it will be frequently using.
 *
 * Parameters
 *    None.
 *
 * Result
 *    TRUE   All ok
 ********************************************************************/
BOOL WINAPI DllMain(HANDLE hinst, DWORD dwReason, LPVOID lpvReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        // Keep track of DLL instance handle while DLL is active.
        g_hinst = (HINSTANCE)hinst;

        // Load all the functions that are used frequently from the proper DLLs.

        // From URLMON:
        g_hinstURLMON = LoadLibrary(L"URLMON");
        if (g_hinstURLMON)
        {
            g_pfnCreateUrlMoniker = (CREATEURLMONIKER*)GetProcAddress(g_hinstURLMON, L"CreateURLMoniker");
        }

        // From MSHTML:
        g_hinstMSHTML = LoadLibrary(L"MSHTML");
        if (g_hinstMSHTML)
        {
            g_pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(g_hinstMSHTML, L"ShowHTMLDialog");
        }
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        // Free all the libaries that this DLL has been using.

        if (g_hinstURLMON)
        {
            g_pfnCreateUrlMoniker = NULL;
            FreeLibrary(g_hinstURLMON);
            g_hinstURLMON = NULL;
        }
 
        if (g_hinstMSHTML)
        {
            g_pfnShowHTMLDialog = NULL;
            FreeLibrary(g_hinstMSHTML);
            g_hinstMSHTML = NULL;
        }

        g_hinst = NULL;
    }

    return TRUE;
}

/********************************************************************
 * DllCanUnloadNow
 *
 * Description
 *    Return if it is okay to unload the DLL (no objects still in use).
 *
 * Parameters
 *    None.
 *
 * Result
 *    S_OK     If no objects in DLL are still in use.
 *    S_FALSE  If any objects in DLL are still in use.
 ********************************************************************/
STDAPI DllCanUnloadNow(void)
{
    return (g_ulLocks) ? S_FALSE : S_OK;
}

/********************************************************************
 * DllGetClassObject
 *
 * Description
 *    Create requested object and return requested interface. Object
 *    should have a reference count of 1 when returned to caller.
 *
 * Parameters
 *    rclsid  in  Class ID of object to create.
 *    riid    in  Interface ID of object to create.
 *    ppvObj  out Pointer to requested interface pointer.
 *
 * Result
 *    S_OK           Success.
 *    E_POINTER      If ppvObj not supplied.
 *    E_NOINTERFACE  If IID is not known. 
 *    E_FAIL         If CLSID is not known.
 ********************************************************************/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvObj)
{
    // Validate return parameter.
    if (!ppvObj)
    {
        return E_POINTER;
    }

    // Initialize return pointer to NULL;
    *ppvObj = NULL;

    // Check for known and handled interface ID.
    if ((IID_IUnknown != riid) && (IID_IClassFactory != riid))
    {
        return E_NOINTERFACE;
    }

    // Check for known and handled class ID.
    if (CLSID_ieui == rclsid)
    {
        // Create new protocol handler object with initial ref count = 0.
        CIEUI *pIEUI = new CIEUI;

        // Get requested interface (will make ref count = 1)
        if (FAILED(pIEUI->QueryInterface(riid, ppvObj)))
        {
            // If could not get requested interface, delete object.
            // Do not use release since ref count = 0.
            delete pIEUI;
        }
        else
        {
            // Got requested interface.
            return S_OK;
        }
    }

    // No handled interface or no handled class ID.
    return E_FAIL;
}


