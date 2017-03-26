/* KallistiOS ##version##

   modhelper.c
   Copyright (C)2003 Dan Potter
*/

#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <sys/process.h>
#include <sys/module.h>
#include <kos/sem.h>

CVSID("$Id: modhelper.c,v 1.1 2003/07/15 07:57:21 bardtx Exp $");

/*
   Couple of helper functions for device drivers and similarly module-like
   programs.
*/

static semaphore_t * quitsem = NULL;

static int sighnd(int sig, void * data) {
	sem_signal(quitsem);
	return 0;
}

int kos_do_module(int (*modinit)(int, char **), int (*modshutdown)(), int argc, char **argv) {
	assert( !quitsem );

	if (modinit(argc, argv) < 0)
		return -1;

	quitsem = sem_create(0);
	signal(SIGQUIT, sighnd);

	daemonize();

	for ( ; ; ) {
		sem_wait(quitsem);
		if (modshutdown() >= 0)
			break;
	}
	sem_destroy(quitsem);
	quitsem = NULL;

	return 0;
}
