/***
*mlock.c - Multi-thread locking routines
*
*       Copyright (c) 1987-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*
*******************************************************************************/

#ifdef _MT

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <mtdll.h>
#include <rterr.h>
#include <stddef.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>
#include <dbgint.h>


/*
 * Local routines
 */
void __cdecl _lockerr_exit(char *);


/*
 * Global Data
 */

/*
 * Statically allocated critical section structures for _LOCKTAB_LOCK,
 * _EXIT_LOCK1, _HEAP_LOCK and _SIGNAL_LOCK.
 */
static CRITICAL_SECTION ltlcritsect;
static CRITICAL_SECTION xlcritsect;
static CRITICAL_SECTION hlcritsect;
static CRITICAL_SECTION sigcritsect;

/*
 * Lock Table
 * This table contains a pointer to the critical section management structure
 * for each lock.
 */
PCRITICAL_SECTION _locktable[_TOTAL_LOCKS] = {
        NULL,           /* 0  == no lock defined   *** OBSOLETE *** */
        &sigcritsect,   /* 1  == _SIGNAL_LOCK      */
        NULL,           /* 2  == _IOB_SCAN_LOCK    */
        NULL,           /* 3  == _TMPNAM_LOCK      */
        NULL,           /* 4  == _INPUT_LOCK       */
        NULL,           /* 5  == _OUTPUT_LOCK      */
        NULL,           /* 6  == _CSCANF_LOCK      */
        NULL,           /* 7  == _CPRINTF_LOCK     */
        NULL,           /* 8  == _CONIO_LOCK       */
        &hlcritsect,    /* 9  == _HEAP_LOCK    */
        NULL,           /* 10 == _BHEAP_LOCK       *** OBSOLETE *** */
        NULL,           /* 11 == _TIME_LOCK    */
        NULL,           /* 12 == _ENV_LOCK     */
        &xlcritsect,    /* 13 == _EXIT_LOCK1       */
        NULL,           /* 14 == _EXIT_LOCK2       *** OBSOLETE *** */
        NULL,           /* 15 == _THREADDATA_LOCK  *** OBSOLETE *** */
        NULL,           /* 16 == _POPEN_LOCK       */
        &ltlcritsect,   /* 17 == _LOCKTAB_LOCK     */
        NULL,           /* 18 == _OSFHND_LOCK      */
        NULL,           /* 19 == _SETLOCALE_LOCK   */
        NULL,           /* 20 == _LC_COLLATE_LOCK  *** OBSOLETE *** */
        NULL,           /* 21 == _LC_CTYPE_LOCK    *** OBSOLETE *** */
        NULL,           /* 22 == _LC_MONETARY_LOCK *** OBSOLETE *** */
        NULL,           /* 23 == _LC_NUMERIC_LOCK  *** OBSOLETE *** */
        NULL,           /* 24 == _LC_TIME_LOCK     *** OBSOLETE *** */
        NULL,           /* 25 == _STREAM_LOCKS     */
        NULL            /* ... */
        };


#define _FATAL  _amsg_exit(_RT_LOCK)

#ifdef _M_IX86
#pragma optimize("y",off)
#endif  /* _M_IX86 */

/***
*_mtinitlocks() - Initialize multi-thread lock scheme
*
*Purpose:
*       Perform whatever initialization is required for the multi-thread
*       locking (synchronization) scheme. This routine should be called
*       exactly once, during startup, and this must be before any requests
*       are made to assert locks.
*
*       NOTES: In Win32, the multi-thread locks are created individually,
*       each upon its first use. That is when any particular lock is asserted
*       for the first time, the underlying critical section is then allocated,
*       initialized and (finally) entered. This allocation and initialization
*       is protected under _LOCKTAB_LOCK. It is _mtinitlocks' job to set up
*       _LOCKTAB_LOCK. _EXIT_LOCK1 is also set up by _mtinitlock
*
*Entry:
*       <none>
*
*Exit:
*       returns on success
*       calls _amsg_exit on failure
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _mtinitlocks (
        void
        )
{


        /*
         * All we need to do is initialize _LOCKTAB_LOCK and _EXIT_LOCK1.
         */
        InitializeCriticalSection( _locktable[_LOCKTAB_LOCK] );
        InitializeCriticalSection( _locktable[_EXIT_LOCK1] );
        InitializeCriticalSection( _locktable[_HEAP_LOCK] );
        InitializeCriticalSection( _locktable[_SIGNAL_LOCK] );

}


