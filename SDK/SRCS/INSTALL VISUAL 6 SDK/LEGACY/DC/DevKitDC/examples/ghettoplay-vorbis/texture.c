/* GhettoPlay: an S3M browser and playback util
   (c)2000 Dan Potter
*/

#include "gp.h"

/* Creates the utility texture used for the font and mouse cursor. The
   resulting texture will be 256x256. */
#include "mouse1.h"
uint32 util_texture = 0;
void setup_util_texture() {
	uint32 ts;
	uint16 *vram;
	int x, y;

	ts = ta_txr_allocate(256*256*2);
	vram = ta_txr_map(ts);
	
	/* First dump in the mouse cursor */
	for (y=0; y<16; y++) {
		for (x=0; x<10; x++) {
			if (mouse1_xpm[y*10+x] == '.')
				*vram = 0xffff;
			else if (mouse1_xpm[y*10+x] == '+')
				*vram = 0xf000;
			else
				*vram = 0x0000;
			vram++;
		}
		vram += 256 - 10;
	}
	
	/* Now add the rest as ASCII characters */
	vram = ta_txr_map(ts);
	for (y=0; y<8; y++) {
		for (x=0; x<16; x++) {
			/* Skip the first (it's a mouse pointer) */
			if (x != 0 || y != 0) 
				bfont_draw(vram, 256, 0, y*16+x);
			vram += 16;
		}
		vram += 23*256;
	}
	
	util_texture = ts;
}
