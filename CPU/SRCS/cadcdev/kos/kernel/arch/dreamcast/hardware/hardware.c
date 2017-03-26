/* KallistiOS ##version##

   hardware.c
   (c)2000-2001 Dan Potter
*/

#include <arch/arch.h>
#include <dc/spu.h>
#include <dc/video.h>
#include <dc/cdrom.h>
#include <dc/asic.h>
#include <dc/maple.h>
#include <dc/net/broadband_adapter.h>
#include <dc/net/lan_adapter.h>
#include <dc/vblank.h>

CVSID("$Id: hardware.c,v 1.9 2003/04/24 03:25:56 bardtx Exp $");

static int initted = 0;

int hardware_sys_init() {
	/* Setup ASIC stuff */
	asic_init();

	/* VBlank multiplexer */
	vblank_init();

	initted = 1;

	return 0;
}

int hardware_periph_init() {
	/* Init sound */
	spu_init();
	spu_dma_init();

	/* Init CD-ROM.. NOTE: NO GD-ROM SUPPORT. ONLY CDs/CDRs. */
	cdrom_init();

	/* Setup maple bus */
	maple_init();

	/* Init video */
	vid_init(DEFAULT_VID_MODE, DEFAULT_PIXEL_MODE);

	/* Setup network (this won't do anything unless we enable netcore) */
	bba_init();
	la_init();

	initted = 2;

	return 0;
}

void hardware_shutdown() {
	switch (initted) {
	case 2:
		la_shutdown();
		bba_shutdown();
		maple_shutdown();
		cdrom_shutdown();
		spu_dma_shutdown();
		spu_shutdown();
		vid_shutdown();
		/* fallthru */
	case 1:
		vblank_shutdown();
		asic_shutdown();
		/* fallthru */
	case 0:
		return;
	}
}


