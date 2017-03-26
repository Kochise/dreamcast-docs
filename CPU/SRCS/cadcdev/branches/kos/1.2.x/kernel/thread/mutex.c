/* KallistiOS ##version##

   mutex.c
   (c)2002 Dan Potter
*/

/* Defines a mutex: these are just wrappers around count-1
   semaphore objects. */

/**************************************/

#include <kos/mutex.h>

CVSID("$Id: mutex.c,v 1.2 2003/02/17 04:20:30 bardtx Exp $");

/**************************************/

/* Create a mutex */
mutex_t * mutex_create() {
	return sem_create(1);
}

/* Destroy a mutex */
void mutex_destroy(mutex_t * m) {
	sem_destroy(m);
}

/* Attempt to lock the mutex; if it's busy, then block */
void mutex_lock(mutex_t * m) {
	sem_wait(m);
}

/* Attempt to lock the mutex; if it's busy and it takes longer than the
   timeout (milliseconds) then return an error. */
int mutex_lock_timed(mutex_t * m, int timeout) {
	return sem_wait_timed(m, timeout);
}

/* Check to see whether the mutex is available; note that this is not
   a threadsafe way to figure out if it _will_ be locked by the time you
   get to locking it. */
int mutex_is_locked(mutex_t * m) {
	return sem_count(m) <= 0;
}

/* Unlock the mutex */
void mutex_unlock(mutex_t * m) {
	sem_signal(m);
}

