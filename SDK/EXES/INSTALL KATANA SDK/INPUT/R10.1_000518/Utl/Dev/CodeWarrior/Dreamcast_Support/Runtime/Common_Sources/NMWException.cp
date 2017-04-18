/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	MWException.cp											*/
/*	Purpose...:	portable exception handling								*/
/*  Copyright.: Copyright © 1993-1999 Metrowerks, Inc.					*/
/************************************************************************/

#ifdef __MC68K__
#pragma far_data off
#endif

#define __NOSTRING__	//	do not include <string>

//#include <Types.h>    // hh 971215 commented out per John McEnerney's instructions
//#include <stdlib.h>
#include <cstdlib>		// as 990622 build using MSL instead of hitachi header
#include <CPlusLib.h>
#include <exception.h>
#include "NMWException.h"

#ifdef _MSL_USING_NAMESPACE      // hh 971207 Added namespace support
	namespace std {
#endif

static void dthandler()		{ abort(); };			//	default terminate handler function
static terminate_handler	thandler = dthandler;	//	pointer to terminate handler function
static void duhandler()		{ terminate(); };		//	default unexpected handler function
static unexpected_handler	uhandler = duhandler;	//	pointer to unexpected handler function

/************************************************************************/
/*	Purpose..: 	Set a terminate handler function						*/
/*	Input....:	pointer to terminate handler function					*/
/*	Return...:	---														*/
/************************************************************************/
extern terminate_handler set_terminate(terminate_handler handler) throw()  // hh 980102 added exception specific
{
	terminate_handler old=thandler; thandler=handler; return old;
}

/************************************************************************/
/*	Purpose..: 	Terminate exception handling							*/
/*	Input....:	---														*/
/*	Return...:	--- (shall not return to caller)						*/
/************************************************************************/
extern void terminate()
{
	thandler();
}

/************************************************************************/
/*	Purpose..: 	Set an unexpected handler function						*/
/*	Input....:	pointer to unexpected handler function					*/
/*	Return...:	---														*/
/************************************************************************/
extern unexpected_handler set_unexpected(unexpected_handler handler) throw()  // hh 980102 added exception specific
{
	unexpected_handler old=uhandler; uhandler=handler; return old;
}

/************************************************************************/
/*	Purpose..: 	Handle unexpected exception								*/
/*	Input....:	---														*/
/*	Return...:	--- (shall not return to caller)						*/
/************************************************************************/
extern void unexpected()
{
	uhandler();
}

#ifdef _MSL_USING_NAMESPACE
	}
#endif

/************************************************************************/
/*	Purpose..: 	Register a global object for later destruction			*/
/*	Input....:	pointer to global object								*/
/*	Input....:	pointer to destructor function							*/
/*	Input....:	pointer to global registration structure				*/
/*	Return...:	pointer to global object (pass thru)					*/
/************************************************************************/
#if !defined(__POWERPC__) && !defined(__CFM68K__)		//	only needed for classic 68K ...

extern void *__register_global_object(void *object,void *destructor,void *regmem)
{
	((DestructorChain *)regmem)->next=__global_destructor_chain;
	((DestructorChain *)regmem)->destructor=destructor;
	((DestructorChain *)regmem)->object=object;
	__global_destructor_chain=(DestructorChain *)regmem;

	return object;
}

#endif

