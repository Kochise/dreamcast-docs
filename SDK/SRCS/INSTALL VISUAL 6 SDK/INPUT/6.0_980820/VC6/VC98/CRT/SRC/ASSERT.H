/***
*assert.h - define the assert macro
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines the assert(exp) macro.
*       [ANSI/System V]
*
*       [Public]
*
****/

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

#ifndef _INTERNAL_IFSTRIP_
#ifndef _ASSERT_OK
#error assert.h not for CRT internal use, use dbgint.h
#endif  /* _ASSERT_OK */
#include <cruntime.h>
#endif  /* _INTERNAL_IFSTRIP_ */


/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef CRTDLL
#define _CRTIMP __declspec(dllexport)
#else  /* CRTDLL */
#ifdef _DLL
#define _CRTIMP __declspec(dllimport)
#else  /* _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP */


/* Define __cdecl for non-Microsoft compilers */

#if (!defined (_MSC_VER) && !defined (__cdecl))
#define __cdecl
#endif  /* (!defined (_MSC_VER) && !defined (__cdecl)) */

/* Define _CRTAPI1 (for compatibility with the NT SDK) */

#ifndef _CRTAPI1
#if _MSC_VER >= 800 && _M_IX86 >= 300
#define _CRTAPI1 __cdecl
#else  /* _MSC_VER >= 800 && _M_IX86 >= 300 */
#define _CRTAPI1
#endif  /* _MSC_VER >= 800 && _M_IX86 >= 300 */
#endif  /* _CRTAPI1 */

#undef  assert

#ifdef NDEBUG

#define assert(exp)     ((void)0)

#else  /* NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

_CRTIMP void __cdecl _assert(void *, void *, unsigned);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#define assert(exp) (void)( (exp) || (_assert(#exp, __FILE__, __LINE__), 0) )

#endif  /* NDEBUG */
