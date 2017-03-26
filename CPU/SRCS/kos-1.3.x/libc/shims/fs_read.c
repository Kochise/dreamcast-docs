/* KallistiOS ##version##

   fs_read.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_read.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

ssize_t fs_read(file_t hnd, void *buffer, size_t cnt) {
	return _fs_read(_local_process, hnd, buffer, cnt);
}


