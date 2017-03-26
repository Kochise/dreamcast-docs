/* KallistiOS ##version##

   jpeg.h
   (c)2001 Dan Potter

   $Id: jpeg.h,v 1.1 2003/02/27 03:46:29 bardtx Exp $
*/

#ifndef __JPEG_JPEG_H
#define __JPEG_JPEG_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/img.h>

#ifdef _arch_dreamcast
	#include <dc/pvr.h>
	
	/* Load a JPEG file into a texture; returns 0 for success, -1 for failure. */
	int jpeg_to_texture(const char * filename, pvr_ptr_t tex, int size, int scale);
#endif

/* Load a JPEG into a KOS PIImage */
int jpeg_to_img(const char *filename, int scale, kos_img_t *rv);

__END_DECLS

#endif	/* __JPEG_JPEG_H */

