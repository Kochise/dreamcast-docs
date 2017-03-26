/*
   Tiki

   init_shutdown.cpp

   Copyright (C)2005 Atani Software
*/

#include "pch.h"

#include "Tiki/sound.h"
#include "Tiki/stream.h"
#include "Tiki/plxcompat.h"
#include "Tiki/hid.h"

namespace Tiki {

bool init(int argc, char **argv) {
	// init the GP2x with the following:
	// 1000 ticks per second
	// 16 bit color
	// 44100/16bit/stereo/60hz sound
	// solid_font
	gp2x_init(1000, 16, 44100, 16, 1, 60, 1);
	memset(gp2x_screen15, 0, 320*240*2);
	gp2x_video_flip();
	memset(gp2x_screen15, 0, 320*240*2);
	gp2x_video_flip();
	return Hid::init();
}

void shutdown() {
	Hid::shutdown();
	gp2x_deinit();
}

void setName(const char *windowName, const char *iconName)
{
}

namespace GL {
void showCursor(bool visible) {
}
}

}
