// prebeep.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently
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

#define STRICT

#include <atlbase.h>

#ifdef _WINDLL

typedef CComModule CMyModule;

#else

class CMyModule : public CComModule
{
public:
	LONG Unlock()
	{
		LONG l = CComModule::Unlock();
		if (l == 0)
			PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
		return l;
	}
	DWORD dwThreadID;
};

#endif

extern CMyModule _Module;

#include <atlcom.h>
