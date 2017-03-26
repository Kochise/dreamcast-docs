/* KallistiOS ##version##

   navi/flash.h
   (c)2002 Dan Potter
   
   $Id: flash.h,v 1.1 2002/05/05 22:17:51 bardtx Exp $
*/

#ifndef __NAVI_FLASH_H
#define __NAVI_FLASH_H

#include <arch/types.h>

/* Return 0 if we successfully detect a compatible device */
int nvflash_detect();

/* Erase a block of flash */
int nvflash_erase_block(uint32 addr);

/* Write a block of data */
int nvflash_write_block(uint32 addr, void * data, uint32 len);

/* Erase the whole flash chip */
int nvflash_erase_all();


#endif	/* __NAVI_FLASH_H */

