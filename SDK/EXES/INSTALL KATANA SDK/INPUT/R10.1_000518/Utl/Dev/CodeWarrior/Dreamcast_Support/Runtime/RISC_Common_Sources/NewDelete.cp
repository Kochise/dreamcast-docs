
/*
 *	NewDelete.cp	-	C++ 'new' and 'delete' operators
 *
 *	Copyright © 1999 Metrowerks, Inc.  All Rights Reserved.
 *
 */

#include <new>
#include <stdlib.h>


#pragma overload	extern void *operator new(size_t) throw(bad_alloc);
#pragma overload	extern void *operator new(size_t,const nothrow_t&) throw();
#pragma overload	extern void operator delete(void *) throw();

#if __MWERKS__>=0x2020
#pragma overload	extern void *operator new[](size_t) throw(bad_alloc);
#pragma overload	extern void *operator new[](size_t,const nothrow_t&) throw();
#pragma overload	extern void operator delete[](void *) throw();
#endif


#ifdef _MSL_USING_NAMESPACE
namespace std {
#endif


	/*	public data	*/

nothrow_t nothrow;						/*	pass this to operator new to avoid exception on failure	*/
char __throws_bad_alloc = 1;			/*	0 -> operator new() may return NULL	*/
new_handler __new_handler = 0;			/*	current operator new() failure handler	*/


/*
 *	set_new_handler	-	setup pointer to new_handler function
 *
 */

new_handler set_new_handler(new_handler new_new_handler) throw()
{
	new_handler old_new_handler = __new_handler;
	char *p = (char *) new_new_handler;
	
	__new_handler = new_new_handler;
	return old_new_handler;
}


#ifdef _MSL_USING_NAMESPACE
}
#endif


/*
 *	operator new	-	standard C++ 'new' operator (throws exception on failure)
 *
 */

void *operator new(size_t size) throw(bad_alloc)
{
	void *ptr;
	
		/*	if the caller wants to allocate an object of size 0, allocate 1		*/
		/*	byte so that we return a valid pointer and don't confuse malloc()	*/
	
	if (size == 0)
		size = 1;
		
		/*	try to allocate memory until we fail and/or throw an exception	*/
	
	while ((ptr = malloc(size)) == NULL) {
		if (__new_handler)
			__new_handler();
		else if (__throws_bad_alloc)
			throw bad_alloc();
		else
			return NULL;
	}
	
		/*	return the pointer to the allocated memory	*/
	
	return ptr;
}


/*
 *	operator new	-	standard C++ 'new' operator (no exception on failure)
 *
 */

void *operator new(size_t size, const nothrow_t&) throw()
{
	void *ptr;
	
		/*	if the caller wants to allocate an object of size 0, allocate 1		*/
		/*	byte so that we return a valid pointer and don't confuse malloc()	*/
	
	if (size == 0)
		size = 1;
		
		/*	try to allocate memory until we fail	*/
	
	while ((ptr = malloc(size)) == NULL) {
		if (__new_handler) {
			try {
				__new_handler();
			}
			catch (bad_alloc) {
				return NULL;
			}
		}
		else
			return NULL;
	}
	
		/*	return the pointer to the allocated memory	*/
	
	return ptr;
}


/*
 *	operator delete	-	standard C++ 'delete' operator
 *
 *	The test for (ptr != NULL) is probably redundant.
 *
 */

void operator delete(void *ptr) throw()
{
	if (ptr != NULL)
		free(ptr);
}


#if __MWERKS__>=0x0202

/*
 *	operator new[]		-	standard C++ 'new[]' operator
 *
 */

void *operator new[](size_t size) throw(bad_alloc)
{
	return operator new(size);
}

/*
 *	operator new[]		-	standard C++ 'new[]' operator (no exception on failure)
 *
 */

void *operator new[](size_t size, const nothrow_t& nt) throw()
{
	return operator new(size, nt);
}

/*
 *	operator delete[]	-	standard C++ 'delete[]' operator
 *
 */

void operator delete[](void *ptr) throw()
{
	operator delete(ptr);
}

#endif
