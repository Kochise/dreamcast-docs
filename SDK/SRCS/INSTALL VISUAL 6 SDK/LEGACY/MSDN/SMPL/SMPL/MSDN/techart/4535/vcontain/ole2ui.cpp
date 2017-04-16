//OLE Control Container Verification Application, Version 1.00
//
//Copyright (c) 1995-6 Microsoft Corp, All Rights Reserved
//
//	This is a part of the Microsoft Source Code Samples.
//	This source code is only intended as a supplement to
//	the Microsoft Development Tools and/or WinHelp implementation.
//	See these sources for detailed information regarding the
//	Microsoft sample programs.
//
//Revisions:
//	November 30, 1995	mtm		First Implementation
//
//Purpose:
//	Generic OLE functions.

#include "stdafx.h"

#ifdef _WIN32
#ifndef _fmemcpy
#define _fmemcpy memcpy
#endif
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW


STDAPI_(LPVOID) OleStdMalloc(ULONG ulSize)
{
	LPMALLOC pMalloc = NULL;
	void FAR* p = NULL;
	
	if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pMalloc)))
	{
		ASSERT(pMalloc != NULL);

		p = pMalloc->Alloc(ulSize);
		pMalloc->Release();
	}
	
	return p;
}


STDAPI_(void) OleStdFree(LPVOID p)
{
	if (p == NULL)		// Free(NULL) is a no-op
	{
		return;
	}
		
	LPMALLOC pMalloc = NULL;
	
	if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pMalloc)))
	{
		ASSERT(pMalloc != NULL);

		pMalloc->Free(p);
		pMalloc->Release();
	}
}


STDAPI_(LPVOID) OleStdRealloc(LPVOID p, ULONG ulSize)
{
	LPMALLOC pMalloc = NULL;
	void FAR* pNew = NULL;
	
	if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pMalloc)))
	{
		ASSERT(pMalloc != NULL);

		pNew = pMalloc->Realloc(p, ulSize);
		pMalloc->Release();
	}
	
	return pNew;
}


