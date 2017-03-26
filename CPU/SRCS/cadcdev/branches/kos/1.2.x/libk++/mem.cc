/* KallistiOS ##version##

   libk++/mem.cc

   (c)2002 Gil Megidish
*/

#include <sys/cdefs.h>
#include <sys/types.h>

CVSID("$Id: mem.cc,v 1.2 2002/09/23 23:03:34 gilm Exp $");

/* This file contains definitions for the basic malloc/free operations
   in C++. You can use this tiny replacement for libstdc++ when you
   don't need the whole thing. */

extern "C" void free(void*);
extern "C" void *malloc(unsigned);

void operator delete(void *ptr) {
	if (ptr)
		free(ptr);
}

void* operator new(size_t len) {
	return malloc(len);
}

void operator delete[](void *ptr) {
	::operator delete(ptr);
}

void* operator new[](size_t len) {
	return ::operator new(len);
}
                     
