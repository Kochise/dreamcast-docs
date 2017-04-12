/***
*mbsdup.c - duplicate a string in malloc'd memory
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _mbsdup() - grab new memory, and duplicate the string into it.
*
*******************************************************************************/

#ifdef _MBCS
#define _strdup _mbsdup
#include <strdup.c>

#endif  /* _MBCS */
