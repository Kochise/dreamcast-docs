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
}

void Sound::stopAll() {
}

//////////////////////////////////////////////////////////////////////////////////////////

Sound::Sound(const string & fn) {
	if (!loadFromFile(fn))
		assert( false );
}

Sound::Sound() {
}

Sound::~Sound() {
}
	
bool Sound::loadFromFile(const string & fn) {
	return false;
}

// Set the default volume value
void Sound::setDefaultVolume(float vol) {
	m_default_vol = vol;
}
        
int Sound::play() {
	return -1;
}

int Sound::play(float vol) {
	return -1;
}

int Sound::play(float vol, float pan) {
	return -1;
}

void Sound::play(int ch, float vol, float pan) {
}

