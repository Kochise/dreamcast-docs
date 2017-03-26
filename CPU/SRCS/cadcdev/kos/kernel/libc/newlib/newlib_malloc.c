/* KallistiOS ##version##

   newlib_malloc.c
   Copyright (C)2004 Dan Potter

*/

#include <stdlib.h>
#include <reent.h>

// We have to provide these for Newlib's reent pieces.

void _free_r(struct _reent * re, void *ptr) { free(ptr); }
void * _malloc_r(struct _reent * re, size_t amt) { return malloc(amt); }
void * _calloc_r(struct _reent * re, size_t nmemb, size_t size) { return calloc(nmemb, size); }
void * _realloc_r(struct _reent * re, void * ptr, size_t size) { return realloc(ptr, size); }
