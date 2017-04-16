/***
*fdopen.c - open a file descriptor as stream
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _fdopen() - opens a file descriptor as a stream, thus allowing
*       buffering, etc.
*
*******************************************************************************/

#include <cruntime.h>
#include <msdos.h>
#include <stdio.h>
#include <file2.h>
#include <dbgint.h>
#include <internal.h>
#include <mtdll.h>
#include <tchar.h>

/***
*FILE *_fdopen(filedes, mode) - open a file descriptor as a stream
*
*Purpose:
*       associates a stream with a file handle, thus allowing buffering, etc.
*       The mode must be specified and must be compatible with the mode
*       the file was opened with in the low level open.
*
*Entry:
*       int filedes - handle referring to open file
*       _TSCHAR *mode - file mode to use ("r", "w", "a", etc.)
*
*Exit:
*       returns stream pointer and sets FILE struct fields if successful
*       returns NULL if fails
*
*Exceptions:
*
*******************************************************************************/

FILE * __cdecl _tfdopen (
        int filedes,
        REG2 const _TSCHAR *mode
        )
{
        REG1 FILE *stream;
        int whileflag, tbflag, cnflag;

        _ASSERTE(mode != NULL);

#if defined (_WIN32)

        _ASSERTE((unsigned)filedes < (unsigned)_nhandle);
        _ASSERTE(_osfile(filedes) & FOPEN);

        if ( ((unsigned)filedes >= (unsigned)_nhandle) ||
             !(_osfile(filedes) & FOPEN) )
            return(NULL);

#else  /* defined (_WIN32) */


#if defined (_M_MPPC) || defined (_M_M68K)

        _ASSERTE((unsigned)filedes < (unsigned)_nfile);
        _ASSERTE(_osfile[filedes] & FOPEN);

        if ( ((unsigned)filedes >= (unsigned)_nfile) ||
             !(_osfile[filedes] & FOPEN) )
            return(NULL);

#endif  /* defined (_M_MPPC) || defined (_M_M68K) */


#endif  /* defined (_WIN32) */


        /* Find a free stream; stream is returned 'locked'. */

        if ((stream = _getstream()) == NULL)
            return(NULL);

        /* First character must be 'r', 'w', or 'a'. */

        switch (*mode) {
            case _T('r'):
                stream->_flag = _IOREAD;
                break;
            case _T('w'):
            case _T('a'):
                stream->_flag = _IOWRT;
                break;
            default:
                stream = NULL;  /* error */
                goto done;
                break;
        }

        /* There can be up to three more optional characters:
           (1) A single '+' character,
           (2) One of 'b' and 't' and
           (3) One of 'c' and 'n'.

           Note that currently, the 't' and 'b' flags are syntax checked
           but ignored.  'c' and 'n', however, are correctly supported.
        */

        whileflag=1;
        tbflag=cnflag=0;
        stream->_flag |= _commode;

        while(*++mode && whileflag)
            switch(*mode) {

                case _T('+'):
                    if (stream->_flag & _IORW)
                        whileflag=0;
                    else {
                        stream->_flag |= _IORW;
                        stream->_flag &= ~(_IOREAD | _IOWRT);
                    }
                    break;

                case _T('b'):
                case _T('t'):
                    if (tbflag)
                        whileflag=0;
                    else
                        tbflag=1;
                    break;

                case _T('c'):
                    if (cnflag)
                        whileflag = 0;
                    else {
                        cnflag = 1;
                        stream->_flag |= _IOCOMMIT;
                    }
                    break;

                case _T('n'):
                    if (cnflag)
                        whileflag = 0;
                    else {
                        cnflag = 1;
                        stream->_flag &= ~_IOCOMMIT;
                    }
                    break;

                default:
                    whileflag=0;
                    break;
            }

#ifndef CRTDLL
        _cflush++;  /* force library pre-termination procedure */
#endif  /* CRTDLL */

        stream->_file = filedes;

#if defined (_M_MPPC) || defined (_M_M68K)
        if ( ( ( _osfile[filedes] & FRDONLY ) && (stream->_flag & (_IORW | _IOWRT)) ) ||
            ( ( _osfile[filedes] & FWRONLY ) && (stream->_flag & (_IORW | _IOREAD)) ) )
        {
            stream->_flag = 0;   /* stream not used */
            return(NULL);
        }
#endif  /* defined (_M_MPPC) || defined (_M_M68K) */

/* Common return */

done:
        _unlock_str(stream);
        return(stream);
}
