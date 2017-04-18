/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		kmbase.h

  Abstract:
	KAMUI = Kamui is Abstruction Model that is Ultimate Interface for PowerVR.
	'kmbase.h' is kamui basic header.

  Environment:
	ANSI C Compiler.

  Notes:
	KAMUI BASIC Data type.

  Revision History:

--*/
#if !defined(__KMBASE_H__)
#define __KMBASE_H__

#if 0
#include <windows.h>
#else

#ifndef VOID
typedef void			VOID;
#endif

#ifndef DWORD
typedef unsigned long	DWORD;					/* dw	*/
#endif

#ifndef CHAR
typedef char 			CHAR;					/* ch	*/
#endif

#ifndef UCHAR
typedef unsigned char 	UCHAR;					/* uch	*/
#endif

#ifndef SHORT
typedef short			SHORT;					/* s	*/
#endif

#ifndef USHORT
typedef unsigned short  USHORT;					/* us	*/
#endif

#ifndef LONG
typedef long            LONG;					/* l	*/
#endif

#ifndef ULONG
typedef unsigned long	ULONG;					/* ul	*/
#endif

#ifndef INT
typedef int 		 	INT;					/* i	*/
#endif

#ifndef UINT
typedef unsigned int 	UINT;					/* u	*/
#endif

#ifndef BOOL
typedef int 		 	BOOL;					/* f	*/
#endif

#ifndef BYTE

typedef unsigned char	BYTE;					/* b	*/
#endif

#ifndef WORD
typedef unsigned short	WORD;					/* w	*/
#endif

#endif

#ifndef PVOID
typedef void *PVOID;
#endif

/*
 * TRUE / FALSE / NULL.
 */
#ifndef FALSE
#define FALSE   0
#endif
#ifndef TRUE
#define TRUE	1
#endif
#ifndef NULL
#define NULL    '\0'                    /* Null pointer */
#endif

/*
 * !!!!  KM_TRUE MUST BE *1*  !!!!
 */
#define KM_FALSE	(0)
#define KM_TRUE		(1)

/*
 * Calling sequence.
 */
#if defined(WIN32)
#define KMAPI		__stdcall
#else
#define KMAPI
#endif

#if defined(WIN32)
#ifndef CALLBACK
#define CALLBACK	__stdcall
#endif
#else
#define CALLBACK
#endif

/*
 * Inline keyword.
 */
#if defined(WIN32)
#define INLINE		__inline
#else
#define INLINE
#endif

/*
 * comment for argument.
 */

#define IN
#define OUT

#if 0
  #define CDECL   _cdecl
  #define PASCAL  _pascal
  #define VOID    void
#endif


#define CONST   const
#define VOLATILE volatile
#define	STATIC	static

typedef int 		 	KMINT32;				/* i	*/
typedef unsigned int 	KMUINT32;				/* u	*/
typedef int 		 	KMBOOL;					/* f	*/

typedef unsigned char	KMBYTE;					/* b	*/
typedef unsigned short	KMWORD;					/* w	*/
typedef unsigned long	KMDWORD;				/* dw	*/

#ifndef _H2INC

typedef struct qword_s {						/* qword */
   DWORD qword_lo;
   DWORD qword_hi;
} KMQWORD;										/* qw	*/

#endif 

typedef char 			KMCHAR8;				/* ch	*/
typedef unsigned char 	KMUCHAR8;				/* uch	*/
typedef short			KMSHORT16;				/* s	*/
typedef unsigned short  KMUSHORT16;				/* us	*/
typedef long            KMLONG32;				/* l	*/
typedef unsigned long	KMULONG32;				/* ul	*/

typedef VOID 			KMVOID;					/* 		*/
typedef KMVOID 			*PKMVOID;				/* p	*/
typedef PKMVOID			*PPKMVOID;				/* pp	*/
typedef PKMVOID			KMHANDLE;				/* h	*/
typedef KMHANDLE		*PKMHANDLE;				/* ph	*/

typedef INT				*PKMINT32;				/* pi	*/
typedef UINT			*PKMUINT32;				/* pu	*/

typedef KMCHAR8			*PKMCHAR8;				/* pch	*/
typedef KMSHORT16		*PKMSHORT16;			/* ps	*/
typedef KMLONG32		*PKMLONG32;				/* pl	*/
typedef KMUCHAR8		*PKMUCHAR8;				/* puch	*/
typedef KMUSHORT16		*PKMUSHORT16;			/* pus	*/
typedef KMULONG32		*PKMULONG32;			/* pul	*/

typedef float			KMFLOAT;				/* f	*/
typedef KMFLOAT			*PKMFLOAT;				/* pf	*/

typedef BYTE			*PKMBYTE;				/* pb	*/
typedef WORD			*PKMWORD;				/* pw	*/
typedef DWORD			*PKMDWORD;				/* pdw	*/

typedef BOOL			*PKMBOOL;				/* pb	*/

/*
 * KMBOOLEAN
 */
typedef BOOL			KMBOOLEAN;				/* b	*/
typedef KMBOOLEAN		*PKMBOOLEAN;			/* pb	*/

/*
 * Kamui Texture type definision...
 */
typedef KMUINT32 KMTEXTURETYPE;
typedef KMTEXTURETYPE	*PKMTEXTURETYPE;

#endif /*__KMBASE_H__ */

