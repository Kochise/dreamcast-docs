/*
   Tiki

   sound.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/sound.h"
#include "Tiki/file.h"

#include <string.h>

using namespace Tiki::Audio;

TIKI_OBJECT_NAME(Sound)
TIKI_OBJECT_BEGIN(Object, Sound)
TIKI_OBJECT_END(Sound)

//////////////////////////////////////////////////////////////////////////////////////////

float Sound::m_default_vol = 0.9f;

bool Sound::initGlobal() {
	return true;
}

void Sound::shutdownGlobal() {
	stopAll();
}

void Sound::stop(int ch) {
	snd_sfx_stop(ch);
}

void Sound::stopAll() {
	snd_sfx_stop_all();
}

//////////////////////////////////////////////////////////////////////////////////////////

Sound::Sound(const string & fn) {
	handle = SFXHND_INVALID;
	
	if (!loadFromFile(fn))
		assert( false );
}

Sound::Sound() {
	handle = SFXHND_INVALID;
}

Sound::~Sound() {
	if(handle != SFXHND_INVALID) {
		snd_sfx_unload(handle);
	}
}
	
bool Sound::loadFromFile(const string & fn) {
	if(handle != SFXHND_INVALID) {
		snd_sfx_unload(handle);
	}
	Debug::printf("Sound::loadFromFile: loading effect %s\n", fn.c_str());

	handle = snd_sfx_load(fn.c_str());

	return (handle != SFXHND_INVALID);
}

// Set the default volume value
void Sound::setDefaultVolume(float vol) {
	m_default_vol = vol;
}
        
int Sound::play() {
	return play(m_default_vol, 0x80);
}

int Sound::play(float vol) {
	return play(vol, 0x80);
}

int Sound::play(float vol, float pan) {
	return snd_sfx_play(handle, (int)(vol * 255), (int)(pan * 255));
}

void Sound::play(int ch, float vol, float pan) {
	snd_sfx_play(handle, (int)(vol * 255), (int)(pan * 255));
}

