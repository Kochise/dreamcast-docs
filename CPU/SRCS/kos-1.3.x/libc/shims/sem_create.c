/* KallistiOS ##version##

   sem_create.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/sem.h>
#include <sys/process.h>

CVSID("$Id: sem_create.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

semaphore_t *sem_create(int val) {
	return _sem_create(_local_process, val);
}
