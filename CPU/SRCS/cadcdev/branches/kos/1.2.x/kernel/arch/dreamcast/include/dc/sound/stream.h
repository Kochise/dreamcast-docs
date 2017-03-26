/* KallistiOS ##version##

   dc/sound/stream.h
   (c)2002 Dan Potter

   $Id: stream.h,v 1.6 2003/03/09 01:26:36 bardtx Exp $

*/

#ifndef __DC_SOUND_STREAM_H
#define __DC_SOUND_STREAM_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Set "get data" callback */
void snd_stream_set_callback(void *(*func)(int samples_requested, int *samples_returned));

/* Add an effect filter to the sound stream chain. When the stream
   buffer filler needs more data, it starts out by calling the initial
   callback (set above). It then calls each function in the effect
   filter chain, which can modify the buffer and the amount of data
   available as well. Filters persist across multiple calls to _init()
   but will be emptied by _shutdown(). */
typedef void (*snd_stream_filter_t)(void * obj, int hz, int channels, void **buffer, int *samplecnt);
void snd_stream_filter_add(snd_stream_filter_t filtfunc, void * obj);

/* Remove a filter added with the above function */
void snd_stream_filter_remove(snd_stream_filter_t filtfunc, void * obj);

/* Load sample data from SH-4 ram into SPU ram (auto-allocate RAM) */
uint32 snd_stream_load_sample(const uint16 *src, uint32 len);

/* Dump all loaded sample data */
void snd_stream_dump_samples();

/* Prefill buffers -- do this before calling start() */
void snd_stream_prefill();

/* Initialize stream system */
int snd_stream_init(void* (*callback)(int, int *));

/* Shut everything down and free mem */
void snd_stream_shutdown();

/* Enable / disable stream queueing */ 
void snd_stream_queue_enable();
void snd_stream_queue_disable();

/* Actually make it go (in queued mode) */
void snd_stream_queue_go();

/* Start streaming */
void snd_stream_start(uint32 freq, int st);

/* Stop streaming */
void snd_stream_stop();

/* Poll streamer to load more data if neccessary */
int snd_stream_poll();

/* Set the volume on the streaming channels */
void snd_stream_volume(int vol);

__END_DECLS

#endif	/* __DC_SOUND_STREAM_H */

