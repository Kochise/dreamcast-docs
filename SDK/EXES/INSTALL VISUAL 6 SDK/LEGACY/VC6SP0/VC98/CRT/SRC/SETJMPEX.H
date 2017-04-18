/***
*setjmpex.h - definitions/declarations for extended setjmp/longjmp routines
*
*       Copyright (c) 1993-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file causes _setjmpex to be called which will enable safe
*       setjmp/longjmp that work correctly with try/except/finally.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_SETJMPEX
#define _INC_SETJMPEX

#if !defined (_WIN32) && !defined (_MAC)
#error ERROR: Only Mac or Win32 targets supported!
#endif  /* !defined (_WIN32) && !defined (_MAC) */

#ifndef _CRTBLD
/* This version of the header files is NOT for user programs.
 * It is intended for use when building the C runtimes ONLY.
 * The version intended for public use will not have this message.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

/*
 * Definitions specific to particular setjmp implementations.
 */

#if defined (_M_IX86)

/*
 * MS compiler for x86
 */

#define setjmp  _setjmp
#define longjmp _longjmpex

#elif defined (_M_MRX000)

#if _MSC_VER >= 1100
#define _setjmpex _setjmpexVfp
#endif  /* _MSC_VER >= 1100 */

#define setjmp _setjmpex

#else  /* defined (_M_MRX000) */

#define setjmp _setjmpex

#endif  /* defined (_M_MRX000) */

#include <setjmp.h>

#endif  /* _INC_SETJMPEX */
