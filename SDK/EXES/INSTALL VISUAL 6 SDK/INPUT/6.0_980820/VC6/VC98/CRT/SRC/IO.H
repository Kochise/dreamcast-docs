/***
*io.h - declarations for low-level file handling and I/O functions
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains the function declarations for the low-level
*       file handling and I/O functions.
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_IO
#define _INC_IO

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

#ifndef _TIME_T_DEFINED
typedef long time_t;            /* time value */
#define _TIME_T_DEFINED         /* avoid multiple def's of time_t */
#endif  /* _TIME_T_DEFINED */

#ifndef _FSIZE_T_DEFINED
typedef unsigned long _fsize_t; /* Could be 64 bits for Win32 */
#define _FSIZE_T_DEFINED
#endif  /* _FSIZE_T_DEFINED */

#ifndef _MAC

#ifndef _FINDDATA_T_DEFINED

struct _finddata_t {
    unsigned    attrib;
    time_t      time_create;    /* -1 for FAT file systems */
    time_t      time_access;    /* -1 for FAT file systems */
    time_t      time_write;
    _fsize_t    size;
    char        name[260];
};

#if _INTEGRAL_MAX_BITS >= 64   
struct _finddatai64_t {
    unsigned    attrib;
    time_t      time_create;    /* -1 for FAT file systems */
    time_t      time_access;    /* -1 for FAT file systems */
    time_t      time_write;
    __int64     size;
    char        name[260];
};
#endif  /* _INTEGRAL_MAX_BITS >= 64    */

#define _FINDDATA_T_DEFINED
#endif  /* _FINDDATA_T_DEFINED */

#ifndef _WFINDDATA_T_DEFINED

struct _wfinddata_t {
    unsigned    attrib;
    time_t      time_create;    /* -1 for FAT file systems */
    time_t      time_access;    /* -1 for FAT file systems */
    time_t      time_write;
    _fsize_t    size;
    wchar_t     name[260];
};

#if _INTEGRAL_MAX_BITS >= 64   
struct _wfinddatai64_t {
    unsigned    attrib;
    time_t      time_create;    /* -1 for FAT file systems */
    time_t      time_access;    /* -1 for FAT file systems */
    time_t      time_write;
    __int64     size;
    wchar_t     name[260];
};
#endif  /* _INTEGRAL_MAX_BITS >= 64    */

#define _WFINDDATA_T_DEFINED
#endif  /* _WFINDDATA_T_DEFINED */

/* File attribute constants for _findfirst() */

#define _A_NORMAL       0x00    /* Normal file - No read/write restrictions */
#define _A_RDONLY       0x01    /* Read only file */
#define _A_HIDDEN       0x02    /* Hidden file */
#define _A_SYSTEM       0x04    /* System file */
#define _A_SUBDIR       0x10    /* Subdirectory */
#define _A_ARCH         0x20    /* Archive file */

#endif  /* _MAC */

/* function prototypes */

_CRTIMP int __cdecl _access(const char *, int);
_CRTIMP int __cdecl _chmod(const char *, int);
_CRTIMP int __cdecl _chsize(int, long);
_CRTIMP int __cdecl _close(int);
_CRTIMP int __cdecl _commit(int);
_CRTIMP int __cdecl _creat(const char *, int);
_CRTIMP int __cdecl _dup(int);
_CRTIMP int __cdecl _dup2(int, int);
_CRTIMP int __cdecl _eof(int);
_CRTIMP long __cdecl _filelength(int);
#ifndef _MAC
_CRTIMP long __cdecl _findfirst(const char *, struct _finddata_t *);
_CRTIMP int __cdecl _findnext(long, struct _finddata_t *);
_CRTIMP int __cdecl _findclose(long);
#endif  /* _MAC */
_CRTIMP int __cdecl _isatty(int);
_CRTIMP int __cdecl _locking(int, int, long);
_CRTIMP long __cdecl _lseek(int, long, int);
_CRTIMP char * __cdecl _mktemp(char *);
_CRTIMP int __cdecl _open(const char *, int, ...);
#ifndef _MAC
_CRTIMP int __cdecl _pipe(int *, unsigned int, int);
#endif  /* _MAC */
_CRTIMP int __cdecl _read(int, void *, unsigned int);
_CRTIMP int __cdecl remove(const char *);
_CRTIMP int __cdecl rename(const char *, const char *);
_CRTIMP int __cdecl _setmode(int, int);
_CRTIMP int __cdecl _sopen(const char *, int, int, ...);
_CRTIMP long __cdecl _tell(int);
_CRTIMP int __cdecl _umask(int);
_CRTIMP int __cdecl _unlink(const char *);
_CRTIMP int __cdecl _write(int, const void *, unsigned int);

