/* This isn't a very well supported mode under KOS but it's here
   for completeness. This is kind of cool actually because thanks to the
   extra pixel precision you can see further into the XOR pattern. */

#include <kos.h>

int main(int argc, char **argv) {
	int x, y;

	/* Do initial setup */	
	vid_set_mode(DM_640x480, PM_RGB888);
	
	for (y=0; y<480; y++)
		for (x=0; x<640; x++) {
			int c = (x ^ y) & 255;
			vram_l[y*640+x] = (c << 17)
				| (c << 8)
				| (c << 0);
		}

	usleep(5 * 1000 * 1000);

	return 0;
}
