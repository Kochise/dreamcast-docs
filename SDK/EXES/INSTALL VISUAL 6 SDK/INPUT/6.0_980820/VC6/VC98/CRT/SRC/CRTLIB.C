/***
*crtlib.c - CRT DLL initialization and termination routine (Win32, Dosx32)
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This module contains initialization entry point for the CRT DLL
*       in the Win32 environment. It also contains some of the supporting
*       initialization and termination code.
*
*******************************************************************************/

#ifdef CRTDLL

#include <cruntime.h>
#include <oscalls.h>
#include <dos.h>
#include <internal.h>
#include <malloc.h>
#include <mbctype.h>
#include <mtdll.h>
#include <process.h>
#include <rterr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <awint.h>
#include <tchar.h>
#include <time.h>
#include <dbgint.h>

/*
 * flag set iff _CRTDLL_INIT was called with DLL_PROCESS_ATTACH
 */
static int proc_attached = 0;

/*
 * command line, environment, and a few other globals
 */
wchar_t *_wcmdln = NULL;           /* points to wide command line */
char *_acmdln = NULL;              /* points to command line */

char *_aenvptr = NULL;      /* points to environment block */
wchar_t *_wenvptr = NULL;   /* points to wide environment block */

void (__cdecl * _aexit_rtn)(int) = _exit;   /* RT message return procedure */

extern int _newmode;    /* declared in <internal.h> */

int __error_mode = _OUT_TO_DEFAULT;

int __app_type = _UNKNOWN_APP;

static void __cdecl inherit(void);  /* local function */

/***
*void __[w]getmainargs - get values for args to main()
*
*Purpose:
*       This function invokes the command line parsing and copies the args
*       to main back through the passsed pointers. The reason for doing
*       this here, rather than having _CRTDLL_INIT do the work and exporting
*       the __argc and __argv, is to support the linked-in option to have
*       wildcard characters in filename arguments expanded.
*
*Entry:
*       int *pargc              - pointer to argc
*       _TCHAR ***pargv         - pointer to argv
*       _TCHAR ***penvp         - pointer to envp
*       int dowildcard          - flag (true means expand wildcards in cmd line)
*       _startupinfo * startinfo- other info to be passed to CRT DLL
*
*Exit:
*       No return value. Values for the arguments to main() are copied through
*       the passed pointers.
*
*******************************************************************************/


_CRTIMP void __cdecl __wgetmainargs (
        int *pargc,
        wchar_t ***pargv,
        wchar_t ***penvp,
        int dowildcard,
        _startupinfo * startinfo)
{

        /* set global new mode flag */
        _newmode = startinfo->newmode;

        if ( dowildcard )
            __wsetargv();   /* do wildcard expansion after parsing args */
        else
            _wsetargv();    /* NO wildcard expansion; just parse args */

        *pargc = __argc;
        *pargv = __wargv;

        /*
         * if wide environment does not already exist,
         * create it from multibyte environment
         */
        if (!_wenviron)
            __mbtow_environ();

        *penvp = _wenviron;
}



_CRTIMP void __cdecl __getmainargs (
        int *pargc,
        char ***pargv,
        char ***penvp,
        int dowildcard
        ,
        _startupinfo * startinfo
        )
{

        /* set global new mode flag */
        _newmode = startinfo->newmode;

        if ( dowildcard )
            __setargv();    /* do wildcard expansion after parsing args */
        else
            _setargv();     /* NO wildcard expansion; just parse args */

        *pargc = __argc;
        *pargv = __argv;
        *penvp = _environ;
}


/***
*BOOL _CRTDLL_INIT(hDllHandle, dwReason, lpreserved) - C DLL initialization.
*
*Purpose:
*       This routine does the C runtime initialization.
*
*Entry:
*
*Exit:
*
*******************************************************************************/

