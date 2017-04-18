/***
*crtexe.c - Initialization for client EXE using CRT DLL (Win32, Dosx32)
*
*       Copyright (c) 1991-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Set up call to client's main() or WinMain().
*
*******************************************************************************/

#ifndef _MAC

#ifdef CRTDLL

/*
 * SPECIAL BUILD MACROS! Note that crtexe.c (and crtexew.c) is linked in with
 * the client's code. It does not go into crtdll.dll! Therefore, it must be
 * built under the _DLL switch (like user code) and CRTDLL must be undefined.
 * The symbol SPECIAL_CRTEXE is turned on to suppress the normal CRT DLL
 * definition of _fmode and _commode using __declspec(dllexport).  Otherwise
 * this module would not be able to refer to both the local and DLL versions
 * of these two variables.
 */

#undef  CRTDLL
#define _DLL

#define SPECIAL_CRTEXE

#include <cruntime.h>
#include <oscalls.h>
#include <internal.h>

#include <math.h>
#include <rterr.h>
#include <stdlib.h>
#include <tchar.h>


/*
 * wWinMain is not yet defined in winbase.h. When it is, this should be
 * removed.
 */

int
WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nShowCmd
    );

#define SPACECHAR   _T(' ')
#define DQUOTECHAR  _T('\"')


#ifdef _M_IX86

/*
 * The local copy of the Pentium FDIV adjustment flag
 * and the address of the flag in MSVCRT*.DLL.
 */

extern int _adjust_fdiv;

extern int * _imp___adjust_fdiv;

#endif  /* _M_IX86 */


/* default floating point precision - X86 only! */

#ifdef _M_IX86
extern void _setdefaultprecision();
#endif  /* _M_IX86 */


/*
 * Declare function used to install a user-supplied _matherr routine.
 */
_CRTIMP void __setusermatherr( int (__cdecl *)(struct _exception *) );


/*
 * Declare the names of the exports corresponding to _fmode and _commode
 */

#ifdef _M_IX86

#define _IMP___FMODE    (__p__fmode())
#define _IMP___COMMODE  (__p__commode())

#else  /* _M_IX86 */

/* assumed to be MIPS or Alpha */

#define _IMP___FMODE    __imp__fmode
#define _IMP___COMMODE  __imp__commode

#endif  /* _M_IX86 */


#if !defined (_M_IX86)
extern int * _IMP___FMODE;      /* exported from the CRT DLL */
extern int * _IMP___COMMODE;    /* these names are implementation-specific */
#endif  /* !defined (_M_IX86) */

extern int _fmode;          /* must match the definition in <stdlib.h> */
extern int _commode;        /* must match the definition in <internal.h> */

extern int _dowildcard;     /* passed to __getmainargs() */

/*
 * Declare/define communal that serves as indicator the default matherr
 * routine is being used.
 */
int __defaultmatherr;

/*
 * routine in DLL to do initialization (in this case, C++ constructors)
 */
extern void __cdecl _initterm(_PVFV *, _PVFV *);

/*
 * pointers to initialization sections
 */
extern _PVFV __xi_a[], __xi_z[];    /* C++ initializers */
extern _PVFV __xc_a[], __xc_z[];    /* C++ initializers */


/*
 * Pointers to beginning and end of the table of function pointers manipulated
 * by _onexit()/atexit().  The atexit/_onexit code is shared for both EXE's and
 * DLL's but different behavior is required.  These values are set to -1 to
 * mark this module as an EXE.
 */

extern _PVFV *__onexitbegin;
extern _PVFV *__onexitend;


/***
*void mainCRTStartup(void)
*
*Purpose:
*       This routine does the C runtime initialization, calls main(), and
*       then exits.  It never returns.
*
*Entry:
*
*Exit:
*
*******************************************************************************/

#ifdef _WINMAIN_

