/* KallistiOS ##version##

   dc/maple/controller.h
   (C)2000-2002 Jordan DeLong, Dan Potter

   $Id: controller.h,v 1.4 2002/05/24 06:47:26 bardtx Exp $

   Thanks to Marcus Comstedt for information on the controller.
*/

#ifndef __DC_MAPLE_CONTROLLER_H
#define __DC_MAPLE_CONTROLLER_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Buttons bitfield defines */
#define CONT_C			(1<<0)
#define CONT_B			(1<<1)
#define CONT_A			(1<<2)
#define CONT_START		(1<<3)
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
#define CONT_DPAD2_RIGHT	(1<<15)

/* Raw controller condition structure */
typedef struct {
	uint16 buttons;			/* buttons bitfield */
	uint8 rtrig;			/* right trigger */
	uint8 ltrig;			/* left trigger */
	uint8 joyx;			/* joystick X */
	uint8 joyy;			/* joystick Y */
	uint8 joy2x;			/* second joystick X */
	uint8 joy2y;			/* second joystick Y */
} cont_cond_t;

/* Our more civilized structure. Note that there are some fairly
   significant differences in value interpretations here between
   this struct and the old one: 

   - "buttons" is zero based: a 1-bit means the button is PRESSED.
   - "joyx", "joyy", "joy2x", and "joy2y" are all zero based: zero
     means they are in the center, negative values are up/left,
     and positive values are down/right.

   Note also that this is the struct you will get back if you call
   maple_dev_status(), NOT a cont_cond_t. However, cont_get_cond() will
   return the old compatible struct for now. */
typedef struct {
	uint32	buttons;		/* Buttons bitfield */
	int	ltrig, rtrig;		/* Triggers */
	int	joyx, joyy;		/* Joystick X/Y */
	int	joy2x, joy2y;		/* Second Joystick X/Y (if applicable) */
} cont_state_t;

/* Init / Shutdown */
int	cont_init();
void	cont_shutdown();

/* Compat function */
int	cont_get_cond(uint8 addr, cont_cond_t *cond);

/* Set a controller callback for a button combo; set addr=0 for any controller */
typedef void (*cont_btn_callback_t)(uint8 addr, uint32 btns);
void	cont_btn_callback(uint8 addr, uint32 btns, cont_btn_callback_t cb);

__END_DECLS

#endif	/* __DC_MAPLE_CONTROLLER_H */

