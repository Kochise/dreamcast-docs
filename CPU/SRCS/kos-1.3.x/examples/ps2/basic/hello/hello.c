/* KallistiOS ##version##

   hello.c
   (c)2001 Dan Potter
*/

#include <kos.h>

/* You can safely remove this line if you don't use a ROMDISK */
extern uint8 romdisk[];

/* These macros tell KOS how to initialize itself. All of this initialization
   happens before main() gets called, and the shutdown happens afterwards. So
   you need to set any flags you want here. Here are some possibilities:

   INIT_NONE		-- don't do any auto init
   INIT_IRQ		-- Enable IRQs
   INIT_THD_PREEMPT	-- Enable pre-emptive threading
   INIT_NET		-- Enable networking (doesn't imply lwIP!)
   INIT_MALLOCSTATS	-- Enable a call to malloc_stats() right before shutdown

   You can OR any or all of those together. If you want to start out with
   the current KOS defaults, use INIT_DEFAULT (or leave it out entirely). */
KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

/* And specify a romdisk, if you want one (or leave it out) */
// KOS_INIT_ROMDISK(romdisk);

/* Your program's main entry point */
int main(int argc, char **argv) {
	uint8 * b;
	int i;
	
	/* The requisite line */
	printf("\nHello world!\n\n");

	/* Exercise the malloc/free calls a bit */
	printf("Allocating some ram:\n");
	b = malloc(64*1024);
	printf("Allocated 64k at %p\n", b);

	for (i=0; i<64*1024; i++)
		b[i] = i & 255;

	for (i=0; i<64*1024; i++)
		if (b[i] != (i & 255))
			printf("mismatch at %d\n", i);

	printf("Memory block checked ok, freeing\n");
	free(b);

	/* Manually cause an interrupt to test IRQs */
	printf("Doing syscall...\n");
	asm("syscall\n nop\n");

	/* Print a banner so we know we succeeded */
	printf("Done!\n");

	return 0;
}


