
/*
 *	ptmf.h	-	pointer-to-member-function support for RISC targets
 *
 *	Copyright © 1997 Metrowerks, Inc.  All Rights Reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	A pointer-to-member-function (PTMF) is represented as a 3-word struct:
 *
 *			nonvirtual member function				virtual member function
 *		+-----------------------------+			+-----------------------------+
 *		|		'this' delta		  |			|		'this' delta		  |
 *		|-----------------------------| 		|-----------------------------|
 *		|			-1				  |			|		 vtbl offset 		  |
 *		|-----------------------------| 		|-----------------------------|
 *		|		function pointer	  |			|		 ventry offset		  |
 *		+-----------------------------+			+-----------------------------+
 *
 *	'this' delta
 *
 *		A value that is added to the 'this' pointer before calling the member function.
 *
 *	vtbl offset
 *
 *		The offset of a (virtual) member functions entry in the vtable.
 *
 *	ventry offset
 *
 *		The offset from the start of an object to its vtable pointer.
 *
 *	function pointer
 *
 *		The absolute address of a (nonvirtual) member function.
 *
 *	A NULL pointer-to-member-function is represented by the structure { 0, 0, 0 };
 *
 *	To work with these pointers the front end generates calls to the following runtime
 *	functions:
 *
 *	extern "C" long __ptmf_test(const PTMF *ptmf);
 *
 *		Test if a pointer to member is not NULL (at least one member != 0).
 *
 *	extern "C" long __ptmf_cmpr(const void *ptmf1, const void *ptmf2);
 *
 *		Compare two pointers to members (result 1: *ptmf1 != *ptmf2; 0: *ptmf1 == *ptmf2).
 *
 *	extern "C" PTMF *__ptmf_cast(long offset, const PTMF *ptmfrom, PTMF *ptmto);
 *
 *		Copy/Cast a pointer to member function.
 *
 *	extern "C" void __ptmf_scall(...);
 *
 *		Call through a pointer-to-member-function. Arguments are in the normal
 *		outgoing argument registers; the first argument is the 'this' pointer.
 *		The PTMF has been left in a target-specific scratch register.
 *
 *	extern "C" void __ptmf_scall4(...);
 *
 *		Call through a pointer-to-member-function that returns an aggregate type.
 *		Arguments are in the normal outgoing argument registers; the first argument
 *		is the hidden argument, and the second argument is the 'this' pointer.
 *		The PTMF has been left in a target-specific scratch register.
 *	
 *	We call a member function from a PTMF like this:
 *
 *		this += ptmf->this_delta;
 *		if (ptmf->vtbl_offset >= 0) {	// virtual member function pointer
 *			vtbl = * (long *) (this + ptmf->func_data.ventry_offset);
 *			fp = * (long *) (vtbl + ptmf->vtbl_offset);
 *		}
 *		else	// nonvirtual member function pointer
 *			fp = ptmf->func_data.func_addr;
 *		jump indirect through fp;
 *
 */


	/*	private types	*/

typedef struct PTMF {
	long	this_delta;				/*	delta to this pointer	*/
	long	vtbl_offset;			/*	offset to member function in vtable	*/
									/*	(-1 -> not a virtual function)		*/
	union {
		void	*func_addr;			/*	nonvirtual function address	*/
		long	ventry_offset;		/*	offset to vtable pointer in object	*/
	} func_data;
} PTMF;


	/*	public data	*/

extern const PTMF __ptmf_null;


	/*	prototypes	*/

#ifdef __cplusplus
extern "C" {
#endif

long __ptmf_test(const PTMF *ptmf);
long __ptmf_cmpr(const PTMF *ptmf1, const PTMF *ptmf2);
void __ptmf_scall(...);
void __ptmf_scall4(...);
PTMF *__ptmf_cast(long offset, const PTMF *ptmfrom, PTMF *ptmto);

#ifdef __cplusplus
}
#endif