#ifdef WPRFLAG
void wWinMainCRTStartup(
#else  /* WPRFLAG */
void WinMainCRTStartup(
#endif  /* WPRFLAG */

#else  /* _WINMAIN_ */

#ifdef WPRFLAG
void wmainCRTStartup(
#else  /* WPRFLAG */
void mainCRTStartup(
#endif  /* WPRFLAG */

#endif  /* _WINMAIN_ */
        void
        )
{
        int argc;   /* three standard arguments to main */
        _TSCHAR **argv;
        _TSCHAR **envp;

        int mainret;

#ifdef _WINMAIN_
        _TUCHAR *lpszCommandLine;
        STARTUPINFO StartupInfo;
#endif  /* _WINMAIN_ */

        _startupinfo    startinfo;

        /*
         * Guard the initialization code and the call to user's main, or
         * WinMain, function in a __try/__except statement.
         */

        __try {
            /*
             * Set __app_type properly
             */
#ifdef _WINMAIN_
            __set_app_type(_GUI_APP);
#else  /* _WINMAIN_ */
            __set_app_type(_CONSOLE_APP);
#endif  /* _WINMAIN_ */

            /*
             * Mark this module as an EXE file so that atexit/_onexit
             * will do the right thing when called, including for C++
             * d-tors.
             */
            __onexitbegin = __onexitend = (_PVFV *)(-1);

            /*
             * Propogate the _fmode and _commode variables to the DLL
             */
            *_IMP___FMODE = _fmode;
            *_IMP___COMMODE = _commode;

#ifdef _M_IX86
            /*
             * Set the local copy of the Pentium FDIV adjustment flag
             */

            _adjust_fdiv = * _imp___adjust_fdiv;
#endif  /* _M_IX86 */

            /*
             * Call _setargv(), which will call the __setargv() in this
             * module if SETARGV.OBJ is linked with the EXE.  If
             * SETARGV.OBJ is not linked with the EXE, a _dummy setargv()
             * will be called.
             */
#ifdef WPRFLAG
            _wsetargv();
#else  /* WPRFLAG */
            _setargv();
#endif  /* WPRFLAG */

            /*
             * If the user has supplied a _matherr routine then set
             * __pusermatherr to point to it.
             */
            if ( !__defaultmatherr )
                __setusermatherr(_matherr);

#ifdef _M_IX86
            _setdefaultprecision();
#endif  /* _M_IX86 */

            /*
             * Do runtime startup initializers.
             */
            _initterm( __xi_a, __xi_z );


            /*
             * Get the arguments for the call to main. Note this must be
             * done explicitly, rather than as part of the dll's
             * initialization, to implement optional expansion of wild
             * card chars in filename args
             */

#ifdef WPRFLAG
            startinfo.newmode = _newmode;

            __wgetmainargs(&argc, &argv, &envp, _dowildcard, &startinfo);
#else  /* WPRFLAG */
            startinfo.newmode = _newmode;

            __getmainargs(&argc, &argv, &envp, _dowildcard, &startinfo);
#endif  /* WPRFLAG */

            /*
             * do C++ constructors (initializers) specific to this EXE
             */
            _initterm( __xc_a, __xc_z );

#ifdef _WINMAIN_
            /*
             * Skip past program name (first token in command line).
             * Check for and handle quoted program name.
                 */
#ifdef WPRFLAG
            /* OS may not support "W" flavors */
            if (_wcmdln == NULL)
                return;
            lpszCommandLine = (wchar_t *)_wcmdln;
#else  /* WPRFLAG */
            lpszCommandLine = (unsigned char *)_acmdln;
#endif  /* WPRFLAG */

            if ( *lpszCommandLine == DQUOTECHAR ) {
                /*
                 * Scan, and skip over, subsequent characters until
                 * another double-quote or a null is encountered.
                 */
                while ( *++lpszCommandLine && (*lpszCommandLine
                        != DQUOTECHAR) );
                /*
                 * If we stopped on a double-quote (usual case), skip
                 * over it.
                 */
                if ( *lpszCommandLine == DQUOTECHAR )
                    lpszCommandLine++;
            }
            else {
                while (*lpszCommandLine > SPACECHAR)
                    lpszCommandLine++;
            }

            /*
             * Skip past any white space preceeding the second token.
             */
            while (*lpszCommandLine && (*lpszCommandLine <= SPACECHAR)) {
                lpszCommandLine++;
            }

            StartupInfo.dwFlags = 0;
            GetStartupInfo( &StartupInfo );

#ifdef WPRFLAG
            mainret = wWinMain(
#else  /* WPRFLAG */
            mainret = WinMain(
#endif  /* WPRFLAG */
                       GetModuleHandle(NULL),
                       NULL,
                       lpszCommandLine,
                       StartupInfo.dwFlags & STARTF_USESHOWWINDOW
                        ? StartupInfo.wShowWindow
                        : SW_SHOWDEFAULT
                      );
#else  /* _WINMAIN_ */

#ifdef WPRFLAG
            __winitenv = envp;
            mainret = wmain(argc, argv, envp);
#else  /* WPRFLAG */
            __initenv = envp;
            mainret = main(argc, argv, envp);
#endif  /* WPRFLAG */

#endif  /* _WINMAIN_ */

            exit(mainret);
        }
        __except ( _XcptFilter(GetExceptionCode(), GetExceptionInformation()) )
        {
            /*
             * Should never reach here
             */
            _exit( GetExceptionCode() );

        } /* end of try - except */

}


#endif  /* CRTDLL */

#else  /* _MAC */

#include <cruntime.h>
#include <internal.h>
#include <stdlib.h>
#include <fltintrn.h>
#include <dbgint.h>

/*
 * routine in DLL to do initialization (in this case, C++ constructors)
 */
extern void __cdecl _initterm(PFV *, PFV *);
extern void __cdecl _DoExitSpecial(int, int, PFV *, PFV *, PFV *, PFV *, PFV *, PFV *);
static char * __cdecl _p2cstr_internal ( unsigned char * str );
static void * memcpy_internal ( void * dst, const void * src,   size_t count);
int __cdecl main(int, char **, char **);             /*generated by compiler*/
void _TestExit(int);

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

extern PFV *__onexitbegin;
extern PFV *__onexitend;

/*this globals are defined in DLL */
extern int __argc;

extern char **__argv;
/***
*void mainCRTStartup(void)
*
*Purpose:
*       This routine does the C runtime initialization, calls main(), and
*       then exits.  It never returns.
*
*Entry:
*
*Exit:
*
*******************************************************************************/

void mainCRTStartup(
        void
        )
{
        int argc = 1;   /* three standard arguments to main */
        char *argv[2];
        char **environ = NULL;
        int mainret;
        char szPgmName[32];
        char *pArg;
        extern unsigned int dwSPStartup;
        extern  void * GetSP(void);

        dwSPStartup = (unsigned int)GetSP();
        memcpy_internal(szPgmName, (char *)0x910, sizeof(szPgmName));
        pArg = _p2cstr_internal(szPgmName);
        argv[0] = pArg;
        argv[1] = NULL;

        __argc = 1;
        __argv = argv;

        /*
         * Mark this module as an EXE file so that atexit/_onexit
         * will do the right thing when called, including for C++
         * d-tors.
         */
        __onexitbegin = __onexitend = (_PVFV *)(-1);

        /*
         * Do runtime startup initializers.
         */
        _initterm( &__xi_a, &__xi_z );

        /*
         * do C++ constructors (initializers) specific to this EXE
         */
        _initterm( &__xc_a, &__xc_z );

        mainret = main(argc, argv, environ);

        //strictly testing hook
        _TestExit(mainret);

        /*
         * This will do special term for the App in the right order
         */
        _DoExitSpecial( mainret,
                        0,
                        &__xp_a,
                        &__xp_z,
                        &__xt_a,
                        &__xt_z,
                        __onexitbegin,
                        __onexitend );
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
