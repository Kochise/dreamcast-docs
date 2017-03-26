/* KallistiOS ##version##

   include/kos/cond.h
   (c)2001 Dan Potter

   $Id: cond.h,v 1.3 2003/02/16 05:16:40 bardtx Exp $

*/

#ifndef __KOS_COND_H
#define __KOS_COND_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/queue.h>
#include <kos/thread.h>
#include <kos/mutex.h>

/* Condition structure */
typedef struct condvar {
	/* List entry for the global list of condvars */
	LIST_ENTRY(condvar)	g_list;
} condvar_t;

LIST_HEAD(condlist, condvar);

/* Allocate a new condvar; the condvar will be assigned
   to the calling process and when that process dies, the condvar
   will also die. */
condvar_t *cond_create();

/* Free a condvar */
void cond_destroy(condvar_t *cv);

/* Wait on a condvar; if there is an associated mutex to unlock
   while waiting, then pass that as well. */
void cond_wait(condvar_t *cv, mutex_t * m);

/* Wait on a condvar; if there is an associated mutex to unlock
   while waiting, then pass that as well. If more than 'timeout'
   milliseconds passes and we still haven't been signaled, return
   an error code (-1). Return success (0) when we are woken normally.
   Note: if 'timeout' is zero, this call is equivalent to 
   cond_wait above. */
int cond_wait_timed(condvar_t *cv, mutex_t * m, int timeout);

/* Signal a single thread waiting on the condvar; you should be
   holding any associated mutex before doing this! */
void cond_signal(condvar_t *cv);

/* Signal all threads waiting on the condvar; you should be holding
   any associated mutex before doing this! */
void cond_broadcast(condvar_t *cv);

/* Init / shutdown */
int cond_init();
void cond_shutdown();

__END_DECLS

#endif	/* __KOS_COND_H */

