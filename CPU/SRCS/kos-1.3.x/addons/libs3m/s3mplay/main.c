/* Small S3M player written as AICA firmware
 *
 * (c)2000 Dan Potter
 *
 * Notes on using:
 *
 * To use this player, you just need to load your S3M into sound RAM
 * at 0x10000, and then load this program into the ARM CPU. This program
 * will then parse the S3M into samples and tracks, etc, and start 
 * playing it. To stop the playback, use dc_snd_stop_arm() in libdream.
 */

/****************** Timer *******************************************/

extern volatile int timer;

void timer_wait(int jiffies) {
	int fin = timer + jiffies;
	while (timer <= fin)
		;
}

/****************** Main Program ************************************/

volatile unsigned long *s3mwait = (unsigned long*)0x1002c;
volatile unsigned long *debug = (unsigned long*)0xffc0;

int arm_main() {
	/* Mono flag */
	debug[1] = 0;

	/* External interface hack */
	debug[2] = 0;

	*debug = 1;

	/* Check to see that there's an S3M waiting */
	/*while (*s3mwait != 0x77826783) {
		int i;
		volatile unsigned long *tmp = (unsigned long *)0;
		for (i=0; i<5000; i++) { *tmp; }
	} */

	*debug = 2;

	/* Initialize the AICA part of the SPU */
	aica_init();

	*debug = 3;

	/* Load the S3M */
	s3m_load();
	
	*debug = 4;
	
	/* Start playback */
	s3m_start_playback();
}






