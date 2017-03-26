/* KallistiOS ##version##

   arch/ps2/include/cache.h
   (c)2001 Dan Potter
   
   $Id: cache.h,v 1.3 2002/11/03 03:40:55 bardtx Exp $
*/

#ifndef __ARCH_CACHE_H
#define __ARCH_CACHE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

#if 0
/* Flush a range of i-cache, given a physical address range */
void icache_flush_range(uint32 start, uint32 count);

/* Invalidate a range of o-cache/d-cache, given a physical address range */
void dcache_inval_range(uint32 start, uint32 count);

/* Flush a range of o-cache/d-cache, given a physical address range */
void dcache_flush_range(uint32 start, uint32 count);
#endif

/* Sync, disable, invalidate, and re-enable all caches; use after rewriting
   some bit of code. */
void cache_flush_all();

__END_DECLS

#endif	/* __ARCH_CACHE_H */

