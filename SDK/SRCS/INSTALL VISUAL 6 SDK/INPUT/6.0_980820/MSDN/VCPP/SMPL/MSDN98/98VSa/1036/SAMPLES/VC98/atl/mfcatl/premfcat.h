// premfcat.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
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

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>

// We can implement the MFC/ATL lock count interaction in two different ways
// (you may comment/uncomment the one you want to try)

// ATL can blindly delegate all the ATL Lock()/Unlock() calls to MFC
/*
class CAtlGlobalModule : public CComModule
{
public:
	LONG Lock()
	{
		AfxOleLockApp();
		return 0;
	}
	LONG Unlock()
	{
		AfxOleUnlockApp();
		return 0;
	}
};
*/
// ATL can increment MFC's lock count the first time and decrement MFC's lock
// count when its lock count reaches zero.
class CAtlGlobalModule : public CComModule
{
public:
	LONG Lock()
	{
		if (GetLockCount()==0)
			AfxOleLockApp();
		return CComModule::Lock();
	}
	LONG Unlock()
	{
		LONG l = CComModule::Unlock();
		if (GetLockCount() == 0)
			AfxOleUnlockApp();
		return l;
	}
};

extern CAtlGlobalModule _Module;
#include <atlcom.h>
