/* KallistiOS 1.2.0

   libos main.c
   (c)2000-2001 Dan Potter

*/

/* When using KallistiOS in a standalone mode, this file and its peers
   in this directory make up the "main" of the kernel library. */

#include <kos.h>
#include <os/process.h>
#include <os/svcmpx.h>

CVSID("$Id");

/* #include <dc/fs_serconsole.h> */
/* #include <dc/ethernet.h> */

/* A romdisk fs image */
extern uint8 romdisk_boot[];

/* Initialize the VMU apple icon */
#include "vmu_icon.h"
void vmu_icon_init() {
	int x, y, xi, xb;
	uint8 bitmap[48*32/8];
	uint8 addr;

	addr = maple_first_vmu();
	if (!addr) return;
	
	memset(bitmap, 0, 48*32/8);	
	for (y=0; y<32; y++)
		for (x=0; x<48; x++) {
			xi = x / 8;
			xb = 0x80 >> (x % 8);
			if (vmu_icon[(31-y)*48+(47-x)] == '.')
				bitmap[y*(48/8)+xi] |= xb;
		}
	
	vmu_draw_lcd(addr, bitmap);
}

/* In disclaimer.c */
void disclaimer();

int main(int argc, char **argv) {
	/* Uncomment the following line if you want to use the dcload
	   output console. */
	/* fs_dcload_init_console(); */

	/* Initialize all hardware and setup the romdisk */
	arch_init_all(1, 1, romdisk_boot);

	/* Init maple bus */
	dbglog(DBG_DEBUG, "Initializing VMU icon\n");
	vmu_icon_init();

	/* Init svcmpx stuff */
	dbglog(DBG_DEBUG, "Initializing Service Multiplexer\n");
	svcmpx_init();

	/* Init process stuff */
	dbglog(DBG_DEBUG, "Initializing Process Manager\n");
	ps_init();

	/* Try to enable ethernet */
	/* printf("init ethernet\r\n");
	eth_init();

	printf("init tcp/ip\r\n");
	lwip_init(); */

	/* Display a disclaimer screen (disable when you're working on your
	   own stuff, or feel free to re-enable when producing a CD image. */
	/* disclaimer(); */

	/* Start a new loaded process */
	{
		char *argv[] = {
			"/rd/rc.boot",
			"/rd/rave.mp3"
		};
		ps_load_and_exec("/rd/init.klf", 2, argv);
	}

	/* Try to disable ethernet */
	/* printf("shutdown ethernet\r\n");
	eth_shutdown(); */

	/* Shutdown svcmpx */
	svcmpx_shutdown();

	/* Shutdown ps */
	ps_shutdown();

	/* Shutdown everything else */
	arch_shutdown_all();
	return 0;
}



