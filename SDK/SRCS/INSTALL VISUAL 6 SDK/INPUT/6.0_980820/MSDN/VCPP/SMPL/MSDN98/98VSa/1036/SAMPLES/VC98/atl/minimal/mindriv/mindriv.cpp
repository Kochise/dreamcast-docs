
// mindriv.cpp : driver for the Minimal sample
//
// This is a part of the ActiveX Template Library.
// Copyright (C) 1996 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// ActiveX Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// ActiveX Template Library product.

#include "premindr.h"
#include <initguid.h>
#include "..\\minimal.h"


///////////////////////////////////////////////////////////////

// helper to do print traces
void _cdecl Trace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	nBuf = _vstprintf(szBuffer, lpszFormat, args);
	_ASSERT(nBuf < sizeof(szBuffer));

	_tprintf(szBuffer);
	OutputDebugString(szBuffer);
	va_end(args);
}

// helper function to do the work
void _cdecl CallMinimal()
{
	Trace(_T("\nSTARTING\n=============================\n"));
	Trace(_T("Calling CoCreateInstance()...\n"));
	IUnknown* pUnk = NULL;
	HRESULT hRes = CoCreateInstance(CLSID_CMinObj, NULL, CLSCTX_INPROC_SERVER,
		IID_IUnknown, (void**)&pUnk);
	if (FAILED(hRes))
	{
		Trace(_T("Failed to create MinObj\n"));
		return;
	}
	Trace(_T("Object created\n"));

	IMinObj* pMin = NULL;
	hRes = pUnk->QueryInterface(IID_IMinObj, (LPVOID*)&pMin);
	pUnk->Release();
	if (FAILED(hRes))
	{
		Trace(_T("QueryInterface() for IMinObj failed\n"));
		return;
	}

	Trace(_T("Calling IMinObj::Hello() method...\n"));
	hRes = pMin->Hello();
	if (SUCCEEDED(hRes))
		Trace(_T("Call succeeded\n"));
	else
		Trace(_T("Call failed\n"));
	Trace(_T("Releasing Object\n"));
	pMin->Release();
	Trace(_T("\nDONE!!!\n=============================\n"));
}

int main( int argc, char *argv[ ])
{

	if (FAILED(CoInitialize(NULL)))
		return -1;

	CallMinimal();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	CoUninitialize();
	return 0;
}
