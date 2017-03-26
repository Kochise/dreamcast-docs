/* KallistiOS ##version##

   sem.c
   Copyright (c)2001,2002,2003 Dan Potter
*/

/* Defines semaphores */

/**************************************/

#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include <kos/thread.h>
#include <kos/limits.h>
#include <kos/sem.h>
#include <kos/genwait.h>
#include <sys/queue.h>
#include <arch/spinlock.h>

CVSID("$Id: sem.c,v 1.13 2003/02/15 02:47:04 bardtx Exp $");

/**************************************/

/* Semaphore list spinlock */
static spinlock_t mutex;

/* Global list of semaphores */
static struct semlist sem_list;

/* Allocate a new semaphore; the semaphore will be assigned
   to the calling process and when that process dies, the semaphore
   will also die. */
semaphore_t *sem_create(int value) {
	semaphore_t	*sm;

	/* Create a semaphore structure */
	sm = (semaphore_t*)malloc(sizeof(semaphore_t));
	if (!sm) {
		errno = ENOMEM;
		return NULL;
	}
	sm->count = value;

	/* Add to the global list */
	spinlock_lock(&mutex);
	LIST_INSERT_HEAD(&sem_list, sm, g_list);
	spinlock_unlock(&mutex);

	return sm;
}

/* Take care of destroying a semaphore */
void sem_destroy(semaphore_t *sm) {
	/* XXX Do something with queued threads */

	/* Remove it from the global list */
	spinlock_lock(&mutex);
	LIST_REMOVE(sm, g_list);
	spinlock_unlock(&mutex);

	/* Free the memory */
	free(sm);
}

int sem_wait(semaphore_t *sm) {
	int old, rv = 0;
	
	if (irq_inside_int()) {
		dbglog(DBG_WARNING, "sem_wait: called inside interrupt\n");
		errno = EPERM;
		return -1;
	}

	old = irq_disable();

	/* If there's enough count left, then let the thread proceed */
	if (sm->count > 0) {
		sm->count--;
	} else {
		/* Block us until we're signaled */
		sm->count--;
		rv = genwait_wait(sm, "sem_wait", 0, NULL);

		/* Did we get interrupted? */
		if (rv < 0) {
			assert( errno == EINTR );
			rv = -1;
		}
	}

	irq_restore(old);

	return rv;
}

/* This function will be called by genwait if we timeout. */
static void sem_timeout(void * obj) {
	/* Convert it back to a semaphore ptr */
	semaphore_t * s = (semaphore_t *)obj;

	/* Release a thread from the count */
	s->count++;
}

/* Wait on a semaphore, with timeout (in milliseconds) */
int sem_wait_timed(semaphore_t *sem, int timeout) {
	int old = 0, rv = 0;

	/* Make sure we're not inside an interrupt */
	if (irq_inside_int()) {
		dbglog(DBG_WARNING, "sem_wait_timed: called inside interrupt\n");
		errno = EPERM;
		return -1;
	}

	/* Check for smarty clients */
	if (timeout <= 0) {
		return sem_wait(sem);
	}

	/* Disable interrupts */
	old = irq_disable();

	/* If there's enough count left, then let the thread proceed */
	if (sem->count > 0) {
		sem->count--;
		rv = 0;
	} else {
		/* Block us until we're signaled */
		sem->count--;
		rv = genwait_wait(sem, "sem_wait_timed", timeout, sem_timeout);
	}

	irq_restore(old);

	return rv;
}

/* Attempt to wait on a semaphore. If the semaphore would block,
   then return an error instead of actually blocking. */
int sem_trywait(semaphore_t *sm) {
	int old = 0;
	int succeeded;

	old = irq_disable();

	/* Is there enough count left? */
	if (sm->count > 0) {
		sm->count--;
		succeeded = 0;
	} else {
		succeeded = -1;
		errno = EAGAIN;
	}

	/* Restore interrupts */
	irq_restore(old);

	return succeeded;
}

/* Signal a semaphore */ 
void sem_signal(semaphore_t *sm) {
	int		old = 0, woken;
	
	old = irq_disable();

	/* Is there anyone waiting? If so, pass off to them */
	if (sm->count < 0) {
		woken = genwait_wake_cnt(sm, 1);
		assert( woken == 1 );
		sm->count++;
	} else {
		/* No one is waiting, so just add another tick */
		sm->count++;
	}

	irq_restore(old);
}

/* Return the semaphore count */
int sem_count(semaphore_t *sm) {
	/* Look for the semaphore */
	return sm->count;
}

/* Initialize semaphore structures */
int sem_init() {
	LIST_INIT(&sem_list);
	spinlock_init(&mutex);
	return 0;
}

/* Shut down semaphore structures */
void sem_shutdown() { }


