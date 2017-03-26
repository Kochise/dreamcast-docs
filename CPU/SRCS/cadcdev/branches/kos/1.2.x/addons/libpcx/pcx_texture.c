/* KallistiOS ##version##

   pcx_texture.c
   (c)2000-2002 Dan Potter

   PCX texture loader
*/

#include <kos.h>
#include <pcx/pcx.h>

CVSID("$Id: pcx_texture.c,v 1.1 2002/04/07 01:54:29 bardtx Exp $");

/* Adjusts a 16-bit image so that instead of RGB565 gray scales, you will
   have ARGB4444 alpha scales. The resulting image will be entirely white. */
/* Imported here to avoid a dependency on libdcutils.a */
static void _txr_to_alpha(uint16 *img, int x, int y) {
	int i;
	short v;
	
	for (i=0; i<x*y; i++) {
		v = img[i] & 0x1f;
		v = ((v >> 1) << 12) | 0x0fff;
		img[i] = v;
	}
}


/* Loads a PCX file into texture RAM, potentially twiddling it and/or
   converting it to an alpha mask. */
int pcx_load_texture(const char *fn, int twiddle, int alpha,
		uint32 *txr_out, int *w, int *h) {
	kos_img_t	img;
	pvr_ptr_t	txr;

	/* Load the image */
	if (pcx_to_img(fn, &img) < 0)
		return -1;

	/* Allocate texture RAM for it */
	txr = pvr_mem_malloc(img.w * img.h * 2);

	/* If requested, convert it to an alpha mask */
	if (alpha)
		_txr_to_alpha((uint16 *)img.data, img.w, img.h);

	/* Now either twiddle it or copy it to texture ram */
	if (twiddle)
		pvr_txr_load_kimg(&img, txr, 0);
	else
		pvr_txr_load(img.data, txr, img.w*img.h*2);

	if (txr_out != NULL) *txr_out = (uint32)txr;
	if (w != NULL) *w = img.w;
	if (h != NULL) *h = img.h;

	kos_img_free(&img, 0);

	return 0;
}

