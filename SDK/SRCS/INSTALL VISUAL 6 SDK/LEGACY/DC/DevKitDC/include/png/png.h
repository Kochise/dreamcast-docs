/* KallistiOS 1.1.6

   png.h
   (c)2002 Jeffrey McBeth

   $Id: png.h,v 1.1 2002/01/11 06:08:20 bardtx Exp $
*/

#ifndef __PNG_PNG_H
#define __PNG_PNG_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* PNG_MASK_ALPHA currently doesn't work, I don't know why */
#define PNG_NO_ALPHA 0
#define PNG_MASK_ALPHA 1
#define PNG_FULL_ALPHA 2
  
  
/* Load a PNG file into a texture; returns 0 for success, -1 for failure. */
int png_to_texture(const char * filename, uint32 tex, uint32 alpha);

__END_DECLS

#endif	/* __PNG_PNG_H */


