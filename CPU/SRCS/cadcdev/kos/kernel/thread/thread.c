/* KallistiOS ##version##

   kernel/thread.c
   Copyright (c)2000,2001,2002,2003 Dan Potter
*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <reent.h>
#include <kos/thread.h>
#include <kos/sem.h>
#include <kos/cond.h>
#include <kos/genwait.h>
#include <arch/irq.h>
#include <arch/timer.h>
#include <arch/arch.h>

CVSID("$Id: thread.c,v 1.22 2003/04/08 05:29:46 bardtx Exp $");

/*

This module supports thread scheduling in KOS. The timer interrupt is used
to re-schedule the processor HZ times per second in pre-emptive mode. 
This is a fairly simplistic scheduler, though it does employ some 
standard advanced OS tactics like priority scheduling and semaphores.

Some of this code ought to look familiar to BSD-heads; I studied the
BSD kernel quite a bit to get some ideas on priorities, and I am
also using their queue library verbatim (sys/queue.h).
 
*/

/* Uncomment the following line to enable experimental jiffyless thread
   switching support. Doesn't work very well right now. */
/* #define JIFFYLESS */

/*****************************************************************************/
/* Thread scheduler data */

/* Thread list. This includes all threads except dead ones. */
static struct ktlist thd_list;

/* Run queue. This is more like on a standard time sharing system than the
   previous versions. The top element of this priority queue should be the
   thread that is ready to run next. When a thread is scheduled, it will be
   removed from this queue. When it's de-scheduled, it will be re-inserted
   by its priority value at the end of its priority group. Note that right
   now this condition is being broken because sleeping threads are on the
   same queue. We deal with those in thd_switch below. */
static struct ktqueue run_queue;

/* "Jiffy" count: this is basically a counter that gets incremented each
   time a timer interrupt happens. XXX: Deprecated. */
vuint32 jiffies;

#ifdef JIFFYLESS
/* Next pre-emption wake up time. If we are in pre-emptive threading mode and
   there are multiple tasks contending for the CPU, then this var will have
   the next system time that we need to wake up for a context switch. */
uint64 thd_next_switch;
#endif

/* The currently executing thread. This thread should not be on any queues. */
kthread_t *thd_current = NULL;

/* Thread mode: cooperative or pre-emptive. */
int thd_mode = THD_MODE_NONE;

/*****************************************************************************/
/* Debug */
#include <kos/dbgio.h>

static const char *thd_state_to_str(kthread_t * thd) {
	switch(thd->state) {
		case STATE_ZOMBIE:
			return "zombie";
		case STATE_RUNNING:
			return "running";
		case STATE_READY:
			return "ready";
		case STATE_WAIT:
			if (thd->wait_msg)
				return thd->wait_msg;
			else
				return "wait";
		default:
			return "unknown";
	}
}

int thd_pslist(int (*pf)(const char *fmt, ...)) {
	kthread_t *cur;

	pf("All threads (may not be deterministic):\n");
	pf("addr\t\ttid\tprio\tflags\twait_timeout\tstate     name\n");
	
	LIST_FOREACH(cur, &thd_list, t_list) {
		pf("%08lx\t", CONTEXT_PC(cur->context));
		pf("%d\t", cur->tid);
		if (cur->prio == PRIO_MAX)
			pf("MAX\t");
		else
			pf("%d\t", cur->prio);
		pf("%08lx\t", cur->flags);
		pf("%ld\t\t", (uint32)cur->wait_timeout);
		pf("%10s", thd_state_to_str(cur));
		pf("%s\n", cur->label);
	}
	pf("--end of list--\n");

	return 0;
}

int thd_pslist_queue(int (*pf)(const char *fmt, ...)) {
	kthread_t *cur;

	pf("Queued threads:\n");
	pf("addr\t\ttid\tprio\tflags\twait_timeout\tstate     name\n");
	TAILQ_FOREACH(cur, &run_queue, thdq) {
		pf("%08lx\t", CONTEXT_PC(cur->context));
		pf("%d\t", cur->tid);
		if (cur->prio == PRIO_MAX)
			pf("MAX\t");
		else
			pf("%d\t", cur->prio);
		pf("%08lx\t", cur->flags);
		pf("%ld\t\t", (uint32)cur->wait_timeout);
		pf("%10s", thd_state_to_str(cur));
		pf("%s\n", cur->label);
	}

	return 0;
}

