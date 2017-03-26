/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: sys_arch.c,v 1.2 2002/03/24 08:25:48 bardtx Exp $
 */

/* Some small changes to port to KOS by Dan Potter */

#include "lwip/debug.h"

#include <kos.h>
#include <assert.h>

#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"

#define UMAX(a, b)      ((a) > (b) ? (a) : (b))

static struct sys_thread *threads = NULL;

struct sys_mbox_msg {
  struct sys_mbox_msg *next;
  void *msg;
};

#define SYS_MBOX_SIZE 100

struct sys_mbox {
  u16_t first, last;
  void *msgs[SYS_MBOX_SIZE];
  sys_sem_t mail;
  sys_sem_t mutex;
};

struct sys_thread {
  struct sys_thread *next;
  struct sys_timeouts timeouts;
  kthread_t * thd;
};

struct sys_thread thread_default;

static sys_sem_t sys_sem_new_(u8_t count);
static void sys_sem_free_(sys_sem_t sem);

/*-----------------------------------------------------------------------------------*/
static struct sys_thread *
current_thread(void)
{
  struct sys_thread *st;
  kthread_t * pt;
  pt = thd_get_current();
  /*  DEBUGF("sys: current_thread: pt %d\n", pt);*/
  for(st = threads; st != NULL; st = st->next) {
    if (st->thd == pt)
      return st;
  }

  return &thread_default;
}
/*-----------------------------------------------------------------------------------*/
struct thread_start_param {
  struct sys_thread *thread;
  void (* function)(void *);
  void *arg;
};

static void
thread_start(void *arg)
{
  struct thread_start_param *tp = arg;
  tp->thread->thd = thd_get_current();
  tp->function(tp->arg);
  free(tp);
}

void
sys_thread_new(void (* function)(void *arg), void *arg)
{
  struct sys_thread *thread;
  struct thread_start_param *thread_param;

  thread = malloc(sizeof(struct sys_thread));
  thread->next = threads;
  thread->timeouts.next = NULL;
  thread->thd = NULL;
  threads = thread;

  thread_param = malloc(sizeof(struct thread_start_param));
  
  thread_param->function = function;
  thread_param->arg = arg;
  thread_param->thread = thread;

  thread->thd = thd_create(thread_start, thread_param);
  assert_msg(thread->thd != NULL, "Couldn't create a new lwIP thread");
}

void sys_thread_init() {
	assert( threads == NULL );

	/* Enter the current thread into the pool */
	/* threads = malloc(sizeof(struct sys_thread));
	threads->next = NULL;
	threads->timeouts.next = NULL;
	threads->thd = thd_get_current(); */

	/* Setup a default catch-all thread */
	thread_default.next = NULL;
	thread_default.timeouts.next = NULL;
	thread_default.thd = NULL;
}

