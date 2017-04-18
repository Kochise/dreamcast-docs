
/*
 *	ExceptionHandler.c	-	Common C++ Exception Handler
 *
 *  Copyright © 1999 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	The compiler and runtime library conspire to implement a "zero runtime overhead"
 *	exception-handling mechanism. The compiler generates Exception Tables for each
 *	function as described in ExceptionTables.h. Here we implement the target-independent
 *	portion of the runtime code that is executed when an exception is thrown.
 *
 *	When an exception is thrown, the compiler generates a call to __throw(). At the
 *	point that we enter __throw() the runtime stack looks like this:
 *
 *				+-----------------------+
 *				|						|
 *				|	Catcher's Frame		|
 *				|						|
 *				+-----------------------+
 *				|	Arbitrary Frame		|
 *				+-----------------------+
 *				| 		...				|
 *				+-----------------------+
 *				|	Arbitrary Frame		|
 *				+-----------------------+
 *				|						|		NOTE: The exception object being thrown
 *				|	Thrower's Frame		|		appears as a local variable in the
 *				|						|		thrower's frame
 *		SP =>	+-----------------------+
 *
 *	The first thing we do is go through the pending stack frames looking for a frame
 *	that corresponds to a function which can catch the exception (or a function whose
 *	specification indicates that the exception cannot be thrown). If we don't find
 *	a catcher then we call terminate().
 *
 *	After we've found the catcher, we unwind the stack by visiting each stack frame
 *	and applying any required exception actions for that frame, e.g. calling destructors
 *	for local variables.
 *	
 *	Finally, we transfer control to the catch-block. Because the exception object being
 *	thrown is a local variable in the stack frame of the thrower, we can't actually discard
 *	the intervening stack space until after the catch processing. So, when control is
 *	transferred to the catcher, the runtime stack looks like this:
 *
 *				+-----------------------+
 *				|						|
 *				|	Catcher's Frame		|
 *				|						|
 *		FP =>	|-----------------------|
 *				|						|
 *				|	Unused Space		|
 *				|						|
 *				|-----------------------|
 *				|	Thrower's Locals	|
 *				|-----------------------|
 *				|						|
 *				|	Unused Space		|
 *				|						|
 *		SP =>	+-----------------------+
 *
 *	FP is some target-specific GPR used as a frame pointer. On RISC machines which use
 *	a static outgoing argument area below the local variables in the frame, we may need
 *	to adjust SP downwards a bit to accomodate the outgoing arguments of the catcher--if
 *	the catch-block makes a function-call, we don't want to overwrite the local exception
 *	temporary from the thrower's frame.
 *
 *	The compiler generates code at the end of the catch-block to restore the stack pointer
 *	to its value at the start of the try-block, so after catch processing the runtime
 *	stack will look like this:
 *
 *				+-----------------------+
 *				|						|
 *				|	Catcher's Frame		|
 *				|						|
 *	SP => FP =>	+-----------------------+
 *
 *	Since we are setting SP to its value saved at the start of the try-block, it may
 *	not be the same as FP if the catcher was already executing in a catch-block at the
 *	time of the throw.
 *
 *	Most of the exception processing is target-independent. Routines for performing
 *	target-specific operations like restoring registers during unwinding, or transferring
 *	control to the catcher, are implemented in ExceptionHandlerTS.cp/.h.
 *
 */

#include <stdlib.h>
#include <CPlusLib.h>
#include <exception.h>
#include "NMWException.h"
#include "ExceptionHandler.h"


	/*	private types	*/

enum { SKIP	= 0, APPLY = 1 };			/*	indicates whether exception actions are to be	*/
										/*	ignored or applied	*/

typedef void (*DeleteFunc)(void *);		/*	type of 'operator delete' function	*/

typedef struct ActionIterator {
	ExceptionInfo	info;				/*	copy of info for exception being thrown	*/
	ThrowContext	context;			/*	copy of throw context	*/
} ActionIterator;

typedef struct ex_catchblock {
	char*			catch_type;			/*	absolute pointer to catch type info	*/
	unsigned long	pcoffset;			/*	function-relative offset to catch label	*/
	long			cinfo_ref;			/*	frame-relative offset to local CatchInfo struct	*/
} ex_catchblock;

typedef struct ex_activecatchblock {
	long			cinfo_ref;			/*	frame-relative offset to local CatchInfo struct	*/
} ex_activecatchblock;

typedef struct ex_specification {
	unsigned long	nspecs;				/*	number of specifications (0-n)	*/
	unsigned long	pcoffset;			/*	function-relative offset to catch label	*/
	long			cinfo_ref;			/*	frame-relative offset to local CatchInfo struct	*/
	char*			specs;				/*	array of absolute pointers to catch type info	*/
} ex_specification;


