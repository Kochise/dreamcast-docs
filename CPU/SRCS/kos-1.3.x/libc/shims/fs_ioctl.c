/* KallistiOS ##version##

   fs_ioctl.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_ioctl.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

int fs_ioctl(file_t hnd, void *data, size_t size) {
	return _fs_ioctl(_local_process, hnd, data, size);
}

