/***
*dbghook.c - Debug CRT Hook Functions
*
*       Copyright (c) 1988-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Allow users to override default alloc hook at link time.
*
*******************************************************************************/

#ifdef _DEBUG

#include <internal.h>
#include <limits.h>
#include <mtdll.h>
#include <malloc.h>
#include <stdlib.h>
#include <dbgint.h>


_CRT_ALLOC_HOOK _pfnAllocHook = _CrtDefaultAllocHook;


/***
*int _CrtDefaultAllocHook() - allow allocation
*
*Purpose:
*       allow allocation
*
*Entry:
*       all parameters ignored
*
*Exit:
*       returns TRUE
*
*Exceptions:
*
*******************************************************************************/
int __cdecl _CrtDefaultAllocHook(
        int nAllocType,
        void * pvData,
        size_t nSize,
        int nBlockUse,
        long lRequest,
        const unsigned char * szFileName,
        int nLine
        )
{
        return 1; /* allow all allocs/reallocs/frees */
}

#endif  /* _DEBUG */
