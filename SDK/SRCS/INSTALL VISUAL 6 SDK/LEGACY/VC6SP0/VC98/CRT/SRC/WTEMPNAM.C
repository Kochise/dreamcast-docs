/***
*wtempnam.c - generate unique file name (wchar_t version)
*
*       Copyright (c) 1986-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*
*******************************************************************************/


#ifndef _UNICODE
#define _UNICODE 1
#endif  /* _UNICODE */

#ifndef UNICODE
#define UNICODE 1
#endif  /* UNICODE */

#undef _MBCS /* UNICODE not _MBCS */

#include "tempnam.c"

