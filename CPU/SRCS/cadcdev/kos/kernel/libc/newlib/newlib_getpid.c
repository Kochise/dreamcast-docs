/* KallistiOS ##version##

   newlib_getpid.c
   Copyright (C)2004 Dan Potter

*/

#include <kos/thread.h>
#include <sys/reent.h>

int _getpid_r(struct _reent * re) {
	return thd_current->tid;
}
