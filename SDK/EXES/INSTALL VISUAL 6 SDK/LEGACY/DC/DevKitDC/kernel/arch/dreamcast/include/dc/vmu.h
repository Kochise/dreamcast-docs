/* KallistiOS 1.1.6

   dc/vmu.h
   (C)2000-2001 Jordan DeLong

   $Id: vmu.h,v 1.2 2002/01/05 07:33:51 bardtx Exp $

*/

#ifndef __DC_VMU_H
#define __DC_VMU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

int vmu_draw_lcd(uint8 addr, void *bitmap);
int vmu_block_read(uint8 addr, uint16 blocknum, uint8 *buffer);
int vmu_block_write(uint8 addr, uint16 blocknum, uint8 *buffer);

__END_DECLS

#endif	/* __DC_VMU_H */

