/* KallistiOS ##version##

   newlib_kill.c
   Copyright (C)2004 Dan Potter

*/

#include <sys/reent.h>
#include <errno.h>

int _kill_r(struct _reent * reent, int pid, int sig) {
	reent->_errno = EINVAL;
	return -1;
}
