/* KallistiOS ##version##

   arch/ps2/include/ioports.h
   (c)2002 Dan Potter
   
   $Id: ioports.h,v 1.1 2002/11/03 03:40:55 bardtx Exp $
*/

#ifndef __PS2_IOPORTS_H
#define __PS2_IOPORTS_H

/* Define __ASM__ before including this file if you want to use it
   from an assembly file. The register definitions will become
   just raw addresses. */

#ifndef __ASM__
#	include <sys/cdefs.h>
	__BEGIN_DECLS
#	include <arch/types.h>
#	define _IOPORT128(x) (*((vuint128 *)(x)))
#	define _IOPORT32(x) (*((vuint32 *)(x)))
#	define _IOPORT8(x)  (*((vuint8 *)(x)))
#	define _IOPTR32(x)  ((vuint32 *)(x))
#else	/* !__ASM__ */
#	define _IOPORT128(x) x
#	define _IOPORT32(x) x
#	define _IOPORT8(x) x
#	define _IOPTR32(x) x
#endif	/* __ASM__ */


/* If there are any misc hardware port definitions, then they'll go here.
   Each major subsystem (e.g., GS) may have its own set of definitions
   elsewhere as well. */

/* Timers */
#define TIMER_COUNT(x)	_IOPORT32((x)*0x800+0xb0000000)
#define TIMER_MODE(x)	_IOPORT32((x)*0x800+0xb0000010)
#define TIMER_COMP(x)	_IOPORT32((x)*0x800+0xb0000020)
#define TIMER_HOLD(x)	_IOPORT32((x)*0x800+0xb0000030)

/* Timer constants for TIMER_MODE */
#define TIMER_CLKS_BUSCLK	0
#define TIMER_CLKS_BUSCLK16	1
#define TIMER_CLKS_BUSCLK256	2
#define TIMER_CLKS_HBLNK	3
#define TIMER_GATE_DISABLE	0
#define TIMER_GATE_ENABLE	(1 << 2)
#define TIMER_GATS_HBLNK	0
#define TIMER_GATS_VBLNK	(1 << 3)
#define TIMER_GATM_00		0		/* Can't even think of good names */
#define TIMER_GATM_01		(1 << 4)	/* for these weird-ass modes... look */
#define TIMER_GATM_10		(2 << 4)	/* in the EE manual on pg 36 */
#define TIMER_GATM_11		(3 << 4)
#define TIMER_ZRET_DISABLE	0
#define TIMER_ZRET_ENABLE	(1 << 6)
#define TIMER_CUE_DISABLE	0
#define TIMER_CUE_ENABLE	(1 << 7)
#define TIMER_CMPE_DISABLE	0
#define TIMER_CMPE_ENABLE	(1 << 8)
#define TIMER_OVFE_DISABLE	0
#define TIMER_OVFE_ENABLE	(1 << 9)
#define TIMER_EQUF		(1 << 10)
#define TIMER_OVFF		(1 << 11)

/* IPU */
#define IPU_CMD		_IOPORT32(0xb0002000)
#define IPU_CTRL	_IOPORT32(0xb0002010)
#define IPU_BP		_IOPORT32(0xb0002020)
#define IPU_TOP		_IOPORT32(0xb0002030)

/* GIF */
#define GIF_CTRL	_IOPORT32(0xb0003000)
#define GIF_MODE	_IOPORT32(0xb0003010)
#define GIF_STAT	_IOPORT32(0xb0003020)
#define GIF_TAG(x)	_IOPORT32((x)*0x10+0xb0003070)
#define GIF_CNT		_IOPORT32(0xb0003080)
#define GIF_P3CNT	_IOPORT32(0xb0003090)
#define GIF_P3TAG	_IOPORT32(0xb00030a0)

/* VIF0/1: x in [0..1] and y in [0..3] */
#define VIF_STAT(x)	_IOPORT32((x)*0x400 + 0xb0003800)
#define VIF_FBRST(x)	_IOPORT32((x)*0x400 + 0xb0003810)
#define VIF_ERR(x)	_IOPORT32((x)*0x400 + 0xb0003820)
#define VIF_MARK(x)	_IOPORT32((x)*0x400 + 0xb0003830)
#define VIF_CYCLE(x)	_IOPORT32((x)*0x400 + 0xb0003840)
#define VIF_MODE(x)	_IOPORT32((x)*0x400 + 0xb0003850)
#define VIF_NUM(x)	_IOPORT32((x)*0x400 + 0xb0003860)
#define VIF_MASK(x)	_IOPORT32((x)*0x400 + 0xb0003870)
#define VIF_CODE(x)	_IOPORT32((x)*0x400 + 0xb0003880)
#define VIF_ITOPS(x)	_IOPORT32((x)*0x400 + 0xb0003890)
#define VIF_ITOP(x)	_IOPORT32((x)*0x400 + 0xb00038d0)
#define VIF_ROW(x,y)	_IOPORT32((x)*0x400 + (y)*0x10 + 0xb0003900)
#define VIF_COL(x,y)	_IOPORT32((x)*0x400 + (y)*0x10 + 0xb0003940)

