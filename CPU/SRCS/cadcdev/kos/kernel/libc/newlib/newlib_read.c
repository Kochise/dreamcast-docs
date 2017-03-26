/* KallistiOS ##version##

   newlib_read.c
   Copyright (C)2004 Dan Potter

*/

#include <kos/fs.h>

long _read_r(void * reent, int fd, void * buf, size_t cnt) {
	return fs_read(fd, buf, cnt);
}
