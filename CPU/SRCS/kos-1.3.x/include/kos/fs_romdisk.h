/* KallistiOS ##version##

   kos/fs_romdisk.h
   (c)2001 Dan Potter

   $Id: fs_romdisk.h,v 1.5 2003/07/31 00:38:00 bardtx Exp $
*/

#ifndef __KOS_FS_ROMDISK_H
#define __KOS_FS_ROMDISK_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>

#define MAX_RD_FILES 16

/* Initialize the file system */
int fs_romdisk_init();

/* De-init the file system; also unmounts any mounted images. */
int fs_romdisk_shutdown();

/* NOTE: the mount/unmount are _not_ thread safe as regards doing multiple
   mounts/unmounts in different threads at the same time, and they don't
   check for open files currently either. Caveat emptor! */

/* Mount a romdisk image; must have called fs_romdisk_init() earlier. */
int fs_romdisk_mount(const char * mountpoint, const uint8 *img);

/* Non-public version */
struct kprocess;
int _fs_romdisk_mount(struct kprocess * proc, const char * mountpoint, const uint8 *img);

/* Unmount a romdisk image */
int fs_romdisk_unmount(const char * mountpoint);

/* Unmount all romdisks owned by the named process */
int fs_romdisk_unmount_proc(struct kprocess * proc);

__END_DECLS

#endif	/* __KOS_FS_ROMDISK_H */

