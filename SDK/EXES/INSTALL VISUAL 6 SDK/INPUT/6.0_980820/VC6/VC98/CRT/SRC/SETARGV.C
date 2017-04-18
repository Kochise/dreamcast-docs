/***
*setargv.c - generic _setargv routine
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Linking in this module replaces the normal setargv with the
*       wildcard setargv.
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>

/***
*_setargv - sets argv by calling __setargv
*
*Purpose:
*       Routine directly transfers to __setargv (defined in stdargv.asm).
*
*Entry:
*       See __setargv.
*
*Exit:
*       See __setargv.
*
*Exceptions:
*       See __setargv.
*
*******************************************************************************/

void __cdecl _setargv (
        void
        )
{
        __setargv();
}
