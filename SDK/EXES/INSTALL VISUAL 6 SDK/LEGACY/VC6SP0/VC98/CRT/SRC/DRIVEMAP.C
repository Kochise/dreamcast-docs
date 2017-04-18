/***
*drivemap.c - _getdrives
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _getdrives()
*
*******************************************************************************/

#include <cruntime.h>
#include <oscalls.h>
#include <direct.h>

#if !defined (_WIN32)
#error ERROR - ONLY WIN32 TARGET SUPPORTED!
#endif  /* !defined (_WIN32) */

/***
*void _getdrivemap(void) - Get bit map of all available drives
*
*Purpose:
*
*Entry:
*
*Exit:
*       drive map with drive A in bit 0, B in 1, etc.
*
*Exceptions:
*
*******************************************************************************/

unsigned long __cdecl _getdrives()
{
    return (GetLogicalDrives());
}
