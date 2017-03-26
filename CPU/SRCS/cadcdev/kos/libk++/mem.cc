/* KallistiOS ##version##

   libk++/mem.cc

   (c)2002 Gil Megidish
*/

#include <sys/cdefs.h>
#include <arch/arch.h>
#include <stdio.h>
#include <sys/types.h>

CVSID("$Id: mem.cc,v 1.2 2002/09/23 23:03:34 gilm Exp $");

/* This file contains definitions for the basic malloc/free operations
   in C++. You can use this tiny replacement for libstdc++ when you
   don't need the whole thing. */

extern "C" void free(void*);
extern "C" void *malloc(unsigned);

asm(
".text\n"
".global __ZdlPv\n"
".global __Znwj\n"
".global __ZdaPv\n"
".global __Znaj\n"
".extern _free\n"
".extern _malloc\n"
"__ZdlPv:\n"
"__ZdaPv:\n"
"	mov.l	freeaddr,r0\n"
"	jmp	@r0\n"
"	nop\n"
".align 2\n"
"freeaddr:	.long	_free\n"
"__Znwj:\n"
"__Znaj:\n"
"	mov.l	mallocaddr,r0\n"
"	jmp	@r0\n"
"	nop\n"
".align 2\n"
"mallocaddr:	.long	_malloc\n"
);

/* void operator delete(void *ptr) {
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
} */
                     
