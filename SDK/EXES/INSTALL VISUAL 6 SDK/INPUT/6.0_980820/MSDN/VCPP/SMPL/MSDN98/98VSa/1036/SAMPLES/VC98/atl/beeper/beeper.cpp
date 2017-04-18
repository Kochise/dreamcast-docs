// beeper.cpp : Implementation of CBeeperApp and DLL registration.
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "prebeep.h"
#include "initguid.h"
#include "beepres.h"
#include "beeper.h"
#include "beepobj.h"

#define IID_DEFINED
#include "beeper_i.c"

CMyModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Beeper, CBeeper)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
//
#ifndef _WINDLL
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
	LPTSTR lpCmdLine, int /*nShowCmd*/)
{
	HRESULT hRes = CoInitialize(NULL);
//  If you are running on NT 4.0 or higher you can use the following call
//  instead to make the EXE free threaded.
//  This means that calls come in on a random RPC thread
//  HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));
	_Module.Init(ObjectMap, hInstance);
	_Module.dwThreadID = GetCurrentThreadId();
	TCHAR szTokens[] = _T("-/");

	LPTSTR lpszToken = _tcstok(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (_tcsicmp(lpszToken, _T("UnregServer"))==0)
			return _Module.UnregisterServer();
		else if (_tcsicmp(lpszToken, _T("RegServer"))==0)
			return _Module.RegisterServer(TRUE);
		lpszToken = _tcstok(NULL, szTokens);
	}

	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER,
		REGCLS_MULTIPLEUSE);
	ATLASSERT(SUCCEEDED(hRes));

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
		DispatchMessage(&msg);

	_Module.RevokeClassObjects();

	CoUninitialize();
	return 0;
}
#else
/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	lpReserved; // to avoid /W4 warning when _MERGE_PROXYSTUB not defined
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}
/////////////////////////////////////////////////////////////////////////////
//

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	HRESULT hRes = S_OK;
#ifdef _MERGE_PROXYSTUB
	hRes = PrxDllRegisterServer();
	if (FAILED(hRes))
		return hRes;
#endif
	// registers object, typelib and all interfaces in typelib
	hRes = _Module.RegisterServer(TRUE);
	return hRes;
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllUnregisterServer(void)
{
	HRESULT hRes = S_OK;
	_Module.UnregisterServer();
#ifdef _MERGE_PROXYSTUB
	hRes = PrxDllUnregisterServer();
#endif
	return hRes;
}

#endif //!_WINDLL
