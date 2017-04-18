/* KallistiOS 1.1.6

   include/kos/thread.h
   (c)2000-2001 Dan Potter

   $Id: thread.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __KOS_THREAD_H
#define __KOS_THREAD_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <arch/irq.h>
#include <arch/arch.h>
#include <sys/queue.h>
#include <sys/iovec.h>

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

	/* Run queue handle */
	TAILQ_ENTRY(kthread)		thdq;

	/* Kernel thread id */
	tid_t	tid;

	/* Static priority: 0..PRIO_MAX (higher means lower priority) */
	prio_t	prio;

	/* Flags */
	uint32	flags;

	/* Process state */
	int	state;

	/* Next scheduled tick; used for thread sleep operations */
	uint32	next_jiffy;

	/* When blocked on message send, this wil point to the place from
	   which to grab the data. */
	iovec_t *msg_send_iov;
	int	msg_send_cnt;

	/* When blocked on message receive, this will point to the place
	   to put the resulting message. */
	iovec_t	*msg_recv_iov;
	int	msg_recv_cnt;

	/* Thread label; used when printing out a user-readable
	   process listing. */
	char	label[256];

	/* Current file system path */
	char	pwd[256];

	/* Register store; used to save thread context */
	irq_context_t	context;

	/* Thread private stack; this should be a pointer to the base
	   of a stack page. */
	uint32	*stack;
	uint32	stack_size;
} kthread_t;

/* Thread flag values */
#define THD_DEFAULTS	0	/* Defaults: no flags */
#define THD_USER	1	/* Thread runs in user mode */
#define THD_QUEUED	2	/* Thread is in the run queue */

/* Thread state values */
#define STATE_ZOMBIE		0x0000	/* Waiting to die */
#define STATE_RUNNING		0x0001	/* Process is "current" */
#define STATE_READY		0x0002	/* Ready to be scheduled */
#define STATE_SLEEP		0x0003	/* Sleeping until next_jiffy */
#define STATE_WAITSEND		0x1000	/* Waiting to be able to send */
#define STATE_WAITRECV		0x1001	/* Waiting to be able to receive */
#define STATE_WAITREPLY		0x1002	/* Waiting for a reply */
#define STATE_WAITSEM		0x2000	/* Waiting on a semaphore queue */
#define STATE_WAITCOND		0x2010	/* Waiting on a condvar queue */

/* Are threads enabled? */
extern int thd_enabled;

/* Thread list; note: do not manipulate directly */
extern struct ktlist thd_list;

/* Run queue; note: do not manipulate directly */
extern struct ktqueue run_queue;

/* The currently executing thread */
extern kthread_t *thd_current;

/* "Jiffy" count */
extern vuint32 jiffies;

/* Given a thread ID, locates the thread structure */
kthread_t *thd_by_tid(tid_t tid);

/* Enqueue a process in the runnable queue; adds it right after the
   process group of the same priority. */
void thd_add_to_runnable(kthread_t *t);

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
void thd_exit();

/* Force a re-schedule */
void thd_schedule();

/* Force a given thread to the front of the queue */
void thd_schedule_next(kthread_t *thd);

/* Throw away the curren thread's timeslice */
void thd_pass();

/* Sleep for a given number of jiffies */
void thd_sleep_jiffies(int cnt);

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


/* Init */
int thd_init();

/* Shutdown */
void thd_shutdown();

__END_DECLS

#endif	/* __KOS_THREAD_H */

