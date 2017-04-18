/* KallistiOS 1.1.6

   include/kos/cond.h
   (c)2001 Dan Potter

   $Id: cond.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __KOS_COND_H
#define __KOS_COND_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/iovec.h>
#include <sys/queue.h>
#include <kos/thread.h>

/* Condition structure */
typedef struct condvar {
	/* List entry for the global list of condvars */
	LIST_ENTRY(condvar)	g_list;

	/* Basic condvar info */
	tid_t		owner;

	/* Threads blocked waiting for a signal */
	struct ktqueue	blocked_wait;
} condvar_t;

LIST_HEAD(condlist, condvar);

/* Allocate a new condvar; the condvar will be assigned
   to the calling process and when that process dies, the condvar
   will also die. */
condvar_t *cond_create();

/* Free a condvar */
void cond_destroy(condvar_t *cv);

/* Wait on a condvar */
void cond_wait(condvar_t *cv);

/* Signal a condvar */
void cond_signal(condvar_t *cv);

/* Free all condvars for the given process' pid */
void cond_freeall(int pid);

/* Init / shutdown */
int cond_init();
void cond_shutdown();

__END_DECLS

#endif	/* __KOS_COND_H */

