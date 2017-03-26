/* KallistiOS ##version##

   fs_pty_create.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs_pty.h>
#include <sys/process.h>

CVSID("$Id: fs_pty_create.c,v 1.2 2003/07/31 00:46:42 bardtx Exp $");

int fs_pty_create(char * buffer, int maxbuflen, file_t * master_out, file_t * slave_out) {
	return _fs_pty_create(_local_process, buffer, maxbuflen, master_out, slave_out);
}
