// brkpntmgr.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f brkpntmgrps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "brkpntmgr.h"

#include "brkpntmgr_i.c"
#include "BrkPnts.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_BrkPnts, CBrkPnts)
END_OBJECT_MAP()

class CBrkpntmgrApp : public CWinApp
{
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
};

CBrkpntmgrApp theApp;

BOOL CBrkpntmgrApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_BRKPNTMGRLib);
    return CWinApp::InitInstance();
}

int CBrkpntmgrApp::ExitInstance()
{
    _Module.Term();
    return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    HRESULT hr = _Module.UnregisterServer();

#if _WIN32_WINNT >= 0x0400
    if (FAILED(hr))
        return hr;

    hr = UnRegisterTypeLib(LIBID_BRKPNTMGRLib, 1, 0, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SYS_WIN32);
#endif

    return hr;
}


