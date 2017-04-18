/* KallistiOS 1.1.6

   dc/controller.h
   (C)2000-2001 Jordan DeLong

   $Id: controller.h,v 1.2 2002/01/05 07:33:51 bardtx Exp $

   Thanks to Marcus Comstedt for information on the controller.
*/

#ifndef __DC_CONTROLLER_H
#define __DC_CONTROLLER_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Buttons bitfield defines */
#define CONT_C			(1<<0)
#define CONT_B			(1<<1)
#define CONT_A			(1<<2)
#define CONT_START			(1<<3)
#define CONT_DPAD_UP		(1<<4)
#define CONT_DPAD_DOWN		(1<<5)
#define CONT_DPAD_LEFT		(1<<6)
#define CONT_DPAD_RIGHT		(1<<7)
#define CONT_Z			(1<<8)
#define CONT_Y			(1<<9)
#define CONT_X			(1<<10)
#define CONT_D			(1<<11)
#define CONT_DPAD2_UP		(1<<12)
#define CONT_DPAD2_DOWN		(1<<13)
#define CONT_DPAD2_LEFT		(1<<14)
#define CONT_DPAD2_RIGHT		(1<<15)

/* controller condition structure */
typedef struct {
	uint16 buttons;			/* buttons bitfield */
	uint8 rtrig;			/* right trigger */
	uint8 ltrig;			/* left trigger */
	uint8 joyx;			/* joystick X */
	uint8 joyy;			/* joystick Y */
	uint8 joy2x;			/* second joystick X */
	uint8 joy2y;			/* second joystick Y */
} cont_cond_t;

int cont_get_cond(uint8 addr, cont_cond_t *cond);

__END_DECLS

#endif	/* __DC_CONTROLLER_H */