/*
 *	BinarySearch	-	binary-search the exception table index for the given return address
 *
 *	The given return address may be either relative or absolute; the caller must perform
 *	any arithmetic so that it matches the values stored in the exception table index.
 *
 *	We return the pointer to the index entry containing the return address, or 0 if not found.
 *
 */

static ExceptionTableIndex *BinarySearch(ExceptionTableIndex *table, unsigned long tablesize, char *return_address)
{
	ExceptionTableIndex *p;
	long i, m, n;
	
		/*	binary-search the table to find an exception index entry which	*/
		/*	contains the given return address	*/
	
	for (i = 0, n = tablesize - 1; i <= n;) {
		p = &table[m = (i + n) >> 1];
		if (return_address < p->function_address)
			n = m - 1;
		else if (return_address > p->function_address + FUNCTION_SIZE(p))
			i = m + 1;
		else
			return(p);
	}
	
		/*	not found	*/
	
	return(0);
}


/*
 *	FindExceptionRecord	-	locate the Exception Table for the given Return Address
 *
 *	We search the Exception Table Index to find the Exception Table corresponding to
 *	the function containing the given return address. We leave the pointer to the
 *	Exception Table in 'info->exception_record', and the pointer to the action list
 *	for the given return address in 'info->action_pointer'. We also leave the pointer
 *	to the start of the function containing the return address in 'info->current_function'.
 *
 */

static void FindExceptionRecord(char *return_address, ExceptionInfo *info)
{
	ExceptionTableIndex *exceptiontable;
	char *rangetable;
	unsigned long return_offset;
	unsigned long currentPC;
	unsigned long deltaPC;
	unsigned long length;
	unsigned long actions;
	
			/*	so far we haven't found anything	*/
		
	info->exception_record = 0;
	info->action_pointer = 0;

		/*	find the Exception Table Index corresponding to 'return_address'	*/
		/*	(in info->exception_table_start and info->exception_table_end)		*/
	
	if (!__FindExceptionTable(info, return_address))
		return;
		
		/*	adjust 'return_address' as needed, e.g. for relative function	*/
		/*	pointers in the exception tables	*/
	
	return_address = __AdjustReturnAddress(info, context, return_address);
		
		/*	binary-search the index for the function containing 'return_address'	*/
	
	if (!(exceptiontable = BinarySearch(info->exception_table_start,
					info->exception_table_end - info->exception_table_start,
					return_address)))
		return;
		
		/*	use the index entry to find the exception table	*/
	
	if (DIRECT_STORED(exceptiontable))
		info->exception_record = (char *) &exceptiontable->exception_table;
	else
		info->exception_record = exceptiontable->exception_table;
		
		/*	get the function-relative offset to the return address	*/
	
	info->current_function = exceptiontable->function_address;
	return_offset = return_address - exceptiontable->function_address;
	
		/*	get the start of the range table	*/
	
	rangetable = __SkipUnwindInfo(info->exception_record);
	
		/*	linear-search the range table to find a range that includes	*/
		/*	the return-address. 'deltaPC' is the offset from the end of	*/
		/*	the previous range to the start of the current range		*/

	for (currentPC = 0;;) {
		rangetable = __DecodeUnsignedNumber(rangetable, &deltaPC);
		if (deltaPC == 0)	/*	end of range table	*/
			return;
		rangetable = __DecodeUnsignedNumber(rangetable, &length);
		rangetable = __DecodeUnsignedNumber(rangetable, &actions);
		currentPC += deltaPC;
		if (return_offset < currentPC)	/*	return_offset is not in any range	*/
			return;
		currentPC += length;
		if (return_offset <= currentPC)	/*	return_offset is in -this- range	*/
			break;
	}
		
		/*	get the pointer to the actions to perform for an exception 	*/
		/*	thrown from 'return_address'	*/

	info->action_pointer = info->exception_record + actions;
}


/*
 *	DecodeCatchBlock	-	decode an EXACTION_CATCHBLOCK exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_CATCHBLOCK
 *		char*			catch_type;	//	absolute pointer to catch type info
 *		uns_var_int		pcoffset;	//	function-relative offset to catch label
 *		var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *
 *	We return the decoded catch-block info in an ex_catchblock struct.
 *
 */

inline void DecodeCatchBlock(char *ap, ex_catchblock *cb)
{
	ap += sizeof(exaction_type);
	ap = __DecodeAddress(ap, &cb->catch_type);
	ap = __DecodeUnsignedNumber(ap, &cb->pcoffset);
	ap = __DecodeSignedNumber(ap, &cb->cinfo_ref);
}


/*
 *	DecodeActiveCatchBlock	-	decode an EXACTION_ACTIVECATCHBLOCK exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_ACTIVECATCHBLOCK
 *		var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *
 *	We return the decoded active-catch-block info in an ex_activecatchblock struct.
 *
 */

inline void DecodeActiveCatchBlock(char *ap, ex_activecatchblock *acb)
{
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &acb->cinfo_ref);
}


