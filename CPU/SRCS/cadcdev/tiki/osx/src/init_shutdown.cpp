/*
   Tiki

   init_shutdown.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"

#include <CoreFoundation/CFString.h>

#if TIKI_PLAT == TIKI_OSX
#	include <OpenAL/al.h>
# include <OpenAL/alc.h>
#else
#	include <al.h>
# include <alc.h>
#endif

#include "Tiki/sound.h"
#include "Tiki/stream.h"
#include "Tiki/plxcompat.h"
#include "Tiki/hid.h"

extern "C" void tiki_set_window_name(CFStringRef windowName);
extern "C" void tiki_set_show_cursor(int visible);

namespace Tiki {

bool init(int argc, char **argv) {
	ALCdevice *dev = NULL;
	ALCcontext *ctx = NULL;
	
	dev = alcOpenDevice(getenv("OPENAL_DEVICE"));  // getenv()==NULL is okay.
  if (dev != NULL) {
		ctx = alcCreateContext(dev, 0);
    if (ctx != NULL) {
			alcMakeContextCurrent(ctx);
      alcProcessContext(ctx);
		} // if
	} // if

	Audio::Sound::initGlobal();
	Audio::Stream::initGlobal();
	GL::Plxcompat::plx_mat3d_init(640, 480);
	Hid::init();

	return true;
}

void shutdown() {
	Audio::Sound::shutdownGlobal();
	Audio::Stream::shutdownGlobal();
	Hid::shutdown();

	//alutExit();
}

void setName(const char *windowName, const char *icon) {
	tiki_set_window_name(CFStringCreateWithCString(NULL, windowName, kCFStringEncodingMacRoman));
}

namespace GL {
void showCursor(bool visible) {
	tiki_set_show_cursor(visible);
}

};
};