#if _INTEGRAL_MAX_BITS >= 64   
_CRTIMP __int64 __cdecl _filelengthi64(int);
_CRTIMP long __cdecl _findfirsti64(const char *, struct _finddatai64_t *);
_CRTIMP int __cdecl _findnexti64(long, struct _finddatai64_t *);
_CRTIMP __int64 __cdecl _lseeki64(int, __int64, int);
_CRTIMP __int64 __cdecl _telli64(int);
#endif  /* _INTEGRAL_MAX_BITS >= 64    */

#ifndef _MAC
#ifndef _WIO_DEFINED

/* wide function prototypes, also declared in wchar.h  */

_CRTIMP int __cdecl _waccess(const wchar_t *, int);
_CRTIMP int __cdecl _wchmod(const wchar_t *, int);
_CRTIMP int __cdecl _wcreat(const wchar_t *, int);
_CRTIMP long __cdecl _wfindfirst(const wchar_t *, struct _wfinddata_t *);
_CRTIMP int __cdecl _wfindnext(long, struct _wfinddata_t *);
_CRTIMP int __cdecl _wunlink(const wchar_t *);
_CRTIMP int __cdecl _wrename(const wchar_t *, const wchar_t *);
_CRTIMP int __cdecl _wopen(const wchar_t *, int, ...);
_CRTIMP int __cdecl _wsopen(const wchar_t *, int, int, ...);
_CRTIMP wchar_t * __cdecl _wmktemp(wchar_t *);

#if _INTEGRAL_MAX_BITS >= 64
_CRTIMP long __cdecl _wfindfirsti64(const wchar_t *, struct _wfinddatai64_t *);
_CRTIMP int __cdecl _wfindnexti64(long, struct _wfinddatai64_t *);
#endif  /* _INTEGRAL_MAX_BITS >= 64 */

#define _WIO_DEFINED
#endif  /* _WIO_DEFINED */
#endif  /* _MAC */

#ifndef _NOT_CRTL_BUILD_
#ifdef _MT
int __cdecl _chsize_lk(int,long);
int __cdecl _close_lk(int);
long __cdecl _lseek_lk(int, long, int);
int __cdecl _setmode_lk(int, int);
int __cdecl _read_lk(int, void *, unsigned int);
int __cdecl _write_lk(int, const void *, unsigned int);
#if _INTEGRAL_MAX_BITS >= 64
__int64 __cdecl _lseeki64_lk(int, __int64, int);
#endif  /* _INTEGRAL_MAX_BITS >= 64 */
#else  /* _MT */
#define _chsize_lk(fh,size)             _chsize(fh,size)
#define _close_lk(fh)                   _close(fh)
#define _lseek_lk(fh,offset,origin)     _lseek(fh,offset,origin)
#define _setmode_lk(fh,mode)            _setmode(fh,mode)
#define _read_lk(fh,buff,count)         _read(fh,buff,count)
#define _write_lk(fh,buff,count)        _write(fh,buff,count)
#if _INTEGRAL_MAX_BITS >= 64
#define _lseeki64_lk(fh,offset,origin)  _lseeki64(fh,offset,origin)
#endif  /* _INTEGRAL_MAX_BITS >= 64 */
#endif  /* _MT */
#endif  /* _NOT_CRTL_BUILD_ */

_CRTIMP long __cdecl _get_osfhandle(int);
_CRTIMP int __cdecl _open_osfhandle(long, int);

#if !__STDC__

/* Non-ANSI names for compatibility */

_CRTIMP int __cdecl access(const char *, int);
_CRTIMP int __cdecl chmod(const char *, int);
_CRTIMP int __cdecl chsize(int, long);
_CRTIMP int __cdecl close(int);
_CRTIMP int __cdecl creat(const char *, int);
_CRTIMP int __cdecl dup(int);
_CRTIMP int __cdecl dup2(int, int);
_CRTIMP int __cdecl eof(int);
_CRTIMP long __cdecl filelength(int);
_CRTIMP int __cdecl isatty(int);
_CRTIMP int __cdecl locking(int, int, long);
_CRTIMP long __cdecl lseek(int, long, int);
_CRTIMP char * __cdecl mktemp(char *);
_CRTIMP int __cdecl open(const char *, int, ...);
_CRTIMP int __cdecl read(int, void *, unsigned int);
_CRTIMP int __cdecl setmode(int, int);
_CRTIMP int __cdecl sopen(const char *, int, int, ...);
_CRTIMP long __cdecl tell(int);
_CRTIMP int __cdecl umask(int);
_CRTIMP int __cdecl unlink(const char *);
_CRTIMP int __cdecl write(int, const void *, unsigned int);

#endif  /* !__STDC__ */

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#ifdef _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_IO */
