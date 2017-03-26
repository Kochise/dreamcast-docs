/* KallistiOS ##version##

   newlib_unlink.c
   Copyright (C)2004 Dan Potter

*/

#include <kos/fs.h>

int _unlink_r(void * reent, const char * fn) {
	return fs_unlink(fn);
}
