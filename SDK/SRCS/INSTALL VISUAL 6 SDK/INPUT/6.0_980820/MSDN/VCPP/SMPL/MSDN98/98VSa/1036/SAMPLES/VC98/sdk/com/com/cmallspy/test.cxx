//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1992 - 1997 Microsoft Corporation.
//
//  File:       test.cxx
//
//  Contents:   test application for CMALSPY sample library
//
//----------------------------------------------------------------------------

#include <windows.h>
#include <ole2.h>
#include "cmallspy.hxx"

extern "C" void printf(CHAR*, ...);

const UINT NALLOCATIONS = 573;


int __cdecl main(int argc, char **argv)
{
    HRESULT     hr;
    LPMALLOCSPY pMallocSpy = new CMallocSpy();

    // Initialize
    CoInitialize(NULL);
    hr = CoRegisterMallocSpy(pMallocSpy);
    if (hr != S_OK)
    {
        printf("CoRegisterMallocSpy failed with %x\n", hr);
        CoUninitialize();
        return 0;
    }
    printf("CoRegisterMallocSpy succeeded.\n");

    // Allocate enoungh to force an expansion
    LPMALLOC pMalloc;
    void    *allocs[NALLOCATIONS];
    ULONG j;

    if ((hr = CoGetMalloc(MEMCTX_TASK, &pMalloc)) != S_OK)
    {
        printf("CoGetMalloc failed with %x\n", hr);
        CoUninitialize();
        return 0;
    }
    printf("CoGetMalloc succeeded.\n");
    printf("Allocating %u memory blocks.\n", NALLOCATIONS);
    for (j = 0; j < NALLOCATIONS; j++)
    {
        allocs[j] = pMalloc->Alloc(173);
    }

    // Now release everything
    printf("Releasing %u memory blocks.\n", NALLOCATIONS);
    for (j = 0; j < NALLOCATIONS; j++)
    {
        pMalloc->Free(allocs[j]);
        allocs[j] = NULL;
    }

    printf("Test complete.\n");
    // All done
    CoRevokeMallocSpy();
    CoUninitialize();
    return 0;
}


