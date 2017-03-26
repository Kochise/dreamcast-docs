/* KallistiOS ##version##

   dc/maple/vmu.h
   (C)2000-2002 Jordan DeLong and Dan Potter

   $Id: vmu.h,v 1.3 2002/09/04 03:38:42 bardtx Exp $

*/

#ifndef __DC_MAPLE_VMU_H
#define __DC_MAPLE_VMU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

int vmu_draw_lcd(maple_device_t * dev, void *bitmap);
int vmu_block_read(maple_device_t * dev, uint16 blocknum, uint8 *buffer);
int vmu_block_write(maple_device_t * dev, uint16 blocknum, uint8 *buffer);

/* Utility function which sets the icon on all available VMUs 
   from an Xwindows XBM. Imported from libdcutils. */
void vmu_set_icon(const char *vmu_icon);

/* Init / Shutdown */
int vmu_init();
void vmu_shutdown();

__END_DECLS

#endif	/* __DC_MAPLE_VMU_H */

