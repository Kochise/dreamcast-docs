/* KallistiOS ##version##

   arch/ps2/include/asmregs.h
   (c)2002 Dan Potter
   
   $Id: asmregs.h,v 1.1 2002/10/27 23:39:23 bardtx Exp $
*/

#ifndef __PS2_ASMREGS_H
#define __PS2_ASMREGS_H

/* This is meant to be included from a .S files for human-readable
   register names. */

/******************************************************** CPU Regs ****/

/* Hard-wired to zero */
#define zero	$0

/* Assembler temp register */
#define at	$1

/* Return value(s) */
#define v0	$2
#define v1	$3

/* Arguments/parameters */
#define a0	$4
#define a1	$5
#define a2	$6
#define a3	$7

/* Temp (caller saved) registers */
#define t0	$8
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define t8	$24
#define t9	$25	/* Shared with JP */

/* (Callee) saved registers */
#define s0	$16
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define s8	$30	/* Shared with FP */

/* PIC Jump register */
#define jp	$25	/* Shared with T9 */

/* Kernel scratch regs */
#define k0	$26
#define k1	$27

/* Global pointer */
#define gp	$28

/* Stack pointer */
#define sp	$29

/* Frame pointer */
#define fp	$30	/* Shared with S8 */

/* Return address */
#define ra	$31

/******************************************************** COP0 regs ****/

#define cp0index	$0
#define cp0random	$1
#define cp0entrylo0	$2
#define cp0entrylo1	$3
#define cp0context	$4
#define cp0pagemask	$5
#define cp0wired	$6
#define cp0badvaddr	$8
#define cp0count	$9
#define cp0entryhi	$10
#define cp0compare	$11
#define cp0status	$12
#define cp0cause	$13
#define cp0epc		$14
#define cp0prid		$15
#define cp0config	$16
#define cp0badpaddr	$23
#define cp0debug	$24
#define cp0perf		$25
#define cp0taglo	$28
#define cp0taghi	$29
#define cp0errorepc	$30

#endif	/* __PS2_ASMREGS_H */

