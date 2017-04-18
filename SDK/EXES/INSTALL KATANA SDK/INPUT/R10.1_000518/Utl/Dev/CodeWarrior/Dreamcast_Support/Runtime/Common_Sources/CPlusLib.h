/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	CPlusLib.h												*/
/*	Purpose...:	C++ specific runtime functions							*/
/*  Copyright.: Copyright © 1993-1997 Metrowerks, Inc.					*/
/************************************************************************/

#ifndef __CPLUSLIB__
#define __CPLUSLIB__

#include <stddef.h>

//
//	#define CABI_ZEROOFFSETVTABLE		1
//		
//	forces vtable pointer to point to the first virtual function pointer,
//	the RTTI header will be at offset -sizeof(RTTIVTableHeader)
//	This flag must be set in CABI.c and in MWRTTI.cp
//

//#define __INTEL__ 1	//	define to 1 to test WIN_ABI

#ifdef __INTEL__

#define CABI_ZEROOFFSETVTABLE		1

#else

#define CABI_ZEROOFFSETVTABLE		0

#endif

//
//	invisible constructor/destructor argument handling
//

#ifdef __INTEL__

#define CTORARG_TYPE			int
#define CTORARG_PARTIAL			(0)				//	construct non-virtual bases
#define CTORARG_COMPLETE		(1)				//	construct all bases	

#define CTORCALL_COMPLETE(ctor,objptr)\
	(((void (*)(void *,CTORARG_TYPE))ctor)(objptr,CTORARG_COMPLETE))

#define DTORARG_TYPE			int
#define DTORARG_DELETEFLAG		0x0001			//	delete after destruction
#define DTORARG_VECTORFLAG		0x0002			//	array destruction

#define DTORCALL_COMPLETE(dtor,objptr)\
	(((void (*)(void *,DTORARG_TYPE))dtor)(objptr,0))

#define DTORCALL_PARTIAL(dtor,objptr)\
	(((void (*)(void *))dtor)(objptr))

#else

#define CTORARG_TYPE			short
#define CTORARG_PARTIAL			(0)				//	construct non-virtual bases
#define CTORARG_COMPLETE		(1)				//	construct all bases	

#if __CFM68K__

	long __getA7(void) = { 0x200F };
	void __setA7(long a7:__d0) = { 0x2E40 };

#define CTORCALL_COMPLETE(ctor,objptr)\
	{\
		long __savedA7 = __getA7();\
		(((void (*)(void *,CTORARG_TYPE))ctor)(objptr,CTORARG_COMPLETE));\
		__setA7(__savedA7);\
	}

#else

#define CTORCALL_COMPLETE(ctor,objptr)\
	(((void (*)(void *,CTORARG_TYPE))ctor)(objptr,CTORARG_COMPLETE))

#endif

#define DTORARG_TYPE			short
#define DTORARG_PARTIAL			(0)				//	destroy non-virtual bases	
#define DTORARG_COMPLETE		(-1)			//	destroy all bases	
#define DTORARG_DELETE			(1)				//	destroy all bases and delete object

#define DTORCALL_COMPLETE(dtor,objptr)\
	(((void (*)(void *,DTORARG_TYPE))dtor)(objptr,DTORARG_COMPLETE))

#define DTORCALL_PARTIAL(dtor,objptr)\
	(((void (*)(void *,DTORARG_TYPE))dtor)(objptr,DTORARG_PARTIAL))

#endif

typedef void *ConstructorDestructor;	//	constructor/destructor function	pointer

typedef struct PTMF {
	long	this_delta;					//	delta to this pointer
	long	vtbl_offset;				//	offset of virtual function pointer in vtable (<0: non-virtual function address)
	union {
		void	*func_addr;				//	non-virtual function address
		long	ventry_offset;			//	offset of vtable pointer in class
	}	func_data;
}	PTMF;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MC68K__
extern long		__ptmf_test(const PTMF *ptmf);
extern long		__ptmf_cmpr(const PTMF *ptmf1,const PTMF *ptmf2);
extern void		__ptmf_call(...);
extern void		__ptmf_scall(...);
#endif

extern PTMF		*__ptmf_cast(long offset,const PTMF *ptmfrom,PTMF *ptmto);

extern void		*__copy(char *to,char *from,size_t size);
extern void		*__new_hdl(size_t size);
extern void		__del_hdl(void *hdl);
extern void		*__init_arr(void *memptr,ConstructorDestructor constructor,size_t object_size,size_t nobjects);
extern void		*__new_arr(ConstructorDestructor constructor,size_t object_size,size_t objects);
extern void		__del_arr(void *memptr,ConstructorDestructor destructor);
extern void		__dc_arr(void *mem,ConstructorDestructor con_des,short object_size,short objects);

extern void		__construct_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n);
extern void		__destroy_arr(void *block,ConstructorDestructor dtor,size_t size,size_t n);
extern void		*__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n);
extern void		__destroy_new_array(void *block,ConstructorDestructor dtor);
extern void		*__destroy_new_array2(void *block,ConstructorDestructor dtor);

#ifdef __cplusplus
}
#endif

#endif