/***
*_mtdeletelocks() - Delete all initialized locks
*
*Purpose:
*       Walks _locktable[] and _lockmap, and deletes every 'lock' (i.e.,
*       critical section) which has been initialized.
*
*       This function is intended for use in DLLs containing the C runtime
*       (i.e., crtdll.dll and user DLLs built using libcmt.lib and the
*       special startup objects). It is to be called from within the DLL's
*       entrypoint function when that function is called with
*       DLL_PROCESS_DETACH.
*
*Entry:
*       <none>
*
*Exit:
*
*Exceptions:
*       behavior undefined/unknown if a lock is being held when this routine
*       is called.
*
*******************************************************************************/

void __cdecl _mtdeletelocks(
        void
        )
{

        int locknum;

        for ( locknum = 0 ; locknum < _TOTAL_LOCKS ; locknum++ ) {

            /*
             * If the 'lock' has been created, delete it
             */
            /*
             * Delete the lock if it had been created
             */
            if ( _locktable[locknum] != NULL ) {
                if ( (locknum != _LOCKTAB_LOCK) && (locknum !=
                  _EXIT_LOCK1) && (locknum != _HEAP_LOCK) &&
                 (locknum != _SIGNAL_LOCK) )
                {
                /*
                 * Free the memory for the CritSect after deleting
                 * it.  It is okay to call free() if the heap lock
                 * is kept valid until after all calls to the heap.
                 */
                DeleteCriticalSection(_locktable[locknum]);
                _free_crt(_locktable[locknum]);
                }
            }

        }

        /*
         * Finally, clean up the special locks
         */
        DeleteCriticalSection( _locktable[_HEAP_LOCK] );
        DeleteCriticalSection( _locktable[_EXIT_LOCK1] );
        DeleteCriticalSection( _locktable[_LOCKTAB_LOCK] );
        DeleteCriticalSection( _locktable[_SIGNAL_LOCK] );

}


/***
* _lock - Acquire a multi-thread lock
*
*Purpose:
*       Note that it is legal for a thread to aquire _EXIT_LOCK1
*       multiple times.
*
*Entry:
*       locknum = number of the lock to aquire
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _lock (
        int locknum
        )
{

        PCRITICAL_SECTION pcs;


        /*
         * Create/open the lock, if necessary
         */
        if ( _locktable[locknum] == NULL ) {

            if ( (pcs = _malloc_crt(sizeof(CRITICAL_SECTION))) == NULL )
                _amsg_exit(_RT_LOCK);

            _mlock(_LOCKTAB_LOCK);  /*** WARNING: Recursive lock call ***/

            if ( _locktable[locknum] == NULL ) {
                InitializeCriticalSection(pcs);
                _locktable[locknum] = pcs;
            }
            else {
                _free_crt(pcs);
            }

            _munlock(_LOCKTAB_LOCK);
        }

        /*
         * Enter the critical section.
         */

        EnterCriticalSection( _locktable[locknum] );

}


/***
* _unlock - Release multi-thread lock
*
*Purpose:
*       Note that it is legal for a thread to aquire _EXIT_LOCK1
*       multiple times.
*
*Entry:
*       locknum = number of the lock to release
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _unlock (
        int locknum
        )
{

        /*
         * leave the critical section.
         */
        LeaveCriticalSection( _locktable[locknum] );

}


#ifdef _M_IX86
#pragma optimize("y",on)
#endif  /* _M_IX86 */

/***
*_lockerr_exit() - Write error message and die
*
*Purpose:
*       Attempt to write out the unexpected lock error message, then terminate
*       the program by a direct API call.  This function is used in place of
*       amsg_exit(_RT_LOCK) when it is judged unsafe to allow further lock
*       or unlock calls.
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _lockerr_exit (
        char *msg
        )
{
        FatalAppExit(0, msg);       /* Die with message box */
        ExitProcess(255);           /* Just die */
}


#endif  /* _MT */
