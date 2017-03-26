/* KallistiOS ##version##

   kos/fs_ramdisk.h
   (c)2002 Dan Potter

   $Id: fs_ramdisk.h,v 1.2 2003/04/24 03:00:02 bardtx Exp $
*/

#ifndef __KOS_FS_RAMDISK_H
#define __KOS_FS_RAMDISK_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>

/* Call this function to have the ramdisk fs take over a piece
   of memory from you and turn it into a ramdisk file. This is handy
   if you have some loaded object but need to use it as a file.
   XXX Doesn't work with multiple ramdisks... do we care? */
int fs_ramdisk_attach(const char * fn, void * obj, size_t size);

/* Does the opposite of attach */
int fs_ramdisk_detach(const char * fn, void ** obj, size_t * size);

int fs_ramdisk_init();
int fs_ramdisk_shutdown();

__END_DECLS

#endif	/* __KOS_FS_RAMDISK_H */