/*
 *	DecodeSpecification	-	decode an EXACTION_SPECIFICATION exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_SPECIFICATION
 *		uns_var_int		nspecs;		//	number of specifications (0-n)
 *		uns_var_int		pcoffset;	//	function-relative offset to catch label
 *		var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *		char*			specs[];	//	array of absolute pointers to catch type info
 *
 *	We return the decoded specification info in an ex_specification struct.
 *
 */

inline void DecodeSpecification(char *ap, ex_specification *sp)
{
	ap += sizeof(exaction_type);
	ap = __DecodeUnsignedNumber(ap, &sp->nspecs);
	ap = __DecodeUnsignedNumber(ap, &sp->pcoffset);
	ap = __DecodeSignedNumber(ap, &sp->cinfo_ref);
	sp->specs = ap;	/*	point into (unaligned) specs array in exception table	*/
}


/*
 *	Branch	-	decode/apply an EXACTION_BRANCH exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_BRANCH
 *		var_int			target;		//	action-relative offset to target action
 */

inline void Branch(ExceptionInfo *info, ThrowContext *context)
{
	long target;
	
		/*	decode the exception action	*/
		
	__DecodeSignedNumber(info->action_pointer + sizeof(exaction_type), &target);
	
		/*	update the action pointer	*/
	
	info->action_pointer += target;	/*	effect branch	*/
}


/*
 *	DestroyLocal	-	decode/apply an EXACTION_DESTROYLOCAL exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYLOCAL
 *		var_int			local;		//	frame-relative offset to local variable
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyLocal(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	long local;
	void *dtor;
	
		/*	decode the exception action	*/
	
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &local);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor),
			__LocalVariable(context, local));
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DestroyLocalCond	-	decode/apply an EXACTION_DESTROYLOCALCOND exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYLOCALCOND [+REGCOND]
 *		var_int			cond;		//	frame-relative offset or reg# of condition variable
 *		var_int			local;		//	frame-relative offset to local variable
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyLocalCond(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	int regcond;
	long cond, local;
	void *dtor;
	local_cond_type destroyIt;
	
		/*	decode the exception action	*/
	
	regcond = *(exaction_type *)ap & REGCOND;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &cond);
	ap = __DecodeSignedNumber(ap, &local);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regcond)
			destroyIt = (local_cond_type) __Register(context, cond);
		else
			destroyIt = *(local_cond_type *)__LocalVariable(context, cond);
		
		if (destroyIt) {
			DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor),
				__LocalVariable(context, local));
		}
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DecodeDestroyLocalPointer	-	decode/apply an EXACTION_DESTROYLOCALPOINTER exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYLOCALPOINTER [+REGPTR]
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyLocalPointer(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	int regptr;
	long ptr;
	void *dtor, *objectptr;
	
		/*	decode the exception action	*/
	
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regptr)
			objectptr = (void *) __Register(context, ptr);
		else
			objectptr = *(void **)__LocalVariable(context, ptr);
		
		DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), objectptr);
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DestroyLocalArray	-	decode/apply an EXACTION_DESTROYLOCALARRAY exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYLOCALARRAY
 *		var_int			array;		//	frame-relative offset of local array
 *		uns_var_int		elements;	//	number of array elements
 *		uns_var_int		elemsize;	//	size of one array element
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyLocalArray(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	long array;
	unsigned long nelements, elemsize, i;
	void *dtor;
	char *arrayptr;
	
		/*	decode the exception action	*/
	
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &array);
	ap = __DecodeUnsignedNumber(ap, &nelements);
	ap = __DecodeUnsignedNumber(ap, &elemsize);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		arrayptr = (char *) __LocalVariable(context, array);
		for (arrayptr += nelements * elemsize, i = nelements; i > 0; i--) {
			arrayptr -= elemsize;
			DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), arrayptr);
		}
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DestroyBase	-	decode/apply an EXACTION_DESTROYBASE exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYBASE [+REGPTR]
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		var_int			offset;		//	offset of member in complete object
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyBase(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	int regptr;
	long ptr, offset;
	void *dtor;
	char *objectptr;
	
		/*	decode the exception action	*/
	
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeSignedNumber(ap, &offset);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regptr)
			objectptr = (char *) __Register(context, ptr);
		else
			objectptr = *(char **)__LocalVariable(context, ptr);
		
		DTORCALL_PARTIAL(__FunctionPointer(info, context, dtor), objectptr + offset);
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DestroyMember	-	decode/apply an EXACTION_DESTROYMEMBER exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYMEMBER [+REGPTR]
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		var_int			offset;		//	offset of member in complete object
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyMember(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	int regptr;
	long ptr, offset;
	void *dtor;
	char *objectptr;
	
		/*	decode the exception action	*/
	
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeSignedNumber(ap, &offset);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regptr)
			objectptr = (char *) __Register(context, ptr);
		else
			objectptr = *(char **)__LocalVariable(context, ptr);
		
		DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), objectptr + offset);
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DestroyMemberCond	-	decode/apply an EXACTION_DESTROYMEMBERCOND exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYMEMBERCOND [+REGCOND] [+REGPTR]
 *		var_int			cond;		//	frame-relative offset or reg# of condition variable
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		var_int			offset;		//	offset of member in complete object
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyMemberCond(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	int regptr, regcond;
	long cond, ptr, offset;
	void *dtor;
	char *objectptr;
	vbase_ctor_arg_type destroyIt;
	
		/*	decode the exception action	*/
	
	regcond = *(exaction_type *)ap & REGCOND;
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &cond);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeSignedNumber(ap, &offset);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regcond)
			destroyIt = (vbase_ctor_arg_type) __Register(context, cond);
		else
			destroyIt = *(vbase_ctor_arg_type *)__LocalVariable(context, cond);
			
		if (destroyIt) {
			if (regptr)
				objectptr = (char *) __Register(context, ptr);
			else
				objectptr = *(char **)__LocalVariable(context, ptr);
		
			DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), objectptr + offset);
		}
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DestroyMemberArray	-	decode/apply an EXACTION_DESTROYMEMBERARRAY exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DESTROYMEMBERARRAY [+REGPTR]
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		var_int			offset;		//	offset of member in complete object
 *		uns_var_int		elements;	//	number of array elements
 *		uns_var_int		elemsize;	//	size of one array element
 *		void*			dtor;		//	absolute pointer to destructor
 */

