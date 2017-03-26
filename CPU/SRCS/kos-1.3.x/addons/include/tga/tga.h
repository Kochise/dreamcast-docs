/* KallistiOS ##version

   tga.h
   (c)2000-2001 Benoit Miller

   $Id: tga.h,v 1.1 2003/02/27 03:46:32 bardtx Exp $

*/

#ifndef __TGA_TGA_H
#define __TGA_TGA_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/img.h>

/* Loads a TGA file into a kos_img_t struct */
int tga_to_img(const char *fn, kos_img_t *rv);

#ifdef _arch_dreamcast
	/* Loads a TGA file into texture RAM, potentially twiddling it. 
   	TGA files include an alpha channel. */
	int tga_load_texture(const char *fn, int twiddle, uint32 *txr, 
		int *w, int *h);
#endif

__END_DECLS

#endif	/* __TGA_TGA_H */

