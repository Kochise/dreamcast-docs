/* KallistiOS Ogg/Vorbis Decoder Library
 *
 * vorbistest.c
 * (c)2001 Thorsten Titze
 *
 * This small program demonstrates the usage of the liboggvorbisplay library
 * to playback audio data encoded with the Vorbis codec.
 *
 * NOTE:
 * You have to put an Ogg File into the RAM Disk which should be called
 * "test.ogg". Or you change the filename in this sourcecode
 */

#include <kos.h>
#include <oggvorbis/sndoggvorbis.h>
#include "display.c"

extern uint8 romdisk[];
long bitrateold,bitratenew;

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) 
{
	cont_cond_t cond;

	print_d("Vorbis Decoder Library Example Program\n\n");

	snd_stream_init();
	sndoggvorbis_init();
	print_d("sndoggvorbis_init();  called...\n");
	
	sndoggvorbis_start("/rd/test.ogg",0);
	print_d("sndoggvorbis_start(\"/rd/test.ogg\",0);  called...\n\n");
	
	printf("main: Vorbisfile artist=%s\r\n",sndoggvorbis_getartist());
	printf("main: Vorbisfile title=%s\r\n",sndoggvorbis_gettitle());

	
	print_d("The OggVorbis File now plays within a thread !\n\n");
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
			sndoggvorbis_stop();
			sndoggvorbis_start("/rd/test.ogg",0);
		}
		// timer_spin_sleep(10);	<-- causes infinite loop sometimes!
		thd_sleep(10);
		bitratenew=sndoggvorbis_getbitrate();
		if (bitratenew != bitrateold)
		{
			printf("main: Vorbisfile current bitrate %ld\r\n",bitratenew);
			bitrateold = bitratenew;
		}
		
	}
	sndoggvorbis_stop();
	sndoggvorbis_shutdown();
	snd_stream_shutdown();
	return 0;
}

