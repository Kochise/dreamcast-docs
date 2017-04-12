/***
*crt0msg.c - startup error messages
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Prints out banner for runtime error messages.
*
*******************************************************************************/

#include <cruntime.h>
#include <internal.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <rterr.h>
#include <cmsgs.h>
#include <awint.h>
#ifdef _MAC
#include <io.h>
#else  /* _MAC */
#include <windows.h>
#endif  /* _MAC */

#include <dbgint.h>


/* struct used to lookup and access runtime error messages */

struct rterrmsgs {
        int rterrno;        /* error number */
        char *rterrtxt;     /* text of error message */
};

/* runtime error messages */

static struct rterrmsgs rterrs[] = {

#ifdef _MAC
        /* 0 */
        { _RT_STACK, _RT_STACK_TXT },
#endif  /* _MAC */

        /* 2 */
        { _RT_FLOAT, _RT_FLOAT_TXT },

#ifdef _MAC
        /* 3 */
        { _RT_INTDIV, _RT_INTDIV_TXT },
#endif  /* _MAC */

#ifdef _WIN32
        /* 8 */
        { _RT_SPACEARG, _RT_SPACEARG_TXT },

        /* 9 */
        { _RT_SPACEENV, _RT_SPACEENV_TXT },
#endif  /* _WIN32 */

        /* 10 */
        { _RT_ABORT, _RT_ABORT_TXT },

#ifdef _WIN32
        /* 16 */
        { _RT_THREAD, _RT_THREAD_TXT },

        /* 17 */
        { _RT_LOCK, _RT_LOCK_TXT },
#endif  /* _WIN32 */

        /* 18 */
        { _RT_HEAP, _RT_HEAP_TXT },

#ifdef _WIN32
        /* 19 */
        { _RT_OPENCON, _RT_OPENCON_TXT },
#endif  /* _WIN32 */

        /* 22 */
        /* { _RT_NONCONT, _RT_NONCONT_TXT }, */

        /* 23 */
        /* { _RT_INVALDISP, _RT_INVALDISP_TXT }, */

#ifdef _WIN32
        /* 24 */
        { _RT_ONEXIT, _RT_ONEXIT_TXT },
#endif  /* _WIN32 */

        /* 25 */
        { _RT_PUREVIRT, _RT_PUREVIRT_TXT },

#ifdef _WIN32
        /* 26 */
        { _RT_STDIOINIT, _RT_STDIOINIT_TXT },

        /* 27 */
        { _RT_LOWIOINIT, _RT_LOWIOINIT_TXT },

        /* 28 */
        { _RT_HEAPINIT, _RT_HEAPINIT_TXT },
#endif  /* _WIN32 */

        /* 120 */
        { _RT_DOMAIN, _RT_DOMAIN_TXT },

        /* 121 */
        { _RT_SING, _RT_SING_TXT },

        /* 122 */
        { _RT_TLOSS, _RT_TLOSS_TXT },

        /* 252 */
        { _RT_CRNL, _RT_CRNL_TXT },

        /* 255 */
        { _RT_BANNER, _RT_BANNER_TXT }

};

/* number of elements in rterrs[] */

#define _RTERRCNT   ( sizeof(rterrs) / sizeof(struct rterrmsgs) )

/* For C, _FF_DBGMSG is inactive, so _adbgmsg is
   set to null
   For FORTRAN, _adbgmsg is set to point to
   _FF_DBGMSG in dbginit initializer in dbgmsg.asm  */

void (*_adbgmsg)(void) = NULL;

/***
*_FF_MSGBANNER - writes out first part of run-time error messages
*
*Purpose:
*       This routine writes "\r\nrun-time error " to standard error.
*
*       For FORTRAN $DEBUG error messages, it also uses the _FF_DBGMSG
*       routine whose address is stored in the _adbgmsg variable to print out
*       file and line number information associated with the run-time error.
*       If the value of _adbgmsg is found to be null, then the _FF_DBGMSG
*       routine won't be called from here (the case for C-only programs).
*
*Entry:
*       No arguments.
*
*Exit:
*       Nothing returned.
*
*Exceptions:
*       None handled.
*
*******************************************************************************/

void __cdecl _FF_MSGBANNER (
        void
        )
{

#ifdef _WIN32
        if ( (__error_mode == _OUT_TO_STDERR) || ((__error_mode ==
               _OUT_TO_DEFAULT) && (__app_type == _CONSOLE_APP)) )
#endif  /* _WIN32 */
        {
            _NMSG_WRITE(_RT_CRNL);  /* new line to begin error message */
            if (_adbgmsg != 0)
                _adbgmsg(); /* call __FF_DBGMSG for FORTRAN */
            _NMSG_WRITE(_RT_BANNER); /* run-time error message banner */
        }
}


