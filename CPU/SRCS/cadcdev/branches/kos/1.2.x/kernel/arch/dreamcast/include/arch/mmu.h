/* KallistiOS ##version##

   arch/dreamcast/include/arch/mmu.h
   (c)2001 Dan Potter
   
   $Id: mmu.h,v 1.3 2002/10/08 07:46:20 bardtx Exp $
*/

#ifndef __ARCH_MMU_H
#define __ARCH_MMU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/iovec.h>

/* Since the software has to handle TLB misses on the SH-4, we have freedom
   to use any page table format we want (and thus save space), but we must
   make it quick to access. The SH-4 can address a maximum of 512M of address
   space per "area", but we only care about one area, so this is the total
   maximum addressable space. With 4K pages, that works out to 2^17 pages
   that must be mappable, or 17 bits. We use 18 bits just to be sure (there
   are a few left over).

   Page tables (per-process) are a sparse two-level array. The virtual address
   space is actually 2^30 bytes, or 2^(30-12)=2^18 pages, so there must be
   a possibility of having that many page entries per process space. A full
   page table for a process would be 1M, so this is obviously too big!! Thus
   the sparse array.

   The bottom layer of the page tables consists of a sub-context array for
   512 pages, which translates into 2K of storage space. The process then
   has the possibility of using one or more of the 512 top-level slots. For
   a very small process (using one page for code/data and one for stack), it
   should be possible to achieve a page table footprint of one page. The tables
   can grow from there as neccessary.

   Virtual addresses are broken up as follows:

   Bits 31 - 22		10 bits top-level page directory
   Bits 21 - 13		9 bits bottom-level page entry
   Bits 11 - 0		Byte index into page

   */

#define MMU_TOP_SHIFT 21
#define MMU_TOP_BITS 10
#define MMU_TOP_MASK ((1 << MMU_TOP_BITS) - 1)
#define MMU_BOT_SHIFT 12
#define MMU_BOT_BITS 9
#define MMU_BOT_MASK ((1 << MMU_BOT_BITS) - 1)
#define MMU_IND_SHIFT 0
#define MMU_IND_BITS 12
#define MMU_IND_MASK ((1 << MMU_IND_BITS) - 1)

/* MMU TLB entry for a single page (one 32-bit word) */
typedef struct mmupage {
	/*uint32	virtual; */	/* implicit */
	uint32		physical:18;	/* Physical page ID	-- 18 bits */
	uint32		prkey:2;	/* Protection key data	-- 2 bits  */
	uint32		valid:1;	/* Valid mapping	-- 1 bit   */
	uint32		shared:1;	/* Shared between procs	-- 1 bit   */
	uint32		cache:1;	/* Cacheable		-- 1 bit   */
	uint32		dirty:1;	/* Dirty		-- 1 bit   */
	uint32		wthru:1;	/* Write-thru enable	-- 1 bit   */
	uint32		blank:7;	/* Reserved		-- 7 bits */
} mmupage_t;

/* MMU sub-context type. We have two-level page tables on
   SH-4, and each sub-context contains 512 entries. */
#define MMU_SUB_PAGES	512
typedef struct mmusubcontext {
	mmupage_t	page[MMU_SUB_PAGES];	/* 512 pages */
} mmusubcontext_t;

/* MMU Context type */
#define MMU_PAGES	1024
typedef struct mmucontext {
	mmusubcontext_t	*sub[MMU_PAGES];	/* 1024 sub-contexts */
	int		asid;			/* Address Space ID */
} mmucontext_t;

/* "Current" page tables (for TLB exception handling) */
extern mmucontext_t *mmu_cxt_current;

/* Set the "current" page tables for TLB handling */
void mmu_use_table(mmucontext_t *context);

/* Allocate a new MMU context; each process should have exactly one of
   these, and these should not exist without a process. */
mmucontext_t *mmu_context_create(int asid);

/* Destroy an MMU context when a process is being destroyed. */
void mmu_context_destroy(mmucontext_t *context);

/* Using the given page tables, translate the virtual page ID to a 
   physical page ID. Return -1 on failure. */
int mmu_virt_to_phys(mmucontext_t *context, int virtpage);

/* Using the given page tables, translate the physical page ID to a
   virtual page ID. Return -1 on failure. */
int mmu_phys_to_virt(mmucontext_t *context, int physpage);

/* Switch to the given context; invalidate any caches as neccessary */
void mmu_switch_context(mmucontext_t *context);

/* Set the given virtual page as invalid (unmap it) */
void mmu_page_invalidate(mmucontext_t *context, int virtpage, int count);

/* Set the given virtual page to map to the given physical page; implies
   turning on the "valid" bit. Also sets the other named attributes.*/
void mmu_page_map(mmucontext_t *context, int virtpage, int physpage,
	int count, int prot, int cache, int share, int dirty);

/* Set the page protection to the given values */
#define MMU_KERNEL_RDONLY	0
#define MMU_KERNEL_RDWR		1
#define MMU_ALL_RDONLY		2
#define MMU_ALL_RDWR		3
void mmu_page_protect(mmucontext_t *context, int virtpage, int count,
	int prot);

/* Set the cacheing type to the given values */
#define MMU_NO_CACHE		1
#define MMU_CACHE_BACK		2	/* Write-back */
#define MMU_CACHE_WT		3	/* Write-thru */
#define MMU_CACHEABLE		MMU_CACHE_BACK
void mmu_page_cache(mmucontext_t *context, int virtpage, int count, int cache);

/* Set a page as shared or not */
#define MMU_NOT_SHARED		0
#define MMU_SHARED		1
void mmu_page_share(mmucontext_t *context, int virtpage, int count, int share);

/* Read the "dirty" bit of the page; potentially reset the bit. */
#define MMU_NO_CHANGE		0
#define MMU_CLEAN		1
#define MMU_DIRTY		2
int mmu_page_dirty(mmucontext_t *context, int virtpage, int count, int reset);

/* Copy a chunk of data from a process' address space into a
   kernel buffer, taking into account page mappings. */
int mmu_copyin(mmucontext_t *context, uint32 srcaddr, uint32 srccnt, void *buffer);

/* Copy a chunk of data from one process' address space to another
   process' address space, taking into account page mappings. */
int mmu_copyv(mmucontext_t *context1, iovec_t *iov1, int iovcnt1,
	mmucontext_t *context2, iovec_t *iov2, int iovcnt2);

/* MMU syscalls */
void sc_mmu_mmap(uint32 dst, size_t len, uint32 src);

/* Get/set thefunction to handle virt->phys page mapping; the function
   should return a pointer to an mmupage_t on success, or NULL on
   failure. */
typedef mmupage_t * (*mmu_mapfunc_t)(mmucontext_t * context, int virtpage);
mmu_mapfunc_t mmu_map_get_callback();
mmu_mapfunc_t mmu_map_set_callback(mmu_mapfunc_t newfunc);

/* Init / shutdown MMU */
int mmu_init();
void mmu_shutdown();

__END_DECLS

#endif	/* __ARCH_MMU_H */

