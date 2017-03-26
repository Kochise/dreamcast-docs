/* KallistiOS ##version##

   sbios_init_shutdown.c
   Copyright (c)2002 Dan Potter
*/

#include <ps2/sbios.h>

/* SBIOS is the PS2RTE runtime kernel that resides in the lower 64k of
   RAM after it boots an image. The SBIOS handles all interactions with
   the IOP, which includes:

     - Hard disk(?)
     - Memory card
     - CD/DVD drive
     - Firewire
     - PS2 pads (controllers)
     - Audio output

   And probably other stuff I don't know about yet. To call into the
   SBIOS, we have to dig into the first of it for the boot info, and
   get an entry proc address ("sbios_call"). This will be used
   for all interactions with the SBIOS. */

CVSID("$Id: sbios_init_shutdown.c,v 1.2 2002/11/06 08:40:08 bardtx Exp $");

int sbios_init() {
	return -1;
}

void sbios_shutdown() {
}
