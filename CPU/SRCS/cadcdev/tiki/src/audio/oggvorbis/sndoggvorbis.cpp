/*
  Tiki

  OggVorbis Interface
  Based on KOS "Ogg/Vorbis Decoder Library"

  Copyright (C)2001,2002 Thorsten Titze
  Copyright (C)2002,2003,2004 Dan Potter
  Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"

#include <assert.h>
#include <string.h>
#include <machine/endian.h>

#include <vorbis/vorbisfile.h>
#include "misc.h"

#include "Tiki/stream.h"
#include "Tiki/oggvorbis.h"

using namespace Tiki::Audio;

/* Enable this #define to do timing testing */
/* #define TIMING_TESTS */

VorbisStream::VorbisStream() {
	// complete buffer + 16KB safety
	m_pcm_buffer = new uint8[BUF_SIZE+16384];
	
	// place we write to
	m_pcm_ptr = m_pcm_buffer;

	// bytes in buffer
	m_pcm_count = 0;
	
	// number of bytes the sndstream driver grabbed at last callback
	m_last_read = 0;
	
	m_vf = new OggVorbis_File;
	m_info = new VorbisFile_info_t;
	
	m_loop = false;
	m_bitrateint = 0;
	m_current_section = 0;
	
	clearComments();
}

VorbisStream::~VorbisStream() {
	stop();
	delete[] m_pcm_buffer;
	delete m_vf;
	delete m_info;
}

VorbisStream::GetDataResult VorbisStream::getData(uint16 * buffer, int * numSamples) {
	int sizeWant = *numSamples * 2 * m_chnCount;
	int sizeOut;
	void * d = internalCallback(sizeWant, &sizeOut);
	*numSamples = sizeOut / (2 * m_chnCount);
	if (!sizeOut)
		return GDEOS;
	memcpy(buffer, d, sizeOut);
	if (sizeOut < sizeWant)
		return GDEOS;
	else
		return GDSuccess;
}

void * VorbisStream::internalCallback(int size, int * size_out) {
#ifdef TIMING_TESTS
	int decoded_bytes = 0;
	uint64 stime;
#endif
	
	// printf("sndoggvorbis: callback requested %d bytes\n",size);

	/* Check if the callback requests more data than our buffer can hold */
	if (size > BUF_SIZE)
		size = BUF_SIZE;

#ifdef TIMING_TESTS
	stime = Time::gettime();
#endif

	/* Shift the last data the AICA driver took out of the PCM Buffer */
	if (m_last_read > 0) {
		m_pcm_count -= m_last_read;
		if (m_pcm_count < 0)
			m_pcm_count=0; /* Don't underrun */
		/* printf("memcpy(%08x, %08x, %d (%d - %d))\n",
			pcm_buffer, pcm_buffer+last_read, pcm_count-last_read, pcm_count, last_read); */
		memcpy(m_pcm_buffer, m_pcm_buffer+m_last_read, m_pcm_count);
		m_pcm_ptr = m_pcm_buffer + m_pcm_count;
	}
	
	// What's our endianness?
#if BYTE_ORDER == BIG_ENDIAN
	int endian = 1;
#else
	int endian = 0;
#endif
	
	/* If our buffer has not enough data to fulfill the callback decode 4 KB
	 * chunks until we have enough PCM samples buffered
	 */
	// printf("sndoggvorbis: fill buffer if not enough data\n");
	long pcm_decoded = 1;
	while(m_pcm_count < size) {
		//int pcm_decoded =  VorbisFile_decodePCMint8(v_headers, pcm_ptr, 4096);
		pcm_decoded = ov_read(m_vf, (char *)m_pcm_ptr, 4096, endian, 2, 1, &m_current_section);

		/* Are we at the end of the stream? If so and looping is
		   enabled, then go ahead and seek back to the first. */
		if (pcm_decoded == 0 && m_loop) {
			/* Seek back */
			if (ov_raw_seek(m_vf, 0) < 0) {
				Debug::printf("oggvorbis: can't ov_raw_seek to the beginning!\n");
			} else {
				/* Try again */
				pcm_decoded = ov_read(m_vf, (char *)m_pcm_ptr, 4096, endian, 2, 1, &m_current_section);
			}
		}
		
#ifdef TIMING_TESTS
		decoded_bytes += pcm_decoded;
#endif
		// printf("pcm_decoded is %d\n", pcm_decoded);
		m_pcm_count += pcm_decoded;
		m_pcm_ptr += pcm_decoded;

		//if (pcm_decoded == 0 && check_for_reopen() < 0)
		//	break;
		if (pcm_decoded == 0)
			break;
	}
	if (m_pcm_count > size)
		*size_out = size;
	else
		*size_out = m_pcm_count;

	/* Let the next callback know how many bytes the last callback grabbed
	 */
	m_last_read = *size_out;

#ifdef TIMING_TESTS
	if (decoded_bytes != 0) {
		uint64 etime = Time::gettime();
		int t = (int)(etime - stime);
		printf("%dms for %d bytes (%.2fms / byte)\n", t, decoded_bytes, t*1.0f/decoded_bytes);
	}
#endif

	// printf("sndoggvorbis: callback: returning\n");

	return m_pcm_buffer;
}

