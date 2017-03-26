/* KallistiOS ##version##

   newlib_open.c
   Copyright (C)2004 Dan Potter

*/

#include <kos/fs.h>
#include <assert.h>
#include <stdio.h>

int _open_r(void * reent, const char * f, int flags, int mode) {
	return fs_open(f, flags);
}
