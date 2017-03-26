/*
   Tiki

   sound.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_SOUND_H
#define __TIKI_SOUND_H

#include "object.h"

#if TIKI_PLAT == TIKI_OSX
#	include <OpenAL/al.h>
#else
#if TIKI_PLAT == TIKI_SDL
#	include <AL/al.h>
#endif
#if TIKI_PLAT == TIKI_WIN32
#	include <al.h>
#endif
#endif

namespace Tiki {
namespace Audio {

class Sound : public Object {
	// These need to be called around any sort of allocation or
	// access of Stream objects.
public:
	static bool initGlobal();
	static void shutdownGlobal();

public:
	TIKI_OBJECT_DECLS(Sound)

	Sound(const string & fn);
	Sound();
	virtual ~Sound();

	// Load a sound from a file for use in this object.
	bool loadFromFile(const string & fn);

	// Play the sound effect with volume 1.0 and panning 0.0. Returns channel id.
	int play();

	// Play with specified volume (0..1) and panning 0.0. Returns channel id.
	int play(float vol);

	// Play with specified volume (0..1) and panning (-1..1). Returns channel id.
	int play(float vol, float pan);
	
	// Play with specified channel id, volume (0..1), and panning (-1..1).
	void play(int chn, float vol, float pan);

	// Stop the specified channel.
static	void stop(int ch);

	// Stop all channels.
static	void stopAll();

	// Set the default volume value 0..1
static	void setDefaultVolume(float vol);

private:
	bool		m_stereo;
#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	ALuint		m_buffer;
#endif
#if TIKI_PLAT == TIKI_DC
	sfxhnd_t	handle;
#endif
#if TIKI_PLAT == TIKI_NDS
#endif

static	float	m_default_vol;
};

}
}

#endif	// __TIKI_SOUND_H
