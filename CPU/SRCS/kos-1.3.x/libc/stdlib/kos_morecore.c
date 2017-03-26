/* KallistiOS ##version##

   kos_morecore.c
   Copyright (C)2003 Dan Potter

   $Id: kos_morecore.c,v 1.1 2003/06/19 04:31:26 bardtx Exp $
*/

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <arch/arch.h>
#include <kos/mm.h>
#include <sys/queue.h>
#include <sys/process.h>

/*

   This module provides _kos_morecore, which is an sbrk-style function that
   handles allocating pages from the free page pool and returning them to
   dlmalloc. Because of the design of dlmalloc, we can safely have gaps in
   the values we return, but we also must keep a stack of used pages so that
   we can free them with negative values of "requested". That's where it
   starts getting tricky.

   Also, because this is always called from dlmalloc, we can assume that
   thread locking has already been done.

*/

/* Our page directory pages are filled with this struct. */
typedef struct pagegrp {
	ptr_t	base;		/* == 0 -> unused */
	size_t	pagecnt;
} pagegrp_t;

/* Each page directory page is prefaced with one of these. This struct
   should be the same size as pagegrp_t. */
typedef struct dirpage {
	TAILQ_ENTRY(dirpage)	q;
} dirpage_t;

/* This will point to our page directory pages. */
static TAILQ_HEAD(dplist, dirpage) dirpages;
static int initted = 0;

/* Some quick constants for portability */
#define ENTRY_CNT ( (PAGESIZE / sizeof(pagegrp_t)) - 1 )
#define ENTRY(p, x) ( ((pagegrp_t *)p)+x+1 )

void * _kos_morecore(ptrdiff_t requested) {
	ptr_t		pages;
	pagegrp_t	* pg;
	dirpage_t	* dp;
	int		down, i, eaten;
	void		* rv;

	if (!initted) {
		TAILQ_INIT(&dirpages);
		initted = 1;
	}

	// printf("%s: morecore: %d\n", _local_process->label, requested);

	/* Demunge release request */
	down = requested < 0;
	if (down)
		requested = -requested;

	/* Check for invalid inputs */
	assert( (requested % PAGESIZE) == 0 );
	assert( sizeof(dirpage_t) == sizeof(pagegrp_t) );

	/* Grab the last entry on the queue. If we don't have one yet, or the
	   last one is full, then allocate one and add it to the chain. */
	dp = NULL;
	if (!TAILQ_EMPTY(&dirpages)) {
		dp = TAILQ_LAST(&dirpages, dplist);
		// printf("  queue not empty, dp = %p\n", dp);
	}
	if (!dp || (requested > 0 && !down && ENTRY(dp, ENTRY_CNT - 1)->base != 0)) {
		// printf("  adding to page dirs\n");
		/* Allocate a new page dir page. */
		dp = (dirpage_t *)mm_palloc(0, 1, _local_process);
		if (dp == NULL)
			return (void *)-1;
		memset(dp, 0, PAGESIZE);
		TAILQ_INSERT_TAIL(&dirpages, dp, q);
	}
	/* Now figure out what to do... */
	if (requested == 0) {
		/* Just return the address after the end of the last allocated
		   block. If we haven't allocated one, return zero. */
		for (i=ENTRY_CNT-1; i>=0; i--) {
			if (ENTRY(dp, i)->base != 0) {
				// printf("  returning %p\n", (void *)(ENTRY(dp, i)->base + ENTRY(dp, i)->pagecnt*PAGESIZE)); 
				return (void *)(ENTRY(dp, i)->base + ENTRY(dp, i)->pagecnt*PAGESIZE);
			}
		}
		// printf("  returning NULL\n");
		return NULL;
	} else if (!down) {	/* Alloc */
		pages = 0;

		/* Find the last entry so we can try to expand that */
		pg = NULL;
		for (i=ENTRY_CNT-1; i>=0; i--) {
			if (ENTRY(dp, i)->base != 0) {
				pg = ENTRY(dp, i);
				break;
			}
		}
		if (pg) {
			/* Try to add to the last block */
			pages = mm_palloc(pg->base + pg->pagecnt*PAGESIZE,
				requested/PAGESIZE, _local_process);

			/* If we succeeded, then just extend the block and return the
			   new space. */
			if (pages == pg->base + pg->pagecnt*PAGESIZE) {
				/* printf("  extended block at %p by %d pages (now %d)\n",
					(void *)pg->base,requested/PAGESIZE,
					pg->pagecnt + requested/PAGESIZE); */
				rv = (void *)(pg->base + pg->pagecnt * PAGESIZE);
				pg->pagecnt += requested/PAGESIZE;
				return rv;
			}
		}

		/* We failed to extend the last block. Try a new one. */
		if (!pages)
			pages = mm_palloc(0, requested / PAGESIZE, _local_process);
		if (!pages)
			return (void *)-1;
		//printf("  allocated %d pages at %p\n", requested / PAGESIZE, (void *)pages);

		/* Add this as a new block to the page dir */
		pg = NULL;
		for (i=0; i<ENTRY_CNT; i++) {
			if (ENTRY(dp, i)->base == 0) {
				pg = ENTRY(dp, i);
				break;
			}
		}
		assert( pg );
		if (!pg)
			return (void *)-1;

		pg->base = pages;
		pg->pagecnt = requested / PAGESIZE;
		//printf("  added page dir entry\n");

		return (void *)pg->base;
	} else {		/* Free */
		/* Find the last entry */
		pg = NULL;
		for (i=ENTRY_CNT-1; i>=0; i--) {
			if (ENTRY(dp, i)->base != 0) {
				pg = ENTRY(dp, i);
				break;
			}
		}
		assert( pg );
		if (!pg)
			return (void *)-1;
		rv = (void *)(pg->base + pg->pagecnt * PAGESIZE);

		//printf("  found last page block at %p(%d)\n", (void *)pg->base, pg->pagecnt);

		requested = requested / PAGESIZE;
		while (requested > 0) {
			/* Can we devour this whole chunk? */
			if (requested >= pg->pagecnt) {
				//printf("  freeing %d pages at %p\n", pg->pagecnt, (void *)pg->base);
				mm_pfree(pg->base, pg->pagecnt);
				eaten = pg->pagecnt;
				pg->base = 0;
			} else {
				eaten = requested;
				//printf("  freeing %d pages at %p\n", eaten, (void *)(pg->base + (pg->pagecnt - eaten)*PAGESIZE));
				mm_pfree(pg->base + (pg->pagecnt - eaten)*PAGESIZE, eaten);
			}
			requested -= eaten;
			pg--;
			i--;
			if (i < 0 && requested > 0) {
				//printf("  going back a page\n");
				/* Go back a page */
				pages = (ptr_t)dp;
				dp = TAILQ_PREV(dp, dplist, q);
				assert( dp );
				if (!dp)
					return (void *)-1;

				/* We killed off that dir page, release it */
				//printf("  freeing page dir page @ %p\n", (void *)pages);
				mm_pfree(pages, 1);

				/* Reposition our counters */
				i = ENTRY_CNT - 1;
				pg = ENTRY(dp, i);
			}
		}

		//printf("  done\n");

		return rv;
	}
}
