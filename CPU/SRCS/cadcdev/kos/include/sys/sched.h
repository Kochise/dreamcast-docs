#ifndef __SYS_SCHED_H
#define __SYS_SCHED_H

#include <kos/cdefs.h>
__BEGIN_DECLS

// These are copied from Newlib to make stuff compile as expected.

#define SCHED_OTHER    0
#define SCHED_FIFO     1
#define SCHED_RR       2

/* Scheduling Parameters, P1003.1b-1993, p. 249
   NOTE:  Fields whose name begins with "ss_" added by P1003.4b/D8, p. 33.  */

struct sched_param {
  int sched_priority;           /* Process execution scheduling priority */
};


// And all this maps pthread types to KOS types for pthread.h.
#include <kos/thread.h>
#include <kos/sem.h>
#include <kos/cond.h>
#include <kos/mutex.h>

// Missing structs we don't care about in this impl.
typedef struct {
	// Empty
} pthread_mutexattr_t;

typedef struct {
	// Empty
} pthread_condattr_t;

typedef struct {
	// Empty
} pthread_attr_t;

typedef struct {
	int initialized;
	int run;
} pthread_once_t;

typedef struct {
	// Empty
} pthread_key_t;

// Map over KOS types. The mutex/condvar maps have to be pointers
// because we allow _INIT #defines to work.
typedef kthread_t * pthread_t;
typedef mutex_t * pthread_mutex_t;
typedef condvar_t * pthread_cond_t;


__END_DECLS

#endif	/* __SYS_SCHED_H */
