/***
*tidtable.c - Access thread data table
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This module contains the following routines for multi-thread
*       data support:
*
*       _mtinit     = Initialize the mthread data
*       _getptd     = get the pointer to the per-thread data structure for
*                       the current thread
*       _freeptd    = free up a per-thread data structure and its
*                       subordinate structures
*       __threadid  = return thread ID for the current thread
*       __threadhandle = return pseudo-handle for the current thread
*
*******************************************************************************/

#if defined (_MT)

# if defined(_NTSUBSET_)

#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>
#include <ntstatus.h>
#include <ntos.h>
#include <fsrtl.h>

# endif /* _NTSUBSET_ */

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <mtdll.h>
#include <memory.h>
#include <msdos.h>
#include <rterr.h>
#include <stdlib.h>
#include <stddef.h>
#include <dbgint.h>

unsigned long __tlsindex = 0xffffffff;



/****
*_mtinit() - Init multi-thread data bases
*
*Purpose:
*       (1) Call _mtinitlocks to create/open all lock semaphores.
*       (2) Allocate a TLS index to hold pointers to per-thread data
*           structure.
*
*       NOTES:
*       (1) Only to be called ONCE at startup
*       (2) Must be called BEFORE any mthread requests are made
*
*Entry:
*       <NONE>
*Exit:
*       returns on success
*       calls _amsg_exit on failure
*
*Uses:
*       <any registers may be modified at init time>
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _mtinit (
        void
        )
{
        _ptiddata ptd;


        /*
         * Initialize the mthread lock data base
         */

        _mtinitlocks();

        /*
         * Allocate a TLS index to maintain pointers to per-thread data
         */
        if ( (__tlsindex = TlsAlloc()) == 0xffffffff )
            return FALSE;       /* fail to load DLL */


        /*
         * Create a per-thread data structure for this (i.e., the startup)
         * thread.
         */
        if ( ((ptd = _calloc_crt(1, sizeof(struct _tiddata))) == NULL) ||
             !TlsSetValue(__tlsindex, (LPVOID)ptd) )
            return FALSE;       /* fail to load DLL */

        /*
         * Initialize the per-thread data
         */

        _initptd(ptd);

        ptd->_tid = GetCurrentThreadId();
        ptd->_thandle = (unsigned long)(-1L);


        return TRUE;
}


/****
*_mtterm() - Clean-up multi-thread data bases
*
*Purpose:
*       (1) Call _mtdeletelocks to free up all lock semaphores.
*       (2) Free up the TLS index used to hold pointers to
*           per-thread data structure.
*
*       NOTES:
*       (1) Only to be called ONCE at termination
*       (2) Must be called AFTER all mthread requests are made
*
*Entry:
*       <NONE>
*Exit:
*       returns
*
*Uses:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _mtterm (
        void
        )
{


        /*
         * Clean up the mthread lock data base
         */

        _mtdeletelocks();

        /*
         * Free up the TLS index
         *
         * (Set the variable __tlsindex back to the unused state (-1L).)
         */

        if ( __tlsindex != 0xffffffff ) {
            TlsFree(__tlsindex);
            __tlsindex = 0xffffffff;
        }
}




/***
*void _initptd(_ptiddata ptd) - initialize a per-thread data structure
*
*Purpose:
*       This routine handles all of the per-thread initialization
*       which is common to _beginthread, _beginthreadex, _mtinit
*       and _getptd.
*
*Entry:
*       pointer to a per-thread data block
*
*Exit:
*       the common fields in that block are initialized
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _initptd (
        _ptiddata ptd
        )
{
        ptd->_pxcptacttab = (void *)_XcptActTab;
        ptd->_holdrand = 1L;

#ifdef _M_MRX000
        /*
         * MIPS per-thread data
         */
        ptd->_MipsPtdDelta =
        ptd->_MipsPtdEpsilon = -1L ;
#endif  /* _M_MRX000 */
}



/***
*_ptiddata _getptd(void) - get per-thread data structure for the current thread
*
*Purpose:
*
*Entry:
*       unsigned long tid
*
*Exit:
*       success = pointer to _tiddata structure for the thread
*       failure = fatal runtime exit
*
*Exceptions:
*
*******************************************************************************/

_ptiddata __cdecl _getptd (
        void
        )
{
        _ptiddata ptd;
        DWORD   TL_LastError;


        TL_LastError = GetLastError();
        if ( (ptd = TlsGetValue(__tlsindex)) == NULL ) {
            /*
             * no per-thread data structure for this thread. try to create
             * one.
             */
            if ( ((ptd = _calloc_crt(1, sizeof(struct _tiddata))) != NULL) &&
                TlsSetValue(__tlsindex, (LPVOID)ptd) ) {

                /*
                 * Initialize of per-thread data
                 */

                _initptd(ptd);

                ptd->_tid = GetCurrentThreadId();
                ptd->_thandle = (unsigned long)(-1L);
            }
            else
                _amsg_exit(_RT_THREAD); /* write message and die */
            }

        SetLastError(TL_LastError);


        return(ptd);
}


/***
*void _freeptd(_ptiddata) - free up a per-thread data structure
*
*Purpose:
*       Called from _endthread and from a DLL thread detach handler,
*       this routine frees up the per-thread buffer associated with a
*       thread that is going away.  The tiddata structure itself is
*       freed, but not until its subordinate buffers are freed.
*
*Entry:
*       pointer to a per-thread data block (malloc-ed memory)
*       If NULL, the pointer for the current thread is fetched.
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _freeptd (
        _ptiddata ptd
        )
{


        /*
         * Do nothing unless per-thread data has been allocated for this module!
         */

        if ( __tlsindex != 0xFFFFFFFF ) {
            /*
             * if parameter "ptd" is NULL, get the per-thread data pointer
             * Must NOT call _getptd because it will allocate one if none exists!
             */

            if ( ! ptd )
                ptd = TlsGetValue(__tlsindex );

            /*
             * Free up the _tiddata structure & its malloc-ed buffers.
             */

            if ( ptd ) {
                if(ptd->_errmsg)
                    _free_crt((void *)ptd->_errmsg);

                if(ptd->_namebuf0)
                    _free_crt((void *)ptd->_namebuf0);

                if(ptd->_namebuf1)
                    _free_crt((void *)ptd->_namebuf1);

                if(ptd->_asctimebuf)
                    _free_crt((void *)ptd->_asctimebuf);

                if(ptd->_gmtimebuf)
                    _free_crt((void *)ptd->_gmtimebuf);

                if(ptd->_cvtbuf)
                    _free_crt((void *)ptd->_cvtbuf);

                                if (ptd->_pxcptacttab != _XcptActTab)
                                        _free_crt((void *)ptd->_pxcptacttab);

                _free_crt((void *)ptd);
            }

            /*
             * Zero out the one pointer to the per-thread data block
             */

            TlsSetValue(__tlsindex, (LPVOID)0);
        }


}



/***
*__threadid()     - Returns current thread ID
*__threadhandle() - Returns "pseudo-handle" for current thread
*
*Purpose:
*       The two function are simply do-nothing wrappers for the corresponding
*       Win32 APIs (GetCurrentThreadId and GetCurrentThread, respectively).
*
*Entry:
*       void
*
*Exit:
*       thread ID value
*
*Exceptions:
*
*******************************************************************************/

_CRTIMP unsigned long __cdecl __threadid (
        void
        )
{
        return( GetCurrentThreadId() );
}

_CRTIMP unsigned long __cdecl __threadhandle(
        void
        )
{
        return( (unsigned long)GetCurrentThread() );
}

#endif  /* defined (_MT) */
