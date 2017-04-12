/***
*difftime.c - return difference between two times as a double
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Find difference between two time in seconds.
*
*******************************************************************************/


#include <cruntime.h>
#include <time.h>

/***
*double difftime(b, a) - find difference between two times
*
*Purpose:
*       returns difference between two times (b-a)
*
*       Multi-thread version must use pascal calling convention to be re-entrant.
*
*Entry:
*       long a, b - times to difference (actually are time_t values)
*
*Exit:
*       returns a double with the time in seconds between two times
*
*Exceptions:
*
*******************************************************************************/

double __cdecl difftime (
        time_t b,
        time_t a
        )
{
        return( (double)( b - a ) );
}

