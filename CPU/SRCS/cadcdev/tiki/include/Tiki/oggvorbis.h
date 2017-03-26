/* 
   Tiki

   sndoggvorbis.h
   Copyright (C)2001 Thorsten Titze
   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC

   An Ogg/Vorbis player library using Stream and the official Xiphophorus
   libogg and libvorbis libraries.

*/

#ifndef __TIKI_OGGVORBIS_H
#define __TIKI_OGGVORBIS_H

#include <stdio.h>
#include "Tiki/stream.h"

struct OggVorbis_File;
struct VorbisFile_info_t;

namespace Tiki {
namespace Audio {

class VorbisStream : public Stream {
public:
	VorbisStream();
	virtual ~VorbisStream();

	// Prime this object using the named OGG file.
	bool load(const string & filename, bool loop);
	
	// Same as the other load(), but takes an opened FILE *. Note that
	// we assume *we* own this file after you pass it in.
	bool load(FILE * f, bool loop);

	virtual void stop();

	void setBitrateInterval(int interval);
	long getBitrate();
	long getPosition();

	string getCommentByName(const string & commentfield);
	string getArtist();
	string getTitle();
	string getGenre();

	/* Enable/disable queued waiting */
	void queueEnable();
	void queueDisable();

	/* Wait for the song to be queued */
	void queueWait();

	/* Queue the song to start if it's in QUEUED */
	void queueGo();

protected:
	virtual GetDataResult getData(uint16 * buffer, int * numSamples);
	void * internalCallback(int size, int * size_out);

	void clearComments();

	bool init();
	void shutdown();

	void mainLoop();
	void waitStart();
	
	static const int BUF_SIZE = 65536;
	uint8			* m_pcm_buffer, * m_pcm_ptr;
	int32			m_pcm_count, m_last_read;
	OggVorbis_File		* m_vf;
	VorbisFile_info_t	* m_info;
	bool			m_loop;
	int			m_bitrateint;
	string			m_lastfilename;
	int			m_current_section;
};

}
}

#endif	/* __TIKI_OGGVORBIS_H */

