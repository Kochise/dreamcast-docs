/********************************************************************
 * vibectrl.cpp
 *
 * Description
 *    Implementation of standard COM exported functions.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "stdafx.h"         // precompiled headers
#include "control.h"        // CVibrationControl
#include "vibectrl_i.c"     // Class IDs and Interface IDs

/********************************************************************
 * Global variables
 ********************************************************************/
CComModule _Module;         // Instance of this DLL

BEGIN_OBJECT_MAP(ObjectMap) // Objects created by this DLL
    OBJECT_ENTRY(CLSID_VibrationControl, CVibrationControl)
END_OBJECT_MAP()

/********************************************************************
 * DllMain 
 *
 * Description
 *    Handle initialization and shutdown of DLL. 
 *
 * Parameters
 *    hInstance     handle for the DLL
 *    dwReason      initializing or shutting down
 *    lpReserved    not used
 *
 * Result
 *    TRUE          All ok
 ********************************************************************/
BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, (HINSTANCE) hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
        _Module.Term();
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
 *    S_OK          no objects in DLL are still in use
 *    S_FALSE       objects in DLL are still in use
 ********************************************************************/
STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/********************************************************************
 * DllGetClassObject
 *
 * Description
 *    Create requested object and return requested interface. Object
 *    should have a reference count of 1 when returned to caller.
 *
 * Parameters
 *    rclsid        Class ID of object to create.
 *    riid          Interface ID of object to create.
 *    ppvObj        Pointer to requested interface pointer.
 *
 * Result
 *    S_OK           Success.
 *    E_POINTER      if ppvObj not supplied.
 *    E_NOINTERFACE  if IID is not known. 
 *    E_FAIL         if CLSID is not known.
 ********************************************************************/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}
