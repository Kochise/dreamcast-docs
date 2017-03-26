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

/*

This port of the snd_sfx manager uses OpenAL to do its work. For simplicity's
sake we just generate CHAN_CNT sources at start time, and one buffer per loaded
sound effect. The rest works pretty much the same as the old snd_sfx API.

*/

using namespace Tiki::Audio;

TIKI_OBJECT_NAME(Sound)
TIKI_OBJECT_BEGIN(Object, Sound)
TIKI_OBJECT_END(Sound)

static void check() {
	ALuint err = alGetError();
	if (err != AL_NO_ERROR) {
		Debug::printf("Sound::check: OpenAL Error %x\n", err);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

// Our sound effect channels.
#define CHAN_CNT 16
static ALuint channels[CHAN_CNT];
static int nextChan = 0;

bool Sound::initGlobal() {
	check();
	memset(channels, 0, sizeof(channels));
	alGenSources(CHAN_CNT, channels);
	check();
	nextChan = 0;

	return true;
}

void Sound::shutdownGlobal() {
	check();
	stopAll();
	alDeleteSources(CHAN_CNT, channels);
	check();
	memset(channels, 0, sizeof(channels));
}

// XXX Threads?
static int findChan() {
	int rv = nextChan++;
	nextChan = nextChan % CHAN_CNT;
	
	return rv;
}

void Sound::stop(int ch) {
	assert( ch >= 0 && ch < CHAN_CNT );
	check();
	alSourceStop(channels[ch]);
	check();
}

void Sound::stopAll() {
	for (int i=0; i<CHAN_CNT; i++)
		stop(i);
}

//////////////////////////////////////////////////////////////////////////////////////////

float Sound::m_default_vol = 0.9f;

Sound::Sound(const string & fn) {
	m_stereo = false;
	m_buffer = 0;

	if (!loadFromFile(fn))
		assert( false );
}

Sound::Sound() {
	m_stereo = false;
	m_buffer = 0;
}

Sound::~Sound() {
	check();
	if (m_buffer) {
		alDeleteBuffers(1, &m_buffer);
		check();
	}
}

bool Sound::loadFromFile(const string & fn) {
	check();

	if (m_buffer) {
		alDeleteBuffers(1, &m_buffer); m_buffer = 0;
		check();
	}

	Debug::printf("Sound::loadFromFile: loading effect %s\n", fn.c_str());

	alGenBuffers(1, &m_buffer);
	check();

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	
	char magic[4];
	uint32	len, hz;
	uint16	*tmp, chn, bitsize, fmt;
	
	File wavFile(fn,"r");
	wavFile.seek(8, SEEK_SET);
	wavFile.read(magic, 4);
	
	if(strncmp(magic, "WAVE", 4)) {
		Debug::printf("Sound::loadFromFile: file is not RIFF WAVE\n");
		wavFile.close();
		alDeleteBuffers(1, &m_buffer); m_buffer = 0;
		return false;
	}
	
	/* Read WAV header info */
	wavFile.seek(0x14, SEEK_SET);
	wavFile.readle16(&fmt, 1);
	wavFile.readle16(&chn, 1);
	wavFile.readle32(&hz, 1);
	wavFile.seek(0x22, SEEK_SET);
	wavFile.readle16(&bitsize, 1);
	
	/* Read WAV data */
	wavFile.seek(0x28, SEEK_SET);
	wavFile.readle32(&len, 1);

	Debug::printf("WAVE file is %s, %dHZ, %d bits/sample, %d bytes total, format %d\n",
		chn==1 ? "mono" : "stereo", hz, bitsize, len, fmt);

	if(chn == 1 && bitsize == 8) {
		format = AL_FORMAT_MONO8;
	} else if(chn == 1 && bitsize == 16) {
		format = AL_FORMAT_MONO16;
	} else if(chn == 2 && bitsize == 8) {
		format = AL_FORMAT_STEREO8;
	} else if(chn == 2 && bitsize == 16) {
		format = AL_FORMAT_STEREO16;
	} else {
		Debug::printf("Sound::loadFromFile: unsupported bitsize / channel combination\n");
		wavFile.close();
		alDeleteBuffers(1, &m_buffer); m_buffer = 0;
		return false;
	}

	size = (ALsizei)len;
	freq = (ALsizei)hz;

	data = malloc(len);
	if(bitsize == 8) {
		wavFile.read(data, len);
	} else { //byte swapping may be needed, depending on host endianness
		for(int i = 0; i < size; i+=2) {
			wavFile.readle16((uint8 *)data + i, 1);
		}
	}	

	alBufferData(m_buffer, format, data, size, freq);
	check();
	
	free(data);
	wavFile.close();
	check();

	if (format == AL_FORMAT_MONO16 || format == AL_FORMAT_MONO8)
		m_stereo = false;
	else
		m_stereo = true;

	return true;
}

// Set the default volume value
void Sound::setDefaultVolume(float vol) {
	m_default_vol = vol;
}
        
int Sound::play() {
	return play(m_default_vol, 0.0f);
}

int Sound::play(float vol) {
	return play(vol, 0.0f);
}

int Sound::play(float vol, float pan) {
	int ch = findChan();
	if (ch < 0) {
		Debug::printf("Sound::play: no channels!\n");
		return -1;
	} else {
		play(ch, vol, pan);
		return ch;
	}
}

void Sound::play(int ch, float vol, float pan) {
	check();

	assert( ch >= 0 && ch < CHAN_CNT );
	ALuint src = channels[ch];
	
	alSourceStop(src);
	check();
	
	// For some bizarre reason this always causes an a003 (INVALID_VALUE) for
	// some sound effects.. and yet it still works.
	alSourcei (src, AL_BUFFER,   m_buffer);
	alGetError();
	// check();
	alSourcef (src, AL_PITCH,    1.0f);
	check();
	alSourcef (src, AL_GAIN,     vol);
	check();
	alSource3f(src, AL_VELOCITY, 0.0, 0.0, 0.0);
	check();
	alSourcei (src, AL_LOOPING,  AL_FALSE);
	check();
	alSource3f(src, AL_DIRECTION, 0.0, 0.0, 0.0);
	check();
	alSourcef (src, AL_ROLLOFF_FACTOR, 0.0);
	check();
	alSourcei (src, AL_SOURCE_RELATIVE, AL_TRUE);
	check();

	// If this is a stereo sample, ignore panning. Otherwise move the
	// sound left or right.
	if (m_stereo)
		alSource3f(src, AL_POSITION, 0.0, 0.0, 0.0);
	else
		alSource3f(src, AL_POSITION, pan, 0.0, 0.0);
	check();
	
	alSourcePlay(src);
	check();
}












