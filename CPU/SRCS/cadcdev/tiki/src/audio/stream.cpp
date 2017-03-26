/*
   Tiki

   stream.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/stream.h"
#include "Tiki/tikitime.h"

#include <string.h>

using namespace Tiki::Audio;
using namespace Tiki::Thread;

TIKI_OBJECT_NAME(Stream)
TIKI_OBJECT_BEGIN(Object, Stream)
	TIKI_OBJECT_RECEIVER("start", Stream::objectStart)
	TIKI_OBJECT_RECEIVER("stop", Stream::objectStop)
TIKI_OBJECT_END(Stream)

/*

This module uses CoreAudio to stream data out to the sound output
device. It's based loosely on the KOS snd_stream module.

*/

bool Stream::initGlobal() {
	return true;
}

void Stream::shutdownGlobal() {
}

Stream::Stream() {
	// Default our members.
	m_bufSize = 0x4000;
	m_chnCount = 2;
	m_freq = 44100;
	m_queueing = false;
	m_volume = 0.8f;
	m_mutex = new Mutex();
	
	m_source = 0;
	m_thread = NULL;
	m_threadActive = false;
	m_state = StateStopped;
}

Stream::~Stream() {
	destroy();
}

bool Stream::create() {
	AutoLock lock(m_mutex);

	destroy();
	
	assert( m_state == StateStopped );

	alGenSources(1, &m_source);
	check();
	alGenBuffers(2, m_buffers);
	check();
	
	alSource3f(m_source, AL_POSITION,	0.0, 0.0, 0.0);
	check();
	alSource3f(m_source, AL_VELOCITY,	0.0, 0.0, 0.0);
	check();
	alSource3f(m_source, AL_DIRECTION,	0.0, 0.0, 0.0);
	check();
	alSourcef (m_source, AL_ROLLOFF_FACTOR,	0.0);
	check();
	alSourcei (m_source, AL_SOURCE_RELATIVE, AL_TRUE);
	check();
	
	return true;
}

void Stream::destroy() {
	AutoLock lock(m_mutex);

	stop();

	assert( m_state == StateStopped );

	if (m_source) {
		alDeleteSources(1, &m_source);
		alDeleteBuffers(1, m_buffers);
		m_source = 0;
	}
}

// virtual void filter(int freq, int chncount, void * buffer, int smpcnt) { }

void Stream::filterAdd(Filter * f) {
	AutoLock lock(m_mutex);

	m_filters.insertTail(f);
}

void Stream::filterRemove(Filter * f) {
	AutoLock lock(m_mutex);

	m_filters.del(f);
}

void Stream::setQueueing(bool isQueued) {
	AutoLock lock(m_mutex);

	m_queueing = isQueued;
}

void Stream::setFrequency(int freq) {
	AutoLock lock(m_mutex);

	m_freq = freq;
}

void Stream::setChannelCount(int chncount) {
	AutoLock lock(m_mutex);

	m_chnCount = chncount;
}

void Stream::start() {
	AutoLock lock(m_mutex);

	if (!m_source)
		return;
	if (m_state != StateStopped)
		return;

	if (m_chnCount == 1)
		m_format = AL_FORMAT_MONO16;
	else
		m_format = AL_FORMAT_STEREO16;

	if (!fillBuffer(m_buffers[0]) || !fillBuffer(m_buffers[1]))
		return;
	
	alSourceQueueBuffers(m_source, 2, m_buffers);
	check();
	alSourcePlay(m_source);
	check();
	
	setVolume(m_volume);
	
	m_state = StatePlaying;
	
	m_threadActive = true;
	m_thread = new Thread::Thread(alThreadProc, this);
}

void Stream::stop() {
	if (m_state == StateStopped)
		return;

	assert( m_thread );
	m_threadActive = false;
	m_thread->join();
	delete m_thread;
	m_thread = NULL;
	
	alSourceStop(m_source);

	int queued;
        alGetSourcei(m_source, AL_BUFFERS_QUEUED, &queued);
    
	while (queued--) {
		ALuint buffer;
		alSourceUnqueueBuffers(m_source, 1, &buffer);
		check();
	}

	m_state = StateStopped;
}

void Stream::pause() {
	AutoLock lock(m_mutex);

	if (!m_source)
		return;
	if (m_state != StatePlaying)
		return;
	
	alSourcePause(m_source);
	m_state = StatePaused;
}

void Stream::resume() {
	AutoLock lock(m_mutex);

	if (!m_source)
		return;
	if (m_state != StatePaused)
		return;
	
	alSourcePlay(m_source);
	m_state = StatePlaying;
}

void Stream::setVolume(float vol) {
	AutoLock lock(m_mutex);

	m_volume = vol;

	alSourcef(m_source, AL_GAIN, vol);
}

bool Stream::isPlaying() {
	AutoLock lock(m_mutex);

	ALenum state;
	alGetSourcei(m_source, AL_SOURCE_STATE, &state);

	return state == AL_PLAYING;
}

int Stream::objectStart(Object * /*from*/, Object * /*arg*/) {
	start(); return 0;
}

int Stream::objectStop(Object * /*from*/, Object * /*arg*/) {
	stop(); return 0;
}


void Stream::processFilters(void * buffer, int smpcnt) {
}

void * Stream::alThreadProc(void * u) {
	Stream * us = (Stream *)u;
	us->threadProc();
	return NULL;
}

void Stream::threadProc() {
	while (m_threadActive) {
		AutoLock lock(m_mutex);

		int processed;
		alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);
		check();
		while (processed--) {
			ALuint buffer;
			alSourceUnqueueBuffers(m_source, 1, &buffer);
			check();

			if (!fillBuffer(buffer))
				return;

			alSourceQueueBuffers(m_source, 1, &buffer);
			check();
		}
		
		lock.unlock();
		Time::sleep(100 * 1000);
	}
}

#if TIKI_PLAT == TIKI_WIN32
#	include <malloc.h>
#	define alloca _alloca
#endif

bool Stream::fillBuffer(ALuint buffer) {
	// Thanks to VC++ we have to do this with alloca.
	void * memfoo = alloca( m_bufSize * m_chnCount * 2 );
	uint16 * pcm = (uint16 *)memfoo;
	// uint16 pcm[m_bufSize * m_chnCount];

	// Call down to get the next chunk of data.
	int recvd = m_bufSize;
	GetDataResult rv = getData(pcm, &recvd);
	if (rv == GDEOS || rv == GDError) {
		alSourceStop(m_source);
		return false;
	}
	processFilters(pcm, recvd);
	alBufferData(buffer, m_format, pcm, m_bufSize * m_chnCount * 2, m_freq);
	check();
	
	return true;
}

void Stream::check() {
	int error = alGetError();

	if (error != AL_NO_ERROR) {
		Debug::printf("Stream::check: OpenAL Error %x\n", error);
	}
}


Stream::GetDataResult Stream::getData(uint16 * buffer, int * numSamples) {
	return GDError;
}














