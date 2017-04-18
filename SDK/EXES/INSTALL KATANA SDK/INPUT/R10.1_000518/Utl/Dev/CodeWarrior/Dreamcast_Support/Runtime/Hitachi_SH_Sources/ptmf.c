
/*
 *	ptmf.c	-	pointer-to-member-function support for Hitachi SH series
 *
 *	Copyright © 1999 Metrowerks, Inc.  All Rights Reserved.
 *
 */

#include <ptmf.h>


/*
 *	__ptmf_null	-	a NULL pointer-to-member-function
 *
 */

const PTMF __ptmf_null = { 0, 0, 0 };


/*
 *	__ptmf_test	-	test pointer-to-member-function for null
 *
 *	A PTMF is null if all fields are 0. We return 0 if the PTMF is null, 1 otherwise.
 *
 */

long __ptmf_test(const PTMF *ptmf)
{
	if (ptmf->this_delta == 0 && ptmf->vtbl_offset == 0 && ptmf->func_data.func_addr == 0)
		return(0);

	return(1);
}


/*
 *	__ptmf_cmpr	-	compare two pointer-to-member-functions
 *
 *	Two PTMF's are equal if all fields are equal.
 *	We return 0 if the PTMFs are equal, 1 otherwise.
 *
 */

long __ptmf_cmpr(const PTMF *ptmf1, const PTMF *ptmf2)
{
	if (ptmf1->this_delta == ptmf2->this_delta
	&&	ptmf1->vtbl_offset == ptmf2->vtbl_offset
	&&	ptmf1->func_data.func_addr == ptmf2->func_data.func_addr)
		return(0);
	
	return(1);
}


/*
 *	__ptmf_cast	-	copy/cast a pointer to member function
 *
 */

PTMF *__ptmf_cast(long offset, const PTMF *ptmfrom, PTMF *ptmto)
{
	ptmto->this_delta = ptmfrom->this_delta + offset;
	ptmto->vtbl_offset = ptmfrom->vtbl_offset;
	ptmto->func_data = ptmfrom->func_data;
	return ptmto;
}


/*
 *	__ptmf_scall	-	call through a pointer-to-member-function
 *
 *	The outgoing arguments are in r4-r7; 'this' is in r4. A pointer to the
 *	PTMF is in r0. We call a member function from a PTMF like this:
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

asm void __ptmf_scall(...)
{
	.set	noreorder
	MOV.L	@(PTMF.this_delta,R0),R1	/*	amount to add to 'this'	*/
	MOV.L	@(PTMF.vtbl_offset,R0),R2	/*	-1 or offset to function in vtable	*/
	MOV.L	@(PTMF.func_data,R0),R3		/*	function pointer or offset to vtable	*/
	CMP_PZ	R2							/*	ptmf->vtbl_offset >= 0 ?	*/
	BF_S	jmp_fp
	ADD		R1,R4						/*	this += ptmf->this_delta	*/
	ADD		R4,R3						/*	point to vptr in object	*/
	MOV.L	@R3,R3						/*	get pointer to vtable	*/
	ADD		R2,R3						/*	point to member function in vtable	*/
	MOV.L	@R3,R3						/*	get pointer to member function	*/
jmp_fp:
	JMP		@R3							/*	jump to member function	*/
}


/*
 *	__ptmf_scall4	-	call through a pointer-to-member-function (aggregate return type)
 *
 *	The outgoing arguments are in r6-r9; the hidden argument for the function result
 *	is in r6; 'this' is in r7. A pointer to the PTMF is in r10.  We call a member
 *	function from a PTMF like this:
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

asm void __ptmf_scall4(...)
{
	.set	noreorder
	MOV.L	@(PTMF.this_delta,R0),R1	/*	amount to add to 'this'	*/
	MOV.L	@(PTMF.vtbl_offset,R0),R2	/*	-1 or offset to function in vtable	*/
	MOV.L	@(PTMF.func_data,R0),R3		/*	function pointer or offset to vtable	*/
	CMP_PZ	R2							/*	ptmf->vtbl_offset >= 0 ?	*/
	BF_S	jmp_fp
	ADD		R1,R5						/*	this += ptmf->this_delta	*/
	ADD		R5,R3						/*	point to vptr in object	*/
	MOV.L	@R3,R3						/*	get pointer to vtable	*/
	ADD		R2,R3						/*	point to member function in vtable	*/
	MOV.L	@R3,R3						/*	get pointer to member function	*/
jmp_fp:
	JMP		@R3							/*	jump to member function	*/
}