/*****************************************************************************/
/* Returns a fresh thread ID for each new thread */

/* Highest thread id (used when assigning next thread id) */
static tid_t tid_highest;


/* Return the next available thread id (assumes wraparound will not run
   into old processes). */
static tid_t thd_next_free() {
	int id;
	id = tid_highest++;
	return id;
}

/* Given a thread ID, locates the thread structure */
kthread_t *thd_by_tid(tid_t tid) {
	kthread_t *np;

	LIST_FOREACH(np, &thd_list, t_list) {
		if (np->tid == tid)
			return np;
	}

	return NULL;
}


/*****************************************************************************/
/* Thread support routines: idle task and start task wrapper */

/* An idle function. This function literally does nothing but loop
   forever. It's meant to be used for an idle task. */
static void thd_idle_task(void *param) {
	/* Uncomment these if you want some debug for deadlocking */
/*	int old = irq_disable();
#ifndef NDEBUG
	thd_pslist();
	printf("Inside idle task now\n");
#endif
	irq_restore(old); */
	for (;;) {
		arch_sleep();	/* We can safely enter sleep mode here */
	}
}

/* Thread execution wrapper; when the thd_create function below
   adds a new thread to the thread chain, this function is the one
   that gets called in the new context. */
void thd_birth(void (*routine)(void *param), void *param) {
	/* Call the thread function */
	routine(param);

	/* Die */
	thd_exit();
}

/* Terminate the current thread */
void thd_exit() {
	/* Call Dr. Kevorkian; after this executes we could be killed
	   at any time. */
	thd_current->state = STATE_ZOMBIE;

	/* Manually reschedule */
	thd_block_now(&thd_current->context);

	/* not reached */
	abort();
}


/*****************************************************************************/
/* Thread creation and deletion */

/* Enqueue a process in the runnable queue; adds it right after the
   process group of the same priority (front_of_line==0) or
   right before the process group of the same priority (front_of_line!=0). 
   See thd_schedule for why this is helpful. */
void thd_add_to_runnable(kthread_t *t, int front_of_line) {
	kthread_t	*i;
	int		done;

	if (t->flags & THD_QUEUED)
		return;

	done = 0;

	if (!front_of_line) {
		/* Look for a thread of lower priority and insert
	   	  before it. If there is nothing on the run queue, we'll 
	   	  fall through to the bottom. */
		TAILQ_FOREACH(i, &run_queue, thdq) {
			if (i->prio > t->prio) {
				TAILQ_INSERT_BEFORE(i, t, thdq);
				done = 1;
				break;
			}
		}
	} else {
		/* Look for a thread of the same or lower priority and
		   insert before it. If there is nothing on the run queue,
		   we'll fall through to the bottom. */
		TAILQ_FOREACH(i, &run_queue, thdq) {
			if (i->prio >= t->prio) {
				TAILQ_INSERT_BEFORE(i, t, thdq);
				done = 1;
				break;
			}
		}
	}

	/* Didn't find one, put it at the end */
	if (!done)
		TAILQ_INSERT_TAIL(&run_queue, t, thdq);

	t->flags |= THD_QUEUED;
}

/* Removes a thread from the runnable queue, if it's there. */
int thd_remove_from_runnable(kthread_t *thd) {
	if (!(thd->flags & THD_QUEUED)) return 0;
	thd->flags &= ~THD_QUEUED;
	TAILQ_REMOVE(&run_queue, thd, thdq);
	return 0;
}

/* New thread function; given a routine address, it will create a
   new kernel thread with a default stack. When the routine
   returns, the thread will exit. Returns the new thread struct. */
