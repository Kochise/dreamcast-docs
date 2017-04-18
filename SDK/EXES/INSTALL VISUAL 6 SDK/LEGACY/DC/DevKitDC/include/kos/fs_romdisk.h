/* KallistiOS 1.1.6

   kos/fs_romdisk.h
   (c)2001 Dan Potter

   $Id: fs_romdisk.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
*/

#ifndef __KOS_FS_ROMDISK_H
#define __KOS_FS_ROMDISK_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>

#define MAX_RD_FILES 8

/* Prototypes */
uint32	romdisk_open(const char *path, int flags);
void	romdisk_close(uint32 fd);
ssize_t	romdisk_read(uint32 fd, void *buf, size_t count);
off_t	romdisk_seek(uint32 fd, off_t offset, int whence);
off_t	romdisk_tell(uint32 fd);
size_t	romdisk_total(uint32 fd);
void*	romdisk_mmap(uint32 fd);

/* Doesn't work yet */
dirent_t *romdisk_readdir(uint32 fd);

int fs_romdisk_init(uint8 *image);
int fs_romdisk_shutdown();

__END_DECLS

#endif	/* __KOS_FS_ROMDISK_H */

