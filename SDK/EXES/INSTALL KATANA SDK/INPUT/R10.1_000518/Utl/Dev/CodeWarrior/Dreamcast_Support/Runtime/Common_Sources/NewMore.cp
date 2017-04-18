/************************************************************************/
/*	Project...:	Standard C++ Library									*/
/*	Name......:	NewMore.cp												*/
/*	Purpose...:	standard C++ library									*/
/*  Copyright.: Copyright © 1993-1997 Metrowerks, Inc.					*/
/************************************************************************/

#include <new>
#include <MacMemory.h>
#include <CPlusLib.h>

#ifdef _MSL_USING_NAMESPACE        // hh 971207 Added namespace support
	namespace std {
#endif

#ifdef __MC68K__
#pragma a6frames on
#endif

char			__throws_bad_alloc = 1;		//	default: throw bad_alloc exception
new_handler		__new_handler;

/************************************************************************/
/*	Purpose..: 	throw a bad_alloc excpetion								*/
/*	Input....:	---														*/
/*	Return...:	---														*/
/************************************************************************/
extern void __throw_bad_alloc()
{
	if(__throws_bad_alloc) throw bad_alloc();
}

/************************************************************************/
/*	Purpose..: 	Set new_handler function								*/
/*	Input....:	new_handler function pointer (or NULL)					*/
/*	Return...:	old new_handler function pointer						*/
/************************************************************************/
extern new_handler set_new_handler(new_handler new_new_handler) throw()
{
	new_handler old_new_handler = __new_handler;
	__new_handler = new_new_handler;
	return old_new_handler;
}

#ifdef _MSL_USING_NAMESPACE
	}
#endif

/************************************************************************/
/*	Purpose..: 	Allocate memory	(handle)								*/
/*	Input....:	size of memory to allocate								*/
/*	Return...:	handle to memory or 0L									*/
/************************************************************************/
void *__new_hdl(size_t size)
{
	void *ptr;

	for(;;)
	{
		if((ptr=NewHandle(size))!=NULL) break;
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
/*	Purpose..: 	Dispose memory (handle)									*/
/*	Input....:	handle to memory or 0L (no action if 0L)				*/
/*	Return...:	---														*/
/************************************************************************/
void __del_hdl(void *hdl)
{
	if(hdl) DisposeHandle((Handle)hdl);
}

// hh 971207 Added namespace support