BOOL WINAPI _CRTDLL_INIT(
        HANDLE  hDllHandle,
        DWORD   dwReason,
        LPVOID  lpreserved
        )
{
        unsigned tmposver;

        if ( dwReason == DLL_PROCESS_ATTACH ) {

            /*
             * Get the full Win32 version. Stash it in a local variable
             * temporarily.
             */
            tmposver = GetVersion();

#ifdef _M_IX86

            /*
             * Make sure we are NOT running on Win32s
             */
            if ( ((tmposver & 0x00ff) == 3) && ((tmposver >> 31) & 1) ) {
                __crtMessageBoxA("MSVCRT.DLL for Win32\n\nError: MSVCRT.DLL is not compatible with Win32s.",
                         "Microsoft Visual C++ Runtime Library",
                         MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);
                return FALSE;
            }

#endif  /* _M_IX86 */


#ifdef _MT
            if ( !_heap_init(1) )   /* initialize heap */
#else  /* _MT */
            if ( !_heap_init(0) )   /* initialize heap */
#endif  /* _MT */
                /*
                 * The heap cannot be initialized, return failure to the
                 * loader.
                 */
                return FALSE;

            /*
             * Store OS version
             */
            _osver = tmposver;

            _winminor = (_osver >> 8) & 0x00FF ;
            _winmajor = _osver & 0x00FF ;
            _winver = (_winmajor << 8) + _winminor;
            _osver = (_osver >> 16) & 0x00FFFF ;

#ifdef _MT
            if(!_mtinit())          /* initialize multi-thread */
            {
                /*
                 * If the DLL load is going to fail, we must clean up
                 * all resources that have already been allocated.
                 */
                _heap_term();       /* heap is now invalid! */

                return FALSE;       /* fail DLL load on failure */
            }
#endif  /* _MT */

            _ioinit();          /* inherit file info */

            _aenvptr = (char *)__crtGetEnvironmentStringsA();

            _acmdln = (char *)GetCommandLineA();
            _wcmdln = (wchar_t *)__crtGetCommandLineW();

#ifdef _MBCS
            /*
             * Initialize multibyte ctype table. Always done since it is
             * needed for processing the environment strings.
             */
            __initmbctable();
#endif  /* _MBCS */

            /*
             * For CRT DLL, since we don't know the type (wide or multibyte)
             * of the program, we create only the multibyte type since that
             * is by far the most likely case. Wide environment will be created
             * on demand as usual.
             */

            _setenvp();             /* get environ info */

            _cinit();               /* do C data initialize */

            /*
             * Increment flag indicating process attach notification
             * has been received.
             */
            proc_attached++;

        }
        else if ( dwReason == DLL_PROCESS_DETACH ) {
                /*
                 * if a client process is detaching, make sure minimal
                 * runtime termination is performed and clean up our
                 * 'locks' (i.e., delete critical sections).
                 */
            if ( proc_attached > 0 ) {
                proc_attached--;

                /*
                 * Any basic clean-up done here may also need
                 * to be done below if Process Attach is partly
                 * processed and then a failure is encountered.
                 */

                if ( _C_Termination_Done == FALSE )
                    _c_exit();

#ifdef _DEBUG
                /* Dump all memory leaks */
                if (_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) & _CRTDBG_LEAK_CHECK_DF)
                {
                    _CrtSetDumpClient(NULL);
                    _CrtDumpMemoryLeaks();
                }
#endif  /* _DEBUG */

                /* Shut down lowio */
                _ioterm();
#ifdef _MT
                /* free TLS index, call _mtdeletelocks() */
                _mtterm();
#endif  /* _MT */

                /* This should be the last thing the C run-time does */
                _heap_term();   /* heap is now invalid! */

            }
            else
                /* no prior process attach, just return */
                return FALSE;

        }
        else if ( dwReason == DLL_THREAD_DETACH )
        {
            _freeptd(NULL);     /* free up per-thread CRT data */
        }

        return TRUE;
}

/***
*_amsg_exit(rterrnum) - Fast exit fatal errors
*
*Purpose:
*       Exit the program with error code of 255 and appropriate error
*       message.
*
*Entry:
*       int rterrnum - error message number (amsg_exit only).
*
*Exit:
*       Calls exit() (for integer divide-by-0) or _exit() indirectly
*       through _aexit_rtn [amsg_exit].
*       For multi-thread: calls _exit() function
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _amsg_exit (
        int rterrnum
        )
{

        if ( (__error_mode == _OUT_TO_STDERR) || ((__error_mode ==
               _OUT_TO_DEFAULT) && (__app_type == _CONSOLE_APP)) )
            _FF_MSGBANNER();    /* write run-time error banner */

        _NMSG_WRITE(rterrnum);      /* write message */
        _aexit_rtn(255);        /* normally _exit(255) */
}


#if defined (_M_IX86)

/*
 * Functions to access user-visible, per-process variables
 */

/*
 * Macro to construct the name of the access function from the variable
 * name.
 */
#define AFNAME(var) __p_ ## var

/*
 * Macro to construct the access function's return value from the variable
 * name.
 */
