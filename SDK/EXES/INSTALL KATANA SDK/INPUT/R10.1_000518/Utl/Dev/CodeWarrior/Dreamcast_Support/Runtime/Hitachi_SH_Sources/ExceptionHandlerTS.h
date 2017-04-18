
/*
 *	ExceptionHandlerTS.h	-	Target-specific C++ Exception Handler support - Hitachi SH
 *
 *  Copyright © 1999 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	Here we define any data structures, macros, and functions which implement
 *	the target-specific aspects of the standard C++ Exception Handler.
 *
 *
 */

#ifndef __EXCEPTIONHANDLERTS_H__
#define	__EXCEPTIONHANDLERTS_H__


typedef struct ThrowContext ThrowContext;
typedef struct ExceptionInfo ExceptionInfo;


/*
 *	TargetContext
 *
 *	This structure contains the target-specific context information needed to
 *	handle an exception. Typically the target context contains all of the (nonvolatile)
 *	general-purpose (and floating-point) registers, and any other registers (e.g.
 *	condition registers) that are preserved across function calls.
 *
 *	This structure is initialized by __throw() when an exception is thrown, and then
 *	updated by __PopStackFrame() as frames are popped. If it is used to store any
 *	target-specific unwind info, then that portion is initialized by __SetupFrameInfo()
 *	below.
 *
 */

typedef struct TargetContext {
	/*	exception context	*/
	unsigned long	GPR[16];			/*	GPR0-GPR15	(not all are saved/restored)	*/
#if __SH4__
	unsigned long	FPR[16];			/*	FPR0-FPR15	(not all are saved/restored)	*/
#endif
	char			*throwSP;			/*	stack pointer on entry to __throw	*/
	/*	unwind info	*/
	unsigned long	frame_size;			/*	size of (fixed portion of) current frame	*/
	unsigned long	argument_size;		/*	size of outgoing argument area in current frame	*/
	int				n_saved_GPRs;		/*	# of GPRs saved in current frame	*/
#if __SH4__
	int				n_saved_FPRs;		/*	# of FPRs saved in current frame	*/
#endif
	int				has_flushback;		/*	1 -> frame has 16 byte flushback area for r4-r7	*/
	int				has_frame_ptr;		/*	1 -> frame uses r14 as frame pointer	*/
} TargetContext;

/*
 *	TargetExceptionInfo
 *
 *	This structure contains any "global" target-specific information needed by the
 *	exception handler. This information is initialized by __FindExceptionTable()
 *	and can be used by any of the routines below.
 *
 *	An example of TargetExceptionInfo might be the start of the code and/or data
 *	sections, which may be used if the exception tables contain relative pointers
 *	to destructors. On many machines, no additional information will be needed.
 *
 */

typedef struct TargetExceptionInfo {
	int				dummy;				/*	no additional info needed for Hitachi SH	*/
} TargetExceptionInfo;

 
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

extern char *__PopStackFrame(ThrowContext *context, ExceptionInfo *info);

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

extern void __SetupFrameInfo(ThrowContext *context, ExceptionInfo *info);

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

extern int __FindExceptionTable(ExceptionInfo *info, char *retaddr);

/*
 *	__SkipUnwindInfo(exceptionrecord)
 *
 *	Given a pointer to an Exception Record, skip past the target-specific UnwindInfo
 *	to point at the Range Table. If the UnwindInfo is fixed-length we can implement
 *	this as a simple macro or inline function, but most targets will have variable-length
 *	UnwindInfo.
 *
 */

extern char *__SkipUnwindInfo(char *exceptionrecord);

/*
 *	__FunctionPointer(info, context, fp)
 *
 *	Do whatever is necessary to convert a function pointer as stored in the
 *	exception tables into a real C/C++ function pointer. If the exception tables
 *	contain absolute pointers we can just return 'fp'. If they contain relative
 *	pointers then we need to add the base of the code section stored in the
 *	target-specific ExceptionInfo, or possibly a base register stored in the
 *	target-specific Context. This hook is provided solely to permit relative
 *	pointers in the exception tables for those targets where it makes sense.
 *
 */

#define __FunctionPointer(info, context, fp)	(fp)
	/*	Hitachi SH uses absolute pointers in exception tables	*/

/*
 *	__AdjustReturnAddress(info, context, retaddr)
 *
 *	Do whatever is necessary to convert a return address into something that
 *	can be compared with the function pointer stored in the Exception Table Index.
 *	If the index contains absolute pointers, we can return 'retaddr' unmodified.
 *	If the index contains relative pointers, we must subtract off the base of
 *	the code section or other base register as stored in the target-specific
 *	ExceptionInfo or Context.
 *
 */

#define	__AdjustReturnAddress(info, context, retaddr)	(retaddr)
	/*	Hitachi SH uses absolute pointers in exception tables	*/

/*
 *	__LocalVariable(context, offset)
 *
 *	Return a pointer to the local variable at offset 'offset' from the current
 *	frame indicated by 'context'.
 *
 *	Typically we simply add the given offset to 'context->FP' which has already
 *	been correctly initialized in __SetupFramePointer().
 *
 */

#define __LocalVariable(context, offset)	((context)->FP + (offset))

/*
 *	__Register(context, regno)
 *
 *	Return the contents of the register 'regno' from the given context;
 *	'regno' is a register number as encoded in the exception tables.
 *
 *	Typically we index an array of GPRs contained the TargetContext struct
 *	by the register number 'regno'. Note that FPRs, if available on the
 *	target, will not appear in the exception tables and do not need to be
 *	handled here.
 *
 */

#define	__Register(context, regno)	((context)->target.GPR[regno])

/*
 *	__TransferControl(info, context, address)
 *
 *	Transfer control back to the program at 'address'. This will always be either
 *	a catch-block or a call to __unexpected() supporting an exception specification.
 *
 *	'address' is of the same form as returned by __AdjustReturnAddress(), i.e.
 *	it is absolute if the exception table index contains absolute addresses, and relative
 *	if it contains relative addresses.
 *
 *	Using the information stored in the ThrowContext we restore all registers, and
 *	restore the stack pointer to its value in the function which called __throw()
 *	(discarding the exception-handling frames but leaving the thrower's frame intact)
 *
 *	Then we fixup the stack frame as needed (e.g. filling in any back-links, guaranteeing
 *	enough space for outgoing arguments, etc) and jump to the target address.
 *
 */

extern void __TransferControl(ThrowContext *context, ExceptionInfo *info, char *address);


#endif
