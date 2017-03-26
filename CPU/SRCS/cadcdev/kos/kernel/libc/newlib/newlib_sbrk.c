/* KallistiOS ##version##

   newlib_sbrk.c
   Copyright (C)2004 Dan Potter

*/

#include <sys/reent.h>
#include <arch/arch.h>

char * _sbrk_r(struct _reent * reent, size_t incr) {
	return (char *)mm_sbrk((unsigned long)incr);
}
