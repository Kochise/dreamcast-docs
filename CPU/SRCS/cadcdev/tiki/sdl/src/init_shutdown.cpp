/*
   Tiki

   init_shutdown.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "Tiki/sound.h"
#include "Tiki/stream.h"
#include "Tiki/plxcompat.h"
#include "Tiki/hid.h"
#include <SDL/SDL.h>

namespace Tiki {

bool init(int argc, char **argv) {
	ALCdevice *dev;
	ALCcontext *context;
	if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_EVENTTHREAD | SDL_INIT_NOPARACHUTE) < 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return false;
	}

	dev = alcOpenDevice("sdl");
	if(dev == NULL)
	{
		fprintf(stderr, "Unable to initialize OpenAL: %s\n", alGetError());
	}
	else
	{
		context = alcCreateContext(dev, NULL);
		if(context == NULL)
		{
			fprintf(stderr, "alcCreateContext returned NULL: %s\n", alGetError());
		}
		else
		{
			alcMakeContextCurrent(context);
			alcProcessContext(context);
			alutInit(&argc, argv);
			Audio::Sound::initGlobal();
			Audio::Stream::initGlobal();
		}
	}
	GL::Plxcompat::plx_mat3d_init(640, 480);
	return Hid::init();
}

void shutdown() {
	Hid::shutdown();
}

void setName(const char *windowName, const char *iconName)
{
	SDL_WM_SetCaption(windowName, iconName);
}

namespace GL {
void showCursor(bool visible) {
	SDL_ShowCursor(visible == true);
}
}

}
