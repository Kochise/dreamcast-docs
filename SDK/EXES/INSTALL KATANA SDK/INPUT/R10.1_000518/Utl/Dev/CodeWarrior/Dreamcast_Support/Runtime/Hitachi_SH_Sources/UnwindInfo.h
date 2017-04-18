
/*
 *	UnwindInfo.h	-	C++ Exception Table Unwind Info for Hitachi SH series
 *
 *  Copyright © 1999 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	The Exception Table for a function contains a target-specific variable-length structure
 *	that includes all information necessary to unwind the stack frame for the function.
 *	An Hitachi SH stack frame looks like this:
 *
 *	HIGH ADDRESSES	|						|
 *					|						|
 *					|-----------------------|
 *					|	incoming arguments	|
 *					|		> 4 words		|
 *					|-----------------------|
 *					|  Return value address |
 *	Caller's SP   =>|-----------------------|
 *					|	GPR save area		|	Storage for nonvolatile GPRs used by callee
 *					|-----------------------|
 *					|	saved PR register	|	Procedure register
 *					|-----------------------|
 *					|		Callee's		|	local vars and temps that resided in virtual
 *					|	spills				|	registers but were spilled by coloring
 *					|-----------------------|
 *					|		Callee's		|	Local vars that are that cannot reside
 *					|	local variables		|	in registers. assigned location before cg
 *	Callee's SP   =>|-----------------------|
 *					|						|
 *	LOW ADDRESSES	|						|
 *
 *	In order to unwind the stack frame, then, we need the following information:
 *
 *	(1)	Frame Size		Since there's no back-link in the frame, we need this to
 *						pop to the caller's frame.
 *
 *	(2)	Argument Size	When we transfer control to a catch-block, the thrower's frame
 *						is still on the stack (because the exception temporary was
 *						allocated there) and if the thrower's argument area is smaller
 *						than the catcher's then we need to increase it before jumping
 *						to the catch-block.
 *
 *	(3)	# Saved GPRs	We need this to restore any of the nonvolatile registers (r20-r29)
 *						that were saved in the frame.
 *
 *	(4)	Flushback?		We need to know if the 16-byte flushback area is present in the frame.
 *
 *	(5)	Separate FP?	We need to know if the frame uses a separate frame pointer (r29)
 *						for accessing locals etc; this will be true for any function
 *						which calls alloca() or which contains a catch-block.
 *
 *	We represent the Unwind Info using a variable-length structure:
 *
 *	|<-2 bits->|<-1 bit->|<-1 bit->|<-4 bits->|
 *	+----------+---------+---------+----------+
 *	|  unused  | has FP? | unused  |  # GPRs  |
 *	+----------+---------+---------+----------+
 *	|  unused  | unused  | unused  |  # FPRs  |
 *	+-----------------------------------------+
 *	| Frame Size (1/2/3/4 bytes as needed)	  |
 *	+-----------------------------------------+
 *
 *	The Frame Size and Outgoing Argument Area Size are represented using the variable-length
 *	unsigned integer format. For most functions, these will occupy only 1 byte each, so the
 *	entire Unwind Info for a function will typically occupy 3 bytes.
 *
 */

#ifndef __UNWINDINFO_H__
#define __UNWINDINFO_H__


#define	UNWIND_USED_GPR_MASK	0x0F	/*	mask to get # saved GPRs from Unwind Info		*/
#define	UNWIND_HAS_FLUSHBACK	0x10	/*	indicates Flushback Area is present in frame	*/
#define UNWIND_HAS_FRAME_PTR	0x20	/*	indicates frame uses separate Frame Pointer		*/
#define UNWIND_HAS_FPU			0x40	/*	indicates if there are soc fpu register			*/
#define UNWIND_RESERVED_2		0x80	/*	(reserved for future use)	*/
#define UNWIND_USED_FPR_MASK	0x0F	/*	mask to get # saved FPRs from Unwind Info		*/	


#endif
