/* KallistiOS ##version##

   pvr_palette.c
   (C)2002 Dan Potter

 */

#include <assert.h>
#include <dc/pvr.h>
#include "pvr_internal.h"

/*
   In addition to its 16-bit truecolor modes, the PVR also supports some
   nice paletted modes. These aren't useful for super high quality images
   most of the time, but they can be useful for doing some interesting
   special effects, like the old cheap "worm hole".
*/

CVSID("$Id: pvr_palette.c,v 1.2 2002/07/17 02:31:44 bardtx Exp $");

/* Set the palette format */
void pvr_set_pal_format(int fmt) {
	PVR_SET(PVR_PALETTE_CFG, fmt);
}

