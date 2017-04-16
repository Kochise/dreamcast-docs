/***
*onexit.c - save function for execution on exit
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _onexit(), atexit() - save function for execution at exit
*
*       In order to save space, the table is allocated via malloc/realloc,
*       and only consumes as much space as needed.  __onexittable is
*       set to point to the table if onexit() is ever called.
*
*******************************************************************************/

#ifdef _WIN32

#include <cruntime.h>
#include <mtdll.h>
#include <stdlib.h>
#include <internal.h>
#include <malloc.h>
#include <rterr.h>
#include <windows.h>
#include <dbgint.h>


void __cdecl __onexitinit(void);

#ifdef _MSC_VER

#pragma data_seg(".CRT$XIC")
static _PVFV pinit = __onexitinit;

#pragma data_seg()

#endif  /* _MSC_VER */

/*
 * Define pointers to beginning and end of the table of function pointers
 * manipulated by _onexit()/atexit().
 */
extern _PVFV *__onexitbegin;
extern _PVFV *__onexitend;

/*
 * Define increment (in entries) for growing the _onexit/atexit table
 */
#define ONEXITTBLINCR   4


/***
*_onexit(func), atexit(func) - add function to be executed upon exit
*
*Purpose:
*       The _onexit/atexit functions are passed a pointer to a function
*       to be called when the program terminate normally.  Successive
*       calls create a register of functions that are executed last in,
*       first out.
*
*Entry:
*       void (*func)() - pointer to function to be executed upon exit
*
*Exit:
*       onexit:
*           Success - return pointer to user's function.
*           Error - return NULL pointer.
*       atexit:
*           Success - return 0.
*           Error - return non-zero value.
*
*Notes:
*       This routine depends on the behavior of _initterm() in CRT0DAT.C.
*       Specifically, _initterm() must not skip the address pointed to by
*       its first parameter, and must also stop before the address pointed
*       to by its second parameter.  This is because _onexitbegin will point
*       to a valid address, and _onexitend will point at an invalid address.
*
*Exceptions:
*
*******************************************************************************/


_onexit_t __cdecl _onexit (
        _onexit_t func
        )
{
        _PVFV   *p;

#ifdef _MT
        _lockexit();            /* lock the exit code */
#endif  /* _MT */

        /*
         * First, make sure the table has room for a new entry
         */
        if ( _msize_crt(__onexitbegin)
                < ((unsigned)((char *)__onexitend -
            (char *)__onexitbegin) + sizeof(_PVFV)) ) {
            /*
             * not enough room, try to grow the table
             */
            if ( (p = (_PVFV *) _realloc_crt(__onexitbegin,
                _msize_crt(__onexitbegin) +
                ONEXITTBLINCR * sizeof(_PVFV))) == NULL )
            {
                /*
                 * didn't work. don't do anything rash, just fail
                 */
#ifdef _MT
                _unlockexit();
#endif  /* _MT */

                return NULL;
            }

            /*
             * update __onexitend and __onexitbegin
             */
            __onexitend = p + (__onexitend - __onexitbegin);
            __onexitbegin = p;
        }

        /*
         * Put the new entry into the table and update the end-of-table
         * pointer.
         */
         *(__onexitend++) = (_PVFV)func;

#ifdef _MT
        _unlockexit();
#endif  /* _MT */

        return func;

}

int __cdecl atexit (
        _PVFV func
        )
{
        return (_onexit((_onexit_t)func) == NULL) ? -1 : 0;
}


/***
* void __onexitinit(void) - initialization routine for the function table
*       used by _onexit() and atexit().
*
*Purpose:
*       Allocate the table with room for 32 entries (minimum required by
*       ANSI). Also, initialize the pointers to the beginning and end of
*       the table.
*
*Entry:
*       None.
*
*Exit:
*       No return value. A fatal runtime error is generated if the table
*       cannot be allocated.
*
*Notes:
*       This routine depends on the behavior of doexit() in CRT0DAT.C.
*       Specifically, doexit() must not skip the address pointed to by
*       __onexitbegin, and it must also stop before the address pointed
*       to by __onexitend.  This is because _onexitbegin will point
*       to a valid address, and _onexitend will point at an invalid address.
*
*       Since the table of onexit routines is built in forward order, it
*       must be traversed by doexit() in CRT0DAT.C in reverse order.  This
*       is because these routines must be called in last-in, first-out order.
*
*       If __onexitbegin == __onexitend, then the onexit table is empty!
*
*Exceptions:
*
*******************************************************************************/

