/***
*wcrtexew.c - Startup code for a wide character Windows EXE built /MD
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _wWinMainCRTStartup, the C Run-Time Library start-up code
*       for a wide character Windows (GUI) application linked with MSVCRT.LIB.
*       This module includes wcrtexe.c, which in turn includes crtexe.c,
*       which contains the common code.
*
*******************************************************************************/

#ifdef CRTDLL
#define _WINMAIN_
#include "wcrtexe.c"
#endif  /* CRTDLL */
