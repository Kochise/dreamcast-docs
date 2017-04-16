/***
*setmode.c - set file translation mode
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defined _setmode() - set file translation mode of a file
*
*******************************************************************************/

#include <cruntime.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>
#include <msdos.h>
#include <mtdll.h>
#include <stddef.h>
#include <internal.h>

/***
*int _setmode(fh, mode) - set file translation mode
*
*Purpose:
*       changes file mode to text/binary, depending on mode arg. this affects
*       whether read's and write's on the file translate between CRLF and LF
*       or is untranslated
*
*Entry:
*       int fh - file handle to change mode on
*       int mode - file translation mode (one of O_TEXT and O_BINARY)
*
*Exit:
*       returns old file translation mode
*       returns -1 and sets errno if fails
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

int __cdecl _setmode (
        int fh,
        int mode
        )
{
        int retval;
#ifndef _MAC
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
#else  /* _MAC */
        if (fh < 0 || fh >= _nfile)
#endif  /* _MAC */
        {
                errno = EBADF;
                return(-1);
        }

        /* lock the file */
        _lock_fh(fh);

        /* set the text/binary mode */
        retval = _setmode_lk(fh, mode);

        /* unlock the file */
        _unlock_fh(fh);

        /* Return to user (_setmode_lk sets errno, if needed) */
        return(retval);

}

/***
*_setmode_lk() - Perform core setmode operation
*
*Purpose:
*       Core setmode code.  Assumes:
*       (1) Caller has validated fh to make sure it's in range.
*       (2) Caller has locked the file handle.
*
*       [See _setmode() description above.]
*
*Entry: [Same as _setmode()]
*
*Exit:  [Same as _setmode()]
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _setmode_lk (
        REG1 int fh,
        int mode
        )
{
        int oldmode;

#else  /* _MT */

int __cdecl _setmode (
        REG1 int fh,
        int mode
        )
{
        int oldmode;

#ifndef _MAC
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
#else  /* _MAC */
        if ( (fh < 0 || fh >= _nfile) ||
             !(_osfile[fh] & FOPEN) )
#endif  /* _MAC */
        {
                errno = EBADF;
                return(-1);
        }

#endif  /* _MT */

#ifndef _MAC
        oldmode = _osfile(fh) & FTEXT;

        if (mode == _O_BINARY)
                _osfile(fh) &= ~FTEXT;
        else if (mode == _O_TEXT)
                _osfile(fh) |= FTEXT;
        else    {
                errno = EINVAL;
                return(-1);
        }
#else  /* _MAC */
        oldmode = _osfile[fh] & FTEXT;

        if (mode == _O_BINARY)
                _osfile[fh] &= ~FTEXT;
        else if (mode == _O_TEXT)
                _osfile[fh] |= FTEXT;
        else    {
                errno = EINVAL;
                return(-1);
        }
#endif  /* _MAC */

        return(oldmode ? _O_TEXT : _O_BINARY);

}
