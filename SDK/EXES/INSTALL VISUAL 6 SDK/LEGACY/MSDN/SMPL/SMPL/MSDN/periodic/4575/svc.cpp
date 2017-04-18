#define INITGUID
#include <windows.h>
#include "s816.h"
#include "sharedpoint.h"
#include "CF.H"

DWORD g_cLocks = 0;
#ifdef EXESVC
const BOOL bIsDll = TRUE;
#else
const BOOL bIsDll = FALSE;
#endif

void SvcLock()
{
    g_cLocks++;
}

void SvcUnlock()
{
    if (--g_cLocks && !bIsDll)
        PostQuitMessage(0);
}

CoClassFactory<CoSharedPoint> g_classFactory;

STDAPI DllGetClassObject(REFCLSID rclsid,
                         REFIID riid,
                         void **ppv)
{
    *ppv = 0;
    if (rclsid == CLSID_CoSharedPoint)
        return g_classFactory.QueryInterface(riid, ppv);
    else
        return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow()
{
    return g_cLocks ? S_FALSE : S_OK;
}

HINSTANCE g_hInstance;
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason,
                    void *)
{
    if (dwReason == DLL_PROCESS_ATTACH)
        g_hInstance = hInstance;
    return TRUE;
}

STDAPI DllRegisterServer()
{
    TCHAR szModuleName[MAX_PATH];
    GetModuleFileName(g_hInstance, szModuleName, sizeof(szModuleName));
    
    TCHAR tszGuid[64];
    OLECHAR oszGuid[64];
    StringFromGUID2(CLSID_CoSharedPoint, oszGuid, sizeof(oszGuid));
    lstrcpy(tszGuid, __TEXTCVAR(oszGuid));
    
    TCHAR szKeyName[1024];
    wsprintf(szKeyName, TEXT("CLSID\\%s\\InprocServer32"), tszGuid);

    RegSetValue(HKEY_CLASSES_ROOT, szKeyName, 
                REG_SZ, szModuleName, lstrlen(szModuleName));

    wsprintf(szKeyName, TEXT("CLSID\\%s\\InprocHandler32"), tszGuid);
    RegSetValue(HKEY_CLASSES_ROOT, szKeyName, 
                REG_SZ, szModuleName, lstrlen(szModuleName));


    return NOERROR;
}

