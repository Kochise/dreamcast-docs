/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    Memory.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _MEMORY_H_
#define _MEMORY_H_

LPVOID
AllocProvMem(
    DWORD cb
);

BOOL
FreeProvMem(
   LPVOID pMem
);

LPVOID
ReallocProvMem(
   LPVOID pOldMem,
   DWORD cbOld,
   DWORD cbNew
);

LPWSTR
AllocProvStr(
    LPWSTR pStr
);

BOOL
FreeProvStr(
   LPWSTR pStr
);


BOOL
ReallocProvStr(
   LPWSTR *ppStr,
   LPWSTR pStr
);

//+---------------------------------------------------------------------------
//
//  Function:   ADsFreeString
//
//  Synopsis:   Frees a BSTR.
//
//
//----------------------------------------------------------------------------

inline void
ProvFreeString(BSTR bstr)
{
    SysFreeString(bstr);
}

STDAPI ProvAllocString(const OLECHAR * pch, BSTR * pBSTR);

#endif

