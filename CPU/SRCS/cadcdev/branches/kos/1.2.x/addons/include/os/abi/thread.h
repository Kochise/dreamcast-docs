/* KallistiOS ##version##

   os/abi/thread.h
   (c)2000-2001 Dan Potter

   $Id: thread.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __OS_ABI_THREAD_H
#define __OS_ABI_THREAD_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>
#include <kos/thread.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	kthread_t *	(*create)(void (*routine)(void *param), void *param);
	int		(*destroy)(kthread_t *thd);
	void		(*exit)();
	void		(*pass)();
	void		(*sleep_jiffies)(int jif);
	void		(*sleep)(int ms);
	uint32		(*jiffies)();
	/* void		(*event_reset)(volatile thd_event_t *event);
	void		(*event_set)(volatile thd_event_t *event);
	void		(*event_wait)(volatile thd_event_t *event);
	int		(*set_prio)(tid_t tid, prio_t prio);
	tid_t		(*get_tid)();
	uint32		blank0[32-14];
	
	sem_t		(*sem_alloc)(int count);
	int		(*sem_free)(sem_t sem);
	int		(*sem_wait)(sem_t sem);
	int		(*sem_signal)(sem_t sem);
	int		(*sem_count)(sem_t sem);
	uint32		blank1[8-5];

	mbox_t		(*mbox_alloc)();
	int		(*mbox_free)(mbox_t mbox);
	int		(*mbox_post)(mbox_t mb, int len, void *data);
	int		(*mbox_fetch)(mbox_t mb, int *len, void **data);
	int		(*mbox_count)(mbox_t mb); */
} abi_thread_t;

__END_DECLS

#endif	/* __OS_ABI_THREAD_H */

