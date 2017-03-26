/* 
   Network Configurator
   
   netcfg.cpp
   Copyright (C)2003 Dan Potter

   $Id: netcfg.cpp,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#include <kos.h>
#include <tsu/font.h>
#include <plx/context.h>
#include <dc/sound/sound.h>
#include "menu.h"
#include "netcfg.h"

/*

This program implements a network configuration tool, with
controller-compatible UI. The idea is to use this app to create and edit
the network config which will then be used by lwIP later.

This is probably overkill, but it's also a nice way to import some more
code from FoF and show off a real Tsunami app.

*/

extern uint8 romdisk[];
netcfg_t cfg;

void dostuff() {
	RefPtr<Font> fnt = new Font("font.txf");
	fnt->setSize(24.0f);

	RefPtr<Menu> cfg = new Menu(fnt);
	cfg->doMenu();
}

int main(int argc, char **argv) {
	printf("netcfg beginning\n");

	memset(&cfg, 0, sizeof(cfg));
	if (netcfg_load(&cfg) < 0)
		printf("unable to load previous config\n");
	else
		printf("loaded previous config\n");

	/* Initialize KOS */
	fs_romdisk_mount("/netcfgrd", romdisk, 0);
	fs_chdir("/netcfgrd");
	vid_init(DEFAULT_VID_MODE, DEFAULT_PIXEL_MODE);
	pvr_init_defaults();
	plx_cxt_init();
	snd_init();

	dostuff();

	pvr_shutdown();
	vid_shutdown();

	fs_romdisk_unmount("/netcfgrd");

	printf("netcfg finished\n");

	return 0;
}


