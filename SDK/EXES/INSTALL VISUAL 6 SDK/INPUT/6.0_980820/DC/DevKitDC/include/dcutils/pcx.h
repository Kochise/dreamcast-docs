/* KallistiOS 1.1.6

   pcx.h
   (c)2000-2001 Dan Potter

   $Id: pcx.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $

*/

#ifndef __PCX_H
#define __PCX_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

typedef struct {
	int	width, height;
	uint16	*pixel_data;
} Image;

Image *pcx_load(const char *fn);
void pcx_free(Image *pcx);

/* Loads a PCX file into texture RAM, potentially twiddling it and/or
   converting it to an alpha mask. */
int pcx_load_texture(const char *fn, int twiddle, int alpha,
	uint32 *txr, int *w, int *h);

__END_DECLS

#endif	/* __PCX_H */