kthread_t *thd_create(void (*routine)(void *param), void *param) {
	kthread_t	*nt;
	tid_t		tid;
	uint32		params[2];
	int		oldirq = 0;

	nt = NULL;

	oldirq = irq_disable();

	/* Get a new thread id */
	tid = thd_next_free();
	if (tid >= 0) {
		/* Create a new thread structure */
		nt = malloc(sizeof(kthread_t));
		if (nt != NULL) {
			/* Clear out potentially unused stuff */
			memset(nt, 0, sizeof(kthread_t));
		
			/* Create a new thread stack */
			nt->stack = (uint32*)malloc(THD_STACK_SIZE);
			nt->stack_size = THD_STACK_SIZE;
	
			/* Populate the context */
			params[0] = (uint32)routine;
			params[1] = (uint32)param;
			irq_create_context(&nt->context,
				((uint32)nt->stack)+nt->stack_size,
				(uint32)thd_birth, params, 0);

			nt->tid = tid;
			nt->prio = PRIO_DEFAULT;
			nt->flags = THD_DEFAULTS;
			nt->state = STATE_READY;
			strcpy(nt->label, "[un-named kernel thread]");
			if (thd_current)
				strcpy(nt->pwd, thd_current->pwd);
			else
				strcpy(nt->pwd, "/");

			_REENT_INIT_PTR((&(nt->thd_reent)));

			/* Insert it into the thread list */
			LIST_INSERT_HEAD(&thd_list, nt, t_list);

			/* Schedule it */
			thd_add_to_runnable(nt, 0);
		}
	}

	irq_restore(oldirq);
	return nt;
}

/* Given a thread id, this function removes the thread from
   the execution chain. */
int thd_destroy(kthread_t *thd) {
	int oldirq = 0;

	/* Make sure there are no ints */
	oldirq = irq_disable();

	/* If any threads were waiting on this one, then go ahead
	   and unblock them. */
	genwait_wake_all(thd);

	/* De-schedule the thread if it's scheduled and free the
	   thread structure */
	thd_remove_from_runnable(thd);
	LIST_REMOVE(thd, t_list);

	/* Free its stack */
	free(thd->stack);

	/* Free the thread */
	free(thd);

	/* Put ints back the way they were */
	irq_restore(oldirq);

	return 0;
}

/*****************************************************************************/
/* Thread attribute functions */

/* Set a thread's priority */
int thd_set_prio(kthread_t *thd, prio_t prio) {
	/* Set the new priority */
	thd->prio = prio;
	return 0;
}

/*****************************************************************************/
/* Scheduling routines */

/* Thread scheduler; this function will find a new thread to run when a 
   context switch is requested. No work is done in here except to change
   out the thd_current variable contents. Assumed that we are in an 
   interrupt context.

   In the normal operation mode, the current thread is pushed back onto
   the run queue at the end of its priority group. This implements the
   standard round robin scheduling within priority groups. If you set the
   front_of_line parameter to non-zero, then this behavior is modified:
   the current thread is pushed onto the run queue at the _front_ of its
   priority group. The effect is that no context switching is done, but
   priority groups are re-checked. This is useful when returning from an
   IRQ after doing something like a sem_signal, where you'd ideally like
   to make sure the priorities are all straight before returning, but you
   don't want a full context switch inside the same priority group.
 */
