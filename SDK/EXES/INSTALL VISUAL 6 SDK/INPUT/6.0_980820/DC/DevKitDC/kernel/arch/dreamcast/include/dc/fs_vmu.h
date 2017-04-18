/* KallistiOS 1.1.6

   dc/fs_vmu.h
   (c)2000-2001 Jordan DeLong

   $Id: fs_vmu.h,v 1.2 2002/01/05 07:33:51 bardtx Exp $

*/

#ifndef __DC_FS_VMU_H
#define __DC_FS_VMU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/fs.h>

/* File functions */
uint32	vmu_open(const char *path, int mode);
void	vmu_close(uint32 hnd);
off_t	vmu_tell(uint32 hnd);
size_t	vmu_total(uint32 hnd);

/* Initialization */
int fs_vmu_init();
int fs_vmu_shutdown();

__END_DECLS

#endif	/* __DC_FS_VMU_H */

