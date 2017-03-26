/* KallistiOS ##version##

   network.c
   (c)2002 Dan Potter
*/

#include <kos.h>

/*

This is a simple network test example. All it does is bring up the
networking system and wait for a bit to let you have a chance to
ping it, etc. Note that this program is totally portable as long
as your KOS platform has networking capabilities, but I'm leaving
it in "dreamcast" for now.
 
*/

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_NET);

int main(int argc, char **argv) {
	/* Wait for a bit so the user can ping, etc */
	usleep(10 * 1000 * 1000);

	return 0;
}


