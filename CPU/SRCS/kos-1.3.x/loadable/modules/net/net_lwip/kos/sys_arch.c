/* KallistiOS ##version##

   sys_arch.c
   Copyright (C)2003 Dan Potter

   Bits and pieces:
   Copyright (C)2001 Swedish Institute of Computer Science
*/
      
#include <stdlib.h>
#include <sys/queue.h>
#include <kos/mutex.h>
#include "arch/sys_arch.h"
#include "lwip/debug.h"
#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"

/* Forward-declare these */
static sys_sem_t sys_sem_new_(u8_t count);
static void sys_sem_free_(sys_sem_t sem);

/***********************************************************************/
/* Thread handling */

/* Each thread has this structure. XXX: Convert to BSD queues. */
struct sys_thread {
	TAILQ_ENTRY(sys_thread)	list;
	struct sys_timeouts	timeouts;
	kthread_t		* thd;
	void			(* function)(void *arg);
	void			* arg;
};

/* Our thread list */
static TAILQ_HEAD(sys_thread_list, sys_thread) threads;
static mutex_t * threads_mutex;

/* This thread will be used as a default when an unknown thread calls back
   into lwIP for something. */
static struct sys_thread thread_default;

/* Return the current lwIP thread */
static struct sys_thread * current_thread(void) {
	struct sys_thread	* st;
	kthread_t		* pt;

	mutex_lock(threads_mutex);

	pt = thd_get_current();
	TAILQ_FOREACH(st, &threads, list) {
		if (st->thd == pt)
			break;
	}
	if (!st)
		st = &thread_default;

	mutex_unlock(threads_mutex);

	return st;
}

/* Threads will start and end here */
static void thread_start(void *arg) {
	struct sys_thread * tp = (struct sys_thread *)arg;

	tp->function(tp->arg);

	mutex_lock(threads_mutex);
	TAILQ_REMOVE(&threads, tp, list);
	mutex_unlock(threads_mutex);

	free(tp);
}

sys_thread_t sys_thread_new(void (* function)(void *arg), void *arg, int prio) {
	struct sys_thread * thread;

	/* XXX: Ignoring prio */

	thread = calloc(1, sizeof(struct sys_thread));
	thread->timeouts.next = NULL;
	thread->thd = NULL;

	mutex_lock(threads_mutex);
	TAILQ_INSERT_TAIL(&threads, thread, list);
	mutex_unlock(threads_mutex);

	thread->function = function;
	thread->arg = arg;

	thread->thd = thd_create(thread_start, thread);
	//thd_set_prio(thread->thd, PRIO_DEFAULT - 1);
	assert_msg(thread->thd != NULL, "Couldn't create a new lwIP thread");

	return thread;
}

void sys_thread_init() {
	/* Setup a default catch-all thread */
	memset(&thread_default, 0, sizeof(thread_default));

	/* Setup thread list */
	TAILQ_INIT(&threads);
	threads_mutex = mutex_create();
}

void sys_thread_shutdown() {
}

/***********************************************************************/
/* Mailboxes. These are a bit more robust and interesting compared to
   the original lwIP sysarch code, because we actually efficiently block
   and wait for open slots when the mbox is full. */

#include <kos/cond.h>

#define SYS_MBOX_SIZE 100

struct sys_mbox {
	// The queue
	int head, tail, cnt;
	void *msgs[SYS_MBOX_SIZE];

	// Access mutex
	mutex_t		* mutex;

	// Signaled whenever mail is available
	condvar_t	* mail;

	// Signaled whenever a message is removed
	condvar_t	* avail;
};


struct sys_mbox * sys_mbox_new() {
	struct sys_mbox *mbox;

	mbox = calloc(1, sizeof(struct sys_mbox));
	mbox->head = mbox->tail = mbox->cnt = 0;

	mbox->mutex = mutex_create();
	mbox->mail = cond_create();
	mbox->avail = cond_create();
  
#ifdef SYS_STATS
	lwip_stats.sys.mbox.used++;
	if(lwip_stats.sys.mbox.used > lwip_stats.sys.mbox.max) {
		lwip_stats.sys.mbox.max = lwip_stats.sys.mbox.used;
	}
#endif /* SYS_STATS */
  
	return mbox;
}

