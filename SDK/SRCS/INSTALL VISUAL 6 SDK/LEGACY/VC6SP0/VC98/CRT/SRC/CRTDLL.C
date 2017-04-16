/***
*crtdll.c - CRT initialization for a DLL using the MSVCRT* model of C run-time
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This module contains the initialization entry point for the C run-time
*       stub in this DLL.  All C run-time code is located in the C Run-Time
*       Library DLL "MSVCRT*.DLL", except for a little bit of start-up code in
*       the EXE, and this code in each DLL.  This code is necessary to invoke
*       the C++ constructors for the C++ code in this DLL.
*
*       This entry point should either be specified as the DLL initialization
*       entry point, or else it must be called by the DLL initialization entry
*       point of the DLL with the same arguments that the entry point receives.
*
*       MPPC note:
*       This is the routine should be pulled in when building a DLL using CRT DLL
*       This should be put into ppccrt30.lib
*       User should either use _DllMainCRTStartup as -Init, and put their own init(if any) in _DllInit
*       Or call _DllMainCRTStartup in their init specified by -Init*
*
*******************************************************************************/

#ifndef _MAC

#ifdef CRTDLL

/*
 * SPECIAL BUILD MACRO! Note that crtexe.c (and crtexew.c) is linked in with
 * the client's code. It does not go into crtdll.dll! Therefore, it must be
 * built under the _DLL switch (like user code) and CRTDLL must be undefined.
 */
#undef  CRTDLL
#define _DLL

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>
#include <stdlib.h>
#define _DECL_DLLMAIN   /* enable prototypes for DllMain and _CRT_INIT */
#include <process.h>
#include <dbgint.h>


#ifdef _M_IX86

/*
 * The local copy of the Pentium FDIV adjustment flag
 *      and the address of the flag in MSVCRT*.DLL.
 */

extern int _adjust_fdiv;

extern int * _imp___adjust_fdiv;

#endif  /* _M_IX86 */


/*
 * routine in DLL to do initialization (in this case, C++ constructors)
 */

extern void __cdecl _initterm(_PVFV *, _PVFV *);

/*
 * pointers to initialization sections
 */

extern _PVFV __xc_a[], __xc_z[];    /* C++ initializers */

/*
 * flag set iff _CRTDLL_INIT was called with DLL_PROCESS_ATTACH
 */
static int __proc_attached = 0;


/*
 * Pointers to beginning and end of the table of function pointers manipulated
 * by _onexit()/atexit().  The atexit/_onexit code is shared for both EXE's and
 * DLL's but different behavior is required.  These values are initialized to
 * 0 by default and will be set to point to a malloc-ed memory block to mark
 * this module as an DLL.
 */

extern _PVFV *__onexitbegin;
extern _PVFV *__onexitend;


/*
 * User routine DllMain is called on all notifications
 */

extern BOOL WINAPI DllMain(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        ) ;

/* _pRawDllMain MUST be a common variable, not extern nor initialized! */

BOOL (WINAPI *_pRawDllMain)(HANDLE, DWORD, LPVOID);


/***
*BOOL WINAPI _CRT_INIT(hDllHandle, dwReason, lpreserved) - C++ DLL
*       initialization.
*BOOL WINAPI _DllMainCRTStartup(hDllHandle, dwReason, lpreserved) - C++ DLL
*       initialization.
*
*Purpose:
*       This is the entry point for DLL's linked with the C/C++ run-time libs.
*       This routine does the C runtime initialization for a DLL linked with
*       MSVCRT.LIB (whose C run-time code is thus in MSVCRT*.DLL.)
*       It will call the user notification routine DllMain on all 4 types of
*       DLL notifications.  The return code from this routine is the return
*       code from the user notification routine.
*
*       On DLL_PROCESS_ATTACH, the C++ constructors for the DLL will be called.
*
*       On DLL_PROCESS_DETACH, the C++ destructors and _onexit/atexit routines
*       will be called.
*
*Entry:
*
*Exit:
*
*******************************************************************************/

BOOL WINAPI _CRT_INIT(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
        /*
         * If this is a process detach notification, check that there has
         * been a prior (successful) process attachment.
         */
        if ( dwReason == DLL_PROCESS_DETACH ) {
            if ( __proc_attached > 0 )
                __proc_attached--;
            else
                /*
                 * no prior process attach. just return failure.
                 */
                return FALSE;
        }

#ifdef _M_IX86

        /*
         * Set the local copy of the Pentium FDIV adjustment flag
         */

        _adjust_fdiv = * _imp___adjust_fdiv;

#endif  /* _M_IX86 */

        /*
         * do C++ constructors (initializers) specific to this DLL
         */

        if ( dwReason == DLL_PROCESS_ATTACH ) {

            /*
             * create the onexit table.
             */
            if ( (__onexitbegin = (_PVFV *)_malloc_crt(32 * sizeof(_PVFV)))
                 == NULL )
                /*
                 * cannot allocate minimal required
                 * size. generate failure to load DLL
                 */
                return FALSE;

            *(__onexitbegin) = (_PVFV) NULL;

            __onexitend = __onexitbegin;

            /*
             * Invoke C++ constructors
             */
            _initterm(__xc_a,__xc_z);

            /*
             * Increment the process attached flag.
             */
            __proc_attached++;

        }
        else if ( dwReason == DLL_PROCESS_DETACH ) {

            /*
             * Any basic clean-up code that goes here must be
             * duplicated below in _DllMainCRTStartup for the
             * case where the user's DllMain() routine fails on a
             * Process Attach notification. This does not include
             * calling user C++ destructors, etc.
             */

            /*
             * do _onexit/atexit() terminators
             * (if there are any)
             *
             * These terminators MUST be executed in
             * reverse order (LIFO)!
             *
             * NOTE:
             *  This code assumes that __onexitbegin
             *  points to the first valid onexit()
             *  entry and that __onexitend points
             *  past the last valid entry. If
             *  __onexitbegin == __onexitend, the
             *  table is empty and there are no
             *  routines to call.
             */

            if (__onexitbegin) {
                _PVFV * pfend = __onexitend;

                while ( -- pfend >= __onexitbegin )
                    /*
                     * if current table entry is not
                     * NULL, call thru it.
                     */
                    if ( *pfend != NULL )
                        (**pfend)();

                /*
                 * free the block holding onexit table to
                 * avoid memory leaks.  Also zero the ptr
                 * variable so that it is clearly cleaned up.
                 */

                _free_crt ( __onexitbegin ) ;

                __onexitbegin = NULL ;
            }
        }

        return TRUE;
}


