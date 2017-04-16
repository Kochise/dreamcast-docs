/***
*cinitexe.c - C Run-Time Startup Initialization
*
*       Copyright (c) 1992-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Do C++ initialization segment declarations for the EXE in CRT DLL
*       model
*
*Notes:
*       The C++ initializers will exist in the user EXE's data segment
*       so the special segments to contain them must be in the user EXE.
*
*******************************************************************************/

#ifndef _MAC

#include <stdio.h>
#include <internal.h>

#pragma data_seg(".CRT$XIA")
_PVFV __xi_a[] = { NULL };

#pragma data_seg(".CRT$XIZ")
_PVFV __xi_z[] = { NULL };

#pragma data_seg(".CRT$XCA")
_PVFV __xc_a[] = { NULL };

#pragma data_seg(".CRT$XCZ")
_PVFV __xc_z[] = { NULL };

#pragma data_seg()  /* reset */


#pragma comment(linker, "/merge:.CRT=.data")

#pragma comment(linker, "/defaultlib:kernel32.lib")

#pragma comment(linker, "/disallowlib:libc.lib")
#pragma comment(linker, "/disallowlib:libcd.lib")
#pragma comment(linker, "/disallowlib:libcmt.lib")
#pragma comment(linker, "/disallowlib:libcmtd.lib")
#ifdef _DEBUG
#pragma comment(linker, "/disallowlib:msvcrt.lib")
#else  /* _DEBUG */
#pragma comment(linker, "/disallowlib:msvcrtd.lib")
#endif  /* _DEBUG */

#else  /* _MAC */

#include <cruntime.h>
#include <msdos.h>
#include <stdio.h>
#include <stdlib.h>
#include <internal.h>
#include <fltintrn.h>
#include <mpw.h>
#include <mtdll.h>
#include <macos\types.h>
#include <macos\segload.h>
#include <macos\gestalte.h>
#include <macos\osutils.h>
#include <macos\traps.h>

/*
 * pointers to initialization functions
 */

#pragma data_seg(".CRT$XIA")
PFV __xi_a = 0;  /* C initializers */

#pragma data_seg(".CRT$XIZ")
PFV __xi_z      = 0;

#pragma data_seg(".CRT$XCA")
PFV __xc_a = 0;  /* C++ initializers */

#pragma data_seg(".CRT$XCZ")
PFV __xc_z = 0;

#pragma data_seg(".CRT$XPA")
PFV __xp_a = 0;  /* C pre-terminators */

#pragma data_seg(".CRT$XPZ")
PFV __xp_z = 0;

#pragma data_seg(".CRT$XTA")
PFV __xt_a = 0;   /* C terminators */

#pragma data_seg(".CRT$XTZ")
PFV __xt_z = 0;

#pragma data_seg()  /* reset */


#ifdef _M_MPPC

#pragma comment(linker, "/defaultlib:interfac.lib")

#pragma comment(linker, "/disallowlib:libc.lib")
#pragma comment(linker, "/disallowlib:libcd.lib")
#ifdef _DEBUG
#pragma comment(linker, "/disallowlib:msvcrt.lib")
#else  /* _DEBUG */
#pragma comment(linker, "/disallowlib:msvcrtd.lib")
#endif  /* _DEBUG */

#endif  /* _M_MPPC */

#endif  /* _MAC */
