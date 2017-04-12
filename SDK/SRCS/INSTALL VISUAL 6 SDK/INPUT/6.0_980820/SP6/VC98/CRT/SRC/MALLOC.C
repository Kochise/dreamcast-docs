/***
*malloc.c - Get a block of memory from the heap
*
*       Copyright (c) 1989-1998, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines the malloc() function.
*
*******************************************************************************/

#include <cruntime.h>
#include <malloc.h>
#include <internal.h>
#include <mtdll.h>
#include <dbgint.h>

#ifdef WINHEAP
#include <windows.h>
#include <winheap.h>
#else  /* WINHEAP */
#include <heap.h>
#endif  /* WINHEAP */


extern int _newmode;    /* malloc new() handler mode */


/***
*void *malloc(size_t size) - Get a block of memory from the heap
*
*Purpose:
*       Allocate of block of memory of at least size bytes from the heap and
*       return a pointer to it.
*
*       Calls the new appropriate new handler (if installed).
*
*Entry:
*       size_t size - size of block requested
*
*Exit:
*       Success:  Pointer to memory block
*       Failure:  NULL (or some error value)
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

void * __cdecl _malloc_base (size_t size)

{
        void *res = _nh_malloc_base(size, _newmode);

        return res;
}


/***
*void *_nh_malloc_base(size_t size) - Get a block of memory from the heap
*
*Purpose:
*       Allocate of block of memory of at least size bytes from the heap and
*       return a pointer to it.
*
*       Calls the appropriate new handler (if installed).
*
*       There are two distinct new handler schemes supported. The 'new' ANSI
*       C++ scheme overrides the 'old' scheme when it is activated. A value of
*       _NOPTH for the 'new' handler indicates that it is inactivated and the
*       'old' handler is then called.
*
*Entry:
*       size_t size - size of block requested
*
*Exit:
*       Success:  Pointer to memory block
*       Failure:  NULL (or some error value)
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

void * __cdecl _nh_malloc_base (size_t size, int nhFlag)
{
        void * pvReturn;

        //  validate size
        if (size > _HEAP_MAXREQ)
            return NULL;

#ifndef WINHEAP
        /* round requested size */
        size = _ROUND2(size, _GRANULARITY);
#endif  /* WINHEAP */

        for (;;) {

            //  allocate memory block
            if (size <= _HEAP_MAXREQ)
                pvReturn = _heap_alloc_base(size);
            else
                pvReturn = NULL;

            //  if successful allocation, return pointer to memory
            //  if new handling turned off altogether, return NULL

            if (pvReturn || nhFlag == 0)
                return pvReturn;

            //  call installed new handler
            if (!_callnewh(size))
                return NULL;

            //  new handler was successful -- try to allocate again
        }
}

/***
*void *_heap_alloc_base(size_t size) - does actual allocation
*
*Purpose:
*       Same as malloc() except the new handler is not called.
*
*Entry:
*       See malloc
*
*Exit:
*       See malloc
*
*Exceptions:
*
*******************************************************************************/

void * __cdecl _heap_alloc_base (size_t size)

{
#ifdef WINHEAP
        void * pvReturn;
#else  /* WINHEAP */
        _PBLKDESC pdesc;
        _PBLKDESC pdesc2;
#endif  /* WINHEAP */


#ifdef WINHEAP

        if ( __active_heap == __V6_HEAP )
        {
            if ( size <= __sbh_threshold )
            {
#ifdef _MT
                _mlock( _HEAP_LOCK );
                __try {
#endif  /* _MT */
                pvReturn = __sbh_alloc_block(size);
#ifdef _MT
                }
                __finally {
                    _munlock( _HEAP_LOCK );
                }
#endif  /* _MT */
                if (pvReturn)
                    return pvReturn;
            }
        }
        else if ( __active_heap == __V5_HEAP )
        {
            /* round up to the nearest paragraph */
            if ( size )
                size = (size + _OLD_PARASIZE - 1) & ~(_OLD_PARASIZE - 1);
            else
                size = _OLD_PARASIZE;

            if ( size  <= __old_sbh_threshold ) {
#ifdef _MT
                _mlock(_HEAP_LOCK);
                __try {
#endif  /* _MT */
                pvReturn = __old_sbh_alloc_block(size >> _OLD_PARASHIFT);
#ifdef _MT
                }
                __finally {
                    _munlock(_HEAP_LOCK);
                }
#endif  /* _MT */
                if ( pvReturn != NULL )
                    return pvReturn;
            }

            return HeapAlloc( _crtheap, 0, size );
        }

        if (size == 0)
            size = 1;
        size = (size + BYTES_PER_PARA - 1) & ~(BYTES_PER_PARA - 1);
        return HeapAlloc(_crtheap, 0, size);
}

