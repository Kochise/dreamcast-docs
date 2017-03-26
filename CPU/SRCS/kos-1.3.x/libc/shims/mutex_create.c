/* KallistiOS ##version##

   mutex_create.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/mutex.h>
#include <sys/process.h>

CVSID("$Id: mutex_create.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

mutex_t *mutex_create() {
	return _mutex_create(_local_process);
}
