/***
*mktemp.c - create a unique file name
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _mktemp() - create a unique file name
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <stdio.h>
#include <io.h>
#include <process.h>
#include <errno.h>
#include <dbgint.h>
#include <stddef.h>
#ifdef _MBCS
#include <mbctype.h>
#include <mbdata.h>
#endif  /* _MBCS */
#include <tchar.h>

/***
*_TSCHAR *_mktemp(template) - create a unique file name
*
*Purpose:
*       given a template of the form "fnamXXXXXX", insert number on end
*       of template, insert unique letter if needed until unique filename
*       found or run out of letters.  The number is generated from the Win32
*       Process ID for single-thread libraries, or the Win32 Thread ID for
*       multi-thread libraries.
*
*Entry:
*       _TSCHAR *template - template of form "fnamXXXXXX"
*
*Exit:
*       return pointer to modifed template
*       returns NULL if template malformed or no more unique names
*
*Exceptions:
*
*******************************************************************************/

_TSCHAR * __cdecl _tmktemp (
        _TSCHAR *template
        )
{
        _TSCHAR *string = template;
        unsigned number;
        int letter = _T('a');
        int xcount = 0;
        int olderrno;

        _ASSERTE(template != NULL);
        _ASSERTE(*template != _T('\0'));

        /*
         * The Process ID is not a good choice in multi-threaded programs
         * because of the likelihood that two threads might call mktemp()
         * almost simultaneously, thus getting the same temporary name.
         * Instead, the Win32 Thread ID is used, because it is unique across
         * all threads in all processes currently running.
         *
         * Note, however, that unlike *NIX process IDs, which are not re-used
         * until all values up to 32K have been used, Win32 process IDs are
         * re-used and tend to always be relatively small numbers.  Same for
         * thread IDs.
         */
#ifdef _MT
        number = __threadid();
#else  /* _MT */
        number = _getpid();
#endif  /* _MT */

        while (*string)
                string++;

        /* replace last five X's */
#ifdef _MBCS
        while ((--string>=template) && (!_ismbstrail(template,string))
                && (*string == 'X') && xcount < 5)
#else  /* _MBCS */
        while (*--string == _T('X') && xcount < 5)
#endif  /* _MBCS */
        {
                xcount++;
                *string = (_TSCHAR)((number % 10) + '0');
                number /= 10;
        }

        /* too few X's ? */
        if (*string != _T('X') || xcount < 5)
                return(NULL);

        /* set first X */
        *string = letter++;

        olderrno = errno;       /* save current errno */
        errno = 0;              /* make sure errno isn't EACCESS */

        /* check all the files 'a'-'z' */
        while ((_taccess(template,0) == 0) || (errno == EACCES))
        /* while file exists */
        {
                errno = 0;
                if (letter == _T('z') + 1) {
                        errno = olderrno;
                        return(NULL);
                }

                *string = (_TSCHAR)letter++;
        }

        errno = olderrno;
        return(template);
}


#else  /* _MAC */


#include <cruntime.h>
#include <internal.h>
#include <stdio.h>
#include <io.h>
#include <errno.h>
#include <dbgint.h>
#include <stddef.h>
#include <macos\errors.h>
#include <macos\processe.h>
#include <macos\gestalte.h>
#include <macos\osutils.h>
#include <macos\traps.h>
#include <macos\toolutil.h>
#ifdef _MBCS
#include <mbctype.h>
#include <mbdata.h>
int __isdbcscode(const char *, const char *);     /* defined in fullpath.c */
#endif  /* _MBCS */

/***
*char *_mktemp(template) - create a unique file name
*
*Purpose:
*       given a template of the form "fnamXXXXXX", insert number on end
*       of template, insert unique letter if needed until unique filename
*       found or run out of letters
*
*Entry:
*       char *template - template of form "fnamXXXXXX"
*
*Exit:
*       return pointer to modifed template
*       returns NULL if template malformed or no more unique names
*
*Exceptions:
*
*******************************************************************************/


char * __cdecl _mktemp (
        char *template
        )
{
        char *string = template;
        unsigned number;
        int letter = 'a';
        int xcount = 0;
        int olderrno;
        ProcessSerialNumber psn;

        _ASSERTE(template != NULL);
        _ASSERTE(*template != '\0');

        if (__TrapFromGestalt(gestaltOSAttr, gestaltLaunchControl))
        {
                GetCurrentProcess(&psn);
                number = (unsigned) psn.lowLongOfPSN;
        }
        else
        {
                /*LATER -- how to get multifinder process id*/
                number = 1;
        }

        while (*string)
                string++;

#ifndef _MBCS
        while (*--string == 'X')
#else  /* _MBCS */
        while ((string>template) && (!__isdbcscode(template,string-1))
                && (*--string == 'X'))
#endif  /* _MBCS */
        {
                xcount++;
                *string = (char)((number % 10) + '0');
                number /= 10;
        }

        if (*++string == '\0' || xcount != 6 )
                return(NULL);

        olderrno = errno;       /* save current errno */
        errno = 0;              /* make sure errno isn't EACCESS */

        while ((_access(template,0) == 0) || (errno == EACCES))
        /* while file exists */
        {
                errno = 0;
                if (letter == 'z'+1) {
                        errno = olderrno;
                        return(NULL);
                }

                *string = (char)letter++;
        }

        errno = olderrno;
        return(template);
}


#endif  /* _MAC */
