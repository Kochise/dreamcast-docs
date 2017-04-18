/***
*execvpe.c - execute a file with given environ; search along PATH
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _execvpe() - execute a file with given environ
*
*******************************************************************************/

#include <cruntime.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <mbstring.h>
#include <tchar.h>
#include <dbgint.h>

#define SLASHCHAR _T('\\')
#define XSLASHCHAR _T('/')

#define SLASH _T("\\")
#define DELIMITER _T(";")

#ifdef _MBCS
/* note, the macro below assumes p is to pointer to a single-byte character
 * or the 1st byte of a double-byte character, in a string.
 */
#define ISPSLASH(p)     ( ((p) == _mbschr((p), SLASHCHAR)) || ((p) == \
_mbschr((p), XSLASHCHAR)) )
#else  /* _MBCS */
#define ISSLASH(c)      ( ((c) == SLASHCHAR) || ((c) == XSLASHCHAR) )
#endif  /* _MBCS */


/***
*int _execvpe(filename, argvector, envvector) - execute a file
*
*Purpose:
*       Executes a file with given arguments and environment.
*       try to execute the file. start with the name itself (directory '.'),
*       and if that doesn't work start prepending pathnames from the
*       environment until one works or we run out. if the file is a pathname,
*       don't go to the environment to get alternate paths. If a needed text
*       file is busy, wait a little while and try again before despairing
*       completely
*
*Entry:
*       _TSCHAR *filename        - file to execute
*       _TSCHAR **argvector - vector of arguments
*       _TSCHAR **envvector - vector of environment variables
*
*Exit:
*       destroys the calling process (hopefully)
*       if fails, returns -1
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _texecvpe (
        REG3 const _TSCHAR *filename,
        const _TSCHAR * const *argvector,
        const _TSCHAR * const *envptr
        )
{
        REG1 _TSCHAR *env;
        _TSCHAR *bbuf = NULL;
        REG2 _TSCHAR *buf;
        _TSCHAR *pfin;

        _ASSERTE(filename != NULL);
        _ASSERTE(*filename != _T('\0'));
        _ASSERTE(argvector != NULL);
        _ASSERTE(*argvector != NULL);
        _ASSERTE(**argvector != _T('\0'));

        _texecve(filename,argvector,envptr);

        if ( (errno != ENOENT)
        || (_tcschr(filename, SLASHCHAR) != NULL)
        || (_tcschr(filename, XSLASHCHAR) != NULL)
        || *filename && *(filename+1) == _T(':')
        || !(env=_tgetenv(_T("PATH"))) )
                goto reterror;

        /* allocate a buffer to hold alternate pathnames for the executable
         */
        if ( (buf = bbuf = _malloc_crt(_MAX_PATH * sizeof(_TSCHAR))) == NULL )
            goto reterror;

        do {
                /* copy a component into bbuf[], taking care not to overflow it
                 */
                /* UNDONE: make sure ';' isn't 2nd byte of DBCS char */
                while ( (*env) && (*env != _T(';')) && (buf < bbuf+(_MAX_PATH-2)*sizeof(_TSCHAR)) )
                        *buf++ = *env++;

                *buf = _T('\0');
                pfin = --buf;
                buf = bbuf;

#ifdef _MBCS
                if (*pfin == SLASHCHAR) {
                        if (pfin != _mbsrchr(buf,SLASHCHAR))
                                /* *pfin is the second byte of a double-byte
                                 * character
                                 */
                                strcat( buf, SLASH );
                }
                else if (*pfin != XSLASHCHAR)
                        strcat(buf, SLASH);
#else  /* _MBCS */
                if (*pfin != SLASHCHAR && *pfin != XSLASHCHAR)
                        _tcscat(buf, SLASH);
#endif  /* _MBCS */

                /* check that the final path will be of legal size. if so,
                 * build it. otherwise, return to the caller (return value
                 * and errno rename set from initial call to _execve()).
                 */
                if ( (_tcslen(buf) + _tcslen(filename)) < _MAX_PATH )
                        _tcscat(buf, filename);
                else
                        break;

                _texecve(buf, argvector, envptr);

                if ( (errno != ENOENT)
#ifdef _MBCS
                && (!ISPSLASH(buf) || !ISPSLASH(buf+1)) )
#else  /* _MBCS */
                && (!ISSLASH(*buf) || !ISSLASH(*(buf+1))) )
#endif  /* _MBCS */
                        break;
        } while ( *env && env++ );

reterror:
        if (bbuf != NULL)
                _free_crt(bbuf);

        return(-1);
}
