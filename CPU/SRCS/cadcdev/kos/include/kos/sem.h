/* KallistiOS ##version##

   include/kos/sem.h
   Copyright (C)2001,2003 Dan Potter

   $Id: sem.h,v 1.7 2003/07/31 00:38:00 bardtx Exp $

*/

#ifndef __KOS_SEM_H
#define __KOS_SEM_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <sys/queue.h>
#include <kos/thread.h>

/* Semaphore structure definition */
typedef struct semaphore {
	/* List entry for the global list of semaphores */
	LIST_ENTRY(semaphore)	g_list;

	/* Basic semaphore info */
	int		count;		/* The semaphore count */
} semaphore_t;

LIST_HEAD(semlist, semaphore);

/* Allocate a new semaphore. Sets errno to ENOMEM on failure. */
semaphore_t *sem_create(int value);

/* Free a semaphore */
void sem_destroy(semaphore_t *sem);

/* Wait on a semaphore. Returns -1 on error:
     EPERM - called inside interrupt
     EINTR - wait was interrupted */
int sem_wait(semaphore_t *sem);

/* Wait on a semaphore, with timeout (in milliseconds); returns -1
   on failure, otherwise 0.
     EPERM  - called inside interrupt
     EINTR  - wait was interrupted
     EAGAIN - timed out */
int sem_wait_timed(semaphore_t *sem, int timeout);

/* Attempt to wait on a semaphore. If the semaphore would block,
   then return an error instead of actually blocking. Note that this
   function, unlike the other waits, DOES work inside an interrupt.
     EAGAIN - would block */
int sem_trywait(semaphore_t *sem);

/* Signal a semaphore */
void sem_signal(semaphore_t *sem);

/* Return the semaphore count */
int sem_count(semaphore_t *sem);

/* Called by the periodic thread interrupt to look for timed out
   sem_wait_timed calls */
void sem_check_timeouts();

/* Init / shutdown */
int sem_init();
void sem_shutdown();

__END_DECLS

#endif	/* __KOS_SEM_H */

