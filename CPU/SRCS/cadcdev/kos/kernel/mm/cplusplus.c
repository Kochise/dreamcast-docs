/* KallistiOS ##version##

   cplusplus.c
   (c)2002 Dan Potter

   This is just a wrapper around malloc() and free() for C++ programs.
 */

#include <malloc.h>

CVSID("$Id: cplusplus.c,v 1.2 2002/01/06 01:14:48 bardtx Exp $");

void *__builtin_new(int size) {
	return malloc(size);
}

void *__builtin_vec_new(int size) {
	return __builtin_new(size);
}

void __builtin_delete(void *ptr) {
	free(ptr);
}

void __builtin_vec_delete(void *ptr) {
	__builtin_delete(ptr);
}

