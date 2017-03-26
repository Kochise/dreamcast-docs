/* KallistiOS ##version##

   g2bus.h
   (c)2002 Dan Potter
   
   $Id: g2bus.h,v 1.5 2002/09/13 06:44:41 bardtx Exp $
*/

#ifndef __DC_G2BUS_H
#define __DC_G2BUS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* DMA copy from SH-4 RAM to G2 bus (dir = 0) or the opposite; 
   length must be a multiple of 32,
   and the source and destination addresses must be aligned on 32-byte
   boundaries. If block is non-zero, this function won't return until
   the transfer is complete. If callback is non-NULL, it will be called
   upon completion (in an interrupt context!). Returns <0 on error. 

   Known working combination :
   
   g2chn = 0, sh4chn = 3 --> mode = 5 (but many other value seems OK ?)
   g2chn = 1, sh4chn = 1 --> mode = 0 (or 4 better ?)
   g2chn = 1, sh4chn = 0 --> mode = 3
   
   It seems that g2chn is not important when choosing mode, so this mode parameter is probably 
   how we actually connect the sh4chn to the g2chn.

   Update : looks like there is a formula, mode = 3 + shchn

*/

/* We use sh channel 3 here to avoid conflicts with the PVR. */
#define SPU_DMA_MODE   6 /* should we use 6 instead, so that the formula is 3+shchn ? 
			    6 works too, so ... */
#define SPU_DMA_G2CHN  0
#define SPU_DMA_SHCHN  3

/* For BBA : sh channel 1 (doesn't seem used) and g2 channel 1 to no conflict with SPU */
#define BBA_DMA_MODE   4
#define BBA_DMA_G2CHN  1
#define BBA_DMA_SHCHN  1

/* For BBA2 : sh channel 0 (doesn't seem used) and g2 channel 2 to no conflict with SPU */
/* This is a second DMA channels used for the BBA, just for fun and see if we can initiate
   two DMA transfers with the BBA concurently. */
#define BBA_DMA2_MODE   3
#define BBA_DMA2_G2CHN  2
#define BBA_DMA2_SHCHN  0

typedef void (*g2_dma_callback_t)(ptr_t data);
int g2_dma_transfer(void *from, void * dest, uint32 length, int block,
	g2_dma_callback_t callback, ptr_t cbdata, 
	uint32 dir, uint32 mode, uint32 g2chn, uint32 sh4chn);

/* Read one byte from G2 */
uint8 g2_read_8(uint32 address);

/* Write one byte to G2 */
void g2_write_8(uint32 address, uint8 value);

/* Read one word from G2 */
uint16 g2_read_16(uint32 address);

/* Write one word to G2 */
void g2_write_16(uint32 address, uint16 value);

/* Read one dword from G2 */
uint32 g2_read_32(uint32 address);

/* Write one dword to G2 */
void g2_write_32(uint32 address, uint32 value);

/* Read a block of 8-bit values from G2 */
void g2_read_block_8(uint8 * output, uint32 address, int amt);

/* Write a block 8-bit values to G2 */
void g2_write_block_8(const uint8 * input, uint32 address, int amt);

/* Read a block of 16-bit values from G2 */
void g2_read_block_16(uint16 * output, uint32 address, int amt);

/* Write a block of 16-bit values to G2 */
void g2_write_block_16(const uint16 * input, uint32 address, int amt);

/* Read a block of 32-bit values from G2 */
void g2_read_block_32(uint32 * output, uint32 address, int amt);

/* Write a block of 32-bit values to G2 */
void g2_write_block_32(const uint32 * input, uint32 address, int amt);

/* When writing to the SPU RAM, this is required at least every 8 32-bit
   writes that you execute */
void g2_fifo_wait();

__END_DECLS

#endif	/* __DC_G2BUS_H */

