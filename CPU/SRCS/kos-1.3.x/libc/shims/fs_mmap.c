/* KallistiOS ##version##

   fs_maap.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_mmap.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

void* fs_mmap(file_t hnd) {
	return _fs_mmap(_local_process, hnd);
}