#else  /* WINHEAP */

        /* try to find a big enough free block
         */
        if ( (pdesc = _heap_search(size)) == NULL )
        {
            if ( _heap_grow(size) != -1 )
            {
                /* try finding a big enough free block again. the
                 * success of the call to _heap_grow should guarantee
                 * it, but...
                 */
                if ( (pdesc = _heap_search(size)) == NULL )
                {
                    /* something unexpected, and very bad, has
                     * happened. abort!
                     */
                    _heap_abort();
                }
            }
            else
                return NULL;
        }

        /* carve the block into two pieces (if necessary). the first piece
         * shall be of the exact requested size, marked inuse and returned to
         * the caller. the leftover piece is to be marked free.
         */
        if ( _BLKSIZE(pdesc) != size ) {
            /* split up the block and free the leftover piece back to
             * the heap
             */
            if ( (pdesc2 = _heap_split_block(pdesc, size)) != NULL )
                _SET_FREE(pdesc2);
        }

        /* mark pdesc inuse
         */
        _SET_INUSE(pdesc);

        /* check proverdesc and reset, if necessary
         */

        _heap_desc.proverdesc = pdesc->pnextdesc;

        return( (void *)((char *)_ADDRESS(pdesc) + _HDRSIZE) );
}


/***
*_PBLKDESC _heap_split_block(pdesc, newsize) - split a heap allocation block
*       into two allocation blocks
*
*Purpose:
*       Split the allocation block described by pdesc into two blocks, the
*       first one being of newsize bytes.
*
*       Notes: It is caller's responsibilty to set the status (i.e., free
*       or inuse) of the two new blocks, and to check and reset proverdesc
*       if necessary. See Exceptions (below) for additional requirements.
*
*Entry:
*       _PBLKDESC pdesc - pointer to the allocation block descriptor
*       size_t newsize  - size for the first of the two sub-blocks (i.e.,
*                 (i.e., newsize == _BLKSIZE(pdesc), on exit)
*
*Exit:
*       If successful, return a pointer to the descriptor for the leftover
*       block.
*       Otherwise, return NULL.
*
*Exceptions:
*       It is assumed pdesc points to a valid allocation block descriptor and
*       newsize is a valid heap block size as is (i.e., WITHOUT rounding). If
*       either of these of assumption is violated, _heap_split_block() will
*       likely corrupt the heap. Note also that _heap_split_block will simply
*       return to the caller if newsize >= _BLKSIZE(pdesc), on entry.
*
*******************************************************************************/

_PBLKDESC __cdecl _heap_split_block (
        REG1 _PBLKDESC pdesc,
        size_t newsize
        )
{
        REG2 _PBLKDESC pdesc2;

        _ASSERTE(("_heap_split_block: bad pdesc arg", _CHECK_PDESC(pdesc)));
        _ASSERTE(("_heap_split_block: bad newsize arg", _ROUND2(newsize,_GRANULARITY) == newsize));

        /* carve the block into two pieces (if possible). the first piece
         * is to be exactly newsize bytes.
         */
        if ( (_BLKSIZE(pdesc) > newsize) && ((pdesc2 = __getempty())
               != NULL) )
        {
            /* set it up to manage the second piece and link it in to
             * the list
             */
            pdesc2->pblock = (void *)((char *)_ADDRESS(pdesc) + newsize +
                     _HDRSIZE);
            *(void **)(pdesc2->pblock) = pdesc2;
            pdesc2->pnextdesc = pdesc->pnextdesc;
            pdesc->pnextdesc = pdesc2;

            return pdesc2;
        }
        return NULL;
}

#endif  /* WINHEAP */

