/***
*wcrt0.c - C runtime console EXE start-up routine (wchar_t version)
*
*       Copyright (c) 1993-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This the actual startup routine for console apps using wide
*       characters.  It calls the user's main routine _wmain() after
*       performing C Run-Time Library initialization.
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

#include "crt0.c"

