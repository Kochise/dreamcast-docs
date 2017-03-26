/* KallistiOS ##version##

   fs_write.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_write.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

ssize_t fs_write(file_t hnd, const void *buffer, size_t cnt) {
	return _fs_write(_local_process, hnd, buffer, cnt);
}