void sys_mbox_free(struct sys_mbox *mbox) {
	if (mbox != SYS_MBOX_NULL) {
#ifdef SYS_STATS
		lwip_stats.sys.mbox.used--;
#endif /* SYS_STATS */
		mutex_lock(mbox->mutex);

		mutex_destroy(mbox->mutex);
		cond_destroy(mbox->mail);
		cond_destroy(mbox->avail);
		mbox->mail = mbox->avail = NULL;
		mbox->mutex = NULL;
		/*  DEBUGF("sys_mbox_free: mbox 0x%lx\n", mbox);*/
		free(mbox);
	}
}

void sys_mbox_post(struct sys_mbox *mbox, void *msg) {
	mutex_lock(mbox->mutex);

	DEBUGF(SYS_DEBUG, ("sys_mbox_post: mbox %p msg %p\n", mbox, msg));

	while (mbox->cnt >= SYS_MBOX_SIZE) {
		cond_wait(mbox->avail, mbox->mutex);
	}

	mbox->msgs[mbox->tail] = msg;
	mbox->cnt++;
	mbox->tail = (mbox->tail + 1) % SYS_MBOX_SIZE;

	cond_signal(mbox->mail);
	mutex_unlock(mbox->mutex);
}

// The timeout stuff is a little bit loose, but that's ok...
u32_t sys_arch_mbox_fetch(sys_mbox_t mbox, void **msg, u32_t timeout) {
	u32_t time = 0;
  
	mutex_lock(mbox->mutex);
  
	while (!mbox->cnt) {
		if (timeout) {
			int foo = cond_wait_timed(mbox->mail, mbox->mutex, timeout);
			if (foo < 0) {
				time = SYS_ARCH_TIMEOUT;
				break;
			}
		} else
			cond_wait(mbox->mail, mbox->mutex);
	}

	if (mbox->cnt) {
		if (msg != NULL) {
			*msg = mbox->msgs[mbox->head];
			DEBUGF(SYS_DEBUG, ("sys_mbox_fetch: mbox %p msg %p\n", mbox, *msg));
		}
  
		mbox->head = (mbox->head + 1) % SYS_MBOX_SIZE;
		mbox->cnt--;
		cond_signal(mbox->avail);
	}

	mutex_unlock(mbox->mutex);

	return time;
}

/***********************************************************************/
/* Semaphores */

sys_sem_t sys_sem_new(u8_t count) {
#ifdef SYS_STATS
	lwip_stats.sys.sem.used++;
	if (lwip_stats.sys.sem.used > lwip_stats.sys.sem.max) {
		lwip_stats.sys.sem.max = lwip_stats.sys.sem.used;
	}
#endif /* SYS_STATS */
	return sys_sem_new_(count);
}

static sys_sem_t sys_sem_new_(u8_t count) {
	return sem_create(count);
}

u32_t sys_arch_sem_wait(sys_sem_t sem, u32_t timeout) {
	if (sem_wait_timed(sem, timeout) >= 0)
	  	return 0;
	else
  		return SYS_ARCH_TIMEOUT;
}

void sys_sem_signal(sys_sem_t sem) {
	sem_signal(sem);
}

void sys_sem_free(sys_sem_t sem) {
	if (sem != SYS_SEM_NULL) {
#ifdef SYS_STATS
		lwip_stats.sys.sem.used--;
#endif /* SYS_STATS */
		sys_sem_free_(sem);
	} 
}

static void sys_sem_free_(sys_sem_t sem) {
	sem_destroy(sem);
}

/*-----------------------------------------------------------------------------------*/
/* unsigned long
sys_unix_now()
{
  struct timeval tv;
  struct timezone tz;
  long sec, usec;
  unsigned long msec;
  gettimeofday(&tv, &tz);

  sec = tv.tv_sec - starttime.tv_sec;
  usec = tv.tv_usec - starttime.tv_usec;
  msec = sec * 1000 + usec / 1000;
  return msec;
} */
/*-----------------------------------------------------------------------------------*/

/***********************************************************************/
/* Overall init */
void sys_init() {
	sys_thread_init();
}

/***********************************************************************/
/* Timeout handling */
struct sys_timeouts * sys_arch_timeouts() {
	struct sys_thread *thread;
  
	thread = current_thread();
	return &thread->timeouts;  
}

