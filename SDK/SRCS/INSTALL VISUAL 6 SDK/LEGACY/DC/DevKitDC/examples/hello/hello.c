/* KallistiOS 1.1.6

   hello.c
   (c)2001 Dan Potter
*/

#include <kos.h>

/* You can safely remove this line if you don't use a ROMDISK */
extern uint8 romdisk[];

/* Your program's main entry point */
int main(int argc, char **argv) {
	/* Initialize KOS. This initializes everything in KOS so it's
	   ready go to after this line. You can set individual things to
	   initialize here, or you can enable sets of things with the
	   following special macros:

	   ALL_ENABLE	-- enables EVERYTHING
	   BASIC_ENABLE	-- enables basic kernel services, no platform
	   		   specific goodies like 3D
	   NONE_ENABLE	-- don't do anything

	   Also you may replace "romdisk" with ROMDISK_NONE if you don't
	   want to use a ROMDISK image. */
	kos_init_all(ALL_ENABLE, romdisk);

	/* The requisite line */
	printf("Hello world!\n");

	/* Shut everything down: not technically required, but a good idea
	   to do this... */
	kos_shutdown_all();

	return 0;
}


