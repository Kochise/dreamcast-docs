/* KallistiOS ##version##

   include/kos/genwait.h
   Copyright (c)2003 Dan Potter

   $Id: genwait.h,v 1.2 2003/02/16 04:55:24 bardtx Exp $

*/

#ifndef __KOS_GENWAIT_H
#define __KOS_GENWAIT_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <sys/queue.h>
#include <kos/thread.h>

/* Sleep on the object "obj". The sleep status will be listed in any
   textual displays as "mesg". If "timeout" is non-zero, then the thread
   will be woken again after timeout milliseconds even if it hasn't
   been signaled manually. If "callback" is non-NULL, then the given
   function will be called with "obj" as its parameter if the wait
   times out (but before the thread is re-scheduled). */
int genwait_wait(void * obj, const char * mesg, int timeout, void (*callback)(void *));

/* Wake up N threads waiting on the given object. If cnt is <=0, then we
   wake all threads. Returns the number of threads actually woken. */
int genwait_wake_cnt(void * obj, int cnt);

/* Wake up all threads waiting on the given object. */
void genwait_wake_all(void * obj);

/* Wake up one thread waiting on the given object. */
void genwait_wake_one(void * obj);

/* Called by the scheduler to look for timed out genwait_wait calls. 
   Pass the current system clock as "now". */
void genwait_check_timeouts(uint64 now);

/* Returns the time of the next timeout event. If there are no pending
   timeout events, then we return zero. Called by the scheduler. */
uint64 genwait_next_timeout();

/* Initialize the genwait system */
int genwait_init();

/* Shut down the genwait system */
void genwait_shutdown();
         

__END_DECLS

#endif	/* __KOS_GENWAIT_H */

