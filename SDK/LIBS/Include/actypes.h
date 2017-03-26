//-----------------------------------------------------------------------------
//
//	FILE:		actypes.h
//
//	DESC:		am/ac global types & defines
//
//	HISTORY:	1998.11.xx	Product Development group
//
//-----------------------------------------------------------------------------
//	COPYRIGHT (C) SEGA OF AMERICA, INC. 1998-2000
//	All rights reserved.
//-----------------------------------------------------------------------------

#if !defined(_ACTYPES_H_)
#define _ACTYPES_H_

//-----------------------------------------------------------------------------
//	Types
//-----------------------------------------------------------------------------

typedef unsigned long				KTU32;
typedef unsigned short				KTU16;
typedef unsigned char				KTU8;

typedef signed long					KTS32;
typedef signed short				KTS16;
typedef signed char					KTS8;

typedef unsigned int				KTUINT;
typedef int							KTINT;

typedef enum { KTFALSE, KTTRUE }	KTBOOL;

typedef float						KTFLOAT;
typedef float						KTF32;
typedef double						KTDOUBLE;
typedef double						KTF64;

typedef char *						KTSTRING;
typedef char						KTCHAR;

//-----------------------------------------------------------------------------
//	Defines
//-----------------------------------------------------------------------------

#define KTASM		__asm__				/* [1] has and [2] uses outputs */
#define KTASMV		__asm__ volatile	/* missing [1] or [2] or both */

#if defined(KTDEBUG)
#define KTSTATIC
#define KTINLINE	static __inline__
#else
#define KTSTATIC	static
#define KTINLINE	static __inline__
#endif

#define KTPACK		__attribute__((__packed__)) __attribute__((__aligned__(1)))

#define KTNULL		(0)

#define ALIGN32					32		/* Alignment on 32-byte boundries */
#define ALIGN32_SIZE(size)		((size) + ALIGN32)
#define ALIGN32_ADDR(addr)		(((KTU32)(addr) + (ALIGN32-1)) & ~(ALIGN32-1))

#define IS_ALIGNED_32(data)		(!((KTU32)(data) & (ALIGN32-1)))
#define IS_NZALIGNED_32(data)	((data) && IS_ALIGNED_32(data))

#define SECTOR_SIZE				2048	/* Alignment on 2048-byte boundries */
#define SECTOR_ALIGN(size)		\
						(((KTU32)(size) + (SECTOR_SIZE-1)) & ~(SECTOR_SIZE-1))

#define IS_ALIGNED_SECTOR(data)		(!((KTU32)(data) & (SECTOR_SIZE-1)))
#define IS_NZALIGNED_SECTOR(data)	((data) && IS_ALIGNED_SECTOR(data))

#define ALIGN(size,align)		\
						(((KTU32)(size) + ((align)-1)) & ~((align)-1))

//-----------------------------------------------------------------------------

#endif	// _ACTYPES_H_
