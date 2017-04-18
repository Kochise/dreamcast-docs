/***
*purevirt.c - stub to trap pure virtual function calls
*
*       Copyright (c) 1992-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _purecall() -
*
*******************************************************************************/


#include <cruntime.h>
#include <internal.h>
#include <rterr.h>

/***
*void _purecall(void) -
*
*Purpose:
*
*Entry:
*       No arguments
*
*Exit:
*       Never returns
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _purecall(
        void
        )
{
        _amsg_exit(_RT_PUREVIRT);
}