/* Wait for the song to be queued */
void VorbisStream::queueWait() {
#if 0
	assert(sndoggvorbis_queue_wait);

	/* Make sure we've loaded ok */
	while (sndoggvorbis_status != STATUS_QUEUED)
		thd_pass();
#endif
}

/* Queue the song to start if it's in QUEUED */
void VorbisStream::queueGo() {
#if 0
	/* Make sure we're ready */
	sndoggvorbis_queue_wait();

	/* Tell it to go */
	sndoggvorbis_status = STATUS_STARTING;
	sem_signal(sndoggvorbis_halt_sem);
#endif
}

/* getter and setter functions for information access 
 */

void VorbisStream::setBitrateInterval(int interval) {
	m_bitrateint=interval;
}

/* sndoggvorbis_getbitrate()
 *
 * returns the actual bitrate of the playing stream. 
 *
 * NOTE:
 * The value returned is only actualized every once in a while !
 */
long VorbisStream::getBitrate() {
	return m_info->actualbitrate;
}

long VorbisStream::getPosition() {
	return m_info->actualposition;
}

/* The following getters only return the contents of specific comment
 * fields. It is thinkable that these return something like "NOT SET"
 * in case the specified field has not been set !
 */
string VorbisStream::getArtist() { return m_info->artist; }
string VorbisStream::getTitle() { return m_info->title; }
string VorbisStream::getGenre() { return m_info->genre; }
string VorbisStream::getCommentByName(const string & commentfield) {
	Debug::printf("oggvorbis: getcommentbyname not implemented for tremor yet\n");
	return NULL;
}

void VorbisStream::clearComments() {
	m_info->artist = "";
	m_info->title = "";
	m_info->album = "";
	m_info->tracknumber = "";
	m_info->organization = "";
	m_info->description = "";
	m_info->genre = "";
	m_info->date = "";
	m_info->location = "";
	m_info->copyright = "";
	m_info->isrc = "";
	m_info->filename = "";

	m_info->nominalbitrate = 0;
	m_info->actualbitrate = 0;

	m_info->actualposition = 0;
}
	
void VorbisStream::stop() {
	if (!isPlaying())
		return;

	Stream::stop();
	ov_clear(m_vf);

	/* Reset our PCM buffer */
	m_pcm_count = 0;
	m_last_read = 0;
	m_pcm_ptr = m_pcm_buffer;
				
	m_lastfilename = "";
	clearComments();
}

static string vc_get_comment(vorbis_comment * vc, const char *commentfield) {
	int i;
	size_t commentlength = strlen(commentfield);

	for (i=0; i<vc->comments; i++) {
		if (!(strncmp(commentfield, vc->user_comments[i], commentlength))) {
			/* Return adress of comment content but leave out the
			 * commentname= part !
			 */
			return (vc->user_comments[i] + commentlength + 1);
		}
	}
	return "<NOT SET>";
}


/* Same as sndoggvorbis_start, but takes an already-opened file. Once a file is
   passed into this function, we assume that _we_ own it. */
bool VorbisStream::load(FILE *f, bool loop) {
	vorbis_comment *vc;
	
	stop();
	
	Debug::printf("oggvorbis: initializing and parsing ogg\n");

	if(ov_open(f, m_vf, NULL, 0) < 0) {
		Debug::printf("oggvorbis: input does not appear to be an Ogg bitstream\n");
		return false;
	}
	
	m_loop = loop;
	m_lastfilename = "<stream>";

	/* Grab all standard comments from the file
	 * (based on v-comment.html found in OggVorbis source packages
	 */
	vc = ov_comment(m_vf, -1);
	if (vc == NULL) {
		Debug::printf("oggvorbis: can't obtain bitstream comments\n");
		clearComments();
	} else {
		m_info->artist = vc_get_comment(vc, "artist");
		m_info->title = vc_get_comment(vc, "title");
		m_info->version = vc_get_comment(vc, "version");
		m_info->album = vc_get_comment(vc, "album");
		m_info->tracknumber = vc_get_comment(vc, "tracknumber");
		m_info->organization = vc_get_comment(vc, "organization");
		m_info->description = vc_get_comment(vc, "description");
		m_info->genre = vc_get_comment(vc, "genre");
		m_info->date = vc_get_comment(vc, "date");
		m_info->filename = m_lastfilename;
		Debug::printf("oggvorbis: Loaded %s - %s\n", m_info->artist.c_str(), m_info->title.c_str());
	}

	vorbis_info * vi = ov_info(m_vf, -1);

	setFrequency(vi->rate);
	setChannelCount(vi->channels);

	Stream::create();

	return true;
}

bool VorbisStream::load(const string & filename, bool loop) {
	FILE * f;

	f = fopen(filename.c_str(), "rb");
	if (!f) {
		Debug::printf("oggvorbis: couldn't open source file \"%s\"!\n", filename.c_str());
		return false;
	}

	return load(f, loop);
}
