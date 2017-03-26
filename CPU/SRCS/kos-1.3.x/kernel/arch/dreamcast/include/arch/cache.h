/* KallistiOS ##version##

   arch/dreamcast/include/cache.h
   (c)2001 Dan Potter
   
   $Id: cache.h,v 1.2 2002/01/05 07:33:50 bardtx Exp $
*/

#ifndef __ARCH_CACHE_H
#define __ARCH_CACHE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Flush a range of i-cache, given a physical address range */
void icache_flush_range(uint32 start, uint32 count);

/* Invalidate a range of o-cache/d-cache, given a physical address range */
void dcache_inval_range(uint32 start, uint32 count);

/* Flush a range of o-cache/d-cache, given a physical address range */
void dcache_flush_range(uint32 start, uint32 count);

__END_DECLS

#endif	/* __ARCH_CACHE_H */

