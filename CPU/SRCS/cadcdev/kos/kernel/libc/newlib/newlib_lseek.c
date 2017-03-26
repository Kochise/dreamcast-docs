/* KallistiOS ##version##

   newlib_lseek.c
   Copyright (C)2004 Dan Potter

*/

#include <kos/fs.h>

off_t _lseek_r(void * reent, int fd, off_t pos, int whence) {
	return fs_seek(fd, pos, whence);
}