void __cdecl __onexitinit (
        void
        )
{
        if ( (__onexitbegin = (_PVFV *)_malloc_crt(32 * sizeof(_PVFV))) == NULL )
            /*
             * cannot allocate minimal required size. generate
             * fatal runtime error.
             */
            _amsg_exit(_RT_ONEXIT);

        *(__onexitbegin) = (_PVFV) NULL;
        __onexitend = __onexitbegin;
}


#ifdef CRTDLL

/***
*__dllonexit(func, pbegin, pend) - add function to be executed upon DLL detach
*
*Purpose:
*       The _onexit/atexit functions in a DLL linked with MSVCRT.LIB
*       must maintain their own atexit/_onexit list.  This routine is
*       the worker that gets called by such DLLs.  It is analogous to
*       the regular _onexit above except that the __onexitbegin and
*       __onexitend variables are not global variables visible to this
*       routine but rather must be passed as parameters.
*
*Entry:
*       void (*func)() - pointer to function to be executed upon exit
*       void (***pbegin)() - pointer to variable pointing to the beginning
*                   of list of functions to execute on detach
*       void (***pend)() - pointer to variable pointing to the end of list
*                   of functions to execute on detach
*
*Exit:
*       Success - return pointer to user's function.
*       Error - return NULL pointer.
*
*Notes:
*       This routine depends on the behavior of _initterm() in CRT0DAT.C.
*       Specifically, _initterm() must not skip the address pointed to by
*       its first parameter, and must also stop before the address pointed
*       to by its second parameter.  This is because *pbegin will point
*       to a valid address, and *pend will point at an invalid address.
*
*Exceptions:
*
*******************************************************************************/

_onexit_t __cdecl __dllonexit (
        _onexit_t func,
        _PVFV ** pbegin,
        _PVFV ** pend
        )
{
        _PVFV   *p;
        unsigned oldsize;

#ifdef _MT
        _lockexit();            /* lock the exit code */
#endif  /* _MT */

        /*
         * First, make sure the table has room for a new entry
         */
        if ( (oldsize = _msize_crt( *pbegin )) <= (unsigned)((char *)(*pend) -
            (char *)(*pbegin)) ) {
            /*
             * not enough room, try to grow the table
             */
            if ( (p = (_PVFV *) _realloc_crt((*pbegin), oldsize +
                ONEXITTBLINCR * sizeof(_PVFV))) == NULL )
            {
                /*
                 * didn't work. don't do anything rash, just fail
                 */
#ifdef _MT
                _unlockexit();
#endif  /* _MT */

                return NULL;
            }

            /*
             * update (*pend) and (*pbegin)
             */
            (*pend) = p + ((*pend) - (*pbegin));
            (*pbegin) = p;
        }

        /*
         * Put the new entry into the table and update the end-of-table
         * pointer.
         */
         *((*pend)++) = (_PVFV)func;

#ifdef _MT
        _unlockexit();
#endif  /* _MT */

        return func;

}

#endif  /* CRTDLL */

#else  /* _WIN32 */

#include <cruntime.h>
#include <mtdll.h>
#include <stdlib.h>
#include <internal.h>
#include <fltintrn.h>            //PFV definition
#include <malloc.h>
#include <rterr.h>
#include <dbgint.h>

/*
 * Define pointers to beginning and end of the table of function pointers
 * manipulated by _onexit()/atexit().
 */
extern PFV *__onexitbegin;
extern PFV *__onexitend;

/*
 * Define increment (in entries) for growing the _onexit/atexit table
 */
#define ONEXITTBLINCR   4


/***
*_onexit(func), atexit(func) - add function to be executed upon exit
*
*Purpose:
*       The _onexit/atexit functions are passed a pointer to a function
*       to be called when the program terminate normally.  Successive
*       calls create a register of functions that are executed last in,
*       first out.
*
*Entry:
*       void (*func)() - pointer to function to be executed upon exit
*
*Exit:
*       onexit:
*               Success - return pointer to user's function.
*               Error - return NULL pointer.
*       atexit:
*               Success - return 0.
*               Error - return non-zero value.
*
*Notes:
*       This routine depends on the behavior of _initterm() in CRT0DAT.C.
*       Specifically, _initterm() must not skip the address pointed to by
*       its first parameter, and must also stop before the address pointed
*       to by its second parameter.  This is because _onexitbegin will point
*       to a valid address, and _onexitend will point at an invalid address.
*
*Exceptions:
*
*******************************************************************************/


