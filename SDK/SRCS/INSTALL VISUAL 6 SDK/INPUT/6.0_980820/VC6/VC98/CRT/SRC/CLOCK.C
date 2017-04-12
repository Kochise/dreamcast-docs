/***
*clock.c - Contains the clock runtime
*
*       Copyright (c) 1987-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       The clock runtime returns the processor time used by
*       the current process.
*
*******************************************************************************/

#ifdef _WIN32


#include <cruntime.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

#include <internal.h>
#include <sys\timeb.h>
#include <sys\types.h>



void __cdecl __inittime(void);

#ifdef _MSC_VER

#pragma data_seg(".CRT$XIC")
static _PVFV pinit = __inittime;

#pragma data_seg()

#endif  /* _MSC_VER */

static unsigned __int64 start_tics;

/***
*clock_t clock() - Return the processor time used by this process.
*
*Purpose:
*       This routine calculates how much time the calling process
*       has used.  At startup time, startup calls __inittime which stores
*       the initial time.  The clock routine calculates the difference
*       between the current time and the initial time.
*
*       Clock must reference _cinitime so that _cinitim.asm gets linked in.
*       That routine, in turn, puts __inittime in the startup initialization
*       routine table.
*
*Entry:
*       No parameters.
*       itime is a static structure of type timeb.
*
*Exit:
*       If successful, clock returns the number of CLK_TCKs (milliseconds)
*       that have elapsed.  If unsuccessful, clock returns -1.
*
*Exceptions:
*       None.
*
*******************************************************************************/

clock_t __cdecl clock (
        void
        )
{
        unsigned __int64 current_tics;
        FILETIME ct;

        GetSystemTimeAsFileTime( &ct );

        current_tics = (unsigned __int64)ct.dwLowDateTime +
                       (((unsigned __int64)ct.dwHighDateTime) << 32);

        /* calculate the elapsed number of 100 nanosecond units */
        current_tics -= start_tics;

        /* return number of elapsed milliseconds */
        return (clock_t)(current_tics / 10000);
}

/***
*void __inittime() - Initialize the time location
*
*Purpose:
*       This routine stores the time of the process startup.
*       It is only linked in if the user issues a clock runtime call.
*
*Entry:
*       No arguments.
*
*Exit:
*       No return value.
*
*Exceptions:
*       None.
*
*******************************************************************************/

void __cdecl __inittime (
        void
        )
{
        FILETIME st;

        GetSystemTimeAsFileTime( &st );

        start_tics = (unsigned __int64)st.dwLowDateTime +
                     (((unsigned __int64)st.dwHighDateTime) << 32);
}



#else  /* _WIN32 */

#if defined (_M_MPPC) || defined (_M_M68K)


#include <cruntime.h>
#include <stdio.h>
#include <time.h>
#include <fltintrn.h>            /* PFV definition */
#include <sys\timeb.h>
#include <sys\types.h>
#include <internal.h>

/* define the entry in initializer table */

#pragma data_seg(".CRT$XIC")

static PFV __pinittime = _inittime;

#pragma data_seg()

static struct _timeb __itimeb;

/***
*clock_t clock() - Return the processor time used by this process.
*
*Purpose:
*       This routine calculates how much time the calling process
*       has used.  At startup time, startup calls _inittime which stores
*       the initial time.  The clock routine calculates the difference
*       between the current time and the initial time.
*
*       Clock must reference _cinitime so that _cinitim.asm gets linked in.
*       That routine, in turn, puts _inittime in the startup initialization
*       routine table.
*
*Entry:
*       No parameters.
*       itime is a static structure of type timeb.
*
*Exit:
*       If successful, clock returns the number of CLK_TCKs (milliseconds)
*       that have elapsed.  If unsuccessful, clock returns -1.
*
*Exceptions:
*       None.
*
*******************************************************************************/

clock_t __cdecl clock (
        void
        )
{
        struct _timeb now;
        clock_t elapsed;

        /* Calculate the difference between the initial time and now. */

        _ftime(&now);
        elapsed = (now.time - __itimeb.time) * CLOCKS_PER_SEC;
        elapsed += (int)now.millitm - (int)__itimeb.millitm;
        return(elapsed);

}



/***
*void _inittime() - Initialize the time location
*
*Purpose:
*       This routine stores the process's time of startup.
*       It is only linked in if the user issues a clock runtime
*       call.
*
*Entry:
*       No arguments.
*
*Exit:
*       No return value.
*
*Exceptions:
*       None.
*
*******************************************************************************/

void __cdecl _inittime (
        void
        )
{
        _ftime(&__itimeb);
}


/***
*time_t _GetApplicationStartTime() - Initialize the time location
*
*Purpose:
*       This routine stores the process's time of startup.
*       It is only linked in if the user issues a clock runtime
*       call.
*
*Entry:
*       No arguments.
*
*Exit:
*       initial application start time.
*
*Exceptions:
*       None.
*
*******************************************************************************/

time_t __cdecl _GetApplicationStartTime (
        void
        )
{

        /* The reference to _tzset causes _inittime to be executed at startup time.*/
        _tzset();
        return __itimeb.time ;
}


#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

#endif  /* _WIN32 */
