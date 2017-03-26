/* KallistiOS ##version##

   fs_dup.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_dup.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

file_t fs_dup(file_t oldfd) {
	return _fs_dup(_local_process, oldfd);
}

