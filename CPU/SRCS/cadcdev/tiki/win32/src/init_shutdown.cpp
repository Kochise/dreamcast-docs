#include "pch.h"

#include "Tiki/plxcompat.h"
#include "Tiki/hid.h"
#include "Tiki/sound.h"
#include "Tiki/stream.h"

#include <al.h>
#include <alc.h>

#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "OpenAL32.lib")

bool Tiki::init(int argc, char **argv) {
	// Let us run with millisecond precision if possible.
	timeBeginPeriod(1);

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

	Audio::Stream::initGlobal();
	Audio::Sound::initGlobal();

	GL::Plxcompat::plx_mat3d_init(640, 480);
	Hid::init();

	return true;
}

void Tiki::shutdown() {
	Hid::shutdown();
	Audio::Sound::shutdownGlobal();
	Audio::Stream::shutdownGlobal();

	timeEndPeriod(1);
}

void Tiki::setName(const char *name, const char *icon) {
    SetWindowText(Tiki::GetWin32Window(), name);
}

void Tiki::GL::showCursor(bool visible) {

}
