/* KallistiOS ##version##

   include/kos/mutex.h
   Copyright (C)2001,2003 Dan Potter

   $Id: mutex.h,v 1.2 2003/07/31 00:38:00 bardtx Exp $

*/

#ifndef __KOS_MUTEX_H
#define __KOS_MUTEX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* These are just wrappers around semaphores */
#include <kos/sem.h>

typedef semaphore_t mutex_t;

/* Create a mutex. Sets errno to ENOMEM on failure. */
mutex_t * mutex_create();

/* Destroy a mutex */
void mutex_destroy(mutex_t * m);

/* Attempt to lock the mutex; if it's busy, then block. Returns 0 on
   success, -1 on error.
     EPERM - called inside interrupt
     EINTR - wait was interrupted */
int mutex_lock(mutex_t * m);

/* Attempt to lock the mutex; if it's busy and it takes longer than the
   timeout (milliseconds) then return an error.
     EPERM  - called inside interrupt
     EINTR  - wait was interrupted
     EAGAIN - timed out */
int mutex_lock_timed(mutex_t * m, int timeout);

/* Check to see whether the mutex is available; note that this is not
   a threadsafe way to figure out if it _will_ be locked by the time you
   get to locking it. */
int mutex_is_locked(mutex_t * m);

/* Attempt to lock the mutex. If the mutex would block, then return an
   error instead of actually blocking. Note that this function, unlike
   the other waits, DOES work inside an interrupt.
     EAGAIN - would block */
int mutex_trylock(mutex_t * m);

/* Unlock the mutex */
void mutex_unlock(mutex_t * m);

__END_DECLS

#endif	/* __KOS_MUTEX_H */

