#include <kos.h>

static kthread_t * thd = NULL;

static void sndserver_thread(void *blagh) {
	printf("sndserver: pid is %d\n", thd_get_current()->tid);
	sndoggvorbis_mainloop();
}

int sndoggvorbis_init() {
	if (thd) {
		printf("sndserver: already initialized!\n");
		return -1;
	}

	printf("sndserver: initializing sndoggvorbis 0.7 [OggVorbis 1.0 based]\n");
	thd = thd_create(sndserver_thread, NULL);
	if (thd != NULL) {
		/* Wait until the oggvorbis decoder thread is ready */
		sndoggvorbis_wait_start();
		printf("sndserver: successfully created thread\n");
		return 0;
	} else {
		printf("sndserver: error creating thread\n");
		return -1;
	}
}

void sndoggvorbis_thd_quit();

void sndoggvorbis_shutdown() {
	if (!thd) {
		printf("sndserver: not initialized!\n");
		return;
	}

	sndoggvorbis_thd_quit();
	thd_wait(thd);

	printf("sndserver: exited successfully\n");
}
