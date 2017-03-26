/* KallistiOS ##version##

   hardware.c
   Copyright (C)2000,2001,2003 Dan Potter
*/

#include <arch/arch.h>
#include <dc/asic.h>
#include <dc/vblank.h>

CVSID("$Id: hardware.c,v 1.11 2003/07/31 00:42:00 bardtx Exp $");

static int initted = 0;

int hardware_sys_init() {
	/* Setup ASIC stuff */
	asic_init();

	/* VBlank multiplexer */
	vblank_init();

	initted = 1;

	return 0;
}

void hardware_shutdown() {
	vblank_shutdown();
	asic_shutdown();
}


