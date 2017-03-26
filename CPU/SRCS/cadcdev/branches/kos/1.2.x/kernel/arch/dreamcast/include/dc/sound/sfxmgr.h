/* KallistiOS ##version##

   dc/sound/sfxmgr.h
   (c)2002 Dan Potter

   $Id: sfxmgr.h,v 1.6 2003/04/24 03:15:09 bardtx Exp $

*/

#ifndef __DC_SOUND_SFXMGR_H
#define __DC_SOUND_SFXMGR_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Sound effect handle type */
typedef uint32 sfxhnd_t;
#define SFXHND_INVALID 0

/* Load a sound effect from a WAV file and return a handle to it */
sfxhnd_t snd_sfx_load(const char *fn);

/* Unload a single sample */
void snd_sfx_unload(sfxhnd_t idx);

/* Unload all loaded samples and free their SPU RAM */
void snd_sfx_unload_all();

/* Play a sound effect with the given volume and panning; if the sound
   effect is in stereo, the panning is ignored. */
void snd_sfx_play(sfxhnd_t idx, int vol, int pan);

/* Stop all playing sound effects. Doesn't stop channels 0 or 1, which
   are assumed to be for streaming. */
void snd_sfx_stop_all();

__END_DECLS

#endif	/* __DC_SOUND_SFXMGR_H */

