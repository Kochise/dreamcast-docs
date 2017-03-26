/* KallistiOS ##version##

   fs_close.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_close.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

void fs_close(file_t hnd) {
	return _fs_close(_local_process, hnd);
}

