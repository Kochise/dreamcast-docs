
/*
 *	ExceptionHandler.h	-	Common C++ Exception Handler interface
 *
 *  Copyright © 1997 Metrowerks, Inc.  All rights reserved.
 *
 */

#ifndef __EXCEPTIONHANDLER_H__
#define __EXCEPTIONHANDLER_H__


#include "CompressedNumbers.h"
#include "ExceptionTables.h"
#include "ExceptionHandlerTS.h"


/*
 *	ThrowContext
 *
 *	This structure records all the necessary information available at the point
 *	where an exception is thrown, and is also used to step back through the pending
 *	stack frames as we look for a catch-block.
 *
 */

typedef struct ThrowContext {
	/*	information about the exception being thrown	*/
	char*			throwtype;		/*	throw type argument (0L: rethrow: throw; )	*/
	void*			location;		/*	location argument (0L: rethrow: throw; )	*/
	void*			dtor;			/*	dtor argument	*/
	/*	information about an exception being -rethrown-	*/
	CatchInfo		*catchinfo;		/*	pointer to rethrow CatchInfo (or 0L)	*/
	/*	information about the current context as we walk the stack	*/
	char*			returnaddr;		/*	return address	*/
	char*			SP;				/*	stack pointer during unwind (used for linkage)	*/
	char*			FP;				/*	frame pointer during unwind (used for locals)	*/
	TargetContext	target;			/*	target-specific information	*/
}	ThrowContext;


/*
 *	ExceptionInfo
 *
 *	Info from the Exception Tables for the exception being thrown.
 *
 */

typedef struct ExceptionInfo {
	char*			current_function;	/*	pointer to current function's executable code	*/
	char*			exception_record;	/*	pointer to current function's exception table	*/
	char*			action_pointer;		/*	pointer to current exception action	*/
	ExceptionTableIndex*	exception_table_start;	/*	pointer to start of exception table index	*/
	ExceptionTableIndex*	exception_table_end;	/*	pointer to end of exception table index	*/
	TargetExceptionInfo		target;					/*	target-specific exception table info	*/
}	ExceptionInfo;


/*
 *	ThrowHandler	-	entry-point to target-independent throw handler
 *
 *	After the target-specific implementation of __throw() saves all of the relevant
 *	throw information in a ThrowContext, it calls this target-independent portion
 *	to do all of the necessary C++ exception-handling.
 *
 */

void __ThrowHandler(ThrowContext *context);


#endif