inline void DestroyMemberArray(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	int regptr;
	long ptr, offset;
	unsigned long nelements, elemsize, i;
	void *dtor;
	char *arrayptr;
	
		/*	decode the exception action	*/
	
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeSignedNumber(ap, &offset);
	ap = __DecodeUnsignedNumber(ap, &nelements);
	ap = __DecodeUnsignedNumber(ap, &elemsize);
	ap = __DecodeAddress(ap, &dtor);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regptr)
			arrayptr = (char *) __Register(context, ptr) + offset;
		else
			arrayptr = *(char **)__LocalVariable(context, ptr) + offset;
		
		for (arrayptr += nelements * elemsize, i = nelements; i > 0; i--) {
			arrayptr -= elemsize;
			DTORCALL_COMPLETE(__FunctionPointer(info, context, dtor), arrayptr);
		}
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DeletePointer	-	decode/apply an EXACTION_DELETEPOINTER exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DELETEPOINTER [+REGPTR]
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		void*			deletefunc;	//	absolute pointer to operator delete()
 */

inline void DeletePointer(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	long ptr;
	void *deletefunc;
	char *objectptr;
	int regptr;
	
		/*	decode the exception action	*/
	
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeAddress(ap, &deletefunc);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regptr)
			objectptr = (char *) __Register(context, ptr);
		else
			objectptr = *(char **)__LocalVariable(context, ptr);
			
		((DeleteFunc) __FunctionPointer(info, context, deletefunc))(objectptr);
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	DeletePointerCond	-	decode/apply an EXACTION_DELETEPOINTERCOND exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_DELETEPOINTERCOND [+REGCOND] [+REGPTR]
 *		var_int			cond;		//	frame-relative offset or reg# of condition variable
 *		var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *		void*			deletefunc;	//	absolute pointer to operator delete()
 */

inline void DeletePointerCond(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	long cond, ptr;
	void *deletefunc;
	char *objectptr;
	int regptr, regcond;
	local_cond_type deleteIt;
	
		/*	decode the exception action	*/
	
	regcond = *(exaction_type *)ap & REGCOND;
	regptr = *(exaction_type *)ap & REGPTR;
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &cond);
	ap = __DecodeSignedNumber(ap, &ptr);
	ap = __DecodeAddress(ap, &deletefunc);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		if (regcond)
			deleteIt = (local_cond_type) __Register(context, cond);
		else
			deleteIt = *(local_cond_type *)__LocalVariable(context, cond);

		if (deleteIt) {
			if (regptr)
				objectptr = (char *) __Register(context, ptr);
			else
				objectptr = *(char **)__LocalVariable(context, ptr);
			
			((DeleteFunc) __FunctionPointer(info, context, deletefunc))(objectptr);
		}
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	CatchBlock	-	decode/apply an EXACTION_CATCHBLOCK exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_CATCHBLOCK
 *		char*			catch_type;	//	absolute pointer to catch type info
 *		uns_var_int		pcoffset;	//	function-relative offset to catch label
 *		var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 */

