/* KallistiOS ##version##

   fs_complete.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_complete.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

int fs_complete(file_t fd, ssize_t * rv) {
	return _fs_complete(_local_process, fd, rv);
}
