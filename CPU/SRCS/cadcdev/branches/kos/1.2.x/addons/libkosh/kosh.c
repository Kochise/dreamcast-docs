/*
 * kosh.c - console shell for kallistios (A Rough version)
 *
 * (C) 2000 Jordan DeLong
 */

#include <stdio.h>
#include "kosh.h"
#include "chdir.h"

/* global exit flag:  if someone sets this we quit */
volatile int kosh_exit = -2;

static void kosh_thread(void *p) {
	conio_printf("  **** KOSH, The KallistiOS Shell ****\n");
	chdir("/");
	while (!kosh_exit)
		input_oneloop();
	conio_printf("Kosh is done\n");
	kosh_exit = -1;
}

int kosh_init() {
	if (kosh_exit != -2)
		return -1;

	kosh_exit = 0;
	thd_create(kosh_thread, NULL);
	return 0;
}

void kosh_shutdown() {
	if (kosh_exit < 0) {
		kosh_exit = -2;
		return;
	}

	kosh_exit = 1;
	while (kosh_exit != -1)
		thd_pass();
	kosh_exit = -2;
}
