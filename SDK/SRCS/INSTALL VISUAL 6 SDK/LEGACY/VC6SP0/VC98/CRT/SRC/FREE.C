/***
*free.c - free an entry in the heap
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines the following functions:
*           free()     - free a memory block in the heap
*
*******************************************************************************/

#ifdef WINHEAP

#include <cruntime.h>
#include <malloc.h>
#include <winheap.h>
#include <windows.h>
#include <internal.h>
#include <mtdll.h>
#include <dbgint.h>

/***
*void free(pblock) - free a block in the heap
*
*Purpose:
*       Free a memory block in the heap.
*
*       Special ANSI Requirements:
*
*       (1) free(NULL) is benign.
*
*Entry:
*       void *pblock - pointer to a memory block in the heap
*
*Return:
*       <void>
*
*******************************************************************************/

void __cdecl _free_base (void * pBlock)
{
        PHEADER     pHeader;


        if (pBlock == NULL)
            return;

        _mlock(_HEAP_LOCK);

        if ((pHeader = __sbh_find_block(pBlock)) != NULL)
        {
            __sbh_free_block(pHeader, pBlock);
            _munlock(_HEAP_LOCK);
        }
        else
        {
            _munlock(_HEAP_LOCK);
            HeapFree(_crtheap, 0, pBlock);
        }
}


#else  /* WINHEAP */


#include <cruntime.h>
#include <heap.h>
#include <malloc.h>
#include <mtdll.h>
#include <stdlib.h>
#include <dbgint.h>

/***
*void free(pblock) - free a block in the heap
*
*Purpose:
*       Free a memory block in the heap.
*
*       Special Notes For Multi-thread: The non-multi-thread version is renamed
*       to _free_lk(). The multi-thread free() simply locks the heap, calls
*       _free_lk(), then unlocks the heap and returns.
*
*Entry:
*       void *pblock - pointer to a memory block in the heap
*
*Return:
*       <void>
*
*******************************************************************************/

#ifdef _MT

void __cdecl _free_base (
        void *pblock
        )
{
       /* lock the heap
        */
        _mlock(_HEAP_LOCK);

        /* free the block
         */
        _free_base_lk(pblock);

        /* unlock the heap
         */
        _munlock(_HEAP_LOCK);
}


/***
*void _free_lk(pblock) - non-locking form of free
*
*Purpose:
*       Same as free() except that no locking is performed
*
*Entry:
*       See free
*
*Return:
*
*******************************************************************************/

void __cdecl _free_base_lk (

#else  /* _MT */

void __cdecl _free_base (

#endif  /* _MT */

        REG1 void *pblock
        )
{
        REG2 _PBLKDESC pdesc;


        /*
         * If the pointer is NULL, just return [ANSI].
         */

        if (pblock == NULL)
            return;

        /*
         * Point to block header and get the pointer back to the heap desc.
         */

        pblock = (char *)pblock - _HDRSIZE;
        pdesc = *(_PBLKDESC*)pblock;

        /*
         * Validate the back pointer.
         */

        if (_ADDRESS(pdesc) != pblock)
            _heap_abort();

        /*
         * Pointer is ok.  Mark block free.
         */

        _SET_FREE(pdesc);

        /*
         * Check for special conditions under which the rover is reset.
         */
        if ( (_heap_resetsize != 0xffffffff) &&
             (_heap_desc.proverdesc->pblock > pdesc->pblock) &&
             (_BLKSIZE(pdesc) >= _heap_resetsize) )
        {
            _heap_desc.proverdesc = pdesc;
        }
#if !defined (_M_MPPC) && !defined (_M_M68K)
        else if ( _heap_desc.proverdesc == pdesc->pnextdesc )
        {
            _heap_desc.proverdesc = pdesc;
        }
#endif  /* !defined (_M_MPPC) && !defined (_M_M68K) */
}

#endif  /* WINHEAP */
