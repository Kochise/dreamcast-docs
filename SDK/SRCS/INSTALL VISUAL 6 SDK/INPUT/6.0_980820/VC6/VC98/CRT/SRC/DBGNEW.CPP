/***
*dbgnew.cpp - defines C++ new() routines, debug version
*
*       Copyright (c) 1995-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Defines C++ new() routines.
*
*******************************************************************************/

#ifdef _DEBUG

#include <cruntime.h>
#include <malloc.h>
#include <mtdll.h>
#include <dbgint.h>

/***
*void * operator new() - Get a block of memory from the debug heap
*
*Purpose:
*       Allocate of block of memory of at least size bytes from the heap and
*       return a pointer to it.
*
*       Allocates any type of supported memory block.
*
*Entry:
*       unsigned int    cb          - count of bytes requested
*       int             nBlockUse   - block type
*       char *          szFileName  - file name
*       int             nLine       - line number
*
*Exit:
*       Success:  Pointer to memory block
*       Failure:  NULL (or some error value)
*
*Exceptions:
*
*******************************************************************************/
void * operator new(
        unsigned int cb,
        int nBlockUse,
        const char * szFileName,
        int nLine
        )
{
        return _nh_malloc_dbg( cb, 1, nBlockUse, szFileName, nLine );
}

#endif  /* _DEBUG */
