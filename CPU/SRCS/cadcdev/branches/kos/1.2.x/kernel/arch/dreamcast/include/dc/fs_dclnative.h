/* KallistiOS ##version##

   kernel/arch/dreamcast/include/dc/fs_dclnative.h
   Copyright (C)2003 Dan Potter

*/

#ifndef __DC_FS_DCLNATIVE_H
#define __DC_FS_DCLNATIVE_H

/* Definitions for the "dcload-ip native" file system. This is like,
   dc-load, but it uses KOS' ethernet drivers to talk directly to the
   installed network adapter. This is far faster and more reliable as
   long as you're not debugging interrupts or something. :) When KOS
   exits, control will be handed back to the resident dcload-ip
   instance. */

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <dc/fs_dcload.h>

/* Printk replacement */
void dclnative_printk(const char *str);

/* File functions */
file_t	dclnative_open(vfs_handler_t * vfs, const char *fn, int mode);
void	dclnative_close(file_t hnd);
ssize_t	dclnative_read(file_t hnd, void *buf, size_t cnt);
off_t	dclnative_seek(file_t hnd, off_t offset, int whence);
off_t	dclnative_tell(file_t hnd);
size_t	dclnative_total(file_t hnd);
dirent_t* dclnative_readdir(file_t hnd);
int     dclnative_rename(vfs_handler_t * vfs, const char *fn1, const char *fn2);
int     dclnative_unlink(vfs_handler_t * vfs, const char *fn);

/* Init/Shutdown */
int fs_dclnative_init();
int fs_dclnative_shutdown();

__END_DECLS

#endif	/* __DC_FS_DCLNATIVE_H */


