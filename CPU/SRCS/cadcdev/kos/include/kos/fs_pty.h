/* KallistiOS ##version##

   kos/fs_pty.h
   Copyright (C)2003 Dan Potter

   $Id: fs_pty.h,v 1.1 2003/06/19 04:30:23 bardtx Exp $
*/

#ifndef __KOS_FS_PTY_H
#define __KOS_FS_PTY_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>

/* Call this function to create a new pty. The name of the pty is written
   into the user-provided buffer (if non-NULL) and two open file descriptors
   pointing to the two ends of the pty are returned. */
int fs_pty_create(char * buffer, int maxbuflen, file_t * master_out, file_t * slave_out);

int fs_pty_init();
int fs_pty_shutdown();

__END_DECLS

#endif	/* __KOS_FS_PTY_H */

