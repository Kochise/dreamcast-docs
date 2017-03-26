/* KallistiOS ##version##

   dc/sound/stream.h
   Copyright (C)2002,2004 Dan Potter

   $Id: stream.h,v 1.6 2003/03/09 01:26:36 bardtx Exp $

*/

#ifndef __DC_SOUND_STREAM_H
#define __DC_SOUND_STREAM_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* The maximum number of streams which can be allocated at once */
#define SND_STREAM_MAX 4

/* The maximum buffer size for a stream */
#define SND_STREAM_BUFFER_MAX 0x10000

/* A stream handle */
typedef int snd_stream_hnd_t;

/* An invalid stream handle */
#define SND_STREAM_INVALID -1

/* Set "get data" callback */
typedef void* (*snd_stream_callback_t)(snd_stream_hnd_t hnd, int smp_req, int * smp_recv);
void snd_stream_set_callback(snd_stream_hnd_t hnd, snd_stream_callback_t cb);

/* Add an effect filter to the sound stream chain. When the stream
   buffer filler needs more data, it starts out by calling the initial
   callback (set above). It then calls each function in the effect
   filter chain, which can modify the buffer and the amount of data
   available as well. Filters persist across multiple calls to _init()
   but will be emptied by _shutdown(). */
typedef void (*snd_stream_filter_t)(snd_stream_hnd_t hnd, void * obj, int hz, int channels, void **buffer, int *samplecnt);
void snd_stream_filter_add(snd_stream_hnd_t hnd, snd_stream_filter_t filtfunc, void * obj);

/* Remove a filter added with the above function */
void snd_stream_filter_remove(snd_stream_hnd_t hnd, snd_stream_filter_t filtfunc, void * obj);

/* Prefill buffers -- do this before calling start() */
void snd_stream_prefill(snd_stream_hnd_t hnd);

/* Initialize stream system */
int snd_stream_init();

/* Shut everything down and free mem */
void snd_stream_shutdown();

/* Allocate and init a stream channel */
snd_stream_hnd_t snd_stream_alloc(snd_stream_callback_t cb, int bufsize);

/* Re-init a stream channel */
int snd_stream_reinit(snd_stream_hnd_t hnd, snd_stream_callback_t cb);

/* Destroy a stream channel */
void snd_stream_destroy(snd_stream_hnd_t hnd);

/* Enable / disable stream queueing */ 
void snd_stream_queue_enable(snd_stream_hnd_t hnd);
void snd_stream_queue_disable(snd_stream_hnd_t hnd);

/* Actually make it go (in queued mode) */
void snd_stream_queue_go(snd_stream_hnd_t hnd);

/* Start streaming */
void snd_stream_start(snd_stream_hnd_t hnd, uint32 freq, int st);

/* Stop streaming */
void snd_stream_stop(snd_stream_hnd_t hnd);

/* Poll streamer to load more data if neccessary */
int snd_stream_poll(snd_stream_hnd_t hnd);

/* Set the volume on the streaming channels */
void snd_stream_volume(snd_stream_hnd_t hnd, int vol);

__END_DECLS

#endif	/* __DC_SOUND_STREAM_H */

