/***
*syserr.h - constants/macros for error message routines
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file contains macros/constants for perror, strerror,
*       and _strerror.
*
*       [Internal]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_SYSERR
#define _INC_SYSERR

#ifndef _CRTBLD
/*
 * This is an internal C runtime header file. It is used when building
 * the C runtimes only. It is not to be used as a public header file.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

/* Macro for perror, strerror, and _strerror */

#define _sys_err_msg(m) _sys_errlist[(((m)<0)||((m)>=_sys_nerr)?_sys_nerr:(m))]

/* Maximum length of an error message.
   NOTE: This parameter value must be correspond to the length of the longest
   message in sys_errlist (source module syserr.c). */

#define _SYS_MSGMAX 38

#endif  /* _INC_SYSERR */
