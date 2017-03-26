/* KallistiOS ##version##

   maple_compat.c
   (C)2002 Dan Potter

 */

#include <assert.h>
#include <string.h>
#include <dc/maple.h>
#include <dc/maple/controller.h>
#include <dc/maple/mouse.h>

CVSID("$Id: maple_compat.c,v 1.3 2002/05/24 06:47:26 bardtx Exp $");

/* Utility function used by other compat functions */
int maple_compat_resolve(uint8 addr, maple_device_t **dev, uint32 funcs) {
	int	p, u;

	maple_raddr(addr, &p, &u);
	if (!maple_dev_valid(p, u))
		return MAPLE_EINVALID;
	*dev = &maple_state.ports[p].units[u];
	if (! ((*dev)->info.functions & funcs) )
		return MAPLE_ENOTSUPP;

	return 0;
}

/****************************************************************************/
/* maple.c */

/* Retrieve function code... */
uint32 maple_device_func(int p, int u) {
	maple_device_t	*dev;
	dev = &maple_state.ports[p].units[u];
	if (!dev->valid)
		return 0;
	else
		return dev->info.functions;
}

/* First with a given function code... */
uint8 maple_first_device(int code) {
	int		p, u;
	uint32		func;

	for (p=0; p<MAPLE_PORT_COUNT; p++)
		for (u=0; u<MAPLE_UNIT_COUNT; u++) {
			func = maple_device_func(p, u);
			if (func & code)
				return maple_addr(p, u);
		}
	return 0;
}

/* First controller */
uint8 maple_first_controller() {
	return maple_first_device(MAPLE_FUNC_CONTROLLER);
}

/* First mouse */
uint8 maple_first_mouse() {
	return maple_first_device(MAPLE_FUNC_MOUSE);
}

/* First keyboard */
uint8 maple_first_kb() {
	return maple_first_device(MAPLE_FUNC_KEYBOARD);
}

/* First LCD unit */
uint8 maple_first_lcd() {
	return maple_first_device(MAPLE_FUNC_LCD);
}

/* First VMU */
uint8 maple_first_vmu() {
	return maple_first_device(MAPLE_FUNC_MEMCARD);
}

/****************************************************************************/
/* controller.c */

/* Get the old compatible condition structure for controller on port
   and fill in cond with it, ret -1 on error. */
int cont_get_cond(uint8 addr, cont_cond_t *cond) {
	int		rv;
	maple_device_t	*dev;
	cont_state_t	*stat;

	/* Resolve a status struct */
	assert( addr != 0 );
	rv = maple_compat_resolve(addr, &dev, MAPLE_FUNC_CONTROLLER);
	if (rv < 0)
		return rv;

	stat = maple_dev_status(dev);
	assert(stat != NULL);

	/* Copy out the pieces into an old compat struct */
	cond->buttons = (uint16)(~stat->buttons);
	cond->ltrig = (uint8)(stat->ltrig);
	cond->rtrig = (uint8)(stat->rtrig);
	cond->joyx = (uint8)(stat->joyx+128);
	cond->joyy = (uint8)(stat->joyy+128);
	cond->joy2x = (uint8)(stat->joy2x+128);
	cond->joy2y = (uint8)(stat->joy2y+128);
		
	return 0;
}

/****************************************************************************/
/* mouse.c */

/* get the condition structure for a mouse at address addr. return a
   -1 if an error occurs. */
int mouse_get_cond(uint8 addr, mouse_cond_t *cond) {
	int		rv;
	maple_device_t	*dev;
	mouse_state_t	*stat;

	assert( addr != 0 );
	rv = maple_compat_resolve(addr, &dev, MAPLE_FUNC_MOUSE);
	if (rv < 0)
		return rv;

	stat = maple_dev_status(dev);
	assert(stat != NULL);

	/* Copy out the pieces into an old compat struct */
	cond->buttons = (uint16)(~stat->buttons);
	cond->dummy1 = cond->dummy2 = cond->dummy3 = cond->dummy4 = 0;
	cond->dx = stat->dx;
	cond->dy = stat->dy;
	cond->dz = stat->dz;

	return 0;
}   