/************************************************************************/
/* Purpose..: Compare a throw and a catch type							*/
/* Input....: pointer to throw type										*/
/* Input....: pointer to catch type (0L: catch(...)						*/
/* Return...: true: can catch; false: cannot catch						*/
/************************************************************************/
extern char __throw_catch_compare(const char *throwtype,const char *catchtype,long *offset_result)
{
	const char	*cptr1,*cptr2;

	*offset_result=0;	
	if((cptr2=catchtype)==0)
	{	//	catch(...)
		return true;
	}
	cptr1=throwtype;

	if(*cptr2=='P')
	{	//	catch(cv T *)
		cptr2++;
		if(*cptr2=='C') cptr2++;
		if(*cptr2=='V') cptr2++;
		if(*cptr2=='v')
		{	//	catch(cv void *)
			if(*cptr1=='P' || *cptr1=='*')
			{	//	throw T*;
				return true;
			}
		}
		cptr2=catchtype;
	}

	switch(*cptr1)
	{	//	class pointer/reference throw
	case '*':
	case '!':
		if(*cptr1++!=*cptr2++) return false;
		for(;;)
		{	//	class name compare loop
			if(*cptr1==*cptr2++)
			{
				if(*cptr1++=='!')
				{	//	class match found / get offset
					long offset;

					for(offset=0; *cptr1!='!';) offset=offset*10+*cptr1++-'0';
					*offset_result=offset; return true;
				}
			}
			else
			{
				while(*cptr1++!='!') ;			//	skip class name
				while(*cptr1++!='!') ;			//	skip offset
				if(*cptr1==0) return false;		//	no more class names => no match
				cptr2=catchtype+1;				//	retry with next class name
			}
		}
		return false;
	}

	while((*cptr1=='P' || *cptr1=='R') && *cptr1==*cptr2)
	{	//	pointer/reference catch => match cv-qualifiers
		cptr1++; cptr2++;
		if(*cptr2=='C')
		{	//	ignore 'const' in throw type
			if(*cptr1=='C') cptr1++;
			cptr2++;
		}
		if(*cptr1=='C') return false;	//	throw type is more cv-qualified

		if(*cptr2=='V')
		{	//	ignore 'volatile' in throw type
			if(*cptr1=='V') cptr1++;
			cptr2++;
		}
		if(*cptr1=='V') return false;	//	throw type is more cv-qualified
	}

	//	plain type throw catch
	for(; *cptr1==*cptr2; cptr1++,cptr2++) if(*cptr1==0) return true;
	return false;
}

#if defined(__MC68K__)	

/************************************************************************/
/*	Purpose..: 	Initialize a new allocated array of objects				*/
/*	Input....:	pointer to allocated memory (+8 bytes) (0L: error)		*/
/*	Input....:	pointer to default constructor function	(or 0L)			*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	pointer to first object in array						*/
/************************************************************************/
extern void *__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor_arg,size_t size,size_t n)
{
	char	*ptr;

	if((ptr=(char *)block)!=0L)
	{
		//	store number of allocated objects and size of one object at the beginnig of the allocated block
		*(size_t *)ptr=size;
		*(size_t *)(ptr+sizeof(size_t))=n;
		ptr+=sizeof(size_t)*2;

		if(ctor)
		{	//	call constructor to initialize array
			volatile ConstructorDestructor	dtor=dtor_arg;	//	force reference to dtor
			char							*p;
			size_t							i;

			#pragma exception_arrayinit
			//	this #pragma adds partial array construction exception action (ptr,dtor,size,i)

			for(i=0,p=ptr; i<n; i++,p+=size)
			{
				CTORCALL_COMPLETE(ctor,p);
			}
		}
	}
	return ptr;	//	return pointer to first object;
}

/************************************************************************/
/*	Purpose..: 	Construct an array of objects							*/
/*	Input....:	pointer to array memory									*/
/*	Input....:	pointer to default constructor function					*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	---														*/
/************************************************************************/
extern void __construct_array(void *ptr,ConstructorDestructor ctor,ConstructorDestructor dtor_arg,size_t size,size_t n)
{
	volatile ConstructorDestructor	dtor=dtor_arg;	//	force reference to dtor
	char							*p;
	size_t							i;

	#pragma exception_arrayinit
	//	this #pragma adds partial array construction exception action (ptr,dtor,size,i)

	for(i=0,p=(char *)ptr; i<n; i++,p+=size)
	{
		CTORCALL_COMPLETE(ctor,p);
	}
}

#else

//	class __partial_array_destructor
//
//		This class is used to guarantee correct destruction of partially
//		constructed arrays if an exception is thrown from an array-element constructor.
//		We use the members of this class to keep track of the partially-constructed
//		state of the array. If the destructor for this class is called and the
//		array was not fully-constructed, we must have thrown an exception, so we
//		destroy each fully-constructed element of the array in reverse order.

class __partial_array_destructor {
private:
	void*					p;		//	pointer to start of array being constructed
	size_t					size;	//	size of each array element
	size_t					n;		//	# of elements being constructed
	ConstructorDestructor	dtor;	//	pointer to destructor for elements or 0
public:
	size_t					i;		//	current element being constructed
	
	__partial_array_destructor(void* array, size_t elementsize, size_t nelements, ConstructorDestructor destructor)
	{
		p=array; size=elementsize; n=nelements; dtor=destructor; i=n;
	}
		
	~__partial_array_destructor()
	{
		char *ptr;
		
		if(i<n && dtor)
		{
			for(ptr=(char *)p+size*i; i>0; i--)
			{
				ptr-=size;
				DTORCALL_COMPLETE(dtor,ptr);
			}
		}
	}
};

