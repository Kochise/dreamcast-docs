/* KallistiOS ##version##

   fs_readdir.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs.h>
#include <sys/process.h>

CVSID("$Id: fs_readdir.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

dirent_t* fs_readdir(file_t hnd) {
	return _fs_readdir(_local_process, hnd);
}

