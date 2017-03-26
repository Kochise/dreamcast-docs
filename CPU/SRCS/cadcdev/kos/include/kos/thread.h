/* KallistiOS ##version##

   include/kos/thread.h
   Copyright (C)2000,2001,2002,2003 Dan Potter

   $Id: thread.h,v 1.13 2003/06/23 05:19:50 bardtx Exp $

*/

#ifndef __KOS_THREAD_H
#define __KOS_THREAD_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <arch/irq.h>
#include <arch/arch.h>
#include <sys/queue.h>
#include <sys/reent.h>

/* Priority values */
#define PRIO_MAX 4096
#define PRIO_DEFAULT 10

/* Pre-define list/queue types */
struct kthread;
TAILQ_HEAD(ktqueue, kthread);
LIST_HEAD(ktlist, kthread);

/* Structure describing one running thread */
typedef struct kthread {
	/* Thread list handle */
	LIST_ENTRY(kthread)		t_list;

	/* Run/Wait queue handle */
	TAILQ_ENTRY(kthread)		thdq;

	/* Timer queue handle (if applicable) */
	TAILQ_ENTRY(kthread)		timerq;

	/* Kernel thread id */
	tid_t	tid;

	/* Static priority: 0..PRIO_MAX (higher means lower priority) */
	prio_t	prio;

	/* Flags */
	uint32	flags;

	/* Process state */
	int	state;

	/* Generic wait target and message, if applicable */
	void		* wait_obj;
	const char	* wait_msg;

	/* Wait timeout callback: if the genwait times out, this function
	   will be called. This allows hooks for things like fixing up
	   semaphore count values, etc. */
	void (*wait_callback)(void * obj);

	/* Next scheduled time; used for sleep and timed block
	   operations. This value is in milliseconds since the start of
	   timer_ms_gettime(). This should be enough for something like
	   2 million years of wait time ;) */
	uint64		wait_timeout;

	/* Thread label; used when printing out a user-readable
	   process listing. */
	/* XXX: Move to TLS */
	char	label[256];

	/* Current file system path */
	/* XXX: Move to TLS */
	char	pwd[256];

	/* Register store; used to save thread context */
	irq_context_t	context;

	/* Thread private stack; this should be a pointer to the base
	   of a stack page. */
	uint32	*stack;
	uint32	stack_size;

	/* Our errno variable */
	/* XXX: Move to TLS */
	int	thd_errno;

	/* Our re-ent struct for newlib */
	struct _reent thd_reent;
} kthread_t;

/* Thread flag values */
#define THD_DEFAULTS	0	/* Defaults: no flags */
#define THD_USER	1	/* Thread runs in user mode */
#define THD_QUEUED	2	/* Thread is in the run queue */

/* Thread state values */
#define STATE_ZOMBIE		0x0000	/* Waiting to die */
#define STATE_RUNNING		0x0001	/* Process is "current" */
#define STATE_READY		0x0002	/* Ready to be scheduled */
#define STATE_WAIT		0x0003	/* Blocked on a genwait */

/* Are threads cooperative or pre-emptive? */
extern int thd_mode;
#define THD_MODE_NONE		-1	/* Threads not running */
#define THD_MODE_COOP		0
#define THD_MODE_PREEMPT	1

/* Thread list; note: do not manipulate directly */
extern struct ktlist thd_list;

/* Run queue; note: do not manipulate directly */
extern struct ktqueue run_queue;

/* The currently executing thread */
extern kthread_t *thd_current;

/* "Jiffy" count; just counts context switches */
/* XXX: Deprecated! */
extern vuint32 jiffies;

/* Blocks the calling thread and performs a reschedule as if a context
   switch timer had been executed. This is useful for, e.g., blocking
   on sync primitives. The param 'mycxt' should point to the calling
   thread's context block. This is implemented in arch-specific code. 
   The meaningfulness of the return value depends on whether the
   unblocker set a return value or not. */
int thd_block_now(irq_context_t * mycxt);

/* This function looks at the state of the system and returns a new
   thread context to swap in. This is called from thd_block_now() and
   from the pre-emptive context switcher. Note that thd_current might
   be NULL on entering this function, if the caller blocked itself.
   It is assumed that by the time this returns, the irq_srt_addr and
   thd_current will be updated.*/
irq_context_t * thd_choose_new();

/* Given a thread ID, locates the thread structure */
kthread_t *thd_by_tid(tid_t tid);

/* Enqueue a process in the runnable queue; adds it right after the
   process group of the same priority if front_of_line is zero,
   otherwise queues it at the front of its priority group. */
void thd_add_to_runnable(kthread_t *t, int front_of_line);

/* Removes a thread from the runnable queue, if it's there. */
int thd_remove_from_runnable(kthread_t *thd);
   
/* New thread function; given a routine address, it will create a
   new kernel thread with a default stack. When the routine
   returns, the thread will exit. Returns the new thread id. */
kthread_t *thd_create(void (*routine)(void *param), void *param);

/* Given a thread id, this function removes the thread from
   the execution chain. */
int thd_destroy(kthread_t *thd);

/* Thread exit syscall (for use in user-mode processes, but can be used
   anywhere). */
void thd_exit() __noreturn;

/* Force a re-schedule; for most cases, you'll want to set front_of_line
   to zero, but read the comments in kernel/thread/thread.c for more
   info, especially if you need to guarantee low latencies. This just
   updates irq_srt_addr and thd_current. Set 'now' to non-zero if you want
   thd_schedule() to use a particular system time for checking timeouts. */
void thd_schedule(int front_of_line, uint64 now);

/* Force a given thread to the front of the queue */
void thd_schedule_next(kthread_t *thd);

/* Throw away the curren thread's timeslice */
void thd_pass();

/* Sleep for a given number of milliseconds */
void thd_sleep(int ms);

/* Set a thread's priority value; if it is scheduled already, it will be
   rescheduled with the new priority value. */
int thd_set_prio(kthread_t *thd, prio_t prio);

/* Return the current thread's kthread struct */
kthread_t *thd_get_current();

/* Retrive / set thread label */
const char *thd_get_label(kthread_t *thd);
void thd_set_label(kthread_t *thd, const char *label);

/* Retrieve / set thread pwd */
const char *thd_get_pwd(kthread_t *thd);
void thd_set_pwd(kthread_t *thd, const char *pwd);

/* Retrieve a pointer to the thread errno */
int * thd_get_errno(kthread_t *thd);

/* Retrieve a pointer to the thread reent struct */
struct _reent * thd_get_reent(kthread_t *thd);

/* Change threading modes */
int thd_set_mode(int mode);

/* Wait for a thread to exit */
int thd_wait(kthread_t * thd);


/* Init */
int thd_init(int mode);

/* Shutdown */
void thd_shutdown();

__END_DECLS

#endif	/* __KOS_THREAD_H */

