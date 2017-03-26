/* KallistiOS ##version##

   dc/fs_vmu.h
   (c)2000-2001 Jordan DeLong

   $Id: fs_vmu.h,v 1.3 2002/08/12 07:25:58 bardtx Exp $

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

