/***
*thread.c - Begin and end a thread
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This source contains the _beginthread() and _endthread()
*       routines which are used to start and terminate a thread.
*
*******************************************************************************/

#ifdef _MT

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <mtdll.h>
#include <msdos.h>
#include <malloc.h>
#include <process.h>
#include <rterr.h>
#include <dbgint.h>

/*
 * Startup code for new thread.
 */
static unsigned long WINAPI _threadstart(void *);

/*
 * declare pointers to per-thread FP initialization and termination routines
 */
_PVFV _FPmtinit;
_PVFV _FPmtterm;


/***
*_beginthread() - Create a child thread
*
*Purpose:
*       Create a child thread.
*
*Entry:
*       initialcode = pointer to thread's startup code address
*       stacksize = size of stack
*       argument = argument to be passed to new thread
*
*Exit:
*       success = handle for new thread if successful
*
*       failure = (unsigned long) -1L in case of error, errno and _doserrno
*                 are set
*
*Exceptions:
*
*******************************************************************************/

unsigned long __cdecl _beginthread (
        void (__cdecl * initialcode) (void *),
        unsigned stacksize,
        void * argument
        )
{
        _ptiddata ptd;                  /* pointer to per-thread data */
        unsigned long thdl;             /* thread handle */
        unsigned long errcode = 0L;     /* Return from GetLastError() */

        /*
         * Allocate and initialize a per-thread data structure for the to-
         * be-created thread.
         */
        if ( (ptd = _calloc_crt(1, sizeof(struct _tiddata))) == NULL )
                goto error_return;

        /*
         * Initialize the per-thread data
         */

        _initptd(ptd);

        ptd->_initaddr = (void *) initialcode;
        ptd->_initarg = argument;

        /*
         * Create the new thread. Bring it up in a suspended state so that
         * the _thandle and _tid fields are filled in before execution
         * starts.
         */
        if ( (ptd->_thandle = thdl = (unsigned long)
              CreateThread( NULL,
                            stacksize,
                            _threadstart,
                            (LPVOID)ptd,
                            CREATE_SUSPENDED,
                            (LPDWORD)&(ptd->_tid) ))
             == 0L )
        {
                errcode = GetLastError();
                goto error_return;
        }

        /*
         * Start the new thread executing
         */
        if ( ResumeThread( (HANDLE)thdl ) == (DWORD)(-1L) ) {
                errcode = GetLastError();
                goto error_return;
        }

        /*
         * Good return
         */
        return(thdl);

        /*
         * Error return
         */
error_return:
        /*
         * Either ptd is NULL, or it points to the no-longer-necessary block
         * calloc-ed for the _tiddata struct which should now be freed up.
         */
        _free_crt(ptd);

        /*
         * Map the error, if necessary.
         */
        if ( errcode != 0L )
                _dosmaperr(errcode);

        return((unsigned long)-1L);
}


/***
*_threadstart() - New thread begins here
*
*Purpose:
*       The new thread begins execution here.  This routine, in turn,
*       passes control to the user's code.
*
*Entry:
*       void *ptd       = pointer to _tiddata structure for this thread
*
*Exit:
*       Never returns - terminates thread!
*
*Exceptions:
*
*******************************************************************************/

static unsigned long WINAPI _threadstart (
        void * ptd
        )
{
        /*
         * Stash the pointer to the per-thread data stucture in TLS
         */
        if ( !TlsSetValue(__tlsindex, ptd) )
                _amsg_exit(_RT_THREAD);

        /*
         * Call fp initialization, if necessary
         */
        if ( _FPmtinit != NULL )
                (*_FPmtinit)();

        /*
         * Guard call to user code with a _try - _except statement to
         * implement runtime errors and signal support
         */
        __try {
                ( (void(__cdecl *)(void *))(((_ptiddata)ptd)->_initaddr) )
                    ( ((_ptiddata)ptd)->_initarg );

                _endthread();
        }
        __except ( _XcptFilter(GetExceptionCode(), GetExceptionInformation()) )
        {
                /*
                 * Should never reach here
                 */
                _exit( GetExceptionCode() );

        } /* end of _try - _except */

        /*
         * Never executed!
         */
        return(0L);
}


/***
*_endthread() - Terminate the calling thread
*
*Purpose:
*
*Entry:
*       void
*
*Exit:
*       Never returns!
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _endthread (
        void
        )
{
        _ptiddata ptd;           /* pointer to thread's _tiddata struct */

        /*
         * Call fp termination, if necessary
         */
        if ( _FPmtterm != NULL )
                (*_FPmtterm)();

        if ( (ptd = _getptd()) == NULL )
                _amsg_exit(_RT_THREAD);

        /*
         * Close the thread handle (if there was one)
         */
        if ( ptd->_thandle != (unsigned long)(-1L) )
                (void) CloseHandle( (HANDLE)(ptd->_thandle) );

        /*
         * Free up the _tiddata structure & its subordinate buffers
         *      _freeptd() will also clear the value for this thread
         *      of the TLS variable __tlsindex.
         */
        _freeptd(ptd);

        /*
         * Terminate the thread
         */
        ExitThread(0);

}

#endif  /* _MT */
