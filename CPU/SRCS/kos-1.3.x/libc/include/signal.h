/* KallistiOS ##version##

   signal.h
   Copyright (C)2003 Dan Potter

   $Id: signal.h,v 1.1 2003/07/15 07:57:35 bardtx Exp $

*/

#ifndef __SIGNAL_H
#define __SIGNAL_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Signal handler type; not entirely unix compatible but that should be ok. */
typedef int (*sighandler_t)(int, void * data);

/* Set a signal handler for the given signal. */
sighandler_t signal(int sig, sighandler_t hnd);

/* Default and ignore actions */
#define SIG_DFL		((sighandler_t)0)
#define SIG_IGN		((sighandler_t)-1)

/* We define a couple of standard *n*x-ish signals that have an obvious
   use. Other things will generally be handled through direct name manager
   interfaces. */
#define SIGQUIT		3	/* Request graceful program termination */
#define SIGCHLD		17	/* Child process terminated */

/* This function should receive process signals (setup by crt0) */
struct kprocess;
int _libc_signal_handler(struct kprocess * self, int sig, void * data);

__END_DECLS

#endif	/* __SIGNAL_H */

