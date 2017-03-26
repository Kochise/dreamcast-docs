/* KallistiOS ##version##

   tga_texture.c
   (c)2000-2001 Benoit Miller

   TGA texture loader.
*/

#include <kos.h>
#include <tga/tga.h>

CVSID("$Id: tga_texture.c,v 1.2 2002/04/07 02:34:27 bardtx Exp $");

/* Loads a TGA file into texture RAM, potentially twiddling it. 
   TGA files already include an alpha channel. */
int tga_load_texture(const char *fn, int twiddle, uint32 *txr_out, int *w, int *h) {
	kos_img_t	img;
	pvr_ptr_t	txr;

	/* Load the image */
	if (tga_to_img(fn, &img) < 0)
		return -1;

	/* Allocate texture RAM for it */
	txr = pvr_mem_malloc(img.w * img.h * 2);

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

