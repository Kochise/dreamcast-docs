/* KallistiOS ##version##

   mm.c
   (c)2000-2002 Dan Potter
*/

#include <arch/types.h>
#include <arch/arch.h>

CVSID("$Id: mm.c,v 1.2 2002/11/03 03:40:55 bardtx Exp $");

/* The end of the program is always marked by the '_end' symbol. So we'll
   longword-align that and add a little for safety. sbrk() calls will
   move up from there. */
extern unsigned long end;
static void *sbrk_base;

/* MM-wide initialization */
int mm_init() {
	int base = (int)(&end);
	base = (base/4)*4 + 4;		/* longword align */
	sbrk_base = (void*)base;
	
	return 0;
}

/* Simple sbrk function */
void* sbrk(unsigned long increment) {
	void *base = sbrk_base;

	if (increment & 3)
		increment = (increment + 4) & ~3;
	sbrk_base += increment;

	/* Hard-coded for RedBoot usage right now */
	if ( ((ptr_t)sbrk_base) >= (0x81ff0000 - 65536) ) {
		panic("out of memory; about to run over kernel stack");
	}
	
	return base;
}


