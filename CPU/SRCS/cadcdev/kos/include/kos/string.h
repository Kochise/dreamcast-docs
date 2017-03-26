/* KallistiOS ##version##

   kos/string.h
   Copyright (C)2004 Dan Potter

*/

#ifndef __KOS_STRING_H
#define __KOS_STRING_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <string.h>

void * memcpy4(void * dest,const void *src,size_t count);
void * memset4(void * s,unsigned long c,size_t count);
void * memcpy2(void * dest,const void *src,size_t count);
void * memset2(void * s,unsigned short c,size_t count);

__END_DECLS

#endif	/* __KOS_STRING_H */


