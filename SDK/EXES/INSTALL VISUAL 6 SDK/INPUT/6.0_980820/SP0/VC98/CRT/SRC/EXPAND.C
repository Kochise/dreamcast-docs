/***
*expand.c - Win32 expand heap routine
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*
*******************************************************************************/

#ifdef WINHEAP

#include <cruntime.h>
#include <malloc.h>
#include <winheap.h>
#include <windows.h>
#include <mtdll.h>
#include <dbgint.h>

/***
*void *_expand(void *pblck, size_t newsize) - expand/contract a block of memory
*       in the heap
*
*Purpose:
*       Resizes a block in the heap to newsize bytes. newsize may be either
*       greater (expansion) or less (contraction) than the original size of
*       the block. The block is NOT moved.
*
*       NOTES:
*
*       (1) In this implementation, if the block cannot be grown to the
*       desired size, the resulting block will NOT be grown to the max
*       possible size.  (That is, either it works or it doesn't.)
*
*       (2) Unlike other implementations, you can NOT pass a previously
*       freed block to this routine and expect it to work.
*
*Entry:
*       void *pblck - pointer to block in the heap previously allocated
*                 by a call to malloc(), realloc() or _expand().
*
*       size_t newsize  - requested size for the resized block
*
*Exit:
*       Success:  Pointer to the resized memory block (i.e., pblck)
*       Failure:  NULL
*
*Uses:
*
*Exceptions:
*       If pblck does not point to a valid allocation block in the heap,
*       _expand() will behave unpredictably and probably corrupt the heap.
*
*******************************************************************************/

void * __cdecl _expand_base (void * pBlock, size_t newsize)
{
    PHEADER     pHeader;
    void *      pvReturn;


    /* validate size */
    if ( newsize > _HEAP_MAXREQ )
        return NULL;

    _mlock(_HEAP_LOCK);

    //  if allocation block lies within the small-block heap,
    //  try to resize it there
    if ((pHeader = __sbh_find_block(pBlock)) != NULL)
    {
        pvReturn = NULL;
        if (newsize <= __sbh_threshold &&
                         __sbh_resize_block(pHeader, pBlock, newsize))
            pvReturn = pBlock;

        _munlock(_HEAP_LOCK);
        return pvReturn;
    }

    _munlock(_HEAP_LOCK);

    //  force nonzero size and round up to next paragraph
    if (newsize == 0)
        newsize = 1;
    newsize = (newsize + BYTES_PER_PARA - 1) & ~(BYTES_PER_PARA - 1);

    return (HeapReAlloc(_crtheap, HEAP_REALLOC_IN_PLACE_ONLY,
                                                    pBlock, newsize));
}


#endif  /* WINHEAP */
