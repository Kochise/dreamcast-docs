/* KallistiOS ##version##

   dc/maple/mouse.h
   (C)2000-2002 Jordan DeLong and Dan Potter

   $Id: mouse.h,v 1.3 2002/05/24 06:47:26 bardtx Exp $

*/

#ifndef __DC_MAPLE_MOUSE_H
#define __DC_MAPLE_MOUSE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* mouse defines */
#define MOUSE_RIGHTBUTTON	(1<<1)
#define MOUSE_LEFTBUTTON	(1<<2)
#define MOUSE_SIDEBUTTON	(1<<3)

#define MOUSE_DELTA_CENTER      0x200

/* Raw mouse condition structure */
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

/* More civilized mouse structure. There are several significant
   differences in data interpretation between the "cooked" and
   the old "raw" structs:

   - buttons are zero-based: a 1-bit means the button is PRESSED
   - no dummy values

   Note that this is what maple_dev_status() will return.
 */
typedef struct {
	uint32	buttons;
	int	dx, dy, dz;
} mouse_state_t;

/* Old maple interface */
int mouse_get_cond(uint8 addr, mouse_cond_t *cond);

/* Init / Shutdown */
int	mouse_init();
void	mouse_shutdown();

__END_DECLS

#endif	/* __DC_MAPLE_MOUSE_H */

