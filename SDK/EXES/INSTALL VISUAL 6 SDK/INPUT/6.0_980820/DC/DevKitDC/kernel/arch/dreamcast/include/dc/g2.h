/* KallistiOS 1.1.6

   dc/g2.h
   (c)2001 Dan Potter

   $Id: g2.h,v 1.3 2002/01/05 07:33:51 bardtx Exp $
  
*/

#ifndef __DC_G2_H
#define __DC_G2_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* All event codes are two 8-bit integers; the top integer is the event code
   register to look in to check the event (and to acknolwedge it). The
   register to check is 0xa05f6900+4*regnum. The bottom integer is the
   bit index within that register. */

/* Event codes for the PVR chip (TA) */
#define G2EVT_TA_RENDERDONE	0x0002		/* Render completed */
#define G2EVT_TA_SCANINT1	0x0003		/* Scanline interrupt 1 */
#define G2EVT_TA_SCANINT2	0x0004		/* Scanline interrupt 2 */
#define G2EVT_TA_VBLINT		0x0005		/* VBL interrupt */
#define G2EVT_TA_OPAQUEDONE	0x0007		/* Opaque list completed */
#define G2EVT_TA_OPAQUEMODDONE	0x0008		/* Opaque modifiers completed */
#define G2EVT_TA_TRANSDONE	0x0009		/* Transparent list completed */
#define G2EVT_TA_TRANSMODDONE	0x000a		/* Transparent modifiers completed */
#define G2EVT_TA_PTDONE		0x0015		/* Punch-thrus completed */
#define G2EVT_TA_PRIMOUTOFMEM	0x0202		/* Out of primitive memory */
#define G2EVT_TA_MATOUTOFMEM	0x0203		/* Out of matrix memory */

/* Event codes for the GD controller */
#define G2EVT_GD_COMMAND	0x0100		/* GD-Rom Command Status */
#define G2EVT_GD_DMA		0x000e		/* GD-Rom DMA complete */

/* Event codes for the Maple controller */
#define G2EVT_MAPLE_DMA		0x000c		/* Maple DMA complete */
#define G2EVT_MAPLE_ERROR	0x000d		/* Maple error (?) */

/* Event codes for the SPU */
#define G2EVT_SPU_DMA		0x000f		/* SPU DMA complete */
#define G2EVT_SPU_IRQ		0x0101		/* SPU interrupt */

/* Event codes for the external port */
#define G2EVT_EXP_MODEM		0x0102		/* modem (?) */
#define G2EVT_EXP_PCI		0x0103		/* BBA IRQ */

/* G2 registers */
#define G2_IRQD_A		(*(vuint32*)0xa05f6910)
#define G2_IRQD_B		(*(vuint32*)0xa05f6914)
#define G2_IRQD_C		(*(vuint32*)0xa05f6918)
#define G2_IRQB_A		(*(vuint32*)0xa05f6920)
#define G2_IRQB_B		(*(vuint32*)0xa05f6924)
#define G2_IRQB_C		(*(vuint32*)0xa05f6928)
#define G2_IRQ9_A		(*(vuint32*)0xa05f6930)
#define G2_IRQ9_B		(*(vuint32*)0xa05f6934)
#define G2_IRQ9_C		(*(vuint32*)0xa05f6938)

#define G2_ACK_A		(*(vuint32*)0xa05f6900)
#define G2_ACK_B		(*(vuint32*)0xa05f6904)
#define G2_ACK_C		(*(vuint32*)0xa05f6908)

/* The type of a G2 event handler */
typedef void (*g2evt_handler)(uint32 code);

/* Set a handler, or remove a handler (see codes above); handler
   functions have one parameter, which is the exception code. */
int g2evt_set_handler(uint32 code, g2evt_handler handler);

/* Enable/Disable G2 events  */
void g2evt_disable_all();
void g2evt_disable(uint32 code);
void g2evt_enable(uint32 code);

/* Lock G2 DMA */
void g2_dma_lock();

/* Unlock G2 DMA */
void g2_dma_unlock();

/* Init routine */
void g2_init();

/* Shutdown */
void g2_shutdown();

__END_DECLS

#endif	/* __DC_G2_H */

