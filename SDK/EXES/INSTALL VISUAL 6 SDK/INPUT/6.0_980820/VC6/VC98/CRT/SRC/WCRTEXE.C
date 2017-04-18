/***
*wcrtexe.c - Initialization for client EXE using CRT DLL (Win32, Dosx32)
*            (wchar_t version)
*
*       Copyright (c) 1993-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Set up call to client's wmain() or wWinMain().
*
*******************************************************************************/


#define WPRFLAG 1

#ifndef _UNICODE
#define _UNICODE 1
#endif  /* _UNICODE */

#ifndef UNICODE
#define UNICODE 1
#endif  /* UNICODE */

#undef _MBCS /* UNICODE not _MBCS */

#include "crtexe.c"

