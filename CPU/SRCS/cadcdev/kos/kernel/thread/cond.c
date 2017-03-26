/* KallistiOS ##version##

   cond.c
   Copyright (c)2001,2003 Dan Potter
*/

/* Defines condition variables, which are like semaphores that automatically
   signal all waiting processes when a signal() is called. */

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include <kos/thread.h>
#include <kos/limits.h>
#include <kos/cond.h>
#include <kos/genwait.h>
#include <sys/queue.h>

CVSID("$Id: cond.c,v 1.8 2003/02/17 04:41:58 bardtx Exp $");

/**************************************/

/* Global list of condvars */
static struct condlist cond_list;

/* Allocate a new condvar; the condvar will be assigned
   to the calling process and when that process dies, the condvar
   will also die. */
condvar_t *cond_create() {
	condvar_t	*cv;
	int		old = 0;

	/* Create a condvar structure */
	cv = (condvar_t*)malloc(sizeof(condvar_t));
	if (!cv) {
		errno = ENOMEM;
		return NULL;
	}

	/* Add to the global list */
	old = irq_disable();
	LIST_INSERT_HEAD(&cond_list, cv, g_list);
	irq_restore(old);

	return cv;
}

/* Free a condvar */
void cond_destroy(condvar_t *cv) {
	int		old = 0;

	/* XXX Do something better with queued threads */
	genwait_wake_all(cv);

	/* Remove it from the global list */
	old = irq_disable();
	LIST_REMOVE(cv, g_list);
	irq_restore(old);

	/* Free the memory */
	free(cv);
}

int cond_wait_timed(condvar_t *cv, mutex_t *m, int timeout) {
	int old, rv;

	if (irq_inside_int()) {
		dbglog(DBG_WARNING, "cond_wait: called inside interrupt\n");
		errno = EPERM;
		return -1;
	}

	old = irq_disable();

	/* First of all, release the associated mutex */
	assert( mutex_is_locked(m) );
	mutex_unlock(m);

	/* Now block us until we're signaled */
	rv = genwait_wait(cv, timeout ? "cond_wait_timed" : "cond_wait", timeout, NULL);

	/* Re-lock our mutex */
	if (rv >= 0 || errno == EAGAIN) {
		mutex_lock(m);
	}

	/* Ok, ready to return */
	irq_restore(old);

	return rv;
}

int cond_wait(condvar_t *cv, mutex_t *m) {
	return cond_wait_timed(cv, m, 0);
}

void cond_signal(condvar_t *cv) {
	int old = 0;

	old = irq_disable();

	/* Wake any one thread who's waiting */
	genwait_wake_one(cv);

	irq_restore(old);
}

void cond_broadcast(condvar_t *cv) {
	int old = 0;

	old = irq_disable();

	/* Wake all threads who are waiting */
	genwait_wake_all(cv);

	irq_restore(old);
}

/* Initialize condvar structures */
int cond_init() {
	LIST_INIT(&cond_list);
	return 0;
}

/* Shut down condvar structures */
void cond_shutdown() {
	/* XXX Destroy all condvars here */
}
