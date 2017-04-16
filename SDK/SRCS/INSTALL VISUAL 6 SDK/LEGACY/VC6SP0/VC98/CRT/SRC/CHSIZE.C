/***
*chsize.c - change size of a file
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       contains the _chsize() function - changes the size of a file.
*
*******************************************************************************/

#include <cruntime.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <dbgint.h>
#include <fcntl.h>
#include <msdos.h>
#include <io.h>
#include <string.h>

#ifndef _MAC
#include <windows.h>
#endif  /* _MAC */

#include <internal.h>
#include <mtdll.h>

#ifdef _MAC
#include <memory.h>
#include <macos\errors.h>
#include <macos\types.h>
#include <macos\files.h>
#endif  /* _MAC */

/***
*int _chsize(filedes, size) - change size of a file
*
*Purpose:
*       Change file size. Assume file is open for writing, or we can't do it.
*       The DOS way to do this is to go to the right spot and write 0 bytes. The
*       Xenix way to do this is to make a system call. We write '\0' bytes because
*       DOS won't do this for you if you lseek beyond eof, though Xenix will.
*
*Entry:
*       int filedes - file handle to change size of
*       long size - new size of file
*
*Exit:
*       return 0 if successful
*       returns -1 and sets errno if fails
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

/* define normal version that locks/unlocks, validates fh */

int __cdecl _chsize (
        REG1 int filedes,
        long size
        )
{
        int r;                          /* return value */

#ifndef _MAC
        if ( ((unsigned)filedes >= (unsigned)_nhandle) ||
             !(_osfile(filedes) & FOPEN) )
#else  /* _MAC */
        if ( filedes < 0 || filedes >= _nfile )
#endif  /* _MAC */
        {
                errno = EBADF;
                return(-1);
        }
        _lock_fh(filedes);
        r = _chsize_lk(filedes,size);
        _unlock_fh(filedes);

        return r;
}

/* now define version that doesn't lock/unlock, validate fh */
int __cdecl _chsize_lk (
        REG1 int filedes,
        long size
        )
{
        long filend;
        long extend;
        long place;
        int cnt;
        char blanks[_INTERNAL_BUFSIZ];
        REG2 char *bl = blanks;
        int oldmode;
        int retval = 0; /* assume good return */

#else  /* _MT */

/* now define normal version */

int __cdecl _chsize (
        REG1 int filedes,
        long size
        )
{
        long filend;
        long extend;
        long place;
        int cnt;
        char blanks[_INTERNAL_BUFSIZ];
        REG2 char *bl = blanks;
        int oldmode;
        int retval = 0; /* assume good return */

#ifndef _MAC
        if ( ((unsigned)filedes >= (unsigned)_nhandle) ||
             !(_osfile(filedes) & FOPEN) )
#else  /* _MAC */
        if ( filedes < 0 || filedes >= _nfile )
#endif  /* _MAC */
        {
            errno = EBADF;
            return(-1);
        }

#endif  /* _MT */
        _ASSERTE(size >= 0);

        /* Get current file position and seek to end */
        if ( ((place = _lseek_lk(filedes, 0L, SEEK_CUR)) == -1L) ||
             ((filend = _lseek_lk(filedes, 0L, SEEK_END)) == -1L) )
            return -1;

        extend = size - filend;

        /* Grow or shrink the file as necessary */

        if (extend > 0L) {

            /* extending the file */

            memset(bl, '\0', _INTERNAL_BUFSIZ);
            oldmode = _setmode_lk(filedes, _O_BINARY);

            /* pad out with nulls */
            do  {
                cnt = (extend >= (long)_INTERNAL_BUFSIZ ) ?
                      _INTERNAL_BUFSIZ : (int)extend;
                if ( (cnt = _write_lk( filedes,
                                       bl,
                                       (extend >= (long)_INTERNAL_BUFSIZ) ?
                                            _INTERNAL_BUFSIZ : (int)extend ))
                     == -1 )
                {
#ifndef _MAC
                    /* Error on write */
                    if (_doserrno == ERROR_ACCESS_DENIED)
                        errno = EACCES;
#endif  /* _MAC */
                    retval = cnt;
                    break;  /* leave write loop */
                }
            }
            while ((extend -= (long)cnt) > 0L);

            _setmode_lk(filedes, oldmode);
            /* retval set correctly */
        }

        else  if ( extend < 0L ) {
            /* shortening the file */

#ifndef _MAC
            /*
             * Set file pointer to new eof...and truncate it there.
             */
            _lseek_lk(filedes, size, SEEK_SET);

            if ( (retval = SetEndOfFile((HANDLE)_get_osfhandle(filedes)) ?
                 0 : -1) == -1 )
            {
                errno = EACCES;
                _doserrno = GetLastError();
            }
#endif  /* _MAC */

#ifdef _MAC
            {
            ParamBlockRec parm;
            OSErr osErr;

            parm.ioParam.ioRefNum = _osfhnd[filedes];
            parm.ioParam.ioMisc = (char *)size;
            osErr = PBSetEOFSync(&parm);
            if (osErr)
            {
                _dosmaperr(osErr);
                retval = -1;
            }
            else
            {
                retval = 0;
            }
            }
#endif  /* _MAC */

        }

        /* else */
        /* no file change needed */
        /* retval = 0; */


/* Common return code */

        _lseek_lk(filedes, place, SEEK_SET);
        return retval;
}
