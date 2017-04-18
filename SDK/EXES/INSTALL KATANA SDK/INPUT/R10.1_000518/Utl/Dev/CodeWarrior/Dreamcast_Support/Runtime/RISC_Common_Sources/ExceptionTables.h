
/*
 *	ExceptionTables.h	-	Common C++ Exception Table Format
 *
 *  Copyright © 1997 Metrowerks, Inc.  All rights reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	In order to support correct and efficient C++ exception-handling, the compiler
 *	generates a comprehensive set of tables for each function in a program, which
 *	describe the proper actions to be taken when an exception is thrown from any
 *	point within the function.
 *
 *	The compiler also generates an index entry for each function which points to
 *	the corresponding exception table. When an exception is thrown, the index is
 *	used to locate the exception-handling info for each return-address on the
 *	runtime stack.
 *
 *	Exception Table Index
 *	---------------------
 *
 *	Each executable program (or shared library on targets which support them)
 *	has an index to the exception tables for functions in the program:
 *
 *		__exception_table_start__:
 *			<index to exception table for function #1>
 *			<index to exception table for function #2>
 *							...
 *			<index to exception table for function #N>
 *		__exception_table_end__:
 *
 *	An index table entry is a 3-word structure with the following format:
 *
 *	|<---- 32 bits ---->|<----- 32 bits ---->|<---------- 32 bits --------->|
 *	+-------------------+-----------------+--+------------------------------+
 *	| function address	|  function size  |DS|	ET ptr or abbrev ET entry	|
 *	+-------------------+-----------------+--+------------------------------+
 *
 *	"function address" is an absolute (or .text-relative) pointer to the code for
 *	the function corresponding to this entry. "function size" is the size in bytes
 *	of the function's code. The LSB of function size is used for a "Direct Store"
 *	flag: if 1 then following word contains a (target-specific) "abbreviated"
 *	Exception Table for trivial functions; otherwise it contains a pointer to the
 *	Exception Table for the function.
 *
 *	The entries are sorted in order of increasing "start PC" so that the table may be
 *	binary-searched. An exception table index entry is generated for any function that
 *	is compiled with Exception Handling enabled; exceptions cannot be thrown through
 *	the frame of a function which has no entry.
 *
 *	Exception Table
 *	---------------
 *
 *	Each function has a corresponding Exception Table of the following form:
 *
 *	|<-- variable length -->|<-- variable length -->|<- 8 bits ->|<-- variable length -->|
 *	+-----------------------+-----------------------+------------+-----------------------+
 *	|	Unwind Info			|	Range Table			|	  0	 	 |	Action Table		 |
 *	+-----------------------+-----------------------+------------+-----------------------+
 *
 *	Unwind Info
 *
 *	This is a target-specific variable-length structure that contains all information
 *	necessary to unwind the stack frame for the function. This may include:
 *
 *		# of saved registers (GPRs, FPRs, condition registers, etc)
 *		size of stack frame (if there is no back-link in the frame)
 *		size of outgoing argument area (for targets with fixed-length frames)
 *		frame pointer register (if a separate frame pointer is used)
 *
 *	For "trivial" functions with no exception actions we use an abbreviated form of the
 *	unwind info that fits in 32 bits (if possible for the target machine). The abbreviated
 *	exception table is stored directly in the Exception Table Index to save space.
 *
 *	Range Table
 *
 *	The range table is a list of PC ranges and their corresponding exception actions:
 *
 *	|<-- variable length -->|<-- variable length -->|<-- variable length -->|
 *	+-----------------------+-----------------------+-----------------------+
 *	|	Start PC (delta)	|		Length			|  Offset to Actions    |
 *	+-----------------------+-----------------------+-----------------------+
 *
 *	The elements of a Range Table entry are stored in a variable-length format so
 *	that small values can be represented using only 1 or 2 bytes. The "Start PC"
 *	is the offset from the end of the previous range to the current range.
 *	"Length" is the length of the range. "Offset to Actions" is an offset from
 *	the start of the Exception Table to the set of actions for this range.
 *
 *	Action Table
 *
 *	The action table is an unstructured stream of actions which must be performed
 *	when an exception is thrown. Typical actions are:
 *
 *		Destroy a local variable
 *		Delete an object
 *		Catch a given exception
 *
 *	Each action starts with an 8-bit action type byte:
 *
 *	|<-1 bit->|<-1 bit-->|<-1 bit-->|<--5 bits--->|
 *	+---------+----------+----------+-------------+
 *	| END BIT | OPT1 BIT | OPT2 BIT | ACTION TYPE |
 *	+---------+----------+----------+-------------+
 *
 *	This is followed by additional action-specific fields. Most fields are signed
 *	or unsigned integers stored in the variable-length format, or 32-bit addresses
 *	stored in target-endian format. The fields are packed--there are no pad bytes
 *	for aligning them on any particular boundary--and must be extracted from the
 *	tables accordingly.
 *
 *	The last action in a list has the END BIT set. The OPT1 and OPT2 bits are
 *	reserved for use by individual actions, documented below.
 *
 */

