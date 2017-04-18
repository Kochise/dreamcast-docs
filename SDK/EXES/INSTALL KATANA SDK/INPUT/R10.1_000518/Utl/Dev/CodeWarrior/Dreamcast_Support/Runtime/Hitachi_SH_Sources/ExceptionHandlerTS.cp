
/*
 *	ExceptionHandlerTS.cp	-	Target-specific C++ Exception Handler support - Hitachi SH
 *
 *  Copyright © 1999 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	Here we define any functions which implement the target-specific aspects of
 *	the standard C++ Exception Handler.
 *
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
 *
 *	Note that for functions which contain catch-blocks or call alloca(), a separate frame
 *	pointer register (r29) will point where "Callee's SP" does in the diagram above; SP
 *	may point anywhere below that.
 *
 *	The UnwindInfo for the Hitachi SH provides the necessary info for decoding the frame:
 *
 *	|<-2 bits->|<-1 bit->|<-1 bit->|<-4 bits->|
 *	+----------+---------+---------+----------+
 *	|  unused  | has FP? | unused  |  # GPRs  |
 *	+----------+---------+---------+----------+
 *	| Frame Size (1/2/3/4 bytes as needed)	  |
 *	+-----------------------------------------+
 *	| Argument Size (1/2/3/4 bytes as needed) |
 *	+----------+---------+---------+----------+
 *	|  unused  | unused  | unused  |  # FPRs  |
 *	+-----------------------------------------+
 *
 */

#include "NMWException.h"
#include "ExceptionHandler.h"
#include "UnwindInfo.h"

 
/*	
 *	__PopStackFrame(context, info)
 *
 *	Restore any registers saved in the current frame, as indicated by the
 *	UnwindInfo stored in 'info->exception_record', and pop the frame.
 *
 *	We don't actually modify the runtime stack; we simply restore the values of
 *	all registers saved in the current function to their value in the function's
 *	caller, IN THE LOCAL COPY OF THE REGISTER VALUES STORED IN 'context'. When we
 *	finally transfer control to a catch-block, we'll copy these values into the
 *	actual machine registers.
 *
 *	We return the return address in the caller--the place where the function whose
 *	frame we are popping would have returned to--so that the caller can use it to
 *	find the corresponding exception table.
 *
 *	We cannot correctly set 'context->FP' to the new frame's frame pointer because
 *	we don't yet have the exception table, which tells us whether the frame used
 *	a separate frame pointer or whether 'context->FP' == 'context->SP'.
 *
 */

char *__PopStackFrame(ThrowContext *context, ExceptionInfo *info)
{
	char *p;
	int has_fpu;
	unsigned long framesize = context->target.frame_size;
	unsigned long FBsize = context->target.has_flushback ? 16 : 0;
	unsigned long *GPRs;
	char *retaddr;
	int i;
	
	p = info->exception_record;
	has_fpu = *p & UNWIND_HAS_FPU;

		/*	restore the saved nonvolatile FPRs and GPRs	*/
	
	GPRs = (unsigned long *) (context->FP + framesize - FBsize - 4);
	
#if __SH4__
	if (has_fpu)
		for (i = 0; i < context->target.n_saved_FPRs; i++)
			context->target.FPR[15-i] = *GPRs--;
#endif		

	for (i = 0; i < context->target.n_saved_GPRs; i++)
		context->target.GPR[14-i] = *GPRs--;

		/*	get the new return address	*/
	
	retaddr = * (char **) (context->FP + framesize - FBsize - 4
						   - 4*context->target.n_saved_FPRs 
						   - 4*context->target.n_saved_GPRs);
		
		/*	remove the frame from the stack	*/
	
	context->SP = context->FP + framesize;
		
		/*	return the new return address	*/
	
	return(retaddr);
}


/*
 *	__SetupFrameInfo(context, info)
 *
 *	Decode the UnwindInfo pointed at by 'info->exception_record'. Using this
 *	and the information contained in 'context', setup any information needed to
 *	address local variables in the current frame. This information is only used
 *	by __LocalVariable() defined below.
 *
 *	Typically this involves setting 'context->FP' to 'context->SP' for functions
 *	which do not have a separate frame pointer, or to whichever general-purpose
 *	register is used as a frame pointer for functions which do require a separate
 *	frame pointer.
 *
 *	On most RISC machines, locals can be addressed via SP unless the function
 *	calls alloca() or contains a catch-block or exception-specification, in which
 *	case a separate frame pointer is used because SP may float while the function
 *	is executing.
 *
 *	It is convenient to retain the decoded UnwindInfo in the target-specific portion
 *	of the ThrowContext so it can be reused by __PopStackFrame() and other routines.
 *
 */