void thd_schedule(int front_of_line, uint64 now) {
	int		dontenq, count;
	kthread_t	*thd, *tnext;

	if (now == 0)
		now = timer_ms_gettime64();

	/* We won't re-enqueue the current thread if it's NULL (i.e., the
	   thread blocked itself somewhere) or if it's a zombie (below) */
	dontenq = thd_current == NULL ? 1 : 0;
	
	/* Destroy all threads marked STATE_ZOMBIE */
	thd = LIST_FIRST(&thd_list);
	count = 0;
	while (thd != NULL) {
		tnext = LIST_NEXT(thd, t_list);

		if (thd->state == STATE_ZOMBIE) {
			if (thd == thd_current)
				dontenq = 1;
			thd_destroy(thd);
		}

		thd = tnext;
		count++;
	}

	/* If there's only one thread left, it's the idle task: exit the OS */
	if (count == 1) {
		dbgio_printf("\nthd_schedule: idle task is the only thing left; exiting\n");
		arch_exit();
	}

	/* Re-queue the last "current" thread onto the run queue if
	   it didn't die */
	if (!dontenq && thd_current->state == STATE_RUNNING) {
		thd_current->state = STATE_READY;
		thd_add_to_runnable(thd_current, front_of_line);
	}

	/* Look for timed out waits */
	genwait_check_timeouts(now);

	/* Search downwards through the run queue for a runnable thread; if
	   we don't find a normal runnable thread, the idle process will
	   always be there at the bottom. */
	TAILQ_FOREACH(thd, &run_queue, thdq) {
		/* Is it runnable? If not, keep going */
		if (thd->state == STATE_READY)
			break;
	}

	/* Didn't find one? Big problem here... */
	if (thd == NULL) {
		thd_pslist(printf);
		panic("couldn't find a runnable thread");
	}
		
	/* We should now have a runnable thread, so remove it from the
	   run queue and switch to it. */
	thd_remove_from_runnable(thd);

	thd_current = thd;
	_impure_ptr = &thd->thd_reent;
	thd->state = STATE_RUNNING;

	/* Make sure the thread hasn't underrun its stack */
	if (thd_current->stack && thd_current->stack_size) {
		if ( CONTEXT_SP(thd_current->context) < (ptr_t)(thd_current->stack) ) {
			thd_pslist(printf);
			thd_pslist_queue(printf);
			assert_msg( 0, "Thread stack underrun" );
		}
	}

	irq_set_context(&thd_current->context);
}

/* Temporary priority boosting function: call this from within an interrupt
   to boost the given thread to the front of the queue. This will cause the
   interrupt return to jump back to the new thread instead of the one that
   was executing (unless it was already executing). */
void thd_schedule_next(kthread_t *thd) {
	/* Can't boost a blocked thread */
	if (thd_current->state != STATE_READY)
		return;

	/* Unfortunately we have to take care of this here */
	if (thd_current->state == STATE_ZOMBIE) {
		thd_destroy(thd);
	} else if (thd_current->state == STATE_RUNNING) {
		thd_current->state = STATE_READY;
		thd_add_to_runnable(thd_current, 0);
	}

	thd_remove_from_runnable(thd);
	thd_current = thd;
	_impure_ptr = &thd->thd_reent;
	thd_current->state = STATE_RUNNING;
	irq_set_context(&thd_current->context);
}

#ifdef JIFFYLESS
/* Looks at our queues and determines when we need to wake up next. */
static void thd_schedule_switch(uint64 now) {
	uint64 nexttmr;
	kthread_t * nt;

	assert( thd_current != NULL );

	/* When is the next timer event due? */
	nexttmr = genwait_next_timeout();

	/* Are we in cooperative threading? If so, we never need a context
	   switch timeout. */
	if (thd_mode == THD_MODE_COOP) {
		/* Just wake up for the timer event */
		if (nexttmr != 0) {
			assert( nexttmr != now );
			timer_primary_wakeup(nexttmr - now);
		}
	} else {
		/* We already should have a runnable task in thd_current. Look also
		   at the run queue. Is there anything at the same priority level
		   as the current thread? */
		nt = TAILQ_FIRST(&run_queue);
		if (nt != NULL && nt->prio <= thd_current->prio) {
			/* Is the timeslice time more than the next timer event? If so
			   then don't bother with a pre-emption timer. */
			if ((nexttmr - now) >= thd_next_switch) {
				/* We need a timeslice pre-emption. Make it so! */
				assert( thd_next_switch != now );
				timer_primary_wakeup(thd_next_switch - now);
			} else {
				/* Just wake up for the timer event. */
				assert( nexttmr != now );
				timer_primary_wakeup(nexttmr - now);
			}
		} else {
			/* Just wake up for the next timer event */
			if (nexttmr != 0) {
				assert( nexttmr != now );
				timer_primary_wakeup(nexttmr - now);
			} else {
				thd_next_switch = 0;
			}
		}
	}
}
#endif /* JIFFYLESS */

