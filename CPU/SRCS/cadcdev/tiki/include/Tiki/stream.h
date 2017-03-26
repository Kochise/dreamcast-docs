/*
   Tiki

   stream.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_STREAM_H
#define __TIKI_STREAM_H

#if TIKI_PLAT == TIKI_OSX
#	include <OpenAL/al.h>
#endif	// TIKI_PLAT==TIKI_OSX
#if TIKI_PLAT == TIKI_SDL
#	include <AL/al.h>
#endif	// TIKI_PLAT==TIKI_SDL
#if TIKI_PLAT == TIKI_WIN32
#	include <al.h>
#endif	// TIKI_PLAT==TIKI_WIN32

#include "Tiki/refcnt.h"
#include "Tiki/list.h"
#include "Tiki/thread.h"
#include "Tiki/object.h"

namespace Tiki {

namespace Thread { class Thread; }

namespace Audio {

// The user should derive from this class to get callbacks for more
// stream data and various other events.
class Stream : public Object {
	// These need to be called around any sort of allocation or
	// access of Stream objects.
public:
	static bool initGlobal();
	static void shutdownGlobal();

	// Constructor/Destructor
public:
	TIKI_OBJECT_DECLS(Stream)
	TIKI_OBJECT_ACCEPTS("start")
	TIKI_OBJECT_ACCEPTS("stop")

	Stream();
	virtual ~Stream();
	
	// You must call these to actually create/destroy the stream. Destroy will
	// be called on destruction if needed though. Note: specialized stream
	// implementations may do this for you.
	bool create();
	void destroy();
	
	// Filters -- these let you do things to the audio stream before it
	// hits the output channel.
public:
	class Filter : public RefCnt {
	public:
		Filter() { }
		virtual ~Filter() { }
		
		virtual void filter(int freq, int chncount, void * buffer, int smpcnt) { }
	};
	void filterAdd(Filter * f);
	void filterRemove(Filter * f);
protected:
	List<Filter>	m_filters;

	// Basic stream functions. Some of these are made virtual so that
	// specialized versions can do other things too.
public:
	void	setQueueing(bool isQueued);
	void	setFrequency(int freq);
	void	setChannelCount(int chncount);
	int getChannelCount() { return m_chnCount; }
	virtual void	start();
	virtual void	stop();
	virtual void	pause();
	virtual void	resume();
	virtual void	setVolume(float vol);	// 0..1
	
	virtual bool	isPlaying();

protected:
	int	objectStart(Object * from, Object * arg);
	int	objectStop(Object * from, Object * arg);

public:
	// Your subclass must override this to provide data for the stream. When
	// this is called, you should try to place numSamples samples into buffer.
	// Return the disposition of the stream, and place the actual number of
	// samples returned back in the numSamples parameter. Note that the number
	// of 16-bit words placed there will be numSamples*numChannels. If you
	// return -1, the stream is considered completed. The endianness of the
	// samples should match the host platform (until we can find a way to make
	// OpenAL deal with one endianness).
	enum GetDataResult {
		GDSuccess,		// A full buffer was returned
		GDError,		// An error occured, and the buffer is in an indeterminate state
		GDEOS			// The buffer may be partially filled, but the stream has finished.
	};
	virtual	GetDataResult getData(uint16 * buffer, int * numSamples);

protected:
	void	processFilters(void * buffer, int smpcnt);
	void	sepData(void * buffer, int len, bool stereo, int16 * outl, int16 * outr);


protected:
	int		m_bufSize;	// Buffer size allocated for this stream (bytes)
	int		m_chnCount;	// Channel count
	int		m_freq;		// Playback frequency
	float		m_volume;	// Current volume (0..1)
	bool		m_queueing;	// Is stream queueing enabled?

	// Mutex for accessing shared structs and audio "hardware"
	RefPtr<Thread::Mutex>	m_mutex;

	enum State {
		StateStopped,
		StatePlaying,
		StatePaused
	};

	State		m_state;
#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	ALuint		m_buffers[2];
	ALuint		m_source;
	ALenum		m_format;
#else
	
#endif
	Thread::Thread * m_thread;
volatile bool		m_threadActive;

static	void 	*	alThreadProc(void * us);
	void		threadProc();
	void		check();
#if TIKI_PLAT != TIKI_DC && TIKI_PLAT != TIKI_NDS
	bool		fillBuffer(ALuint buffer);
#endif

#if TIKI_PLAT == TIKI_DC
private:
	int hnd;
#endif

};


}
}

#endif	// __TIKI_STREAM_H










