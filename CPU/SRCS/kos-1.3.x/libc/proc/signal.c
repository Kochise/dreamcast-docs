/* KallistiOS ##version##

   signal.c
   Copyright (C)2003 Dan Potter
*/

#include <signal.h>
#include <errno.h>
#include <sys/process.h>

CVSID("$Id: signal.c,v 1.1 2003/07/15 07:57:21 bardtx Exp $");

/*
   This module implements a Unix-like signal system. There are two important
   differences between this implementation and Unix:

   1) Signal functions are passed a "data" parameter for more specific info
   2) Signals need not be re-hooked after they are issued.
*/

/* Our signal table. We keep enough here for 32 signals. */
static sighandler_t sigtab[32] = { SIG_DFL };

sighandler_t signal(int sig, sighandler_t hnd) {
	sighandler_t old;

	if (sig >= 32) {
		errno = EINVAL;
		return NULL;
	}

	old = sigtab[sig];
	sigtab[sig] = hnd;
	return old;
}

int _libc_signal_handler(kprocess_t * self, int sig, void * data) {
	if (sig >= 32) {
		errno = EINVAL;
		return -1;
	}

	if (sigtab[sig] == SIG_DFL || sigtab[sig] == SIG_IGN)
		return 0;

	return sigtab[sig](sig, data);
}

