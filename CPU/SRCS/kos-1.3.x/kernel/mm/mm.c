/* KallistiOS ##version##

   mm.c
   Copyright (C)2001,2003 Dan Potter
*/

/* A simple page allocator; this routine is extremely simple and naive
   right now. An almost-static array of pages is kept with one pid_t
   entry per page of memory. Each page is either unused (-1), or belongs
   to some process (whose PID is entered into the slot). */

/* This was imported/adapted from KOS-MMU. */

#include <stdio.h>
#include <assert.h>
#include <kos/mm.h>
#include <arch/spinlock.h>

CVSID("$Id: mm.c,v 1.4 2003/08/02 23:12:36 bardtx Exp $");


/* The end of the program is always marked by the '_end' symbol. So we'll
   longword-align that and add a little for safety. The page allocation
   tables will go after that, and then the actual pages. */
extern ptr_t end;
static pid_t *pt_base;
static int pt_count;
static ptr_t page_base;

static spinlock_t lock;

/* MM-wide initialization */
int mm_init() {
	ptr_t base = (ptr_t)(&end);
	int i;

	/* Page allocation tables go first */
	pt_base = (pid_t*)base;

	/* Pages available in the system */
	pt_count = page_count;

	/* Move up to the next page boundary */
	base = base + pt_count*sizeof(pid_t);
	base = (base + (PAGESIZE-1)) & ~(PAGESIZE-1);

	/* Mark all of the page table pages as not taken */
	for (i=0; i<pt_count; i++)
		pt_base[i] = -1;

	/* Mark all of the kernel pages as taken */
	for (i=0; i<phys_to_page(base); i++)
		pt_base[i] = 0;

	page_base = base;

	dbgio_printf("mm: %ldk/%ldk available\n",
		(uint32)(((pt_count - phys_to_page(base)) << PAGESIZE_BITS) >> 10),
		(uint32)((page_count << PAGESIZE_BITS) >> 10));
	dbgio_printf("    page alloc tables at %p, first page at %p\n",
		pt_base, (void *)page_base);

	spinlock_init(&lock);

	return 0;
}

/* Allocate the first N consecutive pages as owned by the given process,
   and return a physical pointer to the pages. */
static ptr_t _mm_palloc(ptr_t reqat, size_t n, kprocess_t * proc) {
	int i, j, s;
	pid_t pid;

	/* Boostrapping */
	if (proc == NULL)
		pid = 1;
	else
		pid = proc->pid;

	/* If reqat is non-zero, try to alloc there. If that fails, fall
	   back on the normal algorithm. */
	if (reqat != 0) {
		/* Start at the requested page */
		i = phys_to_page(reqat);
		s = 1;

		/* Scan forwards */
		for (j=i; j<(i+n); j++) {
			if (pt_base[j] != -1) {
				s = 0;
				break;
			}
		}
		if (s) {
			/* Yes -- mark this as used and return it */
			for (j=i; j<(i+n); j++)
				pt_base[j] = proc->pid;
			return reqat;
		}
	}

	/* Nope, that failed -- go for the standard approach. */
	for (i=0; i<pt_count; i++) {
		/* Found a potential starting page? */
		if (pt_base[i] == -1) {
			/* Scan forwards to see if there's space */
			s = 1;
			for (j=i+1; j<(i+n); j++)
				if (pt_base[j] != -1) {
					s = 0;
					break;
				}
			if (!s) {
				/* Nope -- skip all the way up since there's
				   no possibility for a match now. */
				i = j;
				continue;
			} else {
				/* Yep -- mark them as used and return the
				   new space. */
				for (j=i; j<(i+n); j++)
					pt_base[j] = proc->pid;
				return page_to_phys(i);
			}
		}
	}

	return (ptr_t)0;
}

ptr_t mm_palloc(ptr_t reqat, size_t n, kprocess_t * proc) {
	ptr_t rv;
	
	spinlock_lock(&lock);
	rv = _mm_palloc(reqat, n, proc);
	spinlock_unlock(&lock);

	return rv;
}

/* Free N blocks starting at the given physical address */
void mm_pfree(ptr_t phys, size_t n) {
	ptr_t page = phys_to_page(phys);
	int i;

	for (i=0; i<n; i++)
		pt_base[page+i] = -1;
}

/* Chown N blocks starting at the given physical address to the
   given process id */
void mm_pchown(ptr_t phys, size_t n, kprocess_t * p) {
	ptr_t page = phys_to_page(phys);
	int i;

	for (i=0; i<n; i++)
		pt_base[page+i] = p->pid;
}

/* Free all pages belonging to a particular process; the number of freed
   pages will be returned. */
int mm_pfreeall(kprocess_t * p) {
	int i, cnt;

	cnt = 0;
	for (i=0; i<pt_count; i++)
		if (pt_base[i] == p->pid) {
			pt_base[i] = -1;
			cnt++;
		}
	return cnt;
}

/* Debug function prints out the memory map */
void mm_dbg_pmap() {
	kprocess_t * proc;
	int i, j, us, fr, cnt;
	int frlargest = 0;
	
	printf("Memory page mappings:\n");
	us = fr = 0;
	for (i=0; i<pt_count; ) {
		if (pt_base[i] == -1) {
			for (j=i,cnt=0; j<=pt_count; j++, cnt++) {
				if (j == pt_count || pt_base[j] != -1) {
					printf(" %d: free (%d pages)\n", i, cnt);
					if (cnt > frlargest)
						frlargest = cnt;
					i = j;
					break;
				}
			}
			fr += cnt;
		} else {
			if (pt_base[i] == 0) {
				printf(" %d: kernel image", i);
			} else {
				proc = process_by_pid(pt_base[i]);
				if (proc == NULL)
					printf(" %d: [unknown (%d)]", i, pt_base[i]);
				else
					printf(" %d: %s", i, proc->argv[0]);
			}

			for (j=i,cnt=0; j<=pt_count; j++, cnt++) {
				if (j == pt_count || pt_base[j] != pt_base[i]) {
					printf(" (%d pages)\n", cnt);
					i = j;
					break;
				}
			}
			us += cnt;
		}
	}
	printf("%d pages used, %d free, %d total\n", us, fr, us+fr);
	printf("%d bytes used, %d free, %d total\n", us*4096, fr*4096, (us+fr)*4096);
	printf("Largest contiguous free block: %d bytes/%d pages\n", frlargest*PAGESIZE, frlargest);
}
