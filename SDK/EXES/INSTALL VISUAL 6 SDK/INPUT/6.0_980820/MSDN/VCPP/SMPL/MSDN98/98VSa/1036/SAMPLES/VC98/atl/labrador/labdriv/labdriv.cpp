// labdriv.cpp : driver for the Labrador sample
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

#include "prelabdr.h"

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
void _cdecl CallLabrador()
{
	WCHAR szTmp[32];

	Trace(_T("\nSTARTING\n=============================\n"));
	Trace(_T("Calling CoCreateInstance()...\n"));
	IUnknown* pUnk = NULL;
	HRESULT hRes = CoCreateInstance(CLSID_Labrador, NULL, CLSCTX_LOCAL_SERVER,
		IID_IUnknown, (void**)&pUnk);
	if (FAILED(hRes))
	{
		Trace(_T("Failed to create Labrador\n"));
		return;
	}
	Trace(_T("Object created\n"));

	IMammal* pMammal = NULL;
	hRes = pUnk->QueryInterface(IID_IMammal, (LPVOID*)&pMammal);
	pUnk->Release();
	if (FAILED(hRes))
	{
		Trace(_T("QueryInterface() for IMammal failed\n"));
		return;
	}

	Trace(_T("Calling through IMammal methods...\n"));
	pMammal->GetSpeciesName(szTmp);
	Trace(_T("Species name is <%ls>\n"), szTmp);
	BOOL bIsAlive;
	pMammal->IsAlive(&bIsAlive);
	if (bIsAlive)
		Trace(_T("And it's alive!\n"));
	else
		Trace(_T("And it's dead!\n"));

	IDog* pDog = NULL;
	hRes = pMammal->QueryInterface(IID_IDog, (void**)&pDog);
	pMammal->Release();
	if (FAILED(hRes))
	{
		Trace(_T("QueryInterface() for IDog failed\n"));
		return;
	}

	Trace(_T("Calling through IDog methods...\n"));
	BOOL bIsBarking;
	pDog->GetPetName(szTmp);
	Trace(_T("Dog's name is <%ls>\n"), szTmp);

	pDog->IsBarking(&bIsBarking);
	if (bIsBarking)
		printf("BARK! BARK! BARK! BARK!\n");

	pDog->SetPetName(L"KIVA");

	pDog->GetPetName(szTmp);
	printf("Dog's New name is <%ls>\n", szTmp);

	Trace(_T("Releasing Object\n"));
	pDog->Release();
	Trace(_T("\nDONE!!!\n=============================\n"));
}

int main( int argc, char *argv[ ])
{

	if (FAILED(CoInitialize(NULL)))
		return -1;

	CallLabrador();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	CoUninitialize();
	return 0;
}
