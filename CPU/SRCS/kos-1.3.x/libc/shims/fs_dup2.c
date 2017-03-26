/* KallistiOS ##version##

   fs_dup2.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_dup2.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

file_t fs_dup2(file_t oldfd, file_t newfd) {
	return _fs_dup2(_local_process, oldfd, newfd);
}

