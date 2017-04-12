/* KallistiOS 1.1.6

   jpeg.h
   (c)2001 Dan Potter

   $Id: jpeg.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
*/

#ifndef __JPEG_JPEG_H
#define __JPEG_JPEG_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Load a JPEG file into a texture; returns 0 for success, -1 for failure. */
int jpeg_to_texture(const char * filename, uint32 tex, int size, int scale);

__END_DECLS

#endif	/* __JPEG_JPEG_H */

