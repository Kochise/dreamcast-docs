/***
*wildcard.c - define the CRT internal variable _dowildcard
*
*       Copyright (c) 1994-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This variable is not public to users but is defined outside the
*       start-up code (CRTEXE.C) to reduce duplicate definitions.
*
*******************************************************************************/

#if defined (CRTDLL)

#include <internal.h>

int _dowildcard = 0;    /* should be in <internal.h> */

#endif  /* defined (CRTDLL) */
