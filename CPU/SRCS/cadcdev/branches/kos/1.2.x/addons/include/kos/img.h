/* KallistiOS ##version##
   
   kos/img.h
   (c)2002 Dan Potter

   $Id: img.h,v 1.4 2003/04/24 03:00:44 bardtx Exp $

*/

#ifndef __KOS_IMG_H
#define __KOS_IMG_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* KOS Platform independent image struct; you can use this for textures or
   whatever you feel it's appropriate for. "width" and "height" are as you
   would expect. "format" has a lower-half which is platform independent
   and used to basically describe the contained data; the upper-half is
   platform dependent and can hold anything (so AND it off if you want
   the bottom part). Note that in some of the more obscure formats (like
   the paletted formats) the data interpretation _may_ be platform dependent.
   Thus we also provide a data-length field. */
typedef struct kos_img {
	void	* data;
	uint32	w, h;
	uint32	fmt;
	uint32	byte_count;
} kos_img_t;

/* Access to the upper and lower pieces of the format word */
#define KOS_IMG_FMT_I(x) ((x) & 0xffff)		/* Platform independent part */
#define KOS_IMG_FMT_D(x) (((x) >> 16) & 0xffff)

/* Macro to create a new format word */
#define KOS_IMG_FMT(i, d) ( ((i) & 0xffff) | (((d) & 0xffff) << 16) )

/* Definitions for the plat independent part *************************************/

/* Bitmap formats */
#define KOS_IMG_FMT_NONE	0x00	/* Undefined */
#define KOS_IMG_FMT_RGB888	0x01	/* Interleaved r/g/b bytes (24-bit) */
#define KOS_IMG_FMT_ARGB8888	0x02	/* Interleaved a/r/g/b bytes (32-bit) */
#define KOS_IMG_FMT_RGB565	0x03	/* r/g/b 5/6/5 (16-bit) */
#define KOS_IMG_FMT_ARGB4444	0x04	/* a/r/g/b 4/4/4/4 (16-bit) */
#define KOS_IMG_FMT_ARGB1555	0x05	/* a/r/g/b 1/5/5/5 (16-bit) */
#define KOS_IMG_FMT_PAL4BPP	0x06	/* Paletted (4-bit) */
#define KOS_IMG_FMT_PAL8BPP	0x07	/* Paletted (8-bit) */
#define KOS_IMG_FMT_YUV422	0x08	/* y/u/v 4/2/2 (8-bit) */
#define KOS_IMG_FMT_BGR565	0x09	/* b/g/r 5/6/5 (16-bit) */
#define KOS_IMG_FMT_RGBA8888	0x10	/* Interleaved r/g/b/a bytes (32-bit) */
#define KOS_IMG_FMT_MASK	0xff

/* Misc attributes */
#define KOS_IMG_INVERTED_X	0x0100	/* X axis is inverted */
#define KOS_IMG_INVERTED_Y	0x0200	/* Y axis is inverted */
#define KOS_IMG_NOT_OWNER	0x0400	/* We don't own the buffer containing
					   the data (ROM or similar) */

/* Util functions ****************************************************************/

/* Free a kos_img_t which was created by an image loader; set struct_also to non-zero
   if you want it to free the struct itself as well. */
void kos_img_free(kos_img_t *img, int struct_also);

__END_DECLS

#endif	/* __KOS_IMG_H */

