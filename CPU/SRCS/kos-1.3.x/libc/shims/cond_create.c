/* KallistiOS ##version##

   cond_create.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/cond.h>
#include <sys/process.h>

CVSID("$Id: cond_create.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

condvar_t *cond_create() {
	return _cond_create(_local_process);
}
