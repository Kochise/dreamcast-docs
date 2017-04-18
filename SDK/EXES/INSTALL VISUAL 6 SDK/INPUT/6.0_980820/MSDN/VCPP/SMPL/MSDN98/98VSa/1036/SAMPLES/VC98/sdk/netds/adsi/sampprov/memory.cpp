/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Memory.cpp

Abstract:

    This module provides all the memory management functions for all Sample
    provider components


Author:

Environment:

    User mode

Revision History :

--*/
#include "adssmp.h"

#define WORD_ALIGN_DOWN(addr) ((LPBYTE)((DWORD)addr &= ~1))
#define DWORD_ALIGN_UP(size) ((size+3)&~3)


LPVOID
AllocProvMem(
    DWORD cb
)
{
    LPDWORD  pMem;
    DWORD    cbNew ;

#if DBG
    cb = DWORD_ALIGN_UP(cb);

    cbNew = cb + (sizeof(DWORD) + sizeof(LONGLONG));
#else
    cbNew = cb ;
#endif

    pMem=(LPDWORD)LocalAlloc(LPTR, cbNew);


#if DBG

    if (!pMem) {
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return 0;
    }

    *pMem=cb;
    *(LPDWORD)((LPBYTE)pMem+cbNew-sizeof(DWORD))=0xdeadfeed;
    pMem = (LPDWORD) (((LPBYTE)pMem)+sizeof(LONGLONG));
#endif

    return (LPVOID)(pMem);
}

BOOL
FreeProvMem(
   LPVOID pMem
)
{
    LPBYTE   pNewMem;

    pNewMem = (LPBYTE)pMem;

#if DBG
    DWORD    cb;
    DWORD    cbNew = 0;

    pNewMem -= sizeof(LONGLONG) ;

    cb = *((LPDWORD)pNewMem);
    cbNew = cb + sizeof(DWORD) + sizeof(LONGLONG);

    if (*(LPDWORD)(pNewMem + cbNew - sizeof(DWORD)) != 0xdeadbeef) {
        ADsAssert(!"Freeing memory not allocated by AllocProvMem") ;
        return FALSE;
    }

    // fill freed memory with known pattern
    memset(pMem, 0x5C, cb);

#endif


    return(LocalFree((LPVOID)pNewMem) == NULL);
}

LPVOID
ReallocProvMem(
   LPVOID pOldMem,
   DWORD cbOld,
   DWORD cbNew
)
{
    LPVOID pNewMem;

    pNewMem=AllocProvMem(cbNew);

    if (pOldMem && pNewMem) {
        memcpy(pNewMem, pOldMem, min(cbNew, cbOld));
        FreeProvMem(pOldMem);
    }

    return pNewMem;
}


LPWSTR
AllocProvStr(
    LPWSTR pStr
)
{
   LPWSTR pMem;

   if (!pStr)
      return 0;

   if (pMem = (LPWSTR)AllocProvMem( wcslen(pStr)*sizeof(WCHAR) + sizeof(WCHAR) ))
      wcscpy(pMem, pStr);

   return pMem;
}

BOOL
FreeProvStr(
   LPWSTR pStr
)
{
   return pStr ? FreeProvMem(pStr)
               : FALSE;
}

BOOL
ReallocProvStr(
   LPWSTR *ppStr,
   LPWSTR pStr
)
{
   FreeProvStr(*ppStr);
   *ppStr=AllocProvStr(pStr);

   return TRUE;
}

STDAPI
ProvAllocString(const OLECHAR * pch, BSTR * pBSTR)
{
    HRESULT hr = S_OK;

    ADsAssert(pBSTR);
    if (!pch)
    {
        *pBSTR = NULL;
        return S_OK;
    }

    *pBSTR = SysAllocString(pch);
    hr = (*pBSTR) ? S_OK : E_OUTOFMEMORY;
    RRETURN(hr);
}


