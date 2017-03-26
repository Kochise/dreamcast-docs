/* KallistiOS ##version##

   dc/asic.h
   (c)2001-2002 Dan Potter

   $Id: asic.h,v 1.4 2003/02/25 07:39:37 bardtx Exp $
  
*/

#ifndef __DC_ASIC_H
#define __DC_ASIC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* All event codes are two 8-bit integers; the top integer is the event code
   register to look in to check the event (and to acknolwedge it). The
   register to check is 0xa05f6900+4*regnum. The bottom integer is the
   bit index within that register. */

/* Event codes for the PVR chip */
#define ASIC_EVT_PVR_RENDERDONE		0x0002		/* Render completed */
#define ASIC_EVT_PVR_SCANINT1		0x0003		/* Scanline interrupt 1 */
#define ASIC_EVT_PVR_SCANINT2		0x0004		/* Scanline interrupt 2 */
#define ASIC_EVT_PVR_VBLINT		0x0005		/* VBL interrupt */
#define ASIC_EVT_PVR_OPAQUEDONE		0x0007		/* Opaque list completed */
#define ASIC_EVT_PVR_OPAQUEMODDONE	0x0008		/* Opaque modifiers completed */
#define ASIC_EVT_PVR_TRANSDONE		0x0009		/* Transparent list completed */
#define ASIC_EVT_PVR_TRANSMODDONE	0x000a		/* Transparent modifiers completed */
#define ASIC_EVT_PVR_DMA		0x0013		/* PVR DMA complete */
#define ASIC_EVT_PVR_PTDONE		0x0015		/* Punch-thrus completed */
#define ASIC_EVT_PVR_PRIMOUTOFMEM	0x0202		/* Out of primitive memory */
#define ASIC_EVT_PVR_MATOUTOFMEM	0x0203		/* Out of matrix memory */

/* Event codes for the GD controller */
#define ASIC_EVT_GD_COMMAND		0x0100		/* GD-Rom Command Status */
#define ASIC_EVT_GD_DMA			0x000e		/* GD-Rom DMA complete */

/* Event codes for the Maple controller */
#define ASIC_EVT_MAPLE_DMA		0x000c		/* Maple DMA complete */
#define ASIC_EVT_MAPLE_ERROR		0x000d		/* Maple error (?) */

/* Event codes for the SPU */
#define ASIC_EVT_SPU_DMA		0x000f		/* SPU (G2 chnl 0) DMA complete */
#define ASIC_EVT_SPU_IRQ		0x0101		/* SPU interrupt */

/* Event codes for G2 bus DMA */
#define ASIC_EVT_G2_DMA0		0x000f		/* G2 DMA chnl 0 complete */
#define ASIC_EVT_G2_DMA1		0x0010		/* G2 DMA chnl 1 complete */
#define ASIC_EVT_G2_DMA2		0x0011		/* G2 DMA chnl 2 complete */
#define ASIC_EVT_G2_DMA3		0x0012		/* G2 DMA chnl 3 complete */

/* Event codes for the external port */
#define ASIC_EVT_EXP_8BIT		0x0102		/* Modem / Lan Adapter */
#define ASIC_EVT_EXP_PCI		0x0103		/* BBA IRQ */

/* ASIC registers */
#define ASIC_IRQD_A		(*(vuint32*)0xa05f6910)
#define ASIC_IRQD_B		(*(vuint32*)0xa05f6914)
#define ASIC_IRQD_C		(*(vuint32*)0xa05f6918)
#define ASIC_IRQB_A		(*(vuint32*)0xa05f6920)
#define ASIC_IRQB_B		(*(vuint32*)0xa05f6924)
#define ASIC_IRQB_C		(*(vuint32*)0xa05f6928)
#define ASIC_IRQ9_A		(*(vuint32*)0xa05f6930)
#define ASIC_IRQ9_B		(*(vuint32*)0xa05f6934)
#define ASIC_IRQ9_C		(*(vuint32*)0xa05f6938)

#define ASIC_ACK_A		(*(vuint32*)0xa05f6900)
#define ASIC_ACK_B		(*(vuint32*)0xa05f6904)
#define ASIC_ACK_C		(*(vuint32*)0xa05f6908)

/* ASIC IRQ priorities (pick one at hook time, or don't choose anything and
   we'll choose a default) */
#define ASIC_IRQ9		1
#define ASIC_IRQB		2
#define ASIC_IRQD		3
#define ASIC_IRQ_DEFAULT	0

/* The type of a ASIC event handler */
typedef void (*asic_evt_handler)(uint32 code);

/* Set a handler, or remove a handler (see codes above); handler
   functions have one parameter, which is the exception code. */
int asic_evt_set_handler(uint32 code, asic_evt_handler handler);

/* Enable/Disable ASIC events; only enable a given event on one irqlevel! */
void asic_evt_disable_all();
void asic_evt_disable(uint32 code, int irqlevel);
void asic_evt_enable(uint32 code, int irqlevel);

/* Init routine */
void asic_init();

/* Shutdown */
void asic_shutdown();

__END_DECLS

#endif	/* __DC_ASIC_H */

