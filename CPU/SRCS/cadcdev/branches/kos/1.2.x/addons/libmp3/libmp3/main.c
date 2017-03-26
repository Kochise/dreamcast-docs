/* KallistiOS ##version##

   libmp3 main.c
   (c)2000-2001 Dan Potter

*/

#include <kos.h>

CVSID("$Id: main.c,v 1.2 2002/01/06 00:40:33 bardtx Exp $");

int sndserver_thread(void *blagh) {
	printf("sndserver: started [DEBUG]\r\n");
	printf("sndserver: pid is %d; capabilities: MP3, SFX\r\n", thd_get_current()->tid);

	sndmp3_mainloop();
	
	printf("sndserver exited\r\n");
	return 0;
}

int mp3_init() {
	if (thd_create(sndserver_thread, NULL) != NULL) {
		sndmp3_wait_start();
		return 0;
	} else
		return -1;
}

int mp3_start(const char *fn, int loop) {
	return sndmp3_start(fn, loop);
}

int mp3_stop() {
	sndmp3_stop();
	return 0;
}

int mp3_shutdown() {
	sndmp3_shutdown();
	return 0;
}


