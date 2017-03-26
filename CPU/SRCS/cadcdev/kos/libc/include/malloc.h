/* KallistiOS ##version##

   malloc.h
   Copyright (C)2003 Dan Potter

   $Id: malloc.h,v 1.6 2003/06/19 04:31:26 bardtx Exp $

*/

#ifndef __MALLOC_H
#define __MALLOC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Unlike previous versions, we totally decouple the implementation from
   the declarations. */

/* ANSI C functions */
struct mallinfo {
	int arena;    /* non-mmapped space allocated from system */
	int ordblks;  /* number of free chunks */
	int smblks;   /* number of fastbin blocks */
	int hblks;    /* number of mmapped regions */
	int hblkhd;   /* space in mmapped regions */
	int usmblks;  /* maximum total allocated space */
	int fsmblks;  /* space available in freed fastbin blocks */
	int uordblks; /* total allocated space */
	int fordblks; /* total free space */
	int keepcost; /* top-most, releasable (via malloc_trim) space */
};

void * malloc(size_t size);
void * calloc(size_t nmemb, size_t size);
void   free(void * ptr);
void * realloc(void * ptr, size_t size);
void * memalign(size_t alignment, size_t size);
void * valloc(size_t size);

struct mallinfo mallinfo();

/* mallopt defines */
#define M_MXFAST 1
#define DEFAULT_MXFAST 64

#define M_TRIM_THRESHOLD -1
#define DEFAULT_TRIM_THRESHOLD (256*1024)

#define M_TOP_PAD -2
#define DEFAULT_TOP_PAD 0

#define M_MMAP_THRESHOLD -3
#define DEFAULT_MMAP_THRESHOLD (256*1024)

#define M_MMAP_MAX -4
#define DEFAULT_MMAP_MAX 65536
int  mallopt(int, int);

/* Debug function */
void malloc_stats();

/* KOS specfic calls */
int malloc_irq_safe();

/* Only available with KM_DBG */
int mem_check_block(void *p);
int mem_check_all();

__END_DECLS

#endif	/* __MALLOC_H */

