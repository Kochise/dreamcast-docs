/***
*new.cxx - defines C++ new routine
*
*       Copyright (c) 1990-1998, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Defines C++ new routine.
*
*******************************************************************************/


#include <cruntime.h>
#include <malloc.h>
#include <new.h>
#include <stdlib.h>
#ifdef WINHEAP
#include <winheap.h>
#else  /* WINHEAP */
#include <heap.h>
#endif  /* WINHEAP */

void * operator new( unsigned int cb )
{
    void *res = _nh_malloc( cb, 1 );

    return res;
}

