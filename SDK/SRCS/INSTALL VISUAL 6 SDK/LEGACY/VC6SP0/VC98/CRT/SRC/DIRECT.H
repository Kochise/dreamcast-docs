/***
*direct.h - function declarations for directory handling/creation
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This include file contains the function declarations for the library
*       functions related to directory handling and creation.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_DIRECT
#define _INC_DIRECT

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

#ifdef _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,8)
#endif  /* _MSC_VER */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef _INTERNAL_IFSTRIP_
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

#ifndef _MAC
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif  /* _WCHAR_T_DEFINED */
#endif  /* _MAC */

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif  /* _SIZE_T_DEFINED */

#ifndef _MAC
/* _getdiskfree structure for _getdiskfree() */
#ifndef _DISKFREE_T_DEFINED

struct _diskfree_t {
        unsigned total_clusters;
        unsigned avail_clusters;
        unsigned sectors_per_cluster;
        unsigned bytes_per_sector;
        };

#define _DISKFREE_T_DEFINED
#endif  /* _DISKFREE_T_DEFINED */
#endif  /* _MAC */

/* function prototypes */

_CRTIMP int __cdecl _chdir(const char *);
_CRTIMP char * __cdecl _getcwd(char *, int);
_CRTIMP int __cdecl _mkdir(const char *);
_CRTIMP int __cdecl _rmdir(const char *);

#ifndef _MAC
_CRTIMP int __cdecl _chdrive(int);
_CRTIMP char * __cdecl _getdcwd(int, char *, int);
_CRTIMP int __cdecl _getdrive(void);
_CRTIMP unsigned long __cdecl _getdrives(void);
_CRTIMP unsigned __cdecl _getdiskfree(unsigned, struct _diskfree_t *);
#endif  /* _MAC */


#ifndef _MAC
#ifndef _WDIRECT_DEFINED

/* wide function prototypes, also declared in wchar.h  */

_CRTIMP int __cdecl _wchdir(const wchar_t *);
_CRTIMP wchar_t * __cdecl _wgetcwd(wchar_t *, int);
_CRTIMP wchar_t * __cdecl _wgetdcwd(int, wchar_t *, int);
_CRTIMP int __cdecl _wmkdir(const wchar_t *);
_CRTIMP int __cdecl _wrmdir(const wchar_t *);

#define _WDIRECT_DEFINED
#endif  /* _WDIRECT_DEFINED */
#endif  /* _MAC */

#ifdef _MT
char * __cdecl _getdcwd_lk(int, char *, int);                   /* _MTHREAD_ONLY */
#ifndef _MAC
wchar_t * __cdecl _wgetdcwd_lk(int, wchar_t *, int);            /* _MTHREAD_ONLY */
#endif  /* _MAC */
#else  /* _MT */
#define _getdcwd_lk(drv, buf, len)  _getdcwd(drv, buf, len)     /* _MTHREAD_ONLY */
#ifndef _MAC
#define _wgetdcwd_lk(drv, buf, len)  _wgetdcwd(drv, buf, len)   /* _MTHREAD_ONLY */
#endif  /* _MAC */
#endif  /* _MT */

#if !__STDC__

/* Non-ANSI names for compatibility */

_CRTIMP int __cdecl chdir(const char *);
_CRTIMP char * __cdecl getcwd(char *, int);
_CRTIMP int __cdecl mkdir(const char *);
_CRTIMP int __cdecl rmdir(const char *);

#ifndef _MAC
#define diskfree_t  _diskfree_t
#endif  /* _MAC */

#endif  /* !__STDC__ */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#ifdef _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_DIRECT */
