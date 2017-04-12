/* KallistiOS 1.1.6

   pvrutils.h
   (c)2000 Dan Potter

   $Id: pvrutils.h,v 1.3 2002/01/05 07:23:32 bardtx Exp $
   
*/

#ifndef __PVRUTILS_H
#define __PVRUTILS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Twiddle function -- copies from a source rectangle in SH-4 ram to a
   destination texture in PVR ram. */
void txr_twiddle_copy(const uint16 *src, uint32 srcw, uint32 srch,
		uint32 dest, uint32 destw, uint32 desth, uint16 bkg);

/* General twiddle function -- copies a rectangle from SH-4 ram to PVR ram. 
   Texture can be 16bpp, 8bpp or 4bpp (i.e. paletted). Contrary to other
   twiddle copy functions,  the rectangle does not
   need to be a square (not tested  with h>w, but this is just
   a matter of a rotation by PI/2).

   w and h must be a power of 2.
   bpp must be either 4, 8 or 16.

   Returns 0 if success, -1 otherwise.

   Contributed by Vincent Penne.

   NOTE: Might be integrated with the normal copy above.
   
 */
int txr_twiddle_copy_general(const void *src, uint32 dest, 
			      uint32 w, uint32 h, uint32 bpp);

/* Twiddle function -- copies from a source rectangle in SH-4 ram to a
   destination texture in PVR ram. The image will be scaled to the texture
   size. */
void txr_twiddle_scale(const uint16 *src, uint32 srcw, uint32 srch,
		uint32 dest, uint32 destw, uint32 desth);

/* Adjusts a 16-bit image so that instead of RGB565 gray scales, you will
   have ARGB4444 alpha scales. The resulting image will be entirely white. */
void txr_to_alpha(uint16 *img, int x, int y);

/* Commits a dummy polygon (for unused lists). Specify the polygon
   type (opaque/translucent). */
void pvr_dummy_poly(int type);

/* Commits an entire blank frame. Assumes two lists active (opaque/translucent) */
void pvr_blank_frame();

__END_DECLS

#endif	/* __PVRUTILS_H */

