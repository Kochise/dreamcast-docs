/* KallistiOS MP3 Decoder Library
 *
 * mp3test.c
 * (c)2001 Thorsten Titze
 *
 * This small program demonstrates the usage of the liboggvorbisplay library
 * to playback audio data encoded with the Vorbis codec.
 *
 * NOTE:
 * You have to put an Ogg File into the RAM Disk which should be called
 * "test.ogg". Or you change the filename in this sourcecode
 */

/* Modified to be an MP3 sample by Dan Potter */

#include <kos.h>
#include <mp3/sndmp3.h>
#include "display.c"

extern uint8 romdisk[];
long bitrateold,bitratenew;

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) 
{
	cont_cond_t cond;

	print_d("mp3 Decoder Library Example Program\n\n");

	mp3_init();
	print_d("sndmp3_init();  called...\n");
	
	mp3_start("/rd/test.mp3",0);
	print_d("mp3_start(\"/rd/test.mp3\",0);  called...\n\n");
	
	/* printf("main: Vorbisfile artist=%s\r\n",sndoggvorbis_getartist());
	printf("main: Vorbisfile title=%s\r\n",sndoggvorbis_gettitle()); */

	
	print_d("The MP3 File now plays within a thread !\n\n");
	print_d("Press START to exit and (Y) to re-start playing...");

	while(1)
	{
		if (cont_get_cond(maple_first_controller(), &cond) < 0)
			break;
		if (!(cond.buttons & CONT_START))
			break;
		if (!(cond.buttons & CONT_Y))
		{
			printf("main: restarting oggvorbis\r\n");
			mp3_stop();
			mp3_start("/rd/test.mp3",0);
		}
		// timer_spin_sleep(10);	<-- causes infinite loop sometimes!
		thd_sleep(10);
		/* bitratenew=sndoggvorbis_getbitrate();
		if (bitratenew != bitrateold)
		{
			printf("main: Vorbisfile current bitrate %ld\r\n",bitratenew);
			bitrateold = bitratenew;
		} */
		
	}
	mp3_stop();
	mp3_shutdown();
	return 0;
}