/***
*__NMSGWRITE(message) - write a given message to handle 2 (stderr)
*
*Purpose:
*       This routine writes the message associated with rterrnum
*       to stderr.
*
*Entry:
*       int rterrnum - runtime error number
*
*Exit:
*       no return value
*
*Exceptions:
*       none
*
*******************************************************************************/

void __cdecl _NMSG_WRITE (
        int rterrnum
        )
{
        int tblindx;
#if defined (_WIN32)
        DWORD bytes_written;            /* bytes written */
#endif  /* defined (_WIN32) */

        for ( tblindx = 0 ; tblindx < _RTERRCNT ; tblindx++ )
            if ( rterrnum == rterrs[tblindx].rterrno )
                break;

        if ( rterrnum == rterrs[tblindx].rterrno )
        {
#ifdef _DEBUG
            /*
             * Report error.
             *
             * If _CRT_ERROR has _CRTDBG_REPORT_WNDW on, and user chooses
             * "Retry", call the debugger.
             *
             * Otherwise, continue execution.
             *
             */

            if (rterrnum != _RT_CRNL)
            {
                if (1 == _CrtDbgReport(_CRT_ERROR, NULL, 0, NULL, rterrs[tblindx].rterrtxt))
                    _CrtDbgBreak();
            }
#endif  /* _DEBUG */

#if defined (_WIN32)
            if ( (__error_mode == _OUT_TO_STDERR) || ((__error_mode ==
                   _OUT_TO_DEFAULT) && (__app_type == _CONSOLE_APP)) )
            {
                WriteFile( GetStdHandle(STD_ERROR_HANDLE),
                           rterrs[tblindx].rterrtxt,
                           strlen(rterrs[tblindx].rterrtxt),
                           &bytes_written,
                           NULL );
            }
            else if (rterrnum != _RT_CRNL)
            {
                #define MAXLINELEN 60
                char * pch;
                char progname[MAX_PATH];
                char outmsg[MAXLINELEN+100];

                if (!GetModuleFileName(NULL, progname, MAX_PATH))
                    strcpy(progname, "<program name unknown>");

                pch = (char *)progname;

                if (strlen(pch) + 1 > MAXLINELEN)
                {
                    pch += strlen(progname) + 1 - MAXLINELEN;
                    strncpy(pch, "...", 3);
                }

                strcpy(outmsg, "Runtime Error!\n\nProgram: ");
                strcat(outmsg, pch);
                strcat(outmsg, "\n\n");
                strcat(outmsg, rterrs[tblindx].rterrtxt);

                __crtMessageBoxA(outmsg,
                        "Microsoft Visual C++ Runtime Library",
                        MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);
            }

#else  /* defined (_WIN32) */

#if defined (_M_M68K) || defined (_M_MPPC)
#if defined (_M_M68K) || defined (_M_MPPC)
            _write(2, rterrs[tblindx].rterrtxt,
#else  /* defined (_M_M68K) || defined (_M_MPPC) */
            write(STDERR_FILENO,rterrs[tblindx].rterrtxt,
#endif  /* defined (_M_M68K) || defined (_M_MPPC) */
            strlen(rterrs[tblindx].rterrtxt));
#else  /* defined (_M_M68K) || defined (_M_MPPC) */

#error ERROR - ONLY WIN32 OR POSIX OR MAC TARGET SUPPORTED!

#endif  /* defined (_M_M68K) || defined (_M_MPPC) */

#endif  /* defined (_WIN32) */

        }
}


#ifdef _WIN32

/***
*_GET_RTERRMSG(message) - returns ptr to error text for given runtime error
*
*Purpose:
*       This routine returns the message associated with rterrnum
*
*Entry:
*       int rterrnum - runtime error number
*
*Exit:
*       no return value
*
*Exceptions:
*       none
*
*******************************************************************************/

char * __cdecl _GET_RTERRMSG (
        int rterrnum
        )
{
        int tblindx;

        for ( tblindx = 0 ; tblindx < _RTERRCNT ; tblindx++ )
            if ( rterrnum == rterrs[tblindx].rterrno )
                break;

        if ( rterrnum == rterrs[tblindx].rterrno )
            return rterrs[tblindx].rterrtxt;
        else
            return NULL;
}
#endif  /* _WIN32 */
