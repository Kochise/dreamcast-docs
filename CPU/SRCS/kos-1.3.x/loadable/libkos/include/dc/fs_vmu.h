/* KallistiOS ##version##

   dc/fs_vmu.h
   (c)2000-2001 Jordan DeLong

   $Id: fs_vmu.h,v 1.1 2003/07/31 00:54:03 bardtx Exp $

*/

#ifndef __DC_FS_VMU_H
#define __DC_FS_VMU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/fs.h>

/* Initialization */
int fs_vmu_init();
int fs_vmu_shutdown();

__END_DECLS

#endif	/* __DC_FS_VMU_H */

