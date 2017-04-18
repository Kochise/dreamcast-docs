/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	MWException.h											*/
/*	Purpose...:	portable exception handling								*/
/*  Copyright.: Copyright © 1993-1997 Metrowerks, Inc.					*/
/************************************************************************/

#ifndef __MWEXCEPTIONS__
#define __MWEXCEPTIONS__

////	[this section needs to be copied from CException.h

typedef short	vbase_ctor_arg_type;
typedef char	local_cond_type;

typedef struct CatchInfo {
	void			*location;				//	pointer to complete exception object
	void			*typeinfo;				//	pointer to complete exception object's typeinfo
	void			*dtor;					//	pointer to complete exception object's destructor function (0: no destructor)
	void			*sublocation;			//	pointer to handlers subobject in complete exception object
	long			pointercopy;			//	adjusted pointer copy for pointer matches (sublocation will point to the loaction)
	void			*stacktop;				//	pointer to handlers stack top (reused for exception specification in specification handler)
}	CatchInfo;

////	[this section needs to be copied from CException.h]

typedef struct DestructorChain {			//	global destructor chain
	struct DestructorChain	*next;			//	pointer to next destructor chain element
	void					*destructor;	//	pointer to destructor function
	void					*object;		//	pointer to memory location (0L: element is marker)
}	DestructorChain;

#ifdef __cplusplus
extern "C" {
#endif

#if __CFM68K__
#pragma import on
#endif

extern DestructorChain	*__global_destructor_chain;
extern void				*__register_global_object(void *object,void *destructor,void *regmem);
extern void				__destroy_global_chain(void);

extern void				__init__catch(CatchInfo* catchinfo);
extern void				__end__catch(CatchInfo* catchinfo);
extern void				__throw(char *throwtype,void *location,void *dtor);
extern char				__throw_catch_compare(const char *throwtype,const char *catchtype,long *offset_result);
extern void				__unexpected(CatchInfo* catchinfo);
void __call_static_initializers(void);  // hh 971215 added per John McEnerney's instructions
#ifdef __POWERPC__
extern int				__register_fragment(char *code_start,char *code_end,char *data_start,char *data_end,
											char *exception_start,char *exception_end,char *TOC);
extern void				__unregister_fragment(int fragmentID);
#endif

#if __CFM68K__
#pragma import reset
#endif

#ifdef __cplusplus
}
#endif
#endif

// hh 971215 added prototype per John McEnerney's instructions
