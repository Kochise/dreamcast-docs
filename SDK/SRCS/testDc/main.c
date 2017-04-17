#include <kos.h>

int main(int argc, char **argv) {
	int x, y;

	/* Bother us with output only if something died */
	dbglog_set_level(DBG_DEAD);
	
	/* Set the video mode */
	vid_set_mode(DM_640x480, PM_RGB565);
	
	for (y=0; y<480; y++)
		for (x=0; x<640; x++) {
			int c = (x ^ y) & 255;
			vram_s[y*640+x] = ((c >> 3) << 12)
				| ((c >> 2) << 5)
				| ((c >> 3) << 0);
		}

	/* Pause to see the results */
	usleep(5*1000*1000);

	return 0;
}
