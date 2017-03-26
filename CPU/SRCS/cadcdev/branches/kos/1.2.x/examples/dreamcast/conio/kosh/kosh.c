/*
 * kosh.c - console shell for kallistios (A Rough version)
 *
 * (C) 2000 Jordan DeLong
 */

#include <stdio.h>
#include "kosh.h"
#include "chdir.h"

/* global exit flag:  if someone sets this we quit */
volatile int kosh_exit = 0;

int (*oldprintf)(const char *fmt, ...);

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

/* get all our abi's and then start our main loop */
int main(int argc, char **argv) {
	pvr_init_defaults();

	printf("kosh starting\n");

	/* initalize the conio service */
	conio_init(CONIO_TTY_PVR, CONIO_INPUT_LINE);
	/* conio_init(CONIO_TTY_SERIAL, CONIO_INPUT_LINE); */

	conio_printf("   **** KOSH v1.4, The KallistiOS Shell ****\n");

	/* change directory to the default */
	chdir("/");

	/* this is the meat */
	while (!kosh_exit)
		input_oneloop();

	/* shutdown console i/o */
	conio_shutdown();

	printf("kosh is done\n");
	return 0;
}
