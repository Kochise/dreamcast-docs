/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	New.cp													*/
/*	Purpose...:	standard C++ library									*/
/*  Copyright.: Copyright © 1993-1998 Metrowerks, Inc.					*/
/************************************************************************/

#include <new>
#include <stdlib.h>
#include <MacMemory.h>

// hh 980121 commented out.  #define new to anything at your own risk!  Not recommended!
//#ifdef DebugNew_H
//	#undef new
//#endif

#ifdef __MC68K__
#pragma a6frames on
#endif

// hh 971207 Moved these up to get them out of std::
//
//	allow user definined replacements of operator new/delete
//

#pragma overload	extern void *operator new(size_t) throw(bad_alloc);
#pragma overload	extern void *operator new(size_t,const nothrow_t&) throw();
#pragma overload	extern void operator delete(void *) throw();

#if __MWERKS__>=0x2020
#pragma overload	extern void *operator new[](size_t) throw(bad_alloc);
#pragma overload	extern void *operator new[](size_t,const nothrow_t&) throw();
#pragma overload	extern void operator delete[](void *) throw();
#endif

#ifdef _MSL_USING_NAMESPACE      // hh 971207 Added namespace support
	namespace std {
#endif

#ifndef NEWMODE
#define NEWMODE NEWMODE_FAST		//	mode used to compile this file
#endif

#define NEWMODE_NONE	0			//	do not define operator new/delete
#define NEWMODE_SIMPLE	1			//	call NewPtr/DisposPtr
#define NEWMODE_MALLOC	2			//	use malloc/free
#define NEWMODE_NORMAL	3			//	regular new/delete
#define NEWMODE_FAST	4			//	regular new/delete fast version

#ifndef NEWMODE_NORMAL_FASTFREE
#define NEWMODE_NORMAL_FASTFREE	0	//	NEWMODE_NORMAL faster free (real bad fragmentation)
#endif

#if		NEWMODE==NEWMODE_SIMPLE
	#define MALLOCFUNC(x)	NewPtr(x)
	#define MFREEFUNC(x)	DisposePtr(x)
	#define PTRTYPE			Ptr
#elif	NEWMODE==NEWMODE_MALLOC
	#define MALLOCFUNC(x)	malloc(x)
	#define MFREEFUNC(x)	free(x)
	#define PTRTYPE			void *
#elif	NEWMODE==NEWMODE_NORMAL || NEWMODE==NEWMODE_FAST
	#define MALLOCFUNC(x)	my_alloc(x)
	#define MFREEFUNC(x)	my_free(x)
	#define PTRTYPE			void *
#endif

extern new_handler	__new_handler;
nothrow_t nothrow;                // hh 980124 added nothrow

// These macros allow DebugNew.cp to redefine operators
// new and delete in debug mode while not adding any overhead
// for the non-debug case.
// 980819 Hsoi - Added macros for array new and array delete

#ifndef OPERATOR_NEW
	#define OPERATOR_NEW			operator new
#endif

#ifndef OPERATOR_ARRAY_DELETE
	#define OPERATOR_ARRAY_DELETE	operator delete[]
#endif

#if __MWERKS__>=0x2020
	#ifndef OPERATOR_ARRAY_NEW
		#define OPERATOR_ARRAY_NEW		operator new[]
	#endif

	#ifndef OPERATOR_DELETE
		#define OPERATOR_DELETE			operator delete
	#endif
#endif

#if NEWMODE==NEWMODE_NORMAL

typedef struct FreeMemList {
	struct FreeMemList	*next;
	long				size;
}	FreeMemList;

static FreeMemList	memlist;				//	dummy header block (always empty)
static size_t _newpoolsize	= 0x00010000L;	//	number of bytes allocated for a new pool
static size_t _newnonptrmax	= 0x00001000L;	//	any object bigger than this will call NewPtr(...) directly 

/************************************************************************/
/*	Purpose..: 	Set size of future allocation pools						*/
/*	Input....:	size of future allocation pools							*/
/*	Return...:	---														*/
/************************************************************************/
void _set_newpoolsize(size_t size)
{
	_newpoolsize=size;
}

/************************************************************************/
/*	Purpose..: 	Set NewPtr(...) pointer threshold						*/
/*	Input....:	size of new threshold									*/
/*	Return...:	---														*/
/************************************************************************/
void _set_newnonptrmax(size_t size)
{
	_newnonptrmax=size;
}

/************************************************************************/
/*	Purpose..: 	Preallocate an allocation pool							*/
/*	Input....:	size of pool to allocate								*/
/*	Return...:	1: no error; 0:	fail									*/
/************************************************************************/
char _prealloc_newpool(size_t size)
{
	FreeMemList	*list;

	if((list=(FreeMemList *)NewPtr(size))==NULL) return 0;
	list->next=memlist.next; list->size=size; memlist.next=list;
	return 1;
}

/************************************************************************/
/*	Purpose..: 	Allocate memory											*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	pointer to memory or 0L									*/
/************************************************************************/
inline void *my_alloc(size_t size)
{
	Ptr ptr;

	if(size>0x7FFFFFF0) return 0;
	size = 4L + ((size + 3L) & 0xFFFFFFFC);	//	alloc *4 quantity plus 4 extra bytes for size

	if(size>=_newnonptrmax)
	{	//	try to get pointer from OS
		if ((ptr=(char *)NewPtr(size))== NULL)
			return NULL;

		*(long *)ptr=-1L; 
		return ptr+4;
	}

	for(;;)
	{
		FreeMemList	*list,*prev;

		for(prev=&memlist,list=prev->next; list; prev=list,list=list->next) if(size<=list->size)
		{
alloc:		if(list->size>=size+sizeof(FreeMemList))
			{	//	split this free block
				list->size-=size; ptr=(Ptr)list+list->size;
				*(long *)ptr=size; return(ptr+4);
			}
			//	remove this block from list
			prev->next=list->next; *(long *)list=list->size; return((Ptr)list+4);
		}
	
		//	not enough free memory in memlist (try to allocate a new Ptr from OS
		if((list=(FreeMemList *)NewPtr(_newpoolsize))==NULL)
		{	//	try to allocate a system block
			if((ptr=NewPtr(size))!=NULL) { *(long *)ptr=-1L; return(ptr+4); }
			return(NULL);
		}
		else
		{
			list->next=memlist.next; list->size=_newpoolsize;
			memlist.next=list; prev=&memlist; goto alloc;
		}
	}
}

/************************************************************************/
/*	Purpose..: 	Dispose memory											*/
/*	Input....:	pointer to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
inline void my_free(void *ptr)
{
	if(ptr)
	{
		long	size;

		ptr=(Ptr)ptr-4; size=*(long *)ptr;
		if(size!=-1L)
		{
			FreeMemList	*list;
#if !NEWMODE_NORMAL_FASTFREE
			FreeMemList	*prev;
			char		merge=0;

			for(prev=&memlist,list=prev->next; list; prev=list,list=list->next)
			{
				if((Ptr)ptr+size==(Ptr)list)
				{	//	merge block in front of this list item
					prev->next=list->next; size+=list->size; list=prev;
					if(merge) break; else { merge=1; continue; }
				}
				if((Ptr)ptr==(Ptr)list+list->size)
				{	//	merge block at the end of this list item
					prev->next=list->next; ptr=list; size+=list->size; list=prev;
					if(merge) break; else { merge=1; continue; }
				}
			}
#endif
			list=(FreeMemList *)ptr; list->next=memlist.next; list->size=size; memlist.next=list;
		}
		else DisposePtr((Ptr)ptr);
	}
}

#elif NEWMODE==NEWMODE_FAST

typedef struct MemPool {
	struct MemPool		*next;				//	pointer to next pool
	size_t				size;				//	number of bytes in pool (including header)
	char				data[];				//	variable size user data section
}	MemPool;

static MemPool	*mempools;						//	list of memory pools
static char		*lastfree;						//	pointer to last free block
static char		*lastend;						//	pointer to last end
static size_t	_newpoolsize	= 0x00010000L;	//	number of bytes allocated for a new pool
static size_t	_newnonptrmax	= 0x00001000L;	//	any object bigger than this will call NewPtr(...) directly 

/************************************************************************/
/*	Purpose..: 	Set size of future allocation pools						*/
/*	Input....:	size of future allocation pools							*/
/*	Return...:	---														*/
/************************************************************************/
void _set_newpoolsize(size_t size)
{
	_newpoolsize=size;
}

/************************************************************************/
/*	Purpose..: 	Set NewPtr(...) pointer threshold						*/
/*	Input....:	size of new threshold									*/
/*	Return...:	---														*/
/************************************************************************/
void _set_newnonptrmax(size_t size)
{
	_newnonptrmax=size;
}

/************************************************************************/
/*	Purpose..: 	Preallocate a memory pool								*/
/*	Input....:	size of pool to allocate								*/
/*	Return...:	1: no error; 0:	fail									*/
/************************************************************************/
char _prealloc_newpool(size_t size)
{
	MemPool	*pool;

	if((pool=(MemPool *)NewPtr(size))==NULL) return 0;

	pool->next=mempools; mempools=pool;
	pool->size=size; *(long *)pool->data=pool->size-sizeof(MemPool);

	return 1;
}

/************************************************************************/
/*	Purpose..: 	Allocate memory											*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	pointer to memory or 0L									*/
/************************************************************************/
inline void *my_alloc(size_t size)
{
	MemPool	*pool;
	char	*ptr,*end;
	long	bsize,nsize;

	if(size>0x7FFFFFF0) return 0;
	size = 4L + ((size + 3L) & 0xFFFFFFFC);	//	alloc *4 quantity plus 4 extra bytes for size

	for(;;)
	{
		if(size>=_newnonptrmax)
		{
			if ((ptr=(char *)NewPtr(size))== NULL)
				return NULL;

			*(long *)ptr=0L; 
			return ptr+4;
		}

		if((ptr=lastfree)!=0L && (bsize=*(long *)ptr)>=(long)size)
		{	//	last free block has enough memory left
			end=lastend; goto alloc2;
		}

		for(pool=mempools; pool; pool=pool->next)
		{
alloc:		for(ptr=pool->data,end=(Ptr)pool+pool->size; ptr<end;) if((bsize=*(long *)ptr)>0)
			{
alloc2:			lastfree=0L;
				while(ptr+bsize<end && (nsize=*(long *)(ptr+bsize))>0)
				{	//	merge block with the next block
					*(long *)ptr=bsize=bsize+nsize;
				}
				if(bsize>=size)
				{	//	pool block is big enough
					if(bsize>=size+8)
					{	//	split this block
						lastfree=ptr; lastend=end;
						bsize-=size; *(long *)ptr=bsize; ptr+=bsize;
						*(long *)ptr=-size; return ptr+4;
					}
					else
					{	//	allocate whole block
						*(long *)ptr=-bsize; return ptr+4;
					}
				}
				else ptr+=bsize;
			}
			else
			{
				if(bsize==0) break;		//	corrupt heap?
				ptr-=bsize;
			}
next:;	}

		//	not enough free memory in mempools (try to allocate a new Ptr from OS)
		if((pool=(MemPool *)NewPtr(_newpoolsize))!=NULL)
		{
			pool->next=mempools; mempools=pool;
			pool->size=_newpoolsize; *(long *)pool->data=pool->size-sizeof(MemPool);
			goto alloc;
		}
		else
		{	//	try to allocate a system block
			if((ptr=(char *)NewPtr(size))!=NULL)
			{
				*(long *)ptr=0L; return ptr+4;
			}
		}

		return NULL;
	}
}

/************************************************************************/
/*	Purpose..: 	Dispose memory											*/
/*	Input....:	pointer to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
inline void my_free(void *ptr)
{
	if(ptr)
	{
		ptr=(char *)ptr-4;
		if((*(long *)ptr=-*(long *)ptr)==0L) DisposePtr((Ptr)ptr);
	}
}

#endif

#ifdef _MSL_USING_NAMESPACE       // hh 971207 Added namespace support
	}
#endif

#if NEWMODE!=NEWMODENONE

/************************************************************************/
/*	Purpose..: 	Allocate memory											*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	pointer to memory or 0L									*/
/************************************************************************/
void *OPERATOR_NEW(size_t size) throw(bad_alloc)
{
	void *ptr;

#if defined(__MODENALIB__) && NEWMODE==NEWMODE_MALLOC
	if (size==0) { size = sizeof(int); }     // hh 971208 Changed sizeof(1) to sizeof(int)
#endif

	for(;;)
	{
		if((ptr=MALLOCFUNC(size))!=NULL) break;
		if(!__new_handler)
		{
			__throw_bad_alloc();
			 break;
		}
		__new_handler();
	}
	return ptr;
}

/************************************************************************/
/*	Purpose..: 	Allocate memory											*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	pointer to memory or 0L									*/
/************************************************************************/
void *OPERATOR_NEW(size_t size,const nothrow_t&) throw()
{
	void *ptr;

#if defined(__MODENALIB__) && NEWMODE==NEWMODE_MALLOC
	if (size==0) { size = sizeof(1); }
#endif

	for(;;)
	{
		if((ptr=MALLOCFUNC(size))!=NULL) break;
		if(!__new_handler)  break;
		try { __new_handler(); }
		catch(bad_alloc&)
		{
			break;
		}
	}
	return ptr;
}

/************************************************************************/
/*	Purpose..: 	Dispose memory											*/
/*	Input....:	pointer to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
void OPERATOR_DELETE(void *ptr) throw()
{
	if(ptr) MFREEFUNC((PTRTYPE)ptr);
}

/************************************************************************/
/*	Purpose..: 	Array allocation/deallocation functions					*/
/*	Input....:	---														*/
/*	Return...:	---														*/
/************************************************************************/
#if __MWERKS__>=0x2020
extern void *OPERATOR_ARRAY_NEW(size_t size) throw(bad_alloc)
{
	return OPERATOR_NEW(size);
}
extern void *OPERATOR_ARRAY_NEW(size_t size,const nothrow_t& nt) throw()
{
	return OPERATOR_NEW(size,nt);
}
extern void OPERATOR_ARRAY_DELETE(void *ptr) throw()
{
	OPERATOR_DELETE(ptr);
}
#endif

#endif

// hh 971207 Added namespace support
// hh 971207 Moved operator new and company up to get them out of std::
// hh 971208 Changed sizeof(1) to sizeof(int)
// hh 980121 commented out Debug_New dance.  #define new to anything at your own risk!  Not recommended!
// hh 980124 added nothrow
// Hsoi 980819 Modified array new and delete to use redefinition macros for DebugNew support