/* KallistiOS ##version##

   include/kos/mm.h
   Copyright (C)2000,2001,2003 Dan Potter

   $Id: mm.h,v 1.1 2003/06/19 04:30:23 bardtx Exp $

*/

#ifndef __KOS_MM_H
#define __KOS_MM_H

#include <arch/arch.h>
#include <arch/types.h>
#include <kos/process.h>

/* Convert a physical address to a physical page index */
#define phys_to_page(a) ( (((ptr_t)(a)) - page_phys_base) >> PAGESIZE_BITS )

/* Convert a physical page index to a physical address */
#define page_to_phys(a) ( ((a) * PAGESIZE) + page_phys_base )

/* MM-wide initialization */
int mm_init();

/* Allocate the first N consecutive pages as owned by the given process,
   and return a physical pointer to the pages. If reqat is non-zero,
   we will attempt to allocate the pages starting at the given
   location (with no guarantees). */
ptr_t mm_palloc(ptr_t reqat, size_t n, kprocess_t * proc);

/* Free N blocks starting at the given physical address */
void mm_pfree(ptr_t phys, size_t n);

/* Chown N blocks starting at the given physical address to the
   given process id */
void mm_pchown(ptr_t phys, size_t n, kprocess_t * proc);

/* Free all pages belonging to a particular process; the number of freed
   pages will be returned. */
int mm_pfreeall(kprocess_t * p);

#endif	/* __KOS_MM_H */



