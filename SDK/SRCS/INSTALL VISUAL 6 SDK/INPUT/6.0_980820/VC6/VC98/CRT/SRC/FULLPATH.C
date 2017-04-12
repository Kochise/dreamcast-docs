/***
*fullpath.c -
*
*       Copyright (c) 1987-1997, Microsoft Corporation. All rights reserved.
*
*Purpose: contains the function _fullpath which makes an absolute path out
*       of a relative path. i.e.  ..\pop\..\main.c => c:\src\main.c if the
*       current directory is c:\src\src
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <stdio.h>
#include <direct.h>
#include <errno.h>
#include <stdlib.h>
#include <internal.h>
#include <tchar.h>
#include <windows.h>


/***
*_TSCHAR *_fullpath( _TSCHAR *buf, const _TSCHAR *path, maxlen );
*
*Purpose:
*
*       _fullpath - combines the current directory with path to form
*       an absolute path. i.e. _fullpath takes care of .\ and ..\
*       in the path.
*
*       The result is placed in buf. If the length of the result
*       is greater than maxlen NULL is returned, otherwise
*       the address of buf is returned.
*
*       If buf is NULL then a buffer is malloc'ed and maxlen is
*       ignored. If there are no errors then the address of this
*       buffer is returned.
*
*       If path specifies a drive, the curent directory of this
*       drive is combined with path. If the drive is not valid
*       and _fullpath needs the current directory of this drive
*       then NULL is returned.  If the current directory of this
*       non existant drive is not needed then a proper value is
*       returned.
*       For example:  path = "z:\\pop" does not need z:'s current
*       directory but path = "z:pop" does.
*
*
*
*Entry:
*       _TSCHAR *buf  - pointer to a buffer maintained by the user;
*       _TSCHAR *path - path to "add" to the current directory
*       int maxlen - length of the buffer pointed to by buf
*
*Exit:
*       Returns pointer to the buffer containing the absolute path
*       (same as buf if non-NULL; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/


_TSCHAR * __cdecl _tfullpath (
        _TSCHAR *UserBuf,
        const _TSCHAR *path,
        size_t maxlen
        )
{
        _TSCHAR *buf;
        _TSCHAR *pfname;
        unsigned long count;


        if ( !path || !*path )  /* no work to do */
            return( _tgetcwd( UserBuf, maxlen ) );

        /* allocate buffer if necessary */

        if ( !UserBuf )
            if ( !(buf = malloc(_MAX_PATH * sizeof(_TSCHAR))) ) {
                errno = ENOMEM;
                return( NULL );
            }
            else
                maxlen = _MAX_PATH;
        else
            buf = UserBuf;

        count = GetFullPathName ( path,
                                  maxlen,
                                  buf,
                                  &pfname );

        if ( count >= maxlen ) {
            if ( !UserBuf )
                free(buf);
            errno = ERANGE;
            return( NULL );
        }
        else if ( count == 0 ) {
            if ( !UserBuf )
                free(buf);
            _dosmaperr( GetLastError() );
            return( NULL );
        }

        return( buf );

}

#else  /* _MAC */

#include <cruntime.h>
#include <stdio.h>
#include <direct.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <internal.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>
#ifdef _MBCS
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>
int __cdecl isdbcscode (const char *, const char *);
#endif  /* _MBCS */


/***
*char *_fullpath( char *buf, const char *path, maxlen );
*
*Purpose:
*
*       _fullpath - combines the current directory with path to form
*       an absolute path. i.e. _fullpath takes care of ::
*       in the path.
*
*       The result is placed in buf. If the length of the result
*       is greater than maxlen NULL is returned, otherwise
*       the address of buf is returned.
*
*       If buf is NULL then a buffer is malloc'ed and maxlen is
*       ignored. If there are no errors then the address of this
*       buffer is returned.
*
*
*Entry:
*       char *buf  - pointer to a buffer maintained by the user;
*       char *path - path to "add" to the current directory
*       int maxlen - length of the buffer pointed to by buf
*
*Exit:
*       Returns pointer to the buffer containing the absolute path
*       (same as buf if non-NULL; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/

char * __cdecl _fullpath (
        char *UserBuf,
        const char *path,
        size_t maxlen
        )
{
        char    *buf;
        size_t   cbPath;

        if( !path || !*path )   /* no work to do */
            return( _getcwd( UserBuf, maxlen ) );

        if (UserBuf && (strlen(path) > maxlen))
            return NULL;

        /* allocate buffer if necessary */

        if( !UserBuf )
        {
            if( !(buf = malloc(_MAX_PATH)) )
            {
                 errno = ENOMEM;
                 return( NULL );
            }
            else
            {
                maxlen = _MAX_PATH;
            }
        }
        else
        {
            buf = UserBuf;
        }

        cbPath = strlen(path);
        if (cbPath > maxlen)
        {
            if (!UserBuf)
            {
                free(buf);
            }
            errno = ERANGE;
            return NULL;
        }

        maxlen = maxlen - cbPath;
        if (*path == ':')
        {
            maxlen++;        //this ":" is not counted
        }

        if ((*path == ':') ||
#ifndef _MBCS
            (strstr(path, ":") == NULL) )
#else  /* _MBCS */
            (_mbsstr(path, ":") == NULL) )
#endif  /* _MBCS */
        {
            //partial path
            if (_getcwd( buf, maxlen ) != NULL)
            {
                if (*path == ':')
                {
                    strcat(buf, path+1);
                }
                else
                {
                    strcat(buf, path);
                }
            }
            else
            {
                if (!UserBuf)
                {
                    free(buf);
                }
                return( NULL);
            }
        }
        else
        {
            //fullpath
            strcpy(buf, path);
        }

        return buf;

}


#ifdef _MBCS
/***
*       int isdbcscode( char *path, char *buf );
*
*Purpose:
*
*       isdbcscode - Check DBCS Code
*
*Entry:
*       char *path - full path
*       char *buf  - pointer to a buffer maintained by the user;
*
*Exit:
*       TRUE    : -1
*       FALSE   : 0
*
*Exceptions:
*
*******************************************************************************/

int __cdecl __isdbcscode(const char *path, const char *buf)
{
        while(path <= buf && *path++) {
            if(_ISLEADBYTE( *(path - 1) ) )
                if(path == buf)
                    return(-1);
                else
                    path++;
        }

        return 0;

}
#endif  /* _MBCS */

#endif  /* _MAC */

