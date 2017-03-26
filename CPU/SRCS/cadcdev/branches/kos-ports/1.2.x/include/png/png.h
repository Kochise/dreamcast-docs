/* KallistiOS ##version##

   png.h
   (c)2002 Jeffrey McBeth

   $Id: png.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $
*/

#ifndef __PNG_PNG_H
#define __PNG_PNG_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/img.h>

/* PNG_MASK_ALPHA currently doesn't work, I don't know why */
#define PNG_NO_ALPHA 0
#define PNG_MASK_ALPHA 1
#define PNG_FULL_ALPHA 2

#ifdef _arch_dreamcast  
	#include <dc/pvr.h>
	
	/* Load a PNG file, allocating a texture, and returning the size of the file */ 
	int png_load_texture(const char *filename, pvr_ptr_t *tex, uint32 alpha, uint32 *w, uint32 *h);

	/* Load a PNG file into a texture; returns 0 for success, -1 for failure. */
	int png_to_texture(const char * filename, pvr_ptr_t tex, uint32 alpha);
#endif

/* Load a PNG to a KOS Platform Independent Image */
int png_to_img(const char * filename, uint32 mask, kos_img_t *rv);

/* Write out a PNG file */
int png_write_data(const char *filename, uint8 *data, uint32 width, uint32 height);

__END_DECLS

#endif	/* __PNG_PNG_H */


