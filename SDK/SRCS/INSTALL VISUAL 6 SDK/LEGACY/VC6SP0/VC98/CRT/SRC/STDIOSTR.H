/***
*stdiostr.h - definitions/declarations for stdiobuf, stdiostream
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       This file defines the classes, values, macros, and functions
*       used by the stdiostream and stdiobuf classes.
*       [AT&T C++]
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifdef __cplusplus

#ifndef _INC_STDIOSTREAM
#define _INC_STDIOSTREAM

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
// Currently, all MS C compilers for Win32 platforms default to 8 byte
// alignment.
#pragma pack(push,8)

#include <useoldio.h>

#endif  /* _MSC_VER */

/* Define _CRTIMP */

#ifndef _CRTIMP
/* current definition */
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

#ifndef _INTERNAL_IFSTRIP_
/* Define _CRTIMP1 */

#ifndef _CRTIMP1
#ifdef CRTDLL1
#define _CRTIMP1 __declspec(dllexport)
#else  /* CRTDLL1 */
#define _CRTIMP1 _CRTIMP
#endif  /* CRTDLL1 */
#endif  /* _CRTIMP1 */
#endif  /* _INTERNAL_IFSTRIP_ */

#include <iostream.h>
#include <stdio.h>

#ifdef _MSC_VER
#pragma warning(disable:4514)           // disable unwanted /W4 warning
// #pragma warning(default:4514)        // use this to reenable, if necessary
#endif  /* _MSC_VER */

class _CRTIMP1 stdiobuf : public streambuf  {
public:
        stdiobuf(FILE* f);
FILE *  stdiofile() { return _str; }

virtual int pbackfail(int c);
virtual int overflow(int c = EOF);
virtual int underflow();
virtual streampos seekoff( streamoff, ios::seek_dir, int =ios::in|ios::out);
virtual int sync();
        ~stdiobuf();
        int setrwbuf(int _rsize, int _wsize);
// protected:
// virtual int doallocate();
private:
        FILE * _str;
};

// obsolescent
class _CRTIMP1 stdiostream : public iostream {  // note: spec.'d as : public IOS...
public:
        stdiostream(FILE *);
        ~stdiostream();
        stdiobuf* rdbuf() const { return (stdiobuf*) ostream::rdbuf(); }

private:
};

#ifdef _MSC_VER
// Restore default packing
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_STDIOSTREAM */

#endif  /* __cplusplus */

