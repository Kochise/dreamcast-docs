/***
*msize.c - calculate the size of a memory block in the heap
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines the following function:
*           _msize()    - calculate the size of a block in the heap
*
*******************************************************************************/


#ifdef WINHEAP


#include <cruntime.h>
#include <malloc.h>
#include <mtdll.h>
#include <winheap.h>
#include <windows.h>
#include <dbgint.h>

/***
*size_t _msize(pblock) - calculate the size of specified block in the heap
*
*Purpose:
*       Calculates the size of memory block (in the heap) pointed to by
*       pblock.
*
*Entry:
*       void *pblock - pointer to a memory block in the heap
*
*Return:
*       size of the block
*
*******************************************************************************/

size_t __cdecl _msize_base (void * pblock)
{
    size_t      retval;


    _mlock(_HEAP_LOCK);

    if (__sbh_find_block(pblock) != NULL)
    {
        retval = (size_t)
                 (((PENTRY)((char *)pblock - sizeof(int)))->sizeFront - 0x9);
        _munlock(_HEAP_LOCK);
    }
    else
    {
        _munlock(_HEAP_LOCK);
        retval = (size_t)HeapSize(_crtheap, 0, pblock);
    }

    return retval;
}

#else  /* WINHEAP */


#include <cruntime.h>
#include <heap.h>
#include <malloc.h>
#include <mtdll.h>
#include <stdlib.h>
#include <dbgint.h>

/***
*size_t _msize(pblock) - calculate the size of specified block in the heap
*
*Purpose:
*       Calculates the size of memory block (in the heap) pointed to by
*       pblock.
*
*Entry:
*       void *pblock - pointer to a memory block in the heap
*
*Return:
*       size of the block
*
*******************************************************************************/

#ifdef _MT

size_t __cdecl _msize_base (
        void *pblock
        )
{
        size_t  retval;

        /* lock the heap
         */
        _mlock(_HEAP_LOCK);

        retval = _msize_lk(pblock);

        /* release the heap lock
         */
        _munlock(_HEAP_LOCK);

        return retval;
}

size_t __cdecl _msize_lk (

#else  /* _MT */

size_t __cdecl _msize_base (

#endif  /* _MT */

        void *pblock
        )
{


        return( (size_t) ((char *)_ADDRESS(_BACKPTR(pblock)->pnextdesc) -
        (char *)pblock) );
}


#endif  /* WINHEAP */
