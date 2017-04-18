/***
*mbdata.h - MBCS lib data
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Defines data for use when building MBCS libs and routines
*
*       [Internal].
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_MBDATA
#define _INC_MBDATA

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if defined (_WIN32)

#define NUM_ULINFO 6 /* multibyte full-width-latin upper/lower info */

#else  /* defined (_WIN32) */

#define NUM_ULINFO 12 /* multibyte full-width-latin upper/lower info */

#endif  /* defined (_WIN32) */

/* global variable to indicate current code page */
extern int __mbcodepage;

/* global flag indicating if the current code page is a multibyte code page */
extern int __ismbcodepage;

#if defined (_WIN32)
/* global variable to indicate current LCID */
extern int __mblcid;
#endif  /* defined (_WIN32) */

/* global variable to indicate current full-width-latin upper/lower info */
extern unsigned short __mbulinfo[NUM_ULINFO];

/*
 * MBCS - Multi-Byte Character Set
 */

/*
 * general use macros for model dependent/independent versions.
 */

#define _ISMBCP     (__ismbcodepage != 0)
#define _ISNOTMBCP  (__ismbcodepage == 0)

#define _ISLEADBYTE(c)  _ismbblead(c)
#define _ISTRAILBYTE(c) _ismbbtrail(c)

#define _ismbbtruelead(_lb,_ch) (!(_lb) && _ismbblead((_ch)))

/* internal use macros since tolower/toupper are locale-dependent */
#define _mbbisupper(_c) ((_mbctype[(_c) + 1] & _SBUP) == _SBUP)
#define _mbbislower(_c) ((_mbctype[(_c) + 1] & _SBLOW) == _SBLOW)

#define _mbbtolower(_c) (_mbbisupper(_c) ? _mbcasemap[_c] : _c)
#define _mbbtoupper(_c) (_mbbislower(_c) ? _mbcasemap[_c] : _c)


/* define full-width-latin upper/lower ranges */

#define _MBUPPERLOW1    __mbulinfo[0]
#define _MBUPPERHIGH1   __mbulinfo[1]
#define _MBCASEDIFF1    __mbulinfo[2]

#define _MBUPPERLOW2    __mbulinfo[3]
#define _MBUPPERHIGH2   __mbulinfo[4]
#define _MBCASEDIFF2    __mbulinfo[5]

#if !defined (_WIN32)

#define _MBLOWERLOW1    __mbulinfo[6]
#define _MBLOWERHIGH1   __mbulinfo[7]

#define _MBLOWERLOW2    __mbulinfo[8]
#define _MBLOWERHIGH2   __mbulinfo[9]

#define _MBDIGITLOW     __mbulinfo[10]
#define _MBDIGITHIGH    __mbulinfo[11]

#endif  /* !defined (_WIN32) */

/* Kanji-specific ranges */
#define _MBHIRALOW      0x829f  /* hiragana */
#define _MBHIRAHIGH     0x82f1

#define _MBKATALOW      0x8340  /* katakana */
#define _MBKATAHIGH     0x8396
#define _MBKATAEXCEPT   0x837f  /* exception */

#define _MBKIGOULOW     0x8141  /* kanji punctuation */
#define _MBKIGOUHIGH    0x81ac
#define _MBKIGOUEXCEPT  0x817f  /* exception */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_MBDATA */
