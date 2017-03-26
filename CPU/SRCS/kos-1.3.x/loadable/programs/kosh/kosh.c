/*
 * kosh.c - console shell for kallistios (A Rough version)
 *
 * (C) 2000 Jordan DeLong
 */

#include <stdio.h>
#include "kosh.h"
#include "chdir.h"
#include "jobs.h"
#include <kos/process.h>
#ifndef SERIAL
#	include <dc/maple.h>
#	include <dc/pvr.h>
#endif
#include <signal.h>

/* global exit flag:  if someone sets this we quit */
volatile int kosh_exit = 0;

int sighnd(int sig, void * data) {
	kosh_exit = 1;
	return 0;
}

int main(int argc, char **argv) {
	int cio = 1;

	signal(SIGQUIT, sighnd);
	job_init();

	/* First check to see if we got any command line args */
	if (argc > 1) {
		if (argv[1][0] == '-')
			cio = 0;
		else {
			printf("kosh: executing script '%s'\n", argv[1]);
			input_exec_script(argv[1]);
			printf("kosh: finished executing script '%s'\n", argv[1]);
			return 0;
		}
	}

#ifndef SERIAL
	vid_init(DEFAULT_VID_MODE, DEFAULT_PIXEL_MODE);
	pvr_init_defaults();
#endif

	/* initalize the conio service */
#ifndef SERIAL
	conio_init(CONIO_TTY_PVR, CONIO_INPUT_LINE);
#else
	if (cio)
		conio_init(CONIO_TTY_SERIAL, CONIO_INPUT_LINE);
	else
		conio_init(CONIO_TTY_STDIO, CONIO_INPUT_LINE);
#endif

	conio_printf("   **** KOSH v1.4, The KallistiOS Shell ****\n");

	/* change directory to the default */
	chdir(fs_getwd());

	/* this is the meat */
	while (!kosh_exit)
		input_oneloop();
	kosh_exit = 0;

	conio_printf("Kosh is done!\n");

	/* shutdown console i/o */
	conio_shutdown();

	return 0;
}

/* static int signal_handler(kprocess_t * proc, int sig) {
	printf("kosh: received signal %d\n", sig);
	if (sig == SIGQUIT) {
		kosh_exit = 1;
		while (kosh_exit)
			thd_pass();
	}
	return 0;
}

int start(kprocess_t * proc, int argc, char **argv) {
	process_set_signal(proc, signal_handler);
	thd_create(proc, main, NULL);
	return 0;
} */

