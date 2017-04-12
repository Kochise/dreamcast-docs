/*
 * kosh.c - console shell for kallistios (A Rough version)
 *
 * (C) 2000 Jordan DeLong
 */

#include <stdio.h>
/* #include <os/abi/libk.h> */
#include "draw.h"
#include "kosh.h"

/* global exit flag:  if someone sets this we quit */
volatile int kosh_exit = 0;

int (*oldprintf)(const char *fmt, ...);

/* KallistOS interfaces */
/* abi_thread_t 	*thread		= NULL;
abi_maple_t 	*maple 		= NULL;
abi_ta_t 	*ta 		= NULL;
abi_video_t	*video		= NULL;
abi_fs_t	*fs		= NULL;
abi_process_t	*process 	= NULL;
abi_svcmpx_t	*svcmpx		= NULL; */

/* get all our abi's and then start our main loop */
int main(int argc, char **argv) {
	kos_init_all(THD_ENABLE | IRQ_ENABLE | TA_ENABLE, NULL);

	printf("kosh starting\r\n");

	/* init all our abi's */
	/* thread = lib_open("thread");
	if (!thread) { printf("Can't open thread library\r\n"); return -1; }
	maple = lib_open("maple");
	if (!maple) { printf("Can't open maple library\r\n"); return -1; }
	ta = lib_open("ta");
	if (!ta) { printf("Can't open ta library\r\n"); return -1; }
	video = lib_open("video");
	if (!video) { printf("Can't open video library\r\n"); return -1; }
	fs = lib_open("fs");
	if (!fs) { printf("Can't open fs library\r\n"); return -1; }
	process = lib_open("process");
	if (!process) { printf("Can't open process library\r\n"); return -1; }
	svcmpx = lib_open("svcmpx");
	if (!svcmpx) { printf("Can't open svcmpx library\r\n"); return - 1; } */

	/* initalize the conio service */
	conio_init();

	conio_printf("   **** KOSH v1.2, The KallistiOS Shell ****\n");

	/* change directory to the default */
	chdir("/cd");

	/* this is the meat */
	while (!kosh_exit) { input_frame(); }

	/* shutdown console i/o */
	conio_shutdown();

	/* close our lib handles */
	/* lib_close(process);
	lib_close(thread);
	lib_close(maple);
	lib_close(ta);
	lib_close(video);
	lib_close(fs); */

	printf("kosh is done\r\n");
	kos_shutdown_all();
	return 0;
}
