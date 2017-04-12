/***
*makepath.c - create path name from components
*
*       Copyright (c) 1987-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       To provide support for creation of full path names from components
*
*******************************************************************************/

#include <cruntime.h>
#include <stdlib.h>
#ifdef _MBCS
#include <mbdata.h>
#include <mbstring.h>
#endif  /* _MBCS */
#include <tchar.h>

/***
*void _makepath() - build path name from components
*
*Purpose:
*       create a path name from its individual components
*
*Entry:
*       _TSCHAR *path  - pointer to buffer for constructed path
*       _TSCHAR *drive - pointer to drive component, may or may not contain
*                     trailing ':'
*       _TSCHAR *dir   - pointer to subdirectory component, may or may not include
*                     leading and/or trailing '/' or '\' characters
*       _TSCHAR *fname - pointer to file base name component
*       _TSCHAR *ext   - pointer to extension component, may or may not contain
*                     a leading '.'.
*
*Exit:
*       path - pointer to constructed path name
*
*Exceptions:
*
*******************************************************************************/

void __cdecl _tmakepath (
        register _TSCHAR *path,
        const _TSCHAR *drive,
        const _TSCHAR *dir,
        const _TSCHAR *fname,
        const _TSCHAR *ext
        )
{
        register const _TSCHAR *p;

        /* we assume that the arguments are in the following form (although we
         * do not diagnose invalid arguments or illegal filenames (such as
         * names longer than 8.3 or with illegal characters in them)
         *
         *  drive:
         *      A           ; or
         *      A:
         *  dir:
         *      \top\next\last\     ; or
         *      /top/next/last/     ; or
         *      either of the above forms with either/both the leading
         *      and trailing / or \ removed.  Mixed use of '/' and '\' is
         *      also tolerated
         *  fname:
         *      any valid file name
         *  ext:
         *      any valid extension (none if empty or null )
         */

        /* copy drive */

        if (drive && *drive) {
                *path++ = *drive;
                *path++ = _T(':');
        }

        /* copy dir */

        if ((p = dir) && *p) {
                do {
                        *path++ = *p++;
                }
                while (*p);
#ifdef _MBCS
                if (*(p=_mbsdec(dir,p)) != _T('/') && *p != _T('\\')) {
#else  /* _MBCS */
                if (*(p-1) != _T('/') && *(p-1) != _T('\\')) {
#endif  /* _MBCS */
                        *path++ = _T('\\');
                }
        }

        /* copy fname */

        if (p = fname) {
                while (*p) {
                        *path++ = *p++;
                }
        }

        /* copy ext, including 0-terminator - check to see if a '.' needs
         * to be inserted.
         */

        if (p = ext) {
                if (*p && *p != _T('.')) {
                        *path++ = _T('.');
                }
                while (*path++ = *p++)
                        ;
        }
        else {
                /* better add the 0-terminator */
                *path = _T('\0');
        }
}
