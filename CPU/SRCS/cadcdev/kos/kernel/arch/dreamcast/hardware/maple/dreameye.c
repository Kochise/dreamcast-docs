/* KallistiOS ##version##

   dreameye.c
   Copyright (C) 2005 Lawrence Sebald
*/

#include <dc/maple.h>
#include <dc/maple/dreameye.h>

static void dreameye_periodic(maple_driver_t *drv) {
}

static int dreameye_attach(maple_driver_t *drv, maple_device_t *dev) {
	dev->status_valid = 1;
	return 0;
}

static void dreameye_detach(maple_driver_t *drv, maple_device_t *dev) {
}

/* Device Driver Struct */
static maple_driver_t dreameye_drv = {
	functions:	MAPLE_FUNC_CAMERA,
	name:		"Dreameye (Camera)",
	periodic:	dreameye_periodic,
	attach:		dreameye_attach,
	detach:		dreameye_detach
};

/* Add the DreamEye to the driver chain */
int dreameye_init() {
	return maple_driver_reg(&dreameye_drv);
}

void dreameye_shutdown() {
	maple_driver_unreg(&dreameye_drv);
}
