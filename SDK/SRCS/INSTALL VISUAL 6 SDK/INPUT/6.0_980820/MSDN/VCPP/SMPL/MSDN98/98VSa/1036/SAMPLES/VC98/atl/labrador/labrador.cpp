// Labrador.cpp : Implementation of EXE registration.
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

#include "prelab.h"
#include "labres.h"
#include "initguid.h"
#include "Labrador.h"
#include "LabObj.h"

#define IID_DEFINED
#include "Labrador_i.c"

CMyModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Labrador, CLabrador)
END_OBJECT_MAP()


#ifdef _WINDLL
#error This project does not support DLL, only EXE targets
#endif

/////////////////////////////////////////////////////////////////////////////
// EXE Entry Point

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

	// have to remember the hread ID to post a WM_QUIT to it to shut down
	// see the implementation of CMyModule::Unlock() for details
	_Module.dwThreadID = GetCurrentThreadId();

	// see if we have to do anything with the registry
	TCHAR szTokens[] = _T("-/");
	LPTSTR lpszToken = _tcstok(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (_tcsicmp(lpszToken, _T("UnregServer"))==0)
			return _Module.UnregisterServer();
		else if (_tcsicmp(lpszToken, _T("RegServer"))==0)
		{
			// passing FALSE because we did not link the typelib
			// into the EXE itself
			return _Module.RegisterServer(FALSE);
		}
		lpszToken = _tcstok(NULL, szTokens);
	}

	// We are an EXE, just register all the class factories at startup
	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
	ATLASSERT(SUCCEEDED(hRes));

	// wait until we get a WM_QUIT
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
		DispatchMessage(&msg);

	// unregister all the class factories
	_Module.RevokeClassObjects();

	CoUninitialize();
	return 0;
}
