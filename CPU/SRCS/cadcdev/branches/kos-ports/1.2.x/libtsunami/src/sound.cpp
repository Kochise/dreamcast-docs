/*      
   Tsunami for KallistiOS ##version##
        
   sound.cpp

   (c)2002 Dan Potter
*/

#include <tsu/sound.h>

CVSID("$Id: sound.cpp,v 1.3 2003/04/24 02:57:20 bardtx Exp $");

int Sound::m_default_vol = 240;

Sound::Sound(const char *fn) {
	m_index = SFXHND_INVALID;
	if (!loadFromFile(fn))
		assert( false );
}

Sound::Sound() {
	m_index = SFXHND_INVALID;
}

Sound::~Sound() {
	if (m_index != SFXHND_INVALID)
		snd_sfx_unload(m_index);
}

void Sound::play() {
	play(m_default_vol, 0x80);
}

void Sound::play(int vol) {
	play(vol, 0x80);
}

void Sound::play(int vol, int pan) {
	snd_sfx_play(m_index, vol, pan);
}

bool Sound::loadFromFile(const char *fn) {
	if (m_index != SFXHND_INVALID)
		snd_sfx_unload(m_index);
	m_index = snd_sfx_load(fn);
	if (m_index == SFXHND_INVALID) {
		dbglog(DBG_WARNING, "Sound::loadFromFile: Can't load '%s'\n", fn);
		return false;
	} else
		return true;
}

// Set the default volume value
void Sound::setDefaultVolume(int vol) {
	m_default_vol = vol;
}
        
