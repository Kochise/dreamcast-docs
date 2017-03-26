/* KallistiOS ##version##

   fs_total.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_total.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

size_t fs_total(file_t hnd) {
	return _fs_total(_local_process, hnd);
}
