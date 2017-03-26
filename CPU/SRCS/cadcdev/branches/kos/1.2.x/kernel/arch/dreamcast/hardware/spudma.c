/* KallistiOS ##version##
  
   spudma.c
   (c)2001-2002 Dan Potter
 */

#include <assert.h>
#include <stdio.h>
#include <dc/spu.h>
/* #include <dc/g2.h> */
#include <arch/irq.h>
#include <arch/cache.h>
#include <kos/thread.h>
#include <kos/sem.h>

CVSID("$Id: spudma.c,v 1.4 2002/02/10 02:30:10 bardtx Exp $");

/*

Handles the DMA part of the SPU functionality.

This module works in two different ways, depending on whether you have
threads enabled or not.

In thread enabled mode, memload will use a semaphore to block itself
until the SPU DMA IRQ is triggered, assuming you ask for it to wait
until the DMA is completed. This is very CPU efficient since the SPU
thread gets scheduled off until the IRQ happens.

In thread disabled mode, memload just spins until the IRQ fires, assuming
you ask for it to wait.

In both cases, if you ask for it not to wait, the function will return
immidiately. You'll have to do your own cleanup.

This is still pretty kludgy but it works.

Thanks to Bitmaster for the info on SPU DMA.

*/

#if 0

typedef struct {
	uint32		ext_addr;		/* External address (SPU-RAM or parallel port) */
	uint32		sh4_addr;		/* SH-4 Address */
	uint32		size;			/* Size in bytes; all addresses and sizes must be 32-byte aligned */
	uint32		dir;			/* 0: cpu->ext; 1: ext->cpu */
	uint32		mode;			/* 5 for SPU transfer */
	uint32		ctrl1;			/* b0 */
	uint32		ctrl2;			/* b0 */
	uint32		u1;			/* ?? */
} g2_dma_ctrl_t;

typedef struct {
	uint32		ext_addr;
	uint32		sh4_addr;
	uint32		size;
	uint32		status;
} g2_dma_stat_t;

typedef struct {
	g2_dma_ctrl_t	dma[4];
	uint32		u1[4];			/* ?? */
	uint32		wait_state;
	uint32		u2[10];			/* ?? */
	uint32		magic;
	g2_dma_stat_t	dma_stat[4];
} g2_dma_reg_t;

/* DMA registers */
vuint32	* const xxy = (vuint32 *)0xa05f6884;
vuint32	* const qacr = (vuint32 *)0xff000038;
vuint32	* const shdma = (vuint32 *)0xffa00000;
volatile g2_dma_reg_t * const extdma = (g2_dma_reg_t *)0xa05f7800;
const int	chn = 0;	/* 0 for SPU; 1, 2, 3 for EXT */

/* Signaling semaphore */
static semaphore_t * dma_done;
static volatile int dma_done_int;

static void dma_disable() {
	/* Disable the DMA */
	extdma->dma[chn].ctrl1 = 0;
	extdma->dma[chn].ctrl2 = 0;
	/* shdma[0x40/4] = 0; */	/* DMAC disable */
}

static void spu_dma_irq(uint32 code) {
	dma_disable();

	/* Signal the SPU thread to continue */
	if (thd_enabled)
		sem_signal(dma_done);
	else
		dma_done_int = 1;
	g2_dma_unlock();
}
#endif

void spu_memload_dma(uint32 dest, void *from, int length) {
	assert_msg( 0, "SPU DMA is broken right now" );

#if 0
	/* Check alignments */
	if ( ((uint32)from) & 31 ) {
		dbglog(DBG_ERROR, "spudma: unaligned source DMA %08x\n", from);
		return;
	}
	if ( ((uint32)dest) & 31 ) {
		dbglog(DBG_ERROR, "spudma: unaligned dest DMA %08x\n", dest);
		return;
	}
	if ( ((uint32)length) & 31 ) {
		length = (length & ~31) + 32;
	}

	/* Adjust destination */
	dest += 0xa0800000;

	g2_dma_lock();

	/* Setup the SH-4 channel */
	shdma[0x20/4] = 0;		/* SAR2 = 0 */
	shdma[0x24/4] = 0;		/* DAR2 = 0 */
	shdma[0x28/4] = 0;		/* DMATCR2 = 0 */
	shdma[0x2c/4] = 0x12c0;		/* CHCR2 = 0x12c0; 32-byte block transfer,
					   burst mode, external request, single address mode,
					   source address incremented; */
	/* The default is correct and screwing with this can
	   interrupt other types of DMA (maple, etc) */
	/* shdma[0x40/4] = 0x8201; */	/* DMAOR = 0x8201; DMAC master enable, CH2 > CH0 > CH1 > CH3,
					   on-demand data transfer */
	/* *xxy = 0;

	qacr[0] = 0x10;
	qacr[1] = 0x10; */

	/* Reset SPU DMA channel */
	/* for (i=chn; i<=chn; i++) {
		extdma->dma[i].ctrl1 = 0;
		extdma->dma[i].ext_addr = 0x009f0000;
		extdma->dma[i].sh4_addr = 0x0cff0000;
		extdma->dma[i].size = 0x20;
		extdma->dma[i].dir = 0;
		extdma->dma[i].mode = 5;
		extdma->dma[i].ctrl1 = 0;
		extdma->dma[i].ctrl2 = 0;
	} */

	/* Write back the cache */
	// dcache_flush_range((uint32)from, length);
	icache_flush_range((uint32)from, length);

	/* Start the DMA transfer */
	extdma->dma[chn].ctrl1 = 0;
	extdma->dma[chn].ctrl2 = 0;
	extdma->dma[chn].ext_addr = dest & 0x1fffffe0;
	extdma->dma[chn].sh4_addr = ((uint32)from) & 0x1fffffe0;
	extdma->dma[chn].size = (length & ~31) | 0x80000000;
	extdma->dma[chn].dir = 0;
	extdma->dma[chn].mode = 5;	/* SPU == 5 */
	extdma->dma[chn].ctrl1 = 1;
	extdma->dma[chn].ctrl2 = 1;

	/* Wait for us to be signaled */
	if (thd_enabled)
		sem_wait(dma_done);
	else {
		while (!dma_done_int)
			;
		dma_done_int = 0;
	}
#endif
}

int spu_dma_init() {
	assert_msg(0, "SPU DMA is broken right now");

#if 0
	/* Create an initially blocked semaphore */
	if (thd_enabled)
		dma_done = sem_create(0);
	else
		dma_done_int = 0;

	/* Hook the G2 interrupt */
	g2evt_set_handler(G2EVT_SPU_DMA, spu_dma_irq);

	/* Setup the DMA transfer on the external side */
	extdma->wait_state = 27;
	extdma->magic = 0x4659404f;

	/* printf("\n** INIT VALUES **\n");
	printf("%08x, %08x, %08x\n",
		extdma->dma[chn].ctrl1,
		extdma->dma[chn].ctrl2,
		shdma[0x40/4]); */
#endif
	return 0;
}

void spu_dma_shutdown() {
	assert_msg(0, "SPU DMA is broken right now");

#if 0
	/* Unhook the G2 interrupt */
	g2evt_set_handler(G2EVT_SPU_DMA, NULL);

	/* Destroy the semaphore */
	if (thd_enabled)
		sem_destroy(dma_done);

	/* Turn off any remaining DMA */
	dma_disable();
#endif
}

