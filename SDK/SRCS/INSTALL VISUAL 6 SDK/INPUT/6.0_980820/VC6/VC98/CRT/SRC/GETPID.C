/***
*getpid.c - get current process id
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Defines _getpid() - get current process id
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <oscalls.h>

/***
*int _getpid() - get current process id
*
*Purpose:
*       Returns the current process id for the calling process.
*
*Entry:
*       None.
*
*Exit:
*       Returns the current process id.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _getpid (
        void
        )
{
        return GetCurrentProcessId();
}

#else  /* _MAC */


#include <cruntime.h>
#include <internal.h>
#include <stdio.h>
#include <io.h>
#include <errno.h>
#include <stddef.h>
#include <macos\errors.h>
#include <macos\processe.h>
#include <macos\gestalte.h>
#include <macos\osutils.h>
#include <macos\traps.h>
#include <macos\toolutil.h>
#include <macos\memory.h>

/***
*int _getpid() - get current process id
*
*Purpose:
*       Returns the current process id for the calling process.
*
*Entry:
*       None.
*
*Exit:
*       Returns the current process id.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/
extern time_t _GetApplicationStartTime();

int __cdecl _getpid (
        void
        )
{
        ProcessSerialNumber psn;
        REG3 unsigned number;


        if (__TrapFromGestalt(gestaltOSAttr, gestaltLaunchControl))
        {
            GetCurrentProcess(&psn);
            number = (unsigned) psn.lowLongOfPSN;
        }
        else
        {
            number = (unsigned)_GetApplicationStartTime();
        }
        return number;

}

#endif  /* _MAC */
