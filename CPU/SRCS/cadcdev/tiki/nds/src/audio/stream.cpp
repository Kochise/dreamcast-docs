/*
   Tiki

   stream.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/stream.h"

#include <string.h>

using namespace Tiki::Audio;
using namespace Tiki::Thread;

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
	m_bufSize = 0x4000;
	m_chnCount = 2;
	m_freq = 44100;
	m_queueing = false;
	m_state = StateStopped;
	m_volume = 0.8f;
	m_mutex = new Mutex();
}

Stream::~Stream() {
	destroy();
}

bool Stream::create() {
	AutoLock lock(m_mutex);
	return true;
}

void Stream::destroy() {
	AutoLock lock(m_mutex);
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
	m_state = StatePlaying;
}

void Stream::stop() {
	AutoLock lock(m_mutex);
	m_state = StateStopped;
}

void Stream::pause() {
	AutoLock lock(m_mutex);
	m_state = StatePaused;
}

void Stream::resume() {
	AutoLock lock(m_mutex);
	m_state = StatePlaying;
}

void Stream::setVolume(float vol) {
	AutoLock lock(m_mutex);

	m_volume = vol;
}

bool Stream::isPlaying() {
	AutoLock lock(m_mutex);

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

// "len" is a *sample* count.
void Stream::sepData(void * buffer, int len, bool stereo, int16 * outl, int16 * outr) {
	int16	* sep_buffer[2] = { outl, outr };
	int16	* bufsrc, * bufdst;
	int	cnt;

	if (stereo) {
		bufsrc = (int16*)buffer;
		bufdst = sep_buffer[0];
		cnt = len;
		do {
			*bufdst = *bufsrc;
			bufdst++; bufsrc+=2; cnt--;
		} while (cnt > 0);

		bufsrc = (int16*)buffer; bufsrc++;
		bufdst = sep_buffer[1];
		cnt = len;
		do {
			*bufdst = *bufsrc;
			bufdst++; bufsrc+=2; cnt--;
		} while (cnt > 0);
	} else {
		memcpy(sep_buffer[0], buffer, len * 2);
		memcpy(sep_buffer[1], buffer, len * 2);
	}
}

Stream::GetDataResult Stream::getData(uint16 * buffer, int * numSamples) {
	return GDError;
}

