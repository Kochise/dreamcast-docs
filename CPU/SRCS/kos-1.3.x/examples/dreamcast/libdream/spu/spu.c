/* Note: This is the old libdream SPU example that happens to load an
   S3M for playback. This is no longer the recommended way to do so!
   You should use the full libs3m library that ships with KOS as an
   add-on instead. This example is mainly left to demonstrate low-level
   sound routines. It also, however, demonstrates how to set up the
   romdisk and how to use its new mmap() feature. */

#include <kos.h>
#include "s3mplay.h"	/* Player ARM code */

uint8 *song;

/* This is sort of an unorthodox way of using the SPU ^_^;; but it's
   how the S3M player works right now. */
volatile unsigned long *snd_dbg = (unsigned long*)0xa080ffc0;
void copy_s3m(char *song, int len) {
	spu_disable();
	spu_memload(0x10000, song, len);
	spu_memload(0, s3mplay, sizeof(s3mplay));

	/* Switch channels to mono if uncommented */
	/* snd_dbg[1] = 1; */
	
	printf("Load OK, starting ARM\n");
	spu_enable();

	while (*snd_dbg != 3)
		;

	while (*snd_dbg == 3)
		;
}

void wait_start() {
	uint8 mcont;
	cont_cond_t cond;

	while (1) {
		mcont = maple_first_controller();
		if (!mcont) continue;
		
		/* Check for start on the controller */
		if (cont_get_cond(mcont, &cond) < 0)
			continue;
		
		if (!(cond.buttons & CONT_START)) {
			printf("Pressed start\n");
			return;
		}
		
		usleep(10 * 1000);
	}
}

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	file_t f;
	int len;
	
	/* Open the S3M file from the romdisk */
	f = fs_open("/rd/cyboman.s3m", O_RDONLY);

	/* Get its length */
	len = fs_total(f);

	/* mmap() the file space; note that this ONLY works on rom file
	   systems for now; this may change later */
	song = fs_mmap(f);

	/* Start a song playing */
	copy_s3m(song, len);

	/* Close the file */
	fs_close(f);

	/* Wait for start */
	wait_start();

	return 0;
}
