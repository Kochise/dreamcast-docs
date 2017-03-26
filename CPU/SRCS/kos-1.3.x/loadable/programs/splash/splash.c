/* KallistiOS ##version##

   splash.c
   Copyright (C)2003 Dan Potter

   $Id: splash.c,v 1.2 2003/07/31 00:51:43 bardtx Exp $
*/

#include <kos.h>
#include <assert.h>
#include <kos/img.h>
#include <jpeg/jpeg.h>

// Our logo
static kos_img_t * logo = NULL;

static void draw_logo() {
	int	y;
	uint16	* ld;

	assert( logo );
	assert( (KOS_IMG_FMT_I(logo->fmt) & KOS_IMG_FMT_MASK) == KOS_IMG_FMT_RGB565 );

	ld = (uint16 *)logo->data;

	for (y=0; y<logo->h; y++) {
		memcpy4(vram_s + y*640, ld + y*logo->w, logo->w*2);
	}
}

int main(int argc, char **argv) {
	vid_init(DEFAULT_VID_MODE, DEFAULT_PIXEL_MODE);

	// Load up our logo graphic
	logo = calloc(1, sizeof(kos_img_t));
	if (jpeg_to_img("logo.jpg", 1, logo) < 0) {
		perror("can't open logo");
		return -1;
	}

	draw_logo();

	return 0;
}
