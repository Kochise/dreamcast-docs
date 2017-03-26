/* KallistiOS ##version##

   fs_seek.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_seek.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

off_t fs_seek(file_t hnd, off_t offset, int whence) {
	return _fs_seek(_local_process, hnd, offset, whence);
}