/* See kos/thread.h for description */
irq_context_t * thd_choose_new() {
	uint64 now = timer_ms_gettime64();

	//printf("thd_choose_new() woken at %d\n", (uint32)now);

	/* Do any re-scheduling */
	thd_schedule(0, now);

#ifdef JIFFYLESS
	/* Increment the context switch counter */
	jiffies++;

	/* Schedule a new next-switch event */
	thd_next_switch = now + 1000/HZ;
	//printf("  resetting thd_next_switch to %d\n", (uint32)thd_next_switch);
	thd_schedule_switch(now);
#endif

	/* Return the new IRQ context back to the caller */
	return &thd_current->context;
}

/*****************************************************************************/

/* Timer function. Check to see if we were woken because of a timeout event
   or because of a pre-empt. For timeouts, just go take care of it and sleep
   again until our next context switch (if any). For pre-empts, re-schedule
   threads, swap out contexts, and sleep. */
static void thd_timer_hnd(irq_context_t *context) {
	/* Get the system time */
	uint64 now = timer_ms_gettime64();

	//printf("timer woke at %d\n", (uint32)now);

#ifdef JIFFYLESS
	/* Did we wake up for a timer event or a context switch? */
	if (thd_next_switch && now >= thd_next_switch) {
		/* Do any re-scheduling. Note that thd_schedule() also checks
		   for timeouts, so if we had those simultaneous with a context
		   switch it'll get caught here. */
		thd_schedule(0, now);

		/* Schedule the next context switch. */
		thd_next_switch = now + 1000/HZ;
		//printf("resetting thd_next_switch to %ld\n", (uint32)thd_next_switch);
	} else {
		/* Just deal with timers */
		genwait_check_timeouts(now);
	}

	/* Request a wakeup at the next time we will need to re-schedule. */
	thd_schedule_switch(now);
#else
	thd_schedule(0, now);
	timer_primary_wakeup(1000/HZ);
#endif
}

/*****************************************************************************/

/* Thread blocking based sleeping; this is the preferred way to
   sleep because it eases the load on the system for the other
   threads. */
void thd_sleep(int ms) {
	if (thd_mode == THD_MODE_NONE) {
		timer_spin_sleep(ms);
		return;
	}

	/* A timeout of zero is the same as thd_pass() and passing zero
	   down to genwait_wait() causes bad juju. */
	if (!ms) {
		thd_pass();
		return;
	}

	/* We can genwait on a non-existant object here with a timeout and
	   have the exact same effect; as a nice bonus, this collapses both
	   sleep cases into a single case, which is nice for scheduling
	   purposes. 0xffffffff definitely doesn't exist as an object, so we'll
	   use that for straight up timeouts. */
	genwait_wait((void *)0xffffffff, "thd_sleep", ms, NULL);
}

/* Manually cause a re-schedule */
void thd_pass() {
	/* Makes no sense inside int */
	if (irq_inside_int()) return;

	/* Pass off control manually */
	thd_block_now(&thd_current->context);
}

/* Wait for a thread to exit */
int thd_wait(kthread_t * thd) {
	int		old, rv;
	kthread_t	* t = NULL;

	/* Can't scan for NULL threads */
	if (thd == NULL)
		return -1;

	if (irq_inside_int()) {
		dbglog(DBG_WARNING, "thd_wait(%p) called inside an interrupt!\n", thd);
		return -1;
	}

	old = irq_disable();
	
	/* Search the thread list and make sure that this thread hasn't
	   already died and been deallocated. */
	LIST_FOREACH(t, &thd_list, t_list) {
		if (t == thd)
			break;
	}

	/* Did we find anything? */
	if (t != thd) {
		rv = -2;
	} else {
		/* Wait for the target thread to die */
		genwait_wait(thd, "thd_wait", 0, NULL);

		/* Ok, we're all clear */
		rv = 0;
	}

	irq_restore(old);
	return rv;
}

/*****************************************************************************/
/* Retrive / set thread label */                     
const char *thd_get_label(kthread_t *thd) {
	return thd->label;
}

void thd_set_label(kthread_t *thd, const char *label) {
	strncpy(thd->label, label, sizeof(thd->label) - 1);
}

