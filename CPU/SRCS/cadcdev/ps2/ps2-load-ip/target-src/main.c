/* ps2-load-ip

   main.c

   Copyright (c)2002 Dan Potter
   License: BSD

   $Id: main.c,v 1.3 2002/11/02 09:33:58 bardtx Exp $
*/

#include "stdio.h"
#include "ioports.h"

#include "fb_support.h"
#include "smap.h"

#include "commands.h"
#include "net.h"
#include "syscalls.h"
#include "ps2loadip.h"

// Some global status vars
int running;
int reset_eth;
int escape_loop;
int console_enabled;

// Print a banner on startup
extern char banner[];
void print_banner() {
	printf( "ps2-load-ip 1.0.1 Copyright (c) 2000-2002 Dan Potter, Andrew Kieschnick,\n"
		"   YAEGASHI Takeshi, SCEI, RedHat, and others.\n"
	#include "banner.h"
		"\n"
	);
}

extern void ps2lip_vectors();
void init() {
	// Get the GS console all up and happy
	lcd_init();
	printf_init();
	print_banner();

	// Initialize the SMAP device
	smap_init();

	// Setup dcload vars
	running = 0;
	reset_eth = 0;
	escape_loop = 0;
	console_enabled = 0;
	cmd_init();
	net_init();
	syscalls_init();

	// Put a pointer to our info block in a predictable place (above
	// the standard RTE boot info block should be safe).
	*((uint32 *)0x81fff800) = (uint32)&ps2lip_vectors;
}

// Main program entry point
void arch_main() {
	init();

	smap_start();
	for ( ; ; ) {
		smap_poll();
		if (reset_eth) {
			smap_stop();
			smap_init();
			smap_start();
			reset_eth = 0;
		}
	}
}