/*-----------------------------------------------------------------------------------*/
struct sys_mbox *
sys_mbox_new()
{
  struct sys_mbox *mbox;

  mbox = malloc(sizeof(struct sys_mbox));
  mbox->first = mbox->last = 0;
  mbox->mail = sys_sem_new_(0);
  mbox->mutex = sys_sem_new_(1);
  
#ifdef SYS_STATS
  stats.sys.mbox.used++;
  if(stats.sys.mbox.used > stats.sys.mbox.max) {
    stats.sys.mbox.max = stats.sys.mbox.used;
  }
#endif /* SYS_STATS */
  
  return mbox;
}
/*-----------------------------------------------------------------------------------*/
void
sys_mbox_free(struct sys_mbox *mbox)
{
  if(mbox != SYS_MBOX_NULL) {
#ifdef SYS_STATS
    stats.sys.mbox.used--;
#endif /* SYS_STATS */
    sys_sem_wait(mbox->mutex);
    
    sys_sem_free_(mbox->mail);
    sys_sem_free_(mbox->mutex);
    mbox->mail = mbox->mutex = NULL;
    /*  DEBUGF("sys_mbox_free: mbox 0x%lx\n", mbox);*/
    free(mbox);
  }
}
/*-----------------------------------------------------------------------------------*/
void
sys_mbox_post(struct sys_mbox *mbox, void *msg)
{
  u8_t first;
  
  sys_sem_wait(mbox->mutex);
  
  DEBUGF(SYS_DEBUG, ("sys_mbox_post: mbox %p msg %p\n", mbox, msg));

  mbox->msgs[mbox->last] = msg;

  if(mbox->last == mbox->first) {
    first = 1;
  } else {
    first = 0;
  }
  
  mbox->last++;
  if(mbox->last == SYS_MBOX_SIZE) {
    mbox->last = 0;
  }

  if(first) {
    sys_sem_signal(mbox->mail);
  }
  
  sys_sem_signal(mbox->mutex);

}
/*-----------------------------------------------------------------------------------*/
u16_t
sys_arch_mbox_fetch(struct sys_mbox *mbox, void **msg, u16_t timeout)
{
  u16_t time = 1;
  
  /* The mutex lock is quick so we don't bother with the timeout
     stuff here. */
  sys_arch_sem_wait(mbox->mutex, 0);
  
  while(mbox->first == mbox->last) {
    sys_sem_signal(mbox->mutex);
    
    /* We block while waiting for a mail to arrive in the mailbox. We
       must be prepared to timeout. */
    if(timeout != 0) {
      time = sys_arch_sem_wait(mbox->mail, timeout);
      
      /* If time == 0, the sem_wait timed out, and we return 0. */
      if(time == 0) {
	return 0;
      }
    } else {
      sys_arch_sem_wait(mbox->mail, 0);
    }
    
    sys_arch_sem_wait(mbox->mutex, 0);
  }
  
  if(msg != NULL) {
    DEBUGF(SYS_DEBUG, ("sys_mbox_fetch: mbox %p msg %p\n", mbox, *msg));
    *msg = mbox->msgs[mbox->first];
  }
  
  mbox->first++;
  if(mbox->first == SYS_MBOX_SIZE) {
    mbox->first = 0;
  }    
  
  sys_sem_signal(mbox->mutex);
  
  return time;
}
/*-----------------------------------------------------------------------------------*/
sys_sem_t
sys_sem_new(u8_t count)
{
#ifdef SYS_STATS
  stats.sys.sem.used++;
  if(stats.sys.sem.used > stats.sys.sem.max) {
    stats.sys.sem.max = stats.sys.sem.used;
  }
#endif /* SYS_STATS */
  return sys_sem_new_(count);
}
/*-----------------------------------------------------------------------------------*/
static sys_sem_t
sys_sem_new_(u8_t count)
{
  return sem_create(count);
}
/*-----------------------------------------------------------------------------------*/
u16_t
sys_arch_sem_wait(sys_sem_t sem, u16_t timeout)
{
  u16_t time = 1;
  if (sem_wait_timed(sem, timeout) >= 0)
  	time = 1;
  else
  	time = 0;
  return time;
}
/*-----------------------------------------------------------------------------------*/
void
sys_sem_signal(sys_sem_t sem)
{
  sem_signal(sem);
}
/*-----------------------------------------------------------------------------------*/
void
sys_sem_free(sys_sem_t sem)
{
  if(sem != SYS_SEM_NULL) {
#ifdef SYS_STATS
    stats.sys.sem.used--;
#endif /* SYS_STATS */
    sys_sem_free_(sem);
  } 
}
/*-----------------------------------------------------------------------------------*/
static void
sys_sem_free_(sys_sem_t sem)
{
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
void
sys_init()
{
	sys_thread_init();
}
/*-----------------------------------------------------------------------------------*/
struct sys_timeouts *
sys_arch_timeouts(void)
{
  struct sys_thread *thread;
  
  thread = current_thread();
  return &thread->timeouts;  
}
/*-----------------------------------------------------------------------------------*/
