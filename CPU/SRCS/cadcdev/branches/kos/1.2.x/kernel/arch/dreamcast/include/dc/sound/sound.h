/* KallistiOS ##version##

   dc/sound/sound.h
   (c)2002 Dan Potter

   $Id: sound.h,v 1.2 2002/07/06 07:57:32 bardtx Exp $

*/

#ifndef __DC_SOUND_SOUND_H
#define __DC_SOUND_SOUND_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Allocate a chunk of SPU RAM; we will return an offset into SPU RAM. */
uint32 snd_mem_malloc(size_t size);

/* Free a previously allocated chunk of memory */
void snd_mem_free(uint32 addr);

/* Return the number of bytes available in the largest free chunk */
uint32 snd_mem_available();

/* Reinitialize the pool with the given RAM base offset */
int snd_mem_init(uint32 reserve);

/* Shut down the SPU allocator */
void snd_mem_shutdown();

/* Initialize driver; note that this replaces the AICA program so that
   if you had anything else going on, it's gone now! */
int snd_init();

/* Shut everything down and free mem */
void snd_shutdown();

/* Queue up a request to the SH4->AICA queue; size is in uint32's */
int snd_sh4_to_aica(void *packet, uint32 size);

/* Start processing requests in the queue */
void snd_sh4_to_aica_start();

/* Stop processing requests in the queue */
void snd_sh4_to_aica_stop();

/* Transfer one packet of data from the AICA->SH4 queue. Expects to
   find AICA_CMD_MAX_SIZE dwords of space available. Returns -1
   if failure, 0 for no packets available, 1 otherwise. Failure
   might mean a permanent failure since the queue is probably out of sync. */
int snd_aica_to_sh4(void *packetout);

/* Poll for responses from the AICA. We assume here that we're not
   running in an interrupt handler (thread perhaps, of whoever
   is using us). */
void snd_poll_resp();

__END_DECLS

#endif	/* __DC_SOUND_SOUND_H */