extern void __SetupFrameInfo(ThrowContext *context, ExceptionInfo *info)
{
	char *p = info->exception_record;
	int has_fpu = *p & UNWIND_HAS_FPU;

		/*	decode the UnwindInfo for the current function	*/
	
	context->target.has_frame_ptr = *p & UNWIND_HAS_FRAME_PTR;
	context->target.has_flushback = *p & UNWIND_HAS_FLUSHBACK;
	context->target.n_saved_GPRs = *p & UNWIND_USED_GPR_MASK;
#if __SH4__
	if (has_fpu) {
		context->target.n_saved_FPRs = *(p+1);
		p = p + 2;
	} else {
		context->target.n_saved_FPRs = 0;
		p = p + 1;
	}
#endif
	p = __DecodeUnsignedNumber(p, &context->target.frame_size);
	context->target.argument_size=0; // for now - outgoing arguments TO BE IMPLEMENTED
	
		/*	setup the frame pointer for addressing locals in the current function	*/
	
	if (context->target.has_frame_ptr)
		context->FP = (char *) context->target.GPR[14];	//	R14 is used as the frame pointer
	else
		context->FP = context->SP;						//	SP is used as the frame pointer
#if 0
#if __SH4__
	if (has_fpu)
		p = __DecodeUnsignedNumber(p, (unsigned long*)&context->target.n_saved_FPRs);
	else 
		context->target.n_saved_FPRs = 0;
#endif
#endif

}


/*
 *	__FindExceptionTable(info, retaddr)
 *
 *	Find the Exception Table Index that (possibly) contains 'retaddr'.
 *	The start and end of the index are stored in 'info->exception_table_start'
 *	and 'info->exception_table_end'.
 *
 *	If there is any target-specific ExceptionInfo it must be initialized here
 *	as well, e.g. base address of code/data sections.
 *
 *	For most targets there is only one exception table, usually accessed via
 *	globals generated by the linker, e.g. __exception_table_start__ and
 *	__exception_table_end__, so we just fill in those addresses and return TRUE.
 *
 *	If the target supports multiple fragments or overlays or for some other reason
 *	has more than one exception table index for a single program, we can use
 *	'retaddr' to find the appropriate index. If 'retaddr' doesn't correspond to
 *	any known exception table index then we must return FALSE.
 *
 *	Note that at this point 'retaddr' is an absolute return address, since we
 *	don't know until this routine finishes what it may be relative to.
 *
 */

int __FindExceptionTable(ExceptionInfo *info, char *retaddr)
{
	extern __declspec(exceptlist) ExceptionTableIndex _exception_table_start__[];
	extern __declspec(exceptlist) ExceptionTableIndex _exception_table_end__[];
	
	info->exception_table_start = _exception_table_start__;
	info->exception_table_end = _exception_table_end__;
	
	return(1);
}


/*
 *	__SkipUnwindInfo(exceptionrecord)
 *
 *	Given a pointer to an Exception Record, skip past the target-specific UnwindInfo
 *	to point at the Range Table. If the UnwindInfo is fixed-length we can implement
 *	this as a simple macro or inline function, but most targets will have variable-length
 *	UnwindInfo.
 *
 */

char *__SkipUnwindInfo(char *p)
{
	unsigned long dummy;
	int has_fpu = *p & UNWIND_HAS_FPU;
	
	p += 1;	/*	skip flag byte	*/
	if (has_fpu)
		p += 1;	/*	skip nb of fp register	*/
	p = __DecodeUnsignedNumber(p, &dummy);	/*	skip frame size	*/
	
	return(p);
}


/*
 *	__TransferControl(info, context, address)
 *
 *	Transfer control back to the program at 'address'. This will always be either
 *	a catch-block or a call to __unexpected() supporting an exception specification.
 *
 *	'address' is of the same form as returned by __AdjustReturnAddress(), i.e.
 *	it is absolute if the exception table index contains absolute addresses, and
 *	relative if it contains relative addresses.
 *
 *	Using the information stored in the ThrowContext we restore all registers, and
 *	restore the stack pointer to its value in the function which called __throw()
 *	(discarding the exception-handling frames but leaving the thrower's frame intact)
 *
 *	Then we fixup the stack frame as needed (e.g. filling in any back-links, guaranteeing
 *	enough space for outgoing arguments, etc) and jump to the target address.
 *
 */

