/*
   font_cvt.c
   (c)2002 Dan Potter
*/

/* Place a properly formatted font image in romdisk as
   "newfont.png" and this program will write out a font.bin
   suitable for usage with the bootstrap in /pc/tmp (requires
   dc-load to be running). */

#include <kos.h>
#include <png/png.h>
#include <assert.h>

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

uint8 outbuffer[16384] = {0};
uint32 obptr = 0;

void write_nybble(uint8 n) {
	uint32 byte = obptr / 2;
	uint32 shift = 4 - (4*(obptr % 2));

	outbuffer[byte] |= n << shift;

	obptr++;
}

void write_nybbles(uint16 row) {
	write_nybble((row >> 8) & 0xf);
	write_nybble((row >> 4) & 0xf);
	write_nybble((row >> 0) & 0xf);
}

int main(int argc, char **argv) {
	int		x, y, i, c;
	kos_img_t	img;
	uint16		pxl;
	file_t		f;

	cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);

	if (png_to_img("/rd/newfont.png", PNG_MASK_ALPHA, &img) < 0) {
		printf("Couldn't load PNG of new font\n");
		return 0;
	}

	printf("Image is %dx%d\n", img.w, img.h);

	for (y=0; y<img.h; y++) {
		for (x=0; x<img.w; x++) {
			pxl = ((uint16*)img.data)[y*img.w+x];
			if (pxl == 0xffff)
				vram_s[y*640+x] = pxl;
		}
	}

	kos_img_free(&img, 0);

	for (c=0; c<96; c++) {
		for (y=0; y<24; y++) {
			pxl = 0;
			for (x=0; x<12; x++) {
				if (vram_s[((y+(c/16)*24)*640+(x+(c%16)*12))])
					pxl |= 0x0800 >> x;
			}
			write_nybbles(pxl);
		}
	}

	assert( (obptr % 2) == 0 );
	printf("Final data size is %d bytes\n", obptr/2);

	f = fs_open("/pc/tmp/font.bin", O_WRONLY);
	assert(f);
	fs_write(f, outbuffer, obptr/2);
	fs_close(f);

	return 0;
}