#ifndef __EXCEPTIONTABLES_H__
#define __EXCEPTIONTABLES_H__


	/*	Exception Table Indices (one per function)	*/

typedef struct ExceptionTableIndex {
	char*			function_address;	/*	absolute (or relative?) address of function	*/
	unsigned long	function_size;		/*	length of function (low bit is ignored)		*/
	char*			exception_table;	/*	absolute (or relative?) address of exception	*/
										/*	table, or abbreviated exception table itself	*/
										/*	if (function_size & DIRECT_STORE_MASK) == 1		*/
} ExceptionTableIndex;

#define	FUNCTION_SIZE_MASK	0xFFFFFFFE	/*	mask relevant bits of 'function_size' field		*/
#define	DIRECT_STORE_MASK	0x00000001	/*	indicates exception table is stored directly	*/

#define	FUNCTION_SIZE(eti)		((eti)->function_size & FUNCTION_SIZE_MASK)
#define	DIRECT_STORED(eti)		(((eti)->function_size & DIRECT_STORE_MASK) != 0)


	/*	Exception Action Type	*/

typedef char exaction_type;				/*	may be signed or unsigned, whichever is better	*/

#define EXACTION_ENDBIT			0x80	/*	set on last action in an action list	*/
#define EXACTION_OPT1BIT		0x40	/*	reserved for use in specific actions	*/
#define EXACTION_OPT2BIT		0x20	/*	reserved for use in specific actions	*/
#define EXACTION_MASK			0x1F	/*	use this to extract action type code	*/

	/*	Action-specific Option Bits	*/

#define	REGCOND		EXACTION_OPT1BIT	/*	condition variable is in a register	*/
#define	REGPTR		EXACTION_OPT2BIT	/*	pointer variable is in a register	*/

	/*	Exception Actions	*/

#define	EXACTION_ENDOFLIST				0
/*
 *	End of list of actions. This is never explicitly generated in an action list,
 *	but is used internally following an action which has the EXACTION_ENDBIT set.
 *
 */

#define	EXACTION_BRANCH					1
/*
 *	Continue processing at another location in the action table.
 *
 *		struct ex_branch {
 *			exaction_type	action;		//	EXACTION_BRANCH
 *			var_int			target;		//	action-relative offset to target action
 *		}
 *
 */

