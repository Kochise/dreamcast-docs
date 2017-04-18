#include <kos.h>

int main(int argc, char **argv) {
	int x, y;

	/* Do initial setup */	
	kos_init_all(NONE_ENABLE, ROMDISK_NONE);

	/* Set the video mode */
	vid_set_mode(DM_320x240_NTSC, PM_RGB565);
	
	for (y=0; y<240; y++)
		for (x=0; x<320; x++) {
			int c = (x ^ y) & 255;
			vram_s[y*320+x] = ((c >> 3) << 12)
				| ((c >> 2) << 5)
				| ((c >> 3) << 0);
		}

	/* Pause to see the results */
	usleep(5*1000*1000);

	return 0;
}