/* Find the current thread */
kthread_t *thd_get_current() {
	return thd_current;
}

/* Retrieve / set thread pwd */   
const char *thd_get_pwd(kthread_t *thd) {
	return thd->pwd;
}

void thd_set_pwd(kthread_t *thd, const char *pwd) {
	strncpy(thd->pwd, pwd, sizeof(thd->pwd) - 1);
}

int * thd_get_errno(kthread_t * thd) {
	return &thd->thd_errno;
}

struct _reent * thd_get_reent(kthread_t *thd) {
	return &thd->thd_reent;
}

/*****************************************************************************/

/* Change threading modes */
int thd_set_mode(int mode) {
	int old = thd_mode;

	/* Nothing to change? */
	if (thd_mode == mode)
		return thd_mode;

	if (thd_mode == THD_MODE_COOP) {
		/* Schedule our first pre-emption wakeup */
#ifdef JIFFYLESS
		thd_next_switch = timer_ms_gettime64() + 1000/HZ;
#endif
		timer_primary_wakeup(1000/HZ);
	} else {
#ifdef JIFFYLESS
		/* Don't do any more pre-empt wakeups */
		thd_next_switch = 0;
#endif
	}

	thd_mode = mode;

	return old;
}

/*****************************************************************************/
/* Init/shutdown */

/* Init */
int thd_init(int mode) {
	kthread_t *idle, *kern;

	/* Make sure we're not already running */
	if (thd_mode != THD_MODE_NONE)
		return -1;

	/* Setup our mode as appropriate */
	thd_mode = mode;

	/* Initialize handle counters */
	tid_highest = 1;

	/* Initialize the thread list */
	LIST_INIT(&thd_list);

	/* Initialize the run queue */
	TAILQ_INIT(&run_queue);

	/* Start off with no "current" thread */
	thd_current = NULL;

	/* Setup a kernel task for the currently running "main" thread */
	kern = thd_create(NULL, NULL);
	strcpy(kern->label, "[kernel]");
	kern->state = STATE_RUNNING;

	/* De-scehdule the thread (it's STATE_RUNNING) */
	thd_remove_from_runnable(kern);
	
	/* Setup an idle task that is always ready to run, in case everyone
	   else is blocked on something. */
	idle = thd_create(thd_idle_task, NULL);
	strcpy(idle->label, "[idle]");
	thd_set_prio(idle, PRIO_MAX);
	idle->state = STATE_READY;

	/* Main thread -- the kern thread */
	thd_current = kern;
	irq_set_context(&kern->context);

	/* Re-initialize jiffy counter */
	jiffies = 0;

	/* Initialize thread sync primitives */
	genwait_init();
	sem_init();
	cond_init();

	/* Setup our pre-emption handler */
	timer_primary_set_callback(thd_timer_hnd);

	/* If we're in pre-emptive mode, then schedule the first context switch */
	if (thd_mode == THD_MODE_PREEMPT) {
		/* Schedule our first wakeup */
#ifdef JIFFYLESS
		thd_next_switch = timer_ms_gettime64() + 1000/HZ;
#endif
		timer_primary_wakeup(1000/HZ);

		printf("thd: pre-emption enabled, HZ=%d\n", HZ);
	} else
		printf("thd: pre-emption disabled\n");

	return 0;
}

/* Shutdown */
void thd_shutdown() {
	kthread_t *n1, *n2;

	/* Disable pre-emption, if neccessary */
	if (thd_mode == THD_MODE_PREEMPT) {
		timer_primary_set_callback(NULL);
	}

	/* Kill remaining live threads */
	n1 = LIST_FIRST(&thd_list);
	while (n1 != NULL) {
		n2 = LIST_NEXT(n1, t_list);
		free(n1->stack);
		free(n1);
		n1 = n2;
	}

	/* Shutdown thread sync primitives */
	sem_shutdown();
	cond_shutdown();
	genwait_shutdown();

	/* Not running */
	thd_mode = THD_MODE_NONE;

	// XXX _impure_ptr is borked
}


