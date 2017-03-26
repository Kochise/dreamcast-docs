/* KallistiOS ##version##

   newlib_wait.c
   Copyright (C)2004 Dan Potter

*/

#include <sys/reent.h>
#include <errno.h>

int _wait_r(struct _reent * reent, int * status) {
	reent->_errno = EAGAIN;
	return -1;
}
