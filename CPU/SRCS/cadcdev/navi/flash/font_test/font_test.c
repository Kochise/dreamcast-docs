/*
   font_test.c
   (c)2002 Dan Potter
*/

/* Simple test to see if the BIOS fonts are working */

#include <kos.h>
#include <assert.h>

int main(int argc, char **argv) {
	int		x, y, i, c;
	
	cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);

	for (y=0, i=32; i<256; y+=24) {
		for (x=0; x<576; x+=12, i++) {
			bfont_draw(vram_s+y*640+x, 640, 1, i);
		}
	}

	return 0;
}


