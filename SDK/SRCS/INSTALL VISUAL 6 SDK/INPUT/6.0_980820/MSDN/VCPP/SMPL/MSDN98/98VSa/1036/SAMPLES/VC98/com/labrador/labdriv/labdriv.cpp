
// labdriv.cpp : driver for the Labrador sample
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
    _ASSERTE(nBuf < sizeof(szBuffer));

    _tprintf(szBuffer);
    OutputDebugString(szBuffer);
    va_end(args);
}

// helper function to do the work
void _cdecl CallLabrador()
{
    USHORT szTmp[32];

    Trace(_T("\nSTARTING\n=============================\n"));
    Trace(_T("Calling CoCreateInstance()...\n"));
    IMammalPtr pMammal(__uuidof(Labrador));

    Trace(_T("Calling through IMammal methods...\n"));
    pMammal->GetSpeciesName(szTmp);
    Trace(_T("Species name is <%ls>\n"), szTmp);
    LONG bIsAlive;
    pMammal->IsAlive(&bIsAlive);
    if (bIsAlive)
        Trace(_T("And it's alive!\n"));
    else
        Trace(_T("And it's dead!\n"));

    IDogPtr pDog = pMammal;

    Trace(_T("Calling through IDog methods...\n"));
    LONG bIsBarking;
    pDog->GetPetName(szTmp);
    Trace(_T("Dog's name is <%ls>\n"), szTmp);

    pDog->IsBarking(&bIsBarking);
    if (bIsBarking)
        printf("BARK! BARK! BARK! BARK!\n");

    pDog->SetPetName(L"KIVA");

    pDog->GetPetName(szTmp);
    printf("Dog's New name is <%ls>\n", szTmp);

    Trace(_T("Releasing Objects\n"));
    pDog = 0;
    pMammal = 0;
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
