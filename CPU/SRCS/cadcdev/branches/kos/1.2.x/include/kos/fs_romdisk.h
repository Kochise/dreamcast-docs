/* KallistiOS ##version##

   kos/fs_romdisk.h
   (c)2001 Dan Potter

   $Id: fs_romdisk.h,v 1.4 2002/08/13 04:54:22 bardtx Exp $
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

/* Mount a romdisk image; must have called fs_romdisk_init() earlier.
   Also note that we do _not_ take ownership of the image data if
   own_buffer is 0, so if you malloc'd that buffer, you must
   also free it after the unmount. If own_buffer is non-zero, then
   we free the buffer when it is unmounted. */
int fs_romdisk_mount(const char * mountpoint, const uint8 *img, int own_buffer);

/* Unmount a romdisk image */
int fs_romdisk_unmount(const char * mountpoint);

__END_DECLS

#endif	/* __KOS_FS_ROMDISK_H */

