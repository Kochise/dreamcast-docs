/* KallistiOS ##version##

   dc/spu.h
   (c)2000-2001 Dan Potter

   $Id: spu.h,v 1.7 2002/10/17 06:10:39 bardtx Exp $

*/

#ifndef __DC_SPU_H
#define __DC_SPU_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Waits for the sound FIFO to empty */
void spu_write_wait();

/* memcpy and memset designed for sound RAM; for addresses, don't
   bother to include the 0xa0800000 offset that is implied. 'length'
   must be a multiple of 4, but if it is not it will be rounded up. */
void spu_memload(uint32 to, void *from, int length);
void spu_memread(void *to, uint32 from, int length);
void spu_memset(uint32 to, uint32 what, int length);

/* DMA copy from SH-4 RAM to SPU RAM; length must be a multiple of 32,
   and the source and destination addresses must be aligned on 32-byte
   boundaries. */
void spu_memload_dma(uint32 dest, void *from, int length);

/* Enable/disable the SPU; note that disable implies reset of the
   ARM CPU core. */
void spu_enable();
void spu_disable();

/* Set CDDA volume: values are 0-15 */
void spu_cdda_volume(int left_volume, int right_volume);

/* Set CDDA panning: values are 0-31, 16=center */
void spu_cdda_pan(int left_pan, int right_pan);

/* Set master volume (0..15) and mono/stereo settings */
void spu_master_mixer(int volume, int stereo);

/* Initialize the SPU; by default it will be left in a state of
   reset until you upload a program. */
int spu_init();

/* Shutdown SPU */
int spu_shutdown();

/* These two are seperate because they have to be done at a different time */
int spu_dma_init();
void spu_dma_shutdown();

__END_DECLS

#endif	/* __DC_SPU_H */

