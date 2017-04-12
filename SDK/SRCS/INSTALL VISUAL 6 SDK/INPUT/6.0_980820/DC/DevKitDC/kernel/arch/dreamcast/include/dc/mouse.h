/* KallistiOS 1.1.6

   dc/mouse.h
   (C)2000-2001 Jordan DeLong

   $Id: mouse.h,v 1.2 2002/01/05 07:33:51 bardtx Exp $

*/

#ifndef __DC_MOUSE_H
#define __DC_MOUSE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* mouse defines */
#define MOUSE_RIGHTBUTTON	(1<<1)
#define MOUSE_LEFTBUTTON	(1<<2)
#define MOUSE_SIDEBUTTON	(1<<3)

#define MOUSE_DELTA_CENTER      0x200

/* mouse condition structure */
typedef struct {
	uint16 buttons;
	uint16 dummy1;
	int16 dx;
	int16 dy;
	int16 dz;
	uint16 dummy2;
	uint32 dummy3;
	uint32 dummy4;
} mouse_cond_t;

int mouse_get_cond(uint8 addr, mouse_cond_t *cond);

__END_DECLS

#endif	/* __DC_MOUSE_H */

