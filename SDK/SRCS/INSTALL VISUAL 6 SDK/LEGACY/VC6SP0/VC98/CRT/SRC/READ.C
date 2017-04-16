/***
*read.c - read from a file handle
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _read() - read from a file handle
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <oscalls.h>
#include <mtdll.h>
#include <io.h>
#include <internal.h>
#include <stdlib.h>
#include <errno.h>
#include <msdos.h>

#define LF 10           /* line feed */
#define CR 13           /* carriage return */
#define CTRLZ 26        /* ctrl-z means eof for text */

/***
*int _read(fh, buf, cnt) - read bytes from a file handle
*
*Purpose:
*       Attempts to read cnt bytes from fh into a buffer.
*       If the file is in text mode, CR-LF's are mapped to LF's, thus
*       affecting the number of characters read.  This does not
*       affect the file pointer.
*
*       NOTE:  The stdio _IOCTRLZ flag is tied to the use of FEOFLAG.
*       Cross-reference the two symbols before changing FEOFLAG's use.
*
*Entry:
*       int fh - file handle to read from
*       char *buf - buffer to read into
*       int cnt - number of bytes to read
*
*Exit:
*       Returns number of bytes read (may be less than the number requested
*       if the EOF was reached or the file is in text mode).
*       returns -1 (and sets errno) if fails.
*
*Exceptions:
*
*******************************************************************************/

#ifdef _MT

/* define normal version that locks/unlocks, validates fh */
int __cdecl _read (
        int fh,
        void *buf,
        unsigned cnt
        )
{
        int r;                          /* return value */

        /* validate handle */
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
        {
            /* out of range -- return error */
            errno = EBADF;
            _doserrno = 0;  /* not o.s. error */
            return -1;
        }

        _lock_fh(fh);                   /* lock file */
        r = _read_lk(fh, buf, cnt);     /* read bytes */
        _unlock_fh(fh);                 /* unlock file */

        return r;
}