#ifndef CRTDLL
_onexit_t _cdecl _onexit (
#else  /* CRTDLL */
_onexit_t _cdecl __onexit (
#endif  /* CRTDLL */
        _onexit_t func
        )

{
        PFV     *p;

        /*
         * First, make sure the table has room for a new entry
         */
        if ( _msize_crt(__onexitbegin) <= (unsigned)((char *)__onexitend -
            (char *)__onexitbegin) ) {
            /*
             * not enough room, try to grow the table
             */
            if ( (p = (PFV *) _realloc_crt(__onexitbegin, _msize(__onexitbegin) +
                ONEXITTBLINCR * sizeof(PFV))) == NULL ) {
                /*
                 * didn't work. don't do anything rash, just fail
                 */
                return NULL;
            }

            /*
             * update __onexitend and __onexitbegin
             */
            __onexitend = p + (__onexitend - __onexitbegin);
            __onexitbegin = p;
        }

        /* push the table down one entry and insert new one at top since we
            need LIFO order */

        for (p = __onexitend++; p > __onexitbegin; p--) {
            *p = *(p-1);
        }
        *__onexitbegin = (PFV)func;
        return func;
}


#ifndef CRTDLL

int _CALLTYPE1 atexit (
        PFV func
        )
{
        return (_onexit((_onexit_t)func) == NULL) ? -1 : 0;
}

#endif  /* CRTDLL */

/***
* void _onexitinit(void) - initialization routine for the function table
*       used by _onexit() and _atexit().
*
*Purpose:
*       Allocate the table with room for 32 entries (minimum required by
*       ANSI). Also, initialize the pointers to the beginning and end of
*       the table.
*
*Entry:
*       None.
*
*Exit:
*       No return value. A fatal runtime error is generated if the table
*       cannot be allocated.
*
*Notes:
*       This routine depends on the behavior of _initterm() in CRT0DAT.C.
*       Specifically, _initterm() must not skip the address pointed to by
*       its first parameter, and must also stop before the address pointed
*       to by its second parameter.  This is because _onexitbegin will point
*       to a valid address, and _onexitend will point at an invalid address.
*
*Exceptions:
*
*******************************************************************************/


/*      define the entry in initializer table */


#pragma data_seg(".CRT$XIC")

static PFV __ponexitinit = _onexitinit;

#pragma data_seg()

void _CALLTYPE1 _onexitinit (
        void
        )
{
        if ( (__onexitbegin = (PFV *)_malloc_crt(32 * sizeof(PFV))) == NULL )
            /*
             * cannot allocate minimal required size. generate
             * fatal runtime error.
             */
            _amsg_exit(_RT_ONEXIT);

        *(__onexitbegin) = NULL;
        __onexitend = __onexitbegin;
}

#ifdef CRTDLL

/***
*__dllonexit(func, pbegin, pend) - add function to be executed upon DLL detach
*
*Purpose:
*       The _onexit/atexit functions in a DLL linked with MSVCRT.LIB
*       must maintain their own atexit/_onexit list.  This routine is
*       the worker that gets called by such DLLs.  It is analogous to
*       the regular _onexit above except that the __onexitbegin and
*       __onexitend variables are not global variables visible to this
*       routine but rather must be passed as parameters.
*
*Entry:
*       void (*func)() - pointer to function to be executed upon exit
*       void (***pbegin)() - pointer to variable pointing to the beginning
*                   of list of functions to execute on detach
*       void (***pend)() - pointer to variable pointing to the end of list
*                   of functions to execute on detach
*
*Exit:
*       Success - return pointer to user's function.
*       Error - return NULL pointer.
*
*Notes:
*       This routine depends on the behavior of _initterm() in CRT0DAT.C.
*       Specifically, _initterm() must not skip the address pointed to by
*       its first parameter, and must also stop before the address pointed
*       to by its second parameter.  This is because *pbegin will point
*       to a valid address, and *pend will point at an invalid address.
*
*Exceptions:
*
*******************************************************************************/

_onexit_t _cdecl __dllonexit (
        _onexit_t func,
        PFV ** pbegin,
        PFV ** pend
        )
{
        PFV   *p;
        unsigned oldsize;

        /*
         * First, make sure the table has room for a new entry
         */
        if ( (oldsize = _msize_crt( *pbegin )) <= (unsigned)((char *)(*pend) -
            (char *)(*pbegin)) ) {
            /*
             * not enough room, try to grow the table
             */
            if ( (p = (PFV *) _realloc_crt((*pbegin), oldsize +
                ONEXITTBLINCR * sizeof(PFV))) == NULL )
            {
                /*
                 * didn't work. don't do anything rash, just fail
                 */

                return NULL;
            }

            /*
             * update (*pend) and (*pbegin)
             */
            (*pend) = p + ((*pend) - (*pbegin));
            (*pbegin) = p;
        }

        /*
         * Put the new entry into the table and update the end-of-table
         * pointer.
         */

        *((*pend)++) = (PFV)func;
        return func;
}

#endif  /* CRTDLL */
#endif  /* _WIN32 */