#define	EXACTION_DESTROYLOCAL			2
/*
 *	Destroy a local variable.
 *
 *		struct ex_destroylocal {
 *			exaction_type	action;		//	EXACTION_DESTROYLOCAL
 *			var_int			local;		//	frame-relative offset to local variable
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define	EXACTION_DESTROYLOCALCOND		3
/*
 *	Destroy a local variable only if a condition variable is TRUE.
 *
 *		struct ex_destroylocalcond {
 *			exaction_type	action;		//	EXACTION_DESTROYLOCALCOND [+REGCOND]
 *			var_int			cond;		//	frame-relative offset or reg# of condition variable
 *			var_int			local;		//	frame-relative offset to local variable
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define	EXACTION_DESTROYLOCALPOINTER	4
/*
 *	Destroy the object pointed at by a local pointer.
 *
 *		struct ex_destroylocalpointer {
 *			exaction_type	action;		//	EXACTION_DESTROYLOCALPOINTER [+REGPTR]
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define	EXACTION_DESTROYLOCALARRAY		5
/*
 *	Destroy each element of a local array variable.
 *
 *		struct ex_destroylocalarray {
 *			exaction_type	action;		//	EXACTION_DESTROYLOCALARRAY
 *			var_int			array;		//	frame-relative offset of local array
 *			uns_var_int		elements;	//	number of array elements
 *			uns_var_int		elemsize;	//	size of one array element
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define EXACTION_DESTROYBASE			6
/*
 *	Destroy a member of an object pointed at by a local pointer.
 *
 *		struct ex_destroybase {
 *			exaction_type	action;		//	EXACTION_DESTROYBASE [+REGPTR]
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			var_int			offset;		//	offset of member in complete object
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define EXACTION_DESTROYMEMBER			7
/*
 *	Destroy a member of an object pointed at by a local pointer.
 *
 *		struct ex_destroymember {
 *			exaction_type	action;		//	EXACTION_DESTROYMEMBER [+REGPTR]
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			var_int			offset;		//	offset of member in complete object
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define EXACTION_DESTROYMEMBERCOND		8
/*
 *	Destroy a member of an object only if a condition variable is TRUE.
 *
 *		struct ex_destroymembercond {
 *			exaction_type	action;		//	EXACTION_DESTROYMEMBERCOND [+REGCOND] [+REGPTR]
 *			var_int			cond;		//	frame-relative offset or reg# of condition variable
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			var_int			offset;		//	offset of member in complete object
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define EXACTION_DESTROYMEMBERARRAY		9
/*
 *	Destroy each element of an array member of an object pointed at by a local pointer.
 *
 *		struct ex_destroymemberarray {
 *			exaction_type	action;		//	EXACTION_DESTROYMEMBERARRAY [+REGPTR]
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			var_int			offset;		//	offset of member in complete object
 *			uns_var_int		elements;	//	number of array elements
 *			uns_var_int		elemsize;	//	size of one array element
 *			void*			dtor;		//	absolute pointer to destructor
 *		}
 *
 */

#define EXACTION_DELETEPOINTER			10
/*
 *	Call operate delete() for a local pointer variable.
 *
 *		struct ex_deletepointer {
 *			exaction_type	action;		//	EXACTION_DELETEPOINTER [+REGPTR]
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			void*			deletefunc;	//	absolute pointer to operator delete()
 *		}
 *
 */

#define EXACTION_DELETEPOINTERCOND		11
/*
 *	Call operate delete() only if a condition variable is TRUE.
 *
 *		struct ex_deletepointercond {
 *			exaction_type	action;		//	EXACTION_DELETEPOINTERCOND [+REGCOND] [+REGPTR]
 *			var_int			cond;		//	frame-relative offset or reg# of condition variable
 *			var_int			ptr;		//	frame-relative offset or reg# of local pointer
 *			void*			deletefunc;	//	absolute pointer to operator delete()
 *		}
 *
 */

#define EXACTION_CATCHBLOCK				12
/*
 *	Catch an exception of a specific type, or all exceptions if catch_type == 0.
 *	
 *		struct ex_catchblock {
 *			exaction_type	action;		//	EXACTION_CATCHBLOCK
 *			char*			catch_type;	//	absolute pointer to catch type info
 *			uns_var_int		pcoffset;	//	function-relative offset to catch label
 *			var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *		}
 *
 */			

#define EXACTION_ACTIVECATCHBLOCK		13
/*
 *	Indicates an active catch block--used to find most recent exception for "throw;"
 *
 *		struct ex_activecatchblock {
 *			exaction_type	action;		//	EXACTION_ACTIVECATCHBLOCK
 *			var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *		}
 *
 */

#define EXACTION_TERMINATE				14
/*
 *	Call terminate() function.
 *
 */

#define EXACTION_SPECIFICATION			15
/*
 *	Note the exception specification for the function. If one of these is encountered
 *	during a throw() and the thrown exception is not listed in the specification,
 *	then we transfer control to 'pcoffset' (which should call unexpected())
 *
 *		struct ex_specification {
 *			exaction_type	action;		//	EXACTION_SPECIFICATION
 *			uns_var_int		nspecs;		//	number of specifications (0-n)
 *			uns_var_int		pcoffset;	//	function-relative offset to catch label
 *			var_int			cinfo_ref;	//	frame-relative offset to local CatchInfo struct
 *			char*			specs[];	//	array of absolute pointers to catch type info
 *		}
 *
 */


#endif
