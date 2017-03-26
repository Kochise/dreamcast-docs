/* KallistiOS ##version##

   g2bus.c
   (c)2000-2002 Dan Potter
*/

/*

  This module handles low-level access to the DC's "G2" bus, which handles
  communication with the SPU (AICA) and the expansion port. One must be
  very careful with this bus, as it requires 32-bit access for most
  things, FIFO checking for PIO access, suspended DMA for PIO access,
  etc, etc... very picky =)

  Thanks to Marcus Comstedt and Marcus Brown for the info about when
  to lock/suspend DMA/etc.

 */

#include <string.h>
#include <stdio.h>
#include <arch/irq.h>
#include <dc/g2bus.h>
#include <arch/spinlock.h>

CVSID("$Id: g2bus.c,v 1.5 2003/02/14 06:33:47 bardtx Exp $");

/* These two macros are based on NetBSD's DC port */

/*
   G2 bus cycles must not be interrupted by IRQs or G2 DMA.
   The following paired macros will take the necessary precautions.
 */

#define G2_LOCK(OLD) \
	do { \
		if (!irq_inside_int()) { \
			OLD = irq_disable(); \
		} \
		/* suspend any G2 DMA here... */ \
		while((*(vuint32 *)0xa05f688c) & 0x20) \
			; \
	} while(0)

#define G2_UNLOCK(OLD) \
	do { \
		/* resume any G2 DMA here... */ \
		if (!irq_inside_int()) \
			irq_restore(OLD); \
	} while(0)

/* Always use these functions to access G2 bus memory (includes the SPU
   and the expansion port, e.g., BBA) */

/* Read one byte from G2 */
uint8 g2_read_8(uint32 address) {
	int old = 0;
	uint8 out;

	G2_LOCK(old);
	out = *((vuint8*)address);
	G2_UNLOCK(old);
	
	return out;
}

/* Write one byte to G2 */
void g2_write_8(uint32 address, uint8 value) {
	int old = 0;

	G2_LOCK(old);
	*((vuint8*)address) = value;
	G2_UNLOCK(old);
}

/* Read one word from G2 */
uint16 g2_read_16(uint32 address) {
	int old = 0;
	uint16 out;

	G2_LOCK(old);
	out = *((vuint16*)address);
	G2_UNLOCK(old);

	return out;
}

/* Write one word to G2 */
void g2_write_16(uint32 address, uint16 value) {
	int old = 0;

	G2_LOCK(old);
	*((vuint16*)address) = value;
	G2_UNLOCK(old);
}

/* Read one dword from G2 */
uint32 g2_read_32(uint32 address) {
	int old = 0;
	uint32 out;

	G2_LOCK(old);
	out = *((vuint32*)address);
	G2_UNLOCK(old);

	return out;
}

/* Write one dword to G2 */
void g2_write_32(uint32 address, uint32 value) {
	int old = 0;

	G2_LOCK(old);
	*((vuint32*)address) = value;
	G2_UNLOCK(old);
}

/* Read a block of 8-bit values from G2 */
void g2_read_block_8(uint8 * output, uint32 address, int amt) {
	const vuint8 * input = (const vuint8 *)address;
	int old = 0;

	G2_LOCK(old);

	while (amt--) {
		*output++ = *input++;
	}

	G2_UNLOCK(old);
}

/* Write a block 8-bit values to G2 */
void g2_write_block_8(const uint8 * input, uint32 address, int amt) {
	vuint8 * output = (vuint8 *)address;
	int old = 0;

	G2_LOCK(old);

	while (amt--) {
		*output++ = *input++;
	}

	G2_UNLOCK(old);
}

/* Read a block of 32-bit values from G2 */
void g2_read_block_32(uint32 * output, uint32 address, int amt) {
	const vuint32 * input = (const vuint32 *)address;
	int old = 0;

	G2_LOCK(old);

	while (amt--) {
		*output++ = *input++;
	}

	G2_UNLOCK(old);
}

/* Write a block of 32-bit values to G2 */
void g2_write_block_32(const uint32 * input, uint32 address, int amt) {
	vuint32 * output = (vuint32 *)address;
	int old = 0;

	G2_LOCK(old);

	while (amt--) {
		*output++ = *input++;
	}

	G2_UNLOCK(old);
}

/* When writing to the SPU RAM, this is required at least every 8 32-bit
   writes that you execute */
void g2_fifo_wait() {
	vuint32 const *g2_fifo = (vuint32*)0xa05f688c;
	int i;

	for (i=0; i<0x1800; i++) {
		if (!(*g2_fifo & 0x11)) break;
	}
}


