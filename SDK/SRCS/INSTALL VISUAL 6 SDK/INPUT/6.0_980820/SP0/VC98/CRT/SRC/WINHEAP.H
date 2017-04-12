/***
*winheap.h - Private include file for winheap directory.
*
*       Copyright (c) 1988-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Contains information needed by the C library heap code.
*
*       [Internal]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_WINHEAP
#define _INC_WINHEAP

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <windows.h>

#define BYTES_PER_PARA      16
#define DWORDS_PER_PARA     4

#define PARAS_PER_PAGE      256     //  tunable value
#define PAGES_PER_GROUP     8       //  tunable value
#define GROUPS_PER_REGION   32      //  tunable value (max 32)

#define BYTES_PER_PAGE      (BYTES_PER_PARA * PARAS_PER_PAGE)
#define BYTES_PER_GROUP     (BYTES_PER_PAGE * PAGES_PER_GROUP)
#define BYTES_PER_REGION    (BYTES_PER_GROUP * GROUPS_PER_REGION)

#define ENTRY_OFFSET        0x0000000cL     //  offset of entry in para
#define OVERHEAD_PER_PAGE   0x00000010L     //  sixteen bytes of overhead
#define MAX_FREE_ENTRY_SIZE (BYTES_PER_PAGE - OVERHEAD_PER_PAGE)
#define BITV_COMMIT_INIT    (((1 << GROUPS_PER_REGION) - 1) << \
                                            (32 - GROUPS_PER_REGION))
#define MAX_ALLOC_DATA_SIZE     0x3f8
#define MAX_ALLOC_ENTRY_SIZE    (MAX_ALLOC_DATA_SIZE + 0x8)

typedef unsigned int    BITVEC;

typedef struct tagListHead
{
    struct tagEntry *   pEntryNext;
    struct tagEntry *   pEntryPrev;
}
LISTHEAD, *PLISTHEAD;

typedef struct tagEntry
{
    int                 sizeFront;
    struct tagEntry *   pEntryNext;
    struct tagEntry *   pEntryPrev;
}
ENTRY, *PENTRY;

typedef struct tagEntryEnd
{
    int                 sizeBack;
}
ENTRYEND, *PENTRYEND;

typedef struct tagGroup
{
    int                 cntEntries;
    struct tagListHead  listHead[64];
}
GROUP, *PGROUP;

typedef struct tagRegion
{
    int                 indGroupUse;
    char                cntRegionSize[64];
    BITVEC              bitvGroupHi[GROUPS_PER_REGION];
    BITVEC              bitvGroupLo[GROUPS_PER_REGION];
    struct tagGroup     grpHeadList[GROUPS_PER_REGION];
}
REGION, *PREGION;

typedef struct tagHeader
{
    BITVEC              bitvEntryHi;
    BITVEC              bitvEntryLo;
    BITVEC              bitvCommit;
    void *              pHeapData;
    struct tagRegion *  pRegion;
}
HEADER, *PHEADER;

extern  HANDLE _crtheap;

/*
 * Global variable declarations for the small-block heap.
 */
extern size_t       __sbh_threshold;

void * __cdecl _nh_malloc(size_t, int);
void * __cdecl _heap_alloc(size_t);

extern PHEADER      __sbh_pHeaderList;        //  pointer to list start
extern PHEADER      __sbh_pHeaderScan;        //  pointer to list rover
extern int          __sbh_sizeHeaderList;     //  allocated size of list
extern int          __sbh_cntHeaderList;      //  count of entries defined

extern PHEADER      __sbh_pHeaderDefer;
extern int          __sbh_indGroupDefer;

extern size_t  __cdecl _get_sb_threshold(void);
extern int     __cdecl _set_sb_threshold(size_t);

extern int     __cdecl _heap_init(int);
extern void    __cdecl _heap_term(void);

extern void *  __cdecl _malloc_base(size_t);
extern void *  __cdecl _nh_malloc_base(size_t, int);
extern void *  __cdecl _heap_alloc_base(size_t);

extern void    __cdecl _free_base(void *);
extern void *  __cdecl _realloc_base(void *, size_t);

extern void *  __cdecl _expand_base(void *, size_t);
extern void *  __cdecl _calloc_base(size_t, size_t);

extern size_t  __cdecl _msize_base(void *);

extern int     __cdecl __sbh_heap_init(void);

extern void *  __cdecl __sbh_alloc_block(int);
extern PHEADER __cdecl __sbh_alloc_new_region(void);
extern int     __cdecl __sbh_alloc_new_group(PHEADER);

extern PHEADER __cdecl __sbh_find_block(void *);

#ifdef _DEBUG
extern int     __cdecl __sbh_verify_block(PHEADER, void *);
#endif  /* _DEBUG */

extern void    __cdecl __sbh_free_block(PHEADER, void *);
extern int     __cdecl __sbh_resize_block(PHEADER, void *, int);

extern void    __cdecl __sbh_heapmin(void);

extern int     __cdecl __sbh_heap_check(void);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_WINHEAP */