inline void CatchBlock(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	void *catch_type;
	unsigned long pcoffset;
	long cinfo_ref;
	
		/*	decode the exception action	*/
	
	ap += sizeof(exaction_type);
	ap = __DecodeAddress(ap, &catch_type);
	ap = __DecodeUnsignedNumber(ap, &pcoffset);
	ap = __DecodeSignedNumber(ap, &cinfo_ref);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		/*	nothing to do	*/
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	ActiveCatchBlock	-	decode/apply an EXACTION_ACTIVECATCHBLOCK exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_ACTIVECATCHBLOCK
 *		var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 */

inline void ActiveCatchBlock(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	long cinfo_ref;
	CatchInfo *catchinfo;
	
		/*	decode the exception action	*/
	
	ap += sizeof(exaction_type);
	ap = __DecodeSignedNumber(ap, &cinfo_ref);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		catchinfo = (CatchInfo *) __LocalVariable(context, cinfo_ref);
		if (catchinfo->dtor) {
			//	re-throwing exception from this block
			if (context->location == catchinfo->location) {
				//	pass destruction responsibility to re-thrown exception
				context->dtor = catchinfo->dtor;
			}
			else
				DTORCALL_COMPLETE(catchinfo->dtor,catchinfo->location);
		}
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	Specification	-	decode/apply an EXACTION_SPECIFICATION exception action
 *
 *	This action is encoded like this in the exception tables:
 *
 *		exaction_type	action;		//	EXACTION_SPECIFICATION
 *		uns_var_int		nspecs;		//	number of specifications (0-n)
 *		uns_var_int		pcoffset;	//	function-relative offset to catch label
 *		var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *		char*			specs[];	//	array of absolute pointers to catch type info
 */

inline void Specification(int apply, ExceptionInfo *info, ThrowContext *context)
{
	char *ap = info->action_pointer;
	unsigned long nspecs, pcoffset;
	long cinfo_ref;
	
		/*	decode the exception action	*/
	
	ap += sizeof(exaction_type);
	ap = __DecodeUnsignedNumber(ap, &nspecs);
	ap = __DecodeUnsignedNumber(ap, &pcoffset);
	ap = __DecodeSignedNumber(ap, &cinfo_ref);
	ap += nspecs * sizeof(char*);
	
		/*	apply it (if we are unwinding)	*/
	
	if (apply) {
		/*	nothing to do	*/
	}
	
		/*	update the action pointer	*/
	
	info->action_pointer = ap;
}


/*
 *	CurrentAction	-	return the current exception action type from an action iterator
 *
 *	The ActionIterator is used to quickly scan the set of all pending exception actions
 *	(including those in frames further up the stack) to search for something specific,
 *	e.g. a catch-block for the current exception, or an active catch block (for rethrow)
 *
 *	The ActionIterator has been initialized with a copy of the current ExceptionInfo and
 *	ThrowContext. We can modify these copies as we step through the set of all exception
 *	actions that apply at this point in the program.
 *
 */

static exaction_type CurrentAction(const ActionIterator *iter)
{
	return(iter->info.action_pointer ? *(exaction_type *)iter->info.action_pointer & EXACTION_MASK : EXACTION_ENDOFLIST);
}


/*
 *	NextAction		-	advance to the next exception action from an action iterator
 *
 *	The ActionIterator is used to quickly scan the set of all pending exception actions
 *	(including those in frames further up the stack) to search for something specific,
 *	e.g. a catch-block for the current exception, or an active catch block (for rethrow)
 *
 *	The ActionIterator has been initialized with a copy of the current ExceptionInfo and
 *	ThrowContext. We can modify these copies as we step through the set of all exception
 *	actions that apply at this point in the program.
 *
 *	If we've reached the end of the list of actions for the current frame, we
 *	pop down the stack (by modifying just the -copy- of ThrowContext) to the next frame
 *	and start returning the associated actions there.
 *
 */

static exaction_type NextAction(ActionIterator *iter)
{
	ExceptionInfo *info = &iter->info;
	ThrowContext *context = &iter->context;
	exaction_type action;

	for (;;) {
	
			/*	if there are no more actions for this frame, pop down to the next	*/
			/*	frame and start processing the actions there	*/
			
		if (!info->action_pointer || *(exaction_type *)info->action_pointer & EXACTION_ENDBIT) {
			FindExceptionRecord(__PopStackFrame(context, info), info);
			if (!info->exception_record)
				terminate();	/*	couldn't find a matching exception record	*/
			__SetupFrameInfo(context, info);
			if (!info->action_pointer)
				continue;		/*	exception record has no actions for return address	*/
		}
		
			/*	otherwise, advance to the next action in the current action list	*/
			
		else {
			switch (*(exaction_type *)info->action_pointer & EXACTION_MASK) {
				case EXACTION_DESTROYLOCAL:
					DestroyLocal(SKIP, info, context);
					break;
				case EXACTION_DESTROYLOCALCOND:
					DestroyLocalCond(SKIP, info, context);
					break;
				case EXACTION_DESTROYLOCALPOINTER:
					DestroyLocalPointer(SKIP, info, context);
					break;
				case EXACTION_DESTROYLOCALARRAY:
					DestroyLocalArray(SKIP, info, context);
					break;
				case EXACTION_DESTROYBASE:
					DestroyBase(SKIP, info, context);
					break;
				case EXACTION_DESTROYMEMBER:
					DestroyMember(SKIP, info, context);
					break;
				case EXACTION_DESTROYMEMBERCOND:
					DestroyMemberCond(SKIP, info, context);
					break;
				case EXACTION_DESTROYMEMBERARRAY:
					DestroyMemberArray(SKIP, info, context);
					break;
				case EXACTION_DELETEPOINTER:
					DeletePointer(SKIP, info, context);
					break;
				case EXACTION_DELETEPOINTERCOND:
					DeletePointerCond(SKIP, info, context);
					break;
				case EXACTION_CATCHBLOCK:
					CatchBlock(SKIP, info, context);
					break;
				case EXACTION_ACTIVECATCHBLOCK:
					ActiveCatchBlock(SKIP, info, context);
					break;
				case EXACTION_SPECIFICATION:
					Specification(SKIP, info, context);
					break;
				default:	/*	error	*/
					terminate();
			}
		}
		
			/*	get the new action type, but don't return EXACTION_BRANCH to the caller	*/
		
		while ((action = *(exaction_type *)info->action_pointer & EXACTION_MASK) == EXACTION_BRANCH)
			Branch(info, context);
		
			/*	return the new action type	*/

		return(action);
	}
}


/*
 *	UnwindStack		-	unwind all stack frames between thrower and catcher
 *
 *	We apply the exception actions for each frame that is being unwound as we go.
 *
 */
 
static void UnwindStack(ThrowContext *context, ExceptionInfo *info, char *catcher)
{
	exaction_type action;

#pragma exception_terminate	/*	this will prevent exception exits during unwinding	*/

	for (;;) {
	
			/*	end of action list? go on to next frame	*/

		if (!info->action_pointer) {
			FindExceptionRecord(__PopStackFrame(context, info), info);
			if (!info->exception_record)
				terminate();	/*	couldn't find a matching exception record	*/
			__SetupFrameInfo(context, info);
			if (!info->action_pointer)
				continue;		/*	exception record has no actions for return address	*/
		}
		
			/*	get next action for this frame	*/

		action = *(exaction_type *)info->action_pointer;
		
			/*	dispatch on action type and apply action	*/

		switch (action & EXACTION_MASK) {
			case EXACTION_BRANCH:
				Branch(info, context);
				break;
			case EXACTION_DESTROYLOCAL:
				DestroyLocal(APPLY, info, context);
				break;
			case EXACTION_DESTROYLOCALCOND:
				DestroyLocalCond(APPLY, info, context);
				break;
			case EXACTION_DESTROYLOCALPOINTER:
				DestroyLocalPointer(APPLY, info, context);
				break;
			case EXACTION_DESTROYLOCALARRAY:
				DestroyLocalArray(APPLY, info, context);
				break;
			case EXACTION_DESTROYBASE:
				DestroyBase(APPLY, info, context);
				break;
			case EXACTION_DESTROYMEMBER:
				DestroyMember(APPLY, info, context);
				break;
			case EXACTION_DESTROYMEMBERCOND:
				DestroyMemberCond(APPLY, info, context);
				break;
			case EXACTION_DESTROYMEMBERARRAY:
				DestroyMemberArray(APPLY, info, context);
				break;
			case EXACTION_DELETEPOINTER:
				DeletePointer(APPLY, info, context);
				break;
			case EXACTION_DELETEPOINTERCOND:
				DeletePointerCond(APPLY, info, context);
				break;
			case EXACTION_CATCHBLOCK:
				if (catcher == info->action_pointer)
					return;	/*	finished unwinding	*/
				CatchBlock(SKIP, info, context);
				break;
			case EXACTION_ACTIVECATCHBLOCK:
				ActiveCatchBlock(APPLY, info, context);
				break;
			case EXACTION_SPECIFICATION:
				if (catcher == info->action_pointer)
					return;	/*	finished unwinding	*/
				Specification(SKIP, info, context);
				break;
			default:	/*	error	*/
				terminate();
		}
		
			/*	check for end of list of actions	*/

		if (action & EXACTION_ENDBIT)
			info->action_pointer = 0;
	}
}


/*
 *	FindMostRecentException	-	find the exception that is currently being handled
 *
 *	We search all pending exception actions for our return address (searching up
 *	the stack as necessary) to find an active catch block.
 *
 */

static CatchInfo *FindMostRecentException(ThrowContext *context, ExceptionInfo *info)
{
	ActionIterator iter;
	exaction_type action;
	CatchInfo *catchinfo;
	ex_activecatchblock acb;
	
		/*	find an active catch-block	*/
	
	iter.info = *info;
	iter.context = *context;
	for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
		switch (action) {
			case EXACTION_ACTIVECATCHBLOCK:
				break;
	
			case EXACTION_ENDOFLIST:
			case EXACTION_DESTROYLOCAL:
			case EXACTION_DESTROYLOCALCOND:
			case EXACTION_DESTROYLOCALPOINTER:
			case EXACTION_DESTROYLOCALARRAY:
			case EXACTION_DESTROYBASE:
			case EXACTION_DESTROYMEMBER:
			case EXACTION_DESTROYMEMBERCOND:
			case EXACTION_DESTROYMEMBERARRAY:
			case EXACTION_DELETEPOINTER:
			case EXACTION_DELETEPOINTERCOND:
			case EXACTION_CATCHBLOCK:
			case EXACTION_SPECIFICATION:
				continue;

			case EXACTION_TERMINATE:
			default:
				terminate();	/*	cannot find most recent exception	*/
		}
		break;
	}
	
		/*	fill in the info for the exception being processed by this catch-block	*/
		
	DecodeActiveCatchBlock(iter.info.action_pointer, &acb);
	catchinfo = (CatchInfo *) __LocalVariable(&iter.context, acb.cinfo_ref);
	context->throwtype = (char *) catchinfo->typeinfo;
	context->location = catchinfo->location;
	context->dtor = 0;	/*	original active catch block is still responsible for destruction	*/
	context->catchinfo = catchinfo;
	
		/*	return the pointer to the CatchInfo struct for the most recent exception	*/
	
	return(catchinfo);
}


/*
 *	IsInSpecification	-	see if the given exception type is in the specification list
 *
 *	The list of exception type pointers in the specification is not guaranteed to
 *	be aligned, so we use __DecodeAddress() to fetch them one by one.
 *
 */

static int IsInSpecification(char *extype, ex_specification *spec)
{
	char *specptr = spec->specs;
	char *spectype;
	long dummy;
	int i;
	
	for (i = 0; i < spec->nspecs; i++) {
		__DecodeAddress(specptr, &spectype);
		if (__throw_catch_compare(extype, spectype, &dummy))
			return(1);
		specptr += 4;
	}
	
	return(0);
}


/*
 *	__unexpected	-	unexpected exception handler
 *
 *	This will be called from within a function containing the specification
 *	that the current exception does not match. We call the user's unexpected()
 *	routine and deal with any exceptions it may throw, or we call terminate().
 *
 */

void __unexpected(CatchInfo* catchinfo)
{
	char *unexp = (char *) catchinfo->stacktop;	/*	we saved this in HandleUnexpected()	*/
	ex_specification spec;

#pragma exception_magic

	try {
		unexpected();
	}
	catch(...) {
		DecodeSpecification(unexp, &spec);
		//	unexpected throws an exception => check if the exception matches the specification
		if(IsInSpecification((char *)((CatchInfo *)&__exception_magic)->typeinfo, &spec))
		{	//	new exception is in specification list => rethrow
			throw;
		}
#ifdef _MSL_USING_NAMESPACE
		if(IsInSpecification("!std::bad_exception!!", &spec))
		{	//	"bad_exception" is in specification list => throw bad_exception()
			throw bad_exception();
		}
#else
		if(IsInSpecification("!bad_exception!!", &spec))
		{	//	"bad_exception" is in specification list => throw bad_exception()
			throw bad_exception();
		}
#endif
		//	cannot handle exception => terminate();
	}
	terminate();
}


/*
 *	HandleUnexpected	-	handle an unexpected exception
 *
 *	If we encounter an exception specification and the exception we are throwing
 *	is not in the list of expected exceptions, we transfer control back to the
 *	routine which contains the specification. (It will call __unexpected() which
 *	will in turn call unexpected() and watch for more exceptions)
 *
 */

static void HandleUnexpected(ThrowContext *context, ExceptionInfo *info, ex_specification *spec, char *unexp)
{
	CatchInfo	*catchinfo;

#pragma exception_terminate		/*	this will prevent exception exits during unwinding	*/

		/*	unwind the stack to the failing specification	*/
		
	UnwindStack(context, info, unexp);
	
		/*	initialize the CatchInfo struct	*/
	
	catchinfo = (CatchInfo *) __LocalVariable(context, spec->cinfo_ref);
	catchinfo->location	= context->location;
	catchinfo->typeinfo	= context->throwtype;
	catchinfo->dtor	= context->dtor;
	catchinfo->stacktop = unexp;	/*	__unexpected will never call __end_catch,	*/
									/*	so we can reuse this field	*/
	
		/*	transfer control to the exception handler	*/
	
	__TransferControl(context, info, info->current_function + spec->pcoffset);
}


/*
 *	FindExceptionHandler	-	find a catch-block that can catch the exception being thrown
 *
 *	If en route we find a function whose exception specification disallows the
 *	exception being thrown, we effect a call to unexpected().
 *
 */

static char *FindExceptionHandler(ThrowContext *context, ExceptionInfo *info, long *result_offset)
{
	ActionIterator iter;
	exaction_type action;
	ex_catchblock handler;
	ex_specification spec;
	
		/*	find a catch-block that can catch the thrown exception type	*/
	
	iter.info = *info;
	iter.context = *context;
	for (action = CurrentAction(&iter);; action = NextAction(&iter)) {
		switch (action) {
			case EXACTION_CATCHBLOCK:
				DecodeCatchBlock(iter.info.action_pointer, &handler);
				if (!__throw_catch_compare(context->throwtype, handler.catch_type, result_offset))
					continue;
				break;

			case EXACTION_SPECIFICATION:
				DecodeSpecification(iter.info.action_pointer, &spec);
				if (!IsInSpecification(context->throwtype, &spec))
					HandleUnexpected(context, info, &spec, iter.info.action_pointer);
					/*	we will never return from this function call	*/
				continue;

			case EXACTION_ENDOFLIST:
			case EXACTION_DESTROYLOCAL:
			case EXACTION_DESTROYLOCALCOND:
			case EXACTION_DESTROYLOCALPOINTER:
			case EXACTION_DESTROYLOCALARRAY:
			case EXACTION_DESTROYBASE:
			case EXACTION_DESTROYMEMBER:
			case EXACTION_DESTROYMEMBERCOND:
			case EXACTION_DESTROYMEMBERARRAY:
			case EXACTION_DELETEPOINTER:
			case EXACTION_DELETEPOINTERCOND:
			case EXACTION_ACTIVECATCHBLOCK:
				continue;

			case EXACTION_TERMINATE:
			default:
				terminate();	/*	cannot find matching catch block	*/
		}
		break;
	}
	
		/*	return the pointer to the EXACTION_CATCHBLOCK action	*/
	
	return(iter.info.action_pointer);
}


/*
 *	SetupCatchInfo	-	remember information about the exception we're catching
 *
 *	We store the throw type, exception temporary location, and other necessary
 *	information in the local CatchInfo struct that has been allocated in the
 *	stack frame of the catcher. Among other things, we use this to implement
 *	"throw;"
 *
 */

static void SetupCatchInfo(ThrowContext *context, long cinfo_ref, long result_offset)
{
	CatchInfo *catchinfo = (CatchInfo *) __LocalVariable(context, cinfo_ref);
	
	catchinfo->location = context->location;
	catchinfo->typeinfo = context->throwtype;
	catchinfo->dtor	 = context->dtor;

	if (*context->throwtype == '*') {
		/*	pointer match (create a pointer copy with adjusted offset)	*/
		catchinfo->sublocation	= &catchinfo->pointercopy;
		catchinfo->pointercopy	= *(long *)context->location + result_offset;
	}
	else {
		/*	traditional or class match (directly adjust offset)	*/
		catchinfo->sublocation	= (char *)context->location + result_offset;
	}
}


/*
 *	__ThrowHandler	-	throw (rethrow) current exception
 *
 *	We assume that __throw() has placed the relevant target-independent and
 *	target-specific information in the given ThrowContext.
 *
 */

void __ThrowHandler(ThrowContext *context)
{
	ExceptionInfo	info;
	char			*catchblock;
	ex_catchblock	handler;
	long 			result_offset;
	
		/*	find the first Exception Table	*/
	
	FindExceptionRecord(context->returnaddr, &info);
	if (!info.exception_record)
		terminate();	/*	cannot find matching exception record	*/
	__SetupFrameInfo(context, &info);
	
		/*	if we're rethrowing the most recent exception, find it;	*/
		/*	context->catchinfo is used when unwinding an active catch block to	*/
		/*	determine whether an exception temporary must be destroyed	*/

	if (!context->throwtype)
		context->catchinfo = FindMostRecentException(context, &info);
	else
		context->catchinfo = 0;
		
		/*	find an exception handler that can catch the exception we're throwing	*/
	
	catchblock = FindExceptionHandler(context, &info, &result_offset);
	DecodeCatchBlock(catchblock, &handler);
	
		/*	unwind the stack to the frame containing the handler; this sets the		*/
		/*	register state in 'context' properly for the control-transfer to the	*/
		/*	catcher	*/
	
	UnwindStack(context, &info, catchblock);
	
		/*	remember information about the exception being caught	*/
	
	SetupCatchInfo(context, handler.cinfo_ref, result_offset);
	
		/*	transfer control to the exception handler	*/
	
	__TransferControl(context, &info, info.current_function + handler.pcoffset);
}


/*
 *	__end__catch	-	deinitialize CatchInfo struct
 *
 *	The compiler generates a call to this at the end of a catch-block to call
 *	any destructor for the temporary object that was caught.
 *
 */

void __end__catch(CatchInfo *catchinfo)
{
	if (catchinfo->location && catchinfo->dtor)
		DTORCALL_COMPLETE(catchinfo->dtor, catchinfo->location);
}
