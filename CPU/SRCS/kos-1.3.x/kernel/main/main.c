/* KallistiOS ##version##

   main.c
   Copyright (C)2003 Dan Potter
*/

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <kos/elf.h>
#include <kos/process.h>
#include <sys/process.h>
#include <arch/arch.h>
#include <arch/cache.h>
#include <arch/mmu.h>

CVSID("$Id: main.c,v 1.4 2003/08/01 03:20:25 bardtx Exp $");

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

extern kprocess_t * controlling_proc;
int process_ksighnd(kprocess_t * proc, int sig, void * data);

void start_daemons() {
	const char * args[] = {
		"kosh.elf",
		"startup.sh"
	};
	kprocess_t * p;

	printf("Starting daemons:\n");
	assert( (p=process_vfork()) );
	assert( process_execv(args[0], 2, args) >= 0 );

	// This might fail if it's really fast, but that's ok.
	process_wait(p);
}

int main(int argc, char **argv) {
	kprocess_t * p;
	dbglog(DBG_INFO, "Hello from kernel main!\n");

	mmu_init();

	fs_chdir("/rd");

	start_daemons();

	printf("Starting kosh:\n");
	controlling_proc = p = process_vfork(); assert( p );
	if (process_execv("kosh.elf", 0, NULL) < 0)
		assert( 0 );

	printf("Waiting for kosh:\n");
	process_wait(p);

	printf("Done!\n");
	return 0;
}

