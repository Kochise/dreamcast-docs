/***
*sys/locking.h - flags for locking() function
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines the flags for the locking() function.
*       [System V]
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_LOCKING
#define _INC_LOCKING

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

#define _LK_UNLCK       0       /* unlock the file region */
#ifdef _WIN32
#define _LK_LOCK        1       /* lock the file region */
#endif  /* _WIN32 */
#define _LK_NBLCK       2       /* non-blocking lock */
#ifdef _WIN32
#define _LK_RLCK        3       /* lock for writing */
#endif  /* _WIN32 */
#define _LK_NBRLCK      4       /* non-blocking lock for writing */

#if !__STDC__
/* Non-ANSI names for compatibility */
#define LK_UNLCK        _LK_UNLCK
#ifdef _WIN32
#define LK_LOCK         _LK_LOCK
#endif  /* _WIN32 */
#define LK_NBLCK        _LK_NBLCK
#ifdef _WIN32
#define LK_RLCK         _LK_RLCK
#endif  /* _WIN32 */
#define LK_NBRLCK       _LK_NBRLCK
#endif  /* !__STDC__ */

#endif  /* _INC_LOCKING */
