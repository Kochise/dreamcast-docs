// ATLCon.cpp : Example showing how to host controls and
//              create frame windows using ATL
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

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "ATLCon.h"
#include "ATLCon_i.c"
#include "ATLCon1.h"
#pragma comment(lib, "comctl32.lib")

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
	lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT

	CoInitialize(0);
	_Module.Init(ObjectMap, hInstance, &LIBID_ATLCONLib);

	// This is because the property browser control uses SysListView32
	::InitCommonControls();

	RECT rcPos = { CW_USEDEFAULT, 0, 0, 0 };
	HMENU hMenu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MENU1));
	HICON hIcon = LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_ICON1));
	CAtlCon frame;
	frame.GetWndClassInfo().m_wc.hIcon = hIcon;
	frame.Create(GetDesktopWindow(), rcPos, _T("ATL Container"), 0, 0, (UINT)hMenu);
	frame.ShowWindow(SW_SHOWNORMAL);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	_Module.Term();
	CoUninitialize();
	return 0;
}
