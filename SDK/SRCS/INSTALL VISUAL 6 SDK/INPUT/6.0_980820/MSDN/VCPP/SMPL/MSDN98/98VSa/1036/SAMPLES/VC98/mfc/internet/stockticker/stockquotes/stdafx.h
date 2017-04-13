// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(AFX_STDAFX_H__039AB255_8602_11D0_9426_00A0C903487E__INCLUDED_)
#define AFX_STDAFX_H__039AB255_8602_11D0_9426_00A0C903487E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <vector>
#include <iostream>
#include <algorithm>

#include <afxwin.h>
#include <afxdisp.h>
#include <afxinet.h>

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
// ATL can increment MFC's lock count the first time and decrement MFC's lock
// count when its lock count reaches zero.
class CAtlGlobalModule : public CComModule
{
public:
	LONG Lock()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (GetLockCount()==0)
			AfxOleLockApp();
		return CComModule::Lock();
	}
	LONG Unlock()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		LONG l = CComModule::Unlock();
		if (GetLockCount() == 0)
			AfxOleUnlockApp();
		return l;
	}
};

extern CAtlGlobalModule _Module;
#include <atlcom.h>

extern bool g_bUpdating;        // currently updating data from net?

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__039AB255_8602_11D0_9426_00A0C903487E__INCLUDED)
