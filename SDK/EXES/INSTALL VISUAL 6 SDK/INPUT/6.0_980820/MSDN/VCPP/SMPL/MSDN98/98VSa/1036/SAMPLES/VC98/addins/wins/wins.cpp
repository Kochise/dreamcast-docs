// wins.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f winsps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "wins.h"
#include "winsapp.h"

#include "wins_i.c"
#include "WindowsList.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_WindowsList, CWindowsList)
END_OBJECT_MAP()

BEGIN_MESSAGE_MAP(CWinsApp, CWinApp)
	//{{AFX_MSG_MAP(CWinsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString strMainKey = _T("Software\\Microsoft\\devstudio\\AddIns\\Wins.WindowsList.1\\");
// don't put in 6.0 key as this will make msdev think it is already registered.
// Then msdev crashes because it gets an empty CString and does a memcpy on it.


CWinsApp theApp;

BOOL CWinsApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_WINSLib);
	CRegKey regKey;

	long lRes;
	unsigned long lCol, lSize;

	lRes = regKey.Create(HKEY_CURRENT_USER, strMainKey);
	if (SUCCEEDED(lRes))
	{
		regKey.QueryValue(m_fAutoSize, _T("AutoSize"));
		regKey.QueryValue(m_fAutoVis, _T("AutoVis"));
		regKey.QueryValue(m_fAutoDir, _T("AutoDir"));
		regKey.QueryValue(lCol, _T("SortedCol"));
		m_iSortedCol = (int)lCol;
		regKey.QueryValue(lSize, _T("Width"));
		if (lSize == 0)
			lSize = DEFAULTWIDTH;
		m_lSize = (int)lSize;
	}
    return CWinApp::InitInstance();
}

int CWinsApp::ExitInstance()
{
	CRegKey regKey;
	long lRes;

	lRes = regKey.Create(HKEY_CURRENT_USER, strMainKey);
	regKey.SetValue(m_fAutoSize, _T("AutoSize"));
	regKey.SetValue(m_fAutoVis, _T("AutoVis"));
	regKey.SetValue(m_fAutoDir, _T("AutoDir"));
	regKey.SetValue(m_iSortedCol, _T("SortedCol"));
	regKey.SetValue(m_lSize, _T("Width"));

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
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    // registers object, typelib and all interfaces in typelib
 	// Register description of this add-in object in its own
	//  "/Description" subkey.
	

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

    hr = UnRegisterTypeLib(LIBID_WINSLib, 1, 0, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SYS_WIN32);
#endif

    return hr;
}


