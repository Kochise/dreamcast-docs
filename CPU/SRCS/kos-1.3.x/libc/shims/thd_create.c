/* KallistiOS ##version##

   thd_create.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/thread.h>
#include <sys/process.h>

CVSID("$Id: thd_create.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

/* We need to associate the process with all thread creation calls
   so that we know which process owns which threads. */
kthread_t *thd_create(void (*routine)(void *param), void *param) {
	return _thd_create(_local_process, routine, param);
}

