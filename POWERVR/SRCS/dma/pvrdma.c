/* KallistiOS 1.1.8
  
   pvrdma.c
   (c)2002 Roger Cattermole
   http://www.boob.co.uk
 */

#include <stdio.h>
#include <dc/pvr.h>
#include <dc/asic.h>
#include <kos/thread.h>
#include <kos/sem.h>

/* Signaling semaphore */
static semaphore_t * pvr_dma_done;
static volatile int pvr_dma_complete;

/* DMA registers */
vuint32	* const pvrdma = (vuint32 *)0xa05f6800;
vuint32	* const shdma  = (vuint32 *)0xffa00000;

/* DMAC registers */
 #define DMAC_SAR2		0x20/4
 #define DMAC_DMATCR2	0x28/4
 #define DMAC_CHCR2		0x2c/4
 #define DMAC_DMAOR		0x40/4

/* PVR Dma registers - Offset by 0xA05F6800 */
 #define PVR_STATE		0x00
 #define PVR_LEN		0x04/4
 #define PVR_DST		0x08/4
 #define PVR_LMMODE0	0x84/4
 #define PVR_LMMODE1	0x88/4

/* Count is in bytes. */

 void pvr_texture_dma(pvr_ptr_t dest, void * src, uint32 count)
 {
	int i;
	uint32 val;
	uint32 src_addr=((uint32)src); 
	uint32 dest_addr=(((unsigned long)dest)&0xFFFFFF)|0x11000000;

	if (pvrdma[PVR_DST]!=0)
	 { 
		dbglog(DBG_ERROR, "PVR_Dma: PVR_DST != 0\n");
		return;
	 }

	val = shdma[DMAC_CHCR2];

	if (val&0x1) /* DE bit set so we must clear it */
		shdma[DMAC_CHCR2]=val|0x1;
	if (val&0x2) /* TE bit set so we must clear it */
		shdma[DMAC_CHCR2]=val|0x2;
	
	/* Check for 32-byte alignment */
	if (src_addr&0x1F)
		dbglog(DBG_WARNING, "PVR_Dma: Src is not 32-byte aligned\n");
	src_addr&=0x0FFFFFE0;

	if (src_addr<0x0c000000)
	 {
		dbglog(DBG_ERROR, "PVR_Dma: Src address < 0x0c000000\n");
		return;
	 }
	
	shdma[DMAC_SAR2]=src_addr;
	shdma[DMAC_DMATCR2]=count/32;
	shdma[DMAC_CHCR2]=0x12c1;

	val = shdma[DMAC_DMAOR];

	if ((val & 0x8007) != 0x8001)
	 {
		dbglog(DBG_ERROR, "PVR_Dma: Failed DMAOR check\n");
		return;
	 }

	pvrdma[PVR_LMMODE0]=0x0;
	pvrdma[PVR_STATE]=dest_addr;
	pvrdma[PVR_LEN]=count;
	pvrdma[PVR_DST]=0x1;

	/* Wait for us to be signaled */
	if (thd_enabled)
		sem_wait(pvr_dma_done);
	else {
		while (!pvr_dma_complete)
			;
		pvr_dma_complete = 0;
	}
 }

void pvr_dma_init()
{
	/* Create an initially blocked semaphore */
	if (thd_enabled)
		pvr_dma_done = sem_create(0);
	else
		pvr_dma_complete = 0;

	/* Hook the neccessary interrupts */
	asic_evt_set_handler(ASIC_EVT_PVR_DMA, pvr_dma_irq_hnd);	asic_evt_enable(ASIC_EVT_PVR_DMA);
}

void pvr_dma_irq_hnd(uint32 code)
{
	if (shdma[DMAC_DMATCR2]!=0)
		dbglog(DBG_INFO,"PVR_Dma: The dma did not complete successfully\n");
	
	/* Signal the SPU thread to continue */
	if (thd_enabled)
		sem_signal(pvr_dma_done);
	else
		pvr_dma_complete = 1;
}
