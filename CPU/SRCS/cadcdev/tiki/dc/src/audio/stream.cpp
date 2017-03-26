/*
   Tiki

   stream.cpp

	 Copyright (C)2007 Sam Steele
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/stream.h"

#include <string.h>
#include <vector>

using namespace Tiki::Audio;
using namespace Tiki::Thread;

Stream *streams[SND_STREAM_MAX];
static uint8 pcm_buffer[SND_STREAM_BUFFER_MAX+16384];

void *cbk(snd_stream_hnd_t hnd, int size, int * size_out) {
	int pcm_decoded = 0;

	/* Check if the callback requests more data than our buffer can hold */
	if (size > SND_STREAM_BUFFER_MAX)
		size = SND_STREAM_BUFFER_MAX;
	
	pcm_decoded = size / (2 * streams[(int)hnd]->getChannelCount());
	Stream::GetDataResult rv = streams[(int)hnd]->getData((uint16 *)pcm_buffer,&pcm_decoded);		
	pcm_decoded *= (2 * streams[(int)hnd]->getChannelCount());
	if(rv == Stream::GDError || rv == Stream::GDEOS) {
		*size_out = 0;
		return NULL;
	} else {
		*size_out = pcm_decoded;
		return pcm_buffer;		
	}
}

TIKI_OBJECT_NAME(Stream)
TIKI_OBJECT_BEGIN(Object, Stream)
	TIKI_OBJECT_RECEIVER("start", Stream::objectStart)
	TIKI_OBJECT_RECEIVER("stop", Stream::objectStop)
TIKI_OBJECT_END(Stream)


bool Stream::initGlobal() {
	return true;
}

void Stream::shutdownGlobal() {
}

Stream::Stream() {
	// Default our members.
	m_bufSize = SND_STREAM_BUFFER_MAX;
	m_chnCount = 1;
	m_freq = 44100;
	m_queueing = false;
	m_volume = 0.8f;
	m_mutex = new Mutex();
	m_thread = NULL;
	m_threadActive = false;
	m_state = StateStopped;	
}

Stream::~Stream() {
	destroy();
}

bool Stream::create() {
	destroy();
	
	assert( m_state == StateStopped );
	hnd = snd_stream_alloc(cbk,SND_STREAM_BUFFER_MAX);
	streams[hnd] = this;
	
	return true;
}

void Stream::destroy() {
	stop();

	assert( m_state == StateStopped );	
}

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
	if (m_state != StateStopped)
		return;
	
	m_state = StatePlaying;
	snd_stream_volume(hnd,int(255.0f * m_volume));
	printf("Starting audio thread...\n");
	m_threadActive = true;
	m_thread = new Thread::Thread(alThreadProc, this);
}

void Stream::stop() {
	if (m_state == StateStopped)
		return;

	assert( m_thread );
	m_threadActive = false;
	printf("Joining audio thread...\n");
	m_thread->join();
	delete m_thread;
	m_thread = NULL;
}

void Stream::pause() {
	if (m_state != StatePlaying)
		return;
	
	m_state = StatePaused;
}

void Stream::resume() {
	AutoLock lock(m_mutex);
}

void Stream::setVolume(float vol) {
	AutoLock lock(m_mutex);

	m_volume = vol;
}

bool Stream::isPlaying() {
	return m_state == StatePlaying;
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
	int stat;
	
	printf("Starting stream...\n");
	snd_stream_start(hnd,m_freq,m_chnCount-1);

	while (m_threadActive) {
		AutoLock lock(m_mutex);
		if((stat = snd_stream_poll(hnd)) < 0) {
			printf("Stopping, status: %d\n",stat);
			m_threadActive = false;
		}
		lock.unlock();
		thd_sleep(50);
	}
	printf("Stopping stream...\n");
	snd_stream_stop(hnd);
	m_state = StateStopped;
	printf("Stream stopped\n");
}

Stream::GetDataResult Stream::getData(uint16 * buffer, int * numSamples) {
	return GDError;
}

