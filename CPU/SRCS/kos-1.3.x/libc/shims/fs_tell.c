/* KallistiOS ##version##

   fs_tell.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_tell.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

off_t fs_tell(file_t hnd) {
	return _fs_tell(_local_process, hnd);
}
