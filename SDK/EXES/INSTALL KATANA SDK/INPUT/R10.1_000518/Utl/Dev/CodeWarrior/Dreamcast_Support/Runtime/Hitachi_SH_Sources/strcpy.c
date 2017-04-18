
/*
 *	strcpy.c	-	__strcpy() and __memcpy() routines for Hitachi SH series
 *
 *	Copyright © 1999 Metrowerks, Inc.  All Rights Reserved.
 *
 *
 *	THEORY OF OPERATION
 *
 *	The compiler defines __strcpy() and __memcpy() as intrinsic functions so
 *	that it can detect the case where the number of bytes being copied is
 *	known at compile-time, and generate inline code.
 *
 *	If the number of bytes being copied is not known at compile-time, calls to
 *	these intrinsics will link to the routines below.
 *
 */

#include <stddef.h>


/*
 *	__strcpy	-	linkable version of __strcpy() intrinsic function
 *
 *	If the compiler sees a call to the __strcpy() intrinsic whose 2nd argument
 *	is not a string literal, it will generate a call to this routine. We must
 *	copy the string byte-by-byte as we do not know if the source and destination
 *	strings are aligned to any particular boundary.
 *
 */

asm char *__strcpy(register char *dst, register const char *src)
{
L1:	MOV.B	@src+,R2;
	MOV.B	R2,@dst;
	ADD		1,dst;
	TST		R2,R2;
	BF		L1;
	RTS;
	NOP;
}


/*
 *	__memcpy	-	linkable version of __memcpy() intrinsic function
 *
 *	If the compiler sees a call to the __memcpy() intrinsic whose 3rd argument
 *	is not a constant-expression, it will generate a call to this routine. We must
 *	move the data byte-by-byte as we do not know if the source and destination
 *	are aligned to any particular boundary.
 *
 */

asm void *__memcpy(register void *dst, register const void* src, register size_t len)
{
	TST		len,len;
	BT		L2;
L1:	MOV.B	@src+,R2;
	MOV.B	R2,@dst;
	ADD		1,dst;
	ADD		-1,len;
	TST		len,len;
	BF		L1;	
L2:
	RTS;
	NOP;
}
