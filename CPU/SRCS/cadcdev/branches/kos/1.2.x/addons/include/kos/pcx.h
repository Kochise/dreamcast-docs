/* KallistiOS ##version##
   
   kos/pcx.h
   (c)2000-2001 Dan Potter

   $Id: pcx.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __KOS_PCX_H
#define __KOS_PCX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* These first two versions are mainly for use with the GBA, and they are
   defined in the "pcx_small" file. They can be used on any architecture of
   course. */
   
/* Flat 15-bit BGR load of the PCX data into whatever buffer -- assumes the
   buffer is the same width as the PCX */
int pcx_load_flat(const char *fn, int *w_out, int *h_out, void *pic_out);

/* Palettized load of the PCX data -- the picture data will go into the
   picture output buffer, and the palette will go into pal_out as
   15-bit BGR data. */
int pcx_load_palette(const char *fn, int *w_out, int *h_out, void *pic_out, void *pal_out);


/* This last version is the larger memory version (for use on DC, etc) */
/* XXX insert definition */

__END_DECLS

#endif	/* __KOS_PCX_H */

