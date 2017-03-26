/* KallistiOS ##version##

   kernel/arch/dreamcast/include/dc/ubc.h
   (C)2002 Dan Potter

   $Id: ubc.h,v 1.1 2002/03/16 19:22:03 bardtx Exp $
*/


#ifndef __DC_UBC_H
#define __DC_UBC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* From the SH-4 PDF */
#define BARA (*((vuint32*)0xFF200000))
#define BASRA (*((vuint8*)0xFF000014))
#define BAMRA (*((vuint8*)0xFF200004))
#define BBRA (*((vuint16*)0xFF200008))
#define BARB (*((vuint32*)0xFF20000C))
#define BASRB (*((vuint8*)0xFF000018))
#define BAMRB (*((vuint8*)0xFF200010))
#define BBRB (*((vuint16*)0xFF200014))
#define BRCR (*((vuint16*)0xFF200020))

/* These are inlined to avoid complications with using them */

/* Pause after setting UBC parameters */
static inline void ubc_pause() {
	__asm__ __volatile__("nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n"
	    "nop\n");
}

/* Disable all UBC breakpoints */
static inline void ubc_disable_all() {
	BBRA = 0;
	BBRB = 0;
	ubc_pause();
}

/* Set a UBC data-write breakpoint at the given address */
static inline void ubc_break_data_write(uint32 address) {
	BASRA = 0;		/* ASID = 0 */
	BARA = address;		/* Break address */
	BAMRA = 4;		/* Mask the ASID */
	BRCR = 0;		/* Nothing special, clear all flags */
	BBRA = 0x28;		/* Operand write cycle, no size constraint */
	ubc_pause();
}

/* More to come.... */

__END_DECLS

#endif	/* __DC_UBC_H */

