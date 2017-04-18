/***
*msize.c - calculate the size of a memory block in the heap
*
*       Copyright (c) 1989-1998, Microsoft Corporation. All rights reserved.
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
        PHEADER     pHeader;


        if ( __active_heap == __V6_HEAP )
        {
#ifdef _MT
            _mlock( _HEAP_LOCK );
            __try {
#endif  /* _MT */
            if ((pHeader = __sbh_find_block(pblock)) != NULL)
                retval = (size_t)
                         (((PENTRY)((char *)pblock - sizeof(int)))->sizeFront - 0x9);
#ifdef _MT
            }
            __finally {
                _munlock( _HEAP_LOCK );
            }
#endif  /* _MT */
            if ( pHeader == NULL )
                retval = (size_t)HeapSize(_crtheap, 0, pblock);
        }
        else if ( __active_heap == __V5_HEAP )
        {
            __old_sbh_region_t *preg;
            __old_sbh_page_t *  ppage;
            __old_page_map_t *  pmap;
#ifdef _MT
            _mlock(_HEAP_LOCK);
            __try {
#endif  /* _MT */
            if ( (pmap = __old_sbh_find_block(pblock, &preg, &ppage)) != NULL )
                retval = ((size_t)(*pmap)) << _OLD_PARASHIFT;
#ifdef _MT
            }
            __finally {
                _munlock( _HEAP_LOCK );
            }
#endif  /* _MT */
            if ( pmap == NULL )
                retval = (size_t) HeapSize( _crtheap, 0, pblock );
        }
        else    /* __active_heap == __SYSTEM_HEAP */
            retval = (size_t)HeapSize(_crtheap, 0, pblock);

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