#define AFRET(var)  &var

/*
 ***
 ***  Template
 ***

_CRTIMP __cdecl
AFNAME() (void)
{
        return AFRET();
}

 ***
 ***
 ***
 */

#ifdef _DEBUG

_CRTIMP long *
AFNAME(_crtAssertBusy) (void)
{
        return AFRET(_crtAssertBusy);
}

_CRTIMP long *
AFNAME(_crtBreakAlloc) (void)
{
        return AFRET(_crtBreakAlloc);
}

_CRTIMP int *
AFNAME(_crtDbgFlag) (void)
{
        return AFRET(_crtDbgFlag);
}

#endif  /* _DEBUG */

_CRTIMP char ** __cdecl
AFNAME(_acmdln) (void)
{
        return AFRET(_acmdln);
}

_CRTIMP wchar_t ** __cdecl
AFNAME(_wcmdln) (void)
{
        return AFRET(_wcmdln);
}

_CRTIMP unsigned int * __cdecl
AFNAME(_amblksiz) (void)
{
        return AFRET(_amblksiz);
}

_CRTIMP int * __cdecl
AFNAME(__argc) (void)
{
        return AFRET(__argc);
}

_CRTIMP char *** __cdecl
AFNAME(__argv) (void)
{
        return AFRET(__argv);
}

_CRTIMP wchar_t *** __cdecl
AFNAME(__wargv) (void)
{
        return AFRET(__wargv);
}

_CRTIMP int * __cdecl
AFNAME(_commode) (void)
{
        return AFRET(_commode);
}

_CRTIMP int * __cdecl
AFNAME(_daylight) (void)
{
        return AFRET(_daylight);
}

_CRTIMP long * __cdecl
AFNAME(_dstbias) (void)
{
        return AFRET(_dstbias);
}

_CRTIMP char *** __cdecl
AFNAME(_environ) (void)
{
        return AFRET(_environ);
}

_CRTIMP wchar_t *** __cdecl
AFNAME(_wenviron) (void)
{
        return AFRET(_wenviron);
}

_CRTIMP int * __cdecl
AFNAME(_fmode) (void)
{
        return AFRET(_fmode);
}

_CRTIMP int * __cdecl
AFNAME(_fileinfo) (void)
{
        return AFRET(_fileinfo);
}

_CRTIMP char *** __cdecl
AFNAME(__initenv) (void)
{
        return AFRET(__initenv);
}

_CRTIMP wchar_t *** __cdecl
AFNAME(__winitenv) (void)
{
        return AFRET(__winitenv);
}

_CRTIMP FILE *
AFNAME(_iob) (void)
{
        return &_iob[0];
}

_CRTIMP unsigned char * __cdecl
AFNAME(_mbctype) (void)
{
        return &_mbctype[0];
}

_CRTIMP unsigned char * __cdecl
AFNAME(_mbcasemap) (void)
{
        return &_mbcasemap[0];
}

_CRTIMP int * __cdecl
AFNAME(__mb_cur_max) (void)
{
        return AFRET(__mb_cur_max);
}


_CRTIMP unsigned int * __cdecl
AFNAME(_osver) (void)
{
        return AFRET(_osver);
}

_CRTIMP unsigned short ** __cdecl
AFNAME(_pctype) (void)
{
        return AFRET(_pctype);
}

_CRTIMP unsigned short ** __cdecl
AFNAME(_pwctype) (void)
{
        return AFRET(_pwctype);
}

_CRTIMP char **  __cdecl
AFNAME(_pgmptr) (void)
{
        return AFRET(_pgmptr);
}

_CRTIMP wchar_t ** __cdecl
AFNAME(_wpgmptr) (void)
{
        return AFRET(_wpgmptr);
}

_CRTIMP long * __cdecl
AFNAME(_timezone) (void)
{
        return AFRET(_timezone);
}

_CRTIMP char ** __cdecl
AFNAME(_tzname) (void)
{
        return &_tzname[0];
}

_CRTIMP unsigned int * __cdecl
AFNAME(_winmajor) (void)
{
        return AFRET(_winmajor);
}

_CRTIMP unsigned int * __cdecl
AFNAME(_winminor) (void)
{
        return AFRET(_winminor);
}

_CRTIMP unsigned int * __cdecl
AFNAME(_winver) (void)
{
        return AFRET(_winver);
}

#endif  /* defined (_M_IX86) */

#endif  /* CRTDLL */
