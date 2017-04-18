/***
*mbscat.c - contains mbscat() and mbscpy()
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       mbscpy() copies one string onto another.
*
*       mbscat() concatenates (appends) a copy of the source string to the
*       end of the destination string, returning the destination string.
*
*******************************************************************************/

#ifdef _MBCS
#define strcat _mbscat
#define strcpy _mbscpy
#define _MBSCAT
#include "strcat.c"
#endif  /* _MBCS */
