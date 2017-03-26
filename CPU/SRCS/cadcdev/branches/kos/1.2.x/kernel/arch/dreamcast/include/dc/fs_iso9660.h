/* KallistiOS ##version##

   dc/fs/iso9660.h
   (c)2000-2001 Dan Potter

   $Id: fs_iso9660.h,v 1.5 2003/04/24 03:14:20 bardtx Exp $
*/

#ifndef __DC_FS_ISO9660_H
#define __DC_FS_ISO9660_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <kos/limits.h>
#include <kos/fs.h>

#define MAX_ISO_FILES 8

/* Call to reset the cache and generally assume that a new disc
   has been (or will be) inserted. This is equivalent to the old
   iso_ioctl() call. */
int iso_reset();

int fs_iso9660_init();
int fs_iso9660_shutdown();

__END_DECLS

#endif	/* __DC_FS_ISO9660_H */

