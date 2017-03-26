/*      
   Tsunami for KallistiOS ##version##
        
   sound.h

   (c)2002 Dan Potter

   $Id: sound.h,v 1.3 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_SOUND_H
#define __TSUNAMI_SOUND_H

#include "refcnt.h"

#include <dc/sound/sfxmgr.h>

class Sound : public RefCnt {
public:
	Sound(const char * fn);
	Sound();
	virtual ~Sound();

	// Load a sound from a file for use in this object.
	bool loadFromFile(const char *fn);

	// Play the sound effect with volume 240 and panning 0x80.
	void play();

	// Play with specified volume and panning 0x80.
	void play(int vol);

	// Play with specified volume and panning.
	void play(int vol, int pan);

	// Set the default volume value
	static void setDefaultVolume(int vol);

private:

	sfxhnd_t	m_index;

	static int	m_default_vol;
};

#endif	/* __TSUNAMI_SOUND_H */
