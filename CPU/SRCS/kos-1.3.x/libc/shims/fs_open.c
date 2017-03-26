/* KallistiOS ##version##

   fs_open.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_open.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

/* We need to associate the process with all filesystem calls
   so that we know which process owns which file descriptors. To
   effect this, we hook fs_xxx and call the _real_ xxx as a
   different name. */

file_t fs_open(const char * fn, int mode) {
	return _fs_open(_local_process, fn, mode);
}