BOOL WINAPI _DllMainCRTStartup(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
        BOOL retcode = TRUE;

        /*
         * If this is a process detach notification, check that there has
         * been a prior process attach notification.
         */
        if ( (dwReason == DLL_PROCESS_DETACH) && (__proc_attached == 0) )
            return FALSE;

        if ( dwReason == DLL_PROCESS_ATTACH || dwReason == DLL_THREAD_ATTACH )
        {
            if ( _pRawDllMain )
                retcode = (*_pRawDllMain)(hDllHandle, dwReason, lpreserved);

            if ( retcode )
                retcode = _CRT_INIT(hDllHandle, dwReason, lpreserved);

            if ( !retcode )
                return FALSE;
        }

        retcode = DllMain(hDllHandle, dwReason, lpreserved);


        if ( (dwReason == DLL_PROCESS_ATTACH) && !retcode )
            /*
             * The user's DllMain routine returned failure, the C runtime
             * needs to be cleaned up. Do this by calling _CRT_INIT again,
             * this time imitating DLL_PROCESS_DETACH. Note this will also
             * clear the __proc_attached flag so the cleanup will not be
             * repeated upon receiving the real process detach notification.
             */
            _CRT_INIT(hDllHandle, DLL_PROCESS_DETACH, lpreserved);

        if ( (dwReason == DLL_PROCESS_DETACH) ||
             (dwReason == DLL_THREAD_DETACH) )
        {
            if ( _CRT_INIT(hDllHandle, dwReason, lpreserved) == FALSE )
                retcode = FALSE ;

            if ( retcode && _pRawDllMain )
                retcode = (*_pRawDllMain)(hDllHandle, dwReason, lpreserved);
        }

        return retcode ;
}

#endif  /* CRTDLL */

#else  /* _MAC */

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <fltintrn.h>
#include <dbgint.h>
#include <macos\types.h>
#include <macos\fragload.h>

/*
 * routine in DLL to do initialization (in this case, C++ constructors)
 */
extern void __cdecl _initterm(PFV *, PFV *);
static char * __cdecl _p2cstr_internal ( unsigned char * str );
static void * memcpy_internal ( void * dst, const void * src,   size_t count);
int _DllInit(InitBlockPtr pinitBlk);

/*
 * pointers to initialization functions
 */

extern PFV __xi_a ;

extern PFV __xi_z ;

extern PFV __xc_a ;  /* C++ initializers */

extern PFV __xc_z ;

extern PFV __xp_a ;  /* C pre-terminators */

extern PFV __xp_z ;

extern PFV __xt_a ;   /* C terminators */

extern PFV __xt_z ;

/*this globals are defined in DLL */
extern int __argc;

extern char **__argv;

extern PFV *__onexitbegin;
extern PFV *__onexitend;

/***
*void _DllMainCRTStartup(void)
*
*Purpose:
*       This routine does the C runtime initialization.
*
*Entry:
*
*Exit:
*
*******************************************************************************/

OSErr _DllMainCRTStartup(
        InitBlockPtr pinitBlk
        )
{
        int argc=1; /* three standard arguments to main */
        char *argv[2];
        char **environ = NULL;
        char szPgmName[32];
        char *pArg;


        memcpy_internal(szPgmName, (char *)0x910, sizeof(szPgmName));
        pArg = _p2cstr_internal(szPgmName);
        argv[0] = pArg;
        argv[1] = NULL;

        __argc = 1;
        __argv = argv;

        /*
         * intialize the global destruction table
         */
        if ( (__onexitbegin = (PFV *)_malloc_crt(32 * sizeof(PFV))) == NULL )
                        {
                        /*
                         * cannot allocate minimal required
                         * size. generate failure to load DLL
                         * any non-zero value will do...
                         */
                        return 1;
                        }

        *(__onexitbegin) = (PFV) NULL;

        __onexitend = __onexitbegin;

        /*
         * Do runtime startup initializers.
         */
        _initterm( &__xi_a, &__xi_z );


        /*
         * do C++ constructors (initializers) specific to this DLL
         */
        _initterm( &__xc_a, &__xc_z );

        return _DllInit(pinitBlk);
}

static char * __cdecl _p2cstr_internal (
        unsigned char * str
        )
{
        unsigned char *pchSrc;
        unsigned char *pchDst;
        int  cch;

        if ( str && *str )
            {
            pchDst = str;
            pchSrc = str + 1;

            for ( cch=*pchDst; cch; --cch )
                {
                *pchDst++ = *pchSrc++;
                }

            *pchDst = '\0';
            }

        return( str );
}


static void * memcpy_internal (
        void * dst,
        const void * src,
        size_t count
        )
{
        void * ret = dst;

        /*
         * copy from lower addresses to higher addresses
         */
        while (count--) {
            *(char *)dst = *(char *)src;
            dst = (char *)dst + 1;
            src = (char *)src + 1;
        }

        return(ret);
}

#endif  /* _MAC */