/* FIFO */
#define FIFO_VIF0	_IOPORT128(0xb0004000)
#define FIFO_VIF1	_IOPORT128(0xb0005000)
#define FIFO_GIF	_IOPORT128(0xb0006000)
#define FIFO_IPU_OUT	_IOPORT128(0xb0007000)
#define FIFO_IPU_IN	_IOPORT128(0xb0007010)

/* DMAC: x in [0..9] with the following support:

   CHCR    MADR    QWC    TADR   ASR0   ASR1   SADR
0   x       x       x       x      x      x
1   x       x       x       x      x      x
2   x       x       x       x      x      x
3   x       x       x
4   x       x       x       x
5   x       x       x
6   x       x       x       x
7   x       x       x
8   x       x       x                           x
9   x       x       x       x                   x

 */
#define DMAC_CHCR(x)	_IOPORT32((x)*0x1000 + 0xb0008000)
#define DMAC_MADR(x)	_IOPORT32((x)*0x1000 + 0xb0008010)
#define DMAC_QWC(x)	_IOPORT32((x)*0x1000 + 0xb0008020)
#define DMAC_TADR(x)	_IOPORT32((x)*0x1000 + 0xb0008030)
#define DMAC_ASR0(x)	_IOPORT32((x)*0x1000 + 0xb0008040)
#define DMAC_ASR1(x)	_IOPORT32((x)*0x1000 + 0xb0008050)
#define DMAC_SADR(x)	_IOPORT32((x)*0x1000 + 0xb0008080)

/* INTC status/mask registers */
#define INTC_STAT	_IOPORT32(0xb000f000)
#define INTC_MASK	_IOPORT32(0xb000f010)

#ifndef __ASM__
/* These macros are needed to toggle the bits since they
   toggle when written to, as opposed to simply accepting the value
   written to them. Only pass one bit at a time. */
#define INTC_MASK_SET(x) do {		\
	if (!(INTC_MASK & (x)))		\
		INTC_MASK |= (x);	\
} while (0)
#define INTC_MASK_CLEAR(x) do {		\
	if (INTC_MASK & (x))		\
		INTC_MASK |= (x);	\
} while (0)

#endif	/* __ASM__ */

/* Bits for the INTC registers */
#define INTM_GS		0x00000001
#define INTM_SBUS	0x00000002
#define INTM_VBON	0x00000004
#define INTM_VBOFF	0x00000008
#define INTM_VIF0	0x00000010
#define INTM_VIF1	0x00000020
#define INTM_VU0	0x00000040
#define INTM_VU1	0x00000080
#define INTM_IPU	0x00000100
#define INTM_TIMER0	0x00000200
#define INTM_TIMER1	0x00000400
#define INTM_TIMER2	0x00000800
#define INTM_TIMER3	0x00001000
#define INTM_SFIFO	0x00002000
#define INTM_VU0WD	0x00004000

/* SIF */
#define SIF_SMFLG	_IOPORT32(0xb000f230)

/* DMAC */
#define DMAC_ENABLER	_IOPORT32(0xb000f520)
#define DMAC_ENABLEW	_IOPORT32(0xb000f590)

/* VU0/VU1 memory regions */
#define VU0_MICROMEM	_IOPTR32(0xb1000000)
#define VU0_VUMEM	_IOPTR32(0xb1004000)
#define VU1_MICROMEM	_IOPTR32(0xb1008000)
#define VU1_VUMEM	_IOPTR32(0xb100c000)

/* GS */
#define GS_PMODE	_IOPTR128(0xb2000000)
#define GS_SMODE1	_IOPTR128(0xb2000010)
#define GS_SMODE2	_IOPTR128(0xb2000020)
#define GS_SRFSH	_IOPTR128(0xb2000030)
#define GS_SYNCH1	_IOPTR128(0xb2000040)
#define GS_SYNCH2	_IOPTR128(0xb2000050)
#define GS_SYNCV	_IOPTR128(0xb2000060)
#define GS_DISPFB1	_IOPTR128(0xb2000070)
#define GS_DISPLAY1	_IOPTR128(0xb2000080)
#define GS_DISPFB2	_IOPTR128(0xb2000090)
#define GS_DISPLAY2	_IOPTR128(0xb20000a0)
#define GS_EXTBUF	_IOPTR128(0xb20000b0)
#define GS_EXTDATA	_IOPTR128(0xb20000c0)
#define GS_EXTWRITE	_IOPTR128(0xb20000d0)
#define GS_BGCOLOR	_IOPTR128(0xb20000e0)
#define GS_CSR		_IOPTR128(0xb2001000)
#define GS_IMR		_IOPTR128(0xb2001010)
#define GS_BUSDIR	_IOPTR128(0xb2001040)
#define GS_SIGLBLID	_IOPTR128(0xb2001080)

/* Misc PIO registers */
#define PIO_DIR		_IOPORT8(0xb400002c)
#define PIO_DATA	_IOPORT8(0xb400002e)

/* Bits for the PIO registers */
#define PIO_DIR_OUT		1
#define PIO_DATA_LED_ON		0
#define PIO_DATA_LED_OFF	1

#ifndef __ASM__
	__END_DECLS
#endif	/* __ASM__ */

#endif	/* __PS2_SBIOS_H */