asm void __TransferControl(register ThrowContext *context, register ExceptionInfo *info, register char *address)
{
	.set	noreorder
		
		//	restore the nonvolatile GPRs of the catcher

	MOV		ThrowContext.target.GPR+32,R0;	//	GPR[8]
	MOV.L	@(R0,context),R8;
	MOV		ThrowContext.target.GPR+36,R0;	//	GPR[9]
	MOV.L	@(R0,context),R9;
	MOV		ThrowContext.target.GPR+40,R0;	//	GPR[10]
	MOV.L	@(R0,context),R10;
	MOV		ThrowContext.target.GPR+44,R0;	//	GPR[11]
	MOV.L	@(R0,context),R11;
	MOV		ThrowContext.target.GPR+48,R0;	//	GPR[12]
	MOV.L	@(R0,context),R12;
	MOV		ThrowContext.target.GPR+52,R0;	//	GPR[13]
	MOV.L	@(R0,context),R13;
	MOV		ThrowContext.target.GPR+56,R0;	//	GPR[14]
	MOV.L	@(R0,context),R14;
	//MOV		ThrowContext.target.GPR+60,R0;	//	GPR[15]
	//MOV.L	@(R0,context),R15;
	
#if __SH4__
	MOV.L	ThrowContext.target.FPR+48,R0;	//	FPR[12]
	FMOV.S	@(R0,context),FR12;
	MOV.L	ThrowContext.target.FPR+52,R0;	//	FPR[13]
	FMOV.S	@(R0,context),FR13;
	MOV.L	ThrowContext.target.FPR+56,R0;	//	FPR[14]
	FMOV.S	@(R0,context),FR14;
	MOV.L	ThrowContext.target.FPR+60,R0;	//	FPR[15]
	FMOV.S	@(R0,context),FR15;
#endif

		//	restore SP to stack top at throw: discards exception-handling frames
		//	but not exception temporaries!
	
	MOV.L	ThrowContext.target.throwSP,R0;
	MOV.L	@(R0,context),R15;

		//	add enough space to the frame to accomodate any outgoing arguments
		//	used by the catcher; this is needed because the thrower may not
		//	have as large an argument area as the catcher, and we don't want the
		//	catcher to overwrite locals in the thrower (i.e. the exception object
		//	being thrown) if it makes any calls from the catch-block.

	MOV.L	ThrowContext.target.argument_size,R0;
	MOV.L	@(R0,context),R1;
	SUB		R1,R15

	//	transfer control to the catch-block
	JMP		@address;
}


/*
 *	__throw(throwtype, location, dtor)
 *
 *	Throw an exception object at 'location' of type 'throwtype'. After catch-handling
 *	is complete, the object will be destroyed by calling destructor 'dtor'.
 *
 *	We capture the necessary target-independent (e.g. stack pointer in the thrower,
 *	return address into the thrower) and target-specific (e.g. the values of nonvolatile
 *	registers from the thrower) context information, and remember the throw-type,
 *	exception-object and its destructor, and then jump to the target-independent
 *	throw handler.
 *
 */
 
asm void __throw(register char *throwtype, register void *location, register void *dtor)
{
	.set	noreorder
		//	capture the stack pointer of the thrower, which we will
		//	need when we transfer control back to the catcher
		
	MOV	R15,R1;
	
		//	allocate space for a local ThrowContext
	
	MOV.L	sizeof(ThrowContext),R2;
	SUB	R2,R15
	
		//	capture the nonvolatile GPRs/FPRs of the thrower
	
	MOV.L	R8,@(ThrowContext.target.GPR+32,R15);	//	GPR[8]
	MOV		ThrowContext.target.GPR+36,R0;	//	GPR[9]
	MOV.L	R9,@(R0,R15);
	MOV		ThrowContext.target.GPR+40,R0;	//	GPR[10]
	MOV.L	R10,@(R0,R15);
	MOV		ThrowContext.target.GPR+44,R0;	//	GPR[11]
	MOV.L	R11,@(R0,R15);
	MOV		ThrowContext.target.GPR+48,R0;	//	GPR[12]
	MOV.L	R12,@(R0,R15);
	MOV		ThrowContext.target.GPR+52,R0;	//	GPR[13]
	MOV.L	R13,@(R0,R15);
	MOV		ThrowContext.target.GPR+56,R0;	//	GPR[14]
	MOV.L	R14,@(R0,R15);
	MOV		ThrowContext.target.GPR+60,R0;	//	GPR[15]
	MOV.L	R15,@(R0,R15);
	
#if __SH4__

	MOV.L	ThrowContext.target.FPR+48,R0;	//	FPR[12]
	FMOV.S	FR12,@(R0,R15);
	MOV.L	ThrowContext.target.FPR+52,R0;	//	FPR[13]
	FMOV.S	FR13,@(R0,R15);
	MOV.L	ThrowContext.target.FPR+56,R0;	//	FPR[14]
	FMOV.S	FR14,@(R0,R15);
	MOV.L	ThrowContext.target.FPR+60,R0;	//	FPR[15]
	FMOV.S	FR15,@(R0,R15);
#endif

		//	throwcontext.SP = throwcontext.throwSP = <stack pointer of caller>;
	MOV.L	R1,@(ThrowContext.SP,R15);
	MOV.L	ThrowContext.target.throwSP,R0;
	MOV.L	R1,@(R0,R15);

		//	throwcontext.returnaddr = <return address into caller>;
	STS		PR,R0;
	MOV.L	R0,@(ThrowContext.returnaddr,R15);

		//	remember the throw-type, location, and dtor
	MOV.L	throwtype,@(ThrowContext.throwtype,R15);
	MOV.L	location,@(ThrowContext.location,R15);
	MOV.L	dtor,@(ThrowContext.dtor,R15);
		
		//	call __ThrowHandler(&throwcontext)
	MOV		R15,R4;
	MOV.L	__ThrowHandler,R0;	
	JMP		@R0;
			
		//	we will never return to here!
}
