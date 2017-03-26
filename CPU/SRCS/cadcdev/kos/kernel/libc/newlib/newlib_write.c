/* KallistiOS ##version##

   newlib_write.c
   Copyright (C)2004 Dan Potter

*/

#include <kos/fs.h>

long _write_r(void * reent, int fd, void * buf, size_t cnt) {
	return fs_write(fd, buf, cnt);
}