/************************************************************************/
/*	Purpose..: 	Initialize a new allocated array of objects				*/
/*	Input....:	pointer to allocated memory (+8 bytes) (0L: error)		*/
/*	Input....:	pointer to default constructor function	(or 0L)			*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	pointer to first object in array						*/
/************************************************************************/
extern void *__construct_new_array(void *block,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n)
{
	char	*ptr;

	if((ptr=(char *)block)!=0L)
	{
		//	store number of allocated objects and size of one object at the beginnig of the allocated block
		*(size_t *)ptr=size;
		*(size_t *)(ptr+sizeof(size_t))=n;
		ptr+=sizeof(size_t)*2;

		if(ctor)
		{	//	call constructor to initialize array
			__partial_array_destructor pad(ptr,size,n,dtor);
			char	*p;

			for(pad.i=0,p=(char *)ptr; pad.i<n; pad.i++,p+=size) CTORCALL_COMPLETE(ctor,p);
		}
	}
	return ptr;	//	return pointer to first object;
}

/************************************************************************/
/*	Purpose..: 	Construct an array of objects							*/
/*	Input....:	pointer to array memory									*/
/*	Input....:	pointer to default constructor function					*/
/*	Input....:	pointer to destructor function (or 0L)					*/
/*	Input....:	size of one array element								*/
/*	Input....:	number of array elements								*/
/*	Return...:	---														*/
/************************************************************************/
extern void __construct_array(void *ptr,ConstructorDestructor ctor,ConstructorDestructor dtor,size_t size,size_t n)
{
	__partial_array_destructor pad(ptr,size,n,dtor);
	char	*p;

	for(pad.i=0,p=(char *)ptr; pad.i<n; pad.i++,p+=size) CTORCALL_COMPLETE(ctor,p);
}

#endif

/************************************************************************/
/*	Purpose..: 	Destroy an array of objects								*/
/*	Input....:	pointer to array memory									*/
/*	Input....:	pointer to destructor function							*/
/*	Input....:	size of one object										*/
/*	Input....:	number of objects										*/
/*	Return...:	---														*/
/************************************************************************/
extern void __destroy_arr(void *block,ConstructorDestructor dtor,size_t size,size_t n)
{
	char	*p;

	for(p=(char *)block+size*n; n>0; n--)
	{
		p-=size;
		DTORCALL_COMPLETE(dtor,p);
	}
}

/************************************************************************/
/*	Purpose..: 	Delete an array of objects								*/
/*	Input....:	pointer to first object	(can be NULL)					*/
/*	Input....:	pointer to destructor function							*/
/*	Return...:	---														*/
/************************************************************************/
extern void __destroy_new_array(void *block,ConstructorDestructor dtor)
{
	if(block)
	{
		if(dtor)
		{
			size_t	i,objects,objectsize;
			char	*p;

			objectsize=*(size_t *)((char *)block-2*sizeof(size_t));
			objects=*(size_t *)((char *)block-sizeof(size_t));
			p=(char *)block+objectsize*objects;
			for(i=0; i<objects; i++)
			{
				p-=objectsize;
				DTORCALL_COMPLETE(dtor,p);
			}
		}
		#if __MWERKS__>=0x2020
		::operator delete[] ((char *)block-2*sizeof(size_t));
		#else
		::operator delete ((char *)block-2*sizeof(size_t));
		#endif
	}
}

/************************************************************************/
/*	Purpose..: 	Destroy a new allocated array of objects				*/
/*	Input....:	pointer to first object	(can be NULL)					*/
/*	Input....:	pointer to destructor function (not NULL)				*/
/*	Return...:	pointer to complete array block							*/
/************************************************************************/
extern void *__destroy_new_array2(void *block,ConstructorDestructor dtor)
{
	size_t	i,objects,objectsize;
	char	*p;

	if(block==NULL) return NULL;

	if(dtor)
	{	//	destroy array members
		objectsize=*(size_t *)((char *)block-2*sizeof(size_t));
		objects=*(size_t *)((char *)block-sizeof(size_t));
		p=(char *)block+objectsize*objects;
		for(i=0; i<objects; i++)
		{
			p-=objectsize;
			DTORCALL_COMPLETE(dtor,p);
		}
	}

	//	return pointer to complete array block
	return (char *)block-2*sizeof(size_t);
}

// hh 971207 Added namespace support
// hh 971215 commented out <Types.h> per John McEnerney's instructions
// hh 980102 added exception specific to set_terminate and set_unexpected
