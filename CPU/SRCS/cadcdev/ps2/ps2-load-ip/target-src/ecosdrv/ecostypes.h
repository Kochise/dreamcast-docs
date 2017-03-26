/* ps2-load-ip

   ecostypes.h

   Copyright (c)2001 YAEGASHI Takeshi
   License: GPL

   $Id: ecostypes.h,v 1.1 2002/10/30 05:34:12 bardtx Exp $
*/

#ifndef __TYPES_H
#define __TYPES_H

#define KUSEG                   0x00000000
#define KSEG0                   0x80000000
#define KSEG1                   0xa0000000
#define KSEG2                   0xc0000000
#define KSEG3                   0xe0000000
#define KSEGX(a)                (((unsigned long)(a)) & 0xe0000000)
#define PHYSADDR(a)		(((unsigned long)(a)) & 0x1fffffff)
#define KSEG0ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG0))
#define KSEG1ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG1))
#define KSEG2ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG2))
#define KSEG3ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG3))

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef signed int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));

typedef signed char __s8;
typedef unsigned char __u8;
typedef signed short __s16;
typedef unsigned short __u16;
typedef signed long __s32;
typedef unsigned long __u32;
typedef signed long long __s64;
typedef unsigned long long __u64;
typedef signed int __s128 __attribute__((mode(TI)));

#endif
