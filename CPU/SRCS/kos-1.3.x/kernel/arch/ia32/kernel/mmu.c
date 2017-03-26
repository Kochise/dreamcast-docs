/* KallistiOS ##version##

   arch/ia32/kernel/mmu.c
   Copyright (c)2003 Dan Potter
*/

#include <string.h>
#include <malloc.h>

#include <kos/thread.h>
#include <arch/arch.h>
#include <arch/types.h>
#include <arch/irq.h>
#include <arch/mmu.h>
#include <arch/dbgio.h>
#include <arch/cache.h>

CVSID("$Id: mmu.c,v 1.1 2003/08/01 03:18:37 bardtx Exp $");

void mmu_reset_itlb() {
}

void mmu_use_table(mmucontext_t *context) {
}

/* Allocate a page table shell; no actual sub-contexts will be allocated
   until a mapping is performed. */
mmucontext_t *mmu_context_create(int asid) {
	return NULL;
}

/* Destroy an MMU context when a process is being destroyed. */
void mmu_context_destroy(mmucontext_t *context) {
}

/* Using the given page tables, translate the virtual page ID to a 
   physical page ID. Return -1 on failure. */
int mmu_virt_to_phys(mmucontext_t *context, int virtpage) {
	return 0;
}

/* Switch to the given context; invalidate any caches as neccessary */
void mmu_switch_context(mmucontext_t *context) {
}

/* Map N pages sequentially */
void mmu_page_map(mmucontext_t *context,
		int virtpage, int physpage, int count,
		int prot, int cache, int share, int dirty) {
}

/* Copy a chunk of data from a process' address space into a
   kernel buffer, taking into account page mappings.

   This routine is pretty nasty.. this is completely platform
   generic but should probably be replaced by a nice assembly
   routine for each platform as appropriate. */
int mmu_copyin(mmucontext_t *context, uint32 srcaddr, uint32 srccnt, void *buffer) {
	return -1;
}

/* Copy a chunk of data from one process' address space to another
   process' address space, taking into account page mappings.

   This routine is pretty nasty.. this is completely platform
   generic but should probably be replaced by a nice assembly
   routine for each platform as appropriate. */
int mmu_copyv(mmucontext_t *context1, iovec_t *iov1, int iovcnt1,
		mmucontext_t *context2, iovec_t *iov2, int iovcnt2) {
	return -1;
}
		

/********************************************************************************/
/* Exception handlers */

mmu_mapfunc_t mmu_map_get_callback() {
	return NULL;
}

mmu_mapfunc_t mmu_map_set_callback(mmu_mapfunc_t newfunc) {
	return NULL;
}

/********************************************************************************/
/* Init routine */
int mmu_init() {
	return 0;
}

/* Shutdown */
void mmu_shutdown() {
}

