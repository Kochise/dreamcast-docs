/* KallistiOS ##version##

   pcx.h
   (c)2000-2002 Dan Potter

   $Id: pcx.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __PCX_PCX_H
#define __PCX_PCX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/img.h>

/* Loads a PCX file into a kos_img_t struct */
int pcx_to_img(const char *fn, kos_img_t *rv);

#ifdef _arch_dreamcast
	/* Loads a PCX file into texture RAM, potentially twiddling it and/or
   	converting it to an alpha mask. */
	int pcx_load_texture(const char *fn, int twiddle, int alpha,
		uint32 *txr, int *w, int *h);
#endif

__END_DECLS

#endif	/* __PCX_H */

