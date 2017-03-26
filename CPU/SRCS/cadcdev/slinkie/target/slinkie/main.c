/*

  slinkie/main.c
  Copyright (C)2004 Dan Potter

*/

#include <dc/scif.h>
#include <dc/video.h>
#include <dc/biosfont.h>
#include <arch/irq.h>
#include <arch/timer.h>
#include <net/net.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <slinkie/exec.h>
#include <slinkie/main.h>

extern int start, _bss_start, end;

int sl_mode = SLMODE_NONE;
uint32 sl_exec_addr = 0;

// Exclusive mode loop: set to SLMODE_NONE to quit.
void excl_loop() {
	int rv;

	sl_mode = SLMODE_EXCL;

	while (sl_mode == SLMODE_EXCL) {
		net_loop();
		if (sl_mode == SLMODE_COOP) {
			nif->if_stop(nif);
			printf("executing at %08lx\n", sl_exec_addr);
			rv = exec(sl_exec_addr, 0, NULL);
			printf("return value was %d\n", rv);
			if (sl_mode != SLMODE_NONE) {
				nif->if_start(nif);
				sl_mode = SLMODE_EXCL;
			}
		}
	}
}

int arch_main() {
	uint8 *bss_start = (uint8 *)(&_bss_start);
	uint8 *bss_end = (uint8 *)(&end);
	uint32 size;

	memset(bss_start, 0, bss_end - bss_start);
	scif_init();
	printf("\n--\nSlinkie " SLINKIE_VERSION " starting.\n");
	timer_init();

	// Sanity check
	size = bss_end - (uint8 *)&start;
	printf("Program size = %d bytes\n", size);
	if (size > 0xb000) {
		printf("warning: program probably too big\n");
	}
	
	vid_init(DM_640x480, PM_RGB565);
	vid_clear(20,0,40);
	bfont_draw_str(vram_s + 20 + 20*640, vid_pixel(224, 224, 224),
		vid_pixel(20,0,40), "Slinkie " SLINKIE_VERSION);

	irq_init();
	if (net_init() < 0) {
		bfont_draw_str(vram_s + 20 + 44*640, vid_pixel(224,224,224),
			vid_pixel(20,0,40), "No device detected");
		printf("No network devices detected!\n");
		timer_spin_sleep(5000);
	} else {
		bfont_draw_str(vram_s + 20 + 44*640, vid_pixel(224,224,224),
			vid_pixel(20,0,40), nif->descr);
		printf("Detected a '%s'\n", nif->descr);
		excl_loop();
		printf("Exiting...\n");
	}

	// If we're running at the "root", we can't exit.
	if ((uint32)&start == 0x8c004000) {
		for ( ; ; )
			;
	}

	vid_clear(0,0,0);

	return 0;
}