/* now define version that doesn't lock/unlock, validate fh */
int __cdecl _read_lk (
        int fh,
        void *buf,
        unsigned cnt
        )
{
        int bytes_read;                 /* number of bytes read */
        char *buffer;                   /* buffer to read to */
        int os_read;                    /* bytes read on OS call */
        char *p, *q;                    /* pointers into buffer */
        char peekchr;                   /* peek-ahead character */
        ULONG filepos;                  /* file position after seek */
        ULONG dosretval;                /* o.s. return value */


#else  /* _MT */

/* now define normal version */
int __cdecl _read (
        int fh,
        void *buf,
        unsigned cnt
        )
{
        int bytes_read;                 /* number of bytes read */
        char *buffer;                   /* buffer to read to */
        int os_read;                    /* bytes read on OS call */
        char *p, *q;                    /* pointers into buffer */
        char peekchr;                   /* peek-ahead character */
        ULONG filepos;                  /* file position after seek */
        ULONG dosretval;                /* o.s. return value */

        /* validate fh */
        if ( ((unsigned)fh >= (unsigned)_nhandle) ||
             !(_osfile(fh) & FOPEN) )
        {
            /* bad file handle */
            errno = EBADF;
            _doserrno = 0;              /* not o.s. error */
            return -1;
        }

#endif  /* _MT */

        bytes_read = 0;                 /* nothing read yet */
        buffer = buf;

        if (cnt == 0 || (_osfile(fh) & FEOFLAG)) {
            /* nothing to read or at EOF, so return 0 read */
            return 0;
        }

        if ((_osfile(fh) & (FPIPE|FDEV)) && _pipech(fh) != LF) {
            /* a pipe/device and pipe lookahead non-empty: read the lookahead
             * char */
            *buffer++ = _pipech(fh);
            ++bytes_read;
            --cnt;
            _pipech(fh) = LF;           /* mark as empty */
        }

        /* read the data */

        if ( !ReadFile( (HANDLE)_osfhnd(fh), buffer, cnt, (LPDWORD)&os_read,
                        NULL ) )
        {
            /* ReadFile has reported an error. recognize two special cases.
             *
             *      1. map ERROR_ACCESS_DENIED to EBADF
             *
             *      2. just return 0 if ERROR_BROKEN_PIPE has occurred. it
             *         means the handle is a read-handle on a pipe for which
             *         all write-handles have been closed and all data has been
             *         read. */

            if ( (dosretval = GetLastError()) == ERROR_ACCESS_DENIED ) {
                /* wrong read/write mode should return EBADF, not EACCES */
                errno = EBADF;
                _doserrno = dosretval;
                return -1;
            }
            else if ( dosretval == ERROR_BROKEN_PIPE ) {
                return 0;
            }
            else {
                _dosmaperr(dosretval);
                return -1;
            }
        }

        bytes_read += os_read;          /* update bytes read */

        if (_osfile(fh) & FTEXT) {
            /* now must translate CR-LFs to LFs in the buffer */

            /* set CRLF flag to indicate LF at beginning of buffer */
            if ( (os_read != 0) && (*(char *)buf == LF) )
                _osfile(fh) |= FCRLF;
            else
                _osfile(fh) &= ~FCRLF;

            /* convert chars in the buffer: p is src, q is dest */
            p = q = buf;
            while (p < (char *)buf + bytes_read) {
                if (*p == CTRLZ) {
                    /* if fh is not a device, set ctrl-z flag */
                    if ( !(_osfile(fh) & FDEV) )
                        _osfile(fh) |= FEOFLAG;
                    break;              /* stop translating */
                }
                else if (*p != CR)
                    *q++ = *p++;
                else {
                    /* *p is CR, so must check next char for LF */
                    if (p < (char *)buf + bytes_read - 1) {
                        if (*(p+1) == LF) {
                            p += 2;
                            *q++ = LF;  /* convert CR-LF to LF */
                        }
                        else
                            *q++ = *p++;    /* store char normally */
                    }
                    else {
                        /* This is the hard part.  We found a CR at end of
                           buffer.  We must peek ahead to see if next char
                           is an LF. */
                        ++p;

                        dosretval = 0;
                        if ( !ReadFile( (HANDLE)_osfhnd(fh), &peekchr, 1,
                                        (LPDWORD)&os_read, NULL ) )
                            dosretval = GetLastError();

                        if (dosretval != 0 || os_read == 0) {
                            /* couldn't read ahead, store CR */
                            *q++ = CR;
                        }
                        else {
                            /* peekchr now has the extra character -- we now
                               have several possibilities:
                               1. disk file and char is not LF; just seek back
                                  and copy CR
                               2. disk file and char is LF; seek back and
                                  discard CR
                               3. disk file, char is LF but this is a one-byte
                                  read: store LF, don't seek back
                               4. pipe/device and char is LF; store LF.
                               5. pipe/device and char isn't LF, store CR and
                                  put char in pipe lookahead buffer. */
                            if (_osfile(fh) & (FDEV|FPIPE)) {
                                /* non-seekable device */
                                if (peekchr == LF)
                                    *q++ = LF;
                                else {
                                    *q++ = CR;
                                    _pipech(fh) = peekchr;
                                }
                            }
                            else {
                                /* disk file */
                                if (q == buf && peekchr == LF) {
                                    /* nothing read yet; must make some
                                       progress */
                                    *q++ = LF;
                                }
                                else {
                                    /* seek back */
                                    filepos = _lseek_lk(fh, -1, FILE_CURRENT);
                                    if (peekchr != LF)
                                        *q++ = CR;
                                }
                            }
                        }
                    }
                }
            }

            /* we now change bytes_read to reflect the true number of chars
               in the buffer */
            bytes_read = q - (char *)buf;
        }

        return bytes_read;              /* and return */
}


#else  /* _MAC */


#include <cruntime.h>
#include <io.h>
#include <internal.h>
#include <stdlib.h>
#include <errno.h>
#include <msdos.h>
#include <macos\files.h>
#include <macos\errors.h>
#include <mpw.h>

/***
*int _read(fh, buf, cnt) - read bytes from a file handle
*
*Purpose:
*       Attempts to read cnt bytes from fh into a buffer.
*
*Entry:
*       int fh - file handle to read from
*       char *buf - buffer to read into
*       int cnt - number of bytes to read
*
*Exit:
*       Returns number of bytes read (may be less than the number requested
*       if the EOF was reached or the file is in text mode).
*       returns -1 (and sets errno) if fails.
*
*Exceptions:
*
*******************************************************************************/


int __cdecl _read (
        int fh,
        const void *buf,
        unsigned cnt
        )
{
        OSErr osErr;
        int cbReturn;
        /* validate handle */
        if ( ((unsigned)fh >= (unsigned)_nfile) || !(_osfile[fh] & FOPEN) ||
             (_osfile[fh] & FWRONLY) )
        {
            /* out of range -- return error */
            errno = EBADF;
            _macerrno = 0;
            return -1;
        }

        if (_osfile[fh] & FDEV)
        {
            MPWFILE *pparm;

            /* MPW console */
            pparm = (MPWFILE *)_osfhnd[fh];
            pparm->count = cnt;
            (const void *)(pparm->pBuff) = buf;
            osErr = (*((pparm->pDevice)->read))(pparm);
            if (osErr)
            {
                osErr = pparm->err;
            }
            cbReturn = cnt - pparm->count;
        }
        else
        {
            ParamBlockRec parm;

            /* File */

            parm.ioParam.ioRefNum = _osfhnd[fh];
            (const void *)parm.ioParam.ioBuffer = buf;
            parm.ioParam.ioReqCount = cnt;
            parm.ioParam.ioPosOffset = 0;
            parm.ioParam.ioPosMode = fsAtMark;
            osErr = PBReadSync(&parm);

            cbReturn = parm.ioParam.ioActCount;
        }

        if (!osErr || osErr == eofErr)
        {
            return cbReturn;
        }
        else
        {
            _dosmaperr(osErr);
            return -1;
        }

}


#endif  /* _MAC */
