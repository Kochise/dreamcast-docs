/***
*mbsspnp.c - Find first string char in charset, pointer return (MBCS)
*
*       Copyright (c) 1985-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Returns maximum leading segment of string consisting solely
*       of characters from charset.  Handles MBCS characters correctly.
*
*******************************************************************************/

#ifdef _MBCS
#define _RETURN_PTR
#include "mbsspn.c"
#endif  /* _MBCS */
