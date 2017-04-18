/***
*abort.c - abort a program by raising SIGABRT
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines abort() - print a message and raise SIGABRT.
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#include <internal.h>
#include <rterr.h>
#include <signal.h>

/***
*void abort() - abort the current program by raising SIGABRT
*
*Purpose:
*       print out an abort message and raise the SIGABRT signal.  If the user
*       hasn't defined an abort handler routine, terminate the program
*       with exit status of 3 without cleaning up.
*
*       Multi-thread version does not raise SIGABRT -- this isn't supported
*       under multi-thread.
*
*Entry:
*       None.
*
*Exit:
*       Does not return.
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl abort (
        void
        )
{
        _NMSG_WRITE(_RT_ABORT); /* write the abort message */



        raise(SIGABRT);     /* raise abort signal */

        /* We usually won't get here, but it's possible that
           SIGABRT was ignored.  So hose the program anyway. */


        _exit(3);
}